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
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TMemo *Memo1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TfrmOutput(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOutput *frmOutput;
//---------------------------------------------------------------------------
#endif
