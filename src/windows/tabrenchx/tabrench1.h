//---------------------------------------------------------------------------

#ifndef tabrench1H
#define tabrench1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#define INI(X) Form1->li_ini->Values[X]
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TImage *ImgMain;
        TImage *ImgPallete;
        TImage *ImgColor;
        TImage *ImgView;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TTimer *Timer1;
        TImage *ImgViewB;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Saveas1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TMenuItem *Edit1;
        TMenuItem *Undo1;
        TMenuItem *N2;
        TMenuItem *Shift1;
        TMenuItem *mnShiftUp;
        TMenuItem *mnShiftRight;
        TMenuItem *mnShiftDown;
        TMenuItem *mnShiftLeft;
        TMenuItem *Mirrow1;
        TMenuItem *mnMirrorV;
        TMenuItem *mnMirrorH;
        TMenuItem *rotate1;
        TMenuItem *N3;
        TMenuItem *Option1;
        TMenuItem *mnPen;
        TMenuItem *mngPen;
        TMenuItem *mngErase;
        TMenuItem *mngPaint;
        TMenuItem *mngSpoit;
        TMenuItem *mnChrs;
        TMenuItem *mnMod;
        TBitBtn *btnNextChr;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TBitBtn *btnPaint;
        TBitBtn *btnSave;
        TBitBtn *btnOpen;
        TBitBtn *btnNew;
        TBitBtn *BitBtn5;
        TMenuItem *IncrementalSave1;
        TMenuItem *Clear1;
        TMenuItem *mnColor16;
        TMenuItem *mngReplace;
        TImage *ImgOr;
        TMenuItem *N4;
        TMenuItem *Export1;
        TMenuItem *Generatepico8gfx1;
        void __fastcall ImgPalleteMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImgMainMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImgMainMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall BtnNewClick(TObject *Sender);
        void __fastcall BtnOpenClick(TObject *Sender);
        void __fastcall BtnSaveasClick(TObject *Sender);
        void __fastcall BtnSaveClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BtnOptionClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall BtnPenClick(TObject *Sender);
        void __fastcall BtnPaintClick(TObject *Sender);
        void __fastcall BtnUndoClick(TObject *Sender);
        void __fastcall BtnSpoitClick(TObject *Sender);
        void __fastcall BtnEraseClick(TObject *Sender);
        void __fastcall BtnUpClick(TObject *Sender);
        void __fastcall BtnRightClick(TObject *Sender);
        void __fastcall BtnDownClick(TObject *Sender);
        void __fastcall BtnLeftClick(TObject *Sender);
        void __fastcall BtnMirrorClick(TObject *Sender);
        void __fastcall ButMirror2Click(TObject *Sender);
        void __fastcall butRotateClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mnOpenChr(TObject *Sender);
        void __fastcall btnNextChrClick(TObject *Sender);
        void __fastcall ImgColorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall IncrementalSave1Click(TObject *Sender);
        void __fastcall Clear1Click(TObject *Sender);
        void __fastcall mnChangePalette(TObject *Sender);
        void __fastcall mngReplaceClick(TObject *Sender);
        void __fastcall Generatepico8gfx1Click(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall DrawPixel(int X,int Y);
        void __fastcall ViewToMain(void);
        void __fastcall LoadIni(void);
        void __fastcall SaveIni(void);
        void __fastcall Backup(void);
        void __fastcall SaveImage(AnsiString fi);
        void __fastcall RefreshChrs(void);
        void __fastcall LoadImage(AnsiString fi);
        bool __fastcall ModifyQuestion(void);
        void __fastcall RefreshPaletteList(void);
        void __fastcall reloadCols(void);
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
        void __fastcall GeneratePico8Gfx(void);
        TStringList *li_ini;
        TColor cols[16];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
