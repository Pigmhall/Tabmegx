//---------------------------------------------------------------------------
#include <vcl.h>
//#include <vcl\registry.hpp>
#include <dir.h>
#include <io.h>
#include <shellapi.h>
#include <stdio.h>
#include <shlobj.h>
#pragma hdrstop

#include "megimage.h"
#include "megson1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmImage *FrmImage;
//---------------------------------------------------------------------------
__fastcall TFrmImage::TFrmImage(TComponent* Owner)
        : TForm(Owner)
{
// DWORD drivemask=GetLogicalDrives();
// AnsiString dr="<X:>";
/* Drives="";
 for(int i=0;i<'Z'-'A';i++){
  if((drivemask&(1<<i))!=0){dr[2]=(char)('A'+i);Drives=Drives+dr+"\n";}}

 TRegistry *re;
 re=new TRegistry;re->RootKey=HKEY_CURRENT_USER;re->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",False);
 wd=re->ReadString("Desktop")+"\\";
 delete re;*/
// wd=FrmMeg1->Fod1->wd;
 //Drives=FrmMeg1->Fod1->Drives;
 Susie.set_spipath(FrmMeg1->di_megpas.c_str());
 FTitle="IMG";
}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::FormShow(TObject *Sender)
{
/* if(FFileName!=""){
  FDir=ExtractFilePath(FFileName);
  Edit1->Text=ExtractFileName(FFileName);}
 else Edit1->Text="";*/

 if(FDir=="")FDir=GetCurrentDir();
 if(FDir[FDir.Length()]!='\\')FDir=FDir+"\\";
// FileListBox1->Update();
 Update();
 if(ListBox1->Items->Text==""){FDir="C:\\";Update();}

 ListBox1->SetFocus();
// result=(Form1->ShowModal()==IDOK)?true:false;
// FileListBox1->Directory="C:\\";FileListBox1->Update();
}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::OkResult(AnsiString st,bool bo){
//きちんとしたﾌｧｲﾙ名が入力されていたら終了
FFileName=FDir+st;ModalResult=IDOK;//Susie.clean();
/* if(!sd||bo||Application->MessageBox("上書き?","",MB_YESNO)==IDYES){
  if(st.LastDelimiter("\\/:,;*?\x22<>|")){
   Application->MessageBox("使えない文字","",MB_OK);
   Edit1->SelectAll();}
  else{FFileName=FDir+st;SetCurrentDir(FDir); ModalResult=IDOK;}}*/}

void __fastcall TFrmImage::Ok(AnsiString st){
//ﾘｽﾄﾎﾞｯｸｽで決定された時の処理
 if(jumpmo){FDir=FrmMeg1->Fod1->li_jumpdir->Strings[ListBox1->ItemIndex];Update();return;}
 if(st[1]=='<'){
  if(st[3]==':'){setdisk(st[2]-'A');FDir=GetCurrentDir();
   if(FDir[FDir.Length()]!='\\')FDir=FDir+"\\";
  Update();}
   else if(st[2]=='.'){FDir.Delete(FDir.Length(),1);FDir=ExtractFilePath(FDir);Update();}
   else if(AnsiPos(".lnk",st)){
//    Form1->Caption=FDir+st.SubString(2,st.Length()-2);
    st=FrmMeg1->Fod1->AnalizeLink(FDir+st.SubString(2,st.Length()-2));if(st!=""){FDir=st+"\\";Update();}
    }
   else{FDir=FDir+st.SubString(2,st.Length()-2)+"\\";Update();}
  Edit1->SelectAll();}
 else OkResult(st,false);
}
void __fastcall TFrmImage::ListBox1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
int a=ListBox1->ItemIndex;
 if(a!=-1){
 AnsiString fn=ListBox1->Items->Strings[a];
  switch(Key){
   case VK_RETURN:Ok(fn);break;
   case VK_ESCAPE:ModalResult=IDCANCEL;break;
   case VK_BACK:if(FDir.Length()>3){FDir.Delete(FDir.Length(),1);FDir=ExtractFilePath(FDir);Update();}break;
//*   case VK_F2:if(fn[1]!='<')Edit1->Text=fn;break;
   case VK_F1:Application->HelpCommand(HELP_CONTEXT,15);break;
   case VK_F3:FDir=FrmMeg1->Fod1->wd;Update();break;
   case VK_F4:FDir=FrmMeg1->Fod1->wmy;Update();break;
   case VK_F5:Update();break;
   case VK_DELETE:if(fn[1]!='<'){
    //mes="ﾌｧｲﾙ"+fn+"を削除してよろしいですか?";
    if(Application->MessageBox("削除?","",MB_YESNO)==IDYES){
     unlink(fn.c_str());ListBox1->Items->Delete(a);ListBox1->ItemIndex=a;
     }} break;
   case 'D':if(Shift.Contains(ssCtrl)){if(Application->MessageBox((FDir+"\nを追加?").c_str(),"ｼﾞｬﾝﾌﾟ",MB_YESNO)==IDYES){FrmMeg1->Fod1->li_jumpdir->Add(FDir);}}break;
   case 'J':if(Shift.Contains(ssCtrl))InitJumpMo2();break;
   }
  if((Key<'0'||Key>=0x70)&&Key!=0x20)keycount=1;
 }

}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::InitJumpMo2(void){// ｼﾞｬﾝﾌﾟ初期化
 int i;AnsiString fn;
 if(!FrmMeg1->Fod1->li_jumpdir->Count)return;
 ListBox1->Clear();for(i=0;i<FrmMeg1->Fod1->li_jumpdir->Count;i++){fn=FrmMeg1->Fod1->li_jumpdir->Strings[i];
  if(fn.Length()>3)fn=ExtractFileName(fn.SubString(1,fn.Length()-1));ListBox1->Items->Add(fn);}
 ListBox1->SetFocus();ListBox1->ItemIndex=0;Caption="ｼﾞｬﾝﾌﾟ";
 jumpmo=true;}

void __fastcall TFrmImage::ListBox1KeyPress(TObject *Sender, char &Key)
{
 int a=ListBox1->ItemIndex,aa;
 char c;
  if(a!=-1&&Key>=32&&Key<127){ //文字が入力された場合の検索
   while(a!=ListBox1->Items->Count){
    aa=(ListBox1->Items->Strings[a][1]=='<')?1:0;
    if(ListBox1->Items->Strings[a].Length()>keycount+aa-1){c=(char)toupper(ListBox1->Items->Strings[a][keycount+aa]);
    if((c==toupper(Key)||(Key==' '&&(c=='_'||c=='-')))&&(keycount==1||toupper(ListBox1->Items->Strings[a][keycount+aa-1])==keyhis)){
     ++keycount;ListBox1->ItemIndex=a;ListBox1Click(Sender);break;}}++a;}
   if(a==ListBox1->Items->Count)keycount=1;else keyhis=c;
  if(jumpmo&&keycount>1)Ok(ListBox1->Items->Strings[ListBox1->ItemIndex]);}
  else keycount=1;
 Key=0;

}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::ListBox1DblClick(TObject *Sender)
{
 if(ListBox1->ItemIndex!=-1)Ok(ListBox1->Items->Strings[ListBox1->ItemIndex]);

}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::Update(){
 TSearchRec sr;
 TStringList *st;
 AnsiString di=ExtractFileName(FDir.SubString(1,FDir.Length()-1));

 if(di=="")Caption=FTitle+" - "+FDir;
 else Caption=FTitle+" - "+di;
 di="";
 if(!FindFirst(FDir+"*.*",faAnyFile,sr)){
  if(((sr.Attr&16)==faDirectory||AnsiPos(".lnk",sr.Name))&&sr.Name!=".")di=di+"<"+sr.Name+">\n";
  while(FindNext(sr)==0){if(((sr.Attr&16)==faDirectory||AnsiPos(".lnk",sr.Name)))di=di+"<"+sr.Name+">\n";}

  st=new TStringList();
  st->Text=di;st->Sort();di=st->Text;

  FileListBox1->Directory=FDir;
  FileListBox1->Update();
  ListBox1->Items->Text=di+FileListBox1->Items->Text+FrmMeg1->Fod1->Drives;
  ListBox1->ItemIndex=0;
  keycount=1;
  delete st;}
jumpmo=false;FindClose(sr);}

/*AnsiString __fastcall TFrmImage::AnalizeLink(String SCFileName)
{
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	hres = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, &(void*)psl);
	if (!SUCCEEDED(hres)) return(-1);

	// ファイル作成用インターフェース取得
	hres = psl->QueryInterface(IID_IPersistFile,&(void*)ppf);
	if (!SUCCEEDED(hres)) return (-1);

	// ファイル名を作る
	wchar_t WFileName[MAX_PATH];
	SCFileName.WideChar(WFileName, MAX_PATH);

	// ショートカット取得
	hres = ppf->Load(WFileName, STGM_READ);
	if (!SUCCEEDED(hres)){
//         Application->MessageBox("err","",MB_OK);
         return (-1);}

	// ショートカットの名前
   //	FSCName = ChangeFileExt(ExtractFileName(SCFileName), "");

	// ディレクトリ
//	FSCDir = ExtractFileDir(SCFileName);

	// リンク先
	WIN32_FIND_DATA Ffblk;
	char str[MAX_PATH + 1];

	psl->GetPath(str, MAX_PATH, &Ffblk, SLGP_UNCPRIORITY);
        SCFileName=StrPas(str);
        if(!DirectoryExists(str)){Application->MessageBox("not dir","err",MB_OK);return "";}
        return SCFileName;}*/

bool __fastcall TFrmImage::LoadGra(AnsiString f){
  if(Susie.set_file(f.c_str())){
   if(Susie.load()){
    Image1->Width = Susie.bmp->Width;
    Image1->Height = Susie.bmp->Height;
    Image1->Picture->Bitmap = Susie.bmp;
     Image1->Width=Image1->Width*2;
     Image1->Height=Image1->Height*2;
    }
   else return false;}
 Image1->Refresh();
 return true;}

// Image1->Picture->Bitmap->Handle=g->NViewLibLoad(StrPCopy(buf,f),false);

void __fastcall TFrmImage::ListBox1Click(TObject *Sender)
{
AnsiString fi;int a;
 if(jumpmo)return;
 if((a=ListBox1->ItemIndex)!=-1){
  fi=ListBox1->Items->Strings[a];
  if(fi[1]=='<'||!LoadGra(FDir+"\\"+fi)){Image1->Picture->Bitmap=NULL;Image1->Width=10;Image1->Height=10;}}
}
//---------------------------------------------------------------------------
void __fastcall TFrmImage::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{int a=ListBox1->ItemIndex;
 if(a!=-1){
 AnsiString fn=ListBox1->Items->Strings[a];
  switch(Key){
   case VK_RETURN:Ok(fn);break;
   case VK_ESCAPE:ModalResult=IDCANCEL;break;}}
}
//---------------------------------------------------------------------------

void __fastcall TFrmImage::FormResize(TObject *Sender)
{
 ListBox1->Width=FrmMeg1->Fod1->Width;
 ListBox1->Height=ClientHeight-Button1->Height;
 ScrollBox1->Left=ListBox1->Width;
 ScrollBox1->Width=ClientWidth-ListBox1->Width;
 ScrollBox1->Height=ClientHeight-Edit1->Height;
 ScrollBox1->Top=Edit1->Height;
 Label1->Left=ListBox1->Width+4;
 Edit1->Left=Label1->Left+Label1->Width;
 Button1->Top=ListBox1->Height;
 Button2->Top=ListBox1->Height;
 Button3->Top=ListBox1->Height;
 Button4->Top=ListBox1->Height;

}
//---------------------------------------------------------------------------

void __fastcall TFrmImage::Button1Click(TObject *Sender)
{
SendMessage(ListBox1->Handle,WM_KEYDOWN,VK_UP,1);
}
//---------------------------------------------------------------------------

void __fastcall TFrmImage::Button2Click(TObject *Sender)
{
SendMessage(ListBox1->Handle,WM_KEYDOWN,VK_DOWN,1);        
}
//---------------------------------------------------------------------------

void __fastcall TFrmImage::Button3Click(TObject *Sender)
{
SendMessage(ListBox1->Handle,WM_KEYDOWN,VK_RETURN,1);
}
//---------------------------------------------------------------------------

void __fastcall TFrmImage::Button4Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

