//---------------------------------------------------------------------------

#ifndef megkeyasH
#define megkeyasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrmKeyas : public TForm
{
__published:	// IDE 管理のコンポーネント
        TLabel *Label1;
        TEdit *EdtCtrl1;
        TLabel *Label2;
        TEdit *EdtSCtrl1;
        TEdit *EdtSCtrl2;
        TEdit *EdtCtrl2;
        TLabel *Label3;
        TEdit *EdtSCtrl3;
        TEdit *EdtCtrl3;
        TLabel *Label4;
        TEdit *EdtSCtrl4;
        TEdit *EdtCtrl4;
        TLabel *Label5;
        TEdit *EdtSCtrl5;
        TEdit *EdtCtrl5;
        TLabel *Label6;
        TEdit *EdtSCtrl6;
        TEdit *EdtCtrl6;
        TLabel *Label7;
        TEdit *EdtSCtrl7;
        TEdit *EdtCtrl7;
        TLabel *Label8;
        TEdit *EdtSCtrl8;
        TEdit *EdtCtrl8;
        TLabel *Label9;
        TEdit *EdtSCtrl9;
        TEdit *EdtCtrl9;
        TLabel *Label10;
        TEdit *EdtSCtrl0;
        TEdit *EdtCtrl0;
        TLabel *Label11;
        TButton *Button1;
        TButton *Button2;
        TLabel *Label12;
        TComboBox *ComboBox1;
        TEdit *EdtAltX;
        TButton *Button3;
        TEdit *EdtShiftAltX;
        TButton *BtnHtml;
        TButton *Button4;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *n2;
        TMenuItem *t1;
        TMenuItem *v1;
        TMenuItem *CLIP1;
        TMenuItem *DATE1;
        TMenuItem *N3;
        TMenuItem *TIME1;
        TMenuItem *INPUT1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BtnHtmlClick(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall mnStrSp(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TFrmKeyas(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmKeyas *FrmKeyas;
//---------------------------------------------------------------------------
#endif
