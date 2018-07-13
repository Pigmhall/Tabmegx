//---------------------------------------------------------------------------

#ifndef megrepH
#define megrepH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmRep : public TForm
{
__published:	// IDE 管理のコンポーネント
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmRep(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRep *frmRep;
//---------------------------------------------------------------------------
#endif
