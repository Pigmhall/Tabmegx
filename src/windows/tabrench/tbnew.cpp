//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tbnew.h"
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
void __fastcall TfrmNew::OKClick(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmNew::Button1Click(TObject *Sender)
{
 ModalResult=mrCancel;        
}
//---------------------------------------------------------------------------
