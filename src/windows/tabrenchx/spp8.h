//---------------------------------------------------------------------------

#ifndef spp8H
#define spp8H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmP8 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TMemo *Memo1;
        TEdit *edtSpn;
        TLabel *spnum;
        TButton *Set;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall SetClick(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TfrmP8(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmP8 *frmP8;
//---------------------------------------------------------------------------
#endif
