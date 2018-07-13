//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sese.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmSeSet *FrmSeSet;
//---------------------------------------------------------------------------
__fastcall TFrmSeSet::TFrmSeSet(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmSeSet::btnOkClick(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TFrmSeSet::btnCancelClick(TObject *Sender)
{
 ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
