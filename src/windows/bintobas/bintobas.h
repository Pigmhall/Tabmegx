//---------------------------------------------------------------------------

#ifndef bintobasH
#define bintobasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TOpenDialog *OpenDialog1;
        TMemo *Memo1;
        TPanel *Panel1;
        TButton *Button1;
        TEdit *edtNum;
        TRadioButton *RadioButton1;
        TRadioButton *chkCcz80;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
