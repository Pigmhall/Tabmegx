//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <dir.h>
#pragma hdrstop
#define BUFSIZE 8192
#define getkey(KY) GetKeyState(KY)&0x80

#include "gobln1.h"
#include "BRegExp.hpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
TBRegExp *br;
TStringList *li_src;
AnsiString di_src;
TStringList *li_replace;
AnsiString pa;
AnsiString errMes;int errPos;
char gbuf[1024];
//---------------------------------------------------------------------------
HWND FindWind(AnsiString ch){
 HWND CurrWnd=GetWindow(Form1->Handle,GW_HWNDFIRST);
 while(CurrWnd){
  GetWindowText(CurrWnd,gbuf,256);
  if(AnsiPos(ch,StrPas(gbuf)))return CurrWnd;
  CurrWnd=GetWindow(CurrWnd,GW_HWNDNEXT);}
 return 0;}

void closeDbApps(AnsiString fi){HWND han;
 int a=fi.AnsiPos(".");fi=fi.SubString(1,a-1);
 while((han=FindWindow((fi+"12345").c_str(),fi.c_str()))!=0){
  PostMessage(han,WM_CLOSE,0,0);}}

void error(AnsiString st,int pos){
 errPos=pos;
 errMes=st;
 throw "Error";}

int posNextOpen(AnsiString st,int po){
 int pos=po;int max=st.Length();char a;
 while(pos!=max&&(a=st[pos])!='{'){++pos;}
 if(pos==max)error("not {",po);
 return pos;}

int posNextClose(AnsiString st,int po){
 int pos=po;int d=0;int max=st.Length();char a;
 while(pos!=max&&((a=st[pos])!='}'||d)){
  if(a=='{')++d;
  if(a=='}'&&d)--d;++pos;}
 if(pos==max)error("not }",po);
 return pos;}

int posNextClose2(AnsiString st,int po){
 int pos=po;int d=0;int max=st.Length();char a;
 while(pos!=max&&((a=st[pos])!=')'||d)){
  if(a=='(')++d;
  if(a==')'&&d)--d;++pos;}
 if(pos==max)error("not )",po);
 return pos;}

int posNextRemClose(AnsiString st,int po){
 int pos=po;int max=st.Length();
 while(pos!=max-1&&(st[pos]!='*'||st[pos+1]!='/'))++pos;
 if(pos==max-1)error("not */",po);
 return pos;}

int posNextElse(AnsiString st,int pos){
 int max=st.Length();char a;
 while(pos!=max&&(a=st[pos])<33){++pos;}
 if(pos>max-4)return -1;
 if(st[pos]=='e'&&st[pos+1]=='l'&&st[pos+2]=='s'&&st[pos+3]=='e'&&st[pos+4]=='{')return pos;
 return -1;}

void convertIfElse(AnsiString &st){
 int a,a2;
 while((a=st.AnsiPos("if("))>0){
  st[a+2]=' ';a=posNextClose2(st,a);st[a]=':';
  a=posNextOpen(st,a);
  st[a]=' ';
  a=posNextClose(st,a);
  a2=posNextElse(st,a+1);
  if(a2!=-1){st[a]=' ';st[a2+4]=':';}
  a=posNextClose(st,a);
  if(a!=-1){st[a]=':';st.Insert("endif",a);}
 }}

int convert(void){
 AnsiString st,st2;int a,a2,i;char c;
 TStringList *li_buf;
 errPos=1;
 try{

 // -- if～else
 // -- add lineno.
/* li_src->Text=st;
 for(i=0;i<li_src->Count;i++){li_src->Strings[i]=li_src->Strings[i]+"`L^"+IntToStr(i+1);}
 st=li_src->Text;*/

 // -- include
 for(i=0;i<li_src->Count;i++){
  st2=li_src->Strings[i];
  if((a=st2.AnsiPos("#include "))==1){
   a+=10;a2=a;while(a2!=st2.Length()&&st2[a2]!='\"'){++a2;}
   AnsiString fi=di_src+st2.SubString(a,a2-a),st2;
   errMes=fi;
   li_buf=new TStringList();
   li_buf->LoadFromFile(fi);
   li_src->Delete(i);
   li_src->Insert(i,li_buf->Text);
   delete li_buf;}}

/* while((a=st.AnsiPos("#include "))>0){
  st[a]='`';a+=10;a2=a;while(a2!=st.Length()&&st[a2]!='\"'){++a2;}
  AnsiString fi=di_src+st.SubString(a,a2-a),st2;
  errMes=fi;
  li_buf->LoadFromFile(fi);
//  st2=li_buf->Text;li_buf->Text=st2;
  fi=st.SubString(a,2);
//  for(i=0;i<li_buf->Count;i++){li_buf->Strings[i]=li_buf->Strings[i]+"`"+fi+"^"+IntToStr(i+1);}
  st.Insert("\n"+li_buf->Text,a2+1);}
 delete li_buf;*/

 // first Replace
 li_buf=new TStringList();
 for(i=0;i<li_src->Count;i++){
  st2=li_src->Strings[i];
  if((a=st2.AnsiPos("#replace "))==1){
   st2.Delete(1,9);li_buf->Add(st2);li_src->Delete(i);}}
 st=li_src->Text;//←←← ｿｰｽをstへ
 for(i=0;i<li_buf->Count;i++){
  st2=li_buf->Strings[i];errMes=st2;
  br->Split("m/,/",st2,2);
  AnsiString r1=br->Strings[0],r2=br->Strings[1];
  br->Subst("s/"+r1+"/"+r2+"/g",st);}
 delete li_buf;

 //-- rem
 while((a=st.AnsiPos("/*"))>0){
  a2=posNextRemClose(st,a);st.Delete(a,a2-a+2);}

 convertIfElse(st);

 // -- for
 while((a=st.AnsiPos("for("))>0){
  st[a+3]=' ';a=posNextClose2(st,a);st[a]=' ';
  a=posNextOpen(st,a);st[a]=':';
  a=posNextClose(st,a);st[a]=':';st.Insert("next",a);}

 // -- do
 while((a=st.AnsiPos("do{"))>0){
  st[a+2]=':';a=posNextClose(st,a);st[a]=' ';st.Insert("loop",a);}

 // -- select
 while((a=st.AnsiPos("switch("))>0){
  st[a+6]=' ';a=posNextClose2(st,a);st[a]=' ';
  a=posNextOpen(st,a);st[a]=':';
  a=posNextClose(st,a);st[a]=':';st.Insert("\nendselect",a);}

 // -- while
 while((a=st.AnsiPos("while("))>0){
  st[a+5]=' ';a=posNextClose2(st,a);st[a]=' ';
  a=posNextOpen(st,a);st[a]=':';
  a=posNextClose(st,a);st[a]=':';st.Insert("endwhile",a);}

 // -- dim
 while((a=st.AnsiPos("dim "))>0){
  st[a]='D';
  while(a!=st.Length()&&(c=st[a])!=';'){
   if(c==','&&st[a-1]==']'){st[a]=' ';st.Insert(":Dim",a);}++a;}}

 // const
 while((a=st.AnsiPos("const "))>0){
  st[a]='`';
  st.Insert("\n#constant",a+5);
  while(a!=st.Length()&&(c=st[a])!=';'){
   if(c==','){st[a]=' ';st.Insert("\n#constant",a);}++a;}
  st[a]='\n';
   }

 //type
 while((a=st.AnsiPos("type "))>0){
  st[a]='T';a=posNextOpen(st,a);st[a]='\n';
  while(a!=st.Length()&&(c=st[a])!='}'){
   if(c==','){st[a]=':';
    if(st[a-1]=='$')st2=" as string";else if(st[a-1]=='#')st2=" as float";else st2=" as integer";
    st.Insert(st2,a);}++a;}
  st[a]=' ';
  if(st[a-1]=='$')st2=" as string";else if(st[a-1]=='#')st2=" as float";else st2=" as integer";
  st.Insert(st2+"\nendtype:",a);
   }

 //sub
 while((a=st.AnsiPos("sub "))>0){
  st[a]='S';a=posNextOpen(st,a);st[a]=':';
  a=posNextClose(st,a);
  a2=a;while(st[a2]!=';')--a2;--a2; // 戻り値が文字か
  i=0;while((c=st[a2])!=';'){if(c=='$')i=1;--a2;}
  st[a]=':';if(i)st.Insert("\nendfunction \x22\x22",a);else st.Insert("\nendfunction 0",a);}

  // simple Replace
 for(i=0;i<li_replace->Count;i++){
  st2=li_replace->Strings[i];errMes=st2;
  br->Split("m/,/",st2,2);
  AnsiString r1=br->Strings[0],r2=br->Strings[1];
  br->Subst("s/"+r1+"/"+r2+"/g",st);}
 errPos=0;
 }catch(...){
  Form1->Memo2->Lines->Add(errMes);
  /*Application->MessageBox(errMes.c_str(),"Error",MB_OK);*/}

 if(errPos){st.Insert("<*>",errPos);
  Form1->Memo1->Lines->Text=st;
  Form1->Memo1->SelStart=Form1->Memo1->Lines->Text.AnsiPos("<*>");
  Form1->Timer1->Enabled=true;return 0;}
 else Form1->Memo1->Lines->Text=st;

 return 1;
 }

//------------------------------- Start
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
 AnsiString st,fi,fi_exe,di_db,cmd;int i;char mo;bool isRun,isCompile;
 br=new TBRegExp();

 pa=ExtractFilePath(Application->ExeName);
 fi="";
 //--- command line
 li_src=new TStringList();mo=0;isRun=false;isCompile=false;
 for(i=1;i<=ParamCount();i++){
  AnsiString co=ParamStr(i);
  if(mo==0){
   if(co=="-g")mo=1;
   else if(co=="-d")mo=2;
   else if(co=="-r")isRun=true;}
  else if(mo==1){mo=0;fi=co;}
  else if(mo==2){mo=0;di_db=co;isCompile=true;}}

 if(fi==""){Memo2->Lines->Add("gobln.exe [-g file.g] [-d DBDir] [-r]");return;}
 Caption=Caption+" - "+fi;
 di_src=ExtractFilePath(fi);
 li_src->LoadFromFile(fi);
 li_replace=new TStringList();
 li_replace->LoadFromFile(pa+"replace.def");
 fi=ChangeFileExt(fi,".dbpro");
// if(!FileExists(fi)){Memo2->Lines->Add(fi+" not found");goto SKIP1;}
 closeDbApps(ExtractFileName(fi));
 if(convert()){
  Memo1->Lines->SaveToFile(ChangeFileExt(fi,".dba"));
  if(isCompile){
   fi_exe=ChangeFileExt(fi,".exe");
   fi=ChangeFileExt(fi,".dbpro");
   unlink(fi_exe.c_str());
   cmd=di_db+"Compiler\\DBPCompiler.exe "+fi;
//   Memo2->Lines->Add(di_src);
//   Memo2->Lines->Add(cmd);
   Exec(cmd,di_src);
// HWND han;  if((han=FindWind("COMPILER ERROR"))>0){SendMessage(han,WM_CLOSE,0,0);
//   WinExec(cmd.c_str(),SW_SHOW);
   if(!FileExists(fi_exe)){
    li_src->LoadFromFile(di_db+"TEMP\\ErrorReport.txt");
    st=li_src->Strings[2];
    if((i=st.Pos("line"))!=0){st.Delete(1,i+4);st.Delete(st.Length(),1);
     Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,StrToInt(st)-1,0);
     li_src->Delete(0);li_src->Delete(0);li_src->Delete(1);li_src->Delete(1);li_src->Delete(1);
     Memo2->Lines->Text=li_src->Text;
     Timer1->Enabled=true;
//     Memo1->SelText="<*>";
     }
   }
   else{if(isRun){chdir(di_src.c_str());WinExec(fi_exe.c_str(),SW_SHOW);}
   ClientWidth=0;ClientHeight=0;Top=-100;
   Application->Terminate();
    }
   }
//  HWND han=FindWind("DarkBASIC Professional Editor");if(han){SetForegroundWindow(han);}
//
  }
 ModifyCol();
 SKIP1:
 delete br;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ModifyCol(void){
 int a=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);
 int x=Memo1->SelStart-Memo1->Perform(EM_LINEINDEX,a, 0);
 int y=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);
 Label1->Caption=IntToStr(y+1)+":"+IntToStr(x+1);}

void __fastcall TForm1::Memo1KeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{switch(Key){
 case VK_ESCAPE:Close();break;
 case VK_F5:
//  HWND han=FindWind("DarkBASIC Professional Editor");
//  if(han){SetForegroundWindow(han);}
//  keybd_event(VK_F5,MapVirtualKey(VK_F5,0),0,0); // Ctrlキーを押す
//  keybd_event(VK_F5,MapVirtualKey(VK_F5,0),KEYEVENTF_KEYUP,0);// Ctrlキーを離す
  break;
 case 'S':if(Shift.Contains(ssAlt)){FindDialog1->Execute();}break;
 case 'L':if(Shift.Contains(ssCtrl)){if(FindDialog1->FindText=="")FindDialog1->Execute();else Find();}break;
 //case VK_F9:Memo1->SelText="<*>";break;
 } ModifyCol();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exec(AnsiString cmd,AnsiString dir){
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
 bufErrOut=bufStdOut;bufStdIn=bufStdOut;
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
// Memo1->Lines->Add(rst);
 }

void __fastcall TForm1::Memo1KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{ModifyCol();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Memo1Scroll(void){
int a=Memo1->SelStart;Memo1->SelText="1";Memo1->SelStart=a;
 Memo1->SelLength=1;Memo1->SelText="";}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{Memo1Scroll();
 Timer1->Enabled=false;}
//---------------------------------------------------------------------------
void __fastcall TForm1::Memo2MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
 int a,y=Memo2->Perform(EM_LINEFROMCHAR,Memo2->SelStart, 0);
 AnsiString st=Memo2->Lines->Strings[y];
 if((a=Memo1->Lines->Text.AnsiPos(st))>0){
  Memo1->SelStart=a;Memo1Scroll();Memo1->SetFocus();}}
//---------------------------------------------------------------------------

//----- FindText(FindText,MatchCase?) true:あった false:なかった
bool __fastcall TForm1::FindText(AnsiString txt,bool MatchCase){
 int i,x,xx;
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
 return false;}

//----- 検索実行
void __fastcall TForm1::Find(void){
 FindDialog1->CloseDialog();
 if(!FindText(FindDialog1->FindText,FindDialog1->Options.Contains(frMatchCase)))
  Application->MessageBox("なし","検索",MB_OK);
 else Memo1->SelText=Memo1->SelText;}

void __fastcall TForm1::FindDialog1Find(TObject *Sender)
{Find();}
//---------------------------------------------------------------------------
