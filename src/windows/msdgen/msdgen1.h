//---------------------------------------------------------------------------

#ifndef msdgen1H
#define msdgen1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TDriveComboBox *DriveComboBox1;
        TFileListBox *FileList1;
        TDirectoryListBox *DirectoryListBox1;
        TMemo *Memo1;
        TImage *Image1;
        TButton *Button1;
        TImage *Image2;
        TRadioButton *rbSprite;
        TRadioButton *rbCharacter;
        TGroupBox *GroupBox1;
        TRadioButton *rbCcz80;
        TRadioButton *rbBasic;
        TButton *Button2;
        TRadioButton *rbQq;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TListBox *FileListBox1;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TBitBtn *btnLock;
        TCheckBox *chkTwoSprites;
        TRadioButton *rbGraphic;
        TCheckBox *chk256;
        TImage *Image3;
        TCheckBox *chkCompress;
        TComboBox *ComboBox1;
        TStatusBar *StatusBar1;
        TCheckBox *chkOneColor;
        TCheckBox *chkDummyR;
        void __fastcall FileList1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall GenSp(int sx,int sy);
        void __fastcall GenSp2(int sx,int sy);
        void __fastcall GenSp21(int sx,int sy);
        void __fastcall GenCh(int sx,int sy);
        void __fastcall GenGra(int sx,int sy);
        void __fastcall GenGraBin(int sx,int sy);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FileRefresh(void);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall btnLockClick(TObject *Sender);
        void __fastcall DirectoryListBox1Change(TObject *Sender);
        void __fastcall AddEndComma(void);
        void __fastcall ComboBox1Change(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall GenCompress(AnsiString fi,int org_len);
        void __fastcall reloadCols(void);
void __fastcall WMDROPFILES(TWMDropFiles Msg);
  BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,WMDROPFILES)
  END_MESSAGE_MAP(TForm)
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
