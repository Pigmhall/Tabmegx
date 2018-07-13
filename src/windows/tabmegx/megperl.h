//---------------------------------------------------------------------------

#ifndef megperlH
#define megperlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFrmPerl : public TForm
{
__published:	// IDE 管理のコンポーネント
        TMemo *Memo1;
        TMainMenu *MainMenu1;
        TMenuItem *M1;
        TMenuItem *Perl1;
        TMenuItem *Perl2;
        TMenuItem *mnTemp;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *X1;
        TSaveDialog *SaveDialog1;
        void __fastcall Perl1Click(TObject *Sender);
        void __fastcall Perl2Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall ListFiles(AnsiString dirName,TMenuItem *OyaItem);
        void __fastcall AddTempItem(AnsiString st,TMenuItem *OyaItem);
        void __fastcall RefreshTemp(void);
        void __fastcall LoadTemp(TObject *Sender);
        TStringList *li_temp;
public:		// ユーザー宣言
        __fastcall TFrmPerl(TComponent* Owner);
        void __fastcall ExecPerl(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrmPerl *FrmPerl;
//---------------------------------------------------------------------------
#endif
