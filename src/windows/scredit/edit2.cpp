//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "edit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmCoord *FrmCoord;
//---------------------------------------------------------------------------
__fastcall TFrmCoord::TFrmCoord(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmCoord::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
