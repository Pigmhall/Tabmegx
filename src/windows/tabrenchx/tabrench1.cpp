//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tabrench1.h"
#include "option1.h"
//#include "jpeg.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define SetColor(X,C) X->Canvas->Pen->Color=C;X->Canvas->Brush->Color=C
#define ResetMod() mod=false;mnMod->Caption=""
#define Mod() if(!mod){mnMod->Caption="*";mod=true;}
TForm1 *Form1;

AnsiString pa,fi_ini;
int SCX=600,SZ=37,WX=16,WY=16,BTH=40;
int sx,sy,sx2,sy2,loc;
const PM_PEN=0,PM_PAINT=1,PM_SPOIT=2,PM_ERASE=3,PM_REPLACE=4;
int penMod=0;
bool mod,ok;
bool isPico8;
TColor pencol,drawcol;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 pa=ExtractFilePath(Application->ExeName);
 pencol=clWhite;loc=0;
 li_ini=new TStringList();
// ImgPallete->Picture->Bitmap->PixelFormat=pf8bit;
 if(DirectoryExists(pa+"..\\palette")){isPico8=false;
  ImgPallete->Picture->LoadFromFile(pa+"..\\palette\\palette.bmp");}
  else{isPico8=true;
  ImgPallete->Picture->LoadFromFile(pa+"palette\\pico8.bmp");}
// ImgPallete->AutoSize=false;
 fi_ini=pa+"tabrench.ini";

 LoadIni();
 if(ParamCount()==1){
  WX=StrToInt(ParamStr(1));
  WY=StrToInt(ParamStr(1));}

 ClientWidth=(SZ*WX<37*16)?37*16:SZ*WX;
 ClientHeight=BTH+SZ*WY+ImgPallete->Height;//+PnlImgbtn->Height;
// BitBlt(ImgMain->Canvas->Handle,0,0,ImgPallete->Width,ImgPallete->Height,ImgPallete->Canvas->Handle,0,0,SRCCOPY);
 ImgMain->Width=SZ*WX;
 ImgMain->Height=SZ*WY;
 ImgMain->Top=BTH;
// ImgMain->Picture->Bitmap->Palette=ImgPallete->Picture->Bitmap->Palette;
 ImgPallete->Top=BTH+SZ*WY+1;
// ImgPallete->Width=ClientWidth;
 ImgColor->Width=SZ;ImgColor->Height=SZ;
 ImgColor->Top=BTH+SZ*WY+1;
 ImgColor->Left=ImgPallete->Width+1;
 ImgView->Width=WX;
 ImgView->Height=WY;
 ImgViewB->Width=WX;
 ImgViewB->Height=WY;
 ImgView->Top=BTH+SZ*WY+1;//+ImgColor->Height+2;
 ImgView->Left=ImgColor->Left+ImgColor->Width+1;
// ClientHeight=SZ*WY;
 PatBlt(ImgMain->Canvas->Handle,0,0,SZ*WX,SZ*WY,BLACKNESS);
 PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
 PatBlt(ImgColor->Canvas->Handle,0,0,32,32,WHITENESS);
 ImgView->Width=WX*2;
 ImgView->Height=WY*2;
 ImgMain->Refresh();
 ImgPallete->Refresh();
 RefreshPaletteList();
 OpenDialog1->InitialDir=pa+"bmp";
 SaveDialog1->InitialDir=pa+"bmp";
 for(int i=0;i<32;i++){ImgOr->Canvas->Pixels[i][0]=((i/4)&1)?clRed:clYellow;
  ImgOr->Canvas->Pixels[i][1]=((i/4)&1)?clRed:clYellow;}
// ImgOr->Canvas->Pen->Color=clRed;
// ImgOr->Canvas->Brush->Color=clRed;
//ImgOr->Canvas->Rectangle(0,0,32,2);

 reloadCols();
}

void __fastcall TForm1::reloadCols(void){
 int i;
 for(i=0;i<16;i++){
  cols[i]=ImgPallete->Canvas->Pixels[(ImgPallete->Width/16)*i][0];}}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadIni(void){
 if(FileExists(fi_ini)){li_ini->LoadFromFile(fi_ini);
  WX=StrToInt(INI("Width"));
  WY=StrToInt(INI("Height"));
  SZ=StrToInt(INI("DotSize"));
 }else{INI("Save256")="1";}}

void __fastcall TForm1::SaveIni(void){
 li_ini->SaveToFile(fi_ini);}

//--- pallete
void __fastcall TForm1::ImgPalleteMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 pencol=ImgPallete->Canvas->Pixels[X][Y];
 ImgColor->Canvas->Pen->Color=pencol;
 ImgColor->Canvas->Brush->Color=pencol;
 ImgColor->Canvas->Rectangle(0,0,SZ,SZ);
 ImgColor->Refresh();
}
//---------------------------------------------------------------------------
int BubSort(int x[ ],int n)
{int i,j,tmp;
 for(i=0;i<n-1;i++){
  for(j=n-1;j>i;j--){
   if(x[j-1]>x[j]){  /* ‘O‚Ì—v‘f‚Ì•û‚ª‘å‚«‚©‚Á‚½‚ç */
    tmp=x[j];x[j]=x[j-1];x[j-1]=tmp;
   }}}
}

void __fastcall TForm1::DrawPixel(int X,int Y){
 SetColor(ImgMain,drawcol);
 sx=(X/SZ)*SZ;sy=(Y/SZ)*SZ;
 ImgView->Canvas->Pixels[X/SZ][Y/SZ]=drawcol;
 ImgMain->Refresh();
 ImgView->Refresh();
 ImgMain->Canvas->Rectangle(sx,sy,sx+SZ,sy+SZ);
 sx2=X/SZ;sy2=Y/SZ;

 int i,j,k,cnum,d[3];bool ex;
 TColor c;
 k=0;
 for(i=0;i<WX;i++){
  c=ImgView->Canvas->Pixels[i][Y/SZ];
  if(c&&k<3){cnum=0;
   for(j=0;j<16;j++){if(cols[j]==c)cnum=j;}
   if(cnum){ex=false;
    for(j=0;j<k;j++){if(d[j]==cnum)ex=true;}
    if(!ex){
     for(j=0;j<16;j++){if(cols[j]==c)d[k]=j;}
     ++k;}}}}
 BubSort(d,3);
 if(k>1){ImgOr->Visible=true;
  ImgOr->Top=ImgPallete->Top;
  ImgOr->Left=(d[0]|d[1])*ImgPallete->Width/16;}
 else ImgOr->Visible=false;

}

//-----
void __fastcall TForm1::ImgMainMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
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
  TColor c=ImgMain->Canvas->Pixels[X][Y];
   drawcol=clBlack;
   DrawPixel(X,Y);}
 if(penMod==PM_PAINT){
  SetColor(ImgView,pencol);
  ImgView->Canvas->FloodFill(X/SZ,Y/SZ,ImgMain->Canvas->Pixels[X][Y],fsSurface);
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
{if(loc)return;if(penMod!=PM_PEN&&penMod!=PM_ERASE)return;
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
// if(Application->MessageBox("Really?","New",MB_YESNO)==ID_YES){

 PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
 ImgView->Refresh();
 SaveDialog1->FileName="";
// Timer1->Enabled=true;
 Caption="tabrench";
 ResetMod();
 ViewToMain();//}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ViewToMain(void){
 int i,j;
 TColor c;
 for(i=0;i<WY;i++){
  for(j=0;j<WX;j++){
   SetColor(ImgMain,ImgView->Canvas->Pixels[j][i]);
   ImgMain->Canvas->Rectangle(j*SZ,i*SZ,j*SZ+SZ,i*SZ+SZ);}}
 ImgView->Refresh();
 ImgMain->Refresh();
}

//---
void __fastcall TForm1::LoadImage(AnsiString fi){
 mnMod->Caption="";mod=false;
 ImgView->Picture->LoadFromFile(fi);
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
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveImage(AnsiString fi){
  Graphics::TBitmap *bmp = new Graphics::TBitmap;
  bmp->Assign(ImgView->Picture->Graphic);
if(INI("Save256")=="1")bmp->PixelFormat=pf8bit;
  bmp->SaveToFile(fi);
  delete bmp;
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
 FrmOption->EdtWidth->Text=IntToStr(WX);
 FrmOption->EdtHeight->Text=IntToStr(WY);
 FrmOption->EdtDotSize->Text=IntToStr(SZ);
 FrmOption->RefreshWindow();
 FrmOption->chk256->Checked=(INI("Save256")=="1")?true:false;
 if(FrmOption->ShowModal()==mrOk){
  try{
  INI("Width")=StrToInt(FrmOption->EdtWidth->Text);
  INI("Height")=StrToInt(FrmOption->EdtHeight->Text);
  INI("DotSize")=StrToInt(FrmOption->EdtDotSize->Text);
  INI("Save256")=(FrmOption->chk256->Checked)?"1":"0";
  SaveIni();
  Application->MessageBox("Please reboot.","Option",MB_OK);
  }
  catch(...){
   Application->MessageBox("Error!","Option",MB_OK|MB_ICONERROR);
 }}
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

void __fastcall TForm1::Button1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnPenClick(TObject *Sender)
{
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
{
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
{
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
{
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
void __fastcall TForm1::BtnUpClick(TObject *Sender)
{
 Backup();
 BitBlt(ImgView->Canvas->Handle,0,0,WX,WY-1,ImgView->Canvas->Handle,0,1,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,WY-1,WX,1,ImgViewB->Canvas->Handle,0,0,SRCCOPY);
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnRightClick(TObject *Sender)
{
 Backup();
 BitBlt(ImgView->Canvas->Handle,1,0,WX-1,WY,ImgView->Canvas->Handle,0,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,0,1,WY,ImgViewB->Canvas->Handle,WX-1,0,SRCCOPY);
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnDownClick(TObject *Sender)
{
 Backup();
 BitBlt(ImgView->Canvas->Handle,0,1,WX,WY-1,ImgView->Canvas->Handle,0,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,0,0,WX,1,ImgViewB->Canvas->Handle,0,WY-1,SRCCOPY);
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnLeftClick(TObject *Sender)
{
 Backup();
 BitBlt(ImgView->Canvas->Handle,0,0,WX-1,WY,ImgView->Canvas->Handle,1,0,SRCCOPY);
 BitBlt(ImgView->Canvas->Handle,WX-1,0,1,WY,ImgViewB->Canvas->Handle,0,0,SRCCOPY);
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnMirrorClick(TObject *Sender)
{int i,j;
 Backup();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,j,i,1,1,ImgViewB->Canvas->Handle,WX-j-1,i,SRCCOPY);}
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButMirror2Click(TObject *Sender)
{int i,j;
 Backup();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,i,j,1,1,ImgViewB->Canvas->Handle,i,WY-j-1,SRCCOPY);}
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::butRotateClick(TObject *Sender)
{int i,j;
 Backup();
 for(i=0;i<WY;i++)for(j=0;j<WX;j++){
  BitBlt(ImgView->Canvas->Handle,j,i,1,1,ImgViewB->Canvas->Handle,WY-1-i,j,SRCCOPY);}
 Mod();
 ViewToMain();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(!ModifyQuestion()){Action=caNone;}
}
//---------------------------------------------------------------------------

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

void __fastcall TForm1::ImgColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{BtnSpoitClick(Sender);}
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

void __fastcall TForm1::Clear1Click(TObject *Sender)
{
// if(Application->MessageBox("Clear?","clear",MB_YESNO)==ID_YES){
  Backup();
  PatBlt(ImgView->Canvas->Handle,0,0,WX,WY,BLACKNESS);
  ViewToMain();
// }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshPaletteList(void){
 int RC,p;
 TSearchRec SearchRec;
 AnsiString ss;
 AnsiString st1=(isPico8)?(pa+"palette"):(pa+"..\\palette");

 RC=FindFirst(st1+"\\*.bmp",faAnyFile,SearchRec);
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
 reloadCols();
}

void __fastcall TForm1::mngReplaceClick(TObject *Sender)
{
 Caption="Replace color";Timer1->Enabled=true;
 ok=false;mngReplace->Checked=true;
 penMod=PM_REPLACE;
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GeneratePico8Gfx(void){
}

void __fastcall TForm1::Generatepico8gfx1Click(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------

