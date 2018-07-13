/****************************************************************************/
/*****	JIS X 0213:2000 ëŒâûäøéöÉRÅ[Éhïœä∑DLL (jis2000.cpp)				*****/
/*****								Copyright(C)2000-2001 ‰≥âÿ(SAKA)	*****/
/****************************************************************************/
#include <windows.h>
#include "resource.h"

#include "jis2001.h"
#include "code_table.h"

/****************************************************************************/
#define	VER		122			// Version 1.22

#define	CR		0x0d
#define	LF		0x0a
#define	ESC		0x1b
#define	SP		0x20
#define	DEL		0x7f
#define	SI		0x0f
#define	SO		0x0e
#define	SS2		0x8e
#define	SS3		0x8f

#define	_isx0201kana(cc)	(0xa1 <= (cc) && (cc) <= 0xdf)
#define	_is_unikana(cc)		(0xff61 <= (cc) && (cc) <= 0xff9f)
#define	_isleadbyte(cc)		((0x81 <= (cc) && (cc) <= 0x9f) || (0xe0 <= (cc) && (cc) <= 0xfc))
#define _istailbyte(cc)		((0x40 <= (cc) && (cc) <= 0x7e) || (0x80 <= (cc) && (cc) <= 0xfc))
#define _sjis2table(cc, st)	((((cc) & 0xff00) >> 8) - (st))*94*2 +((cc) & 0x00ff) - ((((cc) & 0x00ff) <= 0x7e) ? 0x40 : 0x41)


/****************************************************************************/
JIS2000_API int _stdcall GetJis2000Version()
{
	return VER;
}

JIS2000_API int _stdcall GetKanjiCodeType(const char *code, const int count)
{
	int i, jis, jflg, uni, uflg, utf8, u8flg, sjis, sflg, euc, eflg, exe,
		utf7, u7flg, ascii;
	if (count < 2) return JIS2K_NON;
	jis = jflg = uni = uflg = utf8 = u8flg = sjis = sflg =
		u7flg = euc = eflg = exe = 0;
	ascii = utf7 = 1;
	for (i=0; i < (count-1); i++) {
		if (!(i&0x1) && *code==0 && *(code+1)==0)	return JIS2K_BINARY;
		if (*code == 0)   exe   = 1;
		if (*code > 0x80) ascii = 0; 
		if (!(i&0x1) && (*code==CR || *code==LF) && *(code+1)==0)
			uni++;
		else if (i&0x1 &&
			0xa0<=(unsigned char)*code && (unsigned char)*code<=0xf7)
			uflg = 1;
		if (!exe && ascii) {
			if (utf7 && !u7flg && *code == '+')
				u7flg = 1;
			else if (utf7 && u7flg && *code == '-')
				u7flg = 0;
			else if (utf7 && u7flg)
				utf7 = (base64decode[*code] != -1)? 1 : 0;
		}
		if (!exe) {
			if (!jflg && *code == ESC && *(code+1) == '$' &&
				((*(code+2)=='@' || *(code+2)=='B') ||
				 (*(code+2)=='(' && (*(code+3)=='O' || *(code+3)=='P')) ))
				jis++;
			else if (!jflg && *code > DEL)
				jflg = 1;
			else if (!u8flg &&
				((unsigned char)* code    & 0xc0) == 0xc0 &&
				((unsigned char)*(code+1) & 0xc0) == 0x80 &&
				((unsigned char)*(code+2) & 0xc0) == 0x80) {
				utf8++;
				u8flg = 2;
			}
			else if (u8flg) u8flg--;
			else if (!sflg &&
				_isleadbyte((unsigned char)*code) &&
				_istailbyte((unsigned char)*(code+1)) ) {
				sjis++;
				sflg = 1;
			}
			else if (sflg) sflg = 0;
			else if (!eflg &&
				0xa1<=(unsigned char)*code     && (unsigned char)*code<=0xfe &&
				0xa1<=(unsigned char)*(code+1) && (unsigned char)*(code+1)<=0xfe) {
				euc++;
				eflg = 1;
			}
			else if (eflg) eflg = 0;
		}
		code++;
	}
	if (uni && !uflg)						return JIS2K_UNICODE;
	if (exe)								return JIS2K_BINARY;
	if (jis && !jflg)						return JIS2K_JIS;
	else if (utf8 > sjis && utf8 > euc )	return JIS2K_UTF8;
	else if (sjis > euc  && sjis > utf8)	return JIS2K_SJIS;
	else if (euc  > sjis && euc  > utf8)	return JIS2K_EUC;
	else if (!sjis && !euc && !utf8) {
		if (utf7)							return JIS2K_UTF7;
		else								return JIS2K_ASCII;
	}
	return	JIS2K_NON;
}

/****************************************************************************/
JIS2000_API int _stdcall _issjis2000(const unsigned short sjis)
{
	unsigned short hic, loc;
	hic = (sjis & 0xff00) >> 8;
	loc = (sjis & 0x00ff);
	if ( _isleadbyte(hic) && _istailbyte(loc)) {
		if 		(0x889f <= sjis && sjis <= 0x9872)		return JIS2K_KANJI1;
		else if (0x989f <= sjis && sjis <= 0xeaa4)		return JIS2K_KANJI2;
		else if((0x87a0 <= sjis && sjis <= 0x889d) ||
				(0x9874 <= sjis && sjis <= 0x989d) ||
				(0xeaa6 <= sjis && sjis <= 0xeff7))		return JIS2K_KANJI3;
		else if (0xf040 <= sjis && sjis <= 0xfcf4)		return JIS2K_KANJI4;
		else if (0x8140 <= sjis && sjis <= 0x879e){
			return tb_hikanji[ _sjis2table(sjis, 0x81) ];
		}
		else JIS2K_NON;
	}
	return JIS2K_ASCII;
}

JIS2000_API int _stdcall _isx0208pullout(const unsigned short sjis)
{
	int i;
	if (sjis < 0x889f) return 0;
	for (i = 0; i < sizeof(tb_pullout)/sizeof(tb_pullout[0]); i++) {
		if (sjis == tb_pullout[i]) return 1;
	}
	return 0;
}

JIS2000_API unsigned short _stdcall _getsjis(const unsigned char* sjis, int *nByte)
{
	unsigned short cc;
	if (_isx0201kana(*sjis)) {
		*nByte = 2;
		if		(*(sjis+1) == 0xde) cc = tb_kba[*sjis-0xa1];
		else if (*(sjis+1) == 0xdf) cc = tb_kpa[*sjis-0xa1];
		else						cc = 0;
		if (cc == 0) {
			*nByte = 1;
			cc = tb_kha[*sjis-0xa1];
		}
		return cc;
	}
	else if (_isleadbyte(*sjis)) {
		*nByte = 2;
		return (*sjis << 8) | *(sjis+1);
	}
	*nByte = 1;
	return *sjis;
}

JIS2000_API size_t _stdcall _setmbyte(char* buf, const unsigned short code)
{
	if (buf) {
		if (code >= 0x0100) *(buf++) = (code & 0xff00) >> 8;
		*buf = (code) ? code & 0x00ff : 0x3f;
	}
	return (code < 0x0100) ? 1 : 2;
}

JIS2000_API unsigned short _stdcall _sjis2jis(const unsigned short sjis, int *plane)
{
static unsigned short table[][2] = {
	{0x81, 0x84}, {0x82, 0x82}, {0x83, 0x86},
	{0x87, 0x87}, {0x88, 0xe7} };
	unsigned short hic, loc;
	hic = (sjis & 0xff00) >> 8;
	loc = (sjis & 0x00ff);
	/* JIS X 0213:2000 */
	if (plane) *plane = (0xf0 <= hic) ? 2 : 1;
	if (0xf0 <= hic && hic <= 0xf4)
		hic = table[hic - 0xf0][(loc <= 0x9e) ? 0 : 1];
	else if (hic >= 0xf5) hic -= 0xd;
	/* sjis -> jis */
	hic -= (hic <= 0x9f) ? 0x71 : 0xb1;
	hic  = (hic << 1) + 1;
	if (loc > 0x9e) hic++;
	if (loc > 0x7f) loc--;
	loc -= (loc >= 0x9e) ? 0x7d : 0x1f;
	return (hic << 8) | loc;
}

JIS2000_API unsigned short _stdcall _jis2sjis(const unsigned short jis, int plane)
{
	unsigned short hic, loc;
	hic = (jis & 0xff00) >> 8;
	loc = (jis & 0x00ff);
	/* JIS X 0213:2000 */
	if (plane == 2) {
		if		(hic == 0x21 || (0x23 <= hic && hic <= 0x25))
			hic += 0x5e;
		else if (hic == 0x28 || (0x2c <= hic && hic <= 0x2f))
			hic += 0x58;
		else if (hic >= 0x6e)
			hic += 0x1a;
		else return 0;
	}
	/* jis -> sjis */
	loc += (hic & 0x01) ? 0x1f : 0x7d;
	if (loc >= 0x7f) loc++;
	hic = ((hic - 0x21) >> 1) + 0x81;
	if (hic > 0x9f) hic += 0x40;
    return (hic << 8) | loc;
}

JIS2000_API wchar_t _stdcall _sjis2unicode(const unsigned short sjis)
{
	unsigned short wc, hic, loc;
	hic = (sjis & 0xff00) >> 8;
	loc = (sjis & 0x00ff);
	if (sjis <= DEL){
		return sjis;
	}
	else if (_isx0201kana(sjis)) {
		return 0xff61 + sjis - 0x00a1;
	}
	else if (_isleadbyte(hic) && _istailbyte(loc)) {
		hic -= (hic <= 0x9f) ? 0x81 : 0xc1;
		loc -= (loc <= 0x7e) ? 0x40 : 0x41;
		wc = UnicodeTable[(hic * 94 * 2) + loc];
		return (wc == 0x0000) ? 0x3013 : wc;
	}
	return 0x0000;
}

JIS2000_API unsigned short _stdcall _unicode2sjis(const wchar_t uni)
{
	unsigned short hic, loc;
	hic = (uni & 0xff00) >> 8;
	loc = (uni & 0x00ff);
	const unsigned short *table = map_sjis2000[hic];
	if (table != 0x0000) return table[loc];
	return 0x0000;
}

JIS2000_API wchar_t _stdcall _utf8toucs2(const unsigned char *utf8, int *nByte)
{
	int n;
	unsigned short cc = 0;
	if		((*utf8 & 0xfc) == 0xfc) n = 6;
	else if ((*utf8 & 0xf8) == 0xf8) n = 5;
	else if ((*utf8 & 0xf0) == 0xf0) n = 4;
	else if ((*utf8 & 0xe0) == 0xe0) n = 3;
	else if ((*utf8 & 0xc0) == 0xc0) n = 2;
	else 							 n = 1;

	if (nByte) *nByte = n;
	if		(n >  3) return 0xffff;
	else if (n == 3) cc += (*(utf8++) & 0x0f) << 12;
	if		(n >  2) cc += (*(utf8++) & 0x3f) << 6;
	else if (n == 2) cc += (*(utf8++) & 0x1f) << 6;
	if		(n >  1) cc += *utf8++ & 0x3f;
	else if (n == 1) cc  = *utf8;
	return cc;
}

JIS2000_API size_t _stdcall _ucs2toutf8(unsigned char *utf8, const wchar_t uni)
{
	int nn = 1;
	if (0x80  <= uni) nn++;
	if (0x800 <= uni) nn++;

	if		(nn == 3) *(utf8++) = ((uni >> 12) & 0x0f) | 0xe0;
	if		(nn >  2) *(utf8++) = ((uni >> 6)  & 0x3f) | 0x80;
	else if	(nn == 2) *(utf8++) = ((uni >> 6)  & 0x1f) | 0xc0;
	if		(nn >  1) *(utf8++) = (uni & 0x3f) | 0x80;
	else if	(nn == 1) *(utf8++) = (char)uni;
	*utf8 = 0;
	return nn;
}

JIS2000_API unsigned short _stdcall _x0212_2sjis(const unsigned short jis)
{
	if (0x3121 <= jis && jis <= 0x6d7e)
		return tb_x0212_sjis[
			(((jis & 0xff00) >> 8) - 0x31) * 94 + ((jis & 0x00ff) - 0x21) ];
	return 0x0000;
}

/****************************************************************************/
JIS2000_API size_t _stdcall SjisToUnicode(wchar_t *unicode, const char* sjis, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = _getsjis((unsigned char*)sjis, &n)) {
		sjis += n;
		size++;
		if (unicode && count <= size) break;
		if (unicode) *(unicode++) = _sjis2unicode(cc);
	}
	if (unicode && count >= size) *unicode = '\0';
	return (!unicode || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall UnicodeToSjis(char *sjis, const wchar_t *unicode, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	while(cc = *(unicode++)) {
		cc = _unicode2sjis(cc);
		size += (cc < 0x8140) ? 1 : 2;
		if (sjis && count <= size) break;
		if (sjis) sjis += _setmbyte(sjis, cc);
	}
	if (sjis && count >= size) *sjis = '\0';
	return (!sjis || count > size) ? size : -1;
}

/****************************************************************************/
#define	JIS_ASCII			0x0000
#define	JIS_0201			0x0001
#define	JIS_KANA			0x0002
#define	JIS_MEN1			0x0003
#define	JIS_MEN2			0x0004
#define	JIS_0208			0x0005
#define	JIS_0212			0x0006

JIS2000_API size_t _stdcall _sjis2iso2022jp(char *jis, const char *sjis, const size_t count, int mode)
{
	unsigned short cc;
	size_t size = 0;
	int n, m, flag = JIS_ASCII;
	while(cc = _getsjis((unsigned char*)sjis, &n)) {
		sjis += n;
		if (cc >= 0x8140) {
			m = (mode == 0) ? 0 : _issjis2000(cc) & JIS2K_XJIS0208;
			if  (mode == 1 && m) m = !_isx0208pullout(cc);
			cc = _sjis2jis(cc, &n);
			if ((n == 1 && flag != JIS_MEN1 && !m) ||
				(n == 2 && flag != JIS_MEN2 && !m) ||
				(n == 1 && flag != JIS_0208 &&  m)) {
				if (!m)	flag = (n == 1) ? JIS_MEN1 : JIS_MEN2;
				else	flag = JIS_0208;
				size += (!m) ? 4 : 3;
				if (jis && count <= size) break;
				if (jis) {
					*(jis++) = ESC;
					*(jis++) = '$';
					*(jis++) = (!m) ? '(' : 'B';
					if (!m) *(jis++) = (n == 1) ? 'O' : 'P';
				}
			}
		}
		else if (cc <= DEL && flag != JIS_ASCII) {
			flag  = JIS_ASCII;
			size += 3;
			if (jis && count <= size) break;
			if (jis) {
				*(jis++) = ESC;
				*(jis++) = '(';
				*(jis++) = 'B';
			}
		}
		size += (cc < 0x2121) ? 1 : 2;
		if (jis && count <= size) break;
		if (jis) jis += _setmbyte(jis, cc);
	}
	if (jis && count >= size) *jis = '\0';
	return (!jis || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall SjisToIso2022jp3(char *jis, const char *sjis, const size_t count)
{
	return _sjis2iso2022jp(jis, sjis, count, 0);
}

JIS2000_API size_t _stdcall SjisToIso2022jp3Strict(char *jis, const char *sjis, const size_t count)
{
	return _sjis2iso2022jp(jis, sjis, count, 1);
}

JIS2000_API size_t _stdcall SjisToIso2022jp3Compatible(char *jis, const char *sjis, const size_t count)
{
	return _sjis2iso2022jp(jis, sjis, count, 2);
}

JIS2000_API size_t _stdcall Iso2022jpToSjis(char *sjis, const char *jis, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int flag = JIS_ASCII;
	while(cc = *(jis++)) {
		if (cc == ESC && *(jis) == '$' && *(jis+1) == '(' &&
			(*(jis+2) == 'O' || *(jis+2) == 'P')) {
			flag = (*(jis+2) == 'O') ? JIS_MEN1 : JIS_MEN2;
			jis += 3;
		}
		else if (cc == ESC && *(jis) == '$' && *(jis+1) == '(' && *(jis+2) == 'D') {
			flag = JIS_0212;
			jis += 3;
		}
		else if (cc == ESC && *(jis)=='$' && (*(jis+1)=='@' || *(jis+1)=='B')) {
			flag = JIS_0208;
			jis += 2;
		}
		else if (cc == ESC && *(jis)=='(' && *(jis+1)=='B' ) {
			flag = JIS_ASCII;
			jis += 2;
		}
		else if ((cc == ESC && *(jis)=='(' && *(jis+1)=='J' ) ||
			(flag == JIS_KANA && cc == SI)) {
			flag = JIS_0201;
			if (cc == ESC) jis += 2;
		}
		else if ((cc == ESC && *(jis)=='(' && *(jis+1)=='I' ) ||
			(flag == JIS_0201 && cc == SO)) {
			flag = JIS_KANA;
			if (cc == ESC) jis += 2;
		}
		else {
			if (cc == ESC && flag == JIS_ASCII)
				flag = JIS_ASCII;
			if (SP < cc && cc < DEL) {
				if (flag == JIS_KANA)
					cc |= 0x80; 
				else if (flag == JIS_0208 || flag == JIS_MEN1 || flag == JIS_MEN2)
					cc = _jis2sjis((cc<<8)+*(jis++), (flag == JIS_MEN2) ? 2 : 1);
				else if (flag == JIS_0212)
					cc = _x0212_2sjis((cc<<8)+*(jis++));
			}
			size += (cc < 0x8140) ? 1 : 2;
			if (sjis && count <= size) break;
			if (sjis) sjis += _setmbyte(sjis, cc);
		}
	}
	if (sjis && count >= size) *sjis = '\0';
	return (!sjis || count > size) ? size : -1;
}

/****************************************************************************/
JIS2000_API size_t _stdcall SjisToEuc(char *euc, const char *sjis, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = _getsjis((unsigned char*)sjis, &n)) {
		sjis += n;
		if (cc >= 0x8140) {
			cc = _sjis2jis(cc, &n) | 0x8080;
			if (n == 2 && count <= ++size && euc) break;
			else if (n == 2 && euc) *(euc++) = (unsigned char)SS3;
		}
		size += (cc < 0xa1a1) ? 1 : 2;
		if (euc && count <= size) break;
		if (euc) euc += _setmbyte(euc, cc);
	}
	if (euc && count >= size) *euc = '\0';
	return (!euc || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall EucToSjis(char *sjis, const char *euc, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = (unsigned char)*(euc++)) {
		if (cc == SS3 || cc >= 0xa1/*kanji*/) {
			n = 1;
			if (cc == SS3) {
				cc = (unsigned char)*(euc++);
				n = 2;
			}
			if (n == 2 && 0xb1 <= cc && cc <= 0xed)
				cc = _x0212_2sjis(((cc&0x7f)<<8)+(*(euc++)&0x7f));
			else
				cc = _jis2sjis(((cc&0x7f)<<8)+(*(euc++)&0x7f), n);
		}
		else if (cc == SS2) cc = *(euc++) | 0x80;

		size += (cc < 0x8140) ? 1 : 2;
		if (sjis && count <= size) break;
		if (sjis) sjis += _setmbyte(sjis, cc);
	}

	if (sjis && count >= size) *sjis = '\0';
	return (!sjis || count > size) ? size : -1;
}

/****************************************************************************/
JIS2000_API size_t _stdcall X0201ToX0208Kana(char *zen, const char *han, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = _getsjis((unsigned char*)han, &n)) {
		han += n;
		size += (cc < 0x8140) ? 1 : 2;
		if (zen && count <= size) break;
		else if (zen) zen += _setmbyte(zen, cc);
	}
	if (zen && count >= size) *zen = '\0';
	return (!zen || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall WinsjisToSjis2000(char *sjis, const char *win, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = _getsjis((unsigned char*)win, &n)) {
		win += n;
		if		(0x8790 <= cc && cc <= 0x879c)
			cc = tb_sjis_win[cc - 0x8790];
		else if (0xed40 <= cc && cc <= 0xeefc)
			cc = tb_sjis_nec[_sjis2table(cc, 0xed)];
		else if (0xfa40 <= cc && cc <= 0xfa4b)
			cc = tb_sjis_ibm[_sjis2table(cc, 0xfa)];

		size += (cc < 0x8140) ? 1 : 2;
		if (sjis && count <= size) break;
		if (sjis) sjis += _setmbyte(sjis, cc);
	}
	if (sjis && count >= size) *sjis = '\0';
	return (!sjis || count > size) ? size : -1;
}

/****************************************************************************/
JIS2000_API size_t _stdcall UnicodeToUTF8(char* utf8, const wchar_t *unicode, const size_t count)
{
	unsigned short cc;
	unsigned char buf[7];
	size_t size = 0;
	int i, n;
	while(cc = *(unicode++)) {
		size += (n = _ucs2toutf8(buf, cc));
		if (utf8 && count <= size) break;
		if (utf8) {
			for (i = 0; i < n; i++)
				*(utf8++) = buf[i];
		}
	}
	if (utf8 && count >= size) *utf8 = '\0';
	return (!utf8 || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall UTF8ToUnicode(wchar_t *unicode, const char* utf8, const size_t count)
{
	unsigned short cc;
	size_t size = 0;
	int n;
	while(cc = _utf8toucs2((unsigned char*)utf8, &n)) {
		utf8 += n;
		if (n > 3) cc = 0x003f;	/* UCS-4 0x10000 - 0x7fffffff */
		size++;
		if (unicode && count <= size) break;
		if (unicode) *(unicode++) = cc;
	}
	if (unicode && count >= size) *unicode = '\0';
	return (!unicode || count > size) ? size : -1;
}

/****************************************************************************/
JIS2000_API size_t _stdcall _utf7encode(char *utf7, const wchar_t *uni, const size_t count, const int num)
{
	size_t size = 1;
	if (utf7 && count <= size) return -1;
	if (utf7) *(utf7++) = '+';
	char cc;
	wchar_t c1, c2, c3;
	int n  = num / 3;
	for (int i = 0; i <= n; i++) {
		if (i == n) {
			if (num % 3 == 0) break;
			c1 = *uni;
			c2 = (num % 3 == 2)? *(uni+1) : '\0';
			c3 = '\0';
		}
		else {
			c1 = *uni;
			c2 = *(uni+1);
			c3 = *(uni+2);
		}
		for (int t = 0; t <= 7; t++) {
			if (i==n && ((t==3 && num%3==1)||(t==6 && num%3==2)))	break;
			switch (t) {
			case 0 : cc = (char)(  c1 >> 10 );						break;
			case 1 : cc = (char)( (c1 >> 4) & 0x3f);				break;
			case 2 : cc = (char)(((c1 << 2) + (c2 >> 14)) & 0x3f);	break;
			case 3 : cc = (char)( (c2 >> 8) & 0x3f);				break;
			case 4 : cc = (char)( (c2 >> 2) & 0x3f);				break;
			case 5 : cc = (char)(((c2 << 4) + (c3 >> 12)) & 0x3f);	break;
			case 6 : cc = (char)( (c3 >> 6) & 0x3f);				break;
			case 7 : cc = (char)(  c3 & 0x3f );						break;
			}
			size++;
			if (utf7 && count <= size) break;
			if (utf7) *(utf7++) = base64encode[cc];
		}
		if (utf7 && count <= size) break;
		uni += 3;
	}
	size++;
	if (utf7 && count > size) {
		*(utf7++) = '-';
		*utf7 = '\0';
	}
	return (!utf7 || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall _utf16toutf7(char* utf7, const wchar_t *unicode, const size_t count, bool strict)
{
	unsigned short cc;
	size_t size = 0;
	int i, n;
	wchar_t *s;
	bool flg = false;
	while(cc = *(unicode++)) {
		i = (cc < 0x0080) ? utf7code[cc] : 0;
		if (flg && (i == 1 || (i == 2 && !strict))) {
			if ((n = _utf7encode(utf7, s, count-size, (int)(unicode-s-1))) == -1) {
				size = count + 1;
				break;
			}
			size += n;
			if (utf7) utf7 += n;
			flg = false;
		}
		else if (!flg && (i == 0 || (i == 2 && strict))) {
			s = (wchar_t *)(unicode-1);
			flg = true;
		}
		if (!flg && (i == 1 || (i == 2 && !strict))) {
			size++;
			if (utf7) {
				if (count <= size) break;
				*(utf7++) = (char)cc;
			}
		}
		else if (!flg && i == 3) {
			size += 2;
			if (utf7) {
				if (count <= size) break;
				*(utf7++) = '+';
				*(utf7++) = '-';
			}
		}
	}
	if (utf7 && count >= size) *utf7 = '\0';
	return (!utf7 || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall UnicodeToUTF7(char* utf7, const wchar_t *unicode, const size_t count)
{
	return _utf16toutf7(utf7, unicode, count, false);
}

JIS2000_API size_t _stdcall UnicodeToUTF7Strict(char* utf7, const wchar_t *unicode, const size_t count)
{
	return _utf16toutf7(utf7, unicode, count, true);
}

/****************************************************************************/
JIS2000_API size_t _stdcall _utf7decode(wchar_t *uni, const char *utf7, const size_t count, size_t *num)
{
	if (*(utf7++) != '+') {
		if (uni) *uni = '\0';
		if (num) *num = 0;
		return 0;
	}
	if (*utf7 == '-') {
		if (uni) *(uni++) = '+';
		if (uni) *uni = '\0';
		if (num) *num = 2;
		return 1;
	}
	if (num) *num = 1;
	size_t size = 0;
	int t = 0;
	char c6[2];
	unsigned char cc;
	wchar_t wc;
	bool flg = false;
	while (-1) {
		if (*utf7 == '-') {
			if (num) (*num)++;
			break;
		}
		c6[0] = base64decode[ *(utf7++) ];
		c6[1] = base64decode[ *utf7 ];
		if (c6[0] == -1) break;
		if (c6[1] == -1) c6[1] = '\0';
		switch (t) {
		case 0 : cc = (c6[0] << 2) + (c6[1] >> 4);	break;
		case 1 : cc = (c6[0] << 4) + (c6[1] >> 2);	break;
		case 2 : cc = (c6[0] << 6) +  c6[1];		break;
		}
		if (t < 3 && !flg) {
			flg = true;
			wc = cc << 8;
		}
		else if (t < 3 && flg) {
			flg = false;
			size++;
			if (uni && count <= size) break;
			if (uni) *(uni++) = wc + cc;
		}
		if (num) (*num)++;
		if (t++ == 3) t = 0; 
	}
	if (uni && count >= size) *uni = '\0';
	return (!uni || count > size) ? size : -1;
}

JIS2000_API size_t _stdcall UTF7ToUnicode(wchar_t *unicode , const char* utf7, const size_t count)
{
	unsigned short cc;
	size_t nn, size = 0;
	int n;
	while(cc = *(utf7++)) {
		if (cc == '+') {
			utf7--;
			if ((n = _utf7decode(unicode, utf7, count-size, &nn)) == -1) {
				size = count + 1;
				break;
			}
			size += n;
			if (unicode) unicode += n;
			utf7 += nn;
		}
		else if (cc < 0x80 && utf7code[cc] >= 1) {
			size++;
			if (unicode && count <= size) break;
			if (unicode) *(unicode++) = cc;
		}
		else { // error
			return -1;
		}
	}
	if (unicode && count > size) *unicode = '\0';
	return (!unicode || count > size) ? size : -1;
}

/*****	end of file	*****/