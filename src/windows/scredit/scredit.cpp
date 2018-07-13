//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("edit1.cpp", frmEdit);
USEFORM("edit2.cpp", FrmCoord);
USEFORM("frmPrint.cpp", frmPrin);
USEFORM("output1.cpp", frmOutput);
USEFORM("chredit.cpp", frmChrEdit);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmEdit), &frmEdit);
                 Application->CreateForm(__classid(TFrmCoord), &FrmCoord);
                 Application->CreateForm(__classid(TfrmPrin), &frmPrin);
                 Application->CreateForm(__classid(TfrmOutput), &frmOutput);
                 Application->CreateForm(__classid(TfrmChrEdit), &frmChrEdit);
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
