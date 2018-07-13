//---------------------------------------------------------------------------

#ifndef output1H
#define output1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmOutput : public TForm
{
__published:	// IDE 管理のコンポーネント
        TMemo *Memo1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmOutput(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOutput *frmOutput;
//---------------------------------------------------------------------------
#endif
