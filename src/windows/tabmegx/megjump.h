//---------------------------------------------------------------------------

#ifndef megjumpH
#define megjumpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmJump : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TListBox *ListBox1;
        void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TFrmJump(TComponent* Owner);
        void __fastcall MakeList(void);
        int __fastcall GetLineNo(void);
        void __fastcall MakeKouho(AnsiString st);
        TStringList *li_no;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmJump *FrmJump;
//---------------------------------------------------------------------------
#endif
