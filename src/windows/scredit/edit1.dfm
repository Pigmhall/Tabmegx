object frmEdit: TfrmEdit
  Left = 223
  Top = 165
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'scredit'
  ClientHeight = 217
  ClientWidth = 584
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 12
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 105
    Height = 105
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
  end
  object Image2: TImage
    Left = 8
    Top = 40
    Width = 256
    Height = 384
    AutoSize = True
    Visible = False
  end
  object Image3: TImage
    Left = 0
    Top = 0
    Width = 105
    Height = 105
    Visible = False
  end
  object Image2_2: TImage
    Left = 0
    Top = 40
    Width = 256
    Height = 384
    AutoSize = True
    Visible = False
  end
  object BitBtn2: TBitBtn
    Left = 537
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 0
    TabStop = False
    OnClick = mnExportClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888000000000088
      888888880000000000880000000000888888888800000000008800BBFFBB0088
      8888888800BBFFBB008800BBFFBB00888888888800BBFFBB008800FFBBFF0088
      8888888800FFBBFF008800FFBBFF00888888888800FFBBFF0088000000000088
      8800888800000000008800000000008888008888000000000088888800888888
      0088008888880088888888880088888800880088888800888888888800888800
      88EE880088880088888888880088880088EE8800888800888888888800000088
      EE88EE88000000888888888800000088EE88EE88000000888888888888888800
      88EE880088888888888888888888880088EE8800888888888888888888888888
      0088008888888888888888888888888800880088888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888800
      0000000088888888888888888888880000000000888888888888888888888800
      FFBBFF00888888888888888888888800FFBBFF00888888888888888888888800
      BBFFBB00888888888888888888888800BBFFBB00888888888888888888888800
      0000000088888888888888888888880000000000888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnSpoit: TBitBtn
    Left = 441
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 1
    TabStop = False
    OnClick = btnSpoitClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      04000000000000020000120B0000120B00001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888666666
      6666666688888888888888888866666666666666888888888888888866660066
      6666666666888888888888886666006666666666668888888888888866006600
      6666668888888888888888886600660066666688888888888888888888006666
      0088888888888888888888888800666600888888888888888888888888880066
      6600888888888888888888888888006666008888888888888888888888888800
      6666008888888888888888888888880066660088888888888888888888888888
      0066880088880088888888888888888800668800888800888888888888888888
      8800888800000088888888888888888888008888000000888888888888888888
      8888000000008888888888888888888888880000000088888888888888888888
      8888880000000000888888888888888888888800000000008888888888888888
      8888000000000000888888888888888888880000000000008888888888888888
      8888888888000000888888888888888888888888880000008888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnNextChr: TBitBtn
    Left = 390
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 2
    TabStop = False
    OnClick = btnNextChrClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      04000000000000020000120B0000120B00001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8800008888888888888888888888888888000088888888888888888888888888
      0066660088888888888888888888888800666600888888888888888888888800
      6666666600888888888888888888880066666666008888888888888888880066
      6666666666008888888888888888006666666666660088888888888888006666
      6666666666660088888888888800666666666666666600888888888800666666
      6666666666666600888888880066666666666666666666008888880066666666
      6666666666666666008888006666666666666666666666660088880000000000
      0000000000000000008888000000000000000000000000000088888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object BitBtn1: TBitBtn
    Left = 342
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 3
    TabStop = False
    OnClick = BitBtn1Click
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      04000000000000020000120B0000120B00001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888880000000000
      0000000000000000008888000000000000000000000000000088880066666666
      6666666666666666008888006666666666666666666666660088888800666666
      6666666666666600888888880066666666666666666666008888888888006666
      6666666666660088888888888800666666666666666600888888888888880066
      6666666666008888888888888888006666666666660088888888888888888800
      6666666600888888888888888888880066666666008888888888888888888888
      0066660088888888888888888888888800666600888888888888888888888888
      8800008888888888888888888888888888000088888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnRight: TBitBtn
    Left = 291
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 4
    TabStop = False
    OnClick = btnRightClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888800888888888888888888888888888888008888888888888888888888
      8888888800008888888888888888888888888888000088888888888888880000
      0000000000000088888888888888000000000000000000888888888888888888
      8888888800008888888888888888888888888888000088888888888888888888
      8888888800888888888888888888888888888888008888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnDown: TBitBtn
    Left = 243
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 5
    TabStop = False
    OnClick = btnDownClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8800000088888888888888888888888888000000888888888888888888888888
      0000000000888888888888888888888800000000008888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888008888888888888888888888888888880088888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnUp: TBitBtn
    Left = 195
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 6
    TabStop = False
    OnClick = btnUpClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888800
      0000000088888888888888888888880000000000888888888888888888888888
      0000008888888888888888888888888800000088888888888888888888888888
      8800888888888888888888888888888888008888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnLeft: TBitBtn
    Left = 147
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 7
    TabStop = False
    OnClick = btnLeftClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888800
      8888888888888888888888888888880088888888888888888888888888880000
      8888888888888888888888888888000088888888888888888888888888000000
      0000000000008888888888888800000000000000000088888888888888880000
      8888888888888888888888888888000088888888888888888888888888888800
      8888888888888888888888888888880088888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnSave: TBitBtn
    Left = 96
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 8
    TabStop = False
    OnClick = Save1Click
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888800000000
      0000000000000000008888880000000000000000000000000088880033330000
      0000000088880033008888003333000000000000888800330088880033330000
      0000000088880033008888003333000000000000888800330088880033330000
      0000000088880033008888003333000000000000888800330088880033330000
      0000000000000033008888003333000000000000000000330088880033333333
      3333333333333333008888003333333333333333333333330088880033330000
      0000000000003333008888003333000000000000000033330088880033008888
      8888888888880033008888003300888888888888888800330088880033008888
      8888888888880033008888003300888888888888888800330088880033008888
      8888888888880033008888003300888888888888888800330088880033008888
      8888888888880033008888003300888888888888888800330088880033008888
      8888888888880000008888003300888888888888888800000088880033008888
      8888888888880088008888003300888888888888888800880088880000000000
      0000000000000000008888000000000000000000000000000088888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnOpen: TBitBtn
    Left = 48
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 9
    TabStop = False
    OnClick = Open1Click
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888000000000000
      0000000000888888888800000000000000000000008888888888000033333333
      333333333300888888880000333333333333333333008888888800BB00333333
      3333333333330088888800BB003333333333333333330088888800FFBB003333
      3333333333333300888800FFBB0033333333333333333300888800BBFFBB0033
      3333333333333333008800BBFFBB00333333333333333333008800FFBBFFBB00
      0000000000000000000000FFBBFFBB000000000000000000000000BBFFBBFFBB
      FFBBFFBB00888888888800BBFFBBFFBBFFBBFFBB00888888888800FFBBFFBBFF
      BBFFBBFF00888888888800FFBBFFBBFFBBFFBBFF00888888888800BBFFBB0000
      0000000000888888888800BBFFBB000000000000008888888888880000008888
      8888888888880000008888000000888888888888888800000088888888888888
      8888888888888800008888888888888888888888888888000088888888888888
      8888008888880088008888888888888888880088888800880088888888888888
      8888880000008888888888888888888888888800000088888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnNew: TBitBtn
    Left = 0
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 10
    TabStop = False
    OnClick = Clear1Click
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888800000000
      0000000000000088888888880000000000000000000000888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFFFFFFFF00888888888800FFFFFFFFFFFFFFFFFF00888888888800FFFFFF
      FFFFFF00000000888888888800FFFFFFFFFFFF00000000888888888800FFFFFF
      FFFFFF00FF0088888888888800FFFFFFFFFFFF00FF0088888888888800FFFFFF
      FFFFFF00008888888888888800FFFFFFFFFFFF00008888888888888800000000
      0000000088888888888888880000000000000000888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object btnText: TBitBtn
    Left = 489
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 11
    TabStop = False
    OnClick = btnTextClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888000000880000
      0000000088888800008800000088000000000000888888000088770088888800
      7700888800880088880077008888880077008888008800888800880088888800
      8800888800880088888888008888880088008888008800888888880000000000
      8800000088880088888888000000000088000000888800888888888800880088
      8800888800880088880088880088008888008888008800888800888800880088
      0000000088888800000088880088008800000000888888000000888877007788
      8888888888888888888888887700778888888888888888888888888888008888
      8888888888888888888888888800888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 40
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open'
        ShortCut = 114
        OnClick = Open1Click
      end
      object Saveas1: TMenuItem
        Caption = 'Save &as...'
        ShortCut = 16467
        OnClick = Saveas1Click
      end
      object Save1: TMenuItem
        Caption = '&Save'
        ShortCut = 113
        OnClick = Save1Click
      end
      object mnChrEdit: TMenuItem
        Caption = '&Chr Edit'
        ShortCut = 119
        OnClick = mnChrEditClick
      end
      object Coord1: TMenuItem
        Caption = '&Option'
        ShortCut = 120
        OnClick = Coord1Click
      end
      object mnExport: TMenuItem
        Caption = 'Export BASIC'
        OnClick = mnExportClick
      end
      object ExportCCZ801: TMenuItem
        Caption = 'Export ccz80'
        ShortCut = 16453
        OnClick = ExportCCZ801Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Quit1: TMenuItem
        Caption = '&Quit'
        ShortCut = 16465
        OnClick = Quit1Click
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
      object Clear1: TMenuItem
        Caption = 'Clear'
        OnClick = Clear1Click
      end
      object Fill1: TMenuItem
        Caption = 'Fill'
        OnClick = Fill1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Spoit1: TMenuItem
        Caption = 'Spoit'
        OnClick = btnSpoitClick
      end
      object InsertTex1: TMenuItem
        Caption = 'Text'
        OnClick = btnTextClick
      end
    end
    object mnModify1: TMenuItem
    end
    object mnStatus: TMenuItem
    end
    object mnCopy: TMenuItem
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'dat'
    Filter = '*.dat|*.dat'
    Options = [ofHideReadOnly, ofFileMustExist]
    Title = 'open'
    Left = 40
    Top = 40
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'dat'
    Filter = '*.dat|*.dat'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Title = 'save'
    Left = 72
    Top = 40
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 104
    Top = 40
  end
end
