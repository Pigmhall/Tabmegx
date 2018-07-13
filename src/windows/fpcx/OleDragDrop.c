//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//   OLE�h���b�O&�h���b�v��C�݂̂ōs��DLL
//
//                             Copyright (C) Copyright 1998,2002 PATA
//                        Original source by nakka(Tomoaki Nakashima)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/*----------------------
	include
----------------------*/
#define _INC_OLE
#include <windows.h>
#undef	_INC_OLE

#include <oleidl.h>
#include <objidl.h>
#include <Shlobj.h>

#include "OleDragDrop.h"

#ifndef	ARRAYSIZE
#define	ARRAYSIZE(a)	(sizeof(a)/sizeof(a[0]))
#endif
#define APIPRIVATE
//-----------------------------------------------------------------------------
// �h���b�v�t�@�C���̍쐬
// IN  FileName:�t�@�C�����z��, cnt:�t�@�C����
// OUT ret:�h���b�v�t�@�C���\����(HDROP)
//-----------------------------------------------------------------------------
HDROP CreateDropFileMem(char **FileName,int cnt)
{
	BOOL fWide;
	HDROP hDrop;
	LPDROPFILES lpDropFile;
	wchar_t wbuf[_MAX_PATH];
	int flen = 0;
	int i;
	OSVERSIONINFO os_info;
	os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os_info);
	fWide = (os_info.dwPlatformId == VER_PLATFORM_WIN32_NT);
	if (fWide == TRUE) {		/* ���C�h�L���� */
		for (i=0; i<cnt; i++) {
			MultiByteToWideChar(CP_ACP,0,FileName[i],-1,wbuf,ARRAYSIZE(wbuf));
			flen += (wcslen(wbuf) + 1) * sizeof(wchar_t);
		}
		flen++;
	} else {		/* �}���`�o�C�g */
		for (i=0; i<cnt; i++) {
			flen += lstrlen(FileName[i]) + 1;
		}
	}
	hDrop = (HDROP)GlobalAlloc(GHND,sizeof(DROPFILES) + flen + 1);
	if (hDrop == NULL) return NULL;
	lpDropFile = (LPDROPFILES)GlobalLock(hDrop);
	lpDropFile->pFiles = sizeof(DROPFILES);		/* �t�@�C�����̃��X�g�܂ł̃I�t�Z�b�g */
	lpDropFile->pt.x = 0;
	lpDropFile->pt.y = 0;
	lpDropFile->fNC = FALSE;
	lpDropFile->fWide = fWide;					/* ���C�h�L�����̏ꍇ�� TRUE */
	/* �\���̂̌��Ƀt�@�C�����̃��X�g���R�s�[(file1\0file2\0file3\0\0) */
	if (fWide == TRUE) {		/* ���C�h�L���� */
		wchar_t *buf;
		buf = (wchar_t *)(&lpDropFile[1]);
		for (i=0; i<cnt; i++) {
			MultiByteToWideChar(CP_ACP,0,FileName[i],-1,wbuf,ARRAYSIZE(wbuf));
			wcscpy(buf,wbuf);
			buf += wcslen(wbuf) + 1;
		}
	} else {		/* �}���`�o�C�g */
		char *buf;
		buf = (char *)(&lpDropFile[1]);
		for (i=0; i<cnt; i++) {
			lstrcpy(buf,FileName[i]);
			buf += lstrlen(FileName[i]) + 1;
		}
	}
	GlobalUnlock(hDrop);
	return hDrop;
}

//-----------------------------------------------------------------------------
// �h���b�v�t�@�C���\���̂���t���p�X�t�@�C�������X�g(xxx\0yyy\0\0�̌`��)���쐬
// IN   filelist:�t�@�C�������X�g�̊i�[��, bufsize:filelist�̃T�C�Y
// OUT  ret:�h���b�v���ꂽ�t�@�C����
//-----------------------------------------------------------------------------

/*----------------------
	function
----------------------*/
/*----------------------
	IEnumFORMATETC
----------------------*/
HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_QueryInterface(LPENUMFORMATETC lpThis,REFIID riid,LPVOID FAR* lplpvObj);
ULONG STDMETHODCALLTYPE OLE_IEnumFORMATETC_AddRef(LPENUMFORMATETC lpThis);
ULONG STDMETHODCALLTYPE OLE_IEnumFORMATETC_Release(LPENUMFORMATETC lpThis);
HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Next(LPENUMFORMATETC lpThis,ULONG celt,FORMATETC *rgelt,ULONG *pceltFetched);
HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Skip(LPENUMFORMATETC lpThis,ULONG celt);
HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Reset(LPENUMFORMATETC lpThis);
HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Clone(LPENUMFORMATETC lpThis,IEnumFORMATETC **ppenum);

/* IEnumFORMATETC Virtual Table */
static IEnumFORMATETCVtbl efv = {
	OLE_IEnumFORMATETC_QueryInterface,
	OLE_IEnumFORMATETC_AddRef,
	OLE_IEnumFORMATETC_Release,
	OLE_IEnumFORMATETC_Next,
	OLE_IEnumFORMATETC_Skip,
	OLE_IEnumFORMATETC_Reset,
	OLE_IEnumFORMATETC_Clone
};

typedef struct _IENUMFORMATETC_INTERNAL{
	LPVOID lpVtbl;
	ULONG m_refCnt;
	LPUNKNOWN m_pUnknownObj;
	ULONG m_currElement;
	ULONG m_numFormats;
	LPFORMATETC m_formatList;
}IENUMFORMATETC_INTERNAL , *LPIENUMFORMATETC_INTERNAL;

static HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_QueryInterface(LPENUMFORMATETC lpThis,REFIID riid,LPVOID FAR* lplpvObj)
{
	//�v�����ꂽIID�Ɠ����ꍇ�̓I�u�W�F�N�g��Ԃ��B
	if(IsEqualIID(riid,&IID_IUnknown) || IsEqualIID(riid,&IID_IEnumFORMATETC)){
		*lplpvObj = (LPVOID) lpThis;
		 ((LPUNKNOWN)*lplpvObj)->lpVtbl->AddRef(((LPUNKNOWN)*lplpvObj));
		return S_OK;
	}

	*lplpvObj = NULL;
	return ResultFromScode(E_NOINTERFACE);
}

static ULONG STDMETHODCALLTYPE OLE_IEnumFORMATETC_AddRef(LPENUMFORMATETC lpThis)
{
	CONST LPIENUMFORMATETC_INTERNAL pefi = (LPIENUMFORMATETC_INTERNAL)lpThis;

	/* reference count���C���N�������g���� */
	pefi->m_refCnt++;
	/* �e�I�u�W�F�N�g��reference count�������� */
	pefi->m_pUnknownObj->lpVtbl->AddRef(pefi->m_pUnknownObj);

	return pefi->m_refCnt;
}

static ULONG STDMETHODCALLTYPE OLE_IEnumFORMATETC_Release(LPENUMFORMATETC lpThis)
{
	CONST LPIENUMFORMATETC_INTERNAL pefi = (LPIENUMFORMATETC_INTERNAL)lpThis;

	/* reference count���f�N�������g���� */
	pefi->m_refCnt--;
	/* �e�I�u�W�F�N�g��reference count�����炷 */
	pefi->m_pUnknownObj->lpVtbl->Release(pefi->m_pUnknownObj);

	/* reference count�� 0 �ɂȂ����ꍇ�̓I�u�W�F�N�g�̉�����s�� */
	if(pefi->m_refCnt == 0L){
		if(pefi->m_formatList != NULL){
			GlobalFree(pefi->m_formatList);
		}
		GlobalFree(pefi);
		return 0L;
	}

	return pefi->m_refCnt;
}

static HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Next(LPENUMFORMATETC lpThis,ULONG celt,FORMATETC *rgelt,ULONG *pceltFetched)
{
	ULONG i;
	ULONG cReturn=0L;
	LPIENUMFORMATETC_INTERNAL lpefi = ((LPIENUMFORMATETC_INTERNAL)lpThis);

	if(pceltFetched){
		*pceltFetched = 0L;
	}
	if(lpefi->m_formatList == NULL){
		return ResultFromScode(S_FALSE);
	}

	if(rgelt == NULL){
		if(celt == 1){
			return ResultFromScode(S_FALSE);
		}else{
			return ResultFromScode(E_POINTER);
		}
	}

	if(lpefi->m_currElement >= lpefi->m_numFormats){
		return ResultFromScode(S_FALSE);
	}

	for(i = 0;i < celt && lpefi->m_currElement < lpefi->m_numFormats;i++,lpefi->m_currElement++){
		*rgelt = lpefi->m_formatList[lpefi->m_currElement];
		rgelt++;
	}

	if(pceltFetched != NULL){
		*pceltFetched = i;
	}

	return S_OK;

}

static HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Skip(LPENUMFORMATETC lpThis,ULONG celt)
{
	LPIENUMFORMATETC_INTERNAL lpefi = ((LPIENUMFORMATETC_INTERNAL)lpThis);

	lpefi->m_currElement += celt;

	if(lpefi->m_currElement > lpefi->m_numFormats){
		lpefi->m_currElement = lpefi->m_numFormats;
		return ResultFromScode(S_FALSE);
	}
	return S_OK;
}

static HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Reset(LPENUMFORMATETC lpThis)
{
	LPIENUMFORMATETC_INTERNAL lpefi = ((LPIENUMFORMATETC_INTERNAL)lpThis);

	lpefi->m_currElement = 0L;
	return S_OK;
}

static HRESULT STDMETHODCALLTYPE OLE_IEnumFORMATETC_Clone(LPENUMFORMATETC lpThis,IEnumFORMATETC **ppenum)
{
	LPIENUMFORMATETC_INTERNAL pNew;
	LPIENUMFORMATETC_INTERNAL lpefi = ((LPIENUMFORMATETC_INTERNAL)lpThis);
	UINT i;

	/* IEnumFORMATETC���쐬���� */
	pNew = GlobalAlloc(GPTR,sizeof(IENUMFORMATETC_INTERNAL));
	pNew->lpVtbl = (LPVOID)&efv;
	pNew->m_refCnt = 0;
	pNew->m_currElement = 0;

	pNew->m_pUnknownObj = lpefi->m_pUnknownObj;
	pNew->m_numFormats = lpefi->m_numFormats;

	/* �N���b�v�{�[�h�t�H�[�}�b�g�̃��X�g���R�s�[���� */
	pNew->m_formatList = GlobalAlloc(GPTR,sizeof(FORMATETC) * pNew->m_numFormats);
	if(pNew->m_formatList != NULL){
		for(i = 0;i < pNew->m_numFormats;i++){
		    pNew->m_formatList[i] = lpefi->m_formatList[i];
		}
	}

	*ppenum = (struct IEnumFORMATETC *)pNew;
	if(pNew == NULL){
		return ResultFromScode(E_OUTOFMEMORY);
	}
	((LPENUMFORMATETC)pNew)->lpVtbl->AddRef(((LPENUMFORMATETC)pNew));
	pNew->m_currElement = lpefi->m_currElement;

	return S_OK;
}


/*----------------------
	IDataObject
----------------------*/
HRESULT STDMETHODCALLTYPE OLE_IDataObject_QueryInterface(LPDATAOBJECT lpThis,REFIID riid,LPVOID FAR *lplpvObj);
ULONG STDMETHODCALLTYPE OLE_IDataObject_AddRef(LPDATAOBJECT lpThis);
ULONG STDMETHODCALLTYPE OLE_IDataObject_Release(LPDATAOBJECT lpThis);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetDataHere(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_QueryGetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetCanonicalFormatEtc(LPDATAOBJECT lpThis,FORMATETC *pFormatetcIn,FORMATETC *pFormatetcOut);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_SetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium,BOOL fRelease);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_EnumFormatEtc(LPDATAOBJECT lpThis,DWORD dwDirection,IEnumFORMATETC **ppenumFormatetc);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_DAdvise(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,DWORD advf,IAdviseSink *pAdvSink,DWORD *pdwConnection);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_DUnadvise(LPDATAOBJECT lpThis,DWORD dwConnection);
HRESULT STDMETHODCALLTYPE OLE_IDataObject_EnumDAdvise(LPDATAOBJECT lpThis,IEnumSTATDATA **ppenumAdvise);

/* IDataObject Virtual Table */
static IDataObjectVtbl dov = {
	OLE_IDataObject_QueryInterface,
	OLE_IDataObject_AddRef,
	OLE_IDataObject_Release,
	OLE_IDataObject_GetData,
	OLE_IDataObject_GetDataHere,
	OLE_IDataObject_QueryGetData,
	OLE_IDataObject_GetCanonicalFormatEtc,
	OLE_IDataObject_SetData,
	OLE_IDataObject_EnumFormatEtc,
	OLE_IDataObject_DAdvise,
	OLE_IDataObject_DUnadvise,
	OLE_IDataObject_EnumDAdvise
};

typedef struct _IDATAOBJECT_INTERNAL{
	LPVOID lpVtbl;
	ULONG m_refCnt;
	UINT m_numTypes;
	UINT m_maxTypes;
	FORMATETC *m_typeList;
	HWND hWnd;
	UINT uCallbackMessage;
}IDATAOBJECT_INTERNAL , *LPIDATAOBJECT_INTERNAL;


static HRESULT STDMETHODCALLTYPE OLE_IDataObject_QueryInterface(LPDATAOBJECT lpThis,REFIID riid,LPVOID FAR *lplpvObj)
{
	//�v�����ꂽIID�Ɠ����ꍇ�̓I�u�W�F�N�g��Ԃ��B
	if(IsEqualIID(riid,&IID_IUnknown) || IsEqualIID(riid,&IID_IDataObject)){
		*lplpvObj = lpThis;
		 ((LPUNKNOWN)*lplpvObj)->lpVtbl->AddRef(((LPUNKNOWN)*lplpvObj));
		return S_OK;
	}

	*lplpvObj = NULL;
	return ResultFromScode(E_NOINTERFACE);
}

static ULONG STDMETHODCALLTYPE OLE_IDataObject_AddRef(LPDATAOBJECT lpThis)
{
	CONST LPIDATAOBJECT_INTERNAL pdoi = (LPIDATAOBJECT_INTERNAL)lpThis;

	/* reference count���C���N�������g���� */
	pdoi->m_refCnt++;
	return pdoi->m_refCnt;
}

static ULONG STDMETHODCALLTYPE OLE_IDataObject_Release(LPDATAOBJECT lpThis)
{
	CONST LPIDATAOBJECT_INTERNAL pdoi = (LPIDATAOBJECT_INTERNAL)lpThis;

	/* reference count���f�N�������g���� */
	pdoi->m_refCnt--;

	/* reference count�� 0 �ɂȂ����ꍇ�̓I�u�W�F�N�g�̉�����s�� */
	if(pdoi->m_refCnt == 0L){
		if(pdoi->m_typeList != NULL){
			GlobalFree(pdoi->m_typeList);
		}
		GlobalFree(pdoi);
		return 0L;
	}
	return pdoi->m_refCnt;
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium)
{
	CONST LPIDATAOBJECT_INTERNAL pdoi = (LPIDATAOBJECT_INTERNAL)lpThis;
	HGLOBAL hMem;
	UINT i;

	/* �v�����ꂽ�N���b�v�{�[�h�t�H�[�}�b�g�����݂��邩���ׂ� */
	for(i = 0;i < pdoi->m_numTypes;i++){
		if(pdoi->m_typeList[i].cfFormat == pFormatetc->cfFormat){
			if(pFormatetc->tymed & TYMED_HGLOBAL){
				break;
			}
		}
	}
	if(i == pdoi->m_numTypes){
		/* �v�����ꂽ�N���b�v�{�[�h�t�H�[�}�b�g���T�|�[�g���ĂȂ��ꍇ */
		return ResultFromScode(DV_E_FORMATETC);
	}

	/* �E�B���h�E�Ƀf�[�^�̗v�����s�� */
	SendMessage(pdoi->hWnd,pdoi->uCallbackMessage,(WPARAM)pdoi->m_typeList[i].cfFormat,(LPARAM)&hMem);
	if(hMem == NULL){
		return ResultFromScode(STG_E_MEDIUMFULL);
	}

	pmedium->u.hGlobal = hMem;
	pmedium->tymed = TYMED_HGLOBAL;
	pmedium->pUnkForRelease = NULL;

	return S_OK;
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetDataHere(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium)
{
	return ResultFromScode(E_NOTIMPL);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_QueryGetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc)
{
	CONST LPIDATAOBJECT_INTERNAL pdoi = (LPIDATAOBJECT_INTERNAL)lpThis;
	UINT i;

	/* �v�����ꂽ�N���b�v�{�[�h�t�H�[�}�b�g�����݂��邩���ׂ� */
	for(i = 0;i < pdoi->m_numTypes;i++){
		if(pdoi->m_typeList[i].cfFormat == pFormatetc->cfFormat){
			if(pFormatetc->tymed & TYMED_HGLOBAL){
				return S_OK;
			}
		}
	}

	return ResultFromScode(DV_E_FORMATETC);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_GetCanonicalFormatEtc(LPDATAOBJECT lpThis,FORMATETC *pFormatetcIn,FORMATETC *pFormatetcOut)
{
	return ResultFromScode(E_NOTIMPL);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_SetData(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,STGMEDIUM *pmedium,BOOL fRelease)
{
	return ResultFromScode(E_NOTIMPL);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_EnumFormatEtc(LPDATAOBJECT lpThis,DWORD dwDirection,IEnumFORMATETC **ppenumFormatetc)
{
	CONST LPIDATAOBJECT_INTERNAL pdoi = (LPIDATAOBJECT_INTERNAL)lpThis;
	static IENUMFORMATETC_INTERNAL *pefi;
	UINT i;

	if(ppenumFormatetc == NULL){
		return ResultFromScode(E_INVALIDARG);
	}

	if(dwDirection != DATADIR_GET){
		*ppenumFormatetc = NULL;
		return ResultFromScode(E_NOTIMPL);
	}

	/* IEnumFORMATETC���쐬���� */
	pefi = GlobalAlloc(GPTR,sizeof(IENUMFORMATETC_INTERNAL));

	pefi->lpVtbl = (LPVOID)&efv;
	pefi->m_refCnt = 0;
	pefi->m_currElement = 0;

	pefi->m_pUnknownObj = (struct IUnknown *)lpThis;
	pefi->m_numFormats = pdoi->m_numTypes;

	/* �N���b�v�{�[�h�t�H�[�}�b�g�̃��X�g���R�s�[���� */
	pefi->m_formatList = GlobalAlloc(GPTR,sizeof(FORMATETC) * pefi->m_numFormats);
	if(pefi->m_formatList != NULL){
		for(i = 0;i < pefi->m_numFormats;i++){
		    pefi->m_formatList[i] = pdoi->m_typeList[i];
		}
	}
	
	((LPENUMFORMATETC)pefi)->lpVtbl->AddRef(((LPENUMFORMATETC)pefi));

	*ppenumFormatetc = (struct IEnumFORMATETC *)pefi;

	if(*ppenumFormatetc == NULL){
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_DAdvise(LPDATAOBJECT lpThis,FORMATETC *pFormatetc,DWORD advf,IAdviseSink *pAdvSink,DWORD *pdwConnection)
{
	return ResultFromScode(OLE_E_ADVISENOTSUPPORTED);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_DUnadvise(LPDATAOBJECT lpThis,DWORD dwConnection)
{
	return ResultFromScode(OLE_E_NOCONNECTION);
}

static HRESULT STDMETHODCALLTYPE OLE_IDataObject_EnumDAdvise(LPDATAOBJECT lpThis,IEnumSTATDATA **ppenumAdvise)
{
	return ResultFromScode(OLE_E_ADVISENOTSUPPORTED);
}

/*----------------------
	IDropSource
----------------------*/
HRESULT STDMETHODCALLTYPE OLE_IDropSource_QueryInterface(LPDROPSOURCE lpThis,REFIID riid,LPVOID FAR* lplpvObj);
ULONG STDMETHODCALLTYPE OLE_IDropSource_AddRef(LPDROPSOURCE lpThis);
ULONG STDMETHODCALLTYPE OLE_IDropSource_Release(LPDROPSOURCE lpThis);
HRESULT STDMETHODCALLTYPE OLE_IDropSource_QueryContinueDrag(LPDROPSOURCE lpThis,BOOL fEscapePressed,DWORD grfKeyState);
HRESULT STDMETHODCALLTYPE OLE_IDropSource_GiveFeedback(LPDROPSOURCE lpThis,DWORD dwEffect);

/* IDropSource Virtual Table */
static IDropSourceVtbl dsv = {
	OLE_IDropSource_QueryInterface,
	OLE_IDropSource_AddRef,
	OLE_IDropSource_Release,
	OLE_IDropSource_QueryContinueDrag,
	OLE_IDropSource_GiveFeedback,
};

typedef struct _IDROPSOURCE_INTERNAL{
	LPVOID lpVtbl;
	ULONG m_refCnt;
	DWORD m_keyState;
	DWORD m_button;
	UINT uCallbackMessage;
	HWND hWnd;
}IDROPSOURCE_INTERNAL , *LPIDROPSOURCE_INTERNAL;

static HRESULT STDMETHODCALLTYPE OLE_IDropSource_QueryInterface(LPDROPSOURCE lpThis,REFIID riid,LPVOID FAR *lplpvObj)
{
	//�v�����ꂽIID�Ɠ����ꍇ�̓I�u�W�F�N�g��Ԃ��B
	if(IsEqualIID(riid,&IID_IUnknown) || IsEqualIID(riid,&IID_IDropSource)){
		*lplpvObj = (LPVOID) lpThis;
		((LPUNKNOWN)*lplpvObj)->lpVtbl->AddRef(((LPUNKNOWN)*lplpvObj));
		return S_OK;
	}

	*lplpvObj = NULL;
	return ResultFromScode(E_NOINTERFACE);

}

static ULONG STDMETHODCALLTYPE OLE_IDropSource_AddRef(LPDROPSOURCE lpThis)
{
	CONST LPIDROPSOURCE_INTERNAL pdsi = (LPIDROPSOURCE_INTERNAL)lpThis;

	/* reference count���C���N�������g���� */
	pdsi->m_refCnt++;
	return pdsi->m_refCnt;
}

static ULONG STDMETHODCALLTYPE OLE_IDropSource_Release(LPDROPSOURCE lpThis)
{
	CONST LPIDROPSOURCE_INTERNAL pdsi = (LPIDROPSOURCE_INTERNAL)lpThis;
	
	/* reference count���f�N�������g���� */
	pdsi->m_refCnt--;

	/* reference count�� 0 �ɂȂ����ꍇ�̓I�u�W�F�N�g�̉�����s�� */
	if(pdsi->m_refCnt == 0L){
		GlobalFree(pdsi);
		return 0L;
	}
	return pdsi->m_refCnt;
}

static HRESULT STDMETHODCALLTYPE OLE_IDropSource_QueryContinueDrag(LPDROPSOURCE lpThis,BOOL fEscapePressed, DWORD grfKeyState)
{
	CONST LPIDROPSOURCE_INTERNAL pdsi = (LPIDROPSOURCE_INTERNAL)lpThis;

	if(fEscapePressed){
		/* �G�X�P�[�v�������ꂽ�ꍇ�̓L�����Z���ɂ��� */
		SendMessage(pdsi->hWnd,pdsi->uCallbackMessage,(WPARAM)DRAGDROP_S_CANCEL,0);
		return ResultFromScode(DRAGDROP_S_CANCEL);
	}
	
	/* �w��̃L�[��}�E�X�������ꂽ�ꍇ�̓h���b�v�ɂ��� */
	if(pdsi->m_button == 0){
		if(grfKeyState != pdsi->m_keyState){
			SendMessage(pdsi->hWnd,pdsi->uCallbackMessage,(WPARAM)DRAGDROP_S_DROP,0);
			return ResultFromScode(DRAGDROP_S_DROP);
		}
	}else{
		if(!(grfKeyState & pdsi->m_button)){
			SendMessage(pdsi->hWnd,pdsi->uCallbackMessage,(WPARAM)DRAGDROP_S_DROP,0);
			return ResultFromScode(DRAGDROP_S_DROP);
		}
	}
	return S_OK;
}

static HRESULT STDMETHODCALLTYPE OLE_IDropSource_GiveFeedback(LPDROPSOURCE lpThis,DWORD dwEffect)
{
	return ResultFromScode(DRAGDROP_S_USEDEFAULTCURSORS);
}


/* �h���b�O���h���b�v�̊J�n */
int APIPRIVATE OLE_IDropSource_Start(HWND hWnd,UINT uCallbackGetData,UINT uCallbackDropEnd,UINT *ClipFormtList,int cfcnt,int Effect)
{
	static IDATAOBJECT_INTERNAL *pdoi;
	static IDROPSOURCE_INTERNAL *pdsi;
	DWORD lpdwEffect;
	DWORD keyState;
	int i;
	int ret;

	/* IDataObject�̍쐬 */
	pdoi = GlobalAlloc(GPTR,sizeof(IDATAOBJECT_INTERNAL));
	pdoi->lpVtbl = (LPVOID)&dov;
	pdoi->m_refCnt = 0;
	pdoi->m_numTypes = cfcnt;
	pdoi->m_maxTypes = cfcnt;
	/* �L���ȃN���b�v�{�[�h�t�H�[�}�b�g��ݒ肷�� */
	pdoi->m_typeList = GlobalAlloc(GPTR,sizeof(FORMATETC) * cfcnt);
	for(i = 0;i < cfcnt;i++){
		pdoi->m_typeList[i].cfFormat = (CLIPFORMAT)ClipFormtList[i];
		pdoi->m_typeList[i].ptd = NULL;
		pdoi->m_typeList[i].dwAspect = DVASPECT_CONTENT;
		pdoi->m_typeList[i].lindex = -1;
		pdoi->m_typeList[i].tymed = TYMED_HGLOBAL;
	}
	pdoi->hWnd = hWnd;
	pdoi->uCallbackMessage = uCallbackGetData;
	((LPDATAOBJECT)pdoi)->lpVtbl->AddRef((LPDATAOBJECT)pdoi);

	/* IDropSource�̍쐬 */
	pdsi = GlobalAlloc(GPTR,sizeof(IDROPSOURCE_INTERNAL));
	pdsi->lpVtbl = (LPVOID)&dsv;
	pdsi->m_refCnt = 0;
	pdsi->hWnd = hWnd;
	pdsi->uCallbackMessage = uCallbackDropEnd;

	/* �L���ȃL�[�ƃ}�E�X�̏�� */
	if(GetKeyState(VK_RBUTTON) & 0x8000){
		pdsi->m_button = MK_RBUTTON;
	}else{
		pdsi->m_button = MK_LBUTTON;
	}

	/* ���݂̃L�[�ƃ}�E�X�̏�� */
	keyState = 0;
	if(GetKeyState(VK_SHIFT) & 0x8000){
		keyState |= MK_SHIFT;
	}
	if(GetKeyState(VK_CONTROL) & 0x8000){
		keyState |= MK_CONTROL;
	}
	if(GetKeyState(VK_MENU) & 0x8000){
		keyState |= MK_ALT;
	}
	if(GetKeyState(VK_LBUTTON) & 0x8000){
		keyState |= MK_LBUTTON;
	}
	if(GetKeyState(VK_MBUTTON) & 0x8000){
		keyState |= MK_MBUTTON;
	}
	if(GetKeyState(VK_RBUTTON) & 0x8000){
		keyState |= MK_RBUTTON;
	}
	pdsi->m_keyState = keyState;
	((LPDROPSOURCE)pdsi)->lpVtbl->AddRef((LPDROPSOURCE)pdsi);

	lpdwEffect = 0;

	/* �h���b�O&�h���b�v�̊J�n */
	ret = DoDragDrop((LPDATAOBJECT)pdoi,(LPDROPSOURCE)pdsi,Effect,&lpdwEffect);

	/* IDataObject��������� */
	((LPDATAOBJECT)pdoi)->lpVtbl->Release((LPDATAOBJECT)pdoi);
	/* IDropSource��������� */
	((LPDROPSOURCE)pdsi)->lpVtbl->Release((LPDROPSOURCE)pdsi);

	if(ret == DRAGDROP_S_DROP){
		/* �h���b�v��̃A�v���P�[�V�������ݒ肵�����ʂ�Ԃ� */
		return lpdwEffect;
	}else{
		return -1;
	}
}









