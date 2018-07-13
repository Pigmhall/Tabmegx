
//---------------------------------------------------------------------------
//
//      SUSIE �v���O�C���� C++ Builder �ŊȒP�Ɏg�p���邽�߂̃N���X�w�b�_
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
//			SUSIE plug-in ��������擾���邽�߂̍\����
// ============================================================================
struct PictureInfo
{
	long 	left, top;    	// �W�J����ʒu
    long 	width;       	// �摜�̕�
    long 	height;      	//       ����
    WORD 	x_density;   	// ��f�̐����������x
    WORD 	y_density;   	// ��f�̐����������x
    short 	color; 			// �P��f��bit��
    HLOCAL 	info;    		// �摜�̃e�L�X�g�w�b�_
};


// ============================================================================
// ============================================================================
//
//			SUSIE plug-in �v���V�[�W���Ǘ��e�[�u��
//
// ============================================================================
// ============================================================================
struct	TSpi_plugin
{
	int		err;
// ***** �n���h�� *****
	HANDLE			handle;

// ***** ���X�g�|�C���^ *****
	TSpi_plugin		*next;

// ***** �W�J�\�ȃt�@�C���`�������ׂ� *****
	int _export pascal (*IsSupported)(LPSTR filename, DWORD dw);

// ***** �摜�t�@�C���Ɋւ�����𓾂�@*****
	int _export pascal (*GetPictureInfo)(LPSTR buf, long len, unsigned int flag
     									,struct PictureInfo *lpInfo);
// ***** �摜��W�J���� *****
	int _export pascal (*GetPicture)(LPSTR buf, long len, unsigned int flag
              							,HANDLE *pHBInfo, HANDLE *pHBm
              							,FARPROC lpPrgressCallback, long lData);

// ***** �v���r���[�E�J�^���O�\���p�摜�k���W�J���[�e�B�� ******
	int _export pascal (*GetPreview)(LPSTR buf, long len, unsigned int flag
    									,HANDLE *pHBInfo, HANDLE *pHBm
                                        ,FARPROC lpPrgressCallback, long lData);


// ***** �A�[�J�C�u���̂��ׂẴt�@�C���̏����擾���� *****
	int	_export pascal (*GetArchiveInfo)(LPSTR buf, long len
											,unsigned int flag, HLOCAL *lphInf);

// ***** �A�[�J�C�u���̃t�@�C�����擾���� *****
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
        	FreeLibrary(handle);					// ���C�u�������
        }
    };

// ********** DLL Procedure address set *********
	bool	load_library(const char	*lib)
    {
    	bool	ret = false;

		handle = LoadLibrary(lib);					// Win32 API

    	if (handle != NULL) {
    		// === Win32 API �ŃA�h���X�擾 ===
			(void *)IsSupported    = GetProcAddress(handle, "IsSupported");
			(void *)GetPictureInfo = GetProcAddress(handle, "GetPictureInfo");
			(void *)GetPicture     = GetProcAddress(handle, "GetPicture");
			(void *)GetPreview     = GetProcAddress(handle, "GetPreview");
			(void *)GetArchiveInfo = GetProcAddress(handle, "GetArchiveInfo");
			(void *)GetFile        = GetProcAddress(handle, "GetFile");
            // === �ȈՃG���[�`�F�b�N ===
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
//			SUSIE plug-in �摜�擾�Ǘ��N���X
//
// ============================================================================
// ============================================================================
class	TSpiload	{
	protected:

    	bool	err_flag;				// �G���[���\���t���O
    	char	*spi_path;				// SPI �����݂���p�X
    	char	*filename;				// File name
        char	ext[32];				// �g���q

        TSpi_plugin	*spi;				// �v���O�C�����X�g
		TSpi_plugin	*now_spi;			// �Ō�Ɋm�肵���v���O�C��

	public:
        Graphics::TBitmap	*bmp;		// Bitmap �f�[�^
        int		color_depth;			// Color �̐[��(�r�b�g��)
        int		err;					// Win32 �G���[�ԍ� 


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

        void	set_spipath(const char *path);	// SPI �̃p�X��ݒ�
        bool	set_file(const char *src);		// file name set & load
        bool	check(void);					// �t�@�C���̃`�F�b�N
        bool	load(void);						// �t�@�C���̃��[�h
        void	clean(void);					// �p���\���ް���p��
};

#endif
