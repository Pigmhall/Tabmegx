object Form1: TForm1
  Left = 286
  Top = 181
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'msdgen'
  ClientHeight = 449
  ClientWidth = 504
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 20
  object Image1: TImage
    Left = 296
    Top = 0
    Width = 105
    Height = 105
    Stretch = True
  end
  object Image2: TImage
    Left = 0
    Top = 243
    Width = 105
    Height = 105
    AutoSize = True
    Stretch = True
  end
  object Image3: TImage
    Left = 0
    Top = 251
    Width = 105
    Height = 105
    AutoSize = True
    Stretch = True
    Visible = False
  end
  object DriveComboBox1: TDriveComboBox
    Left = 145
    Top = 175
    Width = 153
    Height = 26
    DirList = DirectoryListBox1
    TabOrder = 0
  end
  object FileList1: TFileListBox
    Left = 160
    Top = 8
    Width = 145
    Height = 145
    ItemHeight = 20
    Mask = '*.bmp'
    TabOrder = 1
    Visible = False
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 144
    Top = 0
    Width = 153
    Height = 175
    FileList = FileList1
    ItemHeight = 20
    TabOrder = 2
    OnChange = DirectoryListBox1Change
  end
  object Memo1: TMemo
    Left = 0
    Top = 290
    Width = 505
    Height = 97
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    WordWrap = False
  end
  object Button1: TButton
    Left = 251
    Top = 392
    Width = 129
    Height = 33
    Caption = 'copy and exit'
    TabOrder = 4
    OnClick = Button1Click
  end
  object rbSprite: TRadioButton
    Left = 304
    Top = 77
    Width = 73
    Height = 17
    Caption = 'sprite'
    TabOrder = 5
    OnClick = FileList1Click
  end
  object rbCharacter: TRadioButton
    Left = 304
    Top = 136
    Width = 113
    Height = 17
    Caption = 'character'
    TabOrder = 6
    OnClick = FileList1Click
  end
  object GroupBox1: TGroupBox
    Left = 304
    Top = 184
    Width = 89
    Height = 97
    Caption = 'output'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    object rbCcz80: TRadioButton
      Left = 8
      Top = 48
      Width = 65
      Height = 17
      Caption = 'ccz80'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = FileList1Click
    end
    object rbBasic: TRadioButton
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'basic'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TabStop = True
      OnClick = FileList1Click
    end
    object rbQq: TRadioButton
      Left = 8
      Top = 72
      Width = 65
      Height = 17
      Caption = 'file'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = FileList1Click
    end
  end
  object Button2: TButton
    Left = 107
    Top = 392
    Width = 112
    Height = 33
    Caption = 'copy'
    TabOrder = 8
    OnClick = Button2Click
  end
  object BitBtn1: TBitBtn
    Left = 0
    Top = 201
    Width = 40
    Height = 40
    TabOrder = 9
    OnClick = BitBtn1Click
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
  object BitBtn2: TBitBtn
    Left = 40
    Top = 201
    Width = 40
    Height = 40
    TabOrder = 10
    OnClick = BitBtn2Click
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
  object FileListBox1: TListBox
    Left = 0
    Top = 0
    Width = 143
    Height = 201
    ItemHeight = 20
    TabOrder = 11
    OnClick = FileList1Click
  end
  object BitBtn3: TBitBtn
    Left = 129
    Top = 201
    Width = 40
    Height = 40
    Caption = 'EN'
    TabOrder = 12
    OnClick = BitBtn3Click
  end
  object BitBtn4: TBitBtn
    Left = 89
    Top = 201
    Width = 40
    Height = 40
    Caption = 'HM'
    TabOrder = 13
    OnClick = BitBtn4Click
  end
  object btnLock: TBitBtn
    Left = 177
    Top = 201
    Width = 40
    Height = 40
    Caption = 'LK'
    TabOrder = 14
    OnClick = btnLockClick
  end
  object chkTwoSprites: TCheckBox
    Left = 400
    Top = 98
    Width = 81
    Height = 17
    Caption = '2 sprites'
    TabOrder = 15
    OnClick = FileList1Click
  end
  object rbGraphic: TRadioButton
    Left = 304
    Top = 156
    Width = 89
    Height = 25
    Caption = 'graphic'
    TabOrder = 16
    OnClick = FileList1Click
  end
  object chk256: TCheckBox
    Left = 400
    Top = 161
    Width = 57
    Height = 17
    Caption = '256'
    TabOrder = 17
    OnClick = FileList1Click
  end
  object chkCompress: TCheckBox
    Left = 400
    Top = 182
    Width = 97
    Height = 17
    Caption = 'compress'
    TabOrder = 18
    OnClick = FileList1Click
  end
  object ComboBox1: TComboBox
    Left = 0
    Top = 261
    Width = 121
    Height = 28
    ItemHeight = 20
    TabOrder = 19
    Text = 'ComboBox1'
    OnChange = ComboBox1Change
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 430
    Width = 504
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object chkOneColor: TCheckBox
    Left = 400
    Top = 78
    Width = 81
    Height = 17
    Caption = '1 color'
    TabOrder = 21
    OnClick = FileList1Click
  end
  object chkDummyR: TCheckBox
    Left = 400
    Top = 118
    Width = 89
    Height = 17
    Caption = 'dummyR'
    TabOrder = 22
    OnClick = FileList1Click
  end
end
