//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//   OLE�h���b�O&�h���b�v��C�݂̂ōs��DLL
//
//                             Copyright (C) Copyright 1998,2002 PATA
//                        Original source by nakka(Tomoaki Nakashima)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#ifndef _INC_OLEDRAGDROP
#define _INC_OLEDRAGDROP

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif
#define _stdcall
enum IDROPTARGET_NOTIFY_MSG {
	IDROPTARGET_NOTIFY_DRAGENTER=0,
	IDROPTARGET_NOTIFY_DRAGOVER,
	IDROPTARGET_NOTIFY_DRAGLEAVE,
	IDROPTARGET_NOTIFY_DROP,
};

// dwEffect
#ifndef	DROPEFFECT_NONE
#define	DROPEFFECT_NONE		(0)
#define	DROPEFFECT_COPY		(1)
#define	DROPEFFECT_MOVE		(2)
#define	DROPEFFECT_LINK		(4)
#define	DROPEFFECT_SCROLL	(0x80000000)
#endif

// grfKeyState
#ifndef	MK_LBUTTON
#define	MK_LBUTTON	0x0001
#define	MK_RBUTTON	0x0002
#define	MK_SHIFT	0x0004
#define	MK_CONTROL	0x0008
#define	MK_MBUTTON	0x0010
#endif

typedef struct _IDROPTARGET_NOTIFY {
	POINTL *ppt;					//�}�E�X�̈ʒu
	DWORD dwEffect;					//�h���b�O����ŁA�h���b�O�����Ώۂŋ���������
	DWORD grfKeyState;				//�L�[�̏��
	UINT cfFormat;					//�h���b�v�����f�[�^�̃N���b�v�{�[�h�t�H�[�}�b�g
	HANDLE hMem;					//�h���b�v�����f�[�^
	LPVOID pdo;						//IDataObject
}IDROPTARGET_NOTIFY , *LPIDROPTARGET_NOTIFY;

//-----------------------------------------------------------------------------
// �E�B���h�E��DnD�̃^�[�Q�b�g�Ƃ��ēo�^����
// IN  hWnd: DnD�^�[�Q�b�g�Ƃ��ēo�^����E�B���h�E
//     uCallbackMessage: DnD���s��ꂽ�Ƃ��ɃE�B���h�E�ɑ��M����郁�b�Z�[�W
//                   ���M����郁�b�Z�[�W�̃p�����[�^�ɂ͈ȉ����ݒ肳���
//                   wParam: ����̎��(IDROPTARGET_NOTIFY_MSG)
//                   lParam: IDROPTARGET_NOTIFY�\���̂ւ̃|�C���^
//     cFormat: �󂯎�邱�Ƃ��\�ȃN���b�v�{�[�h�t�H�[�}�b�g�̃��X�g
//     cfcnt: �N���b�v�{�[�h�t�H�[�}�b�g�̔z��̗v�f��
// OUT ret:�o�^�ɐ���������
//-----------------------------------------------------------------------------
DLLEXPORT BOOL _stdcall OLE_IDropTarget_RegisterDragDrop(HWND hWnd,UINT uCallbackMessage,UINT* cFormat,int cfcnt);

//-----------------------------------------------------------------------------
// DnD�̃^�[�Q�b�g����������
// IN  hWnd: DnD�^�[�Q�b�g�Ƃ��ēo�^���Ă���E�B���h�E
//-----------------------------------------------------------------------------
DLLEXPORT void _stdcall OLE_IDropTarget_RevokeDragDrop(HWND hWnd);


//-----------------------------------------------------------------------------
// DnD���J�n����
// IN  hWnd: �ȉ��̃f�[�^�v���EDnD�I�����b�Z�[�W���󂯎��E�B���h�E
//     uCallbackGetData: DnD����f�[�^���K�v�ȂƂ��ɃE�B���h�E�ɑ��M����郁�b�Z�[�W
//                   ���M����郁�b�Z�[�W�̃p�����[�^�ɂ͈ȉ����ݒ肳���
//                   wParam: �v�������N���b�v�{�[�h�t�H�[�}�b�g�̔z��
//                   lParam: �f�[�^���i�[����HANDLE�ւ̃|�C���^
//                           *(HANDLE*)lParam �Ƀf�[�^��ݒ肵�ĕԂ�(NULL�ł���)
//     uCallbackDropEnd: DnD���I�������Ƃ��ɃE�B���h�E�ɑ��M����郁�b�Z�[�W
//                   ���M����郁�b�Z�[�W�̃p�����[�^�ɂ͈ȉ����ݒ肳���
//                   wParam: �h���b�v���삪���������ꍇ��DRAGDROP_S_DROP
//                           �L�����Z�����ꂽ��DRAGDROP_S_CANCEL
//                   lParam: 0
//     ClipFormtList: �T�|�[�g���Ă���N���b�v�{�[�h�t�H�[�}�b�g�̔z��
//     cfcnt: �N���b�v�{�[�h�t�H�[�}�b�g�̔z��̗v�f��
//     Effect: �h���b�O����Ńh���b�O�����Ώۂŋ��������ʂ̑g�ݍ��킹
// OUT ret: �h���b�v��̃A�v���P�[�V�������ݒ肵������(Cancel/Error����-1)
//-----------------------------------------------------------------------------
DLLEXPORT int _stdcall OLE_IDropSource_Start(HWND hWnd,UINT uCallbackGetData,UINT uCallbackDropEnd,UINT *ClipFormtList,int cfcnt,int Effect);


//-----------------------------------------------------------------------------
// �h���b�v�t�@�C���̍쐬
// IN  FileName:�t�@�C�����̔z��, cnt:�t�@�C����
// OUT ret:�h���b�v�t�@�C���\����(HDROP)
//-----------------------------------------------------------------------------
DLLEXPORT HDROP _stdcall CreateDropFileMem(char** FileName,int cnt);


//-----------------------------------------------------------------------------
// �h���b�v�t�@�C���\���̂���t���p�X�t�@�C�������X�g(xxx\0yyy\0\0�̌`��)���쐬
// IN   filelist:�t�@�C�������X�g�̊i�[��, bufsize:filelist�̃T�C�Y
// OUT  ret:�h���b�v���ꂽ�t�@�C����
//-----------------------------------------------------------------------------
DLLEXPORT int _stdcall GetDropFileList(HDROP hDrop,char* filelist,int bufsize);


#ifdef __cplusplus
}
#endif

#endif
