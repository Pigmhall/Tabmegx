//---------------------------------------------------------------------------
#ifndef gobln1H
#define gobln1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TMemo *Memo1;
	TPanel *Panel1;
	TButton *Button1;
	TLabel *Label1;
	TTimer *Timer1;
	TMemo *Memo2;
	TFindDialog *FindDialog1;
	void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	
	void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Memo2MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall FindDialog1Find(TObject *Sender);
private:	// ユーザー宣言
	void __fastcall Exec(AnsiString cmd,AnsiString dir);
        PROCESS_INFORMATION ProcessInfo;
        void __fastcall ModifyCol(void);
        void __fastcall Memo1Scroll(void);
        bool __fastcall FindText(AnsiString txt,bool MatchCase);
        void __fastcall Find(void);
public:		// ユーザー宣言
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
