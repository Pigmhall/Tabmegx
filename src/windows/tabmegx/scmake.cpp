///////////////////////////////////////
// ショートカット作成コンポーネント
// TSCMake 
// 98/09/24	Ver 1.0
// 99/06/22 Ver 1.1 引数追加
// 作者 yamak yamak@a2.mbn.or.jp
///////////////////////////////////////
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SCMake.h"
#pragma package(smart_init)          

// ユーザー定義
//#include <shlobj.h>

//---------------------------------------------------------------------------
// ValidCtrCheck は作成されたコンポーネントが純粋仮想関数を持たないことを
// 保証するために使用されます。
//

/*static inline void ValidCtrCheck(TSCMake *)
{
	new TSCMake(NULL);
} */
//---------------------------------------------------------------------------
// 初期化
__fastcall TSCMake::TSCMake(TComponent* Owner)
	: TComponent(Owner)
{
	// COM使用のための準備
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
	// COMオブジェクト作成の後始末
	CoUninitialize();
}

////////////////////////
// メソッド
// ショートカット作成
int __fastcall TSCMake::CreateLink()
{
	// エラー値の処理
	if (FSCName == "" || FSCDir == "" || FLinkPath == ""){
		return(-1);
	}

	// ショートカットキーがないとき
	if ((FSCKey & 0x00FF) == 0){
		FSCKey = 0;
	}

	// ここからはほとんどSBORLANDのC++Builder会議室からの引用
	// というかそれもMSのドキュメントからの引用のはず
	// Inside Windows 98年1月号も参考にした
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	// COMオブジェクト作成
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, &(void*)psl);

	if (SUCCEEDED(hres)) {
		// リンク先
		psl->SetPath(FLinkPath.c_str());
		// 作業フォルダ
		psl->SetWorkingDirectory(FWorkDir.c_str());
		// ウインドウ状態
		psl->SetShowCmd(FWndState);
		// ショートカットキー
		psl->SetHotkey(FSCKey);
		// アイコン
		psl->SetIconLocation(FIconPath.c_str(), FIconNo);

		// 99/06/21追加
		// 引数
		psl->SetArguments(FArgument.c_str());

		// ファイル作成用インターフェース取得
		hres = psl->QueryInterface(IID_IPersistFile,&(void*)ppf);
		if (SUCCEEDED(hres)) {
			wchar_t wsz[MAX_PATH];

			// ファイル名を作る
			FileName = FSCDir + "\\" + FSCName + ".lnk";
			FileName.WideChar(wsz, MAX_PATH);

			// ショートカット作成
			hres = ppf->Save(wsz, TRUE);
		}
	}

	return (hres);
}


////////////////////
// ショートカット解析
int __fastcall TSCMake::AnalizeLink(String SCFileName)
{
	// ここからはほとんどSBORLANDのC++Builder会議室からの引用
	// というかそれもMSのドキュメントからの引用のはず
	// Inside Windows 98年1月号も参考にした
	HRESULT hres;
	String FileName;

	IShellLink* psl;
	IPersistFile* ppf;

	// ショートカットでなければやめる
	if (ExtractFileExt(SCFileName) != ".lnk") return(-1);

	// COMオブジェクト作成
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, &(void*)psl);
	if (!SUCCEEDED(hres)) return(-1);

	// ファイル作成用インターフェース取得
	hres = psl->QueryInterface(IID_IPersistFile,&(void*)ppf);
	if (!SUCCEEDED(hres)) return (-1);

	// ファイル名を作る
	wchar_t WFileName[MAX_PATH];
	SCFileName.WideChar(WFileName, MAX_PATH);

	// ショートカット取得
	hres = ppf->Load(WFileName, STGM_READ);
	if (!SUCCEEDED(hres)) return (-1);

	// ショートカットの名前
	FSCName = ChangeFileExt(ExtractFileName(SCFileName), "");

	// ディレクトリ
	FSCDir = ExtractFileDir(SCFileName);

	// リンク先
	WIN32_FIND_DATA Ffblk;
	char str[MAX_PATH + 1];

	psl->GetPath(str, MAX_PATH, &Ffblk, SLGP_UNCPRIORITY);
	FLinkPath = str;

	// 作業フォルダ
	psl->GetWorkingDirectory(str, MAX_PATH);
	FWorkDir = str;

	// ウインドウ状態
	psl->GetShowCmd(&FWndState);
	
	// ショートカットキー
	psl->GetHotkey(&FSCKey);

	// アイコン
	psl->GetIconLocation(str, MAX_PATH, &FIconNo);
	FIconPath = str;

	// 99/06/21追加
	// 引数
	psl->GetArguments(str, MAX_PATH);
	FArgument = str;

	return(0);
}

//////////////////////////////
// プロパティ
///////////////////////////////////
// ショートカットキー
// Inside Windows 98年1月号を参考
void __fastcall TSCMake::SetSCKey(TShortCut SCKey)
{
	TShiftState Shift;
	WORD Key = 0;

	// C++BuilderのTShortCut型を
	// ショートカット作成時に使う形に変更
	ShortCutToKey(SCKey, FSCKey, Shift);

	if (FSCKey == 0) return;

	// 同時に押すキーを決める
	// 列挙型は最初よくわからなかった
	if (Shift.Contains(ssShift)){	// Shiftキー
		Key |= (WORD)HOTKEYF_SHIFT;
	}
	if (Shift.Contains(ssAlt)){	// Altキー
		Key |= (WORD)HOTKEYF_ALT;
	}
	if (Shift.Contains(ssCtrl)){	// Ctrlキー
		Key |= (WORD)HOTKEYF_CONTROL;
	}

	// 文字キーはそのままらしい
	Key <<= 8;
	FSCKey |= Key;
}

TShortCut __fastcall TSCMake::GetSCKey()
{
	TShiftState Shift;
	WORD Key, ScShift;

	// 文字キーはそのままらしい
	Key = (WORD)(FSCKey & 0x00ff);
	ScShift = (WORD)((FSCKey & 0xff00) >> 8);

	// 同時に押すキーを決める
	// 列挙型は最初よくわからなかった
	if (ScShift & HOTKEYF_SHIFT){ // Shiftキー
		Shift << ssShift;
	}
	if (ScShift & HOTKEYF_ALT){ // Altキー
		Shift << ssAlt;
	}
	if (ScShift & HOTKEYF_CONTROL){ // Ctrlキー
		Shift << ssCtrl;
	}

	return ShortCut(Key, Shift);
}

////////////////////////////
// ウィンドウ状態
void __fastcall TSCMake::SetWndState(WNDSTATE WndState)
{
	// 列挙型のプロパティを
	// ショートカット作成時に使う形に変更
	if(WndState == Maximize){	// 最大化
		FWndState = SW_MAXIMIZE;
	}else if(WndState == Minimize){	// 最小化
		FWndState = SW_SHOWMINNOACTIVE;
	}else{	// 標準
		FWndState = SW_SHOW;
	}
}

WNDSTATE __fastcall TSCMake::GetWndState()
{
	// 列挙型のプロパティを
	// ショートカット作成時に使う形に変更
	if(FWndState == SW_MAXIMIZE){	// 最大化
		return Maximize;
	}else if(FWndState == SW_SHOWMINNOACTIVE){	// 最小化
		return Minimize;
	}else{	// 標準
		return Normal;
	}
}




