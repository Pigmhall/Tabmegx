//---------------------------------------------------------------------------

#ifndef megdbH
#define megdbH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmDb : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TButton *btnDBProDir;
        TButton *btnAgkDir;
        TEdit *edtAgkDir;
        TEdit *edtDbproDir;
        TLabel *Label19;
        TLabel *Label7;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btnAgkDirClick(TObject *Sender);
        void __fastcall btnDBProDirClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TfrmDb(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDb *frmDb;
//---------------------------------------------------------------------------
#endif
