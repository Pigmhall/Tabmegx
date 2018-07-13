object frmMsx: TfrmMsx
  Left = 213
  Top = 83
  BorderStyle = bsDialog
  Caption = 'MSX, CPC Setting'
  ClientHeight = 547
  ClientWidth = 440
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 20
  object Label1: TLabel
    Left = 8
    Top = 21
    Width = 98
    Height = 20
    Caption = 'Disk Manager'
  end
  object Label2: TLabel
    Left = 8
    Top = 70
    Width = 64
    Height = 20
    Caption = 'Emulator'
  end
  object Label3: TLabel
    Left = 8
    Top = 119
    Width = 42
    Height = 20
    Caption = 'ccz80'
  end
  object Label4: TLabel
    Left = 9
    Top = 98
    Width = 213
    Height = 13
    Caption = 'blueMSX or openMSX or PC-CPC or WinAPE'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 4
    Width = 94
    Height = 13
    Caption = 'Application Path'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 8
    Top = 220
    Width = 154
    Height = 13
    Caption = 'ccz80 and ccZ80+ Options'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 7
    Top = 331
    Width = 104
    Height = 20
    Caption = 'Include(ccz80)'
  end
  object Label9: TLabel
    Left = 7
    Top = 397
    Width = 98
    Height = 20
    Caption = 'ORG address'
  end
  object Label10: TLabel
    Left = 8
    Top = 423
    Width = 100
    Height = 13
    Caption = 'openMSX options'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label11: TLabel
    Left = 7
    Top = 439
    Width = 114
    Height = 20
    Caption = 'DirAsDisk folder'
  end
  object Label12: TLabel
    Left = 7
    Top = 471
    Width = 107
    Height = 20
    Caption = 'Command Line'
  end
  object Label13: TLabel
    Left = 9
    Top = 48
    Width = 194
    Height = 13
    Caption = 'DiskExplorer or Disk-Manager (MSX only)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label14: TLabel
    Left = 8
    Top = 151
    Width = 62
    Height = 20
    Caption = 'ccZ80++'
  end
  object Label15: TLabel
    Left = 7
    Top = 363
    Width = 105
    Height = 20
    Caption = 'Path(ccZ80++)'
  end
  object Label16: TLabel
    Left = 104
    Top = 282
    Width = 35
    Height = 20
    Caption = 'Size:'
  end
  object Label17: TLabel
    Left = 215
    Top = 397
    Width = 104
    Height = 20
    Caption = 'DATA address'
  end
  object Label18: TLabel
    Left = 9
    Top = 238
    Width = 67
    Height = 16
    Caption = 'Export type'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 8
    Top = 187
    Width = 84
    Height = 20
    Caption = 'MGS Player'
  end
  object edtDiskExplorer: TEdit
    Left = 116
    Top = 17
    Width = 285
    Height = 28
    TabOrder = 0
  end
  object edtMsxEmu: TEdit
    Left = 116
    Top = 66
    Width = 285
    Height = 28
    TabOrder = 2
  end
  object edtCcz80: TEdit
    Left = 116
    Top = 115
    Width = 285
    Height = 28
    TabOrder = 5
  end
  object edtLoaderScript: TEdit
    Left = 192
    Top = 254
    Width = 241
    Height = 24
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
  end
  object edtIncludePath: TEdit
    Left = 120
    Top = 327
    Width = 313
    Height = 28
    TabOrder = 18
  end
  object edtOrgAddress: TEdit
    Left = 112
    Top = 393
    Width = 73
    Height = 28
    TabOrder = 20
    Text = '8500'
  end
  object Button1: TButton
    Left = 264
    Top = 505
    Width = 81
    Height = 33
    Caption = '&OK'
    TabOrder = 24
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 352
    Top = 505
    Width = 81
    Height = 33
    Caption = '&Cancel'
    TabOrder = 25
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 400
    Top = 17
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 1
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 400
    Top = 66
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 400
    Top = 114
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 6
    OnClick = Button5Click
  end
  object edtDirAsDisk: TEdit
    Left = 128
    Top = 435
    Width = 305
    Height = 28
    TabOrder = 22
  end
  object edtMachine: TEdit
    Left = 128
    Top = 467
    Width = 305
    Height = 28
    TabOrder = 23
    Text = '-machine'
  end
  object edtCcz80p: TEdit
    Left = 116
    Top = 147
    Width = 285
    Height = 28
    TabOrder = 7
  end
  object Button6: TButton
    Left = 400
    Top = 146
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 8
    OnClick = BtnCcz80pp
  end
  object edtPath: TEdit
    Left = 119
    Top = 359
    Width = 314
    Height = 28
    TabOrder = 19
  end
  object edtRomSize: TComboBox
    Left = 191
    Top = 278
    Width = 81
    Height = 28
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 20
    ParentFont = False
    TabOrder = 16
    Text = '16384'
    Items.Strings = (
      '8192'
      '16384'
      '24576'
      '32768'
      '40960'
      '49152')
  end
  object edtDataAddress: TEdit
    Left = 328
    Top = 393
    Width = 73
    Height = 28
    TabOrder = 21
    Text = 'c000'
  end
  object chkExportBin: TRadioButton
    Left = 8
    Top = 259
    Width = 81
    Height = 17
    Caption = 'BIN file'
    Checked = True
    TabOrder = 11
    TabStop = True
    OnClick = chkExportBinClick
  end
  object chkExportRom: TRadioButton
    Left = 8
    Top = 282
    Width = 81
    Height = 17
    Caption = 'ROM file'
    TabOrder = 15
    OnClick = chkExportRomClick
  end
  object chkExportCom: TRadioButton
    Left = 8
    Top = 305
    Width = 88
    Height = 17
    Caption = 'COM file'
    TabOrder = 17
    OnClick = chkExportComClick
  end
  object chkMakeLoader: TCheckBox
    Left = 93
    Top = 258
    Width = 97
    Height = 17
    Caption = 'make loader'
    Checked = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 12
  end
  object chkDragDsk: TCheckBox
    Left = 243
    Top = 97
    Width = 166
    Height = 17
    Caption = 'Drag a disk image to blueMSX'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object edtMgsPlayer: TEdit
    Left = 116
    Top = 183
    Width = 285
    Height = 28
    TabOrder = 9
  end
  object Button7: TButton
    Left = 399
    Top = 182
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 10
    OnClick = Button7Click
  end
  object btnLSDef: TButton
    Left = 386
    Top = 278
    Width = 48
    Height = 21
    Caption = 'Default'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = btnLSDefClick
  end
  object chkExportExbin: TRadioButton
    Left = 280
    Top = 285
    Width = 89
    Height = 17
    Caption = 'exBin file'
    TabOrder = 26
    OnClick = chkExportExbinClick
  end
  object OpenDialog1: TOpenDialog
    Left = 80
    Top = 118
  end
end
