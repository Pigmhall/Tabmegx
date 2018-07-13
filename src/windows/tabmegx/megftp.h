//---------------------------------------------------------------------------

#ifndef megftpH
#define megftpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <NMFtp.hpp>
#include <Psock.hpp>
//---------------------------------------------------------------------------
/*#define PopName 0
#define PopHost 1
#define PopUser 2
#define PopPassword 3
#define PopPort 4
#define PopApop 5
#define P_NAME(a) GetSplit(PopName,li_pop->Strings[a])
#define P_HOST(a) GetSplit(PopHost,li_pop->Strings[a])
#define P_USER(a) GetSplit(PopUser,li_pop->Strings[a])
#define P_PASSWD(a) GetSplit(PopPassword,li_pop->Strings[a])
#define P_PORT(a) GetSplit(PopPort,li_pop->Strings[a])
#define P_APOP(a) GetSplit(PopApop,li_pop->Strings[a])*/

class TFrmFtp : public TForm
{
__published:	// IDE 管理のコンポーネント
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *EdtHost;
        TEdit *EdtUser;
        TEdit *EdtPasswd;
        TEdit *EdtServerDir;
        TCheckBox *ChkPassive;
        TEdit *EdtChmod;
        TButton *Button1;
        TButton *Button2;
        TComboBox *CmbName;
        TButton *Button3;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall EdtHostKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall CmbNameKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CmbNameChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// ユーザー宣言
        void __fastcall ExtractPa(int a);
        bool __fastcall SavePa(int a);

public:		// ユーザー宣言
        __fastcall TFrmFtp(TComponent* Owner);
        void __fastcall LoadAllIni(void);
        void __fastcall SaveAllIni(void);
//        void __fastcall Upload(int a,AnsiString sdir,AnsiString fi);
//        int __fastcall NameToNum(AnsiString sv);
        TStringList *li_ftp;
        int sel;
//        bool isFtp;//FTP中true
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmFtp *FrmFtp;
//---------------------------------------------------------------------------
#endif

