//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "option1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmOption *FrmOption;
//---------------------------------------------------------------------------
__fastcall TFrmOption::TFrmOption(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::Button2Click(TObject *Sender)
{
 ModalResult=mrCancel;        
}
//---------------------------------------------------------------------------
void __fastcall TFrmOption::RefreshWindow(void){
 try{
 LblWindow->Caption="Window="+IntToStr(StrToInt(EdtWidth->Text)*StrToInt(EdtDotSize->Text))+" x "+IntToStr(StrToInt(EdtHeight->Text)*StrToInt(EdtDotSize->Text));
 }catch(...){
  LblWindow->Caption="Window=???";}
}

void __fastcall TFrmOption::EdtWidthChange(TObject *Sender)
{
if(Visible)RefreshWindow();
}
//---------------------------------------------------------------------------

