//---------------------------------------------------------------------------

#ifndef megmsxH
#define megmsxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmMsx : public TForm
{
__published:	// IDE 管理のコンポーネント
        TEdit *edtDiskExplorer;
        TLabel *Label1;
        TEdit *edtMsxEmu;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *edtCcz80;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *edtLoaderScript;
        TEdit *edtIncludePath;
        TLabel *Label8;
        TEdit *edtOrgAddress;
        TLabel *Label9;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TOpenDialog *OpenDialog1;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *edtDirAsDisk;
        TEdit *edtMachine;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *edtCcz80p;
        TButton *Button6;
        TEdit *edtPath;
        TLabel *Label15;
        TComboBox *edtRomSize;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *edtDataAddress;
        TRadioButton *chkExportBin;
        TRadioButton *chkExportRom;
        TRadioButton *chkExportCom;
        TLabel *Label18;
        TCheckBox *chkMakeLoader;
        TCheckBox *chkDragDsk;
        TLabel *Label7;
        TEdit *edtMgsPlayer;
        TButton *Button7;
        TButton *btnLSDef;
        TRadioButton *chkExportExbin;
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall chkExportBinClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall chkExportRomClick(TObject *Sender);
        void __fastcall BtnCcz80pp(TObject *Sender);
        void __fastcall chkExportComClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall btnLSDefClick(TObject *Sender);
        void __fastcall chkExportExbinClick(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmMsx(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMsx *frmMsx;
//---------------------------------------------------------------------------
#endif
