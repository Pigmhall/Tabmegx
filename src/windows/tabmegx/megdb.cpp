//---------------------------------------------------------------------------
#include <vcl.h>
#include <windowsx.h>
#pragma hdrstop

#include "megdb.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDb *frmDb;
//---------------------------------------------------------------------------
__fastcall TfrmDb::TfrmDb(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDb::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDb::btnAgkDirClick(TObject *Sender)
{
//--------- ﾌｫﾙﾀﾞ選択
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );

 BI.hwndOwner = Handle;                     // オーナーウィンドウのハンドル
 BI.pidlRoot = NULL;                        // ルートフォルダのIDリスト
 BI.pszDisplayName = FName;                 // 選択フォルダのパス
 BI.lpszTitle = "AGK dir (Select 'Tier 1')";   // 表示文字
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // フォルダのみ選択
 BI.lpfn = NULL;                            // コールバック関数
 BI.lParam = 0;                             // コールバック関数に渡される値
 BI.iImage = 0;                             // 選択フォルダのイメージリストインデックス
 ItemID = SHBrowseForFolder( &BI );
 SHGetPathFromIDList( ItemID, DirPath );
 GlobalFreePtr( ItemID );
 if(DirPath[0]!=0)edtAgkDir->Text=StrPas(DirPath)+"\\";
// if(DirPath[0]!=0)INI("dirDB")=StrPas(DirPath)+"\\";
// INI("Extg")=di_megpas+"gobln\\gobln.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
// INI("Extg2")=di_megpas+"gobln\\gobln2.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
// INI("Extg2")=di_megpas+"gobln.exe -g \x22%f\x22 -d \x22%d\x22";
        
}
//---------------------------------------------------------------------------
void __fastcall TfrmDb::btnDBProDirClick(TObject *Sender)
{
//--------- ﾌｫﾙﾀﾞ選択
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );
 BI.hwndOwner = Handle;                     // オーナーウィンドウのハンドル
 BI.pidlRoot = NULL;                        // ルートフォルダのIDリスト
 BI.pszDisplayName = FName;                 // 選択フォルダのパス
 BI.lpszTitle = "DarkBasic Pro dir";   // 表示文字
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // フォルダのみ選択
 BI.lpfn = NULL;                            // コールバック関数
 BI.lParam = 0;                             // コールバック関数に渡される値
 BI.iImage = 0;                             // 選択フォルダのイメージリストインデックス
 ItemID = SHBrowseForFolder( &BI );
 SHGetPathFromIDList( ItemID, DirPath );
 GlobalFreePtr( ItemID );

 if(DirPath[0]!=0)edtDbproDir->Text=StrPas(DirPath)+"\\";
 //INI("dirDB")=StrPas(DirPath)+"\\";
// INI("Extg")=di_megpas+"gobln\\gobln.exe -g \x22%f\x22 -d \x22%b\x22 -r %g";
// INI("Extg2")=di_megpas+"gobln.exe -g \x22%f\x22 -d \x22%d\x22";


}
//---------------------------------------------------------------------------
void __fastcall TfrmDb::Button2Click(TObject *Sender)
{
 ModalResult=mrCancel;

}
//---------------------------------------------------------------------------
