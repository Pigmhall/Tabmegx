//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#define SE(X) li_se->Values[X]
#include "seedit1.h"
#include "sedata.h"
#include "vcl\clipbrd.hpp"
#include "sese.h"
#define TITCAP "Sound Editor"
#define TITCAP2 "Sound Editor - "
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSe *frmSe;
TStringList *li_se,*li_split;
char *gbuf;
//---------------------------------------------------------------------------
__fastcall TfrmSe::TfrmSe(TComponent* Owner)
        : TForm(Owner)
{gbuf=new char[10000];
 li_se=new TStringList();
 li_split=new TStringList();
 isMod=false;
}
void __fastcall TfrmSe::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(isMod){
  int a=Application->MessageBox("Save?","Confirm",MB_YESNOCANCEL);
  if(a==ID_YES){
   if(!SaveFile(false))Action=caNone;}
  else if(a==ID_CANCEL){Action=caNone;}}
// delete gbuf;
}

void __fastcall TfrmSe::Mod(bool a){
 if(a){isMod=true;mnMod->Caption="*";}
 else{isMod=false;mnMod->Caption="";}
 }

//---------------------------------------------------------------------------
//--- Split(‹æØ‚ç‚ê‚½•¶Žš—ñ,‹æØ‚è•¶Žš) li_split‚ÉŒ‹‰Ê
void __fastcall TfrmSe::Split(AnsiString txt,char c){
 char *p,*q,buf[128];
 StrPCopy(gbuf,txt);
 li_split->Clear();
 p=gbuf;q=buf;
 while(*p){
  if(*p==c){*q=0;li_split->Add(buf);q=buf;}
  else{*(q++)=*p;}++p;}
 *q=0;li_split->Add(buf);}

//---- add channel
void __fastcall TfrmSe::AddChannel(int c){
 AnsiString hd="se"+IntToStr(c);
 int cnt=1;
 while(SE(hd+"ch"+IntToStr(cnt)+"Delay")!="")++cnt;
 if(cnt==2){Application->MessageBox("Can't make any more.","SE edit",MB_ICONINFORMATION);return;}
 hd=hd+"ch"+IntToStr(cnt);
 SE(hd+"Delay")=0;
 SE(hd+"Noise")="0";
 lbChannel->Items->Add("Channel "+IntToStr(cnt));
 lbChannel->ItemIndex=cnt-1;
 lbData->Clear();
}

//----
void __fastcall TfrmSe::btnSeAddClick(TObject *Sender)
{int cnt=1;
 while(SE("se"+IntToStr(cnt)+"Name")!="")++cnt;
 AnsiString scnt=IntToStr(cnt);
 SE("se"+scnt+"Name")="Sound";
 lbSe->Items->Add(scnt+" Sound");
 lbSe->ItemIndex=cnt-1;
 lbChannel->Clear();
 lbData->Clear();
 AddChannel(cnt);
 Mod(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::btnDataAddClick(TObject *Sender)
{int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 if(s==-1||c==-1){Application->MessageBox("Select the target sound","Add data",MB_ICONERROR);return;}
 frmData->cmbType->ItemIndex=0;
 frmData->setFormFromData("volm",-5000,0,0);
 if(frmData->ShowModal()==mrOk){
  AnsiString na="se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data";
  AnsiString va=SE(na);
  if(va!=""){va=va+"|";}
  SE(na)=va+frmData->getValueStr();RefreshDataList();
  Mod(true);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::RefreshDataList(void){
 lbData->Clear();
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 if(s==-1||c==-1)return;
 AnsiString st=SE("se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data");
 if(st=="")return;
 Split(st,'|');
 int i;
 for(i=0;i<li_split->Count;i++){
  AnsiString st=li_split->Strings[i];
  lbData->Items->Add(IntToStr(i+1)+":"+frmData->codeToName(st.SubString(1,4))+" "+st.SubString(6,st.Length()-5));}
}

//----
void __fastcall TfrmSe::RefreshChannelList(void){
 int cnt=1;
 lbChannel->Clear();
 int s=lbSe->ItemIndex;
 while(SE("se"+IntToStr(s+1)+"ch"+IntToStr(cnt)+"Delay")!=""){
  lbChannel->Items->Add("Channel "+IntToStr(cnt));
  if(cnt==1)lbChannel->ItemIndex=0;
  ++cnt;}
 if(cnt>0)RefreshDataList();
 }

//---
void __fastcall TfrmSe::btnDataPropertyClick(TObject *Sender)
{
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 int d=lbData->ItemIndex;
 if(s==-1||c==-1||d==-1)return;
 AnsiString na="se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data";
 Split(SE(na),'|');
 int i,p1=0,p2=0,p3=0,a;
 AnsiString st=li_split->Strings[d],st2;
 st2=st.SubString(6,st.Length()-5);
 if(st2!=""){Split(st2,'/');
  a=li_split->Count;
  if(a>0)p1=StrToInt(li_split->Strings[0]);
  if(a>1)p2=StrToInt(li_split->Strings[1]);
  if(a>2)p3=StrToInt(li_split->Strings[2]);}
 frmData->setFormFromData(st.SubString(1,4),p1,p2,p3);
 if(frmData->ShowModal()==mrOk){
  AnsiString va="";
  Split(SE(na),'|');
  for(i=0;i<li_split->Count;i++){
   if(i)va=va+"|";
   if(i==d)va=va+frmData->getValueStr();
   else va=va+li_split->Strings[i];}
  SE(na)=va;RefreshDataList();
  Mod(true);}
}

//---------------------------------------------------------------------------
void __fastcall TfrmSe::btnDataDeleteClick(TObject *Sender)
{//
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 int d=lbData->ItemIndex;
 AnsiString na="se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data";
 if(s==-1||c==-1||d==-1)return;
 if(Application->MessageBox("Really?","Delete",MB_OKCANCEL)==ID_CANCEL)return;
 Split(SE(na),'|');
 AnsiString va="";
 for(int i=0;i<li_split->Count;i++){
  if(i!=d){
   if(va!="")va=va+"|";
   va=va+li_split->Strings[i];}}
 SE(na)=va;RefreshDataList();Mod(true);
}

//---------------------------------------------------------------------------
unsigned char cal16(int a){return (a<0)?16+a:a;}

//export (mod 0:binary 1:basic 2:ccz80++
void __fastcall TfrmSe::ExportNse(char mod){
 unsigned char *buf=new unsigned char[65536],poss[256];
 int a,i,j,k,se,ch,chcnt[256],secnt,ln,hd_ln;
// unsigned char a;
 AnsiString hd,cmd;
 TStringList *li_buf=new TStringList();
 //---dir
 se=1;
 ln=0;
 while(SE("se"+IntToStr(se)+"Name")!=""){
  ln+=2;ch=1;
  while(SE("se"+IntToStr(se)+"ch"+IntToStr(ch)+"Delay")!="")++ch;
  //buf[ln++]=StrToInt(SE("se"+IntToStr(se)+"Bgmcut"))*128+ch-1;chcnt[se]=ch;
  ++se;}
 secnt=se;//buf[0]=secnt-1;
// buf[0]=(ln)&255;
// buf[1]=(ln)/256;
// buf[ln++]=7*32;
 for(i=1;i<secnt;i++){
  //---header
  hd_ln=ln;
  buf[(i-1)*2]=(ln-((i-1)*2))&255;
  buf[(i-1)*2+1]=(ln-((i-1)*2))/256;
  //for(j=1;j<chcnt[i];j++){
  // hd="se"+IntToStr(i)+"ch"+IntToStr(j);
  // ++ln;
  // buf[ln++]=StrToInt(SE(hd+"Delay"));
  // buf[ln++]=cal16(StrToInt(SE(hd+"Detune")))*16+StrToInt(SE(hd+"Priority"));}
  //--- data
  for(j=1;j<2;j++){
   hd="se"+IntToStr(i)+"ch"+IntToStr(j);
   Split(SE(hd+"Data"),'|');
   li_buf->Text=li_split->Text;
   buf[ln++]=StrToInt(SE(hd+"Noise"));
   for(k=0;k<li_buf->Count;k++){
    poss[k]=ln;
    cmd=li_buf->Strings[k];
    Split(cmd.SubString(6,cmd.Length()-5),'/');cmd=cmd.SubString(1,4);
    int p1=0,p2=0,p3=0;
    a=li_split->Count;
    if(cmd!="ende"){
     if(a>0)p1=StrToInt(li_split->Strings[0]);
     if(a>1)p2=StrToInt(li_split->Strings[1]);
     if(a>2)p3=StrToInt(li_split->Strings[2]);}
    //ShowMessage(cmd);

    if(cmd=="volm"){
     buf[ln++]=0*64+p1;}
    else if(cmd=="tone"){
     buf[ln++]=1*32+p1/256;
     buf[ln++]=p1&255;}
    else if(cmd=="nois"){
     buf[ln++]=2*32+p1;}
    else if(cmd=="pota"){
     buf[ln++]=3*32+(p1+8);
     buf[ln++]=p2;}
    else if(cmd=="volp"){
     buf[ln++]=4*32+(p1+8);}
    else if(cmd=="paus"){
     buf[ln++]=5*32+p1;}
    else if(cmd=="loop"){
     buf[ln++]=6*32+p1;
     buf[ln++]=ln+1-poss[p2-1];}
    //else if(cmd=="ende"){
    // buf[ln++]=6*32;
     //buf[ln++]=0;
     //buf[ln++]=255;
     //buf[ln++]=0;
    // }
    else if(cmd=="regi"){
     buf[ln++]=7*32+p1;
     buf[ln++]=p2;
     //buf[ln++]=0;
     //buf[ln++]=255;
     //buf[ln++]=0;
     }

     }
   buf[ln++]=6*32;
   }
  }

 AnsiString dat="";
 switch(mod){
  case 0://binary
   int han;
   if((han=FileCreate(SaveDialog2->FileName))==-1){Application->MessageBox("Can't create file.","Error",MB_ICONERROR);return;}
   FileWrite(han,buf,ln);
   FileClose(han);
   break;
  case 1://basic
   for(i=0;i<ln;i++){
    if(i%80==0){if(dat!="")dat=dat+"\xd\xa";dat=dat+"data";}
    else dat=dat+",";
   dat=dat+IntToHex(buf[i],2);}
   Clipboard()->AsText=dat;
   Application->MessageBox(("Copy to clipboard("+IntToStr(ln)+" bytes)").c_str(),"Export",MB_OK);
   break;
  case 2://ccZ80++
   for(i=0;i<ln;i++){
    if(i)dat=dat+",";
    if(i%256==0&&i){dat=dat+"\xd\xa";}
   dat=dat+"#"+IntToHex(buf[i],2);}
   Clipboard()->AsText=dat.LowerCase();
   Application->MessageBox(("Copy to clipboard("+IntToStr(ln)+" bytes)").c_str(),"Export",MB_OK);
   break;


   }
 delete buf;
 delete li_buf;
}

void __fastcall TfrmSe::mnExportClick(TObject *Sender)
{//SaveDialog1->Filter="*.nse|*.nse";SaveDialog1->DefaultExt="nse";
 if(!SaveDialog2->Execute())return;
 ExportNse(0);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSe::SaveFile(bool isSaveas){
 if(SaveDialog1->FileName==""||isSaveas){
  if(SaveDialog1->Execute()){li_se->SaveToFile(SaveDialog1->FileName);
  Caption=TITCAP2+ExtractFileName(SaveDialog1->FileName);
  Mod(false);return true;}
  return false;}
 else{Mod(false);li_se->SaveToFile(SaveDialog1->FileName);
  return true;}
}

void __fastcall TfrmSe::mnSaveClick(TObject *Sender)
{//SaveDialog1->Filter="*.sed|*.sed";SaveDialog1->DefaultExt="sed";
 SaveFile(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::btnChannelAddClick(TObject *Sender)
{int s=lbSe->ItemIndex;
 if(s==-1){Application->MessageBox("Select SE","Add channel",MB_ICONERROR);return;}
 AddChannel(s+1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::lbChannelClick(TObject *Sender)
{
 RefreshDataList();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSe::CheckMod(void){
 if(isMod){
  int a=Application->MessageBox("Save?","Confirm",MB_YESNOCANCEL);
  if(a==ID_YES){
   if(!SaveFile(false))return false;}
  else if(a==ID_CANCEL){return false;}}
 return true;}

void __fastcall TfrmSe::RefreshSeList(void){
 int cnt=1;
 lbSe->Clear();
 lbChannel->Clear();
 lbData->Clear();
 while(SE("se"+IntToStr(cnt)+"Name")!=""){
  AnsiString nz=(SE("se"+IntToStr(cnt)+"ch1Noise")=="1")?"(n)":"";
  lbSe->Items->Add(IntToStr(cnt)+" "+SE("se"+IntToStr(cnt)+"Name")+nz);
  if(cnt==1)lbSe->ItemIndex=0;
  ++cnt;}
 if(cnt>0){
  RefreshChannelList();}}


void __fastcall TfrmSe::mnOpenClick(TObject *Sender)
{if(!CheckMod())return;
 OpenDialog1->FileName="";
 if(!OpenDialog1->Execute())return;
 mnNewClick(Sender);
 li_se->LoadFromFile(OpenDialog1->FileName);
 RefreshSeList();
 SaveDialog1->FileName=OpenDialog1->FileName;
 Caption=TITCAP2+ExtractFileName(SaveDialog1->FileName);

 Mod(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::mnQuitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::mnNewClick(TObject *Sender)
{if(!CheckMod())return;
 li_se->Clear();
 lbSe->Clear();
 lbChannel->Clear();
 lbData->Clear();
 SaveDialog1->FileName="";
 Caption=TITCAP;
 Mod(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::lbSeClick(TObject *Sender)
{
 RefreshChannelList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::ExportasText1Click(TObject *Sender)
{
 ExportNse(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::btnSePropertyClick(TObject *Sender)
{
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 if(s==-1||c==-1){Application->MessageBox("Select the target sound","Add data",MB_ICONERROR);return;}
 FrmSeSet->EdtName->Text=SE("se"+IntToStr(s+1)+"Name");
 FrmSeSet->ChkNoise->Checked=(SE("se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Noise")=="1")?true:false;
 if(FrmSeSet->ShowModal()==mrOk){
  SE("se"+IntToStr(s+1)+"Name")=FrmSeSet->EdtName->Text;
  SE("se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Noise")=(FrmSeSet->ChkNoise->Checked)?"1":"0";
  AnsiString nz=(SE("se"+IntToStr(s+1)+"ch1Noise")=="1")?"(n)":"";
  lbSe->Items->Strings[s]=IntToStr(s+1)+" "+FrmSeSet->EdtName->Text+nz;
  Mod(true);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::btnUpClick(TObject *Sender)
{
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 int d=lbData->ItemIndex;
 AnsiString na="se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data";
 if(s==-1||c==-1||d==-1||d==0)return;
 Split(SE(na),'|');
 AnsiString va="";
 for(int i=0;i<li_split->Count;i++){
  if(va!="")va=va+"|";
  if(i==d-1)va=va+li_split->Strings[i+1];
  else if(i==d)va=va+li_split->Strings[i-1];
  else va=va+li_split->Strings[i];
  }
 SE(na)=va;RefreshDataList();
 lbData->ItemIndex=d-1;Mod(true);}
//---------------------------------------------------------------------------
void __fastcall TfrmSe::btnDownClick(TObject *Sender)
{
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 int d=lbData->ItemIndex;
 AnsiString na="se"+IntToStr(s+1)+"ch"+IntToStr(c+1)+"Data";
 if(s==-1||c==-1||d==-1||d==lbData->Items->Count-1)return;
 Split(SE(na),'|');
 AnsiString va="";
 for(int i=0;i<li_split->Count;i++){
  if(va!="")va=va+"|";
  if(i==d+1)va=va+li_split->Strings[i-1];
  else if(i==d)va=va+li_split->Strings[i+1];
  else va=va+li_split->Strings[i];
  }
 SE(na)=va;RefreshDataList();
 lbData->ItemIndex=d+1;Mod(true);}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::Saveas1Click(TObject *Sender)
{
 SaveFile(true);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::ccZ801Click(TObject *Sender)
{
 ExportNse(2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSe::btnSeDeleteClick(TObject *Sender)
{int i,j;
 int s=lbSe->ItemIndex;
 int c=lbChannel->ItemIndex;
 AnsiString hd,st;
 if(s==-1||c==-1)return;
 if(Application->MessageBox("Really?","Delete",MB_OKCANCEL)==ID_CANCEL)return;
 for(i=0;i<li_se->Count;i++){
  if(li_se->Strings[i].AnsiPos("se"+IntToStr(s+1))==1){li_se->Delete(i);--i;}}
 for(i=s+1;i<=lbSe->Count;i++){
  hd="se"+IntToStr(i);
  for(j=0;j<li_se->Count;j++){
   st=li_se->Strings[j];
   if(st.AnsiPos(hd)==1){
    st.Delete(1,hd.Length());
    li_se->Strings[j]="se"+IntToStr(i-1)+st;}}
    }
 RefreshSeList();Mod(true);
}
//---------------------------------------------------------------------------

