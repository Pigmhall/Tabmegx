//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bintobas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if(OpenDialog1->Execute()){
//--- “Çž‚Ý
 int sz=StrToInt(edtNum->Text);
 int i,han,len;unsigned char *buf,*p;

  if((han=FileOpen(OpenDialog1->FileName,fmOpenRead))==-1){return;}
  len=FileSeek(han,0,2);
  FileSeek(han,0,0);
  buf=new unsigned char[len+256];
  p=buf;for(i=0;i<len+256;i++)*(p++)=0;
  FileRead(han,buf,len);
  FileClose(han);
//  len=(len/sz+1)*sz;
  AnsiString st="";p=buf;
  bool isCcz80=chkCcz80->Checked;
  for(i=0;i<len;i++){
   if(isCcz80){
    st=st+"#"+IntToHex(*(p++),2);
    if(i!=len-1)st=st+",";
    }
   else{if(i%sz==0){st=st+"data ";}
    st=st+IntToHex(*(p++),2);}
   if(i%sz==sz-1){st=st+"\n";}
   }
  Memo1->Lines->Text=st;
  Memo1->SelectAll();
  Memo1->CopyToClipboard();}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

