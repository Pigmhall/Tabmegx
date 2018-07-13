//---- Megson MainFrom megson1.cpp
#define VER "Tabmegx v1.15\n6/11/2018 N.I"
#include <vcl.h>
#include <vcl\Clipbrd.hpp>
#include <windowsx.h>
#pragma hdrstop

//#include "fod.h"
#include "megson1.h"
#include "megnumber.h"
#include "megkeyas.h"
#include "megimage.h"
#include "megoption.h"
#include "megftp.h"
#include "megcmd.h"
#include "jis2001.h"
#include "megperl.h"
#include "megmsx.h"
#include "megdb.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmMeg1 *FrmMeg1;
const EM_BLUEMSX=0,EM_OPENMSX=1,EM_WINAPE=2,EM_PCCPC=3;
#define NEWTXT "|"
#define NEWFILE "New"
#define KNJHOTKEY "(&E)"
#define INI(X) li_ini->Values[X]
#define SetStatus(A) StatusBar1->SimpleText=A;
const LST_FUNCJUMP=0,LST_KOUHO=1;
const BTNWX=19,BTNWY=4;int BTNSZ=39,BTNSZY=40;
TButton *BtnKey[BTNWX*BTNWY];
#define MENUCLKED if(Active)Memo1->SetFocus()
//---------------------------------------------------------------------------
// Initialize
//---------------------------------------------------------------------------
AnsiString __fastcall TFrmMeg1::getButKey(int x,int y){
 AnsiString st=INI("BtnKey"+IntToStr(x+1)).SubString(y+1,1);
 if(st=="&"){st="&&";}
 if(st=="L"){st="<-";} if(st=="U"){st="^^";}if(st=="D"){st="vv";} if(st=="R"){st="->";}
 if(st=="H")st="<|";
 if(st=="E")st="|>";
 return st;}

__fastcall TFrmMeg1::TFrmMeg1(TComponent* Owner) : TForm(Owner)
{
 int i,j;

 CoInitialize(NULL);
// Fod1=new TFod(FrmMeg1);//Fod1->Execute(2);

 di_megpas=ExtractFilePath(Application->ExeName);
 fi_ini=di_megpas+"tabmegx.ini";
 fi_fpcx=di_megpas+"fpcx\\fpcx.exe";
 bakSelText="";
 kukeiCopy=0;

 li_ini=new TStringList();isFtp=false;
// li_ftp=new TStringList();
 ix=false;tb_in=0;tb_cnt=0;isShift=false;
 Caption="Tabmegx";
 LoadIni();

 if(INI("SjisOnly")!="1"){isSjisOnly=false;
/*  if(g.load_library()==false){Application->MessageBox("jis2000.dllがない","ｴﾗｰ",MB_OK|MB_ICONERROR);Application->Terminate();}*/}
 else{isSjisOnly=true;mnKnj->Enabled=false;}

 for(i=0;i<M_TXT;i++)txt[i]=NEWTXT;
 li_file=new TStringList();
 li_id=new TStringList();
 li_modify=new TStringList();
 li_pos=new TStringList();
 li_knj=new TStringList();
 li_kouho=new TStringList();
 li_no=new TStringList();
 li_butkey=new TStringList();
 reloadKouho();
 butkeyFlg=0;
// li_kouho->Sort();
// li_sellen=new TStringList();
// strRegcode="aBlaDf";
 DragAcceptFiles(Handle,True);
 if(ParamCount()==0)AddNewText(NEWFILE);
 else{for(i=1;i<=ParamCount();i++){
  AddNewText(ParamStr(i));
  try{
   ix=true;LoadKnjText("");}catch(...){}}}
// strCredit=strDecrypt("XZaCeXgGaBlfaFedaAkRV2raDfaHg1Vsyzkz",15);
 Application->HelpFile=ChangeFileExt(Application->ExeName,".hlp");
 li_temp=new TStringList();
 RefreshTemp();
 try{
 BTNSZY=StrToInt(INI("BtnKeySizeY"));
 BTNSZ=StrToInt(INI("BtnKeySizeX"));}catch(...){
  BTNSZ=39;BTNSZY=40;}


 PnlBottom->Height=BTNWY*BTNSZY+StatusBar1->Height;
 for(i=0;i<BTNWY;i++){
  for(j=0;j<BTNWX;j++){
   int a=i*BTNWX+j,sx=(i==3)?BTNSZ*3:BTNSZ;
   BtnKey[a]=new TButton(this);
   BtnKey[a]->Parent=PnlBottom;
   BtnKey[a]->Width=sx;
   BtnKey[a]->Height=BTNSZY;
   BtnKey[a]->Left=j*sx;
   BtnKey[a]->Top=i*BTNSZY;
//   BtnKey[a]->Font->Charset=ANSI_CHARSET;
//   BtnKey[a]->Font->Name="Arial";

//   BtnKey[a]->Font->
   if(i<3){AnsiString st=getButKey(i,j);/*INI("BtnKey"+IntToStr(i+1)).SubString(j+1,1);
    if(st=="&"){st="&&";}    if(st=="L"){st="←";}    if(st=="U"){st="↑";}    if(st=="D"){st="↓";}    if(st=="R"){st="→";}*/
    BtnKey[a]->Caption=st;
    BtnKey[a]->Font->Size=(st.Length()==1)?19:15;
    BtnKey[a]->OnClick=ButKey1Click;}else{BtnKey[a]->OnClick=ButKey2Click;
    BtnKey[a]->Font->Size=11;}
  }}
  fi_ccz80ptarget="";isDmsys=false;refreshTopButtons();
 }

AnsiString __fastcall TFrmMeg1::defaultLoaderScript(void){
 return "clear200,&h84ff:%a1:bload\x22%f\x22,r:%a2:clear200,&hcfff:stop";}
//--------------
// INI file load-save
void __fastcall TFrmMeg1::LoadIni(void){
 if(FileExists(fi_ini)){
  try{
  li_ini->LoadFromFile(fi_ini);
/*  Width=StrToInt(INI("Width"));Height=StrToInt(INI("Height"));Left=StrToInt(INI("Left")); Top=StrToInt(INI("Top"));*/
  Memo1->Color=(TColor)StrToInt(INI("Color"));
  Memo1->Font->Charset=(TFontCharset)StrToInt(INI("FCharSet"));
  Memo1->Font->Color=(TColor)StrToInt(INI("FColor"));
  Memo1->Font->Name=INI("FName");
  Memo1->Font->Size=StrToInt(INI("FSize"));
/*  Fod1->FontColor=(Memo1->Font->Color!=clWhite)?Memo1->Font->Color:clAqua;
  Fod1->Color=Memo1->Color;
  Fod1->Width=StrToInt(INI("FodWidth"));
  Fod1->Height=StrToInt(INI("FodHeight"));
  Fod1->FontSize=StrToInt(INI("FodFontSize"));
  Fod1->DefaultExt=INI("FodDefaultExt");*/
  Memo1->WordWrap=(INI("Wrap")=="1")?true:false;
  Memo1->ScrollBars=(Memo1->WordWrap)?ssVertical:ssBoth;
  mnWrap->Checked=Memo1->WordWrap;
  Width=StrToInt(INI("Width"));
  Height=StrToInt(INI("Height"));
  Left=StrToInt(INI("Left"));
  Top=StrToInt(INI("Top"));

  int i;AnsiString st;
//  for(i=0;i<32;i++){if((st=INI("FodJumpDir"+IntToStr(i)))!=""){Fod1->li_jumpdir->Add(st);}}
  }catch(...){Application->MessageBox("ini error","err",MB_OK|MB_ICONERROR);}}
 else{// Default INI
  INI("BtnKeySizeX")="39";
  INI("BtnKeySizeY")="40";
  INI("FileMaskImg")="*.jpg;*.gif;*.png;*.bmp";
//  INI("FodDefaultExt")="";
  INI("strKeisan")="*2";
  INI("AutoIndent")="1";
  INI("FtpServer0")="my ftp||||||";
  INI("FtpDefault")="0";
  INI("Dbscript")="sqlx.pl";
  INI("Wrap")="0";
  INI("RetcodeSJIS")="Win";
  INI("RetcodeEUC")="Unix";
  INI("RetcodeJIS")="Unix";
  INI("RetcodeUTF8")="Win";
  INI("RetcodeUnicode")="Win";
 // INI("Extjava")="javac \x22%f\x22";
//  INI("Extpl")="perl.exe \x22%f\x22 %a";
  INI("KeyAlt1")="Example|ABCDE|FGHIJK";
  INI("KeyAlt2")="(SelTextExample value=%SELTEXT%)";
  INI("KeyAlt3")="(ClipExample value=%CLIP%)";
  INI("KeyAlt4")="(InputExample value=%INPUT%)";
  INI("FormatDate")="yyyy/MM/dd";
  INI("FormatTime")="hh:mm:ss";
  INI("CmdCtrlF1")="notepad.exe \x22%f\x22 %g";
//  INI("CmdCtrlF2")="perl.exe \x22"+di_megpas+"sample2.pl\x22 \x22%s\x22";

  }  RefreshTextMenu();
   LongTimeFormat=INI("FormatTime");
   ShortDateFormat=INI("FormatDate");
 if(INI("ListBoxY")==""){
  INI("ListBoxFontSize")=10;
//  INI("FodFontSize")=16;
  INI("ListBoxX")=3;
  INI("ListBoxY")=17;//v2.04 values
  INI("ListBoxW")=8;
//  INI("ListBoxH")=18;
  INI("ListBoxW2")=235;
  INI("ListBoxH2")=200;
  INI("FuncJump")="sub|void|int|char|public|";
  INI("WinScpMod")="755";
  INI("BtnKey1")="1234567890-^\[]";
  INI("BtnKey2")="!\x22#$%&'()=~@{}_";
  INI("BtnKey3")=";:+*,./\<>?LUDR";
  }
 int v=0;if(INI("Ver")!="")v=StrToInt(INI("Ver"));
 if(v<109){
  INI("FileMask")="*.bas;*.ccz80;*.ccz80++;*.mus;*.txt;*.pl;*.g;*.g2";
  INI("Extmus")=di_megpas+"mgsc\\mgscwin.exe \x22%f\x22 -t";
  INI("Ccz80Loader")=defaultLoaderScript();}

 INI("Ver")="109";
  }

// if(INI("ListBoxX")=="") if(INI("ListBoxW")=="") if(INI("ListBoxH")=="")if(INI("ListBoxW2")=="")if(INI("ListBoxH2")=="")
void __fastcall TFrmMeg1::SaveIni(void){
/* INI("Width")=IntToStr(Width);
 INI("Height")=IntToStr(Height);
 INI("Left")=IntToStr(Left);
 INI("Top")=IntToStr(Top);*/
 INI("Color")=IntToStr(Memo1->Color);
 INI("FCharSet")=IntToStr(Memo1->Font->Charset);
 INI("FColor")=IntToStr(Memo1->Font->Color);
 INI("FName")=Memo1->Font->Name;
 INI("FSize")=Memo1->Font->Size;
 INI("CWidth")=IntToStr(FrmCmd->Width);
 INI("CHeight")=IntToStr(FrmCmd->Height);
 INI("CLeft")=IntToStr(FrmCmd->Left);
 INI("CTop")=IntToStr(FrmCmd->Top);
 INI("CFCharSet")=IntToStr(FrmCmd->Memo1->Font->Charset);
 INI("CFColor")=IntToStr(FrmCmd->Memo1->Font->Color);
 INI("CFName")=FrmCmd->Memo1->Font->Name;
 INI("CFSize")=FrmCmd->Memo1->Font->Size;
 INI("PlWidth")=IntToStr(FrmPerl->Width);
 INI("PlHeight")=IntToStr(FrmPerl->Height);
 INI("PlLeft")=IntToStr(FrmPerl->Left);
 INI("PlTop")=IntToStr(FrmPerl->Top);
 INI("Wrap")=(Memo1->WordWrap)?"1":"0";
 INI("CWrap")=(FrmCmd->Memo1->WordWrap)?"1":"0";
/* INI("FodWidth")=Fod1->Width;
 INI("FodHeight")=Fod1->Height;
 INI("FodFontSize")=Fod1->FontSize;*/
 INI("Width")=IntToStr(Width);
 INI("Height")=IntToStr(Height);
 INI("Left")=IntToStr(Left);
 INI("Top")=IntToStr(Top);
 int i;
// for(i=0;i<li_ini->Count;i++){if(AnsiPos("FodJumpDir",li_ini->Strings[i])==1){li_ini->Delete(i);--i;}}
// for(i=0;i<Fod1->li_jumpdir->Count;i++){INI("FodJumpDir"+IntToStr(i))=Fod1->li_jumpdir->Strings[i];}

 li_ini->Sort();
 li_ini->SaveToFile(fi_ini);}

//---------------------------------------------------------------------------
// Add, Change Text subroutine
//---------------------------------------------------------------------------
//---- テキスト読込み
void __fastcall TFrmMeg1::LoadKnjText(AnsiString knj2){
 #define cod(X) li_knj->Strings[index]=X;
 #define AMM 4
 bool err=false;
 int han,len,len2;
 char *buf,*buf2;wchar_t *buf3;
 AnsiString fi=li_file->Strings[index];
try{
 //if(fi==fi_ini)SaveIni();
 if(isSjisOnly){Memo1->Lines->LoadFromFile(fi);return;}
 if((han=FileOpen(fi,fmOpenRead))==-1){
  //ShowMessage(fi+"\n"+di_megpas+"temp.csv");
  Application->MessageBox("locked file","Open",MB_OK);
  if(!CopyFile(fi.c_str(),(di_megpas+"temp.csv").c_str(),false)){ShowMessage("OPEN err");}
  if((han=FileOpen(di_megpas+"temp.csv",fmOpenRead))==-1){
   err=true;goto SKIP_READ;}}
 len=FileSeek(han,0,2);FileSeek(han,0,0);
 buf=new char[len+AMM];
 FileRead(han,buf,len);buf[len]=0;FileClose(han);
 if(knj2=="JIS")goto SKIP_JIS;
 else if(knj2=="EUC")goto SKIP_EUC;
 else if(knj2=="UTF8")goto SKIP_UTF8;
 else if(knj2=="Unicode")goto SKIP_UNICODE;
 else if(knj2=="SJIS")goto SKIP_SJIS;

 switch(GetKanjiCodeType(buf,len-1)){
  case JIS2K_JIS:SKIP_JIS:cod("JIS");
   len2=Iso2022jpToSjis(NULL,buf,0);buf2=new char[len2+AMM];
        Iso2022jpToSjis(buf2,buf,len2+AMM);break;
  case JIS2K_EUC:SKIP_EUC:cod("EUC");
   len2=EucToSjis(NULL,buf,0);buf2=new char[len2+AMM];
        EucToSjis(buf2,buf,len2+AMM);buf2[len2]=0;break;
  case JIS2K_UTF8:SKIP_UTF8:cod("UTF8");
   len2=UTF8ToUnicode(NULL,buf,0);buf3=new wchar_t[len2+AMM];
        UTF8ToUnicode(buf3,buf,len2+AMM);
   len2=UnicodeToSjis(NULL,buf3,0);buf2=new char[len2+AMM];
        UnicodeToSjis(buf2,buf3,len2*AMM);delete buf3;break;
  case JIS2K_UNICODE:SKIP_UNICODE:cod("Unicode");
   len2=UnicodeToSjis(NULL,(wchar_t *)buf,0);buf2=new char[len2+AMM];
        UnicodeToSjis(buf2,(wchar_t *)buf,len2+AMM);break;
  case JIS2K_SJIS:SKIP_SJIS:cod("SJIS");goto POKO;
  default:POKO:Memo1->Lines->Text=StrPas(buf);delete buf;return;}
 Memo1->Lines->Text=StrPas(buf2);
 if(!isSjisOnly)mnKnj->Caption=li_knj->Strings[index]+KNJHOTKEY;
}catch(...){err=true;}
 SKIP_READ:
 if(err){CloseFile();Application->MessageBox("failed","open",MB_OK|MB_ICONERROR);return;}
 delete buf;delete buf2;}

//----- テキスト保存
bool __fastcall TFrmMeg1::SaveKnjString(AnsiString fi,AnsiString knj,AnsiString &st){
 #define MTXT st.c_str()
 int len=st.Length()*4,len2,a;
 wchar_t *buf2; char *buf;//=new char[len*2];
 AnsiString ret=INI("Retcode"+knj);
 if(ret=="Unix"){while((a=AnsiPos("\xd",st))!=0){st.Delete(a,1);}}
 else if(ret=="Mac"){while((a=AnsiPos("\xa",st))!=0){st.Delete(a,1);}}

 if(knj=="JIS"){
  len2=SjisToIso2022jp3Compatible(NULL,MTXT,0);buf=new char[len2+AMM];
       SjisToIso2022jp3Compatible(buf,MTXT,len2+AMM);}
 else if(knj=="EUC"){
  len2=SjisToEuc(NULL,MTXT,0);buf=new char[len2+AMM];
       SjisToEuc(buf,MTXT,len2+AMM);}
/* else if(knj=="UTF7"){buf2=new wchar_t[len*2];
  g.SjisToUnicode(buf2,MTXT,len);
  g.UnicodeToUTF7(buf,buf2,len);delete buf2;}*/
 else if(knj=="UTF8"){
  len2=SjisToUnicode(NULL,MTXT,0);buf2=new wchar_t[len2+AMM];
       SjisToUnicode(buf2,MTXT,len2+AMM);
  len2=UnicodeToUTF8(NULL,buf2,0);buf=new char[len2+AMM];
       UnicodeToUTF8(buf,buf2,len2+AMM);delete buf2;}
 else if(knj=="Unicode"){
  len2=SjisToUnicode(NULL,MTXT,0)*2;buf=new char[len2+AMM];
       SjisToUnicode((wchar_t *)buf,MTXT,len2+AMM);}
 else{len2=st.Length();buf=new char[len+1];StrPCopy(buf,st);}

 int han;if((han=FileCreate(fi))==-1){delete buf;return false;}
 FileWrite(han,buf,len2);
 FileClose(han);
 delete buf;
 return true;}

bool __fastcall TFrmMeg1::SaveKnjText(void){
 bool ok;
 try{
  if(isSjisOnly){Memo1->Lines->SaveToFile(li_file->Strings[index]);return true;}
  AnsiString knj=li_knj->Strings[index],st;

/*  if(!isReg){
   TStringList *li_buf;li_buf=new TStringList();
   li_buf->Text=Memo1->Lines->Text;
   if(strCredit!="Megson Pro(unregistered)")return false;
   if(li_buf->Count>1&&!AnsiPos(strCredit,li_buf->Strings[1])){
   li_buf->Strings[1]=li_buf->Strings[1]+"---"+strCredit;}
   st=li_buf->Text;
   if(isSjisOnly){li_buf->SaveToFile(li_file->Strings[index]);return true;}
   delete li_buf;}
  else*/ st=Memo1->Lines->Text;

/*  int a;if(knj=="EUC"||knj=="JIS"){while((a=AnsiPos("\xd",st))!=0){st.Delete(a,1);}*/
  ok=SaveKnjString(li_file->Strings[index],knj,st);
 }catch(...){ok=false;}
 if(!ok){Application->MessageBox("failed","Save",MB_OK|MB_ICONERROR);}
 return ok;}

// AddNewText(Filename)
// Create New Textarea
#define CanAdd (li_id->Count==M_TXT)?false:true

void __fastcall TFrmMeg1::AddNewText(AnsiString name){
 int id=-1,a=-1,i;
 AnsiString st;
 if(name==NEWFILE){
  for(i=0;i<li_file->Count;i++){
   st=li_file->Strings[i];
   if(st.SubString(1,3)==NEWFILE)a=StrToInt(st.SubString(4,st.Length()-3));}
//  ShowMessage(IntToStr);
  name=name+IntToStr(a+1);}

 for(i=0;i<M_TXT;i++){if(txt[i]==NEWTXT){txt[i]="";id=i;i=M_TXT;}}

 li_file->Add(name);
 li_id->Add(IntToStr(id));
 li_pos->Add("000000000000000");
// li_sellen->Add("0");
 li_modify->Add("0");
 li_knj->Add("SJIS");
 TabControl1->Tabs->Add(ExtractFileName(name));
 TabControl1->TabIndex=index;
 ChangeText(li_file->Count-1,true);
}

//-----------
// ChangeText(Next id,Save current text ot txt[])
// Change Tab and save current text
void __fastcall TFrmMeg1::ChangeText(int to_idx,bool issave){
 int b;AnsiString buf;
 if(issave){txt[StrToInt(li_id->Strings[index])]=Memo1->Lines->Text;
  li_pos->Strings[index]=buf.sprintf("%7d%7d%7d",Memo1->SelStart,Memo1->SelLength,SendMessage(Memo1->Handle,EM_GETFIRSTVISIBLELINE,0,0));
  //Caption=li_pos->Strings[index];
  //li_sellen->Strings[index]=IntToStr(Memo1->SelLength);
  }
 index=to_idx;
 ix=true;Memo1->Lines->Text=txt[StrToInt(li_id->Strings[index])];
 if(!isSjisOnly)mnKnj->Caption=li_knj->Strings[index]+KNJHOTKEY;
 buf=li_pos->Strings[index];
 SendMessage(Memo1->Handle,EM_LINESCROLL,0,StrToInt(buf.SubString(1+7*2,7)));
 Memo1->SelStart=StrToInt(buf.SubString(1+7*0,7));
 Memo1->SelLength=StrToInt(buf.SubString(1+7*1,7));
 menuModify->Caption=(li_modify->Strings[index]=="1")?"@":"";
 //menuCol->Caption="1:1";
 SetMenuCol();
 TabControl1->TabIndex=index;
// TabControl1->Hint=li_file->Strings[index];
 //TabControl1->Repaint();
 }

//---------------------------------------------------------------------------
// FILE-MENU
//---------------------------------------------------------------------------
//----- New
void __fastcall TFrmMeg1::New1Click(TObject *Sender)
{MENUCLKED;if(CanAdd){AddNewText("New");Memo1->Clear();}}

//----- Open
void __fastcall TFrmMeg1::Open1Click(TObject *Sender)
{MENUCLKED;
// Fod1->FileName="";
// AnsiString st=INI("FileMask");for(int i=1;i<=st.Length();i++){if(st[i]==';')st[i]='|';}
 OpenDialog1->Filter=INI("FileMask")+"|"+INI("FileMask");
// Fod1->Mask=INI("FileMask");
// Fod1->Title="Open";
 if(CanAdd&&OpenDialog1->Execute()){
  AddNewText(OpenDialog1->FileName);
  ix=true;
  LoadKnjText("");
  }
}
//----- Save
// SaveAsText: true:成功 false:失敗
bool __fastcall TFrmMeg1::SaveAsText(char mo){
 if(li_file->Strings[index].SubString(1,3)!=NEWFILE){
   if(mo==1)SaveDialog1->FileName=ExtractFileName(li_file->Strings[index]);
   else SaveDialog1->FileName=li_file->Strings[index];}
  else SaveDialog1->FileName="";

// Fod1->Mask=INI("FileMask");//Fod1->Mask=INI("FileMask");Fod1->Height=INI("FodHeight");
 if(Memo1->Text.AnsiPos("VirtualRes"))SaveDialog1->Filter="*.g2|*.g2";
 else if(Memo1->Text.AnsiPos("syncOn;"))SaveDialog1->Filter="*.g|*.g";
 else if(Memo1->Text.AnsiPos("#opll_mode"))SaveDialog1->Filter="*.mus|*.mus";
 else if(Memo1->Text.AnsiPos("class "))SaveDialog1->Filter="*.ccz80++|*.ccz80++";
 else if(Memo1->Text.AnsiPos("include \x22"))SaveDialog1->Filter="*.ccz80|*.ccz80";
 else SaveDialog1->Filter=INI("FileMask")+"|"+INI("FileMask");
// Fod1->Title="Save";
 if(SaveDialog1->Execute()){
//  Memo1->Lines->SaveToFile(Fod1->FileName);
  li_file->Strings[index]=SaveDialog1->FileName;
  TabControl1->Tabs->Strings[index]=ExtractFileName(SaveDialog1->FileName);
  if(!SaveKnjText())return false;
  li_modify->Strings[index]="0";
  menuModify->Caption="";
//  FrmImage->FDir=ExtractFileDir(Fod1->FileName);
  return true;}else return false;}

// SaveText: true:成功 false:失敗
bool __fastcall TFrmMeg1::SaveText(void){
 if(li_file->Strings[index].SubString(1,3)==NEWFILE){
  return SaveAsText(0);}
 else{//Memo1->Lines->SaveToFile(li_file->Strings[index]);
  if(!SaveKnjText())return false;
  //if(li_file->Strings[index]==fi_ini){Application->MessageBox("設定を反映","保存",MB_OK);LoadIni();}
  li_modify->Strings[index]="0";
  menuModify->Caption="";}
  SetStatus("Saved");

  return true;}

void __fastcall TFrmMeg1::Saveas1Click(TObject *Sender){SaveAsText(0);MENUCLKED;}
void __fastcall TFrmMeg1::Save1Click(TObject *Sender){SaveText();MENUCLKED;}

//----- Backup
void __fastcall TFrmMeg1::Backup1Click(TObject *Sender)
{//
 AnsiString st;int i;
 st=li_file->Strings[index];
 if(!FileExists(st)||st.SubString(1,3)==NEWFILE){
  Application->MessageBox("The original file is not saved.","Backup",MB_OK);}
 else{
  st[st.Length()]='~';i=0;
  if(FileExists(st)){while(FileExists(st+IntToStr(i))){++i;};st=st+IntToStr(i);}
  CopyFile(li_file->Strings[index].c_str(),st.c_str(),false);
  Application->MessageBox(("Copyed to "+ExtractFileName(st)+".").c_str(),"Backup",MB_OK);}}

//---- Close
// CloseFile: true:成功 false:失敗
bool __fastcall TFrmMeg1::CloseFile(void){
 int ret;
 if(li_modify->Strings[index]=="1"){
  ret=Application->MessageBox((li_file->Strings[index]+"\nsave?").c_str(),"Confirm",MB_YESNOCANCEL|MB_ICONQUESTION);
  if(ret==ID_YES){if(!SaveText())return false;}
  else if(ret==ID_CANCEL)return false;}
 txt[StrToInt(li_id->Strings[index])]=NEWTXT;
 li_id->Delete(index);
 li_pos->Delete(index);
// li_sellen->Delete(index);
 li_modify->Delete(index);
 li_file->Delete(index);
 li_knj->Delete(index);
 //t_buf=TabControl1->Tabs;t_buf->Delete(index);
 TabControl1->Tabs->Delete(index);
 AnsiString st=TabControl1->Tabs->Text;
 TabControl1->Tabs->Text=st;//->Delete(index);
 if(li_file->Count==0){Memo1->Clear();AddNewText(NEWFILE);}
 if(li_file->Count==index)--index;
 ChangeText(index,false);return true;}

void __fastcall TFrmMeg1::Close1Click(TObject *Sender)
{CloseFile();MENUCLKED;}

//----- Quit
void __fastcall TFrmMeg1::Quit1Click(TObject *Sender)
{Close();}

//---------------------- FTPで保存
#define F_NAME(a) GetSplit(0,a)
#define F_HOST(a) GetSplit(1,a)
#define F_USER(a) GetSplit(2,a)
#define F_PASSWD(a) GetSplit(3,a)
#define F_SERVERDIR(a) GetSplit(4,a)
#define F_CHMOD(a) GetSplit(5,a)
#define F_PASSIVE(a) GetSplit(6,a)
#define CKEY str[1]&127

AnsiString TFrmMeg1::GetSplit(int n,AnsiString st){
 int i,a=1,b;
 for(i=0;i<n;i++){a=AnsiPos("|",st);
  if(a){st.Delete(a,1);}}
 if((b=AnsiPos("|",st))!=0){
  st=st.SubString(a,b-a);}else{st=st.SubString(a,st.Length()-a+1);}
 return st;}

void __fastcall TFrmMeg1::SaveFTP1Click(TObject *Sender){
 if(isFtp){Application->MessageBox("FTP now","FTP",MB_OK);return;}
 if(li_file->Strings[index].SubString(1,3)==NEWFILE)return;
 if(li_modify->Strings[index]=="1"&&!SaveText())return;

 AnsiString sdir="",str,mod,fi=li_file->Strings[index];int a,i;

 //--- scp
 GetArgument(sdir,"cpy=");
 if((a=AnsiPos("\\",sdir))!=0){
  mod=menuModify->Caption;
  menuModify->Caption="CPY";
//  AnsiString na=sdir.SubString(a+1,sdir.Length()-a);
  //sdir.Delete(a,sdir.Length()-a+1);
//  ShowMessage(fi+"\n"+sdir);
  CopyFile(fi.c_str(),(sdir+"\\"+ExtractFileName(fi)).c_str(),false);
  menuModify->Caption=mod;
  return;}

 //--- scp
 GetArgument(sdir,"scp=");
 if((a=AnsiPos(":",sdir))!=0){
  mod=menuModify->Caption;
  menuModify->Caption="SCP";
  AnsiString na=sdir.SubString(a+1,sdir.Length()-a);
  sdir.Delete(a,sdir.Length()-a+1);
  SetCurrentDir(ExtractFilePath(fi));
  fi=ExtractFileName(fi);
//  Application->MessageBox(("\x22"+INI("Winscp")+"\x22 "+na+" /command \x22"+"cd "+sdir+"\x22 \x22rm "+fi+"\x22 \x22put "+fi+"\x22 \x22"+"chmod "+INI("WinScpMod")+" "+fi+"\x22").c_str(),"ok",MB_OK);
//  Memo1->SelText="\x22"+INI("Winscp")+"\x22 "+na+" /command \x22"+"cd "+sdir+"\x22 \x22rm "+fi+"\x22 \x22put "+fi+"\x22 \x22"+"chmod "+INI("WinScpMod")+" "+fi+"\x22";
  WinExec(("\x22"+INI("Winscp")+"\x22 "+na+" /command \x22option confirm off\x22 \x22"+"cd "+sdir+"\x22 \x22put "+fi+"\x22 \x22"+"chmod "+INI("WinScpMod")+" "+fi+"\x22 \x22"+"exit\x22").c_str(),SW_SHOW);
//  CallExec(INI("Winscp"),sdir,na+" /command \x22option confirm off\x22 \x22"+"cd "+sdir+"\x22 \x22put "+fi+"\x22 \x22"+"chmod "+INI("WinScpMod")+" "+fi+"\x22",false,false);
  menuModify->Caption=mod;
  return;}
 //--- テキスト内の設定抽出
 GetArgument(sdir,"updir=");
 if((a=AnsiPos("@",sdir))!=0){
  AnsiString na=sdir.SubString(a+1,sdir.Length()-a)+"|";
  sdir.Delete(a,sdir.Length()-a+1);
  a=0;i=0;while((str=INI("FtpServer"+IntToStr(i)))!=""){if(str.AnsiPos(na)==1){a=1;break;}++i;}
  if(!a){Application->MessageBox("FTP not exists","FTP",MB_OK);return;}}
 else{str=INI("FtpServer"+INI("FtpDefault"));}

 //--- Caption
 mod=menuModify->Caption;
 menuModify->Caption="FTP...";
 //----- Upload
 AnsiString chmod=F_CHMOD(str);
 sdir=(sdir=="")?F_SERVERDIR(str):sdir;
 TNMFTP *NMFTP1=new TNMFTP(FrmMeg1);
 NMFTP1->Host=F_HOST(str);
 NMFTP1->UserID=F_USER(str);
 NMFTP1->Password=FrmMeg1->strDecrypt(F_PASSWD(str),CKEY);
 NMFTP1->Passive=(F_PASSIVE(str)=="1")?true:false;
 try{isFtp=true;
  NMFTP1->Connect();
  if(sdir!="")NMFTP1->ChangeDir(sdir);
  NMFTP1->Mode(MODE_IMAGE);
  NMFTP1->Upload(fi, "");
  if(chmod!="")NMFTP1->DoCommand("SITE CHMOD "+chmod+" "+ExtractFileName(fi));
  NMFTP1->Disconnect();
}catch(Exception &e){Application->MessageBox(e.Message.c_str(),"FTP error",MB_OK|MB_ICONERROR);}
 delete NMFTP1;
 isFtp=false;
// Upload(str,sdir,li_file->Strings[index]);
 menuModify->Caption=mod;
}
//----- FTP設定
void __fastcall TFrmMeg1::FTPsetting1Click(TObject *Sender){
/* if(FrmFtp->Visible)FrmFtp->SetFocus();
 else{FrmFtp->LoadAllIni();FrmFtp->ShowModal();}*/
 FrmFtp=new TFrmFtp(Application);
 FrmFtp->ShowModal();
 FrmFtp->Release();}
//  FrmFtp->SaveAllIni();}
//---------------------------------------------------------------------------
// Form Events
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::FormClose(TObject *Sender, TCloseAction &Action){
 int i,k=li_file->Count;
 for(i=0;i<k;i++){if(!CloseFile()){Action=caNone;return;}}
 if(FrmCmd->isRun){TerminateProcess(FrmCmd->ProcessInfo.hProcess,0);}
 SaveIni();CoUninitialize();
 releaseShift();}

void __fastcall TFrmMeg1::FormResize(TObject *Sender)
{Memo1->Width=ClientWidth;
Memo1->Height=TabControl1->Height-Memo1->Top;//+TabControl1->Top;
//Memo1->Height=ClientHeight-PnlTop->Height-PnlBottom->Height-Memo1->Top;
//-16-PnlTop->Height-PnlBottom->Height;
}

//---------------------------------------------------------------------------
// Edit-Menu
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::Selectall1Click(TObject *Sender)
{Memo1->SelectAll();}
//------
void __fastcall TFrmMeg1::Pasteasnew1Click(TObject *Sender)
{if(CanAdd){AddNewText(NEWFILE);ix=true;Memo1->PasteFromClipboard();Modify();}}

//------------------------- FIND ----------------------
// FindText(FindText,MatchCase?) true:あった false:なかった
/*bool __fastcall TFrmMeg1::FindText(AnsiString txt,bool MatchCase){
 int i,j,x,xx;
 AnsiString ltxt;
 if(Memo1->SelLength){Memo1->SelStart+=Memo1->SelLength;Memo1->SelLength=0;}
 Memo1->SelLength=0;
 if(!MatchCase)txt=txt.LowerCase();
// xx=Memo1->Lines->Strings[Memo1->CaretPos.y].Length()-Memo1->CaretPos.x;
 xx=-CursorX()-2;
 for(i=CursorY();i<=Memo1->Lines->Count;i++){
  ltxt=Memo1->Lines->Strings[i];
  if(i==CursorY()){for(j=0;j<CursorX();j++)ltxt[j+1]=1;}
  if(!MatchCase)ltxt=ltxt.LowerCase();

  if((x=ltxt.Pos(txt))!=0){
   Memo1->SelStart+=xx+x+1;
   Memo1->SelLength=txt.Length();return true;}

  if(i==CursorY())xx=Memo1->Lines->Strings[CursorY()].Length()-CursorX();
  else xx+=Memo1->Lines->Strings[i].Length()+2;
//  if(i==Memo1->CaretPos.Line+1)xx+=Memo1->Lines->Strings[i-1].Length()-Memo1->CaretPos.Col+1;
   }
 return false;
}*/
bool __fastcall TFrmMeg1::FindText(AnsiString txt,bool MatchCase){
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


//----- 検索実行
void __fastcall TFrmMeg1::Find(void){
 FindDialog1->CloseDialog();
 if(!FindText(FindDialog1->FindText,FindDialog1->Options.Contains(frMatchCase)))
  Application->MessageBox("not found","find",MB_OK);}
//----- 次を検索
void __fastcall TFrmMeg1::Findnext1Click(TObject *Sender)
{if(FindDialog1->FindText=="")FindDialog1->Execute();else Find();}
//---- 検索ﾎﾞﾀﾝ押下
void __fastcall TFrmMeg1::FindDialog1Find(TObject *Sender)
{Find();}
//----- Find表示
void __fastcall TFrmMeg1::Find1Click(TObject *Sender){MENUCLKED;
 if(INI("KeyAltS")!=""){NextSplit(INI("KeyAltS"));}
 else FindDialog1->Execute();}// FindDialog1->Tag=0;FindDialog1->Title="Search";FindDialog1->Options>>frHideMatchCase;

//----- Replace 1回実行 true:あった false:なかった
bool __fastcall TFrmMeg1::Replace(void){
 int ret;
 if(FindText(ReplaceDialog1->FindText,ReplaceDialog1->Options.Contains(frMatchCase))){
  ret=(isReplaceAll)?mrYes:MessageDlg("Replace?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo<<mbAll<<mbCancel,0);
  if(ret==mrYes||ret==mrAll){
   if(ret==mrAll)isReplaceAll=true;
   Memo1->SelText=ReplaceDialog1->ReplaceText;//Memo1->SelStart=ReplaceDialog1->ReplaceText.Length();
   Modify();}
  else if(ret==mrCancel)return false; return true;}
 else return false;}
//----- 置換表示
void __fastcall TFrmMeg1::Replace1Click(TObject *Sender){
 releaseShift();
 if(Memo1->SelText!=""){ReplaceDialog1->FindText=Memo1->SelText;Memo1->SelLength=0;}
 ReplaceDialog1->Execute();}
//----- 置換ﾎﾞﾀﾝ押下
void __fastcall TFrmMeg1::ReplaceDialog1Replace(TObject *Sender){
 int repcnt;
 if(ReplaceDialog1->Options.Contains(frReplaceAll)){
  ReplaceDialog1->CloseDialog();
  isReplaceAll=false;repcnt=0;while(Replace()){++repcnt;}
  if(isReplaceAll&&repcnt){Application->MessageBox((IntToStr(repcnt)+" words replased").c_str(),"Replace",MB_OK);}
  }else{isReplaceAll=true;Replace();}}
//----- 置換の検索ﾎﾞﾀﾝ押下
void __fastcall TFrmMeg1::ReplaceDialog1Find(TObject *Sender){
 FindText(ReplaceDialog1->FindText,ReplaceDialog1->Options.Contains(frMatchCase));
 ReplaceDialog1->CloseDialog();}

//--------------------------------
//----- Goto
void __fastcall TFrmMeg1::Goto1Click(TObject *Sender)
{
 //int a,b;
 FrmNumber=new TFrmNumber(Application);
  FrmNumber->Edit1->Text="";
 FrmNumber->Caption="Goto";
 FrmNumber->Label1->Caption="Line number";
 if(FrmNumber->ShowModal()==mrOk){
  //a=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart,0);
  //b=StrToInt(FrmNumber->Edit1->Text);
  //Memo1->Perform(EM_LINESCROLL,0,b-a);
  Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,StrToInt(FrmNumber->Edit1->Text)-1,0);
  Memo1->SelLength=0;}
 FrmNumber->Release();}
//--- 先頭行
//Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,0,0);Memo1->SelLength=0; 最終行
//Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,Memo1->Lines->Count-1,0);Memo1->SelLength=0; 連番設定

void __fastcall TFrmMeg1::mnRenbanClick(TObject *Sender)
{
 FrmNumber=new TFrmNumber(Application);
 FrmNumber->Caption="Number setup";
 FrmNumber->Edit1->Text=IntToStr(renno);
 FrmNumber->Label1->Caption="%d in clipboard(ALT+L)";
 if(FrmNumber->ShowModal()==mrOk)renno=StrToInt(FrmNumber->Edit1->Text);
 FrmNumber->Release();
}
//----- 計算
void __fastcall TFrmMeg1::mnKeisanClick(TObject *Sender)
{AnsiString st;int a,b;
 FrmNumber=new TFrmNumber(Application);
 FrmNumber->Caption="Calc";
 FrmNumber->Edit1->Text=INI("strKeisan");
 FrmNumber->Edit1->SelectAll();
 st=Memo1->SelText;try{b=StrToInt(st);}catch(...){return;}
 FrmNumber->Label1->Caption=st;
 if(FrmNumber->ShowModal()==mrOk){st=FrmNumber->Edit1->Text;
  a=StrToInt(st.SubString(2,st.Length()-1));
  switch(st[1]){
   case '+':Memo1->SelText=IntToStr(b+a);break;
   case '-':Memo1->SelText=IntToStr(b-a);break;
   case '/':Memo1->SelText=IntToStr(b/a);break;
   case '*':Memo1->SelText=IntToStr(b*a);break;}
  INI("strKeisan")=st;
 }
 FrmNumber->Release();
}

//---- ｺﾐｯﾄ切替　
void __fastcall TFrmMeg1::Commit1Click(TObject *Sender)
{FrmCmd->mnCommitClick(Sender);}
//---- SQL発行
void __fastcall TFrmMeg1::SQL1Click(TObject *Sender)
{AnsiString st=Memo1->SelText;if(st==""){Application->MessageBox("SQL is not selected","SQL",MB_OK);return;}
 if(INI("Dbd")==""||INI("Dbname")==""||INI("Dbuser")==""){Application->MessageBox("not enough DB setting","SQL",MB_OK);return;}

 AnsiString cmd=INI("Extpl"),arg;
 AnsiString host=INI("Dbhost");if(host=="")host="localhost";
 AnsiString passwd=strDecrypt(INI("Dbpasswd"),50);if(passwd=="")passwd="\x22\x22";
 SaveKnjString(di_megpas+"sql.dat",INI("Dbknj"),st);
 arg=INI("Dbd")+" "+host+" "+INI("Dbname")+" "+INI("Dbuser")+" "+passwd+" "+IntToStr(FrmCmd->mnCommit->Tag);
 //FrmCmd->Show();
 CallExec(cmd,di_megpas+INI("Dbscript"),arg,true,isAlt);
}

//---------------------------------------------------------------------------
// VIEW-MENU
//---------------------------------------------------------------------------
//----- TabControl
void __fastcall TFrmMeg1::TabControl1Change(TObject *Sender)
{ChangeText(TabControl1->TabIndex,true);}
//-----
void __fastcall TFrmMeg1::Next1Click(TObject *Sender)
{ChangeText((index==li_file->Count-1)?0:index+1,true);}
//-----
void __fastcall TFrmMeg1::Back1Click(TObject *Sender)
{ChangeText((index==0)?li_file->Count-1:index-1,true);}
//----- 最大化
void __fastcall TFrmMeg1::Maximize1Click(TObject *Sender)
{if(WindowState==wsNormal)WindowState=wsMaximized;else WindowState=wsNormal;}
//----- Wrap
void __fastcall TFrmMeg1::mnWrapClick(TObject *Sender)
{
 if(mnWrap->Checked){mnWrap->Checked=false;
  Memo1->ScrollBars=ssBoth;Memo1->WordWrap=false;}
 else{mnWrap->Checked=true;
  Memo1->ScrollBars=ssVertical;Memo1->WordWrap=true;}}
//----- Font
void __fastcall TFrmMeg1::Font1Click(TObject *Sender)
{//TColor c=Memo1->Font->Color;
 TFontDialog *FontDialog1;
 FontDialog1=new TFontDialog(FrmMeg1);
 FontDialog1->Font=Memo1->Font;
 //FontDialog1->Font->Color=clBlack;
 if(FontDialog1->Execute()){
  Memo1->Font=FontDialog1->Font;
//  Fod1->FontColor=(Memo1->Font->Color==clWhite)?clAqua:Memo1->Font->Color;
  //FrmCmd->Font=Memo1->Font;
  }delete FontDialog1;}
//---- 背景色
void __fastcall TFrmMeg1::Background1Click(TObject *Sender){
 TColorDialog *ColorDialog1=new TColorDialog(FrmMeg1);
 ColorDialog1->Color=Memo1->Color;
 if(ColorDialog1->Execute()){Memo1->Color=ColorDialog1->Color;
 //Fod1->Color=ColorDialog1->Color;
  //FrmCmd->Color=Memo1->Color;
  }delete ColorDialog1;}
//---
void __fastcall TFrmMeg1::GetArgument(AnsiString &des,AnsiString na){
 int i,a;AnsiString buf;
 for(i=0;i<Memo1->Lines->Count;i++){buf=Memo1->Lines->Strings[i];
  if((a=AnsiPos(na,buf))!=0){
  buf.Delete(1,a+na.Length()-1);if((a=AnsiPos(";",buf))!=0)buf.Delete(a,buf.Length()-a+1);
  des=buf;i=Memo1->Lines->Count;}}}

//----- Browse
void __fastcall TFrmMeg1::Browse1Click(TObject *Sender){
if(INI("EmuKind")==EM_OPENMSX){
// Memo1->Lines->Add(INI("MSXEmulator")+" \x22"+INI("Machine")+"\x22");
 WinExec((INI("MSXEmulator")+" "+INI("Machine")+" -diska "+INI("DirAsDisk")).c_str(),SW_HIDE);
 }
else{
 WinExec(INI("MSXEmulator").c_str(),SW_SHOW);}
/* AnsiString url;
 if(li_modify->Strings[index]=="1"&&!SaveText())return;
 url=li_file->Strings[index];
 GetArgument(url,"browse=");
 ShellExecute(Handle,"open",url.c_str(),"","",SW_SHOW);*/}

//----- ｺﾏﾝﾄﾞ
void __fastcall TFrmMeg1::CallExec(AnsiString cmd,AnsiString fi,AnsiString arg,bool sql,bool isShow){
// if(!strReplace(cmd,"%f",fi))cmd=cmd+" \x22"+fi+"\x22";
// if(!strReplace(cmd,"%a",arg)){if(arg!="")arg=arg+" \x22"+arg+"\x22";}
// if(fi.SubString(1,3)==NEWFILE)fi="";
// Application->MessageBox(cmd.c_str(),"OK",MB_OK);
 strReplace(cmd,"%f",fi);
 strReplace(cmd,"%a",arg);
 strReplace(cmd,"%s",Memo1->SelText);
 strReplace(cmd,"%d",ExtractFilePath(fi));
 strReplace(cmd,"%b",INI("dirDB"));
 strReplace(cmd,"%B",INI("dirAGK"));
// ShowMessage(cmd);
 if(strReplace(cmd,"%g","")){WinExec(cmd.c_str(),SW_SHOW);}
 else{
 /*if(!isShow||FrmCmd->Visible==false)*/FrmCmd->Show();
 FrmCmd->Exec(cmd,(fi.AnsiPos(".ccz80"))?di_megpas:ExtractFilePath(fi),sql);}
}

//-- ファイルサイズを取得
int __fastcall TFrmMeg1::getFileSize(AnsiString fi){
 if(!FileExists(fi))return 0;
 int han;if((han=FileOpen(fi,fmOpenRead))==-1){return 0;}
 int len=FileSeek(han,0,2);FileClose(han);
 return len;}

bool __fastcall TFrmMeg1::isInsDmSys(AnsiString st){
 if(st.AnsiPos("music.ccz80++")||st.AnsiPos("gtext.ccz80++")||st.AnsiPos("sound.ccz80++"))
  return true;else return false;}

//---------- RUN
void __fastcall TFrmMeg1::mnCommandClick(TObject *Sender){MENUCLKED;
 if(li_modify->Strings[index]=="1"&&!SaveText())return;
 AnsiString fi=li_file->Strings[index];
 AnsiString cmd,ext=ExtractFileExt(fi).LowerCase(),fi_comp;ext.Delete(1,1);
 AnsiString arg="";
 AnsiString maing="";
 AnsiString fi_de=INI("DiskExplorer");
 bool isRom=(INI("ExportRom")=="1"||INI("ExportRom")=="2"||INI("ExportRom")=="3")?true:false,isCcz80p=(ext=="ccz80++")?true:false,isCom=(INI("ExportRom")=="2")?true:false,isExbin=(INI("ExportRom")=="3")?true:false;
 bool isMus=(ext=="mus")?true:false;
 bool isDmsys2,isCpc=false;
 AnsiString argRom="1";//,argOrg=INI("Ccz80Org");
 if(isCom){argRom="2";}
 else if(isExbin){argRom="3";}

 //--- gen ccz80 batch
 if(ext=="ccz80"||isCcz80p){
  if(isCcz80p){
   isCpc=(Memo1->Lines->Text.AnsiPos("Amstrad")||INI("EmuKind")==EM_PCCPC||INI("EmuKind")==EM_WINAPE)?true:false;if(isCpc)isRom=false;
   if(!Memo1->Lines->Text.AnsiPos("main()")){
    if(fi_ccz80ptarget==""){Application->MessageBox("Set target file from [View]-[Set target]","Caution",MB_OK);}
    else{fi=fi_ccz80ptarget;isDmsys=false;}}
   else{fi_ccz80ptarget=fi;
    if(isInsDmSys(Memo1->Text)){isDmsys=true;}else{isDmsys=false;}
   }}
  isDmsys2=isDmsys;
  TStringList *li_buf=new TStringList();
  AnsiString fi_bin;
  if(fi_de=="")fi_de="none";
 //  d:\projects\fpcx\fpcx.exe D:\db\bas2\bubbo.bin D:\apps\editd165e2\EDITDISK.exe D:\apps\bluemsx\blueMSX.exe b000
  if(isCcz80p)li_buf->Add("@echo off");
  if(isRom){fi_comp=ChangeFileExt(fi,".asm");// romの場合の追加処理
   li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_comp+"\x22 rom="+argRom+" rommode="+((isCcz80p)?"1":"0")+" data="+INI("Ccz80Data"));
   fi_bin=ChangeFileExt(fi,".tmp");
   AnsiString cmd=INI("Ext"+ext);
   int a;if((a=cmd.AnsiPos(".exe"))>0){cmd.Insert("\x22",a+4);cmd="\x22"+cmd;}
   if(isCom)strReplace(cmd,INI("Ccz80Org"),"100");
   strReplace(cmd,"%f",fi_bin);
   strReplace(cmd,"%d",ExtractFilePath(fi));
   strReplace(cmd," /post=fpcx.bat","");
//   strReplace(cmd,"#"+INI("Ccz80Org"),"");
   li_buf->Add(cmd);}
  else fi_comp=ChangeFileExt(fi,".bin");
  if(isCcz80p)DeleteFile(fi_comp);

  fi_bin=ChangeFileExt(fi,".bin");
//   li_buf->Add(fi_fpcx+" \x22infile="+ChangeFileExt(fi,".asm")+"\x22 view=1");
//   li_buf->SaveToFile(di_megpas+"fpcx.bat");
//   CallExec(INI("ExtCcz80")+" /asm",fi,"",false,isAlt);}
  if(isCpc){bool isApe=(Memo1->Lines->Text.AnsiPos("winape"))?true:false;
   AnsiString emu=INI("MSXEmulator");
   if(!isApe)WinExec((di_megpas+"fpcx\\poscpc.exe -1").c_str(),SW_SHOW);
   li_buf->Add("\x22"+di_megpas+"fpcx\\cpcfs.exe\x22 \x22"+di_megpas+"fpcx\\cpc.dsk\x22 p -b -e \x22"+fi_bin+"\x22,0x"+INI("Ccz80Org")+",0x"+INI("Ccz80Org"));
   li_buf->Add("\x22"+di_megpas+"fpcx\\cpcfs.exe\x22 \x22"+di_megpas+"fpcx\\cpc.dsk\x22 d cpc4.bin");
   li_buf->Add("\x22"+di_megpas+"fpcx\\cpcfs.exe\x22 \x22"+di_megpas+"fpcx\\cpc.dsk\x22 r "+ExtractFileName(fi_bin)+" cpc4.bin");
   if(INI("EmuKind")==EM_PCCPC){
    li_buf->Add("cd \x22"+ExtractFilePath(emu)+"\x22");
    li_buf->Add("\x22"+di_megpas+"fpcx\\run.exe\x22 \x22"+ExtractFileName(emu)+" -disk "+di_megpas+"fpcx\\cpc.dsk -run disc\x22");}
   else if(INI("EmuKind")==EM_WINAPE){
    li_buf->Add("cd \x22"+ExtractFilePath(emu)+"\x22");
    li_buf->Add("\x22"+di_megpas+"fpcx\\run.exe\x22 \x22"+ExtractFileName(emu)+" "+di_megpas+"fpcx\\cpc.dsk /a:disc\x22");}
   else if(isApe){
    li_buf->Add("cd \x22"+di_megpas+"..\\WinAPE\x22");
    li_buf->Add("\x22"+di_megpas+"fpcx\\run.exe\x22 \x22WinApe.exe "+di_megpas+"fpcx\\cpc.dsk /a:disc\x22");
   }else{li_buf->Add("cd \x22"+di_megpas+"..\\pc-cpc\x22");
    li_buf->Add("\x22"+di_megpas+"fpcx\\run.exe\x22 \x22pc-cpc.exe -disk "+di_megpas+"fpcx\\cpc.dsk -run disc -1\x22");
    }
   }
  else if(INI("EmuKind")==EM_OPENMSX){
   if(isExbin)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22"+"outdir="+INI("DirAsDisk")+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 org="+INI("Ccz80Org")+" bloader="+INI("Ccz80GenBas")+" option=\x22"+INI("Machine")+"\x22 rom=3 romsize="+INI("RomSize"));
   else if(isCom)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 option=\x22"+INI("Machine")+"\x22 rom=2 romsize="+INI("RomSize")+" \x22"+"outdir="+INI("DirAsDisk")+"\x22");
   else if(isRom)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 option=\x22"+INI("Machine")+"\x22 rom=1 romsize="+INI("RomSize"));
   else li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22"+"outdir="+INI("DirAsDisk")+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 org="+INI("Ccz80Org")+" bloader="+INI("Ccz80GenBas")+" option=\x22"+INI("Machine")+"\x22");}
  else{
   if(isExbin)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22"+"editdisk="+fi_de+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 org="+INI("Ccz80Org")+" bloader="+INI("Ccz80GenBas")+" dragdsk="+INI("DragDsk")+" rom=3 romsize="+INI("RomSize"));
   else if(isCom)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 rom=2 romsize="+INI("RomSize")+" \x22"+"editdisk="+fi_de+"\x22");
   else if(isRom)li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 rom=1 romsize="+INI("RomSize"));
   else li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_bin+"\x22 \x22"+"editdisk="+fi_de+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 org="+INI("Ccz80Org")+" bloader="+INI("Ccz80GenBas")+" dragdsk="+INI("DragDsk"));}

  li_buf->SaveToFile(di_megpas+"fpcx.bat");
  if((!isRom||isExbin)&&INI("Ccz80GenBas")=="1"&&!isCpc){
   AnsiString st="1 "+INI("Ccz80Loader");
   AnsiString binname=ExtractFileName(fi_bin).UpperCase();if(binname.Length()>12)binname=binname.SubString(1,8)+".BIN";
   strReplace(st,"%f",binname);
   strReplace(st,"%a1",(isDmsys2)?"bload\x22\x44ISKINST.BIN\x22,r:_syson":"");
   strReplace(st,"%a2",(isDmsys2)?"_sysoff":"");
   strReplace(st,"::",":");
   li_buf->Text=st;
   li_buf->SaveToFile(di_megpas+"fpcx\\autoexec.bas");}
  delete li_buf;
  if(isRom){
   cmd=INI("Ext"+ext);
//   strReplace(cmd,"#"+INI("Ccz80Org"),"#4000");
//   AnsiString addOpt;if(isCcz80p)addOpt="/out=assembler";else addOpt="/asm";
   CallExec(cmd+" "+((isCcz80p)?"/out=assembler":"/asm"),fi,"",false,isAlt);goto SKIPCMD;}}
 //-- MGS pre
 if(isMus){fi_comp=ChangeFileExt(fi,".MGS");
  if(FileExists(fi_comp)){if(!DeleteFile(fi_comp)){Application->MessageBox("Can't write the MGS file","Error",MB_ICONERROR);return;}}}

 //---- general execute
 GetArgument(arg,"cmdarg=");
 GetArgument(maing,"maing=");
 if(maing!=""){
  if(ext=="g")gendbpro(fi,false);
  if(ext=="g2")genagk(fi,false);}

 cmd=INI("Ext"+ext);
 if(cmd==""){Application->MessageBox("Not exists application for this extention","Run",MB_OK);return;}
 if(maing!=""){strReplace(fi,ExtractFileName(fi),maing);}
 if(isCpc)strReplace(cmd,"msx","cpc");
 SetStatus("Run");
 CallExec(cmd,fi,arg,false,isAlt);
 SKIPCMD:
 //--- ccz80++ after
 if(isCcz80p&&FileExists(fi_comp)){
  CallExec("fpcx.bat",fi,"",false,isAlt);}
 //--- MGS after
 if(isMus&&getFileSize(fi_comp)){
  if(INI("EmuKind")==EM_OPENMSX){
   CallExec(fi_fpcx+" \x22infile="+fi_comp+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 \x22outdir="+INI("DirAsDisk")+"\x22%g",fi_comp,"",false,isAlt);}
  else{
   CallExec(fi_fpcx+" \x22infile="+fi_comp+"\x22 \x22msxemu="+INI("MSXEmulator")+"\x22 \x22"+"editdisk="+fi_de+"\x22%g",fi_comp,"",false,isAlt);}
 }
}

//----- 再実行/* if(!isAlt||FrmCmd->Visible==false)FrmCmd->Show();
/* FrmCmd->Exec(FrmCmd->Edit1->Text,FrmCmd->CurrentDir,false);*/
//----- ｺﾏﾝﾄﾞｳｨﾝﾄﾞ表示
void __fastcall TFrmMeg1::N6Click(TObject *Sender)
{FrmCmd->Show();}

//--- 登録ｺｰﾄﾞﾁｪｯｸ
//bool __fastcall TFrmMeg1::chkRegcode(AnsiString st){
//return (strEncrypt(st,43)=="8R"+strRegcode+"aGrq")?true:false;}

//----- 設定
void __fastcall TFrmMeg1::mnOptionClick(TObject *Sender){
 int i,j;AnsiString st;
 FrmOption=new TFrmOption(Application);
 FrmOption->EdtFileMask->Text=INI("FileMask");
 FrmOption->ChkSjisOnly->Checked=(INI("SjisOnly")=="1")?true:false;
 FrmOption->ChkAutoIndent->Checked=(INI("AutoIndent")=="1")?true:false;
 FrmOption->CmbDbd->Text=INI("Dbd");
 FrmOption->EdtDbname->Text=INI("Dbname");
 FrmOption->EdtDbhost->Text=INI("Dbhost");
 FrmOption->EdtDbuser->Text=INI("Dbuser");
 FrmOption->EdtDbpasswd->Text=strDecrypt(INI("Dbpasswd"),50);
 FrmOption->CmbDbknj->Text=INI("Dbknj");
 FrmOption->CmbExt->Items->Clear();
 st=INI("FuncJump");st.Delete(st.Length(),1);
 FrmOption->EdtFuncJump->Text=st;
// FrmOption->EdtRegcode->Text=INI("Regcode");
 FrmOption->EdtWinScp->Text=INI("Winscp");
 FrmOption->EdtWinScpMod->Text=INI("WinscpMod");
 FrmOption->EdtSuggestion->Text=INI("ListBoxFontSize");
 for(i=0;i<li_ini->Count;i++){
  if(li_ini->Strings[i].SubString(1,3)=="Ext"){
   st=li_ini->Strings[i];
   FrmOption->CmbExt->Items->Add(st.SubString(4,AnsiPos("=",st)-4));}}
 FrmOption->EdtButkey1->Text=INI("BtnKey1");
 FrmOption->EdtButkey2->Text=INI("BtnKey2");
 FrmOption->EdtButkey3->Text=INI("BtnKey3");
 FrmOption->EdtBtnKeySizeX->Text=INI("BtnKeySizeX");
 FrmOption->EdtBtnKeySizeY->Text=INI("BtnKeySizeY");

 if(FrmOption->ShowModal()==mrOk){
  INI("FileMask")=FrmOption->EdtFileMask->Text;
  INI("SjisOnly")=(FrmOption->ChkSjisOnly->Checked)?"1":"0";
  INI("AutoIndent")=(FrmOption->ChkAutoIndent->Checked)?"1":"0";
 INI("Dbd")=FrmOption->CmbDbd->Text;
 INI("Dbname")=FrmOption->EdtDbname->Text;
 INI("Dbhost")=FrmOption->EdtDbhost->Text;
 INI("Dbuser")=FrmOption->EdtDbuser->Text;
 INI("Dbpasswd")=strEncrypt(FrmOption->EdtDbpasswd->Text,50);
 INI("Dbknj")=FrmOption->CmbDbknj->Text;
 INI("FuncJump")=FrmOption->EdtFuncJump->Text+"|";
 INI("Winscp")=FrmOption->EdtWinScp->Text;
 INI("WinscpMod")=FrmOption->EdtWinScpMod->Text;
 INI("BtnKey1")=FrmOption->EdtButkey1->Text;
 INI("BtnKey2")=FrmOption->EdtButkey2->Text;
 INI("BtnKey3")=FrmOption->EdtButkey3->Text;
 INI("BtnKeySizeX")=FrmOption->EdtBtnKeySizeX->Text;
 INI("BtnKeySizeY")=FrmOption->EdtBtnKeySizeY->Text;
 for(i=0;i<BTNWY-1;i++){for(j=0;j<BTNWX;j++){BtnKey[i*BTNWX+j]->Caption=getButKey(i,j);}}
 INI("ListBoxFontSize")=FrmOption->EdtSuggestion->Text;

 // INI("Regcode")=FrmOption->EdtRegcode->Text;
 RefreshTextMenu();}
 FrmOption->Release();
}
//----- INI表示
/*AddNewText(fi_ini);ix=true;LoadKnjText("");*/
//----- ﾍﾙﾌﾟ
void __fastcall TFrmMeg1::mnHelpClick(TObject *Sender)
{//WinExec(("winhlp32.exe "+di_megpas+"help\\megson.hlp").c_str(),SW_SHOW);
// Application->HelpCommand(HELP_FINDER,0);
// Application->HelpCommand(HELP_CONTEXT,1);
  ShellExecute(Handle,"open",(di_megpas+"doc\\readme.html").c_str(),"","", SW_SHOW);
 // ShellExecute(Handle,"open",(di_megpas+"megson.hlp").c_str(),"","",SW_SHOW);
}
//------ about
void __fastcall TFrmMeg1::mnAboutClick(TObject *Sender)
{Application->MessageBox(VER,"Version",MB_OK);}
//----- Ctrl+F1～F5
void __fastcall TFrmMeg1::mnCtrlFxClick(TObject *Sender){//
 AnsiString cmd=INI("CmdCtrlF"+IntToStr(((TMenuItem*)Sender)->Tag));
 if(cmd==""||(li_modify->Strings[index]==1&&!SaveText()))return;
 AnsiString fi=li_file->Strings[index];
 AnsiString arg="";GetArgument(arg,"cmdarg=");
 CallExec(cmd,fi,arg,false,isAlt);
}

//---------------------------------------------------------------------------
// Tag-Menu
//---------------------------------------------------------------------------
AnsiString __fastcall TFrmMeg1::GetMenuText(AnsiString buf){
 AnsiString buf2=buf[buf.Length()];
 buf=INI(buf);buf2="(&"+buf2+")";
 if(buf=="")return "---"+buf2;
 if(buf.Length()>20){return buf.SubString(1,19)+"..."+buf2;}
 return buf+buf2;}

/*AnsiString __fastcall TFrmMeg1::GetMenuText2(AnsiString buf){
 AnsiString buf2=buf[buf.Length()];
 buf=INI(buf);buf2="(&"+buf2+")";
 if(buf=="")return "---"+buf2;
 if(buf.Length()>20){return buf.SubString(1,19)+"..."+buf2;}
 return buf+buf2;}*/

//#define GetMenuText(T) (T=="")?"(none)":T;
void __fastcall TFrmMeg1::RefreshTextMenu(void){
 mnAlt1->Caption=GetMenuText("KeyAlt1");
 mnAlt2->Caption=GetMenuText("KeyAlt2");
 mnAlt3->Caption=GetMenuText("KeyAlt3");
 mnAlt4->Caption=GetMenuText("KeyAlt4");
 mnAlt5->Caption=GetMenuText("KeyAlt5");
 mnAlt6->Caption=GetMenuText("KeyAlt6");
 mnAlt7->Caption=GetMenuText("KeyAlt7");
 mnAlt8->Caption=GetMenuText("KeyAlt8");
 mnAlt9->Caption=GetMenuText("KeyAlt9");
 mnAlt0->Caption=GetMenuText("KeyAlt0");
 mnShiftAlt1->Caption=GetMenuText("KeyShiftAlt1");
 mnShiftAlt2->Caption=GetMenuText("KeyShiftAlt2");
 mnShiftAlt3->Caption=GetMenuText("KeyShiftAlt3");
 mnShiftAlt4->Caption=GetMenuText("KeyShiftAlt4");
 mnShiftAlt5->Caption=GetMenuText("KeyShiftAlt5");
 mnShiftAlt6->Caption=GetMenuText("KeyShiftAlt6");
 mnShiftAlt7->Caption=GetMenuText("KeyShiftAlt7");
 mnShiftAlt8->Caption=GetMenuText("KeyShiftAlt8");
 mnShiftAlt9->Caption=GetMenuText("KeyShiftAlt9");
 mnShiftAlt0->Caption=GetMenuText("KeyShiftAlt0");
 mnCtrlF1->Caption=GetMenuText("CmdCtrlF1");
 mnCtrlF2->Caption=GetMenuText("CmdCtrlF2");
 mnCtrlF3->Caption=GetMenuText("CmdCtrlF3");
 mnCtrlF4->Caption=GetMenuText("CmdCtrlF4");
 mnCtrlF5->Caption=GetMenuText("CmdCtrlF5");
 }

//---- Tag.割当
void __fastcall TFrmMeg1::mnTagAssignClick(TObject *Sender){
 FrmKeyas=new TFrmKeyas(Application);
 FrmKeyas->EdtCtrl1->Text=INI("KeyAlt1"); FrmKeyas->EdtCtrl2->Text=INI("KeyAlt2"); FrmKeyas->EdtCtrl3->Text=INI("KeyAlt3");
 FrmKeyas->EdtCtrl4->Text=INI("KeyAlt4"); FrmKeyas->EdtCtrl5->Text=INI("KeyAlt5"); FrmKeyas->EdtCtrl6->Text=INI("KeyAlt6");
 FrmKeyas->EdtCtrl7->Text=INI("KeyAlt7"); FrmKeyas->EdtCtrl8->Text=INI("KeyAlt8"); FrmKeyas->EdtCtrl9->Text=INI("KeyAlt9");
 FrmKeyas->EdtCtrl0->Text=INI("KeyAlt0");
 FrmKeyas->EdtSCtrl1->Text=INI("KeyShiftAlt1"); FrmKeyas->EdtSCtrl2->Text=INI("KeyShiftAlt2"); FrmKeyas->EdtSCtrl3->Text=INI("KeyShiftAlt3");
 FrmKeyas->EdtSCtrl4->Text=INI("KeyShiftAlt4"); FrmKeyas->EdtSCtrl5->Text=INI("KeyShiftAlt5"); FrmKeyas->EdtSCtrl6->Text=INI("KeyShiftAlt6");
 FrmKeyas->EdtSCtrl7->Text=INI("KeyShiftAlt7"); FrmKeyas->EdtSCtrl8->Text=INI("KeyShiftAlt8"); FrmKeyas->EdtSCtrl9->Text=INI("KeyShiftAlt9");
 FrmKeyas->EdtSCtrl0->Text=INI("KeyShiftAlt0");
// FrmKeyas->EdtAltX->Text="";FrmKeyas->ComboBox1->Text="";FrmKeyas->EdtShiftAltX->Text="";
 if(FrmKeyas->ShowModal()==mrOk){
  INI("KeyAlt1")=FrmKeyas->EdtCtrl1->Text; INI("KeyAlt2")=FrmKeyas->EdtCtrl2->Text;  INI("KeyAlt3")=FrmKeyas->EdtCtrl3->Text;
  INI("KeyAlt4")=FrmKeyas->EdtCtrl4->Text; INI("KeyAlt5")=FrmKeyas->EdtCtrl5->Text;  INI("KeyAlt6")=FrmKeyas->EdtCtrl6->Text;
  INI("KeyAlt7")=FrmKeyas->EdtCtrl7->Text; INI("KeyAlt8")=FrmKeyas->EdtCtrl8->Text;  INI("KeyAlt9")=FrmKeyas->EdtCtrl9->Text;
  INI("KeyAlt0")=FrmKeyas->EdtCtrl0->Text;
  INI("KeyShiftAlt1")=FrmKeyas->EdtSCtrl1->Text; INI("KeyShiftAlt2")=FrmKeyas->EdtSCtrl2->Text; INI("KeyShiftAlt3")=FrmKeyas->EdtSCtrl3->Text;
  INI("KeyShiftAlt4")=FrmKeyas->EdtSCtrl4->Text; INI("KeyShiftAlt5")=FrmKeyas->EdtSCtrl5->Text; INI("KeyShiftAlt6")=FrmKeyas->EdtSCtrl6->Text;
  INI("KeyShiftAlt7")=FrmKeyas->EdtSCtrl7->Text; INI("KeyShiftAlt8")=FrmKeyas->EdtSCtrl8->Text; INI("KeyShiftAlt9")=FrmKeyas->EdtSCtrl9->Text;
  INI("KeyShiftAlt0")=FrmKeyas->EdtSCtrl0->Text;
  RefreshTextMenu();}
 FrmKeyas->Release();}

//---- Tag.Color
void __fastcall TFrmMeg1::Color1Click(TObject *Sender){
TColorDialog *ColorDialog1=new TColorDialog(FrmMeg1);
if(ColorDialog1->Execute()){
 Memo1->SelText="#"
 +IntToHex((ColorDialog1->Color&0xFF),2)
 +IntToHex((ColorDialog1->Color&0x00FF00)>>8,2)
 +IntToHex((ColorDialog1->Color&0xFF0000)>>16,2);}delete ColorDialog1;}
//---- Tag.AltX

void __fastcall TFrmMeg1::mnAltXClick(TObject *Sender){
 int a=((TMenuItem*)Sender)->Tag;
 AnsiString buf;
 if(a>9)buf="KeyShiftAlt"+IntToStr(a-10);else buf="KeyAlt"+IntToStr(a);
 buf=INI(buf);
 if(buf!="")NextSplit(buf);}
//Tag.IMG
// Kanji Menu
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::mnKnj1Click(TObject *Sender)
{
 li_knj->Strings[index]=((TMenuItem*)Sender)->Caption;
 mnKnj->Caption=li_knj->Strings[index]+KNJHOTKEY;
}
//---------------------------------------------------------------------------
// Memo1 Events
//---------------------------------------------------------------------------
//----
bool __fastcall TFrmMeg1::strReplace(AnsiString &st,AnsiString txt,AnsiString txt2){
 int a;bool re=false;
 while((a=AnsiPos(txt,st))!=0){st.Delete(a,txt.Length());st.Insert(txt2,a);re=true;}
 return re;
}

//----- InsertText(Text) ｶｰｿﾙ位置にText挿入
void __fastcall TFrmMeg1::InsertText(AnsiString &st){
 int a;
//  Caption=ShortDateFormat;
//Caption=LongTimeFormat;
 // while((a=AnsiPos("\\n",st))!=0){st.Delete(a,1);st[a]='\n';}
// while((a=AnsiPos("%DATE%",st))!=0){st.Delete(a,6);st.Insert(DateToStr(Date()),a);}
 strReplace(st,"\\n","\xd\xa");
 strReplace(st,"\\v","|");
 strReplace(st,"\\t","\x9");
 strReplace(st,"%SELTEXT%",bakSelText);
 strReplace(st,"%TIME%",TimeToStr(Time()));
 strReplace(st,"%DATE%",DateToStr(Date()));
// strReplace(st,"%KINO%",DateToStr(Date()-1));
 if(Clipboard()->AsText!="")strReplace(st,"%CLIP%",Clipboard()->AsText);
 if(AnsiPos("%INPUT%",st)){
  FrmNumber=new TFrmNumber(Application);
  FrmNumber->Edit1->Text="";
  FrmNumber->Caption="入力";
  FrmNumber->Label1->Caption="";
  FrmNumber->ShowModal();
  strReplace(st,"%INPUT%",FrmNumber->Edit1->Text);
  FrmNumber->Release();}

// strReplace(st,"%FILE%",ExtractFilePath(li_file->Strings[index]));
// strReplace(st,"%DIR%",ExtractFileDir(li_file->Strings[index]));
// while((a=AnsiPos("%KINO%",st))!=0){st.Delete(a,6);st.Insert(DateToStr(Date()-1),a);}

 Memo1->SelText=st;
 //Strange Addjustment
// Memo1->SelStart+=Memo1->SelLength;Memo1->SelLength=0;
 Modify();}

AnsiString __fastcall TFrmMeg1::NextSplit(AnsiString st){
 int i,a=1,b;bool z=false;
 for(i=0;i<tb_cnt;i++){a=AnsiPos("|",st);
  if(a){/*if(st[a-1]=='\\')--i;*/st.Delete(a,1);}}
 if((b=AnsiPos("|",st))!=0){
  st=st.SubString(a,b-a);++tb_cnt;z=true;}else
  {if(tb_cnt)z=true;tb_cnt=0;st=st.SubString(a,st.Length()-a+1);}

 if(!tb_in)bakSelText=Memo1->SelText;
 InsertText(st);
 if(z){Memo1->SelStart-=st.Length();Memo1->SelLength=st.Length();tb_in=1;}
 return st;}

// %%にﾍﾟｰｽﾄ
void __fastcall TFrmMeg1::PasteToTemp(bool ret){
#define Match4(X) (c1==X&&c2==X&&c3==X&&c4==X)
#define Match1(X,Y) (c1==X&&c2==Y)
 AnsiString st,uid;int l,a,i;char c1,c2/*,c3,c4,tbk*/;
// TDateTime dt;
 if(Memo1->SelLength==0){st=Clipboard()->AsText.Trim();
  if(st.Length()==0)return;
  if(ret){
   TStringList *li;li=new TStringList();
   li->Text=st;st="";a=0;
   for(i=0;i<li->Count;i++){uid=li->Strings[i];
   if(uid.Length()>0&&uid[1]!='\''&&uid[uid.Length()]!='\'')uid="'"+uid+"',";
    st=st+uid;if(++a==5){a=0;st=st+"\x0d\x0a";}}
    st=st.Trim();if(st[st.Length()]==',')st.Delete(st.Length(),1);
   }
  }
 else st=Memo1->SelText.Trim();
 l=Memo1->SelStart+1;a=Memo1->GetTextLen();//tbk=0;
 for(i=l;i<=a;i++){
  c1=Memo1->Lines->Text[i];c2=Memo1->Lines->Text[(a<i+1)?a:i+1];
//  c3=Memo1->Lines->Text[(a<i+2)?a:i+2];
//  c4=Memo1->Lines->Text[(a<i+3)?a:i+3];
//  if(tbk&&(c1==32||c1==10||c1==13))return;
/*  if(Match4('y')){
   Memo1->SelStart=i-1;Memo1->SelLength=4;st=Memo1->SelText;Memo1->SelText=FormatDateTime(st,Now());tbk=1;}
  else if(Match1('y','y')||Match1('m','m')||Match1('d','d')||Match1('h','h')||Match1('n','n')||Match1('s','s')){
   Memo1->SelStart=i-1;Memo1->SelLength=2;st=Memo1->SelText;Memo1->SelText=FormatDateTime(st,Now());tbk=1;}
  else*/ if(Match1('%','%')){
   Memo1->SelStart=i-1;Memo1->SelLength=2;Memo1->SelText=st;
/*   Memo1->SelStart=i-1;Memo1->SelLength=st.Length();*/return;}}}

//---- Modify
void __fastcall TFrmMeg1::Modify(void){
 li_modify->Strings[index]="1";menuModify->Caption="@";}
//---- SetMenuCol
int __fastcall TFrmMeg1::CursorX(void){
 int a=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);
 return Memo1->SelStart-FrmMeg1->Memo1->Perform(EM_LINEINDEX,a, 0);}
int __fastcall TFrmMeg1::CursorY(void){return Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart, 0);}
/*void __fastcall TMegMain::CursorPos(void){
 int CurPos,Line,LinePos;//,LineCount;
  CurPos=Memo1->SelStart;
  Line=Memo1->Perform(EM_LINEFROMCHAR, CurPos, 0);
  LinePos=Memo1->Perform(EM_LINEINDEX, Line, 0);
//  LineCount=Memo1->Perform(EM_GETLINECOUNT,0,0);
 Line0->Caption=IntToStr(Line+1)+":"+IntToStr((CurPos-LinePos)+1);//+"/"+IntToStr(LineCount);
/* int cuy=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart,0);int cux=Memo1->SelStart-Memo1->Perform(EM_LINEINDEX,cuy,0);Line0->Caption=IntToStr(cuy+1)+":"+IntToStr(cux+1);}*/

void __fastcall TFrmMeg1::SetMenuCol(void){
 //menuCol->Caption=IntToStr(Memo1->CaretPos.x+1)+":"+IntToStr(Memo1->CaretPos.y+1);
/* menuCol->Caption=IntToStr(Memo1->CaretPos.y+1)+":"+IntToStr(Memo1->CaretPos.x+1);
 menuCol->Caption=IntToStr(Memo1->CaretPos.y+1)+":"+IntToStr(Memo1->CaretPos.x+1);*/
 if(kukeiCopy==0){menuCol->Caption=IntToStr(CursorY()+1)+":"+IntToStr(CursorX()+1);}
 }
//-----
void __fastcall TFrmMeg1::Memo1Change(TObject *Sender){
 if(ix){ix=false;}else Modify();//lyf=true;
 } // ixが立ってる場合更新ﾌﾗｸﾞ立てない
//-----
int NumCtrlCode(AnsiString st){
 int i,a=0;for(i=1;i<=st.Length();i++){if(st[i]<32)++a;}
 return a;}

void __fastcall TFrmMeg1::Memo1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{int aa,a,i;char c;
 bool iCtrl=Shift.Contains(ssCtrl),
 iShift=Shift.Contains(ssShift),
 iAlt=Shift.Contains(ssAlt);
 AnsiString buf;

 if(iCtrl){
  if(Key>='1'&&Key<='9'&&li_file->Count>Key-'1'){
   ChangeText(Key-'1',true);}}
//  case VK_PRIOR:Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,0,0);Memo1->SelLength=0;break;
//  case VK_NEXT:Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,Memo1->Lines->Count-1,0);Memo1->SelLength=0;break;}}
 if(iAlt){isAlt=true;switch(Key){
  case VK_F9:mnCommandClick(Sender);break;
  case 'Q':if(iCtrl)SQL1Click(Sender);break;
  case VK_RIGHT:a=Memo1->SelStart+Memo1->SelLength;i=a;++a;
  while(a<Memo1->Lines->Text.Length()){++a;c=Memo1->Lines->Text[a];
   if(c=='>'||c=='<'){aa=Memo1->SelLength;
  //z=2;Memo1->SelStart=a-1;Memo1->SelLength=1;Memo1->SelText=c;
   Memo1->SelStart=i-aa;if(c=='<')--a;
   if(iShift)Memo1->SelLength=aa+a-i;
   else{Memo1->SelStart=a;Memo1->SelLength=0;}break;}}break;
  case VK_LEFT:a=Memo1->SelStart;i=a;
   while(a>1){--a;c=Memo1->Lines->Text[a];
    if(c=='>'||c=='<'){
     aa=Memo1->SelLength;//zz=2;Memo1->SelStart=a-1;Memo1->SelLength=1;Memo1->SelText=c;
     --a;Memo1->SelStart=a+1;if(c=='<'){--Memo1->SelStart;++aa;}
     if(iShift)Memo1->SelLength=aa+i-a-1;else Memo1->SelLength=0;
     break;}}break;
  case 188:Memo1->SelText="&lt;";break;
  case 190:Memo1->SelText="&gt;";break;}}

 if(iAlt&&iShift){
  //if(Key>='!'&&Key<=')')Key+='1'-'!';else if(Key=='~')Key='0';
  if(Key>='0'&&Key<='Z'){buf=(char)Key;
  buf=INI("KeyShiftAlt"+buf);
  if(buf!=""){NextSplit(buf);}}}
 else if(iAlt){
  switch(Key){
  case 'L'://sprintf(s,Clipboard()->AsText.c_str(),renno,renno,renno,renno,renno);
    //Memo1->SelText=buf.sprintf(Clipboard()->AsText.c_str(),renno,renno,renno,renno,renno,renno,renno,renno,renno,renno);
    InsertText(buf.sprintf(Clipboard()->AsText.c_str(),renno,renno,renno,renno,renno,renno,renno,renno,renno,renno));
    ++renno;break;
  default:if(Key>='0'&&Key<='Z'){buf=(char)Key;buf=INI("KeyAlt"+buf);//Caption=IntToStr((int)Key);
   if(buf!=""){NextSplit(buf);}}break;}}
 switch(Key){
  case VK_RETURN:ly=CursorY();break;
  case VK_F12:
  if(iAlt){reloadKouho();Application->MessageBox("kouho reloaded","!",MB_OK);}
  else if(iCtrl){Clipboard()->AsText="@"+TabControl1->Tabs->Strings[TabControl1->TabIndex];}else PasteToTemp(iShift);break;
  case VK_F1:
   try{int s1=Memo1->SelStart,s2,a;
    AnsiString st=Memo1->Lines->Text,st2;
    a=s1;while(a>0&&((st[a]>='A'&&st[a]<='Z')||(st[a]>='a'&&st[a]<='z')||(st[a]>='0'&&st[a]<='9')))--a;
    s2=a;a=s1;
    while(a<=st.Length()&&((st[a]>='A'&&st[a]<='Z')||(st[a]>='a'&&st[a]<='z')||(st[a]>='0'&&st[a]<='9')))++a;
   if(s2+1<1||a-s1-1<1)return;//||s2+1>=st.Length())return;
   st=st.SubString(s2+1,a-s2-1);int j;//ShowMessage("|"+st+"|");return;
  AnsiString diDB=(INI("wl")=="agk")?INI("dirAGK"):INI("dirDB");
  if(st.Length()>0){
   for(int i=0;i<li_kouho->Count;i++){
    if(li_kouho->Strings[i].AnsiPos(st)==1){
     st2=li_kouho->Strings[i];
     for(j=st2.Length();j>1&&st2[j]!=',';j--);
     st2.Delete(1,j);
      if(diDB.AnsiPos("Tier"))st2=diDB+"Help\\Reference\\"+st2; else st2=diDB+"Help\\commands\\"+st2;
      if(!FileExists(st2)){
       Application->MessageBox(st2.c_str(),"not found",MB_ICONERROR);return;}
      ShellExecute(Handle,"open",st2.c_str(),NULL,NULL,SW_SHOW);return;
      }}
  if(INI("wl")!="agk")st2=INI("dirDB")+"Help\\commands.html";else st2=INI("dirAGK")+"Help\\menu.htm";
  ShellExecute(Handle,"open",st2.c_str(),NULL,NULL,SW_SHOW);return;}}catch(...){}break;
  //case VK_F11:Caption=IntToStr(NumCtrlCode(Memo1->Lines->Strings[0]));
  }
// ly=CursorY();
 if(Key==VK_BACK&&butkeyFlg){
  if((a=butStr.Length())<2){butkeyFlg=0;butStr="";}
  else butStr=butStr.SubString(1,a-1);
  refreshButStr();
  }
 else if(Key!=VK_SHIFT&&(Key<'A'||Key>'Z')){
  butkeyReset();
  }
 SetMenuCol();
 StatusBar1->SimpleText="";

// StatusBar1->SimpleText=butStr+":"+IntToStr(butkeyFlg);
}
void __fastcall TFrmMeg1::butkeyReset(void){
 int i;
 butkeyFlg=0;
 for(i=0;i<BTNWX;i++)BtnKey[i+BTNWX*3]->Caption="";
}

//----- KeyUp and modify MenuCol
void __fastcall TFrmMeg1::Memo1KeyUp(TObject *Sender, WORD &Key,TShiftState Shift){
int i,a,aa;AnsiString ty,st;
SetMenuCol();

if(Shift.Contains(ssAlt)||Key==VK_MENU)isAlt=false;
if(Key==VK_MENU&&tb_in){tb_in=0;tb_cnt=0;Memo1->SelStart+=Memo1->SelLength;}

if(Key==VK_RETURN&&INI("AutoIndent")=="1"){
 a=CursorY();//Caption=IntToStr(ly)+":"+IntToStr(a);
 if(ly==a-1){
  ty=Memo1->Lines->Strings[ly];
  st="";i=1; if(ty.Length()>0){while(ty.Length()>=i&&(unsigned char)ty[i]<33){st=st+ty[i];++i;}}
  if(i>1){aa=Memo1->SelStart;
   Memo1->Lines->Strings[a]=st+Memo1->Lines->Strings[a];
   Memo1->SelStart=aa+i-1;Memo1->SelLength=0;
   }}ly=-1;}
 //ly=-1;lyf=false;
}
//--- Click
void __fastcall TFrmMeg1::Memo1Click(TObject *Sender)
{SetMenuCol();}
//---------------------------------------------------------------------------
// Windows-Messages
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::WMDROPFILES(TWMDropFiles Msg){
 char buf[256];//int ctrl;
 AnsiString fn,ext,bu;
 int cnt=::DragQueryFile((HDROP)Msg.Drop,0xFFFFFFFF,NULL,0);
 for(int i=0;i<cnt;i++){
  ::DragQueryFile((HDROP)Msg.Drop,i,buf,sizeof(buf));
  fn=StrPas(buf);
  if(FileExists(fn)){/*ext=ExtractFileExt(fn).LowerCase();
   if(ext==".jpg"||ext==".gif"||ext==".png"){
    if(!FrmImage){FrmImage=new TFrmImage(Application);}
    FrmImage->LoadGra(fn);
    bu="<img src=\x22"+FrmImage->Edit1->Text+ExtractFileName(fn)+"\x22 width="+IntToStr(FrmImage->Image1->Width)+" height="+IntToStr(FrmImage->Image1->Height)+">";
    InsertText(bu);}
   else{*/
    AddNewText(fn);ix=true;LoadKnjText("");//}
   }}
 ::DragFinish((HDROP)Msg.Drop);}

//---------------------------------------------------------------------------
// Crypy
//---------------------------------------------------------------------------
const unsigned char pubKey[]={35,91,68,63,75,75,25,4,15,2,36,21,24,27,75,27,61,75,37,10,43,53,52,46,13,46,37,58,66,21,92,19,92,32,20,5,29,13,81,97,90,26,15,82,56,32,93,43,74,57,42,92,50,28,65,33,63,95,94,80,29,30,28,52,30,98,94,34,3,65,21,26,39,19,73,41,60,35,47,68,62,56,78,29,89,25,51,77,16,98,50,65,50,45,48,93,87,39,47,75,56,2,78,20,14,43,51,2,92,39,65,84,32,79,35,53,49,37,20,58,41,71,86,47,44,59,3,42};
AnsiString __fastcall TFrmMeg1::strEncrypt(AnsiString st,int a){
 int i,l=st.Length();unsigned char c;AnsiString rst="";
 for(i=1;i<=l;i++){c=(unsigned char)((st[i]^pubKey[a])+2);if(++a==128)a=0;
  if((c>=0x30&&c<=0x39)||(c>=0x41&&c<=0x5a)||(c>=0x62&&c<=0x7a)){
   rst=rst+(char)c;}
  else{rst=rst+'a'+(char)(0x41+c/16)+(char)(0x73-(c&15));}}return rst;}

AnsiString __fastcall TFrmMeg1::strDecrypt(AnsiString st,int a){
 int i,l=st.Length();unsigned char c;AnsiString rst="";
 for(i=1;i<=l;i++){if(st[i]=='a'&&i<l-1){c=((unsigned char)st[i+1]-0x41)*16+((0x73-(unsigned char)st[i+2])&15);i+=2;}else c=st[i];
  rst=rst+(char)((c-2)^pubKey[a]);
  if(++a==128)a=0;}return rst;}
/*WinExec(("explorer.exe \x22"+ExtractFilePath(li_file->Strings[index])+"\x22").c_str(),SW_SHOW);*/
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::N11Click(TObject *Sender)
{
 if(li_file->Strings[index].SubString(1,3)==NEWFILE)return;
 if(Application->MessageBox("Recover?","Recover",MB_YESNO)==ID_YES){
  ix=true;LoadKnjText(li_knj->Strings[index]);
  li_modify->Strings[index]="0";menuModify->Caption="";}
}
//---------------------------------------------------------------------------
//FTP
/*void __fastcall TFrmMeg1::Upload(AnsiString str,AnsiString sdir,AnsiString fi){
// AnsiString str=INI("FtpServer"+IntToStr(a));
 AnsiString chmod=F_CHMOD(str);
 sdir=(sdir=="")?F_SERVERDIR(str):sdir;
 TNMFTP *NMFTP1=new TNMFTP(FrmMeg1);
 NMFTP1->Host=F_HOST(str);
 NMFTP1->UserID=F_USER(str);
 NMFTP1->Password=FrmMeg1->strDecrypt(F_PASSWD(str),CKEY);
 NMFTP1->Passive=(F_PASSIVE(str)=="1")?true:false;
 try{isFtp=true;
  NMFTP1->Connect();
  if(sdir!="")NMFTP1->ChangeDir(sdir);
  NMFTP1->Mode(MODE_IMAGE);
  NMFTP1->Upload(fi, "");
  if(chmod!="")NMFTP1->DoCommand("SITE CHMOD "+chmod+" "+ExtractFileName(fi));
  NMFTP1->Disconnect();
}catch(Exception &e){Application->MessageBox(e.Message.c_str(),"FTPｴﾗｰ",MB_OK|MB_ICONERROR);}
 delete NMFTP1;
isFtp=false;
} */


void __fastcall TFrmMeg1::TabControl1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{RECT r;int i;
 if(Shift.Contains(ssRight)){
  for(i=0;i<TabControl1->Tabs->Count;i++){
  TabControl1->Perform(TCM_GETITEMRECT,i,(LPARAM)(&r));
  if(PtInRect(r,Point(X,Y))&&i!=TabControl1->TabIndex){TabControl1->TabIndex=i;ChangeText(i,true);return;}}}
 else TabControl1->BeginDrag(false);
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::TabControl1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 if(Sender->ClassNameIs("TTabControl"))Accept=true;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::TabControl1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{RECT r;int a,i;
 if(!Sender->ClassNameIs("TTabControl"))return;

 for(i=0;i<TabControl1->Tabs->Count;i++){
  TabControl1->Perform(TCM_GETITEMRECT,i,(LPARAM)(&r));
  if(PtInRect(r,Point(X,Y))){
   if(i!=TabControl1->TabIndex){
    a=TabControl1->TabIndex;
    TabControl1->Tabs->Move(a,i);
    li_id->Move(a,i);
    li_pos->Move(a,i);
    li_modify->Move(a,i);
    li_file->Move(a,i);
    li_knj->Move(a,i);
//    AnsiString st=txt[a]+"1";txt[a]=txt[i].Unique();txt[i]=st;
    TabControl1->TabIndex=i;index=i;return;}}}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::J1Click(TObject *Sender)
{
// FrmJump=new TFrmJump(Application);
// FrmJump->MakeList();
/* if(FrmJump->ShowModal()==mrOk){
//  Memo1->SelStart=Memo1->Lines->Text.Length();
//  Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,FrmJump->GetLineNo(),0);
 int a,a1,ln=FrmJump->GetLineNo();
  Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,ln,0);Memo1->SelLength=0;
  while((a=Memo1->Perform(EM_GETFIRSTVISIBLELINE,0,0))!=ln){
   if(a==a1)break;a1=a;Memo1->Perform(EM_LINESCROLL,0,1);}
  }
 FrmJump->Release();*/
// ShowMessage(INI("FuncJump"));return;
 if(INI("FuncJump")=="")return;
 lstMo=LST_FUNCJUMP;
 lstMakeList();
 lstInit();
 }
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::mnKouhoClick(TObject *Sender)
{
 AnsiString st="",st2;char c;
 int a=Memo1->SelStart;
 lstMo=LST_KOUHO;
 while(a>0&&(((c=Memo1->Lines->Text[a])>47&&c!=':'&&c!=';'&&c!='<'&&c!='='&&c!='>'&&c!='?'&&c!='{'&&c!='|'&&c!='}'&&c!='~')
 //c!='$'&&c!='&'&&c!='\''&&c!='('&&c!=')'&&c!='*'&&c!='+'&&c!=','&&c!='='&&c!='|'&&c!='"')
 ||c<0||c=='.')
 /*(((c=Memo1->Lines->Text[a])>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z')||c<0)*/){st2=c;st=st2+st;--a;}
 if(st!=""){
//  FrmJump=new TFrmJump(Application);
  lstMakeKouho(st);koho_len=st.Length();kohoStart=a;kohoStr=st;
  if(ListBox1->Items->Count==1){
   ListBox1->ItemIndex=0;WORD Key=VK_RETURN;TShiftState s;
   ListBox1KeyDown(Sender,Key,s);}
  else lstInit();
  }
/* if(FrmJump->ShowModal()==mrOk&&(a=FrmJump->ListBox1->ItemIndex)!=-1){
  st2=FrmJump->ListBox1->Items->Strings[a];
  st2.Delete(1,st.Length());
  if((a=st2.AnsiPos(","))!=0)st2.Delete(a,st2.Length()-a+1);
  Memo1->SelText=st2;}
  INI("ListBoxW2")=FrmJump->ClientWidth;
  INI("ListBoxH2")=FrmJump->ClientHeight;
  FrmJump->Release();}*/
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::lstInit(void){
//li_no=new TStringList();
int y=StrToInt(INI("ListBoxY"));
int x=StrToInt(INI("ListBoxX"));
//int h=StrToInt(INI("ListBoxH"));
int w=StrToInt(INI("ListBoxW"));
ListBox1->Left=x+/*FrmMeg1->Left+x+*/CursorX()*w;
ListBox1->Top=y+/*FrmMeg1->Top+y+*/(CursorY()-Memo1->Perform(EM_GETFIRSTVISIBLELINE,0,0))*(-Memo1->Font->Height);
ListBox1->Color=Memo1->Color;
ListBox1->Font=Memo1->Font;
ListBox1->Font->Size=StrToInt(INI("ListBoxFontSize"));
ListBox1->Width=StrToInt(INI("ListBoxW2"));
ListBox1->Height=StrToInt(INI("ListBoxH2"));
if(ListBox1->Left>Memo1->Width-ListBox1->Width)ListBox1->Left=Memo1->Width-ListBox1->Width;
if(ListBox1->Top>Memo1->Height-ListBox1->Height)ListBox1->Top=Memo1->Height-ListBox1->Height;

//ListBox1->Font->Color=Memo1->Font->Color;
ListBox1->Visible=true;ListBox1->SetFocus();
if(ListBox1->Items->Count>0)ListBox1->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::lstMakeList(void){
 int i,j,a,cnt;AnsiString st,st2;
 TStringList *li=new TStringList();
 li_no->Clear(); ListBox1->Clear();
 st=INI("FuncJump");a=0;
 while((st2=GetSplit(a,st))!=""){li->Add(st2);++a;}
 cnt=li->Count;

 for(i=0;i<Memo1->Lines->Count;i++){
  st=Memo1->Lines->Strings[i];
  for(j=0;j<cnt;j++){
  if(st.Pos(li->Strings[j])==1){//Perl func
   st.Delete(1,li->Strings[j].Length()+1);
   if((a=st.Pos("{"))!=0){st.Delete(a,st.Length()-a+1);}
   if((a=st.Pos("("))!=0){st.Delete(a,st.Length()-a+1);}
   ListBox1->Items->Add(st);
   li_no->Add(IntToStr(i));j=cnt;}}}
 delete li;
}

void __fastcall TFrmMeg1::lstMakeKouho(AnsiString st){
 int i;AnsiString st2;
// Caption="候補";
 ListBox1->Clear();st=st.LowerCase();
 for(i=0;i<FrmMeg1->li_kouho->Count;i++){
  st2=FrmMeg1->li_kouho->Strings[i];
  if(st2.LowerCase().Pos(st)==1){
   ListBox1->Items->Add(st2);}}
}

/*int __fastcall TFrmMeg1::lstGetLineNo(void){
 int a=ListBox1->ItemIndex;
 if(a==-1)return 0;
 return StrToInt(li_no->Strings[a]);}*/

void __fastcall TFrmMeg1::ListBox1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{bool psAlt=Shift.Contains(ssAlt),psShift=Shift.Contains(ssShift);
 AnsiString st2;int a,a1,ln;
 switch(Key){
  case VK_RETURN:if((a=ListBox1->ItemIndex)!=-1){
//   AnsiString st=ListBox1->Items->Strings[a];
   switch(lstMo){
    case LST_KOUHO://--------- 候補の結果
     st2=ListBox1->Items->Strings[a];
     StatusBar1->SimpleText=st2;
     // 決定単語が入力済み単語と異なる
     if(st2.Pos(kohoStr)!=1){Memo1->SelStart=kohoStart;Memo1->SelLength=koho_len;}
     else st2.Delete(1,koho_len);// 一致する場合は残りを出力
     if((a=st2.AnsiPos(","))!=0)st2.Delete(a,st2.Length()-a+1);
     Memo1->SelText=st2;break;
    case LST_FUNCJUMP://---------- 関数移動の結果
     ln=StrToInt(li_no->Strings[a]);
     Memo1->SelStart=Memo1->Perform(EM_LINEINDEX,ln,0);Memo1->SelLength=0;
     a1=-1;while((a=Memo1->Perform(EM_GETFIRSTVISIBLELINE,0,0))!=ln){
     if(a==a1)break;a1=a;Memo1->Perform(EM_LINESCROLL,0,1);}break;}}
  INI("ListBoxW2")=ListBox1->Width; INI("ListBoxH2")=ListBox1->Height;
  case VK_ESCAPE:ListBox1->Visible=false;Memo1->SetFocus();break;
  case VK_UP:if(psAlt){if(psShift)ListBox1->Height-=2;else --ListBox1->Top;}break;
  case VK_RIGHT:if(psAlt){if(psShift)ListBox1->Width+=2;else ++ListBox1->Left;}break;
  case VK_DOWN:if(psAlt){if(psShift)ListBox1->Height+=2;else ++ListBox1->Top;}break;
  case VK_LEFT:if(psAlt){if(psShift)ListBox1->Width-=2;else --ListBox1->Left;}break;
//  case VK_F12:INI("ListBoxX")=ListBox1->Left;INI("ListBoxY")=ListBox1->Top;
//   Application->MessageBox("0,0の位置を設定","ListBox",MB_OK);break;
//  break;
  case VK_F11:INI("ListBoxW")=ListBox1->Left-StrToInt(INI("ListBoxX"));//INI("ListBoxH")=ListBox1->Top-StrToInt(INI("ListBoxY"));
   Application->MessageBox("Set font width.","ListBox",MB_OK);break;
}}

void __fastcall TFrmMeg1::ListBox1Exit(TObject *Sender)
{ListBox1->Visible=false;}

void __fastcall TFrmMeg1::ListBox1Click(TObject *Sender)
{
int a;
 if((a=ListBox1->ItemIndex)!=-1){
  StatusBar1->SimpleText=ListBox1->Items->Strings[a];
}}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::mnKukeiCopyClick(TObject *Sender)
{int i,toX,toY;AnsiString st;
 if(kukeiCopy==0){
  kukeiCopyX=CursorX();
  kukeiCopyY=CursorY();
//  mnKukeiCopy->Caption="どこまで?";
  kukeiCopy=1;//kukeiCopyMod=menuModify->Caption;
  menuCol->Caption="["+IntToStr(kukeiCopyY+1)+","+IntToStr(kukeiCopyX+1)+"]";
 }else{toX=CursorX();toY=CursorY();st="";
  for(i=kukeiCopyY;i<=toY;i++){if(i!=kukeiCopyY)st=st+"\xd\xa";
   st=st+Memo1->Lines->Strings[i].SubString(kukeiCopyX+1,toX-kukeiCopyX);}
  Clipboard()->AsText=st;
  kukeiCopy=0;menuCol->Caption=IntToStr(toY+1)+":"+IntToStr(toX+1);
  //mnKukeiCopy->Caption="矩形ｺﾋﾟｰ";
  }
}
//---------------------------------------------------------------------------
#define notZenkaku(a) (a<0x80||(a>=0xa0&&a<0xe0))

void __fastcall TFrmMeg1::mnTojikigoClick(TObject *Sender)
{unsigned char mo,c,c1,cs,ce;int i,dp,a=Memo1->SelStart+1;
 c=Memo1->Lines->Text[a];mo=0;
 if(c=='{'){ce='}';}
 else if(c=='('){ce=')';}
 else if(c=='['){ce=']';}
 else if(c=='}'){ce='{';mo=1;}
 else if(c==')'){ce='(';mo=1;}
 else if(c==']'){ce='[';mo=1;}
 else{/*Application->MessageBox("括弧","閉じ括弧",MB_OK);*/return;}
 dp=0;c1=0;
 if(mo==0){
  for(i=a+1;i<=Memo1->Lines->Text.Length();i++){
   cs=Memo1->Lines->Text[i];
   if(cs==c&&notZenkaku(c1))++dp;
   if(cs==ce&&notZenkaku(c1)){if(dp==0){Memo1->SelStart=i-1;Memo1->SelLength=1;return;}else --dp;
   }c1=cs;}}
 else{
  for(i=a-1;i>1;i--){
   cs=Memo1->Lines->Text[i];c1=Memo1->Lines->Text[i-1];
   if(cs==c&&notZenkaku(c1))++dp;
   if(cs==ce&&notZenkaku(c1)){if(dp==0){Memo1->SelStart=i-1;Memo1->SelLength=1;return;}else --dp;
   }}}
 Application->MessageBox("not found","Close",MB_OK);
}
//---------------------------------------------------------------------------



void __fastcall TFrmMeg1::mnTextPerlClick(TObject *Sender)
{
 FrmPerl->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::ListFiles(AnsiString dirName,TMenuItem *OyaItem){
int RC,p;
TSearchRec SearchRec;
TMenuItem *KoItem;
AnsiString ss;
RC=FindFirst(dirName+"*.*",faAnyFile,SearchRec);
 while(RC==0){
  if(SearchRec.Name!=".."&&SearchRec.Name!="."){
   ss=dirName+SearchRec.Name;
   if((SearchRec.Attr&faDirectory)==0)AddTempItem(ss,OyaItem);
   if((SearchRec.Attr&faDirectory)>0){
    KoItem=new TMenuItem(OyaItem);
    KoItem->Caption=SearchRec.Name;
    if(OyaItem==mnTag)OyaItem->Insert(mnTagIdx++,KoItem);
    else OyaItem->Add(KoItem);
    ListFiles(ss+"\\",KoItem);}}
   RC=FindNext(SearchRec);}
 FindClose(SearchRec);
}
//---------------------------- AddTempItem
void __fastcall TFrmMeg1::AddTempItem(AnsiString st,TMenuItem *OyaItem){
 TMenuItem *NewItem;
 NewItem=new TMenuItem(OyaItem);
 NewItem->Caption=ExtractFileName(st);
 NewItem->OnClick=LoadTemp;
 NewItem->Tag=li_temp->Count;
 if(OyaItem==mnTag)OyaItem->Insert(mnTagIdx++,NewItem);else OyaItem->Add(NewItem);
 li_temp->Add(st);}
//------------------
// RefreshTemp
void __fastcall TFrmMeg1::RefreshTemp(void){
 int a,i;
// TMenuItem *ToItem; // goﾒﾆｭｰ
 li_temp->Clear();
 AnsiString st;
 a=mnTag->Count-7;for(i=0;i<a;i++){mnTag->Delete(0);}
 mnTagIdx=0;
 ListFiles(FrmMeg1->di_megpas+"template\\",mnTag);

 TMenuItem *NewItem;
 NewItem=new TMenuItem(mnTag);
 NewItem->Caption="<Update>";
 NewItem->OnClick=UpdateTemp;
 mnTag->Insert(mnTagIdx,NewItem);}

void __fastcall TFrmMeg1::LoadTemp(TObject *Sender){
 TStringList *li_buf=new TStringList();
 li_buf->LoadFromFile(li_temp->Strings[((TMenuItem *)Sender)->Tag]);
 AnsiString st=li_buf->Text;int i=st.Length();
 while(i>0&&st[i]>=0&&st[i]<32){st.Delete(i,1);--i;}
 Memo1->SelText=st;Modify();
 delete li_buf;}

void __fastcall TFrmMeg1::UpdateTemp(TObject *Sender){RefreshTemp();}

void __fastcall TFrmMeg1::refreshButStr(void){
 int a,n=0,i;AnsiString buf;
 for(i=0;i<li_butkey->Count;i++){
  buf=li_butkey->Strings[i];
  if((a=buf.AnsiPos(","))!=0)buf.Delete(a,buf.Length()-a+1);
  if(buf.LowerCase().AnsiPos(butStr.LowerCase())==1&&n<BTNWX){
   BtnKey[BTNWX*3+n]->Tag=i;
   BtnKey[BTNWX*3+n]->Caption=buf;++n;}}
 while(n!=BTNWX){BtnKey[BTNWX*3+n]->Caption="";++n;}}

void __fastcall TFrmMeg1::Memo1KeyPress(TObject *Sender, char &Key)
{
 if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')){
  if(butkeyFlg==0)butStr="";
  butkeyFlg=1;
  butStr=butStr+((char)Key);
  refreshButStr();
//  Application->MessageBox(butStr.c_str(),"info",MB_OK);
    }
  else if(Key!=8){butkeyFlg=0;}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::ButKey1Click(TObject *Sender){
 AnsiString st=((TButton*)Sender)->Caption;
// ((TButton*)Sender)->Color=clHighlight;
 if(st=="^^"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_UP,1);}
 else if(st=="->"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_RIGHT,1);}
 else if(st=="vv"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_DOWN,1);}
 else if(st=="<-"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_LEFT,1);}
 else if(st=="<|"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_HOME,1);}
 else if(st=="|>"){SendMessage(Memo1->Handle,WM_KEYDOWN,VK_END,1);}
 else{
  if(st=="&&")st="&";
  Memo1->SelText=st;}
 Memo1->SetFocus();
 butkeyReset();
}

void __fastcall TFrmMeg1::ButKey2Click(TObject *Sender){
 Memo1->SetFocus();
 if(((TButton*)Sender)->Caption==""){
  MENUCLKED;
  mnKouhoClick(Sender);
  return;}
 Memo1->SelStart=Memo1->SelStart-butStr.Length();
 Memo1->SelLength=butStr.Length();
 Memo1->SelText=((TButton*)Sender)->Caption;//+" ";
 AnsiString st=li_butkey->Strings[((TButton*)Sender)->Tag];int i;
 for(i=st.Length();i>1&&st[i]!=',';i--);
 StatusBar1->SimpleText=st.SubString(1,i-1);
 butkeyReset();
}


/* switch( ((TButton*)Sender)->Tag){
  case 0: SendMessage(Memo1->Handle,WM_KEYDOWN,VK_UP,1);break;
  case 1: SendMessage(Memo1->Handle,WM_KEYDOWN,VK_RIGHT,1);break;
  case 2: SendMessage(Memo1->Handle,WM_KEYDOWN,VK_DOWN,1);break;
  case 3: SendMessage(Memo1->Handle,WM_KEYDOWN,VK_LEFT,1);break;
//  case 1:Memo1->SelStart=Memo1->SelStart+1;break;
//  case 3:Memo1->SelStart=Memo1->SelStart-1;break;
}
 Memo1->SetFocus();
 butkeyFlg=0;*/
HWND FindWind(AnsiString ch){
 char gbuf[256];
 HWND CurrWnd=GetWindow(FrmMeg1->Handle,GW_HWNDFIRST);
 while(CurrWnd){
  GetWindowText(CurrWnd,gbuf,256);
  if(AnsiPos(ch,StrPas(gbuf)))return CurrWnd;
  CurrWnd=GetWindow(CurrWnd,GW_HWNDNEXT);}
 return 0;}

void __fastcall TFrmMeg1::btnHelp1Click(TObject *Sender)
{
/* int a;AnsiString st=Memo1->Lines->Text;
 AnsiString wa="";
 a=Memo1->SelStart;if(a>st.Length())return;
 while(a>0&&st[a]>='a'&&st[a]<='z'){--a;}++a;
 while(a<st.Length()+1&&st[a]>='a'&&st[a]<='z'){
  wa=wa+st[a];++a;}

 HWND han=FindWind("99 Basic Help");if(!han){
  WinExec(("winhelp32.exe "+INI("dirQqbas")+"\\QQBASIC.HLP").c_str(),SW_SHOW);}
// ShowMessage("["+wa+"]");
// unsigned long ad=st.c_str();
// unsigned long *d;d=(unsigned long*)wa.c_str();
 WinHelp(han,(INI("dirQqbas")+"\\QQBASIC.HLP").c_str(),HELP_KEY,(unsigned long)wa.c_str());
Memo1->SetFocus();*/
AnsiString ext=ExtractFileExt(li_file->Strings[index]);
if(ext==".g"||ext==".g2"){
 TShiftState Shift;short Key=VK_F1;
 Memo1KeyDown(Sender,Key,Shift);}
else mnHelpClick(Sender);
}
//---------------------------------------------------------------------------
/*
 //--------- ﾌｫﾙﾀﾞ選択
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );
 BI.hwndOwner = Handle;                     // オーナーウィンドウのハンドル
 BI.pidlRoot = NULL;                        // ルートフォルダのIDリスト
 BI.pszDisplayName = FName;                 // 選択フォルダのパス
 BI.lpszTitle = "99 Basicのフォルダ設定";   // 表示文字
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // フォルダのみ選択
 BI.lpfn = NULL;                            // コールバック関数
 BI.lParam = 0;                             // コールバック関数に渡される値
 BI.iImage = 0;                             // 選択フォルダのイメージリストインデックス
 ItemID = SHBrowseForFolder( &BI );
 SHGetPathFromIDList( ItemID, DirPath );
 GlobalFreePtr( ItemID );
 if(DirPath[0]!=0)INI("dirQqbas")=StrPas(DirPath)+"\\";

 OpenDialog1->Filter="fpc.exe|fpc.exe";
 OpenDialog1->FileName="fpc.exe";
 if(OpenDialog1->Execute()){
  INI("Extbas")=OpenDialog1->FileName+" \x22%f\x22 "+INI("dirQqbas")+" %g";
 }
*/

// MENUCLKED;
// WinExec((di_megpas+"msdgen\\msdgen.exe \x22"+ExtractFilePath(li_file->Strings[index])+"bmp\x22 1 3").c_str(),SW_SHOW);


void __fastcall TFrmMeg1::mnPasteClick(TObject *Sender)
{
 MENUCLKED;Memo1->PasteFromClipboard();releaseShift();
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::mnCopyClick(TObject *Sender)
{
 MENUCLKED;Memo1->CopyToClipboard();releaseShift(); SetStatus("Copy");

}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::mnCutClick(TObject *Sender)
{
 MENUCLKED;Memo1->CutToClipboard();releaseShift(); SetStatus("Cut");
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::releaseShift(void){
 if(isShift){isShift=false;
 btnShift->Font->Style=TFontStyles();
 keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),KEYEVENTF_KEYUP,0);}}
void __fastcall TFrmMeg1::btnShiftClick(TObject *Sender)
{
 Memo1->SetFocus();
 if(!isShift){isShift=true;
  btnShift->Font->Style=TFontStyles()<<fsBold;
  keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),0,0);}
 else{releaseShift();}
}
//---------------------------------------------------------------------------
/*// c:\projects\fpcx\fpcx.exe "%f" c:\apps\rumsx\editdisk.exe c:\apps\bluemsx\bluemsx.exe %g
 AnsiString fi_fpcx,fi_editdisk,fi_bluemsx;

 OpenDialog1->Title="Setup 1-3: Select editdisk.exe";
 OpenDialog1->Filter="editdisk.exe|editdisk.exe";
 OpenDialog1->FileName="editdisk.exe";
 if(OpenDialog1->Execute()){fi_editdisk=OpenDialog1->FileName;}else return;

 OpenDialog1->Title="Setup 2-3: Select blueMSX.exe";
 OpenDialog1->Filter="blueMSX.exe|blueMSX.exe";
 OpenDialog1->FileName="blueMSX.exe";
 if(OpenDialog1->Execute()){fi_bluemsx=OpenDialog1->FileName;}else return;

 fi_fpcx=di_megpas+"fpcx\\fpcx.exe";
 if(!FileExists(fi_fpcx)){
  OpenDialog1->Title="Setup 3-3: Select fpcx.exe";
  OpenDialog1->Filter="fpcx.exe|fpcx.exe";
  OpenDialog1->FileName="fpcx.exe";
  OpenDialog1->InitialDir=di_megpas+"fpcx";
 if(OpenDialog1->Execute()){fi_fpcx=OpenDialog1->FileName;}else return;}

 INI("Extbas")=fi_fpcx+" \x22%f\x22 \x22"+fi_editdisk+"\x22 \x22"+fi_bluemsx+"\x22 %g";
 INI("CmdCtrlF1")=fi_fpcx+" view %g";
 mnCtrlF1->Caption=GetMenuText("CmdCtrlF1");
 OpenDialog1->Title="";
 OpenDialog1->FileName="";
*/


void __fastcall TFrmMeg1::SpriteEditor1Click(TObject *Sender)
{
 MENUCLKED;
 if(INI("wl")=="cpc")WinExec((ExtractFilePath(INI("Ccz80p"))+"..\\library\\cpc\\GameUtils\\utils\\SpriteEditorCPC.exe").c_str(),SW_SHOW);
 else WinExec((di_megpas+"tabrenchx\\tabrench.exe "+IntToStr(((TMenuItem*)Sender)->Tag)).c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::GraphicEditorClick(TObject *Sender)
{
 MENUCLKED;
 WinExec((di_megpas+"tabrench\\tabreng.exe").c_str(),SW_SHOW);
}

//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::PaletteEditor1Click(TObject *Sender)
{
 MENUCLKED;
 WinExec((di_megpas+"palette\\palette.exe").c_str(),SW_SHOW);
}

//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::SpriteDataGenerator1Click(TObject *Sender)
{
 MENUCLKED;
 AnsiString x=(((TMenuItem*)Sender)->Tag!=3)?"x":"";
 AnsiString fi=ExtractFileExt(li_file->Strings[index]).LowerCase();
 fi=(fi.AnsiPos(".ccz80"))?"2":"1";
 WinExec((di_megpas+"msdgen\\msdgen.exe \x22"+di_megpas+"tabrench"+x+"\\bmp\x22 "+IntToStr(((TMenuItem*)Sender)->Tag)+" "+fi).c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::MSXoption1Click(TObject *Sender)
{
 AnsiString fi_editdisk="none";
 if(INI("Ccz80GenBas")!=""){
  frmMsx->edtDiskExplorer->Text=INI("DiskExplorer");
  frmMsx->edtMsxEmu->Text=INI("MSXEmulator");
  frmMsx->edtCcz80->Text=INI("Ccz80");
  frmMsx->edtCcz80p->Text=INI("Ccz80p");
  frmMsx->edtMgsPlayer->Text=INI("MgsPlayer");
  frmMsx->chkMakeLoader->Checked=(INI("Ccz80GenBas")=="1")?true:false;
  frmMsx->edtLoaderScript->Text=INI("Ccz80Loader");
  frmMsx->edtIncludePath->Text=INI("Ccz80Include");
  frmMsx->edtOrgAddress->Text=INI("Ccz80Org");
  frmMsx->edtMachine->Text=INI("Machine");
  frmMsx->edtDirAsDisk->Text=INI("DirAsDisk");
  frmMsx->chkExportRom->Checked=(INI("ExportRom")==1)?true:false;
  frmMsx->chkExportCom->Checked=(INI("ExportRom")==2)?true:false;
  if(INI("ExportRom")=="1"){
   frmMsx->chkExportRom->Checked=true;
   frmMsx->chkExportRomClick(Sender);}
  else if(INI("ExportRom")=="2"){
   frmMsx->chkExportCom->Checked=true;
   frmMsx->chkExportComClick(Sender);}
  else if(INI("ExportRom")=="3"){
   frmMsx->chkExportExbin->Checked=true;
   frmMsx->chkExportExbinClick(Sender);}
  else{frmMsx->chkExportBin->Checked=true;
   frmMsx->chkExportBinClick(Sender);}
  frmMsx->edtRomSize->Text=INI("RomSize");
  frmMsx->edtPath->Text=INI("Ccz80pPath");
  frmMsx->edtDataAddress->Text=INI("Ccz80Data");
  frmMsx->chkDragDsk->Checked=(INI("DragDsk")=="1")?true:false;
  }
 if(frmMsx->ShowModal()==mrOk){
  INI("DiskExplorer")=frmMsx->edtDiskExplorer->Text;
  INI("MSXEmulator")=frmMsx->edtMsxEmu->Text;
  INI("MgsPlayer")=frmMsx->edtMgsPlayer->Text;
  INI("Ccz80")=frmMsx->edtCcz80->Text;
  INI("Ccz80p")=frmMsx->edtCcz80p->Text;
  INI("Ccz80GenBas")=(frmMsx->chkMakeLoader->Checked)?"1":"0";
  INI("Ccz80Loader")=frmMsx->edtLoaderScript->Text;
  INI("Ccz80Include")=frmMsx->edtIncludePath->Text;
  INI("Ccz80Org")=frmMsx->edtOrgAddress->Text;
  INI("Machine")=frmMsx->edtMachine->Text;
  INI("DirAsDisk")=frmMsx->edtDirAsDisk->Text;
  if(INI("DiskExplorer")!=""){fi_editdisk=INI("DiskExplorer");}
  if(frmMsx->chkExportBin->Checked)INI("ExportRom")="0";
  else if(frmMsx->chkExportRom->Checked)INI("ExportRom")="1";
  else if(frmMsx->chkExportCom->Checked)INI("ExportRom")="2";
  else if(frmMsx->chkExportExbin->Checked)INI("ExportRom")="3";
//  INI("ExportRom")=(frmMsx->chkExportRom->Checked)?"1":"0";
  INI("RomSize")=frmMsx->edtRomSize->Text;
//  INI("ExportCom")=(frmMsx->chkExportCom->Checked)?"1":"0";
  INI("Ccz80pPath")=frmMsx->edtPath->Text;
  INI("Ccz80Data")=frmMsx->edtDataAddress->Text;
  INI("DragDsk")=(frmMsx->chkDragDsk->Checked)?"1":"0";

  AnsiString st=ExtractFileName(INI("MSXEmulator")).LowerCase();
  if(st.AnsiPos("openmsx")){INI("EmuKind")=EM_OPENMSX;INI("wl")="msx";
   INI("Extbas")=fi_fpcx+" \x22"+"infile=%f\x22 \x22"+"outdir="+INI("DirAsDisk")+"\x22 \x22"+"msxemu="+INI("MsxEmulator")+"\x22 \x22option="+INI("Machine")+"\x22 %g";
   }
  else if(st.AnsiPos("winape")){INI("EmuKind")=EM_WINAPE;INI("wl")="cpc";}
  else if(st.AnsiPos("pc-cpc")){INI("EmuKind")=EM_PCCPC;INI("wl")="cpc";}
  else{INI("EmuKind")=EM_BLUEMSX;INI("wl")="msx";
   INI("Extbas")=fi_fpcx+" \x22"+"infile=%f\x22 \x22"+"editdisk="+fi_editdisk+"\x22 \x22"+"msxemu="+INI("MsxEmulator")+"\x22 dragdsk="+INI("DragDsk")+" %g";
   }
  INI("Extccz80")=INI("Ccz80")+" \x22%f\x22 /org=#"+INI("Ccz80Org")+" /include=\x22%d;"+INI("Ccz80Include")+"\x22 /post=fpcx.bat";
  INI("Extccz80++")=INI("Ccz80p")+" \x22%f\x22 /org=#"+INI("Ccz80Org")+" /path=\x22%d;"+INI("Ccz80pPath")+"\x22 /msg=warning";
//  if(di_megpas.AnsiPos(" "))Application->MessageBox("Please put tabmegx.exe in the folder not including blanks for ccz80.","Caution",MB_OK);
//  INI("CmdCtrlF1")=fi_fpcx+" view=1 %g";
  //tgc
  INI("Extg")=di_megpas+"gobln\\gobln.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
  INI("Extg2")=di_megpas+"gobln\\gobln2.exe -g \x22%f\x22 -d \x22%B\x22 -r %g";
  reloadKouho();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::SourceASMorBAS1Click(TObject *Sender)
{MENUCLKED;
 HWND han;
 if(li_modify->Strings[index]=="1"&&!SaveText())return;
 AnsiString fi=li_file->Strings[index],ext=ExtractFileExt(fi).LowerCase();ext.Delete(1,1);
 bool isCcz80p=(ext=="ccz80++")?true:false;
 if(ext=="ccz80"||isCcz80p){
  han=FindWind("openMSX 0");
  if(han){PostMessage(han,WM_CLOSE,0,0);return;}
  TStringList *li_buf=new TStringList();
  if(isCcz80p)li_buf->Add("@echo off");
  AnsiString fi_comp=ChangeFileExt(fi,".asm");
  if(isCcz80p)DeleteFile(fi_comp);
  li_buf->Add("\x22"+fi_fpcx+"\x22 \x22infile="+fi_comp+"\x22 view=1");
  li_buf->SaveToFile(di_megpas+"fpcx.bat");
  CallExec(INI("Ext"+ext)+" "+((isCcz80p)?"/out=assembler":"/asm"),fi,"",false,isAlt);
  if(isCcz80p&&FileExists(fi_comp)){
   CallExec("fpcx.bat",fi,"",false,isAlt);}
  }
 else if(ext=="bas"){
  WinExec((fi_fpcx+" infile=\x22"+li_file->Strings[index]+"\x22 view=1").c_str(),SW_SHOW);}
 else if(ext=="g"){
  AnsiString f=INI("dirDB")+"TEMP\\FullSourceDump.dba";
  if(FileExists(f)){
   AddNewText(f);
   ix=true;
   LoadKnjText("");}}
 else if(ext=="g2"){
  AnsiString f=ExtractFilePath(fi)+"main.agc";
  if(FileExists(f)){
   AddNewText(f);
   ix=true;
   LoadKnjText("");}}
 else if(ext=="mus"){
  han=FindWind("Winamp 2.80");
  if(han){PostMessage(han,WM_CLOSE,0,0);return;}
  han=FindWind(" - Winamp");
  if(han){PostMessage(han,WM_CLOSE,0,0);return;}
  CallExec(INI("Extmus"),fi,"",false,isAlt);
  fi=ChangeFileExt(fi,".MGS");
  if(getFileSize(fi)){
   WinExec((INI("MgsPlayer")+" \x22"+fi+"\x22").c_str(),SW_SHOW);}
 }

}
//---------------------------------------------------------------------------
/*//--------- ﾌｫﾙﾀﾞ選択
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );

 BI.hwndOwner = Handle;                     // オーナーウィンドウのハンドル
 BI.pidlRoot = NULL;                        // ルートフォルダのIDリスト
 BI.pszDisplayName = FName;                 // 選択フォルダのパス
 BI.lpszTitle = "DarkBasic Pro or AGK";   // 表示文字
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // フォルダのみ選択
 BI.lpfn = NULL;                            // コールバック関数
 BI.lParam = 0;                             // コールバック関数に渡される値
 BI.iImage = 0;                             // 選択フォルダのイメージリストインデックス
 ItemID = SHBrowseForFolder( &BI );
 SHGetPathFromIDList( ItemID, DirPath );
 GlobalFreePtr( ItemID );
 if(DirPath[0]!=0)INI("dirDB")=StrPas(DirPath)+"\\";
 INI("Extg")=di_megpas+"gobln\\gobln.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
 INI("Extg2")=di_megpas+"gobln\\gobln2.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
// INI("Extg2")=di_megpas+"gobln.exe -g \x22%f\x22 -d \x22%d\x22";
*/
void __fastcall TFrmMeg1::gendbpro(AnsiString fi,bool isNew){
 AnsiString na=ExtractFileName(fi);
 na.Delete(na.AnsiPos("."),4);
 AnsiString di=ExtractFilePath(fi)+na;
 if(FileExists(di+".dbpro"))return;
 TStringList *li_buf=new TStringList();
 li_buf->LoadFromFile(di_megpas+"gobln\\mvtemp.dbpro");
 AnsiString st=li_buf->Text;
 strReplace(st,"mvtemp",na);
 li_buf->Text=st;
 li_buf->SaveToFile(di+".dbpro");
 if(isNew){
  CopyFile((di_megpas+"gobln\\mvtemp.g").c_str(),(di+".g").c_str(),false);
  AddNewText(di+".g");
  ix=true;
  LoadKnjText(di+".g");}}

//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::genagk(AnsiString fi,bool isNew){
 AnsiString na=ExtractFileName(fi);
 na.Delete(na.AnsiPos("."),4);
 AnsiString di=ExtractFilePath(fi)+na;
 AnsiString fi2=ChangeFileExt(fi,".agk");
 if(FileExists(fi2))return;
 TStringList *li_buf=new TStringList();
 li_buf->Add("[project]");
 li_buf->Add("description=");
 li_buf->Add("");
 li_buf->Add("[projectfiles]");
 li_buf->Add("FILE_0=main.agc;-1");
 li_buf->SaveToFile(fi2);
 if(isNew){
  CopyFile((di_megpas+"gobln\\mvtemp.g2").c_str(),(di+".g2").c_str(),false);
  AddNewText(di+".g2");
  ix=true;
  LoadKnjText(di+".g2");}
 }

void __fastcall TFrmMeg1::NewDB1Click(TObject *Sender)
{SaveDialog1->Filter="";
 SaveDialog1->FileName="";
 if(SaveDialog1->Execute()){gendbpro(SaveDialog1->FileName,true);}}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::NewAGK1Click(TObject *Sender)
{SaveDialog1->Filter="";
 SaveDialog1->FileName="";
 if(SaveDialog1->Execute()){genagk(SaveDialog1->FileName,true);}}

//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::copyy1Click(TObject *Sender)
{int i,l,a;AnsiString st,ost;
 a=Memo1->Perform(EM_LINEFROMCHAR,Memo1->SelStart,0);
 ost=Memo1->Lines->Strings[a];
 int sa=Memo1->SelStart;
 l=ost.Trim().Length();
 if(((TMenuItem*)Sender)->Tag==1){
  st=ost;
  strReplace(st,"x","z");
  strReplace(st,"X","Z");
  if(l<17){
   a=st.Length();if(a&&st[a]==':')st.Delete(a,1);
   Memo1->SelText=st.Trim();}else Memo1->Lines->Insert(a+1,st);}
 st=ost;
 strReplace(st,"x","y");strReplace(st,"Neyt","Next");
 strReplace(st,"X","Y");
 if(l<17){Memo1->SelStart=sa;
  if(!((TMenuItem*)Sender)->Tag){a=st.Length();if(a&&st[a]==':')st.Delete(a,1);}
  Memo1->SelText=st.Trim();
  SendMessage(Memo1->Handle,WM_KEYDOWN,VK_END,1);
  }
 else{Memo1->Lines->Insert(a+1,st);}

}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::btnDataClick(TObject *Sender)
{
 MENUCLKED;
 AnsiString fi=li_file->Strings[index],ext=ExtractFileExt(fi).LowerCase();
 if(ext==".g"){
  WinExec((di_megpas+"msdgen\\msdgen.exe \x22"+ExtractFilePath(li_file->Strings[index])+"bmp\x22 1 4").c_str(),SW_SHOW);}
 else if(ext==".g2"){
  WinExec((di_megpas+"msdgen\\msdgen.exe \x22"+ExtractFilePath(li_file->Strings[index])+"media\x22 1 4").c_str(),SW_SHOW);}
 else SpriteDataGenerator1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::Bin2Bas1Click(TObject *Sender)
{
 WinExec((di_megpas+"bin2bas\\bin2bas.exe").c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::ScreenEdit1Click(TObject *Sender)
{
 WinExec((di_megpas+"scredit\\scredit.exe").c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::mnSettargetClick(TObject *Sender)
{
 fi_ccz80ptarget=li_file->Strings[index];
 Application->MessageBox(fi_ccz80ptarget.c_str(),"Set target",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::mnClassClick(TObject *Sender)
{
 ShellExecute(Handle,"open",(di_megpas+"doc\\classes\\index.html").c_str(),"","", SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::reloadKouho(void){
 AnsiString wl;
 wl=INI("wl");
 if(wl==""){
  li_kouho->LoadFromFile(di_megpas+"kouho.ini");li_butkey->LoadFromFile(di_megpas+"butkey.ini");}
 else{
  if(wl=="msx"){mnWlMsx->Checked=true;}
  if(wl=="dbpro"){mnWlDbpro->Checked=true;}
  if(wl=="agk"){mnWlAgk->Checked=true;}
  if(wl=="cpc"){mnWlCpc->Checked=true;}
  li_kouho->LoadFromFile(di_megpas+"wordlists\\"+wl+"_kouho.ini");
  li_butkey->LoadFromFile(di_megpas+"wordlists\\"+wl+"_butkey.ini");}
  //Application->MessageBox("kouho reloaded","!",MB_OK);
}

void __fastcall TFrmMeg1::mnWlMsxClick(TObject *Sender)
{AnsiString wls[]={"msx","dbpro","agk","cpc"};
 //((TMenuItem*)Sender)->Checked=true;
 AnsiString wl=wls[((TMenuItem*)Sender)->Tag];
 INI("wl")=wls[((TMenuItem*)Sender)->Tag];
 reloadKouho();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::refreshTopButtons(void){
 if(INI("TopButtons")=="0"){
  popHidetopbuttons->Checked=true;
  PnlTop->Height=0;
  }
 else{
  popHidetopbuttons->Checked=false;
  PnlTop->Height=40;}
}

void __fastcall TFrmMeg1::popHidetopbuttonsClick(TObject *Sender)
{
 if(INI("TopButtons")=="1"||INI("TopButtons")==""){
  INI("TopButtons")="0";}
 else{INI("TopButtons")="1";}
 refreshTopButtons();
 FormResize(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::HextobitbusterHex1Click(TObject *Sender)
{
 WinExec((di_megpas+"msdgen\\hext2bb.exe").c_str(),SW_SHOW);

}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::DarkBasicsetting1Click(TObject *Sender)
{
  frmDb->edtDbproDir->Text=INI("dirDB");
  frmDb->edtAgkDir->Text=INI("dirAGK");
 if(frmDb->ShowModal()==mrOk){
  INI("dirDB")=frmDb->edtDbproDir->Text;
  INI("dirAGK")=frmDb->edtAgkDir->Text;}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::mnDiskManagerClick(TObject *Sender)
{
 AnsiString opt=(INI("DiskExplorer").AnsiPos("editdisk"))?" /S":"";

 WinExec((INI("DiskExplorer")+" \x22"+di_megpas+"\\fpcx\\fpcx.dsk\x22"+opt).c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::mnMmlHelpClick(TObject *Sender)
{
 ShellExecute(Handle,"open",(di_megpas+"doc\\mml\\index.html").c_str(),"","", SW_SHOW);

}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::SoundEditor1Click(TObject *Sender)
{
 MENUCLKED;
 WinExec((di_megpas+"mgsc\\seedit.exe").c_str(),SW_SHOW);

}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::BinaryConcat1Click(TObject *Sender)
{
 WinExec((di_megpas+"bin2bas\\binconct.exe").c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::Bin2Hex1Click(TObject *Sender)
{int b=1,i,n=0;
 AnsiString st=Memo1->SelText.Trim();
 for(i=1;i<=st.Length();i++){
  if(i>1)n*=2;
  if(st[i]=='1')++n;}
 Memo1->SelLength=0;Memo1->SelText=IntToStr(n)+"//";
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::Paste11Click(TObject *Sender)
{
int i;char rt=2,c;
 AnsiString st=Clipboard()->AsText;
 for(i=1;i<=st.Length();i++){
  if(rt){--rt;continue;}
  c=st[i];
  if(c>='c'&&c<='e'){c+=2;st[i]=c;}
  else if(c=='f'){st[i]='a';}
  else if(c=='g'){st[i]='b';}
  else if(c=='a'){st[i]='>';st.Insert("c<",i);i+=2;}//st[i]='>';
  else if(c=='b'){st[i]='>';st.Insert("d<",i);i+=2;}//st[i]='>';
  else if(c>0&&c<32)rt=2;}
 Memo1->SelText=st;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::Undo1Click(TObject *Sender)
{
if(Memo1->CanUndo)Memo1->Undo();        
}
//---------------------------------------------------------------------------

void __fastcall TFrmMeg1::Pastenolf1Click(TObject *Sender)
{
int i,rt=0;char c;
 AnsiString st=Clipboard()->AsText;
 strReplace(st,"\xa","");
 strReplace(st,"\xd","");
 strReplace(st," ","");
 for(i=1;i<st.Length();i++){
  c=st[i];if(i%1000>990&&rt==i/1000&&c==','){++rt;
  st=st.Insert("\xd\xa",i);}}
 Memo1->SelText=st;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMeg1::CPCclass1Click(TObject *Sender){
ShellExecute(Handle,"open",(ExtractFilePath(INI("Ccz80p"))+"..\\library\\cpc\\GameUtils\\doc\\Game Utils para Amstrad CPC - EN.pdf").c_str(),"","",SW_SHOW);
}
//---------------------------------------------------------------------------

