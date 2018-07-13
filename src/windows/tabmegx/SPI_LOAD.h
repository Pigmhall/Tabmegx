
//---------------------------------------------------------------------------
//
//      SUSIE プラグインを C++ Builder で簡単に使用するためのクラスヘッダ
//
//                     class  TSpiload;
//
//			           Programed by CAT.Y
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef spi_loadH
#define spi_loadH

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\graphics.hpp>

//---------------------------------------------------------------------------


// ============================================================================
//			SUSIE plug-in から情報を取得するための構造体
// ============================================================================
struct PictureInfo
{
	long 	left, top;    	// 展開する位置
    long 	width;       	// 画像の幅
    long 	height;      	//       高さ
    WORD 	x_density;   	// 画素の水平方向密度
    WORD 	y_density;   	// 画素の垂直方向密度
    short 	color; 			// １画素のbit数
    HLOCAL 	info;    		// 画像のテキストヘッダ
};


// ============================================================================
// ============================================================================
//
//			SUSIE plug-in プロシージャ管理テーブル
//
// ============================================================================
// ============================================================================
struct	TSpi_plugin
{
	int		err;
// ***** ハンドル *****
	HANDLE			handle;

// ***** リストポインタ *****
	TSpi_plugin		*next;

// ***** 展開可能なファイル形式か調べる *****
	int _export pascal (*IsSupported)(LPSTR filename, DWORD dw);

// ***** 画像ファイルに関する情報を得る　*****
	int _export pascal (*GetPictureInfo)(LPSTR buf, long len, unsigned int flag
     									,struct PictureInfo *lpInfo);
// ***** 画像を展開する *****
	int _export pascal (*GetPicture)(LPSTR buf, long len, unsigned int flag
              							,HANDLE *pHBInfo, HANDLE *pHBm
              							,FARPROC lpPrgressCallback, long lData);

// ***** プレビュー・カタログ表示用画像縮小展開ルーティン ******
	int _export pascal (*GetPreview)(LPSTR buf, long len, unsigned int flag
    									,HANDLE *pHBInfo, HANDLE *pHBm
                                        ,FARPROC lpPrgressCallback, long lData);


// ***** アーカイブ内のすべてのファイルの情報を取得する *****
	int	_export pascal (*GetArchiveInfo)(LPSTR buf, long len
											,unsigned int flag, HLOCAL *lphInf);

// ***** アーカイブ内のファイルを取得する *****
	int	_export pascal (*GetFile)(LPSTR src, long len, LPSTR dest, unsigned int flag
                                            ,FARPROC prgressCallback, long lData);

// Constructor
	TSpi_plugin()
    {
		handle = NULL;
        next = NULL;
    };

// Destructor
	~TSpi_plugin()
    {
    	if (handle != NULL) {
        	FreeLibrary(handle);					// ライブラリ解放
        }
    };

// ********** DLL Procedure address set *********
	bool	load_library(const char	*lib)
    {
    	bool	ret = false;

		handle = LoadLibrary(lib);					// Win32 API

    	if (handle != NULL) {
    		// === Win32 API でアドレス取得 ===
			(void *)IsSupported    = GetProcAddress(handle, "IsSupported");
			(void *)GetPictureInfo = GetProcAddress(handle, "GetPictureInfo");
			(void *)GetPicture     = GetProcAddress(handle, "GetPicture");
			(void *)GetPreview     = GetProcAddress(handle, "GetPreview");
			(void *)GetArchiveInfo = GetProcAddress(handle, "GetArchiveInfo");
			(void *)GetFile        = GetProcAddress(handle, "GetFile");
            // === 簡易エラーチェック ===
			ret = (IsSupported != NULL) & (GetPicture != NULL);
            if (ret == false)
            	err = GetLastError();
        }
        return	ret;
    };

};


// ============================================================================
// ============================================================================
//
//			SUSIE plug-in 画像取得管理クラス
//
// ============================================================================
// ============================================================================
class	TSpiload	{
	protected:

    	bool	err_flag;				// エラー時表示フラグ
    	char	*spi_path;				// SPI が存在するパス
    	char	*filename;				// File name
        char	ext[32];				// 拡張子

        TSpi_plugin	*spi;				// プラグインリスト
		TSpi_plugin	*now_spi;			// 最後に確定したプラグイン

	public:
        Graphics::TBitmap	*bmp;		// Bitmap データ
        int		color_depth;			// Color の深さ(ビット数)
        int		err;					// Win32 エラー番号 


    	TSpiload()								// Constructor
        {
        	err_flag = true;
        	spi_path = new(char[1]);
        	filename = new(char[1]);
            *spi_path = *filename = NULL;		// Terminate string
            bmp = NULL;
            spi = NULL;
        }

       	~TSpiload()								// Destructor
        {
        	delete spi_path;
        	delete filename;

            if (bmp != NULL) delete bmp;
            if (spi != NULL) delete spi;
        }

        void	set_spipath(const char *path);	// SPI のパスを設定
        bool	set_file(const char *src);		// file name set & load
        bool	check(void);					// ファイルのチェック
        bool	load(void);						// ファイルのロード
        void	clean(void);					// 廃棄可能なﾃﾞｰﾀを廃棄
};

#endif
