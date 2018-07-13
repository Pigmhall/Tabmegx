//---------------------------------------------------------------------------

#ifndef frmPrintH
#define frmPrintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmPrin : public TForm
{
__published:	// IDE 管理のコンポーネント
        TEdit *Edit1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmPrin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrin *frmPrin;
//---------------------------------------------------------------------------
#endif
