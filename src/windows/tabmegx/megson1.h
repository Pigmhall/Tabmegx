//---------------------------------------------------------------------------
#ifndef megson1H
#define megson1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//#include "fod.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//#include "jis2000.h"

//---------------------------------------------------------------------------
#define M_TXT 64

class TFrmMeg1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TTabControl *TabControl1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Saveas1;
        TMenuItem *Close1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TMenuItem *Edit1;
        TMenuItem *Pasteasnew1;
        TMenuItem *Selectall1;
        TMenuItem *N2;
        TMenuItem *Find1;
        TMenuItem *Findnext1;
        TMenuItem *Replace1;
        TMenuItem *Goto1;
        TMenuItem *N3;
        TMenuItem *mnRenban;
        TMenuItem *mnKeisan;
        TMenuItem *View1;
        TMenuItem *Next1;
        TMenuItem *Back1;
        TMenuItem *Maximize1;
        TMenuItem *mnWrap;
        TMenuItem *Font1;
        TMenuItem *Background1;
        TMenuItem *mnTag;
        TMenuItem *N17;
        TMenuItem *mnTagAssign;
        TMenuItem *N19;
        TMenuItem *Browse1;
        TMenuItem *mnCommand;
        TMenuItem *menuCol;
        TMenuItem *Color1;
        TMenuItem *N20;
        TFindDialog *FindDialog1;
        TReplaceDialog *ReplaceDialog1;
        TMenuItem *menuModify;
        TMenuItem *mnKnj;
        TMenuItem *SJIS1;
        TMenuItem *EUC1;
        TMenuItem *JIS1;
        TMenuItem *UTF81;
        TMenuItem *Unicode1;
        TMenuItem *Backup1;
        TMenuItem *mnOption;
        TMenuItem *N4;
        TMenuItem *SaveFTP1;
        TMenuItem *N5;
        TMenuItem *FTPsetting1;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *SQL1;
        TMenuItem *Commit1;
        TMenuItem *mnHelp;
        TMenuItem *N10;
        TMenuItem *mnCtrlF5;
        TMenuItem *mnCtrlF1;
        TMenuItem *mnCtrlF2;
        TMenuItem *mnCtrlF3;
        TMenuItem *mnCtrlF4;
        TMenuItem *N11;
        TPopupMenu *PopupMenu1;
        TMenuItem *C1;
        TMenuItem *mnAbout;
        TMenuItem *J1;
        TMenuItem *mnKouho;
        TListBox *ListBox1;
        TMenuItem *mnKukeiCopy;
        TMenuItem *mnTojikigo;
        TMenuItem *mnTextPerl;
        TPanel *PnlTop;
        TPanel *PnlBottom;
        TMemo *Memo1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TStatusBar *StatusBar1;
        TMenuItem *mnCopy;
        TMenuItem *mnCut;
        TMenuItem *mnPaste;
        TMenuItem *N8;
        TBitBtn *btnCut;
        TBitBtn *btnCopy;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TButton *btnShift;
        TMenuItem *Tool1;
        TMenuItem *SpriteEditor1;
        TMenuItem *CharacterEditor1;
        TMenuItem *SpriteDataGenerator1;
        TMenuItem *CharactorDataGenerator1;
        TMenuItem *MSXoption1;
        TMenuItem *SourceASMorBAS1;
        TMenuItem *N9;
        TMenuItem *NewDB1;
        TBitBtn *BitSource;
        TMenuItem *copyy1;
        TMenuItem *copyyz1;
        TBitBtn *btnHelp;
        TBitBtn *btnData;
        TBitBtn *BitBtn5;
        TMenuItem *Bin2Bas1;
        TMenuItem *ScreenEdit1;
        TMenuItem *mnSettarget;
        TMenuItem *GraphicEditor;
        TMenuItem *GraphicDataGenerator1;
        TMenuItem *PaletteEditor1;
        TMenuItem *N12;
        TMenuItem *Help1;
        TMenuItem *mnClass;
        TMenuItem *mnAlt;
        TMenuItem *mnShiftAlt;
        TMenuItem *mnAlt1;
        TMenuItem *mnAlt2;
        TMenuItem *mnAlt3;
        TMenuItem *mnAlt4;
        TMenuItem *mnAlt5;
        TMenuItem *mnAlt6;
        TMenuItem *mnAlt7;
        TMenuItem *mnAlt8;
        TMenuItem *mnAlt9;
        TMenuItem *mnAlt0;
        TMenuItem *mnShiftAlt1;
        TMenuItem *mnShiftAlt2;
        TMenuItem *mnShiftAlt3;
        TMenuItem *mnShiftAlt4;
        TMenuItem *mnShiftAlt5;
        TMenuItem *mnShiftAlt6;
        TMenuItem *mnShiftAlt7;
        TMenuItem *mnShiftAlt8;
        TMenuItem *mnShiftAlt9;
        TMenuItem *mnShiftAlt0;
        TMenuItem *Wordlist1;
        TMenuItem *mnWlMsx;
        TMenuItem *mnWlDbpro;
        TMenuItem *mnWlAgk;
        TMenuItem *NewAGK1;
        TMenuItem *popHidetopbuttons;
        TMenuItem *HextobitbusterHex1;
        TMenuItem *DarkBasicsetting1;
        TMenuItem *mnDiskManager;
        TMenuItem *mnMmlHelp;
        TMenuItem *SoundEditor1;
        TMenuItem *BinaryConcat1;
        TMenuItem *Bin2Hex1;
        TMenuItem *Paste11;
        TMenuItem *Undo1;
        TMenuItem *N13;
        TMenuItem *Pastenolf1;
        TMenuItem *mnWlCpc;
        TMenuItem *CPCclass1;
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall Selectall1Click(TObject *Sender);
        void __fastcall Pasteasnew1Click(TObject *Sender);
        void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Memo1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TabControl1Change(TObject *Sender);
        void __fastcall Next1Click(TObject *Sender);
        void __fastcall Back1Click(TObject *Sender);
        void __fastcall mnWrapClick(TObject *Sender);
        void __fastcall FindDialog1Find(TObject *Sender);
        void __fastcall ReplaceDialog1Find(TObject *Sender);
        void __fastcall ReplaceDialog1Replace(TObject *Sender);
        void __fastcall Find1Click(TObject *Sender);
        void __fastcall Replace1Click(TObject *Sender);
        void __fastcall Font1Click(TObject *Sender);
        void __fastcall Background1Click(TObject *Sender);
        void __fastcall Findnext1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall Goto1Click(TObject *Sender);
        void __fastcall mnRenbanClick(TObject *Sender);
        void __fastcall mnKeisanClick(TObject *Sender);
        void __fastcall Maximize1Click(TObject *Sender);
        void __fastcall Browse1Click(TObject *Sender);
        void __fastcall mnTagAssignClick(TObject *Sender);
        void __fastcall Color1Click(TObject *Sender);
        void __fastcall mnKnj1Click(TObject *Sender);
        void __fastcall Backup1Click(TObject *Sender);
        void __fastcall mnOptionClick(TObject *Sender);
        void __fastcall SaveFTP1Click(TObject *Sender);
        void __fastcall FTPsetting1Click(TObject *Sender);
        void __fastcall mnCommandClick(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall SQL1Click(TObject *Sender);
        void __fastcall Commit1Click(TObject *Sender);
        void __fastcall mnHelpClick(TObject *Sender);
        void __fastcall Memo1Click(TObject *Sender);
        void __fastcall mnCtrlFxClick(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall TabControl1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TabControl1DragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
        void __fastcall TabControl1DragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
        void __fastcall mnAboutClick(TObject *Sender);
        void __fastcall J1Click(TObject *Sender);
        void __fastcall mnKouhoClick(TObject *Sender);
        void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ListBox1Exit(TObject *Sender);
        void __fastcall mnKukeiCopyClick(TObject *Sender);
        void __fastcall mnTojikigoClick(TObject *Sender);
        void __fastcall mnTextPerlClick(TObject *Sender);
        void __fastcall Memo1KeyPress(TObject *Sender, char &Key);
        void __fastcall btnHelp1Click(TObject *Sender);
        void __fastcall mnPasteClick(TObject *Sender);
        void __fastcall mnCopyClick(TObject *Sender);
        void __fastcall mnCutClick(TObject *Sender);
        void __fastcall btnShiftClick(TObject *Sender);
        void __fastcall SpriteEditor1Click(TObject *Sender);
        void __fastcall SpriteDataGenerator1Click(TObject *Sender);
        void __fastcall MSXoption1Click(TObject *Sender);
        void __fastcall SourceASMorBAS1Click(TObject *Sender);
        void __fastcall NewDB1Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall copyy1Click(TObject *Sender);
        void __fastcall btnDataClick(TObject *Sender);
        void __fastcall mnAltXClick(TObject *Sender);
        void __fastcall Bin2Bas1Click(TObject *Sender);
        void __fastcall ScreenEdit1Click(TObject *Sender);
        void __fastcall mnSettargetClick(TObject *Sender);
        void __fastcall GraphicEditorClick(TObject *Sender);
        void __fastcall PaletteEditor1Click(TObject *Sender);
        void __fastcall mnClassClick(TObject *Sender);
        void __fastcall mnWlMsxClick(TObject *Sender);
        void __fastcall NewAGK1Click(TObject *Sender);
        void __fastcall popHidetopbuttonsClick(TObject *Sender);
        void __fastcall HextobitbusterHex1Click(TObject *Sender);
        void __fastcall DarkBasicsetting1Click(TObject *Sender);
        void __fastcall mnDiskManagerClick(TObject *Sender);
        void __fastcall mnMmlHelpClick(TObject *Sender);
        void __fastcall SoundEditor1Click(TObject *Sender);
        void __fastcall BinaryConcat1Click(TObject *Sender);
        void __fastcall Bin2Hex1Click(TObject *Sender);
        void __fastcall Paste11Click(TObject *Sender);
        void __fastcall Undo1Click(TObject *Sender);
        void __fastcall Pastenolf1Click(TObject *Sender);
        void __fastcall CPCclass1Click(TObject *Sender);
private:	// ユーザー宣言
	void __fastcall WMDROPFILES(TWMDropFiles Msg);
//        void __fastcall WMCopyData(TWMCopyData Msg);
//        void __fastcall WMCopyData( TMessage &Message );

/*BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,WMDROPFILES)
//    VCL_MESSAGE_HANDLER(WM_COPYDATA, TMessage, WMCopyData)
END_MESSAGE_MAP(TComponent)*/
        BEGIN_MESSAGE_MAP
         MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,WMDROPFILES)
        END_MESSAGE_MAP(TForm)
        bool __fastcall SaveAsText(char mo);
        bool __fastcall SaveText(void);
        void __fastcall AddNewText(AnsiString name);
        void __fastcall ChangeText(int to_idx,bool issave);
        bool __fastcall FindText(AnsiString txt,bool MatchCase);
        void __fastcall Find(void);
        bool __fastcall Replace(void);
        void __fastcall Modify(void);
        void __fastcall SetMenuCol(void);
        void __fastcall RefreshTextMenu(void);
        AnsiString __fastcall GetMenuText(AnsiString buf);
        void __fastcall InsertText(AnsiString &st);
        void __fastcall LoadIni(void);
        void __fastcall SaveIni(void);
        bool __fastcall CloseFile(void);
        AnsiString __fastcall NextSplit(AnsiString st);
//        AnsiString __fastcall ToSjis(AnsiString st);
        bool __fastcall SaveKnjString(AnsiString fi,AnsiString knj,AnsiString &st);
        bool __fastcall SaveKnjText(void);
        void __fastcall LoadKnjText(AnsiString knj2);
        void __fastcall PasteToTemp(bool ret);
        void __fastcall GetArgument(AnsiString &des,AnsiString na);

//        void __fastcall ShowCmdWnd(void);
        void __fastcall ListFiles(AnsiString dirName,TMenuItem *OyaItem);
        void __fastcall AddTempItem(AnsiString st,TMenuItem *OyaItem);
        void __fastcall RefreshTemp(void);
        void __fastcall LoadTemp(TObject *Sender);
        void __fastcall UpdateTemp(TObject *Sender);
        TStringList *li_temp;
        void __fastcall ButKey1Click(TObject *Sender);
        void __fastcall ButKey2Click(TObject *Sender);
        AnsiString __fastcall getButKey(int x,int y);
        void __fastcall releaseShift(void);
        void __fastcall refreshButStr(void);
        int __fastcall getFileSize(AnsiString fi);
public:		// ユーザー宣言
        __fastcall TFrmMeg1(TComponent* Owner);
        int __fastcall CursorX(void);
        int __fastcall CursorY(void);
        bool __fastcall strReplace(AnsiString &st,AnsiString txt,AnsiString txt2);
        AnsiString __fastcall strEncrypt(AnsiString st,int a);
        AnsiString __fastcall strDecrypt(AnsiString st,int a);
        void __fastcall CallExec(AnsiString cmd,AnsiString fi,AnsiString arg,bool sql,bool isShow);
//        bool __fastcall chkRegcode(AnsiString st);

        AnsiString fi_ini,di_megpas,strRegcode,strCredit,fi_fpcx;
        AnsiString txt[M_TXT];
        TStringList *li_ini;
        TStringList *li_id,*li_pos/*,*li_sellen*/,*li_modify,*li_file,*li_knj;
        TStringList *li_kouho;
        TStringList *li_no;
        TStringList *li_butkey;
        int butkeyFlg;AnsiString butStr;
        AnsiString bakSelText;
        int index;
        int renno;// 連番の数
        int tb_in,tb_cnt;
//        AnsiString strKeisan;
        bool ix;// Memo1を更新するが更新ﾌﾗｸﾞをたてないときtrue
        int ly;//ｵｰﾄｲﾝﾃﾞﾝﾄ用ｶｰｿﾙ行
        bool isReplaceAll;
        bool isSjisOnly;
//        bool isReg;//登録済み
        bool isAlt;//Alt
        bool lyf;
//        int repcnt;//置換した数
//        TFod *Fod1;
  //      Gra g;
        bool isFtp;
        bool isShift;
        bool isDmsys;
        int mnTagIdx;
        char kukeiCopy;int kukeiCopyX,kukeiCopyY;
//        AnsiString kukeiCopyMod;
        AnsiString GetSplit(int n,AnsiString st);
        void __fastcall butkeyReset(void);
        void __fastcall lstInit(void);
        void __fastcall lstMakeList(void);
        void __fastcall lstMakeKouho(AnsiString st);
        void __fastcall gendbpro(AnsiString fi,bool isNew);
        void __fastcall genagk(AnsiString fi,bool isNew);
        int koho_len,kohoStart;AnsiString kohoStr;
        char lstMo;//0=Kouho 1=FuncJump
        AnsiString fi_ccz80ptarget;
        void __fastcall reloadKouho(void);
        void __fastcall refreshTopButtons(void);
        AnsiString __fastcall defaultLoaderScript(void);
//        int __fastcall lstGetLineNo(void);
//        void __fastcall Upload(AnsiString str,AnsiString sdir,AnsiString fi);
//        AnsiString __fastcall TFrmMeg1::extMode(void);
        bool __fastcall isInsDmSys(AnsiString st);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrmMeg1 *FrmMeg1;
//---------------------------------------------------------------------------
#endif

