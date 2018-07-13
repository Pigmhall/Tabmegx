//----------------------------------------------------------------------------
// BRegExp.hpp - bcbdcc32 generated hdr (DO NOT EDIT) rev: 0
// From: BRegExp.pas
//----------------------------------------------------------------------------
#ifndef BRegExpHPP
#define BRegExpHPP
//----------------------------------------------------------------------------
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <System.hpp>
namespace Bregexp
{
//-- type declarations -------------------------------------------------------
typedef char * *PPChar;

#pragma pack(push, 1)
struct TBRegExpRec
{
	char *outp;
	char *outendp;
	int splitctr;
	char * *splitp;
	int rsv1;
	char *parap;
	char *paraendp;
	char *transtblp;
	char * *startp;
	char * *endp;
	int nparens;
} ;
#pragma pack(pop)

typedef TBRegExpRec *pTBRegExpRec;

class __declspec(delphiclass) EBRegExpError;
class __declspec(pascalimplementation) EBRegExpError : public Sysutils::Exception
{
	typedef Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ __fastcall EBRegExpError(const System::AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	/* Exception.CreateFmt */ __fastcall EBRegExpError(const System::AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ __fastcall EBRegExpError(int Ident) : Sysutils::Exception(Ident) { }
	/* Exception.CreateResFmt */ __fastcall EBRegExpError(int Ident, const System::TVarRec * Args, const 
		int Args_Size) : Sysutils::Exception(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ __fastcall EBRegExpError(const System::AnsiString Msg, int AHelpContext)
		 : Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ __fastcall EBRegExpError(const System::AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	/* Exception.CreateResHelp */ __fastcall EBRegExpError(int Ident, int AHelpContext) : Sysutils::Exception(
		Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ __fastcall EBRegExpError(int Ident, const System::TVarRec * Args, 
		const int Args_Size, int AHelpContext) : Sysutils::Exception(Ident, Args, Args_Size, AHelpContext)
		 { }
	
public:
	/* TObject.Destroy */ __fastcall virtual ~EBRegExpError(void) { }
	
};

enum TBRegExpMode { brxNone, brxMatch, brxSplit };

class __declspec(delphiclass) TBRegExp;
class __declspec(pascalimplementation) TBRegExp : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TBRegExpMode Mode;
	char *pTargetString;
	TBRegExpRec *pBRegExp;
	int __fastcall GetMatchPos(void);
	int __fastcall GetMatchLength(void);
	int __fastcall GetSplitCount(void);
	System::AnsiString __fastcall GetMatchStrings(int index);
	int __fastcall GetMatchCount(void);
	int __fastcall GetCount(void);
	System::AnsiString __fastcall GetStrings(int index);
	System::AnsiString __fastcall GetSplitStrings(int index);
	System::AnsiString __fastcall GetLastCommand(void);
	void __fastcall CheckCommand(const System::AnsiString Command);
	
public:
	__fastcall virtual ~TBRegExp(void);
	bool __fastcall Match(const System::AnsiString Command, const System::AnsiString TargetString);
	bool __fastcall Subst(const System::AnsiString Command,  System::AnsiString &TargetString);
	bool __fastcall Split(const System::AnsiString Command, const System::AnsiString TargetString, int 
		Limit);
	bool __fastcall Trans(const System::AnsiString Command,  System::AnsiString &TargetString);
	__property System::AnsiString LastCommand = {read=GetLastCommand, nodefault};
	__property int MatchPos = {read=GetMatchPos, nodefault};
	__property int MatchLength = {read=GetMatchLength, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property System::AnsiString Strings[int index] = {read=GetStrings/*, default*/};
public:
	/* TObject.Create */ __fastcall TBRegExp(void) : System::TObject() { }
	
};

//-- var, const, procedure ---------------------------------------------------
#define BREGEXP_ERROR_MAX (Byte)(80)
extern bool __cdecl (*BMatch)(char * str, char * target, char * targetendp, pTBRegExpRec &rxp, char * 
	msg);
extern bool __cdecl (*BSubst)(char * str, char * target, char * targetendp, pTBRegExpRec &rxp, char * 
	msg);
extern bool __cdecl (*BTrans)(char * str, char * target, char * targetendp, pTBRegExpRec &rxp, char * 
	msg);
extern bool __cdecl (*BSplit)(char * str, char * target, char * targetendp, int limit, pTBRegExpRec 
	&rxp, char * msg);
extern void __cdecl (*BRegFree)(pTBRegExpRec rx);
extern char * __cdecl (*BRegExpVersion)(void);
extern int hDLL;
extern TBRegExp* __fastcall brx(void);
extern void __fastcall finalization(void);

}	/* namespace Bregexp */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Bregexp;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// BRegExp
