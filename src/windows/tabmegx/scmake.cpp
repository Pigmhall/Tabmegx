///////////////////////////////////////
// �V���[�g�J�b�g�쐬�R���|�[�l���g
// TSCMake 
// 98/09/24	Ver 1.0
// 99/06/22 Ver 1.1 �����ǉ�
// ��� yamak yamak@a2.mbn.or.jp
///////////////////////////////////////
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SCMake.h"
#pragma package(smart_init)          

// ���[�U�[��`
//#include <shlobj.h>

//---------------------------------------------------------------------------
// ValidCtrCheck �͍쐬���ꂽ�R���|�[�l���g���������z�֐��������Ȃ����Ƃ�
// �ۏ؂��邽�߂Ɏg�p����܂��B
//

/*static inline void ValidCtrCheck(TSCMake *)
{
	new TSCMake(NULL);
} */
//---------------------------------------------------------------------------
// ������
__fastcall TSCMake::TSCMake(TComponent* Owner)
	: TComponent(Owner)
{
	// COM�g�p�̂��߂̏���
	CoInitialize(NULL);
}
//---------------------------------------------------------------------------
/*namespace Scmake
{
	void __fastcall Register()
	{
		TComponentClass classes[1] = {__classid(TSCMake)};
		RegisterComponents("Samples", classes, 0);
	}
} */
//---------------------------------------------------------------------------
__fastcall TSCMake::~TSCMake()
{
	// COM�I�u�W�F�N�g�쐬�̌�n��
	CoUninitialize();
}

////////////////////////
// ���\�b�h
// �V���[�g�J�b�g�쐬
int __fastcall TSCMake::CreateLink()
{
	// �G���[�l�̏���
	if (FSCName == "" || FSCDir == "" || FLinkPath == ""){
		return(-1);
	}

	// �V���[�g�J�b�g�L�[���Ȃ��Ƃ�
	if ((FSCKey & 0x00FF) == 0){
		FSCKey = 0;
	}

	// ��������͂قƂ��SBORLAND��C++Builder��c������̈��p
	// �Ƃ����������MS�̃h�L�������g����̈��p�̂͂�
	// Inside Windows 98�N1�������Q�l�ɂ���
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	// COM�I�u�W�F�N�g�쐬
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, &(void*)psl);

	if (SUCCEEDED(hres)) {
		// �����N��
		psl->SetPath(FLinkPath.c_str());
		// ��ƃt�H���_
		psl->SetWorkingDirectory(FWorkDir.c_str());
		// �E�C���h�E���
		psl->SetShowCmd(FWndState);
		// �V���[�g�J�b�g�L�[
		psl->SetHotkey(FSCKey);
		// �A�C�R��
		psl->SetIconLocation(FIconPath.c_str(), FIconNo);

		// 99/06/21�ǉ�
		// ����
		psl->SetArguments(FArgument.c_str());

		// �t�@�C���쐬�p�C���^�[�t�F�[�X�擾
		hres = psl->QueryInterface(IID_IPersistFile,&(void*)ppf);
		if (SUCCEEDED(hres)) {
			wchar_t wsz[MAX_PATH];

			// �t�@�C���������
			FileName = FSCDir + "\\" + FSCName + ".lnk";
			FileName.WideChar(wsz, MAX_PATH);

			// �V���[�g�J�b�g�쐬
			hres = ppf->Save(wsz, TRUE);
		}
	}

	return (hres);
}


////////////////////
// �V���[�g�J�b�g���
int __fastcall TSCMake::AnalizeLink(String SCFileName)
{
	// ��������͂قƂ��SBORLAND��C++Builder��c������̈��p
	// �Ƃ����������MS�̃h�L�������g����̈��p�̂͂�
	// Inside Windows 98�N1�������Q�l�ɂ���
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	// �V���[�g�J�b�g�łȂ���΂�߂�
	if (ExtractFileExt(SCFileName) != ".lnk") return(-1);

	// COM�I�u�W�F�N�g�쐬
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, &(void*)psl);
	if (!SUCCEEDED(hres)) return(-1);

	// �t�@�C���쐬�p�C���^�[�t�F�[�X�擾
	hres = psl->QueryInterface(IID_IPersistFile,&(void*)ppf);
	if (!SUCCEEDED(hres)) return (-1);

	// �t�@�C���������
	wchar_t WFileName[MAX_PATH];
	SCFileName.WideChar(WFileName, MAX_PATH);

	// �V���[�g�J�b�g�擾
	hres = ppf->Load(WFileName, STGM_READ);
	if (!SUCCEEDED(hres)) return (-1);

	// �V���[�g�J�b�g�̖��O
	FSCName = ChangeFileExt(ExtractFileName(SCFileName), "");

	// �f�B���N�g��
	FSCDir = ExtractFileDir(SCFileName);

	// �����N��
	WIN32_FIND_DATA Ffblk;
	char str[MAX_PATH + 1];

	psl->GetPath(str, MAX_PATH, &Ffblk, SLGP_UNCPRIORITY);
	FLinkPath = str;

	// ��ƃt�H���_
	psl->GetWorkingDirectory(str, MAX_PATH);
	FWorkDir = str;

	// �E�C���h�E���
	psl->GetShowCmd(&FWndState);
	
	// �V���[�g�J�b�g�L�[
	psl->GetHotkey(&FSCKey);

	// �A�C�R��
	psl->GetIconLocation(str, MAX_PATH, &FIconNo);
	FIconPath = str;

	// 99/06/21�ǉ�
	// ����
	psl->GetArguments(str, MAX_PATH);
	FArgument = str;

	return(0);
}

//////////////////////////////
// �v���p�e�B
///////////////////////////////////
// �V���[�g�J�b�g�L�[
// Inside Windows 98�N1�������Q�l
void __fastcall TSCMake::SetSCKey(TShortCut SCKey)
{
	TShiftState Shift;
	WORD Key = 0;

	// C++Builder��TShortCut�^��
	// �V���[�g�J�b�g�쐬���Ɏg���`�ɕύX
	ShortCutToKey(SCKey, FSCKey, Shift);

	if (FSCKey == 0) return;

	// �����ɉ����L�[�����߂�
	// �񋓌^�͍ŏ��悭�킩��Ȃ�����
	if (Shift.Contains(ssShift)){	// Shift�L�[
		Key |= (WORD)HOTKEYF_SHIFT;
	}
	if (Shift.Contains(ssAlt)){	// Alt�L�[
		Key |= (WORD)HOTKEYF_ALT;
	}
	if (Shift.Contains(ssCtrl)){	// Ctrl�L�[
		Key |= (WORD)HOTKEYF_CONTROL;
	}

	// �����L�[�͂��̂܂܂炵��
	Key <<= 8;
	FSCKey |= Key;
}

TShortCut __fastcall TSCMake::GetSCKey()
{
	TShiftState Shift;
	WORD Key, ScShift;

	// �����L�[�͂��̂܂܂炵��
	Key = (WORD)(FSCKey & 0x00ff);
	ScShift = (WORD)((FSCKey & 0xff00) >> 8);

	// �����ɉ����L�[�����߂�
	// �񋓌^�͍ŏ��悭�킩��Ȃ�����
	if (ScShift & HOTKEYF_SHIFT){ // Shift�L�[
		Shift << ssShift;
	}
	if (ScShift & HOTKEYF_ALT){ // Alt�L�[
		Shift << ssAlt;
	}
	if (ScShift & HOTKEYF_CONTROL){ // Ctrl�L�[
		Shift << ssCtrl;
	}

	return ShortCut(Key, Shift);
}

////////////////////////////
// �E�B���h�E���
void __fastcall TSCMake::SetWndState(WNDSTATE WndState)
{
	// �񋓌^�̃v���p�e�B��
	// �V���[�g�J�b�g�쐬���Ɏg���`�ɕύX
	if(WndState == Maximize){	// �ő剻
		FWndState = SW_MAXIMIZE;
	}else if(WndState == Minimize){	// �ŏ���
		FWndState = SW_SHOWMINNOACTIVE;
	}else{	// �W��
		FWndState = SW_SHOW;
	}
}

WNDSTATE __fastcall TSCMake::GetWndState()
{
	// �񋓌^�̃v���p�e�B��
	// �V���[�g�J�b�g�쐬���Ɏg���`�ɕύX
	if(FWndState == SW_MAXIMIZE){	// �ő剻
		return Maximize;
	}else if(FWndState == SW_SHOWMINNOACTIVE){	// �ŏ���
		return Minimize;
	}else{	// �W��
		return Normal;
	}
}




