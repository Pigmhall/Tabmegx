object frmChrEdit: TfrmChrEdit
  Left = 191
  Top = 118
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'chr edit'
  ClientHeight = 632
  ClientWidth = 592
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 24
  object Image2: TImage
    Left = 160
    Top = 2
    Width = 37
    Height = 37
  end
  object Image3: TImage
    Left = 216
    Top = 0
    Width = 41
    Height = 41
    AutoSize = True
    Visible = False
  end
  object Image1: TImage
    Left = 0
    Top = 41
    Width = 592
    Height = 592
    OnMouseDown = Image1MouseDown
  end
  object lblCnt: TLabel
    Left = 202
    Top = 6
    Width = 26
    Height = 24
    Caption = '(0)'
  end
  object btnOpen: TBitBtn
    Left = 0
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 0
    OnClick = btnOpenClick
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
  object btnSave: TBitBtn
    Left = 48
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 1
    OnClick = btnSaveClick
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
  object btnLoadD: TBitBtn
    Left = 104
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 2
    OnClick = btnLoadDClick
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888880000
      0000000000000088888888888888000000000000000000888888888888888888
      8888888888888888888888888888888888888888888888888888888888880000
      0000000000000088888888888888000000000000000000888888888888888888
      8888888888888888888888888888888888888888888888888888888888888800
      0000000088888888888888888888880000000000888888888888888888888800
      0088880000888888888888888888880000888800008888888888888888888800
      0088888800008888888888888888880000888888000088888888888888888800
      0088888800008888888888888888880000888888000088888888888888888800
      0088888800008888888888888888880000888888000088888888888888888800
      0088880000888888888888888888880000888800008888888888888888888800
      0000000088888888888888888888880000000000888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object BitBtn2: TBitBtn
    Left = 384
    Top = 0
    Width = 48
    Height = 40
    Caption = 'OK'
    TabOrder = 3
    OnClick = BitBtn2Click
  end
  object BitBtn3: TBitBtn
    Left = 440
    Top = 0
    Width = 48
    Height = 40
    TabOrder = 4
    OnClick = BitBtn3Click
    Glyph.Data = {
      76020000424D7602000000000000760000002800000020000000200000000100
      0400000000000002000000000000000000001000000000000000070707000707
      8400078407000784840084070700840784008484070084848400C3C3C3000707
      FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
      8888888888888888888888888888888888888888888888888888888888888888
      8888888888888888888888888888888888888888888888888888888888008888
      8888888888888888008888888800888888888888888888880088888800000088
      8888888888888888888888880000008888888888888888888888888800000000
      8888888888888800888888880000000088888888888888008888888888000000
      8888888888880088888888888800000088888888888800888888888888880000
      0088888888000088888888888888000000888888880000888888888888888800
      0000888800008888888888888888880000008888000088888888888888888888
      0000000000888888888888888888888800000000008888888888888888888888
      8800000088888888888888888888888888000000888888888888888888888888
      0000000000888888888888888888888800000000008888888888888888888800
      0000888800008888888888888888880000008888000088888888888888000000
      0088888888000088888888888800000000888888880000888888888800000000
      8888888888880000888888880000000088888888888800008888888800000088
      8888888888888888008888880000008888888888888888880088888888888888
      8888888888888888888888888888888888888888888888888888}
  end
  object OpenDialog1: TOpenDialog
    Filter = '*.bmp|*.bmp'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 312
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '*.bmp|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 344
    Top = 16
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 56
    Top = 48
  end
end