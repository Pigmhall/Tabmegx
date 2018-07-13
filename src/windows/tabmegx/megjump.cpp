//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "megjump.h"
#include "megson1.h"
#define INI(X) FrmMeg1->li_ini->Values[X]
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmJump *FrmJump;
//---------------------------------------------------------------------------
__fastcall TFrmJump::TFrmJump(TComponent* Owner)
        : TForm(Owner)
{li_no=new TStringList();
int y=StrToInt(INI("ListBoxY"));
int x=StrToInt(INI("ListBoxX"));
int h=StrToInt(INI("ListBoxH"));
int w=StrToInt(INI("ListBoxW"));
Left=FrmMeg1->Left+x+FrmMeg1->CursorX()*w;
Top=FrmMeg1->Top+y+(FrmMeg1->CursorY()-FrmMeg1->Memo1->Perform(EM_GETFIRSTVISIBLELINE,0,0))*h;
ListBox1->Color=FrmMeg1->Memo1->Color;
ListBox1->Font=FrmMeg1->Memo1->Font;
ListBox1->Font->Size=StrToInt(INI("ListBoxFontSize"));
ClientWidth=StrToInt(INI("ListBoxW2"));
ClientHeight=StrToInt(INI("ListBoxH2"));
if(Left>FrmMeg1->Left+FrmMeg1->Width-Width)Left=FrmMeg1->Left+FrmMeg1->Width-Width;
if(Top>FrmMeg1->Top+FrmMeg1->Height-Height)Top=FrmMeg1->Top+FrmMeg1->Height-Height;

//ListBox1->Font->Color=Memo1->Font->Color;

}
//---------------------------------------------------------------------------
void __fastcall TFrmJump::MakeList(void){
 int i,j,a,cnt;AnsiString st,st2;
 Caption="ä÷êîà⁄ìÆ";
 TStringList *li=new TStringList();
 st=INI("FuncJump");a=0;
 while((st2=FrmMeg1->GetSplit(a,st))!=""){li->Add(st2);++a;}
 cnt=li->Count;

 for(i=0;i<FrmMeg1->Memo1->Lines->Count;i++){
  st=FrmMeg1->Memo1->Lines->Strings[i];
  for(j=0;j<cnt;j++){
  if(st.Pos(li->Strings[j])==1){//Perl func
   st.Delete(1,li->Strings[j].Length()+1);
   if((a=st.Pos("{"))!=0){st.Delete(a,st.Length()-a+1);}
   if((a=st.Pos("("))!=0){st.Delete(a,st.Length()-a+1);}
   ListBox1->Items->Add(st);
   li_no->Add(IntToStr(i));j=cnt;}}}
//  else if(st.Pos("int ")==1||st.Pos("void ")==1||st.Pos("char ")==1
 delete li;
 if(ListBox1->Items->Count>0)ListBox1->ItemIndex=0;
}

void __fastcall TFrmJump::MakeKouho(AnsiString st){
 int i;AnsiString st2;
 Caption="åÛï‚";
 for(i=0;i<FrmMeg1->li_kouho->Count;i++){
  st2=FrmMeg1->li_kouho->Strings[i];
  if(st2.Pos(st)==1){
   ListBox1->Items->Add(st2);}}
 if(ListBox1->Items->Count>0)ListBox1->ItemIndex=0;
}

int __fastcall TFrmJump::GetLineNo(void){
 int a=ListBox1->ItemIndex;
 if(a==-1)return 0;
 return StrToInt(li_no->Strings[a]);}

void __fastcall TFrmJump::ListBox1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{bool psAlt=Shift.Contains(ssAlt),psShift=Shift.Contains(ssShift);
 switch(Key){
  case VK_RETURN:ModalResult=mrOk;break;
  case VK_ESCAPE:ModalResult=mrCancel;break;
  case VK_UP:if(psAlt){if(psShift)ClientHeight-=8;else --Top;}break;
  case VK_RIGHT:if(psAlt){if(psShift)ClientWidth+=8;else ++Left;}break;
  case VK_DOWN:if(psAlt){if(psShift)ClientHeight+=8;else ++Top;}break;
  case VK_LEFT:if(psAlt){if(psShift)ClientWidth-=8;else --Left;}break;
  case VK_F2:INI("ListBoxX")=Left-FrmMeg1->Left;INI("ListBoxY")=Top-FrmMeg1->Top;
   Application->MessageBox("0,0ÇÃà íuÇê›íË","ListBox",MB_OK);break;
  break;
  case VK_F3:INI("ListBoxW")=Left-FrmMeg1->Left-StrToInt(INI("ListBoxX"));INI("ListBoxH")=Top-FrmMeg1->Top-StrToInt(INI("ListBoxY"));
   Application->MessageBox("1,1ÇÃà íuÇê›íË","ListBox",MB_OK);break;
  break;

  }
/*ListBoxH=16
ListBoxW=8
ListBoxX=8
ListBoxY=48*/
}
//---------------------------------------------------------------------------

