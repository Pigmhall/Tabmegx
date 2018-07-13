object FrmCmd: TFrmCmd
  Left = 154
  Top = 106
  Width = 497
  Height = 301
  BorderStyle = bsSizeToolWin
  Caption = 'Console_'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Scaled = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 34
    Width = 465
    Height = 214
    BorderStyle = bsNone
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clWhite
    Font.Height = -13
    Font.Name = 'Terminal'
    Font.Style = []
    HideSelection = False
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
    OnChange = Memo1Change
    OnClick = Memo1Click
    OnKeyDown = Edit1KeyDown
  end
  object Edit1: TEdit
    Tag = 1
    Left = 0
    Top = 0
    Width = 121
    Height = 19
    BorderStyle = bsNone
    Color = clBlack
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWhite
    Font.Height = -13
    Font.Name = 'Terminal'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 352
    Top = 0
    Width = 105
    Height = 25
    Caption = 'Close'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = mnCloseClick
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 48
    Top = 32
    object Menu1: TMenuItem
      Caption = 'Menu'
      object N4: TMenuItem
        Caption = '&Clear'
        ShortCut = 112
        OnClick = N4Click
      end
      object N1: TMenuItem
        Caption = 'Select &All'
        ShortCut = 16449
        OnClick = N1Click
      end
      object mnWrap: TMenuItem
        Caption = '&Word wrap'
        ShortCut = 16471
        OnClick = mnWrapClick
      end
      object mnKanji: TMenuItem
        Caption = 'Use &Kanji'
        OnClick = mnKanjiClick
      end
      object mnFont: TMenuItem
        Caption = 'Font...'
        OnClick = mnFontClick
      end
      object Excel1: TMenuItem
        Caption = 'Open with Excel'
        ShortCut = 16453
        OnClick = Excel1Click
      end
      object Exceltxt1: TMenuItem
        Tag = 1
        Caption = 'Open with Excel(txt)'
        ShortCut = 32837
        OnClick = Excel1Click
      end
      object mnSaveSelect: TMenuItem
        Caption = 'Save selected text'
        ShortCut = 16467
        OnClick = mnSaveSelectClick
      end
      object N5: TMenuItem
        Caption = 'Rectangle Copy'
        ShortCut = 16452
        OnClick = N5Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object mnFind: TMenuItem
        Caption = '&Find'
        ShortCut = 32851
        OnClick = mnFindClick
      end
      object mnFindNext: TMenuItem
        Caption = 'Find &Next'
        ShortCut = 16460
        OnClick = mnFindNextClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object mnEditFocus: TMenuItem
        Caption = 'Back to Editor'
        ShortCut = 32849
        OnClick = mnEditFocusClick
      end
      object mnClose: TMenuItem
        Caption = 'Close(&X)'
        ShortCut = 32856
        OnClick = mnCloseClick
      end
    end
    object mnCommit: TMenuItem
      Caption = 'Rollba&ck'
      OnClick = mnCommitClick
    end
    object menuCol: TMenuItem
    end
  end
  object FindDialog1: TFindDialog
    OnFind = FindDialog1Find
    Left = 16
    Top = 32
  end
  object SaveDialog1: TSaveDialog
    Left = 16
    Top = 64
  end
end
