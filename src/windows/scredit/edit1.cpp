//---------------------------------------------------------------------------
#include <vcl.h>
//#include <jpeg.hpp>
#pragma hdrstop
#define IM1 Image1->Canvas->Handle
#define IM2 Image2->Canvas->Handle
#define IM3 Image3->Canvas->Handle
//#define IM4 Image4->Canvas->Handle
#define INI(X) li_ini->Values[X]
#include "edit1.h"
#include "edit2.h"
#include "frmPrint.h"
#include "output1.h"
#include "chredit.h"
#include <vcl\Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEdit *frmEdit;

AnsiString DEFCAP="scredit";
int SWX=16,SWY=15,WX=32,WY=24,SZ=37,MAX=1,MSK=33,SCX=SWX*SZ,SCY=SWY*SZ;//BLY=32*4;
const CPL=16;//Character per line
bool isMod,isSpoit,isText,ok;
char unsigned *ep,*m,st,cst;
int ex,ey,BLY=0,BEY=15,wx,wy,cx1,cy1;
AnsiString pa,fi_ini;
const CURX=15*SZ,CURY=0,TSZ=40;// Cursor Pos(IM1)
const TColor curColor=clRed;
//---------------------------------------------------------------------------
__fastcall TfrmEdit::TfrmEdit(TComponent* Owner)
        : TForm(Owner)
{int i;char *p;
// Image4->Width=SCX;Image4->Height=SCY;PatBlt(IM4,0,0,SCX,SCY,BLACKNESS);
 pa=ExtractFilePath(Application->ExeName);
 fi_ini=pa+"edit.ini";
 li_ini=new TStringList();
 Image2->Picture->LoadFromFile(pa+"fonts37.bmp");
 INI("Width")=WX;
 INI("Height")=WY;
 INI("VW")=SWX;
 INI("VH")=SWY;
 if(FileExists(fi_ini)){li_ini->LoadFromFile(fi_ini);}
 try{
  if(INI("Bitmap")!=""){Image2->Picture->LoadFromFile(INI("Bitmap"));}
   //Image2_2->Picture->LoadFromFile(INI("Bitmap2"));
  //Left=StrToInt(INI("Left"));
  //Top=StrToInt(INI("Top"));
  WX=StrToInt(INI("Width"));
  WY=StrToInt(INI("Height"));
  SWX=StrToInt(INI("VW"));
  SWY=StrToInt(INI("VH"));
  }catch(...){};
 if(WX<SWX)SWX=WX;if(WY<SWY)SWY=WY;SCX=SWX*SZ;SCY=SWY*SZ;
 ClientWidth=SCX;ClientHeight=SCY+SZ+TSZ;
 Image1->Width=SCX;Image1->Height=SCY+SZ;
 Image3->Width=SCX;Image3->Height=SCY;
 Image1->Top=TSZ;
 gsz=SZ;
 Left=0;Top=16;
 m=new unsigned char[WX*WY*MAX];
 p=m;for(i=0;i<WX*WY*MAX;i++)*(p++)=0;
 st=0;ex=1;ey=0;wx=0;wy=0;cst=-1;
 PatBlt(IM1,0,0,SCX,SCY+SZ,BLACKNESS);
 PatBlt(IM3,0,0,SCX,SCY,BLACKNESS);
// Image3->Picture->LoadFromFile("c:\\projects\\bkbmb\\dat\\bm1.bmp");

 PutFloor();PutBlocks();
 OpenDialog1->InitialDir=pa;
// OpenDialog2->InitialDir=pa+"..\\";
 SaveDialog1->InitialDir=pa;
 DragAcceptFiles(Handle,True);
 ResetModify();
 isSpoit=false;isText=false;ok=true;
 Caption=DEFCAP;
}
//------ RefreshCursorStatus
void __fastcall TfrmEdit::RefreshCursorStatus(int x,int y){
// AnsiString st=IntToStr(x)+":"+IntToStr(y);
// if(st!=mnXY->Caption)mnXY->Caption=st;
 //StatusBar1->Panels->Items[3]->Text=;
 }
//--
void __fastcall TfrmEdit::RefreshStatus(void){
 AnsiString st1=IntToStr(cx1)+":"+IntToStr(cy1)+"("+IntToStr(wx)+":"+IntToStr(wy)+") c:"+IntToStr(ex+ey*CPL);// "+IntToStr(st+1)+"
 if(st1!=mnStatus->Caption)mnStatus->Caption=st1;
/* StatusBar1->Panels->Items[0]->Text="lv:"+IntToStr(st+1);
 StatusBar1->Panels->Items[1]->Text=IntToStr(wx)+":"+IntToStr(wy);
 StatusBar1->Panels->Items[2]->Text="c:"+IntToStr(ex+ey*CPL);*/}
//--
void __fastcall TfrmEdit::RefreshCopyStatus(void){
 mnCopy->Caption="["+IntToStr(cst)+"]";
 }

//------ Modify
void __fastcall TfrmEdit::SetModify(void){
 mnModify1->Caption="@";isMod=true;}
void __fastcall TfrmEdit::ResetModify(void){
 mnModify1->Caption="";isMod=false;}

//----- Draw Floor
void __fastcall TfrmEdit::PutFloor(void){
 unsigned char *p;int i,j,ax,ay;
 ep=m+st*WX*WY+wx+wy*WX;p=ep;
// BitBlt(IM1,0,SZ,SCX,SCY,IM3,0,0,SRCCOPY);
//LoadImage("st1"+IntToStr(st));
 PatBlt(IM1,0,SZ,SCX,SCY,BLACKNESS);
 BitBlt(IM1,0,SZ,SCX,SCY,IM3,0,0,SRCCOPY);
 for(i=0;i<SWY;i++){
  for(j=0;j<SWX;j++){
   ax=(*p%CPL)*SZ;ay=(*p/CPL)*SZ+BLY;
   if(!*p)BitBlt(IM1,j*SZ,i*SZ+SZ,SZ,SZ,IM3,j*SZ,i*SZ,SRCPAINT);else
   if(*p)BitBlt(IM1,j*SZ,i*SZ+SZ,SZ,SZ,IM2,ax,ay,SRCPAINT);
   ++p;}p+=WX-SWX;}
// Caption=IntToStr(st+1)+":"+IntToStr(wx);
// for(i=0;i<WY;i++)BitBlt(IM1,WX*SZ/2,i*SZ,1,SZ,IM2,0,48,SRCCOPY);
// for(i=0;i<WX;i++)BitBlt(IM1,i*SZ,WY*SZ/2,SZ,1,IM2,16,48,SRCCOPY);
 RefreshStatus();PutBlocks();
 Image1->Refresh();}

//----- Draw Blocks
void __fastcall TfrmEdit::PutBlocks(void){
 BitBlt(IM1,0,0,CPL*SZ,SZ,IM2,0,ey*SZ+BLY,SRCCOPY);
// BitBlt(IM1,32,0,16,16,IM2,ex*16,ey*16+BLY,SRCCOPY);
// BitBlt(IM1,0+ex*SZ,0,10,10,IM2,CURX+SZ,CURY,SRCAND);
// BitBlt(IM1,0+ex*SZ,0,SZ,SZ,IM2,CURX,CURY,SRCPAINT);
 // DrawSquare
 Image1->Canvas->Pen->Color=curColor;
 Image1->Canvas->MoveTo(ex*SZ,0);Image1->Canvas->LineTo(ex*SZ+SZ-1,0);
 Image1->Canvas->LineTo(ex*SZ+SZ-1,SZ-1);Image1->Canvas->LineTo(ex*SZ,SZ-1);
 Image1->Canvas->LineTo(ex*SZ,0);
 Image1->Canvas->MoveTo(ex*SZ+1,1);Image1->Canvas->LineTo(ex*SZ+SZ-2,1);
 Image1->Canvas->LineTo(ex*SZ+SZ-2,SZ-2);Image1->Canvas->LineTo(ex*SZ+1,SZ-2);
 Image1->Canvas->LineTo(ex*SZ+1,1);
 Image1->Refresh();
 RefreshStatus();}

//----------- Mouse events
void __fastcall TfrmEdit::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{if(!ok)return;if(ActiveControl)ActiveControl=NULL;
 char *p;
 if(Y<SZ){if(X>0&&X<SZ*CPL){ex=X/SZ;PutBlocks();}}// Select Chr
 else if(X>0&&X<SCX&&Y>SZ&&Y<SCY+SZ){if(Button==mbLeft){
  X/=SZ;Y/=SZ;--Y;p=ep+X+Y*WX;cx1=wx+X;cy1=wy+Y;
  if(isText){isText=false;InsertText();}
  else if(Shift.Contains(ssShift)||isSpoit){isSpoit=false;ex=*p%CPL;ey=*p/CPL;PutBlocks();
   Clipboard()->AsText=IntToStr(cx1)+","+IntToStr(cy1);
   }// Pick Chr
  else{*p=ex+ey*CPL;BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM2,ex*SZ,ey*SZ+BLY,SRCCOPY);SetModify();}}
 else{// Erase Chr
  X/=SZ;Y/=SZ;--Y;p=ep+X+Y*WX;*p=0;SetModify();
  //BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM2,0,BLY,SRCCOPY);
  //BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM4,X*SZ,Y*SZ,SRCCOPY);
  BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM3,X*SZ,Y*SZ,SRCCOPY);
  }}
 Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{if(!ok)return;
 char *p;
 if(X>0&&X<SCX&&Y>SZ&&Y<SCY+SZ){X/=SZ;Y/=SZ;--Y;p=ep+X+Y*WX;
  RefreshCursorStatus(wx+X,Y);cx1=wx+X;cy1=wy+Y;
  if(Shift.Contains(ssLeft)&&*p!=ex+ey*CPL){//Set Chr
   *p=ex+ey*CPL;
   BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM2,ex*SZ,ey*SZ+BLY,SRCCOPY);Image1->Refresh();}
  else if(Shift.Contains(ssRight)&&*p!=0){//Erase Chr
   *p=0;
   //BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM4,X*SZ,Y*SZ,SRCCOPY);
   BitBlt(IM1,X*SZ,Y*SZ+SZ,SZ,SZ,IM3,X*SZ,Y*SZ,SRCCOPY);
   Image1->Refresh();}}
}
//------ Key board Event
void __fastcall TfrmEdit::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift){
switch(Key){
  case VK_INSERT:if(ey)--ey;PutBlocks();break;
  case VK_DELETE:if(ey!=BEY)++ey;PutBlocks();break;
  case 'M':if(ex!=CPL-1)++ex;PutBlocks();break;
  case 'N':if(ex)--ex;PutBlocks();break;
  case VK_LEFT:if(wx!=0)--wx;PutFloor();break;
  case VK_RIGHT:if(wx!=WX-SWX)++wx;PutFloor();break;
  case VK_UP:if(wy!=0)--wy;PutFloor();break;
  case VK_DOWN:if(wy!=WY-SWY)++wy;PutFloor();break;
  case VK_ESCAPE:Close();break;
  }
}
//------- Menu events
//----- Open
void __fastcall TfrmEdit::Open1Click(TObject *Sender)
{
 int han;
 if(isMod){if(!SavePrompt())return;}
 OpenDialog1->FileName="";
 if(OpenDialog1->Execute()){
  han=FileOpen(OpenDialog1->FileName,fmOpenRead);
  FileRead(han,m,WX*WY*MAX);
  FileClose(han);
  SaveDialog1->FileName=OpenDialog1->FileName;
  Caption=DEFCAP+" - "+SaveDialog1->FileName;
  ResetModify();
  st=0;wx=0;wy=0;PutFloor();ok=false;Timer1->Enabled=true;}}
//----- 保存確認
bool __fastcall TfrmEdit::SavePrompt(void){
 int a=Application->MessageBox("Save modify?","Confirm",MB_YESNOCANCEL);
 if(a==ID_YES){if(SaveFile())return true;}
 if(a==ID_NO){return true;}
 return false;}
//----- ファイルを保存
bool __fastcall TfrmEdit::SaveFile(void){
 int han;
 if(SaveDialog1->FileName==""){
  if(!SaveDialog1->Execute())return false;
  ok=false;Timer1->Enabled=true;}
 han=FileCreate(SaveDialog1->FileName);
 FileWrite(han,m,WX*WY*MAX);
 FileClose(han);
 Caption=DEFCAP+" - "+SaveDialog1->FileName;
 ResetModify();return true;}
//----- File Save
void __fastcall TfrmEdit::Save1Click(TObject *Sender)
{SaveFile();}
//----- File Save as
void __fastcall TfrmEdit::Saveas1Click(TObject *Sender)
{if(SaveDialog1->Execute())SaveFile();}
//----- File Bitmap
void __fastcall TfrmEdit::mnChrEditClick(TObject *Sender)
{
/* if(OpenDialog2->Execute()){
  Image2->Picture->LoadFromFile(OpenDialog2->FileName);
  INI("Bitmap")=OpenDialog2->FileName;}
 PutBlocks();PutFloor();*/
 frmChrEdit->bmpFile=INI("Bitmap");
 if(frmChrEdit->ShowModal()==mrOk){
  INI("Bitmap")=frmChrEdit->bmpFile;
  Image2->Picture->LoadFromFile(frmChrEdit->bmpFile);
  PutFloor();}
}
//----- File Coord
void __fastcall TfrmEdit::Coord1Click(TObject *Sender){
 FrmCoord->EdtWidth->Text=INI("Width");
 FrmCoord->EdtHeight->Text=INI("Height");
 FrmCoord->EdtSwx->Text=INI("VW");
 FrmCoord->EdtSwy->Text=INI("VH");
 if(FrmCoord->ShowModal()==mrOk){
  INI("Width")=FrmCoord->EdtWidth->Text;
  INI("Height")=FrmCoord->EdtHeight->Text;
  INI("VW")=FrmCoord->EdtSwx->Text;
  INI("VH")=FrmCoord->EdtSwy->Text;
  Application->MessageBox("Please restart.","Option",MB_OK);
  ey=0;ex=0;
  PutBlocks();PutFloor();
  }
}
//----- File Quit
void __fastcall TfrmEdit::Quit1Click(TObject *Sender)
{Close();}
//-------- Edit Clear
void __fastcall TfrmEdit::Clear1Click(TObject *Sender){
 char *p;
 if(Application->MessageBox("Clear?","Confirm",MB_OKCANCEL)==ID_OK){
  p=m+st*WX*WY;for(int i=0;i<WX*WY;i++)*(p++)=0;
  PutFloor();}}
//----- Edit Next
void __fastcall TfrmEdit::NextFloor1Click(TObject *Sender)
{if(st<MAX-1){++st;PutFloor();}}
//----- Edit Back
void __fastcall TfrmEdit::Back1Click(TObject *Sender)
{if(st>0){--st;PutFloor();}}
//----- Edit Copy
void __fastcall TfrmEdit::Copy1Click(TObject *Sender)
{cst=st;RefreshCopyStatus();
}
//----- Edit Paste
void __fastcall TfrmEdit::Paste1Click(TObject *Sender)
{char *p,*q;
 if(Application->MessageBox("Paste?","Confirm",MB_OKCANCEL)==ID_OK){
  p=m+st*WX*WY;q=m+cst*WX*WY;for(int i=0;i<WX*WY;i++)*(p++)=*(q++);
  PutFloor();}}
//-------------- Form events
void __fastcall TfrmEdit::FormClose(TObject *Sender, TCloseAction &Action){
/*if(Application->MessageBox("終了?","確認",MB_OKCANCEL) ==ID_CANCEL)Action = caNone;*/
 if(isMod){if(!SavePrompt()){Action=caNone;return;}}
// INI("Left")=IntToStr(Left);INI("Top")=IntToStr(Top);
 li_ini->SaveToFile(fi_ini);delete m;}

//---------------------------------------------------------------------------
void __fastcall TfrmEdit::LoadImage(AnsiString fi){
//---
 }
//----- Drag file
void __fastcall TfrmEdit::WMDROPFILES(TWMDropFiles Msg){
 char buf[256];//int ctrl;
// int cnt=::DragQueryFile((HDROP)Msg.Drop,0xFFFFFFFF,NULL,0);
 ::DragQueryFile((HDROP)Msg.Drop,0,buf,sizeof(buf));
 Image3->Picture->LoadFromFile(StrPas(buf));
// delete m;
 SCX=Image3->Width;SCY=Image3->Height;
 ClientWidth=SCX;ClientHeight=SCY+SZ;
 WX=SCX/SZ;WY=SCY/SZ;SWX=WX;SWY=WY;
/* Image1->Picture->Bitmap=NULL;
 Image1->Width=SCX;Image1->Height=SCY+SZ;*/
// Image3->Width=SCX;Image3->Height=SCY;
/* char *p;int i;
 m=new char[WX*WY*MAX];
 p=m;for(i=0;i<WX*WY*MAX;i++)*(p++)=0;
 st=0;ex=1;ey=0;wx=0;wy=0;cst=-1;
 PatBlt(IM1,0,0,SCX,SCY,BLACKNESS);*/
// PatBlt(IM3,0,0,SCX,SCY,BLACKNESS);
 ::DragFinish((HDROP)Msg.Drop);PutFloor();PutBlocks();}

void __fastcall TfrmEdit::InsertText(void)
{frmPrin->Edit1->Text="";
 if(frmPrin->ShowModal()==mrOk){
 AnsiString st1=frmPrin->Edit1->Text;int i;unsigned char c,*p;
  p=m+st*WX*WY+cy1*WX+cx1;
  for(i=1;i<=st1.Length();i++){
   c=(unsigned char)st1[i];
   *(p++)=c;}
  SetModify();PutFloor();}
}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::mnExportClick(TObject *Sender)
{
 AnsiString st1,st2;unsigned char *p;int i,j;
 p=m+st*WX*WY;st1="";
 for(i=0;i<WY;i++){
  st1=st1+"data ";st2="";
  for(j=0;j<WX;j++){
   st2=st2+IntToHex(*(p++),2);}
  st1=st1+st2+"\n";}
 frmOutput->Memo1->Lines->Text=st1;
 frmOutput->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmEdit::btnLeftClick(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_LEFT,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnRightClick(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_RIGHT,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnUpClick(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_UP,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnDownClick(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_DOWN,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::BitBtn1Click(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_INSERT,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnNextChrClick(TObject *Sender)
{TShiftState a;FormKeyDown(Sender,VK_DELETE,a);}
//---------------------------------------------------------------------------
void __fastcall TfrmEdit::btnSpoitClick(TObject *Sender)
{isSpoit=true;}
//---------------------------------------------------------------------------

void __fastcall TfrmEdit::Timer1Timer(TObject *Sender)
{
 ok=true;Timer1->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmEdit::btnTextClick(TObject *Sender)
{
 isText=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmEdit::Fill1Click(TObject *Sender)
{char *p;
 if(Application->MessageBox("Fill?","Confirm",MB_OKCANCEL)==ID_OK){
  p=m+st*WX*WY;for(int i=0;i<WX*WY;i++)*(p++)=ex+ey*CPL;
  PutFloor();}}
//---------------------------------------------------------------------------

void __fastcall TfrmEdit::ExportCCZ801Click(TObject *Sender)
{
 AnsiString st1,st2;unsigned char *p;int i,j;
 p=m+st*WX*WY;st1="";
 for(i=0;i<WY;i++){
  st2="";
  for(j=0;j<WX;j++){
   if(j)st2=st2+",";
   st2=st2+"#"+IntToHex(*(p++),2);}
  if(i<WY-1)st2=st2+",";
  st1=st1+st2+"\n";}
 frmOutput->Memo1->Lines->Text=st1;
 frmOutput->Show();
}
//---------------------------------------------------------------------------

