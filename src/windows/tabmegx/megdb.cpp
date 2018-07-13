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
//--------- ̫��ޑI��
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );

 BI.hwndOwner = Handle;                     // �I�[�i�[�E�B���h�E�̃n���h��
 BI.pidlRoot = NULL;                        // ���[�g�t�H���_��ID���X�g
 BI.pszDisplayName = FName;                 // �I���t�H���_�̃p�X
 BI.lpszTitle = "AGK dir (Select 'Tier 1')";   // �\������
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // �t�H���_�̂ݑI��
 BI.lpfn = NULL;                            // �R�[���o�b�N�֐�
 BI.lParam = 0;                             // �R�[���o�b�N�֐��ɓn�����l
 BI.iImage = 0;                             // �I���t�H���_�̃C���[�W���X�g�C���f�b�N�X
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
//--------- ̫��ޑI��
 BROWSEINFO BI;  char DirPath[MAX_PATH];
 char FName[MAX_PATH];  LPITEMIDLIST ItemID;
 memset( &BI, 0, sizeof(BROWSEINFO) );
 memset( DirPath, 0, MAX_PATH );
 memset( FName, 0, MAX_PATH );
 BI.hwndOwner = Handle;                     // �I�[�i�[�E�B���h�E�̃n���h��
 BI.pidlRoot = NULL;                        // ���[�g�t�H���_��ID���X�g
 BI.pszDisplayName = FName;                 // �I���t�H���_�̃p�X
 BI.lpszTitle = "DarkBasic Pro dir";   // �\������
 BI.ulFlags = BIF_RETURNONLYFSDIRS;         // �t�H���_�̂ݑI��
 BI.lpfn = NULL;                            // �R�[���o�b�N�֐�
 BI.lParam = 0;                             // �R�[���o�b�N�֐��ɓn�����l
 BI.iImage = 0;                             // �I���t�H���_�̃C���[�W���X�g�C���f�b�N�X
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
