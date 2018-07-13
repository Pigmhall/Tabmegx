//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "megftp.h"
#include "megson1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmFtp *FrmFtp;
//---------------------------------------------------------------------------
#define P_NAME(a) FrmMeg1->GetSplit(0,li_ftp->Strings[a])
#define P_HOST(a) FrmMeg1->GetSplit(1,li_ftp->Strings[a])
#define P_USER(a) FrmMeg1->GetSplit(2,li_ftp->Strings[a])
#define P_PASSWD(a) FrmMeg1->GetSplit(3,li_ftp->Strings[a])
#define P_SERVERDIR(a) FrmMeg1->GetSplit(4,li_ftp->Strings[a])
#define P_CHMOD(a) FrmMeg1->GetSplit(5,li_ftp->Strings[a])
#define P_PASSIVE(a) FrmMeg1->GetSplit(6,li_ftp->Strings[a])
#define INI(X) FrmMeg1->li_ini->Values[X]
#define CKEY li_ftp->Strings[a][1]&127

__fastcall TFrmFtp::TFrmFtp(TComponent* Owner)
        : TForm(Owner)
{li_ftp=new TStringList();/*isFtp=false;*/}

void __fastcall TFrmFtp::LoadAllIni(void){
 int i=0;
 AnsiString st;
 li_ftp->Clear();CmbName->Items->Clear();
 while((st=INI("FtpServer"+IntToStr(i)))!=""){
  li_ftp->Add(st);
//  Application->MessageBox(li_ftp->Strings[i].c_str(),st.c_str(),MB_OK);
  CmbName->Items->Add(FrmMeg1->GetSplit(0,li_ftp->Strings[i]));
  ++i;}
 sel=StrToInt(INI("FtpDefault"));ExtractPa(sel);}

void __fastcall TFrmFtp::SaveAllIni(void){
 int i,j;
 for(i=0;i<FrmMeg1->li_ini->Count;i++){
  if(FrmMeg1->li_ini->Strings[i].SubString(1,9)=="FtpServer"){
   FrmMeg1->li_ini->Delete(i);--i;}}

 for(i=0;i<li_ftp->Count;i++){INI("FtpServer"+IntToStr(i))=li_ftp->Strings[i];}
 INI("FtpDefault")=IntToStr(sel);}

void __fastcall TFrmFtp::ExtractPa(int a){
// Caption=li_ftp->Strings[a];
 CmbName->Text=P_NAME(a);
 EdtHost->Text=P_HOST(a);
 EdtUser->Text=P_USER(a);
 EdtPasswd->Text=FrmMeg1->strDecrypt(P_PASSWD(a),CKEY);
 EdtServerDir->Text=P_SERVERDIR(a);
 EdtChmod->Text=P_CHMOD(a);
 ChkPassive->Checked=(P_PASSIVE(a)=="1")?true:false;
}

bool __fastcall TFrmFtp::SavePa(int a){
 if(CmbName->Items->Strings[a]==""){Application->MessageBox("Input name","Setting",MB_OK);return false;}
 li_ftp->Strings[a]=
  CmbName->Items->Strings[a]+"|"+
  EdtHost->Text+"|"+
  EdtUser->Text+"|"+
  FrmMeg1->strEncrypt(EdtPasswd->Text,CmbName->Items->Strings[a][1]&127)+"|"+
  EdtServerDir->Text+"|"+
  EdtChmod->Text+"|"+
  ((ChkPassive->Checked)?"1":"0");return true;
}

//---------------------------------------------------------------------------
void __fastcall TFrmFtp::Button1Click(TObject *Sender)
{if(SavePa(sel)){ModalResult=mrOk;SaveAllIni();/*Close();*/}}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::Button2Click(TObject *Sender)
{ModalResult=mrCancel;/*Close();*/}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::EdtHostKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 switch(Key){
  case VK_RETURN:if(!SavePa(sel))return;SaveAllIni();
  case VK_ESCAPE:Close();break;}}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::Button3Click(TObject *Sender)
{
 if(!SavePa(sel))return;
 CmbName->Text="New"+IntToStr(CmbName->Items->Count+1);
 CmbName->Items->Add(CmbName->Text);
 li_ftp->Add(CmbName->Text+"||||||");
 CmbName->ItemIndex=CmbName->Items->Count-1;sel=CmbName->ItemIndex;
 EdtHost->Text="";
 EdtUser->Text="";
 EdtPasswd->Text="";
 EdtServerDir->Text="";
 EdtChmod->Text="";
 ChkPassive->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::Button4Click(TObject *Sender)
{
 if(CmbName->Items->Count==1){
  Application->MessageBox("Can't delete last server","delete",MB_ICONINFORMATION);return;}
 if(Application->MessageBox("Delete?","",MB_YESNO)==ID_NO)return;
 li_ftp->Delete(sel);
 CmbName->Items->Delete(sel);if(sel>CmbName->Items->Count-1)--sel;ExtractPa(sel);
}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::CmbNameKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 switch(Key){
  case VK_UP:case VK_DOWN:case VK_RIGHT: case VK_LEFT: return;
  case VK_RETURN:if(!SavePa(sel))return;SaveAllIni();
  case VK_ESCAPE:Close();break;
  default:
 CmbName->Items->Strings[sel]=CmbName->Text;
// P_NAME(sel)=CmbName->Text;
 break;}
}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::CmbNameChange(TObject *Sender)
{
 if(CmbName->ItemIndex!=-1&&sel!=CmbName->ItemIndex){
  if(!SavePa(sel)){CmbName->ItemIndex=sel;return;}sel=CmbName->ItemIndex;ExtractPa(sel);
  //pa->Strings[0]=IntToStr(sel);
  }}
//---------------------------------------------------------------------------
/*int __fastcall TFrmFtp::NameToNum(AnsiString sv){
 int i;
 for(i=0;i<li_ftp->Count;i++){
  if(GetSplit(0,li_ftp->Strings[i])==sv)return i;}
 return -1;}*/

void __fastcall TFrmFtp::FormShow(TObject *Sender)
{LoadAllIni();CmbName->SetFocus();}
//---------------------------------------------------------------------------
void __fastcall TFrmFtp::FormClose(TObject *Sender, TCloseAction &Action)
{delete li_ftp;}
//---------------------------------------------------------------------------

