//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#define INI(X) FrmMeg1->li_ini->Values[X]
#include "megmsx.h"
#include "megson1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMsx *frmMsx;
//---------------------------------------------------------------------------
__fastcall TfrmMsx::TfrmMsx(TComponent* Owner)
        : TForm(Owner)
{btnLSDefClick(NULL);if(INI("Ccz80GenBas")==""){
  FrmMeg1->MSXoption1Click(NULL);}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::Button3Click(TObject *Sender)
{
 OpenDialog1->Filter="editdisk.exe;DISKMGR.exe|editdisk.exe;DISKMGR.exe";
 OpenDialog1->FileName=edtDiskExplorer->Text;
 if(OpenDialog1->Execute()){
  edtDiskExplorer->Text=OpenDialog1->FileName;}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::Button4Click(TObject *Sender)
{
 OpenDialog1->Filter="blueMSX.exe;openmsx.exe;PC-CPC.exe;WinApe.exe|blueMSX.exe;openmsx.exe;PC-CPC.exe;WinApe.exe";
 OpenDialog1->FileName=edtMsxEmu->Text;
 if(OpenDialog1->Execute()){
  edtMsxEmu->Text=OpenDialog1->FileName;
  AnsiString st=ExtractFileName(edtMsxEmu->Text).LowerCase();
  if(st.AnsiPos("openmsx")&&edtDirAsDisk->Text==""){
   edtDirAsDisk->Text=FrmMeg1->di_megpas+"openmsxdir";}
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::Button5Click(TObject *Sender)
{
 OpenDialog1->Filter="ccz80.exe|ccz80.exe";
 OpenDialog1->FileName=edtCcz80->Text;
 if(OpenDialog1->Execute()){
  edtCcz80->Text=OpenDialog1->FileName;
  AnsiString di=ExtractFilePath(ExtractFileDir(OpenDialog1->FileName));
  edtIncludePath->Text=di+"include;"+di+"systems\\msx\\include";
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsx::Button1Click(TObject *Sender)
{
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsx::Button2Click(TObject *Sender)
{
 ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::BtnCcz80pp(TObject *Sender)
{
 OpenDialog1->Filter="ccz80++.exe|ccz80++.exe";
 OpenDialog1->FileName=edtCcz80p->Text;
 if(OpenDialog1->Execute()){
  edtCcz80p->Text=OpenDialog1->FileName;
  AnsiString di=ExtractFilePath(ExtractFileDir(OpenDialog1->FileName));
  edtPath->Text=di+"classes\\generic;"+di+"classes\\msx;"+FrmMeg1->di_megpas+"classes;"+di+"library\\cpc\\GameUtils\\classes";
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::chkExportBinClick(TObject *Sender)
{
 chkMakeLoader->Enabled=true;
 edtLoaderScript->Enabled=true;
 edtRomSize->Enabled=false;
 if(Visible){edtOrgAddress->Text=INI("BasOrg");}
}
void __fastcall TfrmMsx::chkExportRomClick(TObject *Sender)
{
// chkGenBasicLoader->Enabled=!chkExportRom->Checked;
 chkMakeLoader->Enabled=false;
 edtLoaderScript->Enabled=false;
 edtRomSize->Enabled=true;
 edtDataAddress->Enabled=true;
 if(Visible){
  //if(chkExportRom->Checked){
   INI("BasOrg")=edtOrgAddress->Text;edtOrgAddress->Text="4000";
   if(edtDataAddress->Text=="")edtDataAddress->Text="c000";
   if(edtRomSize->Text=="")edtRomSize->Text="16384";
//   }
//  else{edtOrgAddress->Text=INI("BasOrg");}
 }
}
//
void __fastcall TfrmMsx::chkExportComClick(TObject *Sender)
{
 chkMakeLoader->Enabled=false;
 edtLoaderScript->Enabled=false;
 edtRomSize->Enabled=false;
 edtDataAddress->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsx::Button7Click(TObject *Sender)
{
 OpenDialog1->Filter="*.exe|*.exe";
 OpenDialog1->FileName=edtMgsPlayer->Text;
 if(OpenDialog1->Execute()){
  edtMgsPlayer->Text=OpenDialog1->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::btnLSDefClick(TObject *Sender)
{
 edtLoaderScript->Text=FrmMeg1->defaultLoaderScript();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsx::chkExportExbinClick(TObject *Sender)
{
 chkMakeLoader->Enabled=true;
 edtLoaderScript->Enabled=true;
 edtRomSize->Enabled=true;
}
//---------------------------------------------------------------------------

