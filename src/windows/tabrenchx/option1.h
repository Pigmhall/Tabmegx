//---------------------------------------------------------------------------

#ifndef option1H
#define option1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmOption : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TLabel *Label1;
        TEdit *EdtWidth;
        TEdit *EdtHeight;
        TLabel *Label2;
        TEdit *EdtDotSize;
        TLabel *Label3;
        TButton *Button1;
        TButton *Button2;
        TLabel *LblWindow;
        TCheckBox *chk256;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall EdtWidthChange(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TFrmOption(TComponent* Owner);
        void __fastcall RefreshWindow(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmOption *FrmOption;
//---------------------------------------------------------------------------
#endif
