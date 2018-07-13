//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Clipbrd.hpp>
#pragma hdrstop

#include "megcmd.h"
#include "megson1.h"
#include "jis2001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmCmd *FrmCmd;
//---------------------------------------------------------------------------
#define INI(X) FrmMeg1->li_ini->Values[X]
#define BUFSIZE 8192
__fastcall TFrmCmd::TFrmCmd(TComponent* Owner)
        : TForm(Owner)
{isRun=false;CurrentDir=GetCurrentDir();kukeiCopy=0;
 if(INI("CWidth")!=""){
  FrmCmd->Width=StrToInt(INI("CWidth"));
  FrmCmd->Height=StrToInt(INI("CHeight"));
  FrmCmd->Left=StrToInt(INI("CLeft"));
  FrmCmd->Top=StrToInt(INI("CTop"));
  FrmCmd->Memo1->Font->Charset=(TFontCharset)StrToInt(INI("CFCharSet"));
  FrmCmd->Memo1->Font->Color=(TColor)StrToInt(INI("CFColor"));
  FrmCmd->Memo1->Font->Name=INI("CFName");
  FrmCmd->Memo1->Font->Size=StrToInt(INI("CFSize"));
  FrmCmd->Edit1->Font=FrmCmd->Memo1->Font;
  FrmCmd->Memo1->Color=Memo1->Color;
  FrmCmd->Memo1->WordWrap=(INI("CWrap")=="1")?true:false;
  FrmCmd->Memo1->ScrollBars=(FrmCmd->Memo1->WordWrap)?ssVertical:ssBoth;
  FrmCmd->mnWrap->Checked=FrmCmd->Memo1->WordWrap;}
// FrmMeg1->strRegcode=FrmMeg1->strRegcode+"BtQNaCk";
// FrmMeg1->isReg=FrmMeg1->chkRegcode(INI("Regcode"));
// if(!FrmMeg1->isReg){FrmMeg1->Caption=FrmMeg1->Caption+FrmMeg1->strDecrypt("taIeaKdaMpYaLiaAnaAo",40);FrmMeg1->Show();
//  Application->MessageBox("Megson Proはｼｪｱｳｪｱです。\n送金方法についてはreadme.txtをご覧ください。\n登録前は保存するﾃｷｽﾄの2行目の語尾にｸﾚｼﾞｯﾄが挿入されます。","ｼｪｱｳｪｱ",MB_OK);}
}
//---------------------------------------------------------------------------
/*void __fastcall TFrmCmd::ToSjis(AnsiString &st,char *des,bool sql){
 int len;char *buf;
 if(!mnKanji->Checked){COPYONLY:st=st+StrPas(des);return;}
 AnsiString knj=(sql)?INI("Dbknj"):FrmMeg1->li_knj->Strings[FrmMeg1->index];
 if(knj=="EUC"){len=FrmMeg1->g.EucToSjis(NULL,des,0);buf=new char[len+4];
  FrmMeg1->g.EucToSjis(buf,des,len+4);}
// else if(knj=="JIS"){FrmMeg1->g.Iso2022jpToSjis(res,des,BUFSIZE*2-1);return;}
 else goto COPYONLY;
 st=st+StrPas(buf);delete buf;

 /* else {switch(FrmMeg1->g.GetKanjiCodeType(des,BUFSIZE-1)){
  case JIS2K_JIS:Memo1->Lines->Add("JIS");FrmMeg1->g.Iso2022jpToSjis(res,des,BUFSIZE*2-1);break;
  case JIS2K_EUC:Memo1->Lines->Add("EUC");FrmMeg1->g.EucToSjis(res,des,BUFSIZE*2-1);break;
  default:goto COPYONLY;}}}*/

void __fastcall TFrmCmd::Exec(AnsiString cmd,AnsiString dir,bool sql){
  HANDLE hReadPipe, hWritePipe;
  HANDLE hStdInReadPipe, hStdInWritePipe, hStdInWritePipeDup;
  HANDLE hErrReadPipe, hErrWritePipe;
  SECURITY_ATTRIBUTES sa;
  STARTUPINFO StartupInfo;
  char bufStdOut[BUFSIZE],*bufErrOut,*bufStdIn;
  DWORD dwStdOut, dwErrOut, dwRet;
  DWORD StreamBufferSize, nWritten;
  TMemoryStream *stdIn;
  AnsiString st,rst;
  int i,ly=Memo1->Lines->Count;
  bufErrOut=bufStdOut;bufStdIn=bufStdOut;
 if(isRun){Application->MessageBox("running...","Console",MB_OK);return;}
 isRun=true;Caption="Console_"+((sql)?(AnsiString)"SQL...":cmd);
 if(!sql)Edit1->Text=cmd;

 sa.nLength= sizeof(SECURITY_ATTRIBUTES);
 sa.lpSecurityDescriptor=NULL;
 sa.bInheritHandle=true;

 hReadPipe=0; hWritePipe=0;
 hErrReadPipe=0; hErrWritePipe=0;
 stdIn=new TMemoryStream(); stdIn->Position=0;
 rst="";

 CreatePipe(&hStdInReadPipe, &hStdInWritePipe,&sa,BUFSIZE);
 DuplicateHandle(GetCurrentProcess(),hStdInWritePipe,GetCurrentProcess(),&hStdInWritePipeDup,0,false,DUPLICATE_SAME_ACCESS);
 CloseHandle(hStdInWritePipe);

 CreatePipe(&hReadPipe,&hWritePipe, &sa, BUFSIZE);
 try{CreatePipe(&hErrReadPipe,&hErrWritePipe, &sa, BUFSIZE);
  try{
   ZeroMemory(&StartupInfo,sizeof(STARTUPINFO));
   StartupInfo.cb=sizeof(STARTUPINFO);
   StartupInfo.dwFlags= STARTF_USESTDHANDLES;
   StartupInfo.wShowWindow= SW_HIDE; // これがないと DOS 窓が表示されてしまう
   StartupInfo.hStdInput= hStdInReadPipe; // 標準 IO にパイプの端っこを指定してやる
   StartupInfo.hStdOutput= hWritePipe;
   StartupInfo.hStdError = hErrWritePipe;
      // コンソールアプリ起動
   if(CreateProcess(NULL,cmd.c_str(),&sa,NULL,true,DETACHED_PROCESS,NULL,dir.c_str(),&StartupInfo,&ProcessInfo)==true){
    WaitForInputIdle(ProcessInfo.hProcess,1000);// 入力待ちになるまで待ってから，
    StreamBufferSize=BUFSIZE;
    while(StreamBufferSize==BUFSIZE){// 入力を与える
     StreamBufferSize = stdIn->Read(bufStdIn,BUFSIZE);
     WriteFile(hStdInWritePipeDup, &bufStdIn, StreamBufferSize, &nWritten,NULL);}
    CloseHandle(hStdInWritePipeDup);

    try{
     do{Application->ProcessMessages();Sleep(50);
      PeekNamedPipe(hReadPipe, NULL, 0, NULL, &dwStdOut, NULL);
      if(dwStdOut>0){
       ReadFile(hReadPipe,bufStdOut,BUFSIZE-1,&dwStdOut,NULL);
       bufStdOut[dwStdOut]=0;rst=rst+StrPas(bufStdOut);//ToSjis(rst,bufStdOut,sql);
//       rst=rst+ToSjis(bufStdOut,sql);
//       StrPas(bufStdIn);
       //Memo1->Lines->Text.Insert(StrPas(bufStdIn),Memo1->Lines->Text.Length());
//       Memo1->Lines->Add(StrPas(bufStdIn));
       }
      PeekNamedPipe(hErrReadPipe, NULL, 0, NULL, &dwErrOut, NULL);
      if(dwErrOut>0){
       ReadFile(hErrReadPipe, bufErrOut,BUFSIZE-1, &dwErrOut, NULL);
       bufErrOut[dwErrOut]=0;rst=rst+StrPas(bufErrOut);/*ToSjis(bufErrOut,bufStdIn,sql);
       rst=rst+StrPas(bufStdIn);ToSjis(rst,bufErrOut,sql);*/}
      dwRet = WaitForSingleObject(ProcessInfo.hProcess, 0);
      }while(dwRet!=WAIT_OBJECT_0);// コンソールアプリのプロセスが存在している間

      CloseHandle(ProcessInfo.hProcess);
      CloseHandle(ProcessInfo.hThread);
      CloseHandle(hStdInReadPipe);
     }catch(...){
      CloseHandle(ProcessInfo.hProcess);
      CloseHandle(ProcessInfo.hThread);
      CloseHandle(hStdInReadPipe);}
   }}catch(...){CloseHandle(hErrReadPipe);CloseHandle(hErrWritePipe);
 }}catch(...){CloseHandle(hReadPipe);CloseHandle(hWritePipe);}
 delete stdIn;

 int len;char *buf;
 AnsiString knj=(sql)?INI("Dbknj"):FrmMeg1->li_knj->Strings[FrmMeg1->index];
 if(mnKanji->Checked){
  if(knj=="EUC"){len=EucToSjis(NULL,rst.c_str(),0);buf=new char[len+4];
   EucToSjis(buf,rst.c_str(),len+4);}
  else if(knj=="JIS"){len=Iso2022jpToSjis(NULL,rst.c_str(),0);buf=new char[len+4];
   Iso2022jpToSjis(buf,rst.c_str(),len+4);}
  else goto POKO;
// else if(knj=="JIS"){FrmMeg1->g.Iso2022jpToSjis(res,des,BUFSIZE*2-1);return;}
  rst=StrPas(buf);delete buf;}

 POKO:

//  TStringList *li_buf=new TStringList();li_buf->Add(rst);
//  for(i=0;i<li_buf->Count;i++){Memo1->Lines->Add(li_buf->Strings[i]);}
//  Application->MessageBox(IntToStr(li_buf->Count).c_str(),"",MB_OK);
//  delete li_buf;
// while((i=AnsiPos("\xd",rst))!=0){rst.Delete(i,1);}
// FrmMeg1->strReplace(rst,"\xd\xd\xa","\xd\xa");
// FrmMeg1->strReplace(rst,"\xa","%|R!");
// FrmMeg1->strReplace(rst,"\xa","\xd\xa");
// FrmMeg1->strReplace(rst,"%|R!","\xd\xa");
 for(i=1;i<=rst.Length()-3;i++){
  if(rst[i]==13&&rst[i+1]==13&&rst[i+2]==10)rst[i]=' ';}
// while((i=rst.Pos("\xd\xd\xa"))!=0){rst.Delete(i,1);}
 Memo1->Lines->Add(rst);
 isRun=false;Caption="Console_";CurrentDir=dir;
 if(sql&&Memo1->Lines->Count>ly+1&&AnsiPos("-",Memo1->Lines->Strings[ly+2])==1)Edit1->Text=Memo1->Lines->Strings[ly+1];
 }

void __fastcall TFrmCmd::FormResize(TObject *Sender)
{
 Edit1->Width=ClientWidth-Button1->Width;
 Button1->Left=ClientWidth-Button1->Width;
 Edit1->Height=-Edit1->Font->Height+6;
 Button1->Height=Edit1->Height;
 Memo1->Width=ClientWidth;
 Memo1->Height=ClientHeight-Edit1->Height;
 Memo1->Top=Edit1->Height;
}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnCommitClick(TObject *Sender)
{
 if(mnCommit->Checked){mnCommit->Tag=0;mnCommit->Checked=false;mnCommit->Caption="Rollba&ck";}
 else{mnCommit->Tag=1;mnCommit->Checked=true;mnCommit->Caption="&Commit";}
}
//---------------------------------------------------------------------------
// Exec(Memo1->Lines->Strings[CursorY()],CurrentDir,false);
void __fastcall TFrmCmd::mnCloseClick(TObject *Sender)
{Close();}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnFontClick(TObject *Sender)
{TFontDialog *FontDialog1=new TFontDialog(FrmCmd);
 FontDialog1->Font=Memo1->Font;
 if(FontDialog1->Execute()){
  Memo1->Font=FontDialog1->Font;
  Edit1->Font=FontDialog1->Font;
//  Edit1->Height=-Edit1->Font->Height;
  FormResize(Sender);
  }delete FontDialog1;
}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnEditFocusClick(TObject *Sender)
{
 FrmMeg1->Show();
}

/*void __fastcall TFrmCmd::Sachi(AnsiString FindText){
 AnsiString se;
 char *buf,*ft,*p,*q,*pp,c,c1;int a,b,i,j;
 bool ck=(FindDialog1->Options.Contains(frMatchCase))?true:false;
 a=Memo1->GetTextLen();
 if(a==0)return;
 b=FindText.Length();
 if(b==0||b>a)return;
 buf=StrAlloc(a+1);
 ft=StrAlloc(b+1);
 Memo1->GetTextBuf(buf,a);StrPCopy(ft,FindText);
 i=Memo1->SelStart+1;p=buf+i;c1=(!ck)?(char)toupper(*ft):*ft;
 for(;i<a-b;i++){
  c=(!ck)?(char)toupper(*p):*p;//c=(!ck)?:toupper(*p);//      ||(ck&&toupper(*q)==toupper(*pp))
  if(c==c1){
   q=ft;pp=p;j=0;while(*q){if(*q==*pp||(!ck&&toupper(*q)==toupper(*pp)))++j;++q;++pp;}
   if(j==b){
    Memo1->SelStart=i;
    Memo1->SelLength=b;
    se=Memo1->SelText;Memo1->SelText=se;
    Memo1->SelStart=i;
    Memo1->SelLength=b;
    goto END;}}
  ++p;}
  Application->MessageBox("なし","検索",MB_OK);
END:
 StrDispose(ft);StrDispose(buf);}*/
 
// FindText(FindText,MatchCase?) true:あった false:なかった
bool __fastcall TFrmCmd::FindText(AnsiString txt,bool MatchCase){
 int i,j,x,xx;
 AnsiString ltxt;
 if(Memo1->SelLength){Memo1->SelStart+=Memo1->SelLength;Memo1->SelLength=0;}
 Memo1->SelLength=0;
 ltxt=Memo1->Lines->Text;
 if(!MatchCase){txt=txt.LowerCase();ltxt=ltxt.LowerCase();}
 xx=Memo1->SelStart;
 for(i=1;i<=xx;i++)ltxt[i]=1;
 if((x=ltxt.AnsiPos(txt))!=0){
  Memo1->SelStart=x-1;
  Memo1->SelLength=txt.Length();return true;}
 return false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::Find(void){
//Sachi(FindDialog1->FindText);FindDialog1->CloseDialog();
 FindDialog1->CloseDialog();
 if(!FindText(FindDialog1->FindText,FindDialog1->Options.Contains(frMatchCase)))
 Application->MessageBox("なし","検索",MB_OK);}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnFindClick(TObject *Sender)
{FindDialog1->Execute();}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnFindNextClick(TObject *Sender)
{if(FindDialog1->FindText=="")FindDialog1->Execute();else Find();
//Sachi(FindDialog1->FindText);
}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::FindDialog1Find(TObject *Sender)
{Find();}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnWrapClick(TObject *Sender)
{
 if(mnWrap->Checked){mnWrap->Checked=false;
  Memo1->ScrollBars=ssBoth;Memo1->WordWrap=false;}
 else{mnWrap->Checked=true;
  Memo1->ScrollBars=ssVertical;Memo1->WordWrap=true;}}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnKanjiClick(TObject *Sender)
{mnKanji->Checked=(mnKanji->Checked)?false:true;}
//---------------------------------------------------------------------------
int __fastcall TFrmCmd::CursorX(void){
 int a=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);
 return Memo1->SelStart-Memo1->Perform(EM_LINEINDEX,a, 0);}
int __fastcall TFrmCmd::CursorY(void){return Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);}

void __fastcall TFrmCmd::Memo1Change(TObject *Sender){SetMenuCol();}

void __fastcall TFrmCmd::SetMenuCol(void){
if(kukeiCopy==0){menuCol->Caption=IntToStr(CursorY()+1)+":"+IntToStr(CursorX()+1);}}

//---------------------------------------------------------------------------

void __fastcall TFrmCmd::N1Click(TObject *Sender)
{Memo1->SelectAll();}
//---------------------------------------------------------------------------

void __fastcall TFrmCmd::N4Click(TObject *Sender)
{Memo1->Clear();SetMenuCol();}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::Memo1Click(TObject *Sender)
{SetMenuCol();}
//---------------------------------------------------------------------------

void __fastcall TFrmCmd::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{SetMenuCol();
 switch(Key){
  case VK_ESCAPE: if(isRun)TerminateProcess(ProcessInfo.hProcess,0);break;
  case VK_RETURN: if(((TWinControl*)Sender)->Tag)Exec(Edit1->Text,CurrentDir,false);break;}
}
//---------------------------------------------------------------------------

void __fastcall TFrmCmd::Excel1Click(TObject *Sender)
{
 char buf[256];
 TStringList *li=new TStringList();
 AnsiString fi,fi2;//=ExtractFilePath(Application->ExeName)+"temp.csv";
 int a=1;
 do{fi=ExtractFilePath(Application->ExeName)+"temp"+IntToStr(a)+".csv";
  fi2=ExtractFilePath(Application->ExeName)+"temp"+IntToStr(a)+".cst";
 ++a;}while(FileExists(fi)||FileExists(fi2));
 int i;
 li->Text=Memo1->SelText;
 li->SaveToFile(fi);
 if(((TComponent *)Sender)->Tag==0){
  ShellExecute(Handle,"open",fi.c_str(),"","",SW_SHOW);}
 else{
  FindExecutable(fi.c_str(),NULL,buf);
//  fi2=ChangeFileExt(fi,".cst");
  RenameFile(fi,fi2);
  WinExec(("\x22"+StrPas(buf)+"\x22 \x22"+fi2+"\x22").c_str(),SW_SHOW);
  }
 delete li;
}
//---------------------------------------------------------------------------



void __fastcall TFrmCmd::N5Click(TObject *Sender)
{int i,toX,toY;AnsiString st;
 if(kukeiCopy==0){
  kukeiCopyX=CursorX();
  kukeiCopyY=CursorY();
  kukeiCopy=1;menuCol->Caption="["+IntToStr(kukeiCopyY+1)+","+IntToStr(kukeiCopyX+1)+"]";
 }else{toX=CursorX();toY=CursorY();st="";
  for(i=kukeiCopyY;i<=toY;i++){if(i!=kukeiCopyY)st=st+"\xd\xa";
   st=st+Memo1->Lines->Strings[i].SubString(kukeiCopyX+1,toX-kukeiCopyX);}
  Clipboard()->AsText=st;
  kukeiCopy=0;menuCol->Caption=IntToStr(toY+1)+":"+IntToStr(toX+1);
  //mnKukeiCopy->Caption="矩形ｺﾋﾟｰ";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmCmd::mnSaveSelectClick(TObject *Sender)
{AnsiString st;
 SaveDialog1->InitialDir=ExtractFileDir(FrmMeg1->li_file->Strings[FrmMeg1->index]);
 st=FrmMeg1->Memo1->SelText;

 if(st.Length()<256&&st.AnsiPos("\r")==0&&st.AnsiPos("\n")==0){
  SaveDialog1->FileName=FrmMeg1->Memo1->SelText;}
 else SaveDialog1->FileName="";
 if(SaveDialog1->Execute()){
  TStringList *li=new TStringList();
  li->Text=Memo1->SelText;
  li->SaveToFile(SaveDialog1->FileName);}
}
//---------------------------------------------------------------------------



