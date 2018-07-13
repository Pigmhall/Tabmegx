//---------------------------------------------------------------------------

#ifndef megimageH
#define megimageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include "spi_load.h"
//---------------------------------------------------------------------------
class TFrmImage : public TForm
{
__published:	// IDE 管理のコンポーネント
        TListBox *ListBox1;
        TEdit *Edit1;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TFileListBox *FileListBox1;
        TLabel *Label1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ListBox1KeyPress(TObject *Sender, char &Key);
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// ユーザー宣言
 AnsiString FMask,FExt/*,Drives,wd*/;
 int keycount,FHeight,FWidth,FFontSize;
 bool jumpmo;
 char keyhis,sd;
 TColor FColor,FFontColor;
 void __fastcall Update();
// AnsiString __fastcall AnalizeLink(String SCFileName);
 void __fastcall Ok(AnsiString st);
 void __fastcall OkResult(AnsiString st,bool bo);
 void __fastcall InitJumpMo2(void);
        TSpiload	Susie;
public:		// ユーザー宣言
        __fastcall TFrmImage(TComponent* Owner);
        AnsiString FTitle,FDir,FFileName,Drives;
        bool __fastcall LoadGra(AnsiString f);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmImage *FrmImage;
//---------------------------------------------------------------------------
#endif
