//---------------------------------------------------------------------------
#ifndef fpc1H
#define fpc1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TMemo *Memo1;
	TPanel *Panel1;
	TEdit *Edit1;
	TTimer *Timer1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// ユーザー宣言
    int mo;
    bool __fastcall FindText(AnsiString txt,bool MatchCase);
    void __fastcall hideWindow(void);
public:		// ユーザー宣言
	__fastcall TForm1(TComponent* Owner);
    bool __fastcall convert(AnsiString fi_in,AnsiString fi_out);
    void __fastcall exportRomAsm(AnsiString fi_in,AnsiString fi_out,bool isCom,bool isExbin);
    void __fastcall genRom(AnsiString fi_in,int kb);
    void __fastcall bsave(AnsiString fi_in,AnsiString fi_out);
    void __fastcall bsaveExbin(AnsiString fi_in,AnsiString fi_out);
        };
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
