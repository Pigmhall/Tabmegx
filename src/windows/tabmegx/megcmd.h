//---------------------------------------------------------------------------

#ifndef megcmdH
#define megcmdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFrmCmd : public TForm
{
__published:	// IDE 管理のコンポーネント
        TMemo *Memo1;
        TEdit *Edit1;
        TMainMenu *MainMenu1;
        TMenuItem *Menu1;
        TMenuItem *mnCommit;
        TMenuItem *mnWrap;
        TMenuItem *mnFind;
        TMenuItem *mnFindNext;
        TMenuItem *N2;
        TMenuItem *mnClose;
        TMenuItem *mnFont;
        TMenuItem *mnEditFocus;
        TFindDialog *FindDialog1;
        TMenuItem *N3;
        TMenuItem *mnKanji;
        TMenuItem *menuCol;
        TMenuItem *N1;
        TMenuItem *N4;
        TMenuItem *Excel1;
        TMenuItem *N5;
        TMenuItem *Exceltxt1;
        TSaveDialog *SaveDialog1;
        TMenuItem *mnSaveSelect;
        TButton *Button1;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall mnCommitClick(TObject *Sender);
        void __fastcall mnCloseClick(TObject *Sender);
        void __fastcall mnFontClick(TObject *Sender);
        void __fastcall mnEditFocusClick(TObject *Sender);
        void __fastcall mnFindClick(TObject *Sender);
        void __fastcall mnFindNextClick(TObject *Sender);
        void __fastcall FindDialog1Find(TObject *Sender);
        void __fastcall mnWrapClick(TObject *Sender);
        void __fastcall mnKanjiClick(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall Memo1Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Excel1Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall mnSaveSelectClick(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall Find(void);
        bool __fastcall FindText(AnsiString txt,bool MatchCase);
//        void __fastcall ToSjis(char *des,char *res,bool sql);
//        void __fastcall ToSjis(AnsiString &st,char *des,bool sql);
        int __fastcall CursorX(void);
        int __fastcall CursorY(void);
        void __fastcall SetMenuCol(void);
//        void __fastcall Sachi(AnsiString FindText);
        char kukeiCopy;int kukeiCopyX,kukeiCopyY;


public:		// ユーザー宣言
        __fastcall TFrmCmd(TComponent* Owner);
        void __fastcall Exec(AnsiString cmd,AnsiString dir,bool sql);
        PROCESS_INFORMATION ProcessInfo;
        bool isRun;//実行中
        AnsiString CurrentDir;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmCmd *FrmCmd;
//---------------------------------------------------------------------------
#endif
