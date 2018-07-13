//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "palNew.h"
#include "palette1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmNew *frmNew;
//---------------------------------------------------------------------------
__fastcall TfrmNew::TfrmNew(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmNew::Button1Click(TObject *Sender)
{
 if(Edit1->Text==""){Application->MessageBox("Input new palette name","Prompt",MB_OK);return;}
 for(int i=0;i<frmPal->ComboBox1->Items->Count;i++){
  if(Edit1->Text==frmPal->ComboBox1->Items->Strings[i]){
   Application->MessageBox("palette name already exists","Prompt",MB_OK);return;}}
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNew::Button2Click(TObject *Sender)
{
 ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
