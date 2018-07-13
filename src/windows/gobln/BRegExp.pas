unit BRegExp;

//=====================================================================
// BRegExp.pas : Borland Delphi �p BREGEXP.DLL ���p���j�b�g
//               1998/10/03��      osamu@big.or.jp
//
// BREGEXP.DLL �́Ahttp://www.hi-ho.or.jp/~babaq/ �ɂČ��J����Ă���
// Perl5�݊��̐��K�\���G���W�� BREGEXP.DLL �� Borland Delphi ���痘�p
// ���邽�߂̃��j�b�g�t�@�C���ł��BDelphi 3 �ō쐬���܂������A32bit
// �ł� Delphi ����� C++ Builder �œ���\�Ǝv���܂��B
//
// BREGEXP.DLL �̗��p�����Ȃǂ́A���z�[���y�[�W�����Q�Ɖ������B�L�p��
// ���C�u�����𖳏��Œ񋟉������Ă��� babaq ����Ɋ��ӂ���ƂƂ��ɁA
// ����̂���������҂��Ă��܂��B
//
// �{���j�b�g�̒��쌠�ɂ��ẮA�Ƃ₩����������͂���܂���B�D����
// �悤�ɂ��g���������B�������A���p�ɓ������Ă͂������̐ӔC�̉��ɂ���
// �����܂��B�{���j�b�g�Ɋւ��� osamu@big.or.jp �͉���ӔC�𕉂����Ƃ�
// �������̂Ƃ��܂��B
//
// �{���j�b�g�́A DLL �ƂƂ��ɔz�z����Ă���w�b�_�t�@�C���y�сA��L�z�[��
// �y�[�W�ōs��ꂽ���[�U�T�|�[�g�̃��O�t�@�C�������Ƃɍ쐬����܂����B
// ���C�Â��̓_�Ȃǂ���܂�����Aosamu@big.or.jp �܂œd�q���[���ɂ�
// ���m�点������΁A�C������ł͂Ȃ�炩�̑Ώ�������\��������܂��B(^_^;
//
// �g�p���@�ɂ��Ă͕t���̃w���v�t�@�C���������������B
//=====================================================================
//               2001/04/14��      osamu@big.or.jp
// �{�Ƃ̃h�L�������g�̃o�[�W�����A�b�v�ɔ������o���Ă����o�O���C��
// brx �֐��𓱓�
// �󕶎��ɑ΂��錟���̃G���[���
// MatchPos �� 1 ���琔���n�߂�悤�Ɏd�l�ύX
// Subst ��� Strings[] ���Q�Ɖ\�ɂ���
// ����ɔ�����ʂ̕�����ɑ΂���u����������͒x���Ȃ���
//=====================================================================

interface

uses SysUtils,Windows;

//=====================================================================
// �{�� BREGEXP.H �ƁA�T�|�[�g�z�[���y�[�W�̃h�L�������g���
// BREGEXP.DLL �ƒ��������錾
//=====================================================================

const
BREGEXP_ERROR_MAX= 80;  // �G���[���b�Z�[�W�̍ő咷

type
PPChar=^PChar;
TBRegExpRec=packed record
    outp: PChar;        // �u�������ʐ擪�|�C���^
    outendp: PChar;     // �u�������ʖ����|�C���^
    splitctr: Integer;  // split ���ʃJ�E���^
    splitp: PPChar;     // split ���ʃ|�C���^�|�C���^
    rsv1: Integer;      // �\��ς�
    parap: PChar;       // �R�}���h������擪�|�C���^ ('s/xxxxx/yy/gi')
    paraendp: PChar;    // �R�}���h�����񖖔��|�C���^
    transtblp: PChar;   // tr �e�[�u���ւ̃|�C���^
    startp: PPChar;     // �}�b�`����������ւ̐擪�|�C���^
    endp: PPChar;       // �}�b�`����������ւ̖����|�C���^
    nparens: Integer;   // match/subst ���̊��ʂ̐�
end;
pTBRegExpRec=^TBRegExpRec;

{function BMatch(str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean; cdecl;
    external 'bregexp.dll';
function BSubst(str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean; cdecl;
    external 'bregexp.dll';
function BTrans(str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean; cdecl;
    external 'bregexp.dll';
function BSplit(str, target, targetendp: PChar; limit: Integer;
                var rxp: pTBRegExpRec; msg: PChar): Boolean; cdecl;
    external 'bregexp.dll';
procedure BRegFree(rx: pTBRegExpRec); cdecl;
    external 'bregexp.dll' name 'BRegfree';
function BRegExpVersion: PChar; cdecl;
    external 'bregexp.dll' name 'BRegexpVersion';}

//=====================================================================
// TBRegExp : BREGEXP.DLL �̋@�\���J�v�Z��������I�u�W�F�N�g
//=====================================================================

type
EBRegExpError=class(Exception) end;
TBRegExpMode=(brxNone, brxMatch, brxSplit);
TBRegExp=class(TObject)
  private
    Mode: TBRegExpMode;
    pTargetString: PChar;
    pBRegExp: PTBRegExpRec;
    function GetMatchPos: Integer;
    function GetMatchLength: Integer;
    function GetSplitCount: Integer;
    function GetMatchStrings(index:Integer): string;
    function GetMatchCount: Integer;
    function GetCount: Integer;
    function GetStrings(index: Integer): string;
    function GetSplitStrings(index: Integer): string;
    function GetLastCommand: string;
    procedure CheckCommand(const Command: string);
  public
    destructor Destroy; override;
  public
    function Match(const Command, TargetString: string): Boolean;
    function Subst(const Command: string; var TargetString: string): Boolean;
    function Split(const Command, TargetString: string; Limit: Integer): Boolean;
    function Trans(const Command: string;var TargetString: string): Boolean;
    property LastCommand: string read GetLastCommand;
    property MatchPos: Integer read GetMatchPos;
    property MatchLength: Integer read GetMatchLength;
    property Count: Integer read GetCount;
    property Strings[index: Integer]: string read GetStrings; default;
end;

//=====================================================================
// �����I�Ɏ��̉��A�j������郆�[�e�B���e�B�C���X�^���X
//=====================================================================

function brx: TBRegExp;
var
BMatch:function (str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean;cdecl;
BSubst:function (str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean;cdecl;
BTrans:function (str, target, targetendp: PChar;
                var rxp: pTBRegExpRec; msg: PChar): Boolean;cdecl;
BSplit:function (str, target, targetendp: PChar; limit: Integer;
                var rxp: pTBRegExpRec; msg: PChar): Boolean;cdecl;
BRegFree:procedure (rx: pTBRegExpRec);cdecl;
BRegExpVersion:function : PChar; cdecl;{cdecl;}
hDLL:THandle;

//=====================================================================

implementation

//=====================================================================

var fbrx: TBRegExp;

function brx: TBRegExp;
begin
 if fbrx=nil then fbrx:=TBRegExp.Create;
  Result:=fbrx;
end;

//=====================================================================

destructor TBRegExp.Destroy;
begin
   if pBRegExp<>nil then
        BRegFree(pBRegExp);
{    FreeLibrary(hDLL);}
    inherited Destroy;
end;

//=====================================================================
// �O��̃R�}���h�������Ԃ�

function TBRegExp.GetLastCommand: string;
var len: Integer;
begin
    if pBRegExp=nil then begin
        Result:= '';
    end else begin
        len:= Integer(pBRegExp^.paraendp)-Integer(pBRegExp^.parap);
        SetLength(Result, len);
        Move(pBRegExp^.parap^, Result[1], len);
    end;
end;

//=====================================================================
// �O��ƈقȂ�R�}���h�ł���΃L���b�V�����N���A��������葱��

procedure TBRegExp.CheckCommand(const Command: string);
var p,q: PChar;
begin
    if pBRegExp=nil then Exit;
    p:= pBRegExp.parap - 1;
    q:= PChar(@Command[1]) - 1;
    repeat
        Inc(p);
        Inc(q);
        if p^<>q^ then begin
            BRegFree(pBRegExp);
            pBRegExp:= nil;
            Break;
        end;
    until p^=#0;
end;

//=====================================================================

function TBRegExp.Match(const Command, TargetString: string): Boolean;
var ErrorString: string;
    i: Integer;
begin
    CheckCommand(Command);
    SetLength(ErrorString, BREGEXP_ERROR_MAX);
    Mode:=brxNone;
    if TargetString='' then begin // �G���[���
        i:=0;
        Result:=BMatch(
            PChar(Command),
            PChar(@i),
            PChar(@i)+1,    
            pBRegExp,
            PChar(ErrorString));
    end else begin
        Result:=BMatch(
            PChar(Command),
            PChar(TargetString),
            PChar(TargetString)+Length(TargetString),
            pBRegExp,
            PChar(ErrorString));
    end;
    SetLength(ErrorString, StrLen(PChar(ErrorString)));
    if ErrorString<>'' then
        raise EBRegExpError.Create(ErrorString);
    if Result then Mode:= brxMatch;
    pTargetString:= PChar(TargetString);
end;

//=====================================================================

function TBRegExp.Subst(const Command: string;
                        var TargetString: string): Boolean;
const TextBuffer: string='';
var ErrorString: string;
    ep,sp: PPChar;
    i: Integer;
begin
    CheckCommand(Command);
    Result:=False;
    if TargetString='' then Exit;
    TextBuffer:= TargetString;  // ( ) �𐳂����Ԃ����߂Ƀe�L�X�g��ۑ�����
    UniqueString(TextBuffer);
    SetLength(ErrorString, BREGEXP_ERROR_MAX);
    Mode:=brxNone;
    Result:=BSubst(
        PChar(Command),
        PChar(TargetString),
        PChar(TargetString)+Length(TargetString),
        pBRegExp,
        PChar(ErrorString));
    SetLength(ErrorString,StrLen(PChar(ErrorString)));
    if ErrorString<>'' then
        raise EBRegExpError.Create(ErrorString);

    if Result then begin // ( ) �̌��ʂ𐳂����Ԃ�����
        sp:=pBRegExp^.startp;
        ep:=pBRegExp^.endp;
        for i:=0 to GetMatchCount-1 do begin
            Inc(ep^, Integer(TextBuffer)-Integer(TargetString));
            Inc(sp^, Integer(TextBuffer)-Integer(TargetString));
            Inc(sp);
            Inc(ep);
        end;
        TargetString:= pBRegExp^.outp;
        Mode:=brxMatch;
    end;
end;

//=====================================================================

function TBRegExp.Trans(const Command: string;
                        var TargetString: string): Boolean;
var ErrorString: string;
begin
    CheckCommand(Command);
    Mode:=brxNone;
    if TargetString='' then // �G���[���
        TargetString:= #0;
    SetLength(ErrorString, BREGEXP_ERROR_MAX);
    Result:=BTrans(
        PChar(Command),
        PChar(TargetString),
        PChar(TargetString)+Length(TargetString),
        pBRegExp,
        PChar(ErrorString));
    SetLength(ErrorString,StrLen(PChar(ErrorString)));
    if ErrorString<>'' then
        raise EBRegExpError.Create(ErrorString);
    if Result then TargetString:=pBRegExp^.outp;
end;

//=====================================================================

function TBRegExp.Split(const Command, TargetString: string;
                        Limit: Integer): Boolean;
var ErrorString: string;
    t: string;
begin
    CheckCommand(Command);
    SetLength(ErrorString, BREGEXP_ERROR_MAX);
    Mode:=brxNone;
    if TargetString='' then begin // �G���[���
        t:= #0;
        Result:=BSplit(
            PChar(Command),
            PChar(t),
            PChar(t)+1,
            Limit,
            pBRegExp,
            PChar(ErrorString));
    end else begin
        Result:=BSplit(
            PChar(Command),
            PChar(TargetString),
            PChar(TargetString)+Length(TargetString),
            Limit,
            pBRegExp,
            PChar(ErrorString));
    end;
    SetLength(ErrorString,StrLen(PChar(ErrorString)));
    if ErrorString<>'' then
        raise EBRegExpError.Create(ErrorString);
    Mode:=brxSplit;
end;

//=====================================================================

function TBRegExp.GetMatchPos: Integer;
begin
    if Mode<>brxMatch then
        raise EBRegExpError.Create('no match pos');
    Result:=Integer(pBRegExp.startp^)-Integer(pTargetString)+1;
end;

//=====================================================================

function TBRegExp.GetMatchLength: Integer;
begin
    if Mode<>brxMatch then
        raise EBRegExpError.Create('no match length');
    Result:=Integer(pBRegExp.endp^)-Integer(pBRegExp.startp^);
end;

//=====================================================================

function TBRegExp.GetCount: Integer;
begin
    Result:=0;
    case Mode of
    brxNone:
        raise EBRegExpError.Create('no count now');
    brxMatch:
        Result:=GetMatchCount;
    brxSplit:
        Result:=GetSplitCount;
    end;
end;

//=====================================================================

function TBRegExp.GetMatchCount: Integer;
begin
    Result:= pBRegExp^.nparens+1;
end;

//=====================================================================

function TBRegExp.GetSplitCount: Integer;
begin
    Result:=pBRegExp^.splitctr;
end;

//=====================================================================

function TBRegExp.GetStrings(index: Integer): string;
begin
    Result:='';
    case Mode of
    brxNone:
        raise EBRegExpError.Create('no strings now');
    brxMatch:
        Result:=GetMatchStrings(index);
    brxSplit:
        Result:=GetSplitStrings(index);
    end;
end;

//=====================================================================

function TBRegExp.GetMatchStrings(index:Integer):string;
var sp,ep: PPChar;
begin
    Result:='';
    if (index<0) or (index>=GetMatchCount) then
        raise EBRegExpError.Create('index out of range');
    sp:=pBRegExp^.startp; Inc(sp, index);
    ep:=pBRegExp^.endp;   Inc(ep, index);
    SetLength(Result,Integer(ep^)-Integer(sp^));
    Move(sp^^,PChar(Result)^,Integer(ep^)-Integer(sp^));
end;

//=====================================================================

function TBRegExp.GetSplitStrings(index:Integer): string;
var p: PPChar;
    sp,ep: PChar;
begin
    if (index<0) or (index>=GetSplitCount) then
        raise EBRegExpError.Create('index out of range');
    p:=pBRegExp^.splitp;
    Inc(p,index*2); sp:=p^;
    Inc(p);         ep:=p^;
    SetLength(Result,Integer(ep)-Integer(sp));
    Move(sp^,PChar(Result)^,Integer(ep)-Integer(sp));
end;

//=====================================================================

initialization
 hDLL := LoadLibrary('BREGEXP.DLL');
  if hDLL = 0 then
    raise Exception.Create('BREGEXP.DLL�̃��[�h�Ɏ��s'#$d#$a'�G���[�R�[�h=' +IntToStr(GetLastError));
  @BMatch:= GetProcAddress(hDLL,'BMatch');
  @BSubst:= GetProcAddress(hDLL,'BSubst');
  @BTrans:= GetProcAddress(hDLL,'BTrans');
  @BSplit:= GetProcAddress(hDLL,'BSplit');
  @BRegFree:= GetProcAddress(hDLL,'BRegfree');
  @BRegExpVersion:= GetProcAddress(hDLL,'BRegexpVersion');

finalization
  fbrx.Free;
  FreeLibrary(hDLL);
end.

