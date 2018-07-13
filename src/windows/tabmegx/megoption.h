//---------------------------------------------------------------------------

#ifndef megoptionH
#define megoptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFrmOption : public TForm
{
__published:	// IDE 管理のコンポーネント
        TEdit *EdtFileMask;
        TButton *Button1;
        TButton *Button2;
        TLabel *Label1;
        TCheckBox *ChkSjisOnly;
        TCheckBox *ChkAutoIndent;
        TComboBox *CmbExt;
        TEdit *EdtCmd;
        TButton *Button4;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *EdtDbname;
        TLabel *Label5;
        TEdit *EdtDbuser;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *EdtDbpasswd;
        TComboBox *CmbDbd;
        TLabel *Label8;
        TEdit *EdtDbhost;
        TComboBox *CmbDbknj;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TButton *BtnBrowse0;
        TButton *Button5;
        TLabel *Label13;
        TComboBox *CmbFx;
        TLabel *Label15;
        TEdit *EdtFxcmd;
        TButton *BtnBrowse1;
        TButton *Button7;
        TLabel *Label14;
        TEdit *EdtFuncJump;
        TLabel *Label12;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *EdtWinScp;
        TButton *Button3;
        TEdit *EdtWinScpMod;
        TLabel *Label18;
        TLabel *Label19;
        TEdit *EdtButkey1;
        TEdit *EdtButkey2;
        TEdit *EdtButkey3;
        TEdit *EdtBtnKeySizeX;
        TLabel *Label20;
        TEdit *EdtBtnKeySizeY;
        TLabel *Label21;
        TOpenDialog *OpenDialog1;
        TLabel *Label22;
        TEdit *EdtSuggestion;
        TLabel *Label23;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall CmbExtChange(TObject *Sender);
        void __fastcall BtnBrowse0Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall CmbFxChange(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TFrmOption(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmOption *FrmOption;
//---------------------------------------------------------------------------
#endif
