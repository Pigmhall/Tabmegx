//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Clipbrd.hpp>
#pragma hdrstop

#include "megperl.h"
#include "megson1.h"
#include "megcmd.h"

#define INI(X) FrmMeg1->li_ini->Values[X]
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmPerl *FrmPerl;
//---------------------------------------------------------------------------
__fastcall TFrmPerl::TFrmPerl(TComponent* Owner)
        : TForm(Owner)
{
 if(INI("PlWidth")!=""){
  FrmPerl->Width=StrToInt(INI("PlWidth"));
  FrmPerl->Height=StrToInt(INI("PlHeight"));
  FrmPerl->Left=StrToInt(INI("PlLeft"));
  FrmPerl->Top=StrToInt(INI("PlTop"));
  Memo1->Color=(TColor)StrToInt(INI("Color"));
  Memo1->Font->Charset=(TFontCharset)StrToInt(INI("FCharSet"));
  Memo1->Font->Color=(TColor)StrToInt(INI("FColor"));
  Memo1->Font->Name=INI("FName");
  Memo1->Font->Size=StrToInt(INI("FSize"));

  //FrmPerl->Memo1->Font->Charset=(TFontCharset)StrToInt(INI("CFCharSet"));
  //FrmPerl->Memo1->Font->Color=(TColor)StrToInt(INI("CFColor"));
  //FrmPerl->Memo1->Font->Name=INI("CFName");
 // FrmPerl->Memo1->Font->Size=StrToInt(INI("CFSize"));
//  FrmPerl->Edit1->Font=FrmPerl->Memo1->Font;
 // FrmPerl->Memo1->Color=Memo1->Color;
 // FrmPerl->Memo1->WordWrap=(INI("CWrap")=="1")?true:false;
//  FrmPerl->Memo1->ScrollBars=(FrmPerl->Memo1->WordWrap)?ssVertical:ssBoth;
  /*FrmPerl->mnWrap->Checked=FrmPerl->Memo1->WordWrap;*/}
 li_temp=new TStringList();

 SaveDialog1->InitialDir=FrmMeg1->di_megpas+"perltmp";
 RefreshTemp();
}
//---------------------------------------------------------------------------
void __fastcall TFrmPerl::ExecPerl(void){
 AnsiString cmd,st;
 cmd=INI("Extpl");
 if(cmd==""){Application->MessageBox("ｵﾌﾟｼｮﾝで拡張子「pl」にperl.exeのﾊﾟｽを設定してください。","Perl",MB_OK);return;}

 st=Memo1->Lines->Text;
 FrmMeg1->strReplace(st,"%target%","meg.tmp");

 TStringList *li_pl=new TStringList();
 li_pl->Text=st;
 li_pl->SaveToFile(FrmMeg1->di_megpas+"meg.pl");
 FrmMeg1->CallExec(cmd,FrmMeg1->di_megpas+"meg.pl","",false,true);
 delete li_pl;
}

void __fastcall TFrmPerl::Perl1Click(TObject *Sender)
{
// if(li_modify->Strings[index]=="1"&&!SaveText())return;
// AnsiString fi=li_file->Strings[index];
 FrmMeg1->Memo1->Lines->SaveToFile(FrmMeg1->di_megpas+"meg.tmp");
 ExecPerl();
}
//---------------------------------------------------------------------------
void __fastcall TFrmPerl::Perl2Click(TObject *Sender)
{TStringList *li_buf;
 li_buf=new TStringList();
 li_buf->Text=Clipboard()->AsText;
 li_buf->SaveToFile(FrmMeg1->di_megpas+"meg.tmp");
 delete li_buf;
 ExecPerl();
}
//---------------------------------------------------------------------------
void __fastcall TFrmPerl::ListFiles(AnsiString dirName,TMenuItem *OyaItem){
int RC,p;
TSearchRec SearchRec;
TMenuItem *KoItem;
AnsiString ss;
RC=FindFirst(dirName+"*.*",faAnyFile,SearchRec);
 while(RC==0){
  if(SearchRec.Name!=".."&&SearchRec.Name!="."){
   ss=dirName+SearchRec.Name;
   if((SearchRec.Attr&faDirectory)==0)AddTempItem(ss,OyaItem);
   if((SearchRec.Attr&faDirectory)>0){
    KoItem=new TMenuItem(OyaItem);
    KoItem->Caption=SearchRec.Name;
    OyaItem->Add(KoItem);
    ListFiles(ss+"\\",KoItem);}}
   RC=FindNext(SearchRec);}
 FindClose(SearchRec);
}
//---------------------------- AddTempItem
void __fastcall TFrmPerl::AddTempItem(AnsiString st,TMenuItem *OyaItem){
 TMenuItem *NewItem;
 NewItem=new TMenuItem(OyaItem);
 NewItem->Caption=ExtractFileName(st);
 NewItem->OnClick=LoadTemp;
 NewItem->Tag=li_temp->Count;
 OyaItem->Add(NewItem);
 li_temp->Add(st);}
//------------------
// RefreshTemp
void __fastcall TFrmPerl::RefreshTemp(void){
 int a,i;
// TMenuItem *ToItem; // goﾒﾆｭｰ
 li_temp->Clear();
 AnsiString st;
 a=mnTemp->Count;for(i=0;i<a;i++){mnTemp->Delete(0);}
 ListFiles(FrmMeg1->di_megpas+"perltmp\\",mnTemp);}

void __fastcall TFrmPerl::LoadTemp(TObject *Sender){
 Memo1->Lines->LoadFromFile(li_temp->Strings[((TMenuItem *)Sender)->Tag]);
 SaveDialog1->FileName=li_temp->Strings[((TMenuItem *)Sender)->Tag];
}

void __fastcall TFrmPerl::N3Click(TObject *Sender)
{
 Memo1->Clear();
 SaveDialog1->InitialDir=FrmMeg1->di_megpas+"perltmp";
 SaveDialog1->FileName="";
}
//---------------------------------------------------------------------------
void __fastcall TFrmPerl::N2Click(TObject *Sender)
{
 if(SaveDialog1->Execute()){
  Memo1->Lines->SaveToFile(SaveDialog1->FileName);RefreshTemp();}
}
//---------------------------------------------------------------------------

