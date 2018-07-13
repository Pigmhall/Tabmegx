//---- Key Assigin (megkeyas.cpp)
#include <vcl.h>
#pragma hdrstop

#include "megkeyas.h"
#include "megson1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmKeyas *FrmKeyas;

#define INI(X) FrmMeg1->li_ini->Values[X]
//---------------------------------------------------------------------------
__fastcall TFrmKeyas::TFrmKeyas(TComponent* Owner)
        : TForm(Owner){}
//---------------------------------------------------------------------------
void __fastcall TFrmKeyas::Button1Click(TObject *Sender)
{ModalResult=mrOk;}
//---------------------------------------------------------------------------
void __fastcall TFrmKeyas::Button2Click(TObject *Sender)
{ModalResult=mrCancel;}
//---------------------------------------------------------------------------
void __fastcall TFrmKeyas::Button3Click(TObject *Sender)
{
 if(ComboBox1->Text!=""){
//  INI(("keyAlt"+IntToStr(ComboBox1->Text[1])))=EdtAltX->Text;
//  INI(("keyShiftAlt"+IntToStr(ComboBox1->Text[1])))=EdtShiftAltX->Text;
  INI(("KeyAlt"+ComboBox1->Text))=EdtAltX->Text;
  INI(("KeyShiftAlt"+ComboBox1->Text))=EdtShiftAltX->Text;
 Application->MessageBox(("Alt+"+ComboBox1->Text+"="+EdtAltX->Text+"\n"
  +"Shift+Alt+"+ComboBox1->Text+"="+EdtShiftAltX->Text).c_str(),"Assign",MB_OK);
}}
//---------------------------------------------------------------------------
void __fastcall TFrmKeyas::ComboBox1Change(TObject *Sender)
{//if(ComboBox1->Text!=""){
// EdtAltX->Text=INI(("keyAlt"+IntToStr(ComboBox1->Text[1])));
// EdtShiftAltX->Text=INI(("keyShiftAlt"+IntToStr(ComboBox1->Text[1])));}}
 EdtAltX->Text=INI("KeyAlt"+ComboBox1->Text);
 EdtShiftAltX->Text=INI("KeyShiftAlt"+ComboBox1->Text);}
//---------------------------------------------------------------------------
void __fastcall TFrmKeyas::BtnHtmlClick(TObject *Sender)
{
 if(Application->MessageBox("Assign HTML preset?","Assign",MB_YESNO)==ID_NO)return;
 INI("KeyAltA")="<a href=\x22";INI("KeyShiftAltA")="</a>";
 INI("KeyAltB")="<b>%SELTEXT%</b>";//INI("KeyShiftAltB")="</b>";
 INI("KeyAltC")="<center>";INI("KeyShiftAltC")="</center>";
 INI("KeyAltD")="%DATE%";//INI("KeyAltD")="%KINO%";
 INI("KeyAltF")="<font |<form name=";INI("KeyShiftAltF")="</font>|</form>";
 INI("KeyAltH")="<html><head><title></title>\\n</head><body>";INI("KeyShiftAltH")="</body></html>";
 INI("KeyAltO")="<option value=";//INI("KeyShiftAltO")="";
 INI("KeyAltR")="<br>";INI("KeyShiftAltR")="<br clear=all>";
// INI("KeyAltS")="<select name=|<script type='text/javascript'>\\n<!--";INI("KeyShiftAltS")="</select>|// -->\\n</script>";
 INI("KeyAltT")="<table>|<tr>|<td>";INI("KeyShiftAltT")="</table>|</tr>|</td>";
 INI("KeyAltU")="<u>%SELTEXT%</u>";//INI("KeyShiftAltU")="</u>";
 INI("KeyAltY")="<i>%SELTEXT%</i>|<input type=";//INI("KeyShiftAltY")="</i>";
// INI("KeyAlt")="";INI("KeyShiftAlt")="";

}
//---------------------------------------------------------------------------

void __fastcall TFrmKeyas::Button4Click(TObject *Sender)
{
 Application->HelpCommand(HELP_CONTEXT,2);
}
//---------------------------------------------------------------------------
const AnsiString strSp[]={
"\\n","\\t","\\v","%CLIP%","%SELTEXT%","%INPUT%","%DATE%","%TIME%"
};
void __fastcall TFrmKeyas::mnStrSp(TObject *Sender)
{
 if(//(ActiveControl is TEdit)==1
  ActiveControl&&ActiveControl->Tag==0){
  ((TEdit*)ActiveControl)->SelText=strSp[((TMenuItem*)Sender)->Tag];}
}
//---------------------------------------------------------------------------

