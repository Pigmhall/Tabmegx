//----- Megnumber (数値入力ダイアログ)

#include <vcl.h>
#pragma hdrstop

#include "megnumber.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmNumber *FrmNumber;
//---------------------------------------------------------------------------
__fastcall TFrmNumber::TFrmNumber(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmNumber::Button1Click(TObject *Sender)
{ModalResult=mrOk;}
//---------------------------------------------------------------------------
void __fastcall TFrmNumber::Button2Click(TObject *Sender)
{ModalResult=mrCancel;}
//---------------------------------------------------------------------------
void __fastcall TFrmNumber::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{switch(Key){
  case VK_ESCAPE:ModalResult=mrCancel;return;
  case VK_RETURN:ModalResult=mrOk;return;}}
//---------------------------------------------------------------------------
