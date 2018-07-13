/****************************************************************************/
/*****	JIS X 0213:2000 ëŒâûäøéöÉRÅ[Éhïœä∑DLL (jis2000.h)				*****/
/*****									Copyright(C)2000 ‰≥âÿ(SAKA)		*****/
/****************************************************************************/

#ifdef JIS2000_EXPORTS
#define JIS2000_API __declspec(dllexport)
#else
#define JIS2000_API __declspec(dllimport)
#endif

#define	JIS2K_ASCII			0x0000
#define	JIS2K_JIS			0x0100
#define	JIS2K_SJIS			0x0200
#define	JIS2K_EUC			0x0400
#define	JIS2K_UNICODE		0x0800
#define	JIS2K_UTF8			0x0801
#define	JIS2K_UTF7			0x0802
#define	JIS2K_NON			0x1000
#define	JIS2K_BINARY		0x2000

#define	JIS2K_KANJI1		0x0001
#define	JIS2K_KANJI2		0x0002
#define	JIS2K_KANJI3		0x0004
#define	JIS2K_KANJI4		0x0008
#define	JIS2K_HIKANJI1		0x0010
#define	JIS2K_HIKANJI3		0x0040
#define JIS2K_XJIS0208		JIS2K_KANJI1 + JIS2K_KANJI2 + JIS2K_HIKANJI1
#define JIS2K_XJIS0213		JIS2K_KANJI3 + JIS2K_KANJI4 + JIS2K_HIKANJI3

extern "C" {
	JIS2000_API int _stdcall GetJis2000Version(void);
	JIS2000_API int _stdcall GetKanjiCodeType(const char *code, const int count);

	JIS2000_API int _stdcall _issjis2000(const unsigned short sjis);
	JIS2000_API int _stdcall _isx0208pullout(const unsigned short sjis);

	JIS2000_API unsigned short _stdcall _getsjis(const unsigned char* sjis, int *nByte);
	JIS2000_API size_t _stdcall _setmbyte(char* buf, const unsigned short code);

	JIS2000_API unsigned short _stdcall _sjis2jis(const unsigned short sjis, int *plane);
	JIS2000_API unsigned short _stdcall _jis2sjis(const unsigned short jis, const int plane);

	JIS2000_API wchar_t _stdcall _sjis2unicode(const unsigned short sjis);
	JIS2000_API unsigned short _stdcall _unicode2sjis(const wchar_t uni);
	JIS2000_API wchar_t _stdcall _utf8toucs2(const unsigned char *utf8, int *nByte);
	JIS2000_API size_t _stdcall _ucs2toutf8(unsigned char *utf8, const wchar_t uni);

	JIS2000_API unsigned short _stdcall _x0212_2sjis(const unsigned short jis);

	JIS2000_API size_t _stdcall SjisToUnicode(wchar_t *unicode, const char* sjis, const size_t count);
	JIS2000_API size_t _stdcall UnicodeToSjis(char *sjis, const wchar_t *unicode, const size_t count);

	JIS2000_API size_t _stdcall _sjis2iso2022jp(char *jis, const char *sjis, const size_t count, int mode);
	JIS2000_API size_t _stdcall SjisToIso2022jp3(char *jis, const char *sjis, const size_t count);
	JIS2000_API size_t _stdcall SjisToIso2022jp3Strict(char *jis, const char *sjis, const size_t count);
	JIS2000_API size_t _stdcall SjisToIso2022jp3Compatible(char *jis, const char *sjis, const size_t count);
	JIS2000_API size_t _stdcall Iso2022jpToSjis(char *sjis, const char *jis, const size_t count);

	JIS2000_API size_t _stdcall SjisToEuc(char *euc, const char *sjis, const size_t count);
	JIS2000_API size_t _stdcall EucToSjis(char *sjis, const char *euc, const size_t count);

	JIS2000_API size_t _stdcall X0201ToX0208Kana(char *zen, const char *han, const size_t count);
	JIS2000_API size_t _stdcall WinsjisToSjis2000(char *sjis, const char *win, const size_t count);

	JIS2000_API size_t _stdcall UnicodeToUTF8(char* utf8, const wchar_t *unicode, const size_t count);
	JIS2000_API size_t _stdcall UTF8ToUnicode(wchar_t *unicode, const char* utf8, const size_t count);

	JIS2000_API size_t _stdcall _utf7encode(char *utf7, const wchar_t *uni, const size_t count, const size_t num);
	JIS2000_API size_t _stdcall _utf7decode(wchar_t *uni, const char *utf7, size_t *num);
	JIS2000_API size_t _stdcall _utf162toutf7(char* utf7, const wchar_t *uni, const size_t count, bool strict);
	JIS2000_API size_t _stdcall UnicodeToUTF7(char* utf7, const wchar_t *unicode, const size_t count);
	JIS2000_API size_t _stdcall UnicodeToUTF7Strict(char* utf7, const wchar_t *unicode, const size_t count);
	JIS2000_API size_t _stdcall UTF7ToUnicode(wchar_t *unicode , const char* utf7, const size_t count);

}

/*****	end of file	*****/