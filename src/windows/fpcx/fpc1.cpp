//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <dir.h>
#pragma hdrstop

#include "fpc1.h"
#include "BRegExp.hpp"
#include <shlobj.h>
#include <windowsx.h>
#include "oledragdrop.h"
#define INI(X) li_ini->Values[X]
//---------------------------------------------------------------------------
//c:\projects\fpc\test.bas C:\apps\qqbas119
//c:\projects\fpc\test.bas view
#pragma resource "*.dfm"
TForm1 *Form1;
TBRegExp *br;
TStringList *li_replace,*li_ini;
const EM_BLUEMSX=0,EM_OPENMSX=1;
AnsiString errMes,pa;int errPos,ti,emKind,moRom;
AnsiString fi_dsk,fi_bas,fi_bas2,fi_openBload,fi_editdisk,fi_bluemsx,st_org;
bool drag_dsk,up_only;
// ﾄﾞﾗｯｸﾞｴﾐｭﾚｰｼｮﾝ
typedef struct{
 WORD wSize;
 POINT ptMousePos;
 BOOL fInNonClientArea;} DROPFILESTRUCT, FAR *LPDROPFILESTRUCT;

HDROP FAR DragCreateFiles(void){
 HGLOBAL hDrop;
 LPDROPFILESTRUCT lpDropFileStruct;

 hDrop=GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE|GMEM_ZEROINIT,sizeof(DROPFILESTRUCT)+1);
 if(hDrop==NULL)return((HDROP)hDrop);
 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);
 lpDropFileStruct->wSize=sizeof(DROPFILESTRUCT);
 lpDropFileStruct->fInNonClientArea=true;
// lpDropFileStruct->ptMousePos.x=x;lpDropFileStruct->ptMousePos.y=y;
 GlobalUnlock(hDrop);
 return((HDROP)hDrop);}

HDROP FAR DragAppendFile(HGLOBAL hDrop, LPCSTR szPathname){
 LPDROPFILESTRUCT lpDropFileStruct;
 LPCSTR lpCrnt; WORD wSize;
 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);
 lpCrnt=(LPSTR)lpDropFileStruct+lpDropFileStruct->wSize;
 while(*lpCrnt){
  while(*lpCrnt)lpCrnt++;lpCrnt++;}

 wSize=(WORD)(lpCrnt-(LPSTR)lpDropFileStruct+1);
 GlobalUnlock(hDrop);
 hDrop=GlobalReAlloc(hDrop,wSize+lstrlen(szPathname)+1,GMEM_SHARE|GMEM_MOVEABLE|GMEM_ZEROINIT);
 if(!hDrop)return((HDROP)hDrop);

 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);
 lstrcpy((LPSTR)lpDropFileStruct+wSize-1,szPathname);
 GlobalUnlock(hDrop);
 return((HDROP)hDrop);}

//--- ウィンド検索 (ﾀｲﾄﾙﾊﾞｰ) ハンドルを返す
HWND FindWind(AnsiString ch){
 char gbuf[256];
 HWND CurrWnd=GetWindow(Form1->Handle,GW_HWNDFIRST);
 while(CurrWnd){
  GetWindowText(CurrWnd,gbuf,256);
  if(AnsiPos(ch,StrPas(gbuf)))return CurrWnd;
  CurrWnd=GetWindow(CurrWnd,GW_HWNDNEXT);}
 return 0;}

//---------------------------------------------------------------------------
void __fastcall TForm1::hideWindow(void){
 Position=poDesigned;Left=-1000;ClientWidth=200;
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
 AnsiString fi,fi2,ext;int i;
 pa=ExtractFilePath(Application->ExeName);
 br=new TBRegExp();
 li_replace=new TStringList();
 li_replace->LoadFromFile(pa+"basrep.def");
 li_ini=new TStringList();
 fi_dsk=pa+"fpcx.dsk";
 fi_bas=pa+"autoexec.bas";//;ChangeFileExt(fi,".tmp");
 ti=0;
 for(i=1;i<=ParamCount();i++)li_ini->Add(ParamStr(i));

// if(ParamCount()==1&&INI("view")==1){Memo1->Lines->LoadFromFile(fi_bas);return;}
fi_editdisk=INI("editdisk");
fi_bluemsx=INI("msxemu");
fi=ExtractFileName(fi_bluemsx).LowerCase();
drag_dsk=(INI("dragdsk")=="1")?true:false;up_only=false;

if(fi.AnsiPos("openmsx")){emKind=EM_OPENMSX;}else{emKind=EM_BLUEMSX;}
if(emKind==EM_OPENMSX&&INI("rom")!=1){
 if(INI("outdir")==""){Memo1->Lines->Add("need outdir");return;}}
 //BASIC
fi=INI("infile");ext=ExtractFileExt(fi).LowerCase();
if(ext==".bas"){
 if(!convert(fi,fi_bas))return;
 if(INI("view")==1){Memo1->Lines->LoadFromFile(fi_bas);return;}
// chdir(ExtractFileDir(fi).c_str());
// WinExec((ParamStr(2)+"\\qqbasic.exe "+fi2).c_str(),SW_SHOW);
 hideWindow();mo=0;Timer1->Enabled=true;
}
//CCZ80
if(ext==".asm"){
 if(INI("view")==1){Memo1->Lines->LoadFromFile(fi);return;}
 if(INI("rom")==1){moRom=StrToInt(INI("rommode"));exportRomAsm(fi,ChangeFileExt(fi,".tmp"),false,false);hideWindow();Application->Terminate();}
 if(INI("rom")==2){moRom=StrToInt(INI("rommode"));exportRomAsm(fi,ChangeFileExt(fi,".tmp"),true,false);hideWindow();Application->Terminate();}
 if(INI("rom")==3){moRom=StrToInt(INI("rommode"));exportRomAsm(fi,ChangeFileExt(fi,".tmp"),false,true);hideWindow();Application->Terminate();}
 }
if(ext==".bin"){
 if(INI("rom")==1){
//  unlink(ChangeFileExt(fi,".tmp").c_str());
  genRom(fi,StrToInt(INI("romsize")));}
 else if(INI("rom")==2){
  INI("bloader")="0";
  fi_bas=ChangeFileExt(fi,".COM");
  unlink(fi_bas.c_str());
  RenameFile(fi,fi_bas);
  INI("infile")=fi_bas;
  fi_dsk=pa+"fpcx_dos.dsk";goto PPP1;
 }
 else{
  fi_bas2=fi_bas;
  if(emKind==EM_OPENMSX){fi_openBload=INI("outdir")+"\\AUTOEXEC.BAS";}//+ExtractFileName(ChangeFileExt(fi,".bas"));}
  fi_bas=fi;//ChangeFileExt(fi,".org");
  st_org=INI("org");
  if(INI("rom")==3)bsaveExbin(fi,ChangeFileExt(fi,".org"));else bsave(fi,ChangeFileExt(fi,".org"));
  PPP1:
 // chdir(ExtractFileDir(fi).c_str());
 // WinExec((ParamStr(2)+"\\qqbasic.exe "+fi2).c_str(),SW_SHOW);
//  HWND han=FindWind("Console_");if(han)PostMessage(han,WM_CLOSE,0,0);
  hideWindow();mo=0;Timer1->Enabled=true;}
  //Application->Terminate();
}
 if(ext==".mgs"){
  fi_bas=fi;//INI("infile");
  up_only=true;
  //HWND han=FindWind("Console_");if(han)PostMessage(han,WM_CLOSE,0,0);
  hideWindow();mo=0;Timer1->Enabled=true;}
}
//---------------------------------------------------------------------------
int posNextRemClose(AnsiString st,int po){
 int pos=po;int max=st.Length();
 while(pos!=max-1&&(st[pos]!='*'||st[pos+1]!='/'))++pos;
// if(pos==max-1)error("not */",po);
 return pos;}

bool __fastcall TForm1::convert(AnsiString fi_in,AnsiString fi_out){
 TStringList *li,*li2,*li_func,*li_after;int i,j,k,linenum,a,a2,afterFnc,isAfter;
 AnsiString st,st2;
 li=new TStringList();
 TStringList *li_final=new TStringList();
 TStringList *li_label=new TStringList();
 li->LoadFromFile(fi_in);

 if(br->Match("m/[\\d]+ /",li->Strings[0])){
  li_final->Text=li->Text;
}else{

 li_after=new TStringList();

 //--- analyse basic extensions(Andmegx)
 #define STST 1
 for(i=0;i<li->Count;i++){
  st=li->Strings[i];
  if((a=st.Pos("include "))==STST){
   st2=st.SubString(a+8,st.Length()-(a+8)+1);
   try{
   li_after->LoadFromFile(ExtractFilePath(fi_in)+st2);
   }catch(...){Application->MessageBox(("Failed to open "+st2).c_str(),"error",MB_ICONERROR);return false;}
   li->Delete(i);
   li->Insert(i,li_after->Text);}
  // define a=b
  else while((a=st.Pos("define "))>=STST){a2=a;a+=7;
   st2="";while(a<st.Length()+STST&&st[a]!='='){st2=st2+st[a];++a;}
   if(a<st.Length()+STST){
	li_label->Add(st2);
	st2="";++a;while(a<st.Length()+STST&&st[a]!=':'){st2=st2+st[a];++a;}
	li_label->Add(st2);
	st.Delete(a2,a-a2+1);
	}else{st.Delete(a2,7);}
   li->Strings[i]=st;
  }
 }


 st=li->Text;
 li_after->Clear();
// try{

  // simple Replace
 for(i=0;i<li_replace->Count;i++){
  st2=li_replace->Strings[i];errMes=st2;
  br->Split("m/##/",st2,2);
  AnsiString r1=br->Strings[0],r2=br->Strings[1];
  br->Subst("s/"+r1+"/"+r2+"/g",st);}

 //-- rem
 while((a=st.AnsiPos("/*"))>0){
  a2=posNextRemClose(st,a);st.Delete(a,a2-a+2);}

 li->Text=st;

//*func(a,b,c)の変換
/*AnsiString st3,st4,st5,st6;int colnum;
 li_func=new TStringList();
 for(i=0;i<li->Count;i++){
  st=li->Strings[i];
  if(br->Match("m/^\\*([^\\)]+)\\(/",st)){li_func->Add(br->Strings[1]);// *func(a,b,c)を探す
   st2="*"+br->Strings[1];
//   st3=st.SubString(AnsiPos("(")+1,st.Length-(AnsiPos("(")+1)+1);
   j=st.AnsiPos("(")+1;
   st3="";colnum=0;
   for(;j<=st.Length();j++){
    if(st[j]==','||st[j]==')'){st2=st2+":"+st3+"=r10("+IntToStr(colnum)+")";st3="";++colnum;}
    else st3=st3+st[j];}
  li->Strings[i]=st2;
}}*/

//switch
int inSwi=0;AnsiString stSwi;
for(i=0;i<li->Count;i++){
 st=li->Strings[i];
 if((a=st.AnsiPos("switch "))>0){
  stSwi=st.SubString(a+7,st.Length()-(a+7)+1);inSwi=1;
  li->Strings[i]="";}
 if(br->Match("m/case ([^:]*):/",st)){
  st2=br->Strings[1];
  br->Subst("s/case ([^:]*):/if "+stSwi+"="+st2+" then begin /",st);
  li->Strings[i]=st;}
 if(br->Match("m/break/",st)){
  br->Subst("s/break//",st);
  li->Strings[i]=st;
  li->Insert(i+1,"endif");}
}
//li->SaveToFile("temp.txt");
//add line num
int cntBegin=100,locnum=1;
li2=new TStringList();
afterFnc=1;
do{
int ifkaiso=0;isAfter=0;
 li_after->Text="";li2->Text="";
 for(i=0;i<li->Count;i++){st=li->Strings[i].Trim();
//  ShowMessage("["+st+"]");

  //if文の中身をためていく
  if(isAfter){
   if((a=st.AnsiPos("endif"))>0){
    if(ifkaiso>0){--ifkaiso;goto doubleBegin;}
    if(a>1)li_after->Add(st.SubString(1,a-1));
    li_after->Add("return");
    st2=li2->Strings[li2->Count-1];//st2.Delete(1,st2.AnsiPos(" "));
    li2->Delete(li2->Count-1);
    if(st.AnsiPos("endif ")>0){
     st=st2+st.SubString(a+5,st.Length()-(a+5)+1);}else st=st2;
//    st="★"+st2+"☆";
    isAfter=0;}
   else{doubleBegin:
    if(st.AnsiPos("begin")){++ifkaiso;}// ダブルビギン
    li_after->Add(st);continue;}}

  //if文
  if((a=st.AnsiPos("begin"))>0){
   li_after->Add("*afterfunc"+IntToStr(afterFnc));
   if(st.AnsiPos("begin ")>0)li_after->Add(st.SubString(a+6,st.Length()-(a+6)+1));
   st=st.SubString(1,a-1)+"gosub *afterfunc"+IntToStr(afterFnc++);isAfter=1;
   ifkaiso=0;
   }
  //ローカル変数
/*  if(st.Length()>0&&st[1]=='*'){++locnum;}
  br->Subst("s/@([a-z])/r"+IntToStr(locnum)+"_$1/gi",st);

  //関数の展開
  for(j=0;j<li_func->Count;j++){st2=li_func->Strings[j];
   while((k=st.AnsiPos(st2+"("))>0&&st[1]!='*'){
    //ShowMessage(st2);
    //関数の前の変数
    st5="";
    if(k>2&&st[k-1]=='='){int i2=k-2,j2=1;
     while(i2>0&&st[i2]!=' '&&st[i2]!=':'){st6=st[i2];st5=st6+st5;--i2;++j2;}
     st.Delete(i2+1,j2);k-=j2;//変数部分を削除
     st5=":"+st5+"=result";}

    if(k>1)st3=st.SubString(1,k-1);else st3="";
    //引数の展開
    while(k<=st.Length()&&st[k]!='(')++k;++k;st4="";colnum=0;
    while(k<=st.Length()&&st[k-1]!=')'){
     if(st[k]==','||st[k]==')'){st3=st3+"r10("+IntToStr(colnum)+")="+st4+":";st4="";++colnum;}else st4=st4+st[k];
     ++k;}
    st3=st3+"gosub *"+st2+st5;
    if(k!=st.Length())st3=st3+st.SubString(k,st.Length()-k+1);
    st=st3;
   }}*/
  if(st.Length()>0){
//    ShowMessage(IntToStr(i)+"/"+IntToStr(isAfter)+":"+st);
   li2->Add(st);}}

for(i=0;i<li_after->Count;i++){
 st=li_after->Strings[i].Trim();
 if(st.Length()>0){li2->Add(st);/*++linenum;*/}}

--cntBegin;
li->Text=li2->Text;
//Memo1->Lines->Add(li->Text+"\n-------------------------------");
}while(li->Text.AnsiPos("begin")&&cntBegin>0);
if(cntBegin==0)Application->MessageBox("multiple begin over flow!","error",MB_ICONERROR);

//}catch(...){Memo1->Lines->Add(errMes);}

// add line number
linenum=1;
for(i=0;i<li2->Count;i++){
 st=li2->Strings[i];
 if(st[1]=='*'){
  AnsiString ln="*";
  int a=2;while(a<=st.Length()&&st[a]!=':'){ln=ln+st[a];++a;}
  li_label->Add(ln);li_label->Add(IntToStr(linenum));
//  ShowMessage(ln);
  if(a-1==st.Length())continue;st.Delete(1,a);
  }
 li_final->Add(IntToStr(linenum)+" "+st);++linenum;}

//  br->Subst("s/@([a-z])/r"+IntToStr(locnum)+"_$1/gi",st);
// label conversion
st=li_final->Text;
for(i=li_label->Count/2-1;i>=0;i--){
 AnsiString la=li_label->Strings[i*2],va=li_label->Strings[i*2+1];
 br->Subst("s/\\"+la+"/"+va+"/g",st);}
li_final->Text=st;
//if(br->Match("m/^\\*([^\\)]+)\\(/",st)){li_func->Add(br->Strings[1]);

 // save
 int fa;
 unlink(fi_out.c_str());
/* if(FileExists(fi_out)){
  fa=FileGetAttr(fi_out);
  FileSetAttr(fi_out,fa-faHidden);}*/
}// ALLSKIP:
 li_final->SaveToFile(fi_out);
 delete li_label;
 delete li_final;
 delete li;
// fa=FileGetAttr(fi_out);
// FileSetAttr(fi_out,fa+faHidden);
 return true;
}

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
  Memo1->SelLength=txt.Length();
  ltxt=Memo1->SelText;Memo1->SelText="";
  Memo1->SelText=ltxt;
  Memo1->SelStart=x-1;
  Memo1->SelLength=txt.Length();
  return true;}
  Application->MessageBox("not found","find",MB_OK);
 return false;}

void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{int i;
 if(Key==VK_ESCAPE)Close();
 if(Edit1->Text=="")return;
 if(Key==VK_RETURN){ Memo1->SetFocus();FindText(Edit1->Text,false);

/*  for(i=0;i<Memo1->Lines->Count;i++){
   if(Memo1->Lines->Strings[i].AnsiPos(Edit1->Text)==1){
    Memo1->SetFocus();
    Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,i,0);
    Memo1->SelLength=Edit1->Text.Length();
    Memo1->SelText=Edit1->Text;//Memo1->SelLength=1;Memo1->SelText="";
    Memo1->SelLength=0;return;}}*/}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Memo1KeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
 switch(Key){
  case VK_ESCAPE: Close();break;
  case 'L':if(Shift.Contains(ssCtrl))Button1Click(Sender);break;
  case 'A':if(Shift.Contains(ssCtrl))Memo1->SelectAll();break;}

}
//---------------------------------------------------------------------------
HWND han_de;
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
HWND han;HDROP hDrop,hDropT;
 switch(mo){
  case 0:SKIP_MO0:
   if(emKind==EM_BLUEMSX){
    if(!drag_dsk){han=FindWind("blueMSX");
     if(han){SetForegroundWindow(han);
      PostMessage(han,WM_CLOSE,0,0);
      return;}}
    if(fi_editdisk.LowerCase().AnsiPos("diskmgr")){
     WinExec((fi_editdisk+" -A -F -C \x22"+fi_dsk+"\x22 \x22"+fi_bas+"\x22").c_str(),SW_SHOW);
     mo=7;return;}
    else{
     WinExec((fi_editdisk+" \x22"+fi_dsk+"\x22 /S").c_str(),SW_SHOW);
     mo=1;}}
//Memo1->Lines->Add("c:\\apps\\diskman\\DISKMGR.exe -A -F -C \x22"+fi_dsk+"\x22 \x22"+fi_bas+"\x22");
//WinExec((fi_bluemsx+" /diskA \x22"+fi_dsk+"\x22").c_str(),SW_SHOW);
   else if(emKind==EM_OPENMSX){
    if(fi_bas.Pos("autoexec.bas"))
     CopyFile(fi_bas.c_str(),(INI("outdir")+"\\AUTOEXEC.BAS").c_str(),false);
    else CopyFile(fi_bas.c_str(),(INI("outdir")+"\\"+ExtractFileName(INI("infile"))).c_str(),false);
//    CopyFile(fi_bas.c_str(),(INI("outdir")+"\\AUTOEXEC.BAS").c_str(),false);
    if(INI("bloader")==1){CopyFile(fi_bas2.c_str(),fi_openBload.c_str(),false);}
    if(!up_only){
     //--focus openMSX
     han=FindWind("openMSX 0");
     if(han){SetForegroundWindow(han);
//     keybd_event(VK_F1,MapVirtualKey(VK_F1,0),0,0); // Ctrlキーを押す
//     keybd_event(VK_F1,MapVirtualKey(VK_F1,0),KEYEVENTF_KEYUP,0);// Ctrlキーを離す
      Application->Terminate();
     }else{
//     Memo1->Lines->Add((fi_bluemsx+" "+INI("option")+" -diska \x22"+INI("outdir")+"\x22").c_str());
      WinExec((fi_bluemsx+" "+INI("option")+" -diska \x22"+INI("outdir")+"\x22").c_str(),SW_HIDE);}}
    Application->Terminate();
   }
   break;
  case 1:SKIP_MO1:han_de=FindWind("DiskExplorer");
   if(!han_de)return;
   hDrop=DragCreateFiles();
   hDropT=DragAppendFile(hDrop,fi_bas.c_str());
   PostMessage(han_de,WM_DROPFILES,(WPARAM)hDrop,0L);
   //addLog("add file to disk");
   mo=2;ti=0;break;
  case 2:
   han=FindWind("重複するファイル");
   if(!han){han=FindWind("Confirm File Replace");
    if(!han){han=FindWind("Overwite");
      if(!han){han=FindWind("上書きの確認");
       if(!han){++ti;
        han_de=FindWind("DiskExplorer");
        if(!han_de||ti==10)mo=3;
        return;
        }}}}
   SKIP_MO2:SetForegroundWindow(han);
   keybd_event('Y',MapVirtualKey('Y',0),0,0); // Ctrlキーを押す
   keybd_event('Y',MapVirtualKey('Y',0),KEYEVENTF_KEYUP,0);// Ctrlキーを離す
   mo=3;
   break;
  case 3:if(INI("bloader")==1){fi_bas=fi_bas2;mo=1;INI("bloader")="0";goto SKIP_MO1;}

  han=FindWind("重複するファイル");
   if(!han){han=FindWind("Confirm File Replace");
    if(!han){han=FindWind("Overwite");
      if(!han){han=FindWind("上書きの確認");
       if(!han){
/*  keybd_event(VK_MENU,MapVirtualKey(VK_MENU,0),0,0); // Ctrlキーを押す
  keybd_event(VK_F4,MapVirtualKey(VK_F4,0),0,0); // Ctrlキーを押す
  keybd_event(VK_F4,MapVirtualKey(VK_F4,0),KEYEVENTF_KEYUP,0); // Ctrlキーを押す
  keybd_event(VK_MENU,MapVirtualKey(VK_MENU,0),KEYEVENTF_KEYUP,0); // Ctrlキーを押す*/
   PostMessage(han_de,WM_CLOSE,0,0);
   if(up_only){Application->Terminate();return;}
//  mo=2;
   if(drag_dsk){han=FindWind("blueMSX");
    if(!han){goto SKIP_MO3;}
    hDrop=DragCreateFiles();
    hDropT=DragAppendFile(hDrop,fi_dsk.c_str());
    PostMessage(han,WM_DROPFILES,(WPARAM)hDrop,0L);
    SetForegroundWindow(han);
    Application->Terminate();}
   else{SKIP_MO3:WinExec((fi_bluemsx+" /diskA \x22"+fi_dsk+"\x22").c_str(),SW_SHOW);
    mo=6;
    Application->Terminate();}
   }}}}else goto SKIP_MO2;
   break;
  case 4:han=FindWind("blueMSX");
   if(!han){/*addLog("blueMSX not found");*/return;}
   SetForegroundWindow(han);
   Application->Terminate();
   break;
  case 5:mo=1;break;

  //--- Disk-Managerの時の処理
  case 7:han_de=FindWind("Disk-Manager");
   if(han_de)return;
   if(up_only){Application->Terminate();return;}
   if(INI("bloader")==1){fi_bas=fi_bas2;mo=1;INI("bloader")="0";goto SKIP_MO0;}

   if(drag_dsk){han=FindWind("blueMSX");
    if(!han){
     //Timer1->Enabled=false; Application->MessageBox("Please run blueMSX","caution",MB_OK);Timer1->Enabled=false;return;
     goto SKIP_MO7;
     }
    hDrop=DragCreateFiles();
    hDropT=DragAppendFile(hDrop,fi_dsk.c_str());
    PostMessage(han,WM_DROPFILES,(WPARAM)hDrop,0L);
    SetForegroundWindow(han);
    //keybd_event(VK_F5,MapVirtualKey(VK_F5,0),0,0); // Ctrlキーを押す
    //keybd_event(VK_F5,MapVirtualKey(VK_F5,0),KEYEVENTF_KEYUP,0);// Ctrlキーを離す
    Application->Terminate();}
   else{SKIP_MO7:
   WinExec((fi_bluemsx+" /diskA \x22"+fi_dsk+"\x22").c_str(),SW_SHOW);
//   mo=6;
   Application->Terminate();}
   break;

 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bsave(AnsiString fi_in,AnsiString fi_out){
//--- 読込み
 int han,len,dec;char *buf;
 unlink(fi_out.c_str());
 RenameFile(fi_in,fi_out);
// fi_in=ExtractFileName(fi_in).UpperCase();if(fi_in.Length()>12)fi_in=fi_in.SubString(1,8)+".BIN";
 if((han=FileOpen(fi_out,fmOpenRead))==-1){return;}
 len=FileSeek(han,0,2);
 FileSeek(han,0,0);
 buf=new char[len+8];
 FileRead(han,buf+7,len);
 FileClose(han);

 sscanf(st_org.c_str(),"%x",&dec);
 buf[0]=0xfe;
 buf[1]=dec&255;
 buf[2]=dec>>8;
 buf[5]=dec&255;
 buf[6]=dec>>8;
 dec+=len-1;
 buf[3]=dec&255;
 buf[4]=dec>>8;
//--- 書き込み
// int han,len;char *buf;
 if((han=FileCreate(fi_in))==-1){return;}
 FileWrite(han,buf,len+7);
 FileClose(han);
 delete buf;
}

void __fastcall TForm1::bsaveExbin(AnsiString fi_in,AnsiString fi_out){
//--- 読込み
 int han,len,dec;char *buf;
 unlink(fi_out.c_str());
 RenameFile(fi_in,fi_out);
// fi_in=ExtractFileName(fi_in).UpperCase();if(fi_in.Length()>12)fi_in=fi_in.SubString(1,8)+".BIN";
 if((han=FileOpen(fi_out,fmOpenRead))==-1){return;}
 len=FileSeek(han,0,2);
 buf=new char[len+8];
 int romsize=StrToInt(INI("romsize"));
 len-=romsize;
 FileSeek(han,romsize,0);
 FileRead(han,buf+7,len);
 FileClose(han);

 sscanf(st_org.c_str(),"%x",&dec);
 buf[0]=0xfe;
 buf[1]=dec&255;
 buf[2]=dec>>8;
 buf[5]=dec&255;
 buf[6]=dec>>8;
 dec+=len-1;
 buf[3]=dec&255;
 buf[4]=dec>>8;
//--- 書き込み
// int han,len;char *buf;
 if((han=FileCreate(fi_in))==-1){return;}
 FileWrite(han,buf,len+7);
 FileClose(han);
 delete buf;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if(Edit1->Text=="")return;
 Memo1->SetFocus();
 FindText(Edit1->Text,false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 Close();
}

//#define addAsm(X) li2->Add("asm{\x22"+X+"\x22};")
//---------------------------------------------------------------------------
void __fastcall TForm1::exportRomAsm(AnsiString fi_in,AnsiString fi_out,bool isCom,bool isExbin){
 TStringList *li,*li2,*li_after,*li_before;int i;AnsiString st,st2;
 bool moRand,moSd;
 li=new TStringList();
 li2=new TStringList();
 li_after=new TStringList();
 li_before=new TStringList();
 li->LoadFromFile(fi_in);
 moRand=false;moSd=false;
 if(moRom==1){//ccz80++
  li2->Add("class MainClass{");
  li2->Add("static void main(){");
  li2->Add("asm{");
  li2->Add((isCom)?"org #100":"org #0000");}
 for(i=0;i<li->Count;i++){
  st=li->Strings[i];
  if(st==""||br->Match("m/^[ ]+;/",st))continue;
  if(isCom&&st.AnsiPos("org ")){continue;}
  if(st.AnsiPos("_")==1&&st.AnsiPos("_p0")){moSd=true;li_before->Add(st);continue;}
  if(moSd){
   if(st.AnsiPos("_")==1){moSd=false;}else{li_before->Add(st);continue;}}

  if(st.AnsiPos("__begin_program:")){
   if(!isCom&&!isExbin){
    li2->Add("defb 65");li2->Add("defb 66");li2->Add("defw _main1");
    li2->Add("defw 0");li2->Add("defw 0");li2->Add("defw 0");li2->Add("defw 0");li2->Add("defw 0");
/* li2->Add("_main1:");
 li2->Add("ld a,#c3");
 li2->Add("ld (#feda),a");
 li2->Add("ld hl,_main2");
 li2->Add("ld (#fedb),hl");
 li2->Add("ret");*/
    }st="_main1:";}
  if(st.AnsiPos("__end_program:")){continue;}
  if(st.AnsiPos("__satbl:")){li_after->Add("__satbl:defb 0,0,0,0");continue;}
  if(st.AnsiPos("__satblad:")){li_after->Add("__satblad: defw #1E00");continue;}
  if(st.AnsiPos("_rand:")&&!isCom&&!isExbin){moRand=true;li_after->Add("_seed: defw 0");}
  if(moRom==1){if(br->Match("m/defs [\\d]+|defb 0$|defw 0$|defs [\\d]+ |defb 0 |defw 0 /",st)){
   if(isExbin){li_before->Add(st2);li_before->Add(st);}
   else{li_after->Add(st2);li_after->Add(st);}
   li2->Delete(li2->Count-1);st="";}}
  else{
   if(br->Match("m/defs [\\d]+|defb 0$|defw 0$/",st)){
    if(isExbin){li_before->Add(st2);li_before->Add(st);}
    else{li_after->Add(st2);li_after->Add(st);}
   li2->Delete(li2->Count-1);st="";}}

  if(!isCom&&!isExbin){
   if(moRom==1)br->Subst("s/__rand\\+1/_seed/g",st);
   else if(st.AnsiPos("ld   (_rand+1),hl")){st="ld (_seed),hl";}
   if(moRand){
    if(st.AnsiPos("ld   de,0")){st="ld de,(_seed)";}
    if(st.AnsiPos("ret")){moRand=false;}}}

//  if(st!=""&&!br->Match("m/^[ ]+;/",st)){
   br->Subst("s/\x22/\\\\x22/g",st);li2->Add(st);st2=st;}//}
 if(!isCom&&!isExbin)li2->Add("org #"+INI("data"));
 for(i=0;i<li_after->Count;i++)li2->Add(li_after->Strings[i]);

 /*for(i=0;i<li2->Count;i++){
  st=li2->Strings[i];li2->Strings[i]="asm{\x22"+st+"\x22};";}*/
 if(moRom==0){st="asm{";
  for(i=0;i<li2->Count;i++){
   if(i)st=st+",";st=st+"\x22"+li2->Strings[i]+"\x22";}
  st=st+"};";
  li2->Text=st;}
 else if(moRom==1)li2->Add("}}}");

//ShowMessage("here2");
 if(moRom==1){//ccz80++
 if(li_before->Count){//#0000番地アドレスがあればそのまま　なければ消す
  if(isCom)li2->Strings[3]="org #100\njp _main1\n"+li_before->Text+"\norg #4000\n";
  else if(isExbin)li2->Strings[3]="org #"+INI("data")+"\n"+li_before->Text+"\n";
  else li2->Strings[3]="org #0000\n"+li_before->Text+"\n";
  }else li2->Strings[3]="";}
 li2->SaveToFile(fi_out);
}

void __fastcall TForm1::genRom(AnsiString fi_in,int kb){
//--- 読込み
 int i,han,len;char *buf,*p;
 if((han=FileOpen(fi_in,fmOpenRead))==-1){Application->MessageBox("file not found!","error",MB_ICONERROR);return;}
 len=FileSeek(han,0,2);
 FileSeek(han,0,0);
 buf=new char[(len<kb)?(kb):(len+1)];
 p=buf;for(i=0;i<kb;i++)*(p++)=0;
 FileRead(han,buf,len);
 FileClose(han);
 fi_in=ChangeFileExt(fi_in,".rom");
//--- 書き込み
 if((han=FileCreate(fi_in))==-1){Application->MessageBox("can't write file!","error",MB_ICONERROR);return;}
 FileWrite(han,buf,kb);
 FileClose(han);


if(emKind==EM_OPENMSX){
 WinExec((fi_bluemsx+" "+INI("option")+" -carta \x22"+fi_in+"\x22").c_str(),SW_HIDE);}
else{
 WinExec((fi_bluemsx+" /rom1 \x22"+fi_in+"\x22").c_str(),SW_SHOW);}
 Application->Terminate();
}
