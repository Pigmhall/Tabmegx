//---------------------------------------------------------------------------

#ifndef colorH
#define colorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmColor : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TTrackBar *tbR;
        TLabel *lblR;
        TTrackBar *tbG;
        TLabel *lblG;
        TTrackBar *tbB;
        TLabel *lblB;
        TButton *OK;
        TButton *Button1;
        TImage *Image1;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall tbRChange(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TfrmColor(TComponent* Owner);
        void __fastcall RefreshPal(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmColor *frmColor;
//---------------------------------------------------------------------------
#endif
