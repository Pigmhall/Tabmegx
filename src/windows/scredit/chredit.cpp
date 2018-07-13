//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chredit.h"
#include "edit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmChrEdit *frmChrEdit;
TStringList *li_temp;

int SZ;bool ok;
AnsiString di_chr;
//---------------------------------------------------------------------------
__fastcall TfrmChrEdit::TfrmChrEdit(TComponent* Owner)
        : TForm(Owner)
{SZ=frmEdit->gsz;
Image2->Width=SZ;
Image2->Height=SZ;
Image1->Width=SZ*16;
Image1->Height=SZ*16;
Left=0;Top=32;ok=true;
li_temp=new TStringList();
PatBlt(Image2->Canvas->Handle,0,0,SZ,SZ,BLACKNESS);
di_chr=ExtractFilePath(ExtractFileDir(Application->ExeName))+"tabrenchx\\bmp";
//di_chr=ExtractFilePath(Application->ExeName)+"..\\tabrenchx\\bmp";
}
//---------------------------------------------------------------------------
void __fastcall TfrmChrEdit::RefreshChrs(void){
 li_temp->Clear();
 di_chr=ExtractFileDir(OpenDialog1->FileName);
 AnsiString di=di_chr+"\\";
 int RC,i;bool num;
 TSearchRec SearchRec;
 AnsiString hd="",fi=ExtractFileName(OpenDialog1->FileName);
 i=1;
 if(fi[i]>='0'&&fi[i]<='9'){num=true;
  while(fi[i]>='0'&&fi[i]<='9'){hd=hd+fi[i];++i;}}
 else{num=false;
  while((fi[i]>='a'&&fi[i]<='z')||fi[i]>='A'&&fi[i]<='Z'){hd=hd+fi[i];++i;}}
// ShowMessage(hd);
 RC=FindFirst(di+"*.bmp",faAnyFile,SearchRec);
 while(RC==0){
  if(SearchRec.Name.AnsiPos(hd)==1&&(!num||SearchRec.Name[hd.Length()+1]<'0'||SearchRec.Name[hd.Length()+1]>'9'))li_temp->Add(SearchRec.Name);
   RC=FindNext(SearchRec);}
//  finally
 FindClose(SearchRec);
 li_temp->Sort();
}

void __fastcall TfrmChrEdit::btnLoadDClick(TObject *Sender)
{
 if(DirectoryExists(di_chr)){//Application->MessageBox("find","OK",MB_OK);
 OpenDialog1->InitialDir=di_chr;}
 if(OpenDialog1->Execute()){
  Image3->Picture->LoadFromFile(OpenDialog1->FileName);
  PatBlt(Image2->Canvas->Handle,0,0,SZ,SZ,BLACKNESS);
  StretchBlt(Image2->Canvas->Handle,0,0,SZ,SZ,Image3->Canvas->Handle,0,0,Image3->Width,Image3->Height,SRCCOPY);
  Image2->Refresh();
  RefreshChrs();lblCnt->Caption="("+IntToStr(li_temp->Count)+")";}
}
//---------------------------------------------------------------------------
void __fastcall TfrmChrEdit::FormShow(TObject *Sender)
{
 BitBlt(Image1->Canvas->Handle,0,0,SZ*16,SZ*16,frmEdit->Image2->Canvas->Handle,0,0,SRCCOPY);
 Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmChrEdit::btnOpenClick(TObject *Sender)
{OpenDialog1->InitialDir=ExtractFilePath(Application->ExeName);
 if(OpenDialog1->Execute()){
  Image1->Picture->LoadFromFile(OpenDialog1->FileName);
  bmpFile=OpenDialog1->FileName;ok=false;Timer1->Enabled=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmChrEdit::BitBtn2Click(TObject *Sender)
{
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmChrEdit::BitBtn3Click(TObject *Sender)
{
 ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfrmChrEdit::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{if(!ok)return;
 X=(X/SZ);Y=(Y/SZ);
// BitBlt(Image1->Canvas->Handle,X*SZ,Y*SZ,SZ,SZ,Image2->Canvas->Handle,0,0,SRCCOPY);
// if(li_temp->Count>1){
  for(int i=0;i<li_temp->Count;i++){
   Image3->Picture->LoadFromFile(di_chr+"\\"+li_temp->Strings[i]);
   PatBlt(Image2->Canvas->Handle,0,0,SZ,SZ,BLACKNESS);
   StretchBlt(Image2->Canvas->Handle,0,0,SZ,SZ,Image3->Canvas->Handle,0,0,Image3->Width,Image3->Height,SRCCOPY);
   BitBlt(Image1->Canvas->Handle,X*SZ,Y*SZ,SZ,SZ,Image2->Canvas->Handle,0,0,SRCCOPY);
   ++X;if(X==16){X=0;++Y;}
  }
 Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmChrEdit::btnSaveClick(TObject *Sender)
{
SaveDialog1->InitialDir=ExtractFilePath(Application->ExeName);
 if(SaveDialog1->Execute()){
  Image1->Picture->SaveToFile(SaveDialog1->FileName);
  bmpFile=SaveDialog1->FileName;ok=false;Timer1->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChrEdit::Timer1Timer(TObject *Sender)
{
 ok=true;Timer1->Enabled=false;        
}
//---------------------------------------------------------------------------

