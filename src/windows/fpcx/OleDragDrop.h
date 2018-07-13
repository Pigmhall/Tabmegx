//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//   OLEドラッグ&ドロップをCのみで行うDLL
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
	POINTL *ppt;					//マウスの位置
	DWORD dwEffect;					//ドラッグ操作で、ドラッグされる対象で許される効果
	DWORD grfKeyState;				//キーの状態
	UINT cfFormat;					//ドロップされるデータのクリップボードフォーマット
	HANDLE hMem;					//ドロップされるデータ
	LPVOID pdo;						//IDataObject
}IDROPTARGET_NOTIFY , *LPIDROPTARGET_NOTIFY;

//-----------------------------------------------------------------------------
// ウィンドウをDnDのターゲットとして登録する
// IN  hWnd: DnDターゲットとして登録するウィンドウ
//     uCallbackMessage: DnDが行われたときにウィンドウに送信されるメッセージ
//                   送信されるメッセージのパラメータには以下が設定される
//                   wParam: 操作の種類(IDROPTARGET_NOTIFY_MSG)
//                   lParam: IDROPTARGET_NOTIFY構造体へのポインタ
//     cFormat: 受け取ることが可能なクリップボードフォーマットのリスト
//     cfcnt: クリップボードフォーマットの配列の要素数
// OUT ret:登録に成功したか
//-----------------------------------------------------------------------------
DLLEXPORT BOOL _stdcall OLE_IDropTarget_RegisterDragDrop(HWND hWnd,UINT uCallbackMessage,UINT* cFormat,int cfcnt);

//-----------------------------------------------------------------------------
// DnDのターゲットを解除する
// IN  hWnd: DnDターゲットとして登録しているウィンドウ
//-----------------------------------------------------------------------------
DLLEXPORT void _stdcall OLE_IDropTarget_RevokeDragDrop(HWND hWnd);


//-----------------------------------------------------------------------------
// DnDを開始する
// IN  hWnd: 以下のデータ要求・DnD終了メッセージを受け取るウィンドウ
//     uCallbackGetData: DnDするデータが必要なときにウィンドウに送信されるメッセージ
//                   送信されるメッセージのパラメータには以下が設定される
//                   wParam: 要求されるクリップボードフォーマットの配列
//                   lParam: データを格納するHANDLEへのポインタ
//                           *(HANDLE*)lParam にデータを設定して返す(NULLでも可)
//     uCallbackDropEnd: DnDが終了したときにウィンドウに送信されるメッセージ
//                   送信されるメッセージのパラメータには以下が設定される
//                   wParam: ドロップ操作が発生した場合はDRAGDROP_S_DROP
//                           キャンセルされたらDRAGDROP_S_CANCEL
//                   lParam: 0
//     ClipFormtList: サポートしているクリップボードフォーマットの配列
//     cfcnt: クリップボードフォーマットの配列の要素数
//     Effect: ドラッグ操作でドラッグされる対象で許される効果の組み合わせ
// OUT ret: ドロップ先のアプリケーションが設定した効果(Cancel/Error時は-1)
//-----------------------------------------------------------------------------
DLLEXPORT int _stdcall OLE_IDropSource_Start(HWND hWnd,UINT uCallbackGetData,UINT uCallbackDropEnd,UINT *ClipFormtList,int cfcnt,int Effect);


//-----------------------------------------------------------------------------
// ドロップファイルの作成
// IN  FileName:ファイル名の配列, cnt:ファイル数
// OUT ret:ドロップファイル構造体(HDROP)
//-----------------------------------------------------------------------------
DLLEXPORT HDROP _stdcall CreateDropFileMem(char** FileName,int cnt);


//-----------------------------------------------------------------------------
// ドロップファイル構造体からフルパスファイル名リスト(xxx\0yyy\0\0の形式)を作成
// IN   filelist:ファイル名リストの格納先, bufsize:filelistのサイズ
// OUT  ret:ドロップされたファイル数
//-----------------------------------------------------------------------------
DLLEXPORT int _stdcall GetDropFileList(HDROP hDrop,char* filelist,int bufsize);


#ifdef __cplusplus
}
#endif

#endif
