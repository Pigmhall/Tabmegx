//---------------------------------------------------------------------------

#ifndef chreditH
#define chreditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmChrEdit : public TForm
{
__published:	// IDE 管理のコンポーネント
        TBitBtn *btnOpen;
        TBitBtn *btnSave;
        TImage *Image2;
        TImage *Image3;
        TBitBtn *btnLoadD;
        TOpenDialog *OpenDialog1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TSaveDialog *SaveDialog1;
        TImage *Image1;
        TTimer *Timer1;
        TLabel *lblCnt;
        void __fastcall btnLoadDClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnOpenClick(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall RefreshChrs(void);
public:		// ユーザー宣言
        __fastcall TfrmChrEdit(TComponent* Owner);
        int SZ;
        AnsiString bmpFile;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChrEdit *frmChrEdit;
//---------------------------------------------------------------------------
#endif
