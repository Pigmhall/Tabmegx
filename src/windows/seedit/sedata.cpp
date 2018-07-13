//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sedata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmData *frmData;
//---------------------------------------------------------------------------
__fastcall TfrmData::TfrmData(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmData::cmbTypeChange(TObject *Sender)
{
 switch(cmbType->ItemIndex){
  case 0://Volume
   lblParam1->Caption="Volume";lblRange1->Caption="0~15";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="";lblRange2->Caption="";edtParam2->Visible=false;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
//   lblParam1->Caption="Noise";lblRange1->Caption="0:off 1:on";edtParam1->Visible=true;edtParam1->Text="";
//   lblParam2->Caption="Tone";lblRange2->Caption="0:off 1:on";edtParam2->Visible=true;edtParam2->Text="";
//   lblParam3->Caption="Volume";lblRange3->Caption="0~15";edtParam3->Visible=true;edtParam3->Text="";
   break;
  case 1://Tone
   lblParam1->Caption="Value";lblRange1->Caption="0~4095";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="";lblRange2->Caption="";edtParam2->Visible=false;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 2://Noise
   lblParam1->Caption="Value";lblRange1->Caption="0~15";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="";lblRange2->Caption="";edtParam2->Visible=false;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 3://Potalment
   lblParam1->Caption="Value";lblRange1->Caption="-8~7(0:rand)";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="Time";lblRange2->Caption="0~255";edtParam2->Visible=true;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 4://Volume+
   lblParam1->Caption="Value";lblRange1->Caption="-8~7";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="";lblRange2->Caption="";edtParam2->Visible=false;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 5://Pause
   lblParam1->Caption="Time";lblRange1->Caption="0~31";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="";lblRange2->Caption="";edtParam2->Visible=false;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 6://Loop
   lblParam1->Caption="Count";lblRange1->Caption="1~31";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="Goto";lblRange2->Caption="line number";edtParam2->Visible=true;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
  case 7://Register
   lblParam1->Caption="Register";lblRange1->Caption="0~13";edtParam1->Visible=true;edtParam1->Text="";
   lblParam2->Caption="Value";lblRange2->Caption="0~255";edtParam2->Visible=true;edtParam2->Text="";
   lblParam3->Caption="";lblRange3->Caption="";edtParam3->Visible=false;edtParam3->Text="";
   break;
   }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmData::codeToName(AnsiString cod){
 AnsiString na="";
 if(cod=="volm")na=cmbType->Items->Strings[0];
 else if(cod=="tone")na=cmbType->Items->Strings[1];
 else if(cod=="nois")na=cmbType->Items->Strings[2];
 else if(cod=="pota")na=cmbType->Items->Strings[3];
 else if(cod=="volp")na=cmbType->Items->Strings[4];
 else if(cod=="paus")na=cmbType->Items->Strings[5];
 else if(cod=="loop")na=cmbType->Items->Strings[6];
 else if(cod=="regi")na=cmbType->Items->Strings[7];
 return na;
}


AnsiString __fastcall TfrmData::getValueStr(void)
{AnsiString rs;
 switch(cmbType->ItemIndex){
  case 0:rs="volm:"+edtParam1->Text;break;
  case 1:rs="tone:"+edtParam1->Text;break;
  case 2:rs="nois:"+edtParam1->Text;break;
  case 3:rs="pota:"+edtParam1->Text+"/"+edtParam2->Text;break;
  case 4:rs="volp:"+edtParam1->Text;break;
  case 5:rs="paus:"+edtParam1->Text;break;
  case 6:rs="loop:"+edtParam1->Text+"/"+edtParam2->Text;break;
  case 7:rs="regi:"+edtParam1->Text+"/"+edtParam2->Text;break;}
 return rs;
}

void __fastcall TfrmData::setFormFromData(AnsiString st,int pa1,int pa2,int pa3){
 AnsiString cod=st;//.SubString(1,4);
 if(cod=="volm")cmbType->ItemIndex=0;
 else if(cod=="tone")cmbType->ItemIndex=1;
 else if(cod=="nois")cmbType->ItemIndex=2;
 else if(cod=="pota")cmbType->ItemIndex=3;
 else if(cod=="volp")cmbType->ItemIndex=4;
 else if(cod=="paus")cmbType->ItemIndex=5;
 else if(cod=="loop")cmbType->ItemIndex=6;
 else if(cod=="regi")cmbType->ItemIndex=7;
 cmbTypeChange(NULL);
 if(cmbType->ItemIndex==0&&pa1==-5000){
  edtParam1->Text="";  edtParam2->Text="";  edtParam3->Text="";}
 else{
  edtParam1->Text=IntToStr(pa1); edtParam2->Text=IntToStr(pa2); edtParam3->Text=IntToStr(pa3);}
}

void __fastcall TfrmData::btnOkClick(TObject *Sender)
{int p1,p2,p3;
 try{
  if(lblParam1->Caption!="")p1=StrToInt(edtParam1->Text);
  if(lblParam2->Caption!="")p2=StrToInt(edtParam2->Text);
  if(lblParam3->Caption!="")p3=StrToInt(edtParam3->Text);}
 catch(...){
  Application->MessageBox("A non-numeric value exists.","Error",MB_ICONERROR);
  return;}
 bool err=false;
 switch(cmbType->ItemIndex){
  case 0:if(p1<0||p1>15)err=true;break;
  case 1:if(p1<0||p1>4095)err=true;break;
  case 2:if(p1<0||p1>15)err=true;break;
  case 3:if(p1<-8||p1>7||p2<0||p2>255)err=true;break;
  case 4:if(p1<-8||p1>7)err=true;break;
  case 5:if(p1<1||p1>31)err=true;break;
  case 6:if(p1<0||p1>31||p2<0)err=true;break;
  case 7:if(p1<0||p1>13||p2<0||p2>255)err=true;break;

  }
 if(err){  Application->MessageBox("Range error.","Error",MB_ICONERROR);
  return;}



 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmData::btnCancelClick(TObject *Sender)
{
 ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
