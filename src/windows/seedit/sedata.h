//---------------------------------------------------------------------------

#ifndef sedataH
#define sedataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmData : public TForm
{
__published:	// IDE 管理のコンポーネント
        TButton *btnOk;
        TButton *btnCancel;
        TComboBox *cmbType;
        TLabel *Label1;
        TEdit *edtParam1;
        TLabel *lblParam1;
        TLabel *lblRange1;
        TEdit *edtParam2;
        TLabel *lblParam2;
        TLabel *lblRange2;
        TEdit *edtParam3;
        TLabel *lblParam3;
        TLabel *lblRange3;
        void __fastcall cmbTypeChange(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmData(TComponent* Owner);
        AnsiString __fastcall getValueStr(void);
        AnsiString __fastcall codeToName(AnsiString cod);
        void __fastcall setFormFromData(AnsiString st,int pa1,int pa2,int pa3);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmData *frmData;
//---------------------------------------------------------------------------
#endif
