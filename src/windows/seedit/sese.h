//---------------------------------------------------------------------------

#ifndef seseH
#define seseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmSeSet : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TCheckBox *ChkNoise;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label1;
        TEdit *EdtName;
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TFrmSeSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSeSet *FrmSeSet;
//---------------------------------------------------------------------------
#endif
