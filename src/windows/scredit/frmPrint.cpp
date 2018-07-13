//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmPrint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrin *frmPrin;
//---------------------------------------------------------------------------
__fastcall TfrmPrin::TfrmPrin(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrin::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrin::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 switch(Key){
  case VK_RETURN:ModalResult=mrOk;break;
  case VK_ESCAPE:ModalResult=mrCancel;break;}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrin::FormShow(TObject *Sender)
{
 Edit1->SetFocus();
}
//---------------------------------------------------------------------------

