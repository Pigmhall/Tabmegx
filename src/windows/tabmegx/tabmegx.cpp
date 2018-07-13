//---------------------------------------------------------------------------
#include <vcl.h>
#include <shellapi.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("megson1.cpp", FrmMeg1);
USEFORM("megnumber.cpp", FrmNumber);
USEFORM("megkeyas.cpp", FrmKeyas);
USEFORM("megoption.cpp", FrmOption);
USEFORM("megftp.cpp", FrmFtp);
USEFORM("megcmd.cpp", FrmCmd);
USEFORM("megperl.cpp", FrmPerl);
USEFORM("megmsx.cpp", frmMsx);
USEFORM("megdb.cpp", frmDb);
//---------------------------------------------------------------------------
typedef struct{
 WORD wSize;
 POINT ptMousePos;
 BOOL fInNonClientArea;
} DROPFILESTRUCT, FAR *LPDROPFILESTRUCT;

HDROP FAR DragCreateFiles(void){
 HGLOBAL hDrop;
 LPDROPFILESTRUCT lpDropFileStruct;

 hDrop=GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE|GMEM_ZEROINIT,sizeof(DROPFILESTRUCT)+1);
 if(hDrop==NULL)return((HDROP)hDrop);
 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);
 lpDropFileStruct->wSize=sizeof(DROPFILESTRUCT);
 lpDropFileStruct->fInNonClientArea=true;
 GlobalUnlock(hDrop);
 return((HDROP)hDrop);}

HDROP FAR DragAppendFile(HGLOBAL hDrop, LPCSTR szPathname){
 LPDROPFILESTRUCT lpDropFileStruct;
 LPCSTR lpCrnt;
 WORD wSize;

 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);

 lpCrnt=(LPSTR)lpDropFileStruct+lpDropFileStruct->wSize;
 while(*lpCrnt){
  while(*lpCrnt)lpCrnt++;
  lpCrnt++;}

 wSize=(WORD)(lpCrnt-(LPSTR)lpDropFileStruct+1);
 GlobalUnlock(hDrop);
 hDrop=GlobalReAlloc(hDrop,wSize+lstrlen(szPathname)+1,GMEM_SHARE|GMEM_MOVEABLE|GMEM_ZEROINIT);
 if(!hDrop)return((HDROP)hDrop);

 lpDropFileStruct=(LPDROPFILESTRUCT)GlobalLock(hDrop);
 lstrcpy((LPSTR)lpDropFileStruct+wSize-1,szPathname);
 GlobalUnlock(hDrop);
 return((HDROP)hDrop);
// WHND han=FindWindow("","Adobe Photoshop");
}

/*HWND FindWind(AnsiString ch){
 HWND CurrWnd=GetWindow(Form1->Handle,GW_HWNDFIRST);
 char c2[256];
 while(CurrWnd){
  GetWindowText(CurrWnd,c2,256);
  if(AnsiPos(ch,StrPas(c2)))return CurrWnd;
  CurrWnd=GetWindow(CurrWnd,GW_HWNDNEXT);}
 return 0;}*/

bool Nijukido(void){
 HWND han=FindWindow("TFrmMeg1","Tabmegx");
 if(!han){
/*  han=FindWindow("TFrmMeg1","Megson(–¢“o˜^)");
  if(!han)*/return false;}
 SetForegroundWindow(han);
 if(ParamCount()==0)return true;

 HDROP hDrop,hDropT;
 hDrop=DragCreateFiles();
 hDropT=DragAppendFile(hDrop,ParamStr(1).c_str());
 if(hDropT==NULL){GlobalFree(hDrop);/*hDrop=NULL;*/ return true;}else hDrop=hDropT;
 PostMessage(han,WM_DROPFILES,(WPARAM)hDrop,0L);return true;
}

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
if(Nijukido())return 0;
        try
        {
                 Application->Initialize();
                 Application->HelpFile = "";
                 Application->CreateForm(__classid(TFrmMeg1), &FrmMeg1);
                 Application->CreateForm(__classid(TFrmCmd), &FrmCmd);
                 Application->CreateForm(__classid(TFrmPerl), &FrmPerl);
                 Application->CreateForm(__classid(TfrmMsx), &frmMsx);
                 Application->CreateForm(__classid(TfrmDb), &frmDb);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
