object FrmOption: TFrmOption
  Left = 203
  Top = 25
  BorderStyle = bsDialog
  Caption = 'Option'
  ClientHeight = 557
  ClientWidth = 450
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'MS Sans Serif'
  Font.Pitch = fpFixed
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 20
  object Label1: TLabel
    Left = 8
    Top = 13
    Width = 67
    Height = 20
    Caption = 'File mask'
  end
  object Label2: TLabel
    Left = 105
    Top = 115
    Width = 55
    Height = 13
    Caption = 'Execute file'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 9
    Top = 117
    Width = 44
    Height = 13
    Caption = 'Extention'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 264
    Width = 70
    Height = 20
    Caption = 'Database'
  end
  object Label5: TLabel
    Left = 17
    Top = 294
    Width = 114
    Height = 20
    Caption = 'Database name'
  end
  object Label6: TLabel
    Left = 141
    Top = 326
    Width = 34
    Height = 20
    Caption = 'User'
  end
  object Label7: TLabel
    Left = 273
    Top = 325
    Width = 69
    Height = 20
    Caption = 'Password'
  end
  object Label8: TLabel
    Left = 17
    Top = 322
    Width = 34
    Height = 20
    Caption = 'Host'
  end
  object Label9: TLabel
    Left = 283
    Top = 264
    Width = 76
    Height = 20
    Caption = 'Kanji Code'
  end
  object Label10: TLabel
    Left = 9
    Top = 98
    Width = 167
    Height = 13
    Caption = 'Application of each extention'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label11: TLabel
    Left = 9
    Top = 243
    Width = 55
    Height = 13
    Caption = 'Database'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label13: TLabel
    Left = 96
    Top = 164
    Width = 327
    Height = 16
    Caption = '%f=filename'#12288'%a=argument'#12288'%s=selectedtext %g=GUI'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Microsoft Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 9
    Top = 189
    Width = 59
    Height = 13
    Caption = 'Ctrl+F1'#65374'F5'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 10
    Top = 214
    Width = 21
    Height = 13
    Caption = 'Ctrl+'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
  end
  object Label12: TLabel
    Left = 8
    Top = 71
    Width = 108
    Height = 20
    Caption = 'Function words'
  end
  object Label16: TLabel
    Left = 9
    Top = 353
    Width = 47
    Height = 13
    Caption = 'WinSCP'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label17: TLabel
    Left = 9
    Top = 373
    Width = 82
    Height = 20
    Caption = 'Execute file'
  end
  object Label18: TLabel
    Left = 318
    Top = 373
    Width = 48
    Height = 20
    Caption = 'chmod'
  end
  object Label19: TLabel
    Left = 9
    Top = 401
    Width = 63
    Height = 13
    Caption = 'Button Key'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label20: TLabel
    Left = 202
    Top = 422
    Width = 31
    Height = 20
    Caption = 'Size'
  end
  object Label21: TLabel
    Left = 303
    Top = 425
    Width = 11
    Height = 20
    Caption = 'X'
  end
  object Label22: TLabel
    Left = 6
    Top = 507
    Width = 212
    Height = 13
    Caption = 'U=up D=down L=left R=right H=home E=end'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Microsoft Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
  end
  object Label23: TLabel
    Left = 9
    Top = 529
    Width = 116
    Height = 13
    Caption = 'Suggestion font size'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = [fsBold]
    ParentFont = False
  end
  object EdtFileMask: TEdit
    Left = 94
    Top = 9
    Width = 340
    Height = 28
    TabOrder = 0
  end
  object Button1: TButton
    Left = 235
    Top = 514
    Width = 69
    Height = 32
    Caption = '&OK'
    TabOrder = 21
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 310
    Top = 514
    Width = 66
    Height = 32
    Caption = '&Cancel'
    TabOrder = 22
    OnClick = Button2Click
  end
  object ChkSjisOnly: TCheckBox
    Left = 8
    Top = 44
    Width = 257
    Height = 17
    Caption = 'SJIS only'
    TabOrder = 1
  end
  object ChkAutoIndent: TCheckBox
    Left = 286
    Top = 43
    Width = 155
    Height = 17
    Caption = 'auto indent'
    TabOrder = 2
  end
  object CmbExt: TComboBox
    Left = 8
    Top = 131
    Width = 73
    Height = 28
    AutoComplete = False
    ItemHeight = 20
    TabOrder = 4
    OnChange = CmbExtChange
  end
  object EdtCmd: TEdit
    Left = 93
    Top = 131
    Width = 184
    Height = 28
    TabOrder = 5
  end
  object Button4: TButton
    Left = 317
    Top = 131
    Width = 52
    Height = 30
    Caption = 'Apply'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = Button4Click
  end
  object EdtDbname: TEdit
    Left = 161
    Top = 291
    Width = 121
    Height = 28
    TabOrder = 14
  end
  object EdtDbuser: TEdit
    Left = 182
    Top = 322
    Width = 79
    Height = 28
    TabOrder = 16
  end
  object EdtDbpasswd: TEdit
    Left = 352
    Top = 322
    Width = 79
    Height = 28
    PasswordChar = '*'
    TabOrder = 17
  end
  object CmbDbd: TComboBox
    Left = 164
    Top = 260
    Width = 84
    Height = 28
    ItemHeight = 20
    TabOrder = 12
    Items.Strings = (
      'Mysql'
      'Oracle'
      'Pg')
  end
  object EdtDbhost: TEdit
    Left = 60
    Top = 322
    Width = 69
    Height = 28
    TabOrder = 15
  end
  object CmbDbknj: TComboBox
    Left = 376
    Top = 261
    Width = 57
    Height = 28
    ItemHeight = 20
    ItemIndex = 0
    TabOrder = 13
    Text = 'SJIS'
    Items.Strings = (
      'SJIS'
      'EUC'
      'JIS')
  end
  object BtnBrowse0: TButton
    Left = 277
    Top = 131
    Width = 28
    Height = 30
    Caption = '...'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = BtnBrowse0Click
  end
  object Button5: TButton
    Left = 382
    Top = 514
    Width = 59
    Height = 32
    Caption = '&Help'
    TabOrder = 23
    OnClick = Button5Click
  end
  object CmbFx: TComboBox
    Left = 36
    Top = 207
    Width = 45
    Height = 28
    AutoComplete = False
    Style = csDropDownList
    ItemHeight = 20
    TabOrder = 8
    OnChange = CmbFxChange
    Items.Strings = (
      'F1'
      'F2'
      'F3'
      'F4'
      'F5')
  end
  object EdtFxcmd: TEdit
    Left = 93
    Top = 207
    Width = 184
    Height = 28
    TabOrder = 9
  end
  object BtnBrowse1: TButton
    Tag = 1
    Left = 277
    Top = 207
    Width = 28
    Height = 26
    Caption = '...'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    OnClick = BtnBrowse0Click
  end
  object Button7: TButton
    Left = 316
    Top = 207
    Width = 53
    Height = 26
    Caption = 'Apply'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    OnClick = Button7Click
  end
  object EdtFuncJump: TEdit
    Left = 166
    Top = 67
    Width = 251
    Height = 28
    TabOrder = 3
  end
  object EdtWinScp: TEdit
    Left = 115
    Top = 370
    Width = 169
    Height = 28
    TabOrder = 18
  end
  object Button3: TButton
    Tag = 2
    Left = 285
    Top = 371
    Width = 28
    Height = 30
    Caption = '...'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 19
    OnClick = BtnBrowse0Click
  end
  object EdtWinScpMod: TEdit
    Left = 379
    Top = 370
    Width = 38
    Height = 28
    TabOrder = 20
  end
  object EdtButkey1: TEdit
    Left = 11
    Top = 418
    Width = 182
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 24
  end
  object EdtButkey2: TEdit
    Left = 11
    Top = 447
    Width = 182
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 25
  end
  object EdtButkey3: TEdit
    Left = 11
    Top = 476
    Width = 182
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 26
  end
  object EdtBtnKeySizeX: TEdit
    Left = 243
    Top = 420
    Width = 54
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 27
  end
  object EdtBtnKeySizeY: TEdit
    Left = 323
    Top = 420
    Width = 54
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 28
  end
  object EdtSuggestion: TEdit
    Left = 139
    Top = 524
    Width = 54
    Height = 29
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    TabOrder = 29
  end
  object OpenDialog1: TOpenDialog
    Filter = '*.exe;*.com;*.bat|*.exe;*.com;*.bat'
    Left = 112
    Top = 184
  end
end
