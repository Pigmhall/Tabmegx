//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "palette1.h"
#include "color.h"
#include "palNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPal *frmPal;
AnsiString pa,fi_cur;
//---------------------------------------------------------------------------
__fastcall TfrmPal::TfrmPal(TComponent* Owner)
        : TForm(Owner)
{fi_cur="palette.bmp";
 pa=ExtractFilePath(Application->ExeName);
 Image1->Picture->LoadFromFile(pa+fi_cur);
 Generate();
 RefreshList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{X=(X/32)*32;
 TColor pencol=Image1->Canvas->Pixels[X][0];
 frmColor->tbB->Max=(chk5bits->Checked)?31:7;
 frmColor->tbG->Max=(chk5bits->Checked)?31:7;
 frmColor->tbR->Max=(chk5bits->Checked)?31:7;
 frmColor->tbB->Position=pencol/65536/BITS;
 frmColor->tbG->Position=((pencol/256)&255)/BITS;
 frmColor->tbR->Position=(pencol&255)/BITS;
 frmColor->RefreshPal();
 if(frmColor->ShowModal()==mrOk){
  BitBlt(Image1->Canvas->Handle,X,0,32,40,frmColor->Image1->Canvas->Handle,0,0,SRCCOPY);
  Image1->Refresh();
  Generate();}

}
//---------------------------------------------------------------------------

void __fastcall TfrmPal::btDefaultClick(TObject *Sender)
{
 Image1->Picture->Bitmap=NULL;
 Image1->Picture->LoadFromFile(pa+"default.bmp");
 Generate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::btCopyClick(TObject *Sender)
{
 Memo1->SelectAll();Memo1->CopyToClipboard();
 StatusBar1->SimpleText="Copied to clipboard.";Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::Generate(void){
AnsiString st;
 for(int i=0;i<16;i++){if(i)st=st+", ";
  TColor pencol=Image1->Canvas->Pixels[i*32][0];
  int b=pencol/65536/BITS;
  int g=((pencol/256)&255)/BITS;
  int r=(pencol&255)/BITS;
//  if(rbBasic->Checked){
   st=st+IntToStr(r)+","+IntToStr(g)+","+IntToStr(b);}//}
 Memo1->Lines->Text=st;}

void __fastcall TfrmPal::btSaveClick(TObject *Sender)
{
 Image1->Picture->SaveToFile(pa+"palette.bmp");
 if(fi_cur!="palette.bmp")Image1->Picture->SaveToFile(pa+fi_cur);
 StatusBar1->SimpleText="Saved.";Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPal::Timer1Timer(TObject *Sender)
{
 StatusBar1->SimpleText="";Timer1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::RefreshList(void){
 int RC,p;
 TSearchRec SearchRec;
 AnsiString ss;
 RC=FindFirst(pa+"*.bmp",faAnyFile,SearchRec);
 ComboBox1->Items->Clear();
 while(RC==0){
  ss=SearchRec.Name;
  ComboBox1->Items->Add(ss.SubString(1,ss.Length()-4));
  if(ss==fi_cur)ComboBox1->ItemIndex=ComboBox1->Items->Count-1;
  RC=FindNext(SearchRec);}
//  finally
 FindClose(SearchRec);
 btDel->Enabled=(fi_cur=="palette.bmp"||fi_cur=="default.bmp")?false:true;
}

void __fastcall TfrmPal::ComboBox1Change(TObject *Sender)
{
 fi_cur=ComboBox1->Items->Strings[ComboBox1->ItemIndex]+".bmp";
 Image1->Picture->Bitmap=NULL;
 Image1->Picture->LoadFromFile(pa+fi_cur);
 btDel->Enabled=(fi_cur=="palette.bmp"||fi_cur=="default.bmp")?false:true;
 Generate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::btAddClick(TObject *Sender)
{frmNew->Edit1->Text="";
 if(frmNew->ShowModal()==mrOk){
  fi_cur=frmNew->Edit1->Text+".bmp";
  ComboBox1->Items->Add(fi_cur);
  Image1->Picture->SaveToFile(pa+fi_cur);
  RefreshList();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::Button3Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPal::btDelClick(TObject *Sender)
{
 AnsiString fi=ComboBox1->Items->Strings[ComboBox1->ItemIndex];
 if(Application->MessageBox("Delete current palette?","prompt",MB_YESNO)==ID_YES){
  DeleteFile(pa+fi+".bmp");
  fi_cur="palette.bmp";
  RefreshList();
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPal::btCopyExitClick(TObject *Sender)
{
 Memo1->SelectAll();Memo1->CopyToClipboard();
 Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmPal::chk5bitsClick(TObject *Sender)
{
 Generate();
}
//---------------------------------------------------------------------------

