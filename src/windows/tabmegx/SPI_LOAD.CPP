//---------------------------------------------------------------------------
//
//        SUSIE プラグインを C++ Builder で簡単に使用するためのクラス
//
//                     class  TSpiload;
//
//			           Programed by CAT.Y
//
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#include <dir.h>
#include <dos.h>
#pragma hdrstop

#include "spi_load.h"
//---------------------------------------------------------------------------


// **********************************************************
//			SPI のパスを設定し、ロードする
// **********************************************************
void	TSpiload::set_spipath(const char *path)
{
	TSpi_plugin		*plg,*pre;
    char	*spi_allpath, *wk;
    HANDLE	fh;
	WIN32_FIND_DATA	ff;

// ***** SPI の PATH を設定 *****
    if (spi_path != NULL)
    	delete	spi_path;
    spi_path = new (char[strlen(path)+16]);
    spi_allpath = new (char[strlen(path)+16]);		// local
    wk = new (char[strlen(path)+300]);				// work area
    strcpy(spi_path, path);
    sprintf(spi_allpath, "%s\\*.SPI", path);

// ***** プラグインの検索 *****
    pre = NULL;

    fh = FindFirstFile(spi_allpath, &ff);
	while (fh != INVALID_HANDLE_VALUE)
	{
    	plg = new(TSpi_plugin);

        sprintf(wk, "%s\\%s", spi_path, ff.cFileName);		// file name make

// ***** プラグインロード *****
   	    if (plg->load_library(wk) == false) {
// DLL load error
			delete plg;				// エラーなので解放
       	} else {
// DLL load succsess
    		if (pre == NULL) {
   	    		spi = plg;			// リストの先頭
        	} else {
   	    		pre->next = plg;	// リストの連結
       		}
			pre = plg;
        }
		if (FindNextFile(fh, &ff) == false)
        	break;
	}
    if (fh != INVALID_HANDLE_VALUE)
    	FindClose(fh);
}



// **********************************************************
//			file name set & check
// **********************************************************
bool	TSpiload::set_file(const char *src)
{
	AnsiString	tmp;

// ***** ファイルの拡張子を取得 *****
    tmp = UpperCase(ExtractFileExt(src));
    strcpy(ext, tmp.c_str());

// ***** ファイルの全体名を設定 *****
	if (filename != NULL)
    	delete filename;
    filename = new (char[strlen(src)+1]);
    strcpy(filename, src);

// ***** ファイルの展開可能チェック *****
    return	check();
}



// **********************************************************
//			ファイルの展開チェック
// **********************************************************
bool	TSpiload::check()
{
	bool	ret = false;
	TSpi_plugin		*lib;
    HFILE	lf;


/*    if (strcmp(ext, ".BMP") == 0 || strcmp(ext, ".ICO") == 0 || strcmp(ext, ".WMF") == 0
		   	|| strcmp(ext, ".EMF") == 0) {
// VCL で処理可能な形式？
        ret = true;
    } nito070202*/

// file open
    for (lib = spi ; lib != NULL && ret == false ; lib = lib->next) {
// ロードされた SPI があるか、ﾁｪｯｸ OK になるまで
	    lf = _lopen(filename, OF_READ | OF_SHARE_DENY_NONE );
		if ( (*lib->IsSupported)(filename, (DWORD)lf) != 0) {
// サポートしている DLL を発見
			now_spi = lib;
           	ret = true;
        }
        _lclose(lf);
	}

    return	ret;
}



// **************************************************************
// 				ファイルのロード
//
//		注) check を呼び出して now_spi をセットしておくこと
// **************************************************************
bool	TSpiload::load(void)
{
	PictureInfo		pinfo;
	bool	ret = false;
	HANDLE	bmpdata, bmpinfo;
    void	*pbmpdata;
    BITMAPINFO *pbmpinfo;

// ===================================
// ===== Bitmap を新規に作成する =====
// ===================================
    if (bmp != NULL) {
    	delete bmp;			// 旧領域解放
    }
    bmp = new (Graphics::TBitmap);

/*    if (strcmp(ext, ".BMP") == 0 || strcmp(ext, ".ICO") == 0 || strcmp(ext, ".WMF") == 0
    	|| strcmp(ext, ".EMF") == 0) {
// =================================
// ===== BITMAP ファイル等場合 =====
// =================================
		bmp->LoadFromFile(filename);
        if (bmp->Empty == false)
        	ret = true;
    }nito070202*/

    if (ret == false) {
// ================================================
// ===== VCL で処理できない画像ファイルの場合 =====
// ================================================
	    if ((*now_spi->GetPictureInfo)(filename, 0, 0, &pinfo) == 0) {
// Bitmap オブジェクトを新規作成して幅と高さを設定
	    	bmp->Width = pinfo.width;
    		bmp->Height = pinfo.height;
        	color_depth = pinfo.color;
		    GlobalFree(pinfo.info);			// TEXT info 解放

// 画像のロード
    	    if ( (*now_spi->GetPicture)(filename, 0, 0,  &bmpinfo, &bmpdata, NULL, 0) == 0 ) {
	    		pbmpdata = GlobalLock(bmpdata);		// Win32 API でロック
    			pbmpinfo = (LPBITMAPINFO)GlobalLock(bmpinfo);

// 画像の取得
	        	if (SetDIBits(bmp->Canvas->Handle, bmp->Handle, 0, pinfo.height
    	        			,pbmpdata, pbmpinfo, DIB_RGB_COLORS) == 0) {
        	    	err = GetLastError();		// API error
            	} else {
            		ret = true;			// 成功
	            }
// 後始末
				GlobalUnlock(pbmpdata);
				GlobalUnlock(pbmpinfo);
				GlobalFree(bmpdata);
				GlobalFree(bmpinfo);
// Bitmap save (TEST)
///////            bmp->SaveToFile("TEST.BMP");
			}
        }
    }

    return	ret;
}


// **************************************************************
// 				廃棄可能なﾃﾞｰﾀを廃棄
//		(用がすんだら呼び出せば、メモリが節約できる)
// **************************************************************
void	TSpiload::clean(void)
{
	if (bmp != NULL) {
    	delete bmp;				// Bitmap を廃棄
    }
}

