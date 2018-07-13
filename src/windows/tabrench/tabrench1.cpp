//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tabrench1.h"
#include "option1.h"
//#include "jpeg.hpp"
#include "imgctl.h"
#include "color.h"
#include "tbnew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define SetColor(X,C) X->Canvas->Pen->Color=C;X->Canvas->Brush->Color=C
#define ResetMod() mod=false;mnMod->Caption=""
#define Mod() if(!mod){mnMod->Caption="*";mod=true;}
TForm1 *Form1;

AnsiString pa,fi_ini;
int SCX=600,SZ=37,WX=32,WY=32,WX2=16,WY2=16,BTH=40,BTW=48;
int sx,sy,sx2,sy2,cx,cy,ovx,ovy,loc;
const PM_PEN=0,PM_PAINT=1,PM_SPOIT=2,PM_ERASE=3,PM_REPLACE=4;
int penMod=0;
bool mod,ok;

TColor pencol,drawcol;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 pa=ExtractFilePath(Application->ExeName);
 pencol=clWhite;loc=0;
 li_ini=new TStringList();
// ImgPallete->Picture->Bitmap->PixelFormat=pf8bit;
 ImgPallete->Picture->LoadFromFile(pa+"col256_1.bmp");
 fi_ini=pa+"tabrench.ini";
 LoadIni();
 Top=16;Left=0;

 ClientHeight=BTH+SZ*WY2+ImgPallete->Height;
// BitBlt(ImgMain->Canvas->Handle,0,0,ImgPallete->Width,ImgPallete->Height,ImgPallete->Canvas->Handle,0,0,SRCCOPY);
 ImgMain->Width=SZ*WX2;
 ImgMain->Height=SZ*WY2;
 ImgMain->Top=BTH;
// ImgMain->Picture->Bitmap->Palette=ImgPallete->Picture->Bitmap->Palette;
 ImgPallete->Top=BTH+SZ*WY2+1;
 ImgColor->Width=SZ;ImgColor->Height=SZ;
 ImgColor->Top=BTH+SZ*WY2+1;
 ImgColor->Left=ImgPallete->Width+1;
 ImgView->Width=WX;
 ImgView->Height=WY;
 ImgViewB->Width=WX;
 ImgViewB->Height=WY;
 ImgView->Top=BTH+SZ*WY2+ImgColor->Height+2;
 ImgView->Left=ImgPallete->Width+1;
 ClientWidth=SZ*WX2;
 SetButtonSize(btnNew,BTW*0);
 SetButtonSize(btnOpen,BTW*1);
 SetButtonSize(btnSave,BTW*2);
 SetButtonSize(btnPaint,BTW*3+8);
 SetButtonSize(btnSpoit,BTW*4+8);
 SetButtonSize(btnLeft,BTW*5+16);
 SetButtonSize(btnUp,BTW*6+16);
 SetButtonSize(btnDown,BTW*7+16);
 SetButtonSize(btnRight,BTW*8+16);
 SetButtonSize(btnNextChr,BTW*9+24);
 if(BTW*9+24+BTW>ClientWidth)ClientWidth=BTW*9+24+BTW;
// Resize();
 // BitBlt(ImgMain->Canvas->Handle,0,0,ImgPallete->Width,ImgPallete->Height,ImgPallete->Canvas->Handle,0,0,SRCCOPY);
// ClientHeight=SZ*WY;
 PatBlt(ImgMain->Canvas->Handle,0,0,SZ*WX2,SZ*WY2,BLACKNESS);
 PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
 PatBlt(ImgColor->Canvas->Handle,0,0,32,32,WHITENESS);
 cx=0;cy=0;
 ImgView->Width=WX*2;
 ImgView->Height=WY*2;
 ImgCurV->Canvas->Pen->Color=clRed;
 ImgCurV->Canvas->Brush->Color=clRed;
 ImgCurH->Canvas->Pen->Color=clRed;
 ImgCurH->Canvas->Brush->Color=clRed;
 ImgCurV->Canvas->Rectangle(0,0,2,4);
 ImgCurH->Canvas->Rectangle(0,0,4,2);
 ImgMain->Refresh();
 ImgPallete->Refresh();
 ViewToMain();ResetMod();
 RefreshPaletteList();
 OpenDialog1->InitialDir=pa+"bmp";
 SaveDialog1->InitialDir=pa+"bmp";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetButtonSize(TButton *btn,int l){
 btn->Width=BTW;
 btn->Height=BTH;
 btn->Left=l;}


void __fastcall TForm1::LoadIni(void){
 if(FileExists(fi_ini)){li_ini->LoadFromFile(fi_ini);
  try{WX=StrToInt(INI("Width"));
  WY=StrToInt(INI("Height"));
  WX2=StrToInt(INI("Width2"));
  WY2=StrToInt(INI("Height2"));
  SZ=StrToInt(INI("DotSize"));
  BTW=StrToInt(INI("ButtonW"));
  BTH=StrToInt(INI("ButtonH"));
  }catch(...){}
 }else{INI("Save256")="0";}}

void __fastcall TForm1::SaveIni(void){
 li_ini->SaveToFile(fi_ini);}

//--- pallete
void __fastcall TForm1::ChangeColor(TColor c){
 pencol=c;
 ImgColor->Canvas->Pen->Color=pencol;
 ImgColor->Canvas->Brush->Color=pencol;
 ImgColor->Canvas->Rectangle(0,0,SZ,SZ);
 ImgColor->Refresh();}

void __fastcall TForm1::ImgPalleteMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{ChangeColor(ImgPallete->Canvas->Pixels[X][Y]);}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawPixel(int X,int Y){
//Caption="DO:"+IntToStr(drawcol);
  SetColor(ImgMain,drawcol);
  sx=(X/SZ)*SZ;sy=(Y/SZ)*SZ;
  ImgView->Canvas->Pixels[cx+X/SZ][cy+Y/SZ]=drawcol;
  ImgMain->Refresh();
  ImgView->Refresh();
  ImgMain->Canvas->Rectangle(sx,sy,sx+SZ,sy+SZ);
  sx2=X/SZ;sy2=Y/SZ;
}

//-----
void __fastcall TForm1::ImgMainMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{if(X>=(WX-cx)*SZ||Y>=(WY-cy)*SZ)return;
 if(loc)return;Backup();
 if(Shift.Contains(ssAlt))goto GO_SPOIT;
 Mod();
 if(penMod==PM_PEN){ok=true;
  TColor c=ImgMain->Canvas->Pixels[X][Y];
  if(c!=pencol){
   drawcol=pencol;}
   else{
   drawcol=pencol;
    }
  DrawPixel(X,Y);}
 if(penMod==PM_ERASE||Shift.Contains(ssRight)){ok=true;
 //  TColor c=ImgMain->Canvas->Pixels[X][Y];
   drawcol=clBlack;
   DrawPixel(X,Y);}
 if(penMod==PM_PAINT){
  SetColor(ImgView,pencol);
  ImgView->Canvas->FloodFill(cx+X/SZ,cy+Y/SZ,ImgMain->Canvas->Pixels[X][Y],fsSurface);
  ViewToMain();
  ImgColor->Refresh();BtnPenClick(Sender);
 }
 if(penMod==PM_SPOIT){GO_SPOIT:
  pencol=ImgMain->Canvas->Pixels[X][Y];
  ImgColor->Canvas->Pen->Color=pencol;
  ImgColor->Canvas->Brush->Color=pencol;
  ImgColor->Canvas->Rectangle(0,0,SZ,SZ);
  ImgColor->Refresh();BtnPenClick(Sender);
  }
 if(penMod==PM_REPLACE){
  TColor c=ImgMain->Canvas->Pixels[X][Y];int i,j;
  for(i=0;i<WY;i++)for(j=0;j<WX;j++){
   if(ImgView->Canvas->Pixels[j][i]==c)ImgView->Canvas->Pixels[j][i]=pencol;}
   ViewToMain();
   BtnPenClick(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImgMainMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{/*if(loc)return;
  if(X>=(WX-cx)*SZ||Y>=(WY-cy)*SZ)return;
 if(penMod!=PM_PEN&&penMod!=PM_ERASE)return;
 sx=(X/SZ);sy=(Y/SZ);
 if(ok&&Shift.Contains(ssLeft)&&(sx!=sx2||sy!=sy2)){
//ShowMessage(IntToStr(sx)+";"+IntToStr(sy));
  DrawPixel(X,Y);
 } */

if(loc)return;if(penMod!=PM_PEN&&penMod!=PM_ERASE)return;
 sx=(X/SZ);sy=(Y/SZ);
 if(ok&&(Shift.Contains(ssRight)||Shift.Contains(ssLeft))&&(sx!=sx2||sy!=sy2)){
  DrawPixel(X,Y);
 }
 }
//---------------------------------------------------------------------------
bool __fastcall TForm1::ModifyQuestion(void){
 int a;
 if(mod){
  if((a=Application->MessageBox("Save current image?","Prompt",MB_YESNOCANCEL))==ID_YES)BtnSaveClick(NULL);
  if(a==ID_CANCEL)return false;
  }
 return true;
}
void __fastcall TForm1::BtnNewClick(TObject *Sender)
{
 if(!ModifyQuestion())return;
 if(((TMenuItem*)Sender)->Tag==1){
/*   frmNew->edtW->Text=IntToStr(WX);
   frmNew->edtH->Text=IntToStr(WY);*/
   frmNew->udW->Position=WX;
   frmNew->udH->Position=WY;
  if(frmNew->ShowModal()==mrOk){
   WX=StrToInt(frmNew->edtW->Text);
   WY=StrToInt(frmNew->edtH->Text);}
  ImgView->Picture->Bitmap=NULL;
  ImgViewB->Picture->Bitmap=NULL;
  ImgView->Width=WX;ImgView->Height=WY;
  ImgViewB->Width=WX;ImgViewB->Height=WY;
  PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
  ImgView->Width=WX*2;
  ImgView->Height=WY*2;}

  PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
  ImgView->Refresh();
  SaveDialog1->FileName="";
// Timer1->Enabled=true;
  Caption="tabrench";
  cx=0;cy=0;
  ResetMod();
  ViewToMain();//}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ViewToMain(void){
 int i,j;
 TColor c;
 ImgCurH->Left=ImgView->Left-4;
 ImgCurH->Top=ImgView->Top+cy*2;
 ImgCurV->Left=ImgView->Left+cx*2;
 ImgCurV->Top=ImgView->Top-4;
 for(i=0;i<WY2;i++){
  for(j=0;j<WX2;j++){
   SetColor(ImgMain,ImgView->Canvas->Pixels[cx+j][cy+i]);
   ImgMain->Canvas->Rectangle(j*SZ,i*SZ,j*SZ+SZ,i*SZ+SZ);}}
 ImgMain->Refresh();
 ImgView->Refresh();
}

//---
void __fastcall TForm1::LoadImage(AnsiString fi){
 mnMod->Caption="";mod=false;
 ImgView->Picture->Bitmap=NULL;
 ImgViewB->Picture->Bitmap=NULL;
 ImgView->AutoSize=true;
 ImgView->Picture->LoadFromFile(fi);
 ImgView->AutoSize=false;
 WX=ImgView->Width;WY=ImgView->Height;
 ImgViewB->Width=WX;ImgViewB->Height=WY;
 ImgView->Width=WX*2;
 ImgView->Height=WY*2;
 if(cx>WX-WX2){cx=WX-WX2;}
 if(cy>WY-WY2){cx=WY-WY2;}
 ImgView->Refresh();
 SaveDialog1->FileName=fi;
 Caption="tabrench - "+ExtractFileName(fi);
 ViewToMain();}

void __fastcall TForm1::BtnOpenClick(TObject *Sender)
{if(!ModifyQuestion())return;
 if(OpenDialog1->Execute()){
  LoadImage(OpenDialog1->FileName);
  RefreshChrs();loc=1;Timer1->Enabled=true;}
}
//--------- Save Image
BOOL MyDIBtoPNG(HDIBC hDIB, LPCSTR lpPngFile){
 PNGOPT po;
 PALTRANS paltrns;
 po.dwFlag=0;		/* 初期化 */
 //圧縮レベルを 0 ～ 9 で設定します。設定しなかった場合はデフォルトの圧縮率になります。なお、JPEGと違い、画質には影響しません。
 po.dwFlag |= POF_COMPLEVEL;	/* フラグを立てる */
 po.wCompLevel = 9;
 po.dwFlag |= POF_TRNSCOLOR;
 po.clrTrans=RGB(0,0,0);	/* 紫をセット */
 po.dwReserved1=0;
 po.dwReserved2=0;
 return DIBtoPNGex(lpPngFile,hDIB,&po);}

void __fastcall TForm1::SaveImage(AnsiString fi){
 Graphics::TBitmap *bmp = new Graphics::TBitmap;
 bmp->Assign(ImgView->Picture->Graphic);
 if(INI("Save256")=="1")bmp->PixelFormat=pf8bit;
 bmp->SaveToFile(fi);
 delete bmp;
 if(INI("Png")=="1"){
  AnsiString fi_png=fi;
  fi_png=ChangeFileExt(fi,".png");
 // BOOL bRes;//=FALSE;
  HDIB hDIB;//NULL;
  hDIB=ToDIB(fi.c_str());
  if(hDIB!=NULL){
   /*bRes=*/MyDIBtoPNG(hDIB,fi_png.c_str());
   DeleteDIB(hDIB);}}

/*  TImage *image1;Graphics::TBitmap *BM;
  TJPEGImage *JP;
  image1=new TImage(Form1);
  image1->Picture=ImgView->Picture;
  JP=new TJPEGImage();
  BM=new Graphics::TBitmap;
  JP->Assign(image1->Picture->Graphic);
  image1->Picture->Graphic=JP;
  JP->Compress();
  JP->PixelFormat=pf8bit;
  BM->Assign(image1->Picture->Graphic);
  image1->Canvas->Draw(0,0,BM);
  image1->Picture->SaveToFile(fi);*/

  Caption="Saved as "+ExtractFileName(fi);Timer1->Enabled=true;
  ResetMod();
}

void __fastcall TForm1::BtnSaveasClick(TObject *Sender)
{
 if(SaveDialog1->Execute()){
  SaveImage(SaveDialog1->FileName);
//  ImgView->Picture->SaveToFile(SaveDialog1->FileName);
//Caption="tabrench - "+ExtractFileName(SaveDialog1->FileName);
  RefreshChrs();
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnSaveClick(TObject *Sender)
{//TDateTime st=Now();
AnsiString fi;
 if(SaveDialog1->FileName==""){
  int a=0;
  do{++a;fi=pa+"bmp\\"+IntToStr(a)+".bmp";
  }while(FileExists(fi));
  SaveDialog1->FileName=fi;
  SaveImage(fi);
  //ImgView->Picture->SaveToFile(fi);
  //BtnSaveasClick(Sender);
  }
 else{SaveImage(SaveDialog1->FileName);}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
 Caption="tabrench - "+ExtractFileName(SaveDialog1->FileName);
 Timer1->Enabled=false;loc=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnOptionClick(TObject *Sender)
{
 FrmOption->EdtWidth2->Text=IntToStr(WX2);
 FrmOption->EdtHeight2->Text=IntToStr(WY2);
 FrmOption->EdtWidth->Text=IntToStr(WX);
 FrmOption->EdtHeight->Text=IntToStr(WY);
 FrmOption->EdtDotSize->Text=IntToStr(SZ);
 FrmOption->EdtButtonW->Text=IntToStr(BTW);
 FrmOption->EdtButtonH->Text=IntToStr(BTH);
 FrmOption->RefreshWindow();
 FrmOption->chk256->Checked=(INI("Save256")=="1")?true:false;
 FrmOption->chkPng->Checked=(INI("Png")=="1")?true:false;
 if(FrmOption->ShowModal()==mrOk){
  try{
  INI("Width")=StrToInt(FrmOption->EdtWidth->Text);
  INI("Height")=StrToInt(FrmOption->EdtHeight->Text);
  INI("Width2")=StrToInt(FrmOption->EdtWidth2->Text);
  INI("Height2")=StrToInt(FrmOption->EdtHeight2->Text);
  INI("DotSize")=StrToInt(FrmOption->EdtDotSize->Text);
  INI("Save256")=(FrmOption->chk256->Checked)?"1":"0";
  INI("Png")=(FrmOption->chkPng->Checked)?"1":"0";
  INI("ButtonW")=StrToInt(FrmOption->EdtButtonW->Text);
  INI("ButtonH")=StrToInt(FrmOption->EdtButtonH->Text);
  SaveIni();
  Application->MessageBox("please reboot.","Option",MB_OK);
  }
  catch(...){
   Application->MessageBox("failed!","Option",MB_OK|MB_ICONERROR);
 }}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnPenClick(TObject *Sender)
{//mnPen->Caption="Pen";
/* BtnPen->Font->Style=TFontStyles();
 BtnPaint->Font->Style=TFontStyles();
 BtnSpoit->Font->Style=TFontStyles();
 BtnErase->Font->Style=TFontStyles();
 BtnPen->Font->Style=TFontStyles()<<fsBold;*/
 mngPen->Checked=true;
 penMod=PM_PEN;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnPaintClick(TObject *Sender)
{//mnPen->Caption="Paint";
/* BtnPen->Font->Style=TFontStyles();
 BtnPaint->Font->Style=TFontStyles();
 BtnSpoit->Font->Style=TFontStyles();
 BtnErase->Font->Style=TFontStyles();
 BtnPaint->Font->Style=TFontStyles()<<fsBold;*/
 ok=false;mngPaint->Checked=true;
 Caption="Paint";Timer1->Enabled=true;
 penMod=PM_PAINT;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnSpoitClick(TObject *Sender)
{//mnPen->Caption="Spoit";//Caption="";
/* BtnPen->Font->Style=TFontStyles();
 BtnPaint->Font->Style=TFontStyles();
 BtnSpoit->Font->Style=TFontStyles();
 BtnErase->Font->Style=TFontStyles();
 BtnSpoit->Font->Style=TFontStyles()<<fsBold;*/
 Caption="Spoit";Timer1->Enabled=true;
 ok=false;mngSpoit->Checked=true;
 penMod=PM_SPOIT;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnEraseClick(TObject *Sender)
{//mnPen->Caption="Erase";
/* BtnPen->Font->Style=TFontStyles();
 BtnPaint->Font->Style=TFontStyles();
 BtnSpoit->Font->Style=TFontStyles();
 BtnErase->Font->Style=TFontStyles();
 BtnErase->Font->Style=TFontStyles()<<fsBold;*/
 mngErase->Checked=true;
 penMod=PM_ERASE;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Backup(void){
 BitBlt(ImgViewB->Canvas->Handle,0,0,WX,WY,ImgView->Canvas->Handle,0,0,SRCCOPY);}

void __fastcall TForm1::BtnUndoClick(TObject *Sender)
{
 BitBlt(ImgView->Canvas->Handle,0,0,WX,WY,ImgViewB->Canvas->Handle,0,0,SRCCOPY);
 ImgView->Refresh();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImgViewMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if(Shift.Contains(ssLeft)){
  cx+=X-ovx;
  cy+=Y-ovy;
  if(cx<0)cx=0;if(cx>WX-WX2)cx=WX-WX2;
  if(cy<0)cy=0;if(cy>WY-WY2)cy=WY-WY2;
  ViewToMain();
  ovx=X;ovy=Y;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ImgViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 ovx=X;ovy=Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshChrs(void){
 AnsiString di=ExtractFilePath(SaveDialog1->FileName);
 int RC,i;bool num;
 int a=mnChrs->Count;for(i=0;i<a;i++){mnChrs->Delete(0);}
 TSearchRec SearchRec;
 AnsiString hd="",fi=ExtractFileName(SaveDialog1->FileName);
 i=1;
 if(fi[i]>='0'&&fi[i]<='9'){num=true;
  while(fi[i]>='0'&&fi[i]<='9'){hd=hd+fi[i];++i;}}
 else{num=false;
  while((fi[i]>='a'&&fi[i]<='z')||fi[i]>='A'&&fi[i]<='Z'){hd=hd+fi[i];++i;}}
 TStringList *li_temp=new TStringList();

 RC=FindFirst(di+"*.bmp",faAnyFile,SearchRec);
 while(RC==0){
  if(SearchRec.Name.AnsiPos(hd)==1&&(!num||SearchRec.Name[hd.Length()+1]<'0'||SearchRec.Name[hd.Length()+1]>'9'))li_temp->Add(SearchRec.Name);
   RC=FindNext(SearchRec);}
//  finally
 FindClose(SearchRec);
 li_temp->Sort();
 for(i=0;i<li_temp->Count;i++){
  TMenuItem *NewItem;
  NewItem=new TMenuItem(mnChrs);
  NewItem->Caption=li_temp->Strings[i];
  NewItem->OnClick=mnOpenChr;
  mnChrs->Add(NewItem);}
 delete li_temp;
}

void __fastcall TForm1::mnOpenChr(TObject *Sender){
 if(mod){BtnSaveClick(Sender);}
 AnsiString di=ExtractFilePath(SaveDialog1->FileName);
// ShowMessage(di+((TMenuItem*)Sender)->Caption);
 LoadImage(di+((TMenuItem*)Sender)->Caption);
}

void __fastcall TForm1::ImgColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 frmColor->tbB->Position=pencol/65536;
 frmColor->tbG->Position=(pencol/256)&255;
 frmColor->tbR->Position=pencol&255;
 frmColor->RefreshPal();
 if(frmColor->ShowModal()==mrOk){
  ChangeColor(frmColor->Image1->Canvas->Pixels[0][0]);}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnUpClick(TObject *Wender)
{if(cy>0){cy=cy-4;ViewToMain();}}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnDownClick(TObject *Wender)
{if(cy<WY-WY2){cy=cy+4;ViewToMain();}}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnLeftClick(TObject *Wender)
{if(cx>0){cx=cx-4;ViewToMain();}}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnRightClick(TObject *Wender)
{if(cx<WX-WX2){cx=cx+4;ViewToMain();}}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(!ModifyQuestion()){Action=caNone;}
}

void __fastcall TForm1::btnNextChrClick(TObject *Sender)
{
 int i,a=mnChrs->Count;
 if(!a)return;
 AnsiString fi=ExtractFileName(SaveDialog1->FileName);
 for(i=0;i<a;i++){
  if(mnChrs->Items[i]->Caption==fi){
   mnOpenChr(mnChrs->Items[(i==a-1)?0:i+1]);}}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnShiftUpClick(TObject *Sender)
{
 Backup();Mod();
 BitBlt(ImgView->Canvas->Handle,0,0,WX,WY-1,ImgView->Canvas->Handle,0,1,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,WY-1,WX,1,ImgViewB->Canvas->Handle,0,0,SRCCOPY);
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnShiftRightClick(TObject *Sender)
{
 Backup();Mod();
 BitBlt(ImgView->Canvas->Handle,1,0,WX-1,WY,ImgView->Canvas->Handle,0,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,0,1,WY,ImgViewB->Canvas->Handle,WX-1,0,SRCCOPY);
 ViewToMain();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mnShiftDownClick(TObject *Sender)
{
 Backup();Mod();
 BitBlt(ImgView->Canvas->Handle,0,1,WX,WY-1,ImgView->Canvas->Handle,0,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,0,WX,1,ImgViewB->Canvas->Handle,0,WY-1,SRCCOPY);
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnShiftLeftClick(TObject *Sender)
{
 Backup();Mod();
 BitBlt(ImgView->Canvas->Handle,0,0,WX-1,WY,ImgView->Canvas->Handle,1,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,WX-1,0,1,WY,ImgViewB->Canvas->Handle,0,0,SRCCOPY);
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnMirrorVClick(TObject *Sender)
{int i,j;
 Backup();Mod();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,j,i,1,1,ImgViewB->Canvas->Handle,WX-j-1,i,SRCCOPY);}
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::mnMirrorHClick(TObject *Sender)
{int i,j;
 Backup();Mod();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,i,j,1,1,ImgViewB->Canvas->Handle,i,WY-j-1,SRCCOPY);}
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rotate1Click(TObject *Sender)
{
int i,j;
 Backup();Mod();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,j,i,1,1,ImgViewB->Canvas->Handle,WY-1-i,j,SRCCOPY);}
 ViewToMain();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IncrementalSave1Click(TObject *Sender)
{
 AnsiString fi=SaveDialog1->FileName,fi2;
 if(fi!=""){
  int a=fi.AnsiPos(".bmp");
  char c=fi[a-1];
  if(c>='0'&&c<='9'){fi=fi.SubString(1,a-1)+"a.bmp";}
  else if(c>='a'&&a<='y'){
   fi[a-1]=c+1;}
  else goto SKIP;
//  ModifyQuestion();
  if(FileExists(fi)){
   if(Application->MessageBox((fi+" exists").c_str(),"overwrite?",MB_YESNO)!=ID_YES)return;}
  SaveDialog1->FileName=fi;
  SaveImage(fi);RefreshChrs();return;
   }
 SKIP:
 Application->MessageBox("Can't save++","Error",MB_OK);

}
//---------------------------------------------------------------------------
//void __fastcall TForm1::Resize(void){}
void __fastcall TForm1::Clear1Click(TObject *Sender)
{
  Backup();
  PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
  ViewToMain();
}
//---------------------------------------------------------------------------
// ImgPallete->Picture->Bitmap=NULL;
// ImgPallete->Picture->LoadFromFile(pa+"..\\palette\\palette.bmp");
//---------------------------------------------------------------------------

void __fastcall TForm1::mnColor256Click(TObject *Sender)
{
 ImgPallete->Picture->Bitmap=NULL;
 ImgPallete->Picture->LoadFromFile(pa+"col256_"+IntToStr(((TMenuItem*)Sender)->Tag)+".bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshPaletteList(void){
 int RC,p;
 TSearchRec SearchRec;
 AnsiString ss;
 RC=FindFirst(pa+"..\\palette\\*.bmp",faAnyFile,SearchRec);
 while(RC==0){
  ss=SearchRec.Name;
  TMenuItem *NewItem;
  NewItem=new TMenuItem(mnColor16);
  NewItem->Caption=ss.SubString(1,ss.Length()-4);
  NewItem->OnClick=mnChangePalette;
  mnColor16->Add(NewItem);
  RC=FindNext(SearchRec);}
 FindClose(SearchRec);
}

void __fastcall TForm1::mnChangePalette(TObject *Sender){
 ImgPallete->Picture->Bitmap=NULL;
 ImgPallete->Picture->LoadFromFile(pa+"..\\palette\\"+((TMenuItem*)Sender)->Caption+".bmp");
}

void __fastcall TForm1::mngReplaceClick(TObject *Sender)
{
 Caption="Replace color";Timer1->Enabled=true;
 ok=false;mngReplace->Checked=true;
 penMod=PM_REPLACE;
}
//---------------------------------------------------------------------------


