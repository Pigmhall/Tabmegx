object FrmPerl: TFrmPerl
  Left = 151
  Top = 130
  Width = 390
  Height = 260
  BorderStyle = bsSizeToolWin
  Caption = 'Perl'
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 12
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 382
    Height = 214
    Align = alClient
    Color = clBlack
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWhite
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Lines.Strings = (
      'open(IN,"%target%");'
      'while($buf=<IN>){'
      ' if($buf=~/aa/){print $buf;}'
      '}'
      'close(IN);'
      '')
    ParentFont = False
    TabOrder = 0
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 64
    Top = 40
    object M1: TMenuItem
      Caption = '&Menu'
      object Perl1: TMenuItem
        Caption = 'Execute current file'
        ShortCut = 16504
        OnClick = Perl1Click
      end
      object Perl2: TMenuItem
        Caption = 'Execute Clip board'
        OnClick = Perl2Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object N3: TMenuItem
        Caption = 'Clear'
        OnClick = N3Click
      end
      object N2: TMenuItem
        Caption = 'Save as template'
        ShortCut = 16467
        OnClick = N2Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object X1: TMenuItem
        Caption = 'Close'
        ShortCut = 32856
      end
    end
    object mnTemp: TMenuItem
      Caption = '&Template'
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'pl'
    Filter = '*.pl|*.pl'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 96
    Top = 40
  end
end
