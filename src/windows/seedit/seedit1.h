//---------------------------------------------------------------------------

#ifndef seedit1H
#define seedit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmSe : public TForm
{
__published:	// IDE 管理のコンポーネント
        TListBox *lbSe;
        TListBox *lbChannel;
        TListBox *lbData;
        TLabel *Label1;
        TLabel *Label3;
        TBitBtn *btnSeAdd;
        TBitBtn *btnSeProperty;
        TBitBtn *btnSeDelete;
        TBitBtn *btnChannelDelete;
        TBitBtn *btnChannelProperty;
        TBitBtn *btnChannelAdd;
        TBitBtn *btnDataDelete;
        TBitBtn *btnDataProperty;
        TBitBtn *btnDataAdd;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *mnOpen;
        TMenuItem *mnSave;
        TMenuItem *mnExport;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog2;
        TMenuItem *mnNew;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *mnQuit;
        TMenuItem *ExportasText1;
        TBitBtn *btnUp;
        TBitBtn *btnDown;
        TMenuItem *Saveas1;
        TMenuItem *mnMod;
        TMenuItem *Export1;
        TMenuItem *ccZ801;
        void __fastcall btnSeAddClick(TObject *Sender);
        void __fastcall btnDataAddClick(TObject *Sender);
        void __fastcall btnDataPropertyClick(TObject *Sender);
        void __fastcall mnExportClick(TObject *Sender);
        void __fastcall mnSaveClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnChannelAddClick(TObject *Sender);
        void __fastcall lbChannelClick(TObject *Sender);
        void __fastcall mnOpenClick(TObject *Sender);
        void __fastcall mnQuitClick(TObject *Sender);
        void __fastcall mnNewClick(TObject *Sender);
        void __fastcall lbSeClick(TObject *Sender);
        void __fastcall btnDataDeleteClick(TObject *Sender);
        void __fastcall ExportasText1Click(TObject *Sender);
        void __fastcall btnSePropertyClick(TObject *Sender);
        void __fastcall btnUpClick(TObject *Sender);
        void __fastcall btnDownClick(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall ccZ801Click(TObject *Sender);
        void __fastcall btnSeDeleteClick(TObject *Sender);
private:	// ユーザー宣言
        bool isMod;
        void __fastcall AddChannel(int c);
        void __fastcall RefreshDataList(void);
        void __fastcall RefreshChannelList(void);
        void __fastcall ExportNse(char mod);
        void __fastcall Mod(bool a);
        bool __fastcall CheckMod(void);
        bool __fastcall SaveFile(bool isSaveas);
        void __fastcall RefreshSeList(void);
public:		// ユーザー宣言
        __fastcall TfrmSe(TComponent* Owner);
        void __fastcall Split(AnsiString txt,char c);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSe *frmSe;
//---------------------------------------------------------------------------
#endif
