//---------------------------------------------------------------------------

#ifndef megnumberH
#define megnumberH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmNumber : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TFrmNumber(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmNumber *FrmNumber;
//---------------------------------------------------------------------------
#endif
