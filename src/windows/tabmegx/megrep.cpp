//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "megrep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRep *frmRep;
//---------------------------------------------------------------------------
__fastcall TfrmRep::TfrmRep(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmRep::Button1Click(TObject *Sender)
{
 ModalResult=mrYes;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRep::Button2Click(TObject *Sender)
{
 ModalResult=mrNo;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRep::Button3Click(TObject *Sender)
{
 ModalResult=mrCancel;

}
//---------------------------------------------------------------------------
void __fastcall TfrmRep::Button4Click(TObject *Sender)
{
 ModalResult=mrAll;

}
//---------------------------------------------------------------------------
