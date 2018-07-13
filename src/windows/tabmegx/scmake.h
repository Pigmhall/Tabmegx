///////////////////////////////////////
// ショートカット作成コンポーネント
// TSCMake 
// 98/09/24	Ver 1.0
// 99/06/22 Ver 1.1 引数追加
// 作者 yamak yamak@a2.mbn.or.jp
///////////////////////////////////////
//---------------------------------------------------------------------------
#ifndef SCMakeH
#define SCMakeH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
enum		WNDSTATE {Normal, Maximize, Minimize};

class TSCMake : public TComponent
{
private:
	String 	FSCDir;
	String 	FSCName;
	String 	FLinkPath;
	String 	FWorkDir;
	int			FWndState;
	WORD		FSCKey;
	String	FIconPath;
	int			FIconNo;
    String FArgument;

protected:
	WNDSTATE __fastcall GetWndState();
	void __fastcall SetWndState(WNDSTATE WndState);
	TShortCut __fastcall GetSCKey();
	void __fastcall SetSCKey(TShortCut SCKey);

public:
	__fastcall TSCMake(TComponent* Owner);
	__fastcall ~TSCMake();
	int __fastcall CreateLink();
	int __fastcall AnalizeLink(String SCFileName);

__published:
	__property String SCDir = 	{read = FSCDir, 	write = FSCDir};
	__property String SCName = 	{read = FSCName, 	write = FSCName};
	__property String LinkPath = 	{read = FLinkPath,	write = FLinkPath};
	__property String WorkDir = 	{read = FWorkDir, 	write = FWorkDir};
	__property WNDSTATE WndState = 	{read = GetWndState, write = SetWndState, default = Normal};
	__property TShortCut	SCKey	 =	{read = GetSCKey, write = SetSCKey};
	__property String	IconPath	 =	{read = FIconPath, write = FIconPath};
	__property int		IconNo	 =	{read = FIconNo, write = FIconNo};
	// 99/06/22 引数追加
    __property String 	Argument  = { read = FArgument, write = FArgument };

};
//---------------------------------------------------------------------------
#endif
 
