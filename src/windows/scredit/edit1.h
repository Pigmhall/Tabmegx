//---------------------------------------------------------------------------

#ifndef edit1H
#define edit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmEdit : public TForm
{
__published:	// IDE 管理のコンポーネント
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TMenuItem *Edit1;
        TMenuItem *Clear1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TMenuItem *mnChrEdit;
        TMenuItem *Coord1;
        TMenuItem *mnModify1;
        TMenuItem *Saveas1;
        TImage *Image2_2;
        TMenuItem *mnExport;
        TBitBtn *BitBtn2;
        TBitBtn *btnSpoit;
        TBitBtn *btnNextChr;
        TBitBtn *BitBtn1;
        TBitBtn *btnRight;
        TBitBtn *btnDown;
        TBitBtn *btnUp;
        TBitBtn *btnLeft;
        TBitBtn *btnSave;
        TBitBtn *btnOpen;
        TBitBtn *btnNew;
        TMenuItem *mnStatus;
        TMenuItem *mnCopy;
        TTimer *Timer1;
        TBitBtn *btnText;
        TMenuItem *N2;
        TMenuItem *Spoit1;
        TMenuItem *InsertTex1;
        TMenuItem *Fill1;
        TMenuItem *ExportCCZ801;
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Clear1Click(TObject *Sender);
        void __fastcall NextFloor1Click(TObject *Sender);
        void __fastcall Back1Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mnChrEditClick(TObject *Sender);
        void __fastcall Coord1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall Copy1Click(TObject *Sender);
        void __fastcall Paste1Click(TObject *Sender);
        void __fastcall mnExportClick(TObject *Sender);
        void __fastcall btnLeftClick(TObject *Sender);
        void __fastcall btnRightClick(TObject *Sender);
        void __fastcall btnUpClick(TObject *Sender);
        void __fastcall btnDownClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall btnNextChrClick(TObject *Sender);
        void __fastcall btnSpoitClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall btnTextClick(TObject *Sender);
        void __fastcall Fill1Click(TObject *Sender);
        void __fastcall ExportCCZ801Click(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall PutBlocks(void);
        void __fastcall PutFloor(void);
        void __fastcall LoadImage(AnsiString fi);
        void __fastcall RefreshCursorStatus(int x,int y);
	void __fastcall WMDROPFILES(TWMDropFiles Msg);
        BEGIN_MESSAGE_MAP
         MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,WMDROPFILES)
        END_MESSAGE_MAP(TForm)
        void __fastcall RefreshStatus(void);
        void __fastcall RefreshCopyStatus(void);
        void __fastcall SetModify(void);
        void __fastcall ResetModify(void);
        bool __fastcall SaveFile(void);
        bool __fastcall SavePrompt(void);
public:		// ユーザー宣言
        __fastcall TfrmEdit(TComponent* Owner);
        void __fastcall InsertText(void);
        int gsz;
        TStringList *li_ini;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEdit *frmEdit;
//---------------------------------------------------------------------------
#endif
