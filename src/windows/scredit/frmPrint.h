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
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TEdit *Edit1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TfrmPrin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrin *frmPrin;
//---------------------------------------------------------------------------
#endif
