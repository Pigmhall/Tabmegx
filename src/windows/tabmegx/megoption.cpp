//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "megoption.h"
#include "megson1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define INI(X) FrmMeg1->li_ini->Values[X]

TFrmOption *FrmOption;
//---------------------------------------------------------------------------
__fastcall TFrmOption::TFrmOption(TComponent* Owner)
        : TForm(Owner){
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button1Click(TObject *Sender)
{
/* if(EdtRegcode->Text!=""&&!FrmMeg1->isReg){//8RaBlaDfBtQNaCkaGrq
  if(!FrmMeg1->chkRegcode(EdtRegcode->Text)){Application->MessageBox("“o˜^º°ÄÞ‚ªˆá‚¢‚Ü‚·","“o˜^",MB_OK);return;}
  else{Application->MessageBox("‚ ‚è‚ª‚Æ‚¤‚²‚´‚¢‚Ü‚·","“o˜^",MB_OK);FrmMeg1->isReg=true;FrmMeg1->Caption="Megson";}
  }*/
ModalResult=mrOk;}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button2Click(TObject *Sender)
{ModalResult=mrCancel;}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button4Click(TObject *Sender)
{int i;bool mod=false;AnsiString st;
 if(CmbExt->Text==""||EdtCmd->Text=="")return;
 INI("Ext"+CmbExt->Text)=EdtCmd->Text;
 for(i=0;i<CmbExt->Items->Count;i++){
  if(CmbExt->Items->Strings[i]==CmbExt->Text){mod=true;}}

 st="\n"+CmbExt->Text+"="+EdtCmd->Text;
 if(!mod){CmbExt->Items->Add(CmbExt->Text);
  Application->MessageBox(("’Ç‰Á"+st).c_str(),"ºÏÝÄÞ",MB_OK);}
 else Application->MessageBox(("XV"+st).c_str(),"ºÏÝÄÞ",MB_OK);
 CmbExt->Text="";EdtCmd->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::CmbExtChange(TObject *Sender)
{
 if(CmbExt->ItemIndex!=-1){
  EdtCmd->Text=INI("Ext"+CmbExt->Items->Strings[CmbExt->ItemIndex]);}
}
//---------------------------------------------------------------------------

void __fastcall TFrmOption::BtnBrowse0Click(TObject *Sender)
{
 OpenDialog1->FileName="";
// FrmMeg1->Fod1->Mask="*.exe;*.com;*.bat";
 if(OpenDialog1->Execute()){
  switch(((TButton*)Sender)->Tag){
   case 0:EdtCmd->Text=OpenDialog1->FileName+" \x22%f\x22 %a";break;
   case 1:EdtFxcmd->Text=OpenDialog1->FileName+" \x22%f\x22 %a";break;
   case 2:EdtWinScp->Text=OpenDialog1->FileName;break;}}
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button5Click(TObject *Sender)
{
 Application->HelpCommand(HELP_CONTEXT,14);
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button7Click(TObject *Sender)
{int i;AnsiString st;
 if(CmbFx->Text=="")return;
 INI("CmdCtrl"+CmbFx->Text)=EdtFxcmd->Text;
 Application->MessageBox(("Ctrl+"+CmbFx->Text+"="+EdtFxcmd->Text).c_str(),"XV",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::CmbFxChange(TObject *Sender)
{
 if(CmbFx->ItemIndex!=-1){
  EdtFxcmd->Text=INI("CmdCtrl"+CmbFx->Text);}
}
//---------------------------------------------------------------------------

