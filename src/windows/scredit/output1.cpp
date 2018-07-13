//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "output1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmOutput *frmOutput;
//---------------------------------------------------------------------------
__fastcall TfrmOutput::TfrmOutput(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmOutput::Button1Click(TObject *Sender)
{
 Memo1->SelectAll();
 Memo1->CopyToClipboard();
 Close();        
}
//---------------------------------------------------------------------------
