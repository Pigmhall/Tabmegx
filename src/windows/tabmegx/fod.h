//FOD.H ---------------------------------------------------------------------
#ifndef fodH
#define fodH
//---------------------------------------------------------------------------
#include <vcl\SysUtils.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Forms.hpp>
#include <vcl\FileCtrl.hpp>

//---------------------------------------------------------------------------
class TFod : public TComponent
{
private:
 TForm *Form1;
 TListBox *ListBox1;
 TFileListBox *FileListBox1;
 TEdit *Edit1;
 AnsiString FTitle,FMask,FDir,FFileName,FExt;
 int keycount,FHeight,FWidth,FFontSize;
 bool jumpmo;
 char keyhis,sd;
 TColor FColor,FFontColor;
 void Update();
 void __fastcall ListBox1KeyDown(TObject *Sender,WORD &Key,TShiftState Shift);
 void __fastcall ListBox1KeyPress(TObject *Sender, char &Key);
 void __fastcall ListBox1DblClick(TObject *Sender);
 void __fastcall Ok(AnsiString st);
 void __fastcall OkResult(AnsiString st,bool bo);
 void __fastcall Edit1KeyDown(TObject *Sender,WORD &Key,TShiftState Shift);
 void __fastcall FormShow(TObject *Sender);
 void __fastcall InitJumpMo(void);
protected:
public:
 __fastcall TFod(TComponent* Owner);
 bool __fastcall Execute(char a);
 AnsiString TFod::AnalizeLink(String SCFileName);
 AnsiString Drives,wd,wmy;
 TStringList *li_jumpdir;
__published:
 __property int Height={read=FHeight,write=FHeight,default=256};
 __property int Width={read=FWidth,write=FWidth,default=128};
 __property TColor FontColor={read=FFontColor,write=FFontColor,default=clWindowText};
 __property int FontSize={read=FFontSize,write=FFontSize,default=9};
 __property AnsiString Title={read=FTitle,write=FTitle};
 __property AnsiString Mask={read=FMask,write=FMask};
 __property AnsiString Directory={read=FDir,write=FDir};
 __property AnsiString FileName={read=FFileName,write=FFileName};
 __property AnsiString DefaultExt={read=FExt,write=FExt};
 __property TColor Color={read=FColor,write=FColor,default=clWindow};
};

#endif

