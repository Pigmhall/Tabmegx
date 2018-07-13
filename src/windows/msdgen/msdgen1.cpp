//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "msdgen1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TColor cols[16],cols256[256];
int mo;AnsiString ext,pa;bool isLock;
char colerr;
const CE_NOERR=0,CE_NOTFOUND=1,CE_3RDCOLOR=2,CE_MANYCOLOR=3;
static char *cestr[]={"no error",
"color code not found",
"3rd color is not or'ing color",
"too many colors"};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{pa=ExtractFilePath(Application->ExeName);
 Image2->Picture->LoadFromFile(pa+"..\\palette\\palette.bmp");
 Image3->Picture->LoadFromFile(pa+"color256.bmp");
 reloadCols();
 Image2->AutoSize=false;
 Image2->Width=256;Image2->Height=16;
 for(int i=0;i<256;i++){
  cols256[i]=Image3->Canvas->Pixels[i][0];}

 if(ParamCount()>=1){
  AnsiString st=ParamStr(1);
//  DriveComboBox1->Drive=ExtractFileDrive(st);
  DirectoryListBox1->Directory=st;/*ExtractFileDir(st);*/}
 ext=".bmp";
 if(ParamCount()>=2){
  AnsiString st=ParamStr(2);
  if(st=="1"){rbSprite->Checked=true;}
  else if(st=="2"){rbCharacter->Checked=true;}
  else if(st=="3"){rbGraphic->Checked=true;}
DragAcceptFiles(Handle,True);
//  DriveComboBox1->Drive=ExtractFileDrive(st);
/*ExtractFileDir(st);*/}

 if(ParamCount()>=3){
  AnsiString st=ParamStr(3);
  if(st=="1"){rbBasic->Checked=true;}
  else if(st=="2"){rbCcz80->Checked=true;}
  else if(st=="3"){rbQq->Checked=true;}
  else if(st=="4"){rbQq->Checked=true;FileList1->Mask="*.png";ext=".png";}
//  DriveComboBox1->Drive=ExtractFileDrive(st);
/*ExtractFileDir(st);*/}
isLock=false;
FileRefresh();
 SendMessage(FileListBox1->Handle,WM_KEYDOWN,VK_END,1);

 int RC,p;
 TSearchRec SearchRec;
 AnsiString ss;
 RC=FindFirst(pa+"..\\palette\\*.bmp",faAnyFile,SearchRec);
 ComboBox1->Items->Clear();
 while(RC==0){
  ss=SearchRec.Name;
  ComboBox1->Items->Add(ss.SubString(1,ss.Length()-4));
  if(ss=="palette.bmp")ComboBox1->ItemIndex=ComboBox1->Items->Count-1;
  RC=FindNext(SearchRec);}
//  finally
 FindClose(SearchRec);

  }

void __fastcall TForm1::reloadCols(void){
 int i;
 for(i=0;i<16;i++){
  cols[i]=Image2->Canvas->Pixels[(Image2->Width/16)*i][0];}}

//---------------------------------------------------------------------------
int binToInt(char *ptr)
{
    unsigned int val = 0;
    while( *ptr != '\0' ) {
        switch( *ptr++ ) {
            case '0':
                val *= 2;
                break;
            case '1':
                val = val * 2 + 1;
                break;
        }
    }
    return val;
}
//----
int mscol(TColor c){
 int i;
 for(i=0;i<16;i++){
  if(c==cols[i])return i;}
 colerr=CE_NOTFOUND;
 return 15;}

int mscol256(TColor c){
 int i;
 for(i=0;i<256;i++){
  if(c==cols256[i])return i;}
 colerr=CE_NOTFOUND;
 return 0;}

AnsiString addData(int f,AnsiString src,int a){
 if(f==1){if(src!="")src=src+",";src=src+"#";}
 src=src+IntToHex(a,2);
 return src;}

//------------ sprite
void __fastcall TForm1::GenSp(int sx,int sy){
 int f=(rbBasic->Checked)?0:1;
 int i,j;
 TColor c,c1=clBlack;
 AnsiString st,stc;
 char ch[17],co;
 if(f==0){st="data";stc="data";}
 else{st="";stc="";}
 for(i=0;i<sy;i++){
  co=0;
  for(j=0;j<sx;j++){
   c=Image1->Canvas->Pixels[j][i];
   if(co==0&&c!=c1){co=1;
    stc=addData(f,stc,mscol(c));}
   if(j<8)ch[j]=(c==c1)?'0':'1';}
  if(!co){
   stc=addData(f,stc,0);}
  ch[j]=0;
//  if(!i)st=st+",";
  st=addData(f,st,binToInt(ch));}
// ShowMessage("1:"+st+"\n2:"+stc+"\n"+IntToStr(f));
 if(sx>8){
  for(i=0;i<sy;i++){
   for(j=0;j<8;j++){
    c=Image1->Canvas->Pixels[j+8][i];
    ch[j]=(c==c1)?'0':'1';}
   ch[j]=0;
//  if(!i)st=st+",";
   st=addData(f,st,binToInt(ch));}}
 if(chkOneColor->Checked){
  if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st+"\n";}
  else Memo1->Lines->Text=st+"\n";}
 else{if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st+"\n"+stc+"\n";}
  else Memo1->Lines->Text=st+"\n"+stc+"\n";}
}

//------------ 2-sprites
void BubSort(int x[ ],int n)
{int i,j,tmp;
 for(i=0;i<n-1;i++){
  for(j=n-1;j>i;j--){
   if(x[j-1]>x[j]){  /* 前の要素の方が大きかったら */
    tmp=x[j];x[j]=x[j-1];x[j-1]=tmp;
   }}}
}

void __fastcall TForm1::GenSp2(int sx,int sy){
 int f=(rbBasic->Checked)?0:1;
 int i,j,ii,k,cnum,d[3];bool ex;bool dr=chkDummyR->Checked;
 TColor c;
 AnsiString st,stc,st2,stc2;
 char ch[17],ch2[17];
 if(f==0){st="data";stc="data";st2="data";stc2="data";}
 else{st="";stc="";st2="";stc2="";}
 for(i=0;i<sy;i++){
  //analyse 2 color with cc bit
  k=0;for(j=0;j<3;j++)d[j]=0;
  for(j=0;j<sx;j++){c=Image1->Canvas->Pixels[j][i];
   if(c){cnum=mscol(c);
    if(cnum){ex=false;
     for(ii=0;ii<k;ii++){if(d[ii]==cnum)ex=true;}
     if(!ex){if(k==3)colerr=CE_MANYCOLOR;else{d[k]=cnum;++k;}}}}}
  BubSort(d,k);
//  ShowMessage(IntToStr(d[0])+"/"+IntToStr(d[1])+"/"+IntToStr(d[2])+"/"+IntToStr(d[0]|d[1]));
  stc=addData(f,stc,d[0]);
  stc2=addData(f,stc2,d[1]|64);
  if(d[2]&&(d[0]|d[1])!=d[2])colerr=CE_3RDCOLOR;

  for(j=0;j<8;j++){
   cnum=mscol(Image1->Canvas->Pixels[j][i]);
   ch[j]=(cnum&&d[0]&&(cnum==d[0]||cnum==d[2]))?'1':'0';
   ch2[j]=(cnum&&d[1]&&(cnum==d[1]||cnum==d[2]))?'1':'0';}
  ch[j]=0;ch2[j]=0;
//  if(!i)st=st+",";
  st=addData(f,st,binToInt(ch));
  st2=addData(f,st2,binToInt(ch2));}
// ShowMessage("1:"+st+"\n2:"+stc+"\n"+IntToStr(f));
 if(sx>8){
  for(i=0;i<sy;i++){
   k=0;for(j=0;j<3;j++)d[j]=0;
   for(j=0;j<sx;j++){c=Image1->Canvas->Pixels[j][i];
    if(c){cnum=mscol(c);
     if(cnum){ex=false;
      for(ii=0;ii<k;ii++){if(d[ii]==cnum)ex=true;}
      if(!ex){if(k==3)colerr=CE_MANYCOLOR;else{d[k]=cnum;++k;}}}}}
   BubSort(d,k);

   for(j=0;j<8;j++){
    cnum=mscol(Image1->Canvas->Pixels[8+j][i]);
    ch[j]=((j!=7||!dr)&&cnum&&d[0]&&(cnum==d[0]||cnum==d[2]))?'1':'0';
    ch2[j]=((j!=7||!dr)&&cnum&&d[1]&&(cnum==d[1]||cnum==d[2]))?'1':'0';}

   ch[j]=0;ch2[j]=0;
//  if(!i)st=st+",";
   st=addData(f,st,binToInt(ch));
   st2=addData(f,st2,binToInt(ch2));
   }}

 if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st+"\n"+st2+"\n"+stc+"\n"+stc2+"\n";}
 else Memo1->Lines->Text=st+"\n"+st2+"\n"+stc+"\n"+stc2+"\n";
}

void __fastcall TForm1::GenSp21(int sx,int sy){
 int f=(rbBasic->Checked)?0:1;
 int i,j,ii,k,cnum,d[3];bool ex;
 TColor c;
 AnsiString st,st2;
 char ch[17],ch2[17];
 if(f==0){st="data";st2="data";}
 else{st="";st2="";}

 k=0;for(j=0;j<2;j++)d[j]=0;
 for(i=0;i<sy;i++){//ShowMessage(i);
  for(j=0;j<sx;j++){c=Image1->Canvas->Pixels[j][i];
   if(c){cnum=mscol(c);
    if(cnum){ex=false;
     for(ii=0;ii<k;ii++){if(d[ii]==cnum)ex=true;}
     if(!ex){if(k==2)colerr=CE_MANYCOLOR;else{d[k]=cnum;++k;}}}}}}
// BubSort(d,2);
// ShowMessage(IntToStr(d[0])+"/"+IntToStr(d[1])+"/"+IntToStr(d[2]));

 for(i=0;i<sy;i++){
  for(j=0;j<8;j++){
   cnum=mscol(Image1->Canvas->Pixels[j][i]);
   ch[j]=(cnum&&d[0]&&(cnum==d[0]))?'1':'0';
   ch2[j]=(cnum&&d[1]&&(cnum==d[1]))?'1':'0';}
  ch[j]=0;ch2[j]=0;
//  if(!i)st=st+",";
  st=addData(f,st,binToInt(ch));
  st2=addData(f,st2,binToInt(ch2));}
// ShowMessage("1:"+st+"\n2:"+stc+"\n"+IntToStr(f));
 if(sx>8){
  for(i=0;i<sy;i++){
   for(j=0;j<8;j++){
    cnum=mscol(Image1->Canvas->Pixels[8+j][i]);
    ch[j]=(cnum&&d[0]&&(cnum==d[0]))?'1':'0';
    ch2[j]=(cnum&&d[1]&&(cnum==d[1]))?'1':'0';}

   ch[j]=0;ch2[j]=0;
//  if(!i)st=st+",";
   st=addData(f,st,binToInt(ch));
   st2=addData(f,st2,binToInt(ch2));
   }}

 if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st+"\n"+st2+"\n";}
 else Memo1->Lines->Text=st+"\n"+st2+"\n";
}
//----- character
void __fastcall TForm1::GenCh(int sx,int sy){
 int f=(rbBasic->Checked)?0:1;
 int i,j,ii;
 TColor c,c1,c2;
 AnsiString st,stc;
 char ch[9],co;
 if(f==0){st="data";stc="";}
 else{st="";stc="";}
 for(i=0;i<sy;i++){
  co=0;
  c1=Image1->Canvas->Pixels[0][i];
  c2=Image1->Canvas->Pixels[0][i];
  for(j=0;j<8;j++){
   c=Image1->Canvas->Pixels[j][i];
   if(co==0&&c!=c1){co=1;c2=c;}
    //stc=stc+IntToHex(mscol(c),2);
   ch[j]=(c==c1)?'0':'1';}
  ch[j]=0;
//  if(!i)st=st+",";
  st=addData(f,st,binToInt(ch));
  stc=addData(f,stc,mscol(c2)*16+mscol(c1));}

 if(sx>8){for(ii=8;ii<sx;ii+=8){
 for(i=0;i<sy;i++){
  co=0;
  c1=Image1->Canvas->Pixels[ii][i];
  c2=Image1->Canvas->Pixels[ii][i];
  for(j=0;j<8;j++){
   c=Image1->Canvas->Pixels[j+ii][i];
   if(co==0&&c!=c1){co=1;c2=c;}
    //stc=stc+IntToHex(mscol(c),2);
   ch[j]=(c==c1)?'0':'1';}
  ch[j]=0;
//  if(!i)st=st+",";
  st=addData(f,st,binToInt(ch));
  stc=addData(f,stc,mscol(c2)*16+mscol(c1));}}
}
 if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st+","+stc+"\n";}
 else Memo1->Lines->Text=st+","+stc+"\n";
}

//------------- graphic
void __fastcall TForm1::GenGra(int sx,int sy){
 int f=(rbBasic->Checked)?0:1;
 int i,j;
 AnsiString st,st2="";
// colcnt=false;
//GRA_RETRY:colerr=false;
 if(f==0){st="data";}else{st="";}
 for(i=0;i<sy;i++){
  if(!f&&i){st2=st2+st+"\n";st="data";}
//  if(!f){if(st.Length()>128){st2=st2+st+"\n";st="data";}else st=st+",";}
  for(j=0;j<sx;j++){
   if(st.Length()>512){
    st2=st2+st+"\n";
    if(f==0){st="data";}else{st="";}}
   if(!chk256->Checked){
    st=addData(f,st,mscol(Image1->Canvas->Pixels[j][i])*16+mscol(Image1->Canvas->Pixels[j+1][i]));
    ++j;}
   else st=addData(f,st,mscol256(Image1->Canvas->Pixels[j][i]));}
}
// if(!colcnt&&colerr){colcnt=true;chk256->Checked=!chk256->Checked;goto GRA_RETRY;}
 st2=st2+st;
  if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st2+"\n";}
  else Memo1->Lines->Text=st2+"\n";
}

//-------- compress
void __fastcall TForm1::GenCompress(AnsiString fi,int org_len){
 int i,han,len;unsigned char *buf,*p;

 SetCurrentDir(ExtractFilePath(pa));
 //WinExec((pa+"pack.exe "+ExtractFileName(fi)).c_str(),SW_HIDE);
 system((pa+"pack.exe "+ExtractFileName(fi)).c_str());
 AnsiString st,st2;

 if((han=FileOpen(fi+".pck",fmOpenRead))==-1){
  Application->MessageBox("compress file load failed","ERROR",MB_OK);return;}
 len=FileSeek(han,0,2);
 FileSeek(han,0,0);
 buf=new unsigned char[len+1];
 FileRead(han,buf,len);
 FileClose(han);

 st="";st2="// "+IntToStr(len)+" bytes\n";p=buf+4;
 for(i=0;i<len-4;i++){
  if(st.Length()>512){st2=st2+st+"\n";st="";}
  if(st!="")st=st+",";
  st=st+"#"+IntToHex(*p,2);++p;}
// if(!colcnt&&colerr){colcnt=true;chk256->Checked=!chk256->Checked;goto GRA_RETRY;}
 st2=st2+st+"\n";
 if(isLock){Memo1->Lines->Text=Memo1->Lines->Text+st2+"\n";}
 else Memo1->Lines->Text=st2+"\n";}

//------------- graphic(BINARY)
void __fastcall TForm1::GenGraBin(int sx,int sy){
 int i,j,ln;
 unsigned char *m,c,*p;
 m=new char[sx*sy];

 p=m;ln=0;
 for(i=0;i<sy;i++){
  for(j=0;j<sx;j++){
   if(!chk256->Checked){
    c=((unsigned char)mscol(Image1->Canvas->Pixels[j][i]))*16+((unsigned char)mscol(Image1->Canvas->Pixels[j+1][i]));
    ++j;}
   else c=((unsigned char)mscol256(Image1->Canvas->Pixels[j][i]));
   *(p++)=c;++ln;}
  }

  int han;
  if((han=FileCreate(pa+"temp"))==-1){Application->MessageBox("can't write temp file","Error",MB_OK);return;}
  FileWrite(han,m,ln);
  FileClose(han);
  GenCompress(pa+"temp",ln);
}

//-------------------------------------
void __fastcall TForm1::FileList1Click(TObject *Sender)
{int sx,sy;
 int a=FileListBox1->ItemIndex;
 if(a==-1)return;
 Image1->AutoSize=true;
 AnsiString fi=FileListBox1->Items->Strings[a];fi=ChangeFileExt(fi,".bmp");
 Image1->Picture->LoadFromFile(FileList1->Directory+"\\"+fi);
 Image1->AutoSize=false;
 sx=Image1->Width;sy=Image1->Height;
 Image1->Width=Image1->Width*2;
 Image1->Height=Image1->Height*2;
 Image1->Refresh();
 colerr=CE_NOERR;StatusBar1->SimpleText="";
  if(rbQq->Checked){
   AnsiString st=FileListBox1->Items->Strings[a];
   if(DirectoryListBox1->Directory.Pos("media"))Memo1->Lines->Text="\x22"+st+"\x22";
   else Memo1->Lines->Text="\x22"+ExtractFileName(DirectoryListBox1->Directory)+"\\"+st+"\x22";}
  else{
 if(rbSprite->Checked){if(chkTwoSprites->Checked){if(chkOneColor->Checked)GenSp21(sx,sy);else GenSp2(sx,sy);}else GenSp(sx,sy);}
 if(rbCharacter->Checked)GenCh(sx,sy);
 if(rbGraphic->Checked){if(chkCompress->Checked)GenGraBin(sx,sy);else GenGra(sx,sy);}

 }
 if(colerr)StatusBar1->SimpleText="Error: "+AnsiString(cestr[colerr]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{AddEndComma();
 Memo1->SelectAll();
 Memo1->CopyToClipboard();
 Application->Terminate();
}
//---------------------------------------------------------------------------
//--- ウィンド検索 (ﾀｲﾄﾙﾊﾞｰ) ハンドルを返す
HWND FindWind(AnsiString ch){
 char gbuf[256];
 HWND CurrWnd=GetWindow(Form1->Handle,GW_HWNDFIRST);
 while(CurrWnd){
  GetWindowText(CurrWnd,gbuf,256);
  if(AnsiPos(ch,StrPas(gbuf)))return CurrWnd;
  CurrWnd=GetWindow(CurrWnd,GW_HWNDNEXT);}
 return 0;}

void __fastcall TForm1::AddEndComma(void){
 int i;AnsiString st;
 if(rbCcz80->Checked){
  for(i=0;i<Memo1->Lines->Count-1;i++){
   st=Memo1->Lines->Strings[i];
   if(st.Length())st=st+",";
   Memo1->Lines->Strings[i]=st;
  }}
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{AddEndComma();
 Memo1->SelectAll();
 Memo1->CopyToClipboard();
 HWND han=FindWind("Tabmegx");
 if(han)SetForegroundWindow(han);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
 SendMessage(FileListBox1->Handle,WM_KEYDOWN,VK_UP,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
 SendMessage(FileListBox1->Handle,WM_KEYDOWN,VK_DOWN,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
 SendMessage(FileListBox1->Handle,WM_KEYDOWN,VK_END,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileRefresh(void){
 int i,n=1,ok1,ok2;char c;
 FileListBox1->Clear();
 AnsiString st;
 do{
  st=IntToStr(n)+ext;ok1=0;c='a';
  do{
   ok2=0;
   for(i=0;i<FileList1->Items->Count;i++){
//   ShowMessage(st+"::"+FileList1->Items->Strings[i]);
    if(st==FileList1->Items->Strings[i]){
     FileList1->Items->Delete(i);
     FileListBox1->Items->Add(st);ok1=1;ok2=1;i=FileList1->Items->Count;}}
   if(ok2==1){st=IntToStr(n)+c+ext;++c;}
   }while(ok2==1);
  ++n;
  }while(ok1==1);
 for(i=0;i<FileList1->Items->Count;i++){
  FileListBox1->Items->Add(FileList1->Items->Strings[i]);}
}


void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
 SendMessage(FileListBox1->Handle,WM_KEYDOWN,VK_HOME,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnLockClick(TObject *Sender)
{if(!isLock){
  btnLock->Font->Style=TFontStyles()<<fsBold;
  isLock=true;}
 else{
  btnLock->Font->Style=TFontStyles();
  isLock=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DirectoryListBox1Change(TObject *Sender)
{
FileRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
 AnsiString fi_cur=ComboBox1->Items->Strings[ComboBox1->ItemIndex]+".bmp";
 Image2->Picture->Bitmap=NULL;
 Image2->AutoSize=true;
 Image2->Picture->LoadFromFile(pa+"..\\palette\\"+fi_cur);
 reloadCols();
 Image2->AutoSize=false;
 Image2->Width=256;Image2->Height=16;
 FileList1Click(Sender);
// Image2->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WMDROPFILES(TWMDropFiles Msg){
 int i;AnsiString st;
 char buf[MAX_PATH];
 //ドラッグされたファイルの個数
 int cnt=::DragQueryFile((HDROP)Msg.Drop,0xFFFFFFFF,NULL,0);
 if(cnt){
  ::DragQueryFile((HDROP)Msg.Drop,0,buf,sizeof(buf));
  st=StrPas(buf);
  DirectoryListBox1->Directory=ExtractFileDir(st);
  st=ExtractFileName(st);
  for(i=0;i<FileListBox1->Items->Count;i++){
   if(FileListBox1->Items->Strings[i]==st){FileListBox1->ItemIndex=i;FileList1Click(NULL);return;}}
}}

