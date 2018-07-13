//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "color.h"
#include "palette1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmColor *frmColor;
//---------------------------------------------------------------------------
__fastcall TfrmColor::TfrmColor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmColor::RefreshPal(void)
{
 lblR->Caption="R:"+IntToStr(tbR->Position);
 lblG->Caption="G:"+IntToStr(tbG->Position);
 lblB->Caption="B:"+IntToStr(tbB->Position);
 TColor c=(tbB->Position*BITS+BITSZ)*65536+(tbG->Position*BITS+BITSZ)*256+tbR->Position*BITS+BITSZ;
 Image1->Canvas->Pen->Color=c;
 Image1->Canvas->Brush->Color=c;
 Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
 Image1->Refresh();
}

void __fastcall TfrmColor::OKClick(TObject *Sender)
{
 ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmColor::Button1Click(TObject *Sender)
{
 ModalResult=mrCancel;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmColor::tbRChange(TObject *Sender)
{
 RefreshPal();
}
//---------------------------------------------------------------------------
