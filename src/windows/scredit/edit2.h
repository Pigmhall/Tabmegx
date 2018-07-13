//---------------------------------------------------------------------------

#ifndef edit2H
#define edit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmCoord : public TForm
{
__published:	// IDE 管理のコンポーネント
        TLabel *Label1;
        TEdit *EdtWidth;
        TLabel *Label2;
        TEdit *EdtHeight;
        TButton *Button1;
        TLabel *Label3;
        TEdit *EdtSwx;
        TLabel *Label4;
        TEdit *EdtSwy;
        void __fastcall Button1Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TFrmCoord(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmCoord *FrmCoord;
//---------------------------------------------------------------------------
#endif
