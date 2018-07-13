//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spp8.h"
#include "spcur1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmP8 *frmP8;
//---------------------------------------------------------------------------
__fastcall TfrmP8::TfrmP8(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmP8::Button1Click(TObject *Sender)
{
 Memo1->Clear();Memo1->PasteFromClipboard();
 Label1->Caption="Pasted "+IntToStr(Memo1->Lines->Count)+" lines to the buffer.";
 Form1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmP8::Button2Click(TObject *Sender)
{
 Memo1->SelectAll();Memo1->CopyToClipboard();
 Label1->Caption="Copied.";
 Form1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmP8::Button3Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmP8::SetClick(TObject *Sender)
{
 int sp=StrToInt(edtSpn->Text);
 int i,j,x=(sp&15)*8,y=(sp/16)*8;
 char *p;p=Form1->m;AnsiString st,st2;
 for(i=y;i<y+8;i++){st="";
  for(j=0;j<8;j++){
   st=st+IntToHex(*p,1).LowerCase();++p;}
//  ShowMessage(IntToHex(*p,1)[1]);
  st2=Memo1->Lines->Strings[i];st2.Delete(x+1,8);st2.Insert(st,x+1);
  Memo1->Lines->Strings[i]=st2;
  //Memo1->Lines->Strings[i].Insert(st,x+1);
  }
 Label1->Caption="Set "+IntToStr(sp);
 edtSpn->Text=IntToStr(sp+1);
 Form1->SetFocus();
  }
//---------------------------------------------------------------------------
