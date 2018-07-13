//---------------------------------------------------------------------------

#ifndef tbnewH
#define tbnewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmNew : public TForm
{
__published:	// IDE 管理のコンポーネント
        TEdit *edtW;
        TEdit *edtH;
        TLabel *Label1;
        TLabel *Label2;
        TUpDown *udW;
        TUpDown *udH;
        TButton *Button1;
        TButton *OK;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNew *frmNew;
//---------------------------------------------------------------------------
#endif
