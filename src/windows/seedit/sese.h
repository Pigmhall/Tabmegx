//---------------------------------------------------------------------------

#ifndef seseH
#define seseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmSeSet : public TForm
{
__published:	// IDE 管理のコンポーネント
        TCheckBox *ChkNoise;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label1;
        TEdit *EdtName;
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TFrmSeSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSeSet *FrmSeSet;
//---------------------------------------------------------------------------
#endif
