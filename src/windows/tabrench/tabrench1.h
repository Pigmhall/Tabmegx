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
        TImage *ImgCurV;
        TImage *ImgCurH;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Saveas1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TMenuItem *Edit1;
        TMenuItem *mnPen;
        TMenuItem *mnChrs;
        TMenuItem *Undo1;
        TMenuItem *N2;
        TMenuItem *Option1;
        TMenuItem *mngPen;
        TMenuItem *mngErase;
        TMenuItem *mngPaint;
        TMenuItem *mngSpoit;
        TMenuItem *mnMod;
        TBitBtn *btnNew;
        TBitBtn *btnOpen;
        TBitBtn *btnSave;
        TBitBtn *btnDown;
        TBitBtn *btnLeft;
        TBitBtn *btnPaint;
        TBitBtn *btnUp;
        TBitBtn *btnRight;
        TBitBtn *btnNextChr;
        TMenuItem *Shift1;
        TMenuItem *Mirrow1;
        TMenuItem *rotate1;
        TMenuItem *mnShiftUp;
        TMenuItem *mnShiftRight;
        TMenuItem *mnShiftDown;
        TMenuItem *mnShiftLeft;
        TMenuItem *mnMirrorV;
        TMenuItem *mnMirrorH;
        TMenuItem *N3;
        TBitBtn *btnSpoit;
        TMenuItem *IncrementalSave1;
        TMenuItem *mnNewSize;
        TMenuItem *Clear1;
        TMenuItem *Color1;
        TMenuItem *mnColor16;
        TMenuItem *mnColor256;
        TMenuItem *mngReplace;
        TMenuItem *N2561;
        TMenuItem *N25631;
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
        void __fastcall mnOpenChr(TObject *Sender);
        void __fastcall ImgViewMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ImgViewMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImgColorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnUpClick(TObject *Sender);
        void __fastcall btnDownClick(TObject *Sender);
        void __fastcall btnLeftClick(TObject *Sender);
        void __fastcall btnRightClick(TObject *Sender);
        void __fastcall btnNextChrClick(TObject *Sender);
        void __fastcall mnShiftUpClick(TObject *Sender);
        void __fastcall mnShiftRightClick(TObject *Sender);
        void __fastcall mnShiftDownClick(TObject *Sender);
        void __fastcall mnShiftLeftClick(TObject *Sender);
        void __fastcall mnMirrorVClick(TObject *Sender);
        void __fastcall mnMirrorHClick(TObject *Sender);
        void __fastcall rotate1Click(TObject *Sender);
        void __fastcall IncrementalSave1Click(TObject *Sender);
        void __fastcall Clear1Click(TObject *Sender);
        void __fastcall mnColor256Click(TObject *Sender);
        void __fastcall mnChangePalette(TObject *Sender);
        void __fastcall mngReplaceClick(TObject *Sender);
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
        void __fastcall ChangeColor(TColor c);
        void __fastcall SetButtonSize(TButton *btn,int l);
        void __fastcall RefreshPaletteList(void);
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
        TStringList *li_ini;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
