//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "exec1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{AnsiString st="";
for(int i=1;i<=ParamCount();i++){
 if(i>1)st=st+" ";st=st+ParamStr(i);}
if(st!="")WinExec(st.c_str(),SW_SHOW);
Application->Terminate();
}
//---------------------------------------------------------------------------