//---------------------------------------------------------------------------

#ifndef palNewH
#define palNewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmNew : public TForm
{
__published:	// IDE 管理のコンポーネント
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNew *frmNew;
//---------------------------------------------------------------------------
#endif
