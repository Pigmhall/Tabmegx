//FOD.CPP -------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl\registry.hpp>
#include <dir.h>
#include <io.h>
#include <shellapi.h>
#include <stdio.h>
#include <shlobj.h>
#pragma hdrstop

#include "fod.h"
#include "megson1.h"
#define INI(X) FrmMeg1->li_ini->Values[X]
//---------------------------------------------------------------------------
/*static inline TFod *ValidCtrCheck()
{
 return new TFod(NULL);
}*/
//---------------------------------------------------------------------------
__fastcall TFod::TFod(TComponent* Owner)
	: TComponent(Owner)
{
 FWidth=256;FHeight=384;
 FFontColor=clAqua;
 FFontSize=10;
 FMask="*.*";FColor=clBlack;// FColor=clWindow;

 DWORD drivemask=GetLogicalDrives();
 AnsiString dr="<X:>";
 Drives="";
 for(int i=0;i<'Z'-'A';i++){
  if((drivemask&(1<<i))!=0){dr[2]=(char)('A'+i);Drives=Drives+dr+"\n";}}

 TRegistry *re;
 re=new TRegistry;re->RootKey=HKEY_CURRENT_USER;re->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",False);
 wd=re->ReadString("Desktop")+"\\";
 wmy=re->ReadString("Personal")+"\\";
 delete re;
// re->Free();
 Form1=new TForm(this);
// Form1->FormStyle=

 ListBox1=new TListBox(this);
 Edit1=new TEdit(this);
 FileListBox1=new TFileListBox(this);
 li_jumpdir=new TStringList();

/* int a=0;AnsiString st;
 while((st=INI("FodJumpDir"+IntToStr(a)))!=""){li_jumpdir->Add(st);}*/
}
//---------------------------------------------------------------------------
bool __fastcall TFod::Execute(char a){
// 0:open 1:save 2:init 3:destroy
 bool result;

/* if(a==2){
 DWORD drivemask=GetLogicalDrives();
 AnsiString dr="<X:>";
 Drives="";
 for(int i=0;i<'Z'-'A';i++){
  if((drivemask&(1<<i))!=0){dr[2]=(char)('A'+i);Drives=Drives+dr+"\n";}}

 TRegistry *re;
 re=new TRegistry;re->RootKey=HKEY_CURRENT_USER;re->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",False);
 wd=re->ReadString("Desktop")+"\\";
 delete re;
// re->Free();
 Form1=new TForm(this);
 ListBox1=new TListBox(this);
 Edit1=new TEdit(this);
 FileListBox1=new TFileListBox(this);return true;}*/

 Form1->BorderStyle=bsDialog;
 Form1->ClientWidth=FWidth;
 Form1->ClientHeight=FHeight;
 Form1->Position=poScreenCenter;
 Form1->Caption=FTitle;
 Form1->OnShow=FormShow;
 FileListBox1->Visible=false;
 FileListBox1->Mask=FMask;
 FileListBox1->Parent=Form1;
 ListBox1->Font=FrmMeg1->Memo1->Font;
 Edit1->Font=FrmMeg1->Memo1->Font;
 ListBox1->Font->Size=FontSize;
 ListBox1->Font->Color=FontColor;
 Edit1->Font->Size=FontSize;
 Edit1->Font->Color=FontColor;
 ListBox1->Left=0;
 ListBox1->Top=0;
 ListBox1->Width=Form1->ClientWidth;
 ListBox1->Height=Form1->ClientHeight-Edit1->Height;
 ListBox1->Parent=Form1;
// ListBox1->TabOrder=(TTabOrder)(a^0);
 ListBox1->OnKeyDown=ListBox1KeyDown;
 ListBox1->OnKeyPress=ListBox1KeyPress;
 ListBox1->OnDblClick=ListBox1DblClick;
 ListBox1->Color=FColor;
 Edit1->Left=0;
 Edit1->Top=ListBox1->Height;
 Edit1->Width=Form1->ClientWidth;
 Edit1->Parent=Form1;
// Edit1->TabOrder=(TTabOrder)(a^1);
 Edit1->Color=FColor;
 sd=a;
 Edit1->OnKeyDown=Edit1KeyDown;
 if(FFileName!=""){
  FDir=ExtractFilePath(FFileName);
  Edit1->Text=ExtractFileName(FFileName);}
 else Edit1->Text="";

/*if(a==3){
 ListBox1->Free();
 Edit1->Free();
 FileListBox1->Free();
 Form1->Free();return true;}*/
// jumpmo=false;
 if(FDir=="")FDir=GetCurrentDir();
 if(FDir[FDir.Length()]!='\\')FDir=FDir+"\\";
 Update();
 if(ListBox1->Items->Text==""){FDir="C:\\";Update();}

// else{try{
//try{
 result=(Form1->ShowModal()==IDOK)?true:false;
//  }catch(...){result=false;}}

/* delete ListBox1;
 delete Edit1;
 delete FileListBox1;
 delete Form1;*/
 FileListBox1->Directory="C:\\";FileListBox1->Update();
// FileListBox1->Directory="";

 return result;
}

void __fastcall TFod::FormShow(TObject *Sender){
 if(sd){Edit1->SetFocus();}else ListBox1->SetFocus();
}

void __fastcall TFod::OkResult(AnsiString st,bool bo){
//きちんとしたﾌｧｲﾙ名が入力されていたら終了
 if(!sd||bo||Application->MessageBox("上書き?","",MB_YESNO)==IDYES){
  if(st.LastDelimiter("\\/:,;*?\x22<>|")){
   Application->MessageBox("使えない文字","",MB_OK);
   Edit1->SelectAll();}
  else{FFileName=FDir+st;SetCurrentDir(FDir); Form1->ModalResult=IDOK;}}}

void __fastcall TFod::Ok(AnsiString st){
//ﾘｽﾄﾎﾞｯｸｽで決定された時の処理
 if(jumpmo){FDir=li_jumpdir->Strings[ListBox1->ItemIndex];Update();return;}
 if(st[1]=='<'){
  if(st[3]==':'){setdisk(st[2]-'A');FDir=GetCurrentDir();
   if(FDir[FDir.Length()]!='\\')FDir=FDir+"\\";
  Update();}
   else if(st[2]=='.'){FDir.Delete(FDir.Length(),1);FDir=ExtractFilePath(FDir);Update();}
   else if(AnsiPos(".lnk",st)){
//    Form1->Caption=FDir+st.SubString(2,st.Length()-2);
    st=AnalizeLink(FDir+st.SubString(2,st.Length()-2));if(st!=""){FDir=st+"\\";Update();}
    }
   else{FDir=FDir+st.SubString(2,st.Length()-2)+"\\";Update();}
  Edit1->SelectAll();}
 else OkResult(st,false);
}

void __fastcall TFod::InitJumpMo(void){// ｼﾞｬﾝﾌﾟ初期化
 int i;AnsiString fn;
 if(!li_jumpdir->Count)return;
 ListBox1->Clear();for(i=0;i<li_jumpdir->Count;i++){fn=li_jumpdir->Strings[i];// a=0;for(j=1;j<=fn.Length();j++){if(fn[j]=='\\')++a;}
  if(fn.Length()>3)fn=ExtractFileName(fn.SubString(1,fn.Length()-1));ListBox1->Items->Add(fn);}
 ListBox1->SetFocus();ListBox1->ItemIndex=0;Form1->Caption="ｼﾞｬﾝﾌﾟ";
 jumpmo=true;}

void __fastcall TFod::ListBox1KeyDown(TObject *Sender,WORD &Key,TShiftState Shift){
int a=ListBox1->ItemIndex;
 if(a!=-1){
 AnsiString fn=ListBox1->Items->Strings[a];
  switch(Key){
   case VK_RETURN:Ok(fn);break;
   case VK_ESCAPE:Form1->ModalResult=IDCANCEL;break;
   case VK_BACK:if(FDir.Length()>3){FDir.Delete(FDir.Length(),1);FDir=ExtractFilePath(FDir);Update();}break;
   case VK_F1:Application->HelpCommand(HELP_CONTEXT,5);break;
   case VK_F2:if(fn[1]!='<')Edit1->Text=fn;break;
   case VK_F3:FDir=wd;Update();break;
   case VK_F4:FDir=wmy;Update();break;
   case VK_F5:Update();break;
   case VK_DELETE:if(fn[1]!='<'){
    //mes="ﾌｧｲﾙ"+fn+"を削除してよろしいですか?";
    if(Application->MessageBox("削除?","",MB_YESNO)==IDYES){
     if(jumpmo)li_jumpdir->Delete(a);else unlink(fn.c_str());ListBox1->Items->Delete(a);ListBox1->ItemIndex=a;
     }} break;
   case 'D':if(Shift.Contains(ssCtrl)){if(Application->MessageBox((FDir+"\nを追加?").c_str(),"ｼﾞｬﾝﾌﾟ",MB_YESNO)==IDYES){li_jumpdir->Add(FDir);}}break;
   case 'J':if(Shift.Contains(ssCtrl))InitJumpMo();break;
   }
  if((Key<'0'||Key>=0x70)&&Key!=0x20){keycount=1;}
 }
}
void __fastcall TFod::ListBox1KeyPress(TObject *Sender, char &Key){
 int a=ListBox1->ItemIndex,aa;
 char c;
  if(a!=-1&&Key>=32&&Key<127){ //文字が入力された場合の検索
   while(a!=ListBox1->Items->Count){
    aa=(ListBox1->Items->Strings[a][1]=='<')?1:0;
    if(ListBox1->Items->Strings[a].Length()>keycount+aa-1){c=(char)toupper(ListBox1->Items->Strings[a][keycount+aa]);
     if((c==toupper(Key)||(Key==' '&&(c=='_'||c=='-')))&&(keycount==1||toupper(ListBox1->Items->Strings[a][keycount+aa-1])==keyhis)){
     ++keycount;ListBox1->ItemIndex=a;break;}}++a;}
   if(a==ListBox1->Items->Count)keycount=1;else keyhis=c;
   if(jumpmo&&keycount>1)Ok(ListBox1->Items->Strings[ListBox1->ItemIndex]);}
  else keycount=1;
 Key=0;
}

void __fastcall TFod::ListBox1DblClick(TObject *Sender){
 if(ListBox1->ItemIndex!=-1)Ok(ListBox1->Items->Strings[ListBox1->ItemIndex]);
}

void __fastcall TFod::Edit1KeyDown(TObject *Sender,WORD &Key,TShiftState Shift){
// TSearchRec sr;
 AnsiString st=Edit1->Text,st2;
 switch(Key){
   case 'J':if(Shift.Contains(ssCtrl))InitJumpMo();break;
   case VK_RETURN:
   if(st.LastDelimiter("*?")){FileListBox1->Mask=st;Edit1->SelectAll();Update();return;}

   if((st==""&&FDir.Length()!=3)||st==".."){FDir.Delete(FDir.Length(),1);FDir=ExtractFilePath(FDir);Edit1->SelectAll();Update();return;}
   if(st.Length()<4){
    st[1]='X';
    if(st=="X:"||st=="X:\\"){
     if(st=="X:\\")Edit1->Text.Delete(Edit1->Text.Length()-1,1);
     if(Drives.Pos(Edit1->Text.UpperCase())){
      setdisk(Edit1->Text.UpperCase()[1]-'A');
      FDir=GetCurrentDir();Update();return;}
     }
    }
   st=Edit1->Text;

   if(st=="\\"){FDir=FDir.SubString(1,3);Edit1->SelectAll();Update();return;}
//   if(!FindFirst(FDir+st,faAnyFile,sr)){
//    if(sr.Attr==faDirectory){FDir=FDir+sr.Name+"\\";Edit1->SelectAll();FindClose(sr);Update();return;}}
//   FindClose(sr);
   if(DirectoryExists(FDir+st)){FDir=FDir+st+"\\";Edit1->SelectAll();Update();return;}
//   if(!FindFirst(st,faAnyFile,sr)){
//    if(sr.Attr==faDirectory){FDir=st+"\\";Edit1->SelectAll();FindClose(sr);Update();return;}}
   if(DirectoryExists(st)){{FDir=st+"\\";Edit1->SelectAll();Update();return;}}
   //FindClose(sr);
   if(ExtractFileExt(st)=="")st=st+FExt;
//   if(!FindFirst(FDir+st,faAnyFile,sr)){FindClose(sr);
   if(FileExists(FDir+st)){//FindClose(sr);
    OkResult(st,false);}
   else{/*FindClose(sr);*/if(sd)OkResult(st,true);
   else Edit1->SelectAll();}
     break;
  case VK_ESCAPE:Form1->ModalResult=IDCANCEL;break;
  case VK_INSERT:
   if(st.LastDelimiter("\\/:,;*?\x22<>|")){
    Application->MessageBox("使えない文字","",MB_OK);
    Edit1->SelectAll();}
   else{
    //mes="ﾌｫﾙﾀﾞ"+st+"を作成しますか?";
    if(Application->MessageBox(("ﾌｫﾙﾀﾞ"+st+"を作成しますか?").c_str(),"",MB_YESNO)==IDYES){
     if(CreateDir(FDir+st)){ListBox1->Items->Insert(ListBox1->ItemIndex,"<"+st+">");
      --ListBox1->ItemIndex;
      Edit1->SelectAll();}
     else Application->MessageBox("失敗","",MB_OK);}} break;
  case VK_F1:Application->HelpCommand(HELP_CONTEXT,5);break;
  case VK_F3:FDir=wd;Update();break;
  case VK_F4:FDir=wmy;Update();break;
  case VK_F5:Update();break;
  case VK_F2:int a=ListBox1->ItemIndex;
   st2=ListBox1->Items->Strings[a];
   if(st2[1]!='<'){
//    mes="ﾌｧｲﾙ"+st2+"を"+st+"に名前を変えますか?";
    if(Application->MessageBox(("ﾌｧｲﾙ"+st2+"を"+st+"に名前を変更しますか?").c_str(),"",MB_YESNO)==IDYES){
//     mes=FDir+st;
/*     char *p,*f1,*f2;
     f1=new char[st2.Length()+3];StrPCopy(f1,st2);
     p=f1;while(*p)++p;*(++p)=0;
     f2=new char[mes.Length()+3];StrPCopy(f2,mes);
     p=f2;while(*p)++p;*(++p)=0;

     SHFILEOPSTRUCT shfileCopy;
     memset(&shfileCopy,0,sizeof(shfileCopy));
     shfileCopy.wFunc=FO_RENAME;
     shfileCopy.fFlags=0;
     shfileCopy.fAnyOperationsAborted=TRUE;
     shfileCopy.pFrom=f1;
     shfileCopy.pTo=f2;
     int iRet=SHFileOperation(&shfileCopy);
     delete[] f1;delete[] f2;*/
     if(rename((FDir+st2).c_str(),(FDir+st).c_str())==0){
      ListBox1->Items->Strings[a]=st;
      ListBox1->ItemIndex=a;}}} break;
}}

void TFod::Update(){
 TSearchRec sr;
 TStringList *st;
 AnsiString di=ExtractFileName(FDir.SubString(1,FDir.Length()-1));

 if(di=="")Form1->Caption=FTitle+" - "+FDir;
 else Form1->Caption=FTitle+" - "+di;
 di="";
 if(!FindFirst(FDir+"*.*",faAnyFile,sr)){
  if(((sr.Attr&16)==faDirectory||AnsiPos(".lnk",sr.Name))&&sr.Name!=".")di=di+"<"+sr.Name+">\n";
  while(FindNext(sr)==0){if(((sr.Attr&16)==faDirectory||AnsiPos(".lnk",sr.Name)))di=di+"<"+sr.Name+">\n";}
  st=new TStringList();
  st->Text=di;st->Sort();di=st->Text;

  FileListBox1->Directory=FDir;
  FileListBox1->Update();
  ListBox1->Items->Text=di+FileListBox1->Items->Text+Drives;
  ListBox1->ItemIndex=0;
  keycount=1;
  delete st;}
 else{if(FDir!="C:\\"){FDir="C:\\";Update();}else Form1->ModalResult=IDCANCEL;return;}
jumpmo=false;FindClose(sr);}


AnsiString TFod::AnalizeLink(String SCFileName)
{
	// ここからはほとんどSBORLANDのC++Builder会議室からの引用
	// というかそれもMSのドキュメントからの引用のはず
	// Inside Windows 98年1月号も参考にした
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	// ショートカットでなければやめる
//	if (ExtractFileExt(SCFileName) != ".lnk") return(-1);

	// COMオブジェクト作成
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
        if(!DirectoryExists(str)){Application->MessageBox("ﾌｫﾙﾀﾞではない","",MB_OK);return "";}
        return SCFileName;

/*	FLinkPath = str;

	// 作業フォルダ
	psl->GetWorkingDirectory(str, MAX_PATH);
	FWorkDir = str;

	// ウインドウ状態
	psl->GetShowCmd(&FWndState);

	// ショートカットキー
	psl->GetHotkey(&FSCKey);

	// アイコン
	psl->GetIconLocation(str, MAX_PATH, &FIconNo);
	FIconPath = str;

	// 99/06/21追加
	// 引数
	psl->GetArguments(str, MAX_PATH);
	FArgument = str;

	return(0);*/
}
/*namespace Fod
{
	void __fastcall Register()
	{
		TComponentClass classes[1] = {__classid(TFod)};
		RegisterComponents("Samples", classes, 0);
	}
} */
//---------------------------------------------------------------------------

