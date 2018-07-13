//---------------------------------------------------------------------------

#ifndef palette1H
#define palette1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#define BITS ((frmPal->chk5bits->Checked)?8:32)
#define BITSZ ((frmPal->chk5bits->Checked)?7:15)
//---------------------------------------------------------------------------
class TfrmPal : public TForm
{
__published:	// IDE 管理のコンポーネント
        TImage *Image1;
        TMemo *Memo1;
        TStatusBar *StatusBar1;
        TComboBox *ComboBox1;
        TButton *btAdd;
        TButton *btDel;
        TTimer *Timer1;
        TBitBtn *btSave;
        TBitBtn *btCopy;
        TBitBtn *btQuit;
        TBitBtn *btCopyExit;
        TImage *Image2;
        TCheckBox *chk5bits;
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btDefaultClick(TObject *Sender);
        void __fastcall btCopyClick(TObject *Sender);
        void __fastcall btSaveClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall btAddClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall btDelClick(TObject *Sender);
        void __fastcall btCopyExitClick(TObject *Sender);
        void __fastcall chk5bitsClick(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall Generate(void);
        void __fastcall RefreshList(void);
public:		// ユーザー宣言
        __fastcall TfrmPal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPal *frmPal;
//---------------------------------------------------------------------------
#endif
