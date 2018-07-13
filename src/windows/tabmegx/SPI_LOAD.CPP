//---------------------------------------------------------------------------
//
//        SUSIE �v���O�C���� C++ Builder �ŊȒP�Ɏg�p���邽�߂̃N���X
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
//			SPI �̃p�X��ݒ肵�A���[�h����
// **********************************************************
void	TSpiload::set_spipath(const char *path)
{
	TSpi_plugin		*plg,*pre;
    char	*spi_allpath, *wk;
    HANDLE	fh;
	WIN32_FIND_DATA	ff;

// ***** SPI �� PATH ��ݒ� *****
    if (spi_path != NULL)
    	delete	spi_path;
    spi_path = new (char[strlen(path)+16]);
    spi_allpath = new (char[strlen(path)+16]);		// local
    wk = new (char[strlen(path)+300]);				// work area
    strcpy(spi_path, path);
    sprintf(spi_allpath, "%s\\*.SPI", path);

// ***** �v���O�C���̌��� *****
    pre = NULL;

    fh = FindFirstFile(spi_allpath, &ff);
	while (fh != INVALID_HANDLE_VALUE)
	{
    	plg = new(TSpi_plugin);

        sprintf(wk, "%s\\%s", spi_path, ff.cFileName);		// file name make

// ***** �v���O�C�����[�h *****
   	    if (plg->load_library(wk) == false) {
// DLL load error
			delete plg;				// �G���[�Ȃ̂ŉ��
       	} else {
// DLL load succsess
    		if (pre == NULL) {
   	    		spi = plg;			// ���X�g�̐擪
        	} else {
   	    		pre->next = plg;	// ���X�g�̘A��
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

// ***** �t�@�C���̊g���q���擾 *****
    tmp = UpperCase(ExtractFileExt(src));
    strcpy(ext, tmp.c_str());

// ***** �t�@�C���̑S�̖���ݒ� *****
	if (filename != NULL)
    	delete filename;
    filename = new (char[strlen(src)+1]);
    strcpy(filename, src);

// ***** �t�@�C���̓W�J�\�`�F�b�N *****
    return	check();
}



// **********************************************************
//			�t�@�C���̓W�J�`�F�b�N
// **********************************************************
bool	TSpiload::check()
{
	bool	ret = false;
	TSpi_plugin		*lib;
    HFILE	lf;


/*    if (strcmp(ext, ".BMP") == 0 || strcmp(ext, ".ICO") == 0 || strcmp(ext, ".WMF") == 0
		   	|| strcmp(ext, ".EMF") == 0) {
// VCL �ŏ����\�Ȍ`���H
        ret = true;
    } nito070202*/

// file open
    for (lib = spi ; lib != NULL && ret == false ; lib = lib->next) {
// ���[�h���ꂽ SPI �����邩�A���� OK �ɂȂ�܂�
	    lf = _lopen(filename, OF_READ | OF_SHARE_DENY_NONE );
		if ( (*lib->IsSupported)(filename, (DWORD)lf) != 0) {
// �T�|�[�g���Ă��� DLL �𔭌�
			now_spi = lib;
           	ret = true;
        }
        _lclose(lf);
	}

    return	ret;
}



// **************************************************************
// 				�t�@�C���̃��[�h
//
//		��) check ���Ăяo���� now_spi ���Z�b�g���Ă�������
// **************************************************************
bool	TSpiload::load(void)
{
	PictureInfo		pinfo;
	bool	ret = false;
	HANDLE	bmpdata, bmpinfo;
    void	*pbmpdata;
    BITMAPINFO *pbmpinfo;

// ===================================
// ===== Bitmap ��V�K�ɍ쐬���� =====
// ===================================
    if (bmp != NULL) {
    	delete bmp;			// ���̈���
    }
    bmp = new (Graphics::TBitmap);

/*    if (strcmp(ext, ".BMP") == 0 || strcmp(ext, ".ICO") == 0 || strcmp(ext, ".WMF") == 0
    	|| strcmp(ext, ".EMF") == 0) {
// =================================
// ===== BITMAP �t�@�C�����ꍇ =====
// =================================
		bmp->LoadFromFile(filename);
        if (bmp->Empty == false)
        	ret = true;
    }nito070202*/

    if (ret == false) {
// ================================================
// ===== VCL �ŏ����ł��Ȃ��摜�t�@�C���̏ꍇ =====
// ================================================
	    if ((*now_spi->GetPictureInfo)(filename, 0, 0, &pinfo) == 0) {
// Bitmap �I�u�W�F�N�g��V�K�쐬���ĕ��ƍ�����ݒ�
	    	bmp->Width = pinfo.width;
    		bmp->Height = pinfo.height;
        	color_depth = pinfo.color;
		    GlobalFree(pinfo.info);			// TEXT info ���

// �摜�̃��[�h
    	    if ( (*now_spi->GetPicture)(filename, 0, 0,  &bmpinfo, &bmpdata, NULL, 0) == 0 ) {
	    		pbmpdata = GlobalLock(bmpdata);		// Win32 API �Ń��b�N
    			pbmpinfo = (LPBITMAPINFO)GlobalLock(bmpinfo);

// �摜�̎擾
	        	if (SetDIBits(bmp->Canvas->Handle, bmp->Handle, 0, pinfo.height
    	        			,pbmpdata, pbmpinfo, DIB_RGB_COLORS) == 0) {
        	    	err = GetLastError();		// API error
            	} else {
            		ret = true;			// ����
	            }
// ��n��
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
// 				�p���\���ް���p��
//		(�p�����񂾂�Ăяo���΁A���������ߖ�ł���)
// **************************************************************
void	TSpiload::clean(void)
{
	if (bmp != NULL) {
    	delete bmp;				// Bitmap ��p��
    }
}
