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
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TfrmNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNew *frmNew;
//---------------------------------------------------------------------------
#endif
