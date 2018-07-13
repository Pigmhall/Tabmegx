object FrmMeg1: TFrmMeg1
  Left = 288
  Top = 174
  Width = 600
  Height = 454
  Caption = 'Start'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object TabControl1: TTabControl
    Left = 0
    Top = 40
    Width = 592
    Height = 272
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    HotTrack = True
    ParentFont = False
    ParentShowHint = False
    PopupMenu = PopupMenu1
    ShowHint = False
    TabHeight = 20
    TabOrder = 0
    TabStop = False
    OnChange = TabControl1Change
    OnDragDrop = TabControl1DragDrop
    OnDragOver = TabControl1DragOver
    OnMouseDown = TabControl1MouseDown
    object Memo1: TMemo
      Left = 0
      Top = 23
      Width = 353
      Height = 145
      Color = clBlack
      Ctl3D = True
      Font.Charset = OEM_CHARSET
      Font.Color = clWhite
      Font.Height = -19
      Font.Name = 'Terminal'
      Font.Style = []
      HideSelection = False
      ParentCtl3D = False
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
      WantTabs = True
      WordWrap = False
      OnChange = Memo1Change
      OnClick = Memo1Click
      OnKeyDown = Memo1KeyDown
      OnKeyPress = Memo1KeyPress
      OnKeyUp = Memo1KeyUp
    end
  end
  object PnlTop: TPanel
    Left = 0
    Top = 0
    Width = 592
    Height = 40
    Align = alTop
    BevelOuter = bvNone
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS UI Gothic'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Button6: TButton
      Left = 152
      Top = 0
      Width = 25
      Height = 40
      Caption = 'Save...'
      Font.Charset = SHIFTJIS_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Visible = False
      OnClick = Saveas1Click
    end
    object Button7: TButton
      Left = 120
      Top = 0
      Width = 41
      Height = 40
      Caption = 'CL'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Close1Click
    end
    object Button8: TButton
      Left = 525
      Top = 0
      Width = 41
      Height = 40
      Caption = 'Run'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = mnCommandClick
    end
    object btnCut: TBitBtn
      Left = 208
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 3
      OnClick = mnCutClick
      Glyph.Data = {
        76020000424D7602000000000000760000002800000020000000200000000100
        0400000000000002000000000000000000001000000000000000070707000707
        8400078407000784840084070700840784008484070084848400C3C3C3000707
        FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
        8888888888888888888888888888888888888888888888888888888888884444
        8888888888888888888888888888444488888888888888888888888888448888
        4488884444888888888888888844888844888844448888888888888888448888
        4488448888448888888888888844888844884488884488888888888888448888
        4488448888448888888888888844888844884488884488888888888888884444
        4488448888448888888888888888444444884488884488888888888888888888
        4488444444888888888888888888888844884444448888888888888888888888
        4400448888888888888888888888888844004488888888888888888888888888
        8800888888888888888888888888888888008888888888888888888888888888
        0000008888888888888888888888888800000088888888888888888888888888
        0088008888888888888888888888888800880088888888888888888888888800
        0088000088888888888888888888880000880000888888888888888888888800
        8888880088888888888888888888880088888800888888888888888888888800
        8888880088888888888888888888880088888800888888888888888888888800
        8888880088888888888888888888880088888800888888888888888888888888
        8888888888888888888888888888888888888888888888888888}
    end
    object btnCopy: TBitBtn
      Left = 248
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 4
      OnClick = mnCopyClick
      Glyph.Data = {
        76020000424D7602000000000000760000002800000020000000200000000100
        0400000000000002000000000000000000001000000000000000070707000707
        8400078407000784840084070700840784008484070084848400C3C3C3000707
        FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        4444444444444444448888888888888844444444444444444488888888888888
        44FFFFFFFFFFFFFF448888888888888844FFFFFFFFFFFFFF4488888888888888
        44FF0000000000FF448888888888888844FF0000000000FF4488000000000000
        44FFFFFFFFFFFFFF448800000000000044FFFFFFFFFFFFFF448800FFFFFFFFFF
        44FF0000000000FF448800FFFFFFFFFF44FF0000000000FF448800FF00000000
        44FFFFFFFFFFFFFF448800FF0000000044FFFFFFFFFFFFFF448800FFFFFFFFFF
        44FF0000FF444444448800FFFFFFFFFF44FF0000FF444444448800FF00000000
        44FFFFFFFF44FF44888800FF0000000044FFFFFFFF44FF44888800FFFFFFFFFF
        44FFFFFFFF444488888800FFFFFFFFFF44FFFFFFFF444488888800FF0000FF00
        4444444444448888888800FF0000FF004444444444448888888800FFFFFFFF00
        FF00888888888888888800FFFFFFFF00FF00888888888888888800FFFFFFFF00
        0088888888888888888800FFFFFFFF0000888888888888888888000000000000
        8888888888888888888800000000000088888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888}
    end
    object BitBtn1: TBitBtn
      Left = 288
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 5
      OnClick = mnPasteClick
      Glyph.Data = {
        76020000424D7602000000000000760000002800000020000000200000000100
        0400000000000002000000000000000000001000000000000000070707000707
        8400078407000784840084070700840784008484070084848400C3C3C3000707
        FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        4444444444444444444488888888888844444444444444444444880000000000
        44FFFFFFFFFFFFFFFF4488000000000044FFFFFFFFFFFFFFFF44007733773377
        44FF444444444444FF4400773377337744FF444444444444FF44003377337733
        44FFFFFFFFFFFFFFFF4400337733773344FFFFFFFFFFFFFFFF44007733773377
        44FF444444FF4444444400773377337744FF444444FF44444444003377337733
        44FFFFFFFFFF44FF448800337733773344FFFFFFFFFF44FF4488007733773377
        44FFFFFFFFFF4444888800773377337744FFFFFFFFFF44448888003377337733
        4444444444444400888800337733773344444444444444008888007733773377
        3377337733773300888800773377337733773377337733008888003377000000
        0000000000777700888800337700000000000000007777008888007777008888
        88888888007733008888007777008888888888880077330088880033773300BB
        0000BB007733770088880033773300BB0000BB00773377008888880000000000
        BBBB0000000000888888880000000000BBBB0000000000888888888888888800
        0000008888888888888888888888880000000088888888888888888888888888
        8888888888888888888888888888888888888888888888888888}
    end
    object BitBtn2: TBitBtn
      Left = 0
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 6
      OnClick = New1Click
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
    object BitBtn3: TBitBtn
      Left = 40
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 7
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
    object BitBtn4: TBitBtn
      Left = 80
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 8
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
    object btnShift: TButton
      Left = 167
      Top = 0
      Width = 41
      Height = 40
      Caption = 'SH'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      OnClick = btnShiftClick
    end
    object BitSource: TBitBtn
      Left = 419
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 10
      OnClick = SourceASMorBAS1Click
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
    object btnHelp: TBitBtn
      Left = 459
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 11
      OnClick = btnHelp1Click
      Glyph.Data = {
        76020000424D7602000000000000760000002800000020000000200000000100
        0400000000000002000000000000000000001000000000000000070707000707
        8400078407000784840084070700840784008484070084848400C3C3C3000707
        FF0007FF070007FFFF00FF070700FF07FF00FFFF0700FFFFFF00888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8800008888888888888888888888888888000088888888888888888888888888
        00BB330088888888888888888888888800BB3300888888888888888888888888
        00BB330088888888888888888888888800BB3300888888888888888888888888
        8800008888888888888888888888888888000088888888888888888888888888
        00BB330088888888888888888888888800BB3300888888888888888888888888
        00BB330088888888888888888888888800BB3300888888888888888888888888
        00BB330088888888888888888888888800BB3300888888888888888888888888
        00BBBB3300888888888888888888888800BBBB33008888888888888888880000
        8800BBBB3300888888888888888800008800BBBB33008888888888888800BB33
        008800BBBB330088888888888800BB33008800BBBB330088888888888800BB33
        00888800BB330088888888888800BB3300888800BB330088888888888800BBBB
        330000BBBB330088888888888800BBBB330000BBBB33008888888888888800BB
        BBBBBBBB3300888888888888888800BBBBBBBBBB330088888888888888888800
        0000000000888888888888888888880000000000008888888888888888888888
        8888888888888888888888888888888888888888888888888888}
    end
    object btnData: TBitBtn
      Left = 379
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 12
      OnClick = btnDataClick
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
    object BitBtn5: TBitBtn
      Left = 328
      Top = 0
      Width = 40
      Height = 40
      TabOrder = 13
      OnClick = Replace1Click
      Glyph.Data = {
        76020000424D7602000000000000760000002800000020000000200000000100
        04000000000000020000120B0000120B00001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        8888888888888888888888888888888888888888888888888888888888888888
        8866888800000000888888888888888888668888000000008888888888888888
        8866668800888888008888888888888888666688008888880088888888666666
        6666666600888888008888888866666666666666008888880088888888668888
        8866668800888888008888888866888888666688008888880088888888668888
        8866888800000000888888888866888888668888000000008888880088888800
        8888888800888888008888008888880088888888008888880088880088888800
        8888888800888888008888008888880088888888008888880088880000000000
        8888888800888888008888000000000088888888008888880088880088888800
        8888888800000000888888008888880088888888000000008888880088888800
        8888888888888888888888008888880088888888888888888888888800880088
        8888888888888888888888880088008888888888888888888888888800880088
        8888888888888888888888880088008888888888888888888888888888008888
        8888888888888888888888888800888888888888888888888888888888008888
        8888888888888888888888888800888888888888888888888888888888888888
        8888888888888888888888888888888888888888888888888888}
    end
  end
  object PnlBottom: TPanel
    Left = 0
    Top = 312
    Width = 592
    Height = 96
    Align = alBottom
    BevelOuter = bvNone
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object StatusBar1: TStatusBar
      Left = 0
      Top = 77
      Width = 592
      Height = 19
      Panels = <>
      SimplePanel = True
    end
  end
  object ListBox1: TListBox
    Left = 8
    Top = 64
    Width = 219
    Height = 235
    Color = clBlack
    Ctl3D = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWhite
    Font.Height = -13
    Font.Name = 'Terminal'
    Font.Style = []
    ItemHeight = 16
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    Visible = False
    OnClick = ListBox1Click
    OnExit = ListBox1Exit
    OnKeyDown = ListBox1KeyDown
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 24
    Top = 40
    object File1: TMenuItem
      AutoHotkeys = maManual
      Caption = 'File'
      object New1: TMenuItem
        Caption = 'New'
        ShortCut = 16462
        OnClick = New1Click
      end
      object NewDB1: TMenuItem
        Caption = 'New DBpro'
        OnClick = NewDB1Click
      end
      object NewAGK1: TMenuItem
        Caption = 'New AGK'
        OnClick = NewAGK1Click
      end
      object Open1: TMenuItem
        Caption = 'Open'
        ShortCut = 114
        OnClick = Open1Click
      end
      object Saveas1: TMenuItem
        Caption = 'Save as...'
        ShortCut = 16467
        OnClick = Saveas1Click
      end
      object Save1: TMenuItem
        Caption = 'Save'
        ShortCut = 113
        OnClick = Save1Click
      end
      object N11: TMenuItem
        Caption = 'Recover'
        ShortCut = 119
        OnClick = N11Click
      end
      object Backup1: TMenuItem
        Caption = 'Backup'
        ShortCut = 16450
        OnClick = Backup1Click
      end
      object Close1: TMenuItem
        Caption = 'Close'
        ShortCut = 32882
        OnClick = Close1Click
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object SaveFTP1: TMenuItem
        Caption = '&FTP save'
        OnClick = SaveFTP1Click
      end
      object FTPsetting1: TMenuItem
        Caption = 'F&TP setup'
        OnClick = FTPsetting1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Quit1: TMenuItem
        Caption = 'Quit'
        ShortCut = 32856
        OnClick = Quit1Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object Undo1: TMenuItem
        Caption = 'Undo'
        OnClick = Undo1Click
      end
      object N13: TMenuItem
        Caption = '-'
      end
      object mnPaste: TMenuItem
        Caption = 'Paste'
        OnClick = mnPasteClick
      end
      object mnCopy: TMenuItem
        Caption = 'Copy'
        OnClick = mnCopyClick
      end
      object mnCut: TMenuItem
        Caption = 'Cut'
        OnClick = mnCutClick
      end
      object N8: TMenuItem
        Caption = '-'
      end
      object Pasteasnew1: TMenuItem
        Caption = 'Paste as new'
        ShortCut = 16464
        OnClick = Pasteasnew1Click
      end
      object Selectall1: TMenuItem
        Caption = 'Select all'
        ShortCut = 16449
        OnClick = Selectall1Click
      end
      object mnKukeiCopy: TMenuItem
        Caption = 'Rectangle copy'
        ShortCut = 24644
        OnClick = mnKukeiCopyClick
      end
      object Paste11: TMenuItem
        Caption = 'Paste+1'
        OnClick = Paste11Click
      end
      object Pastenolf1: TMenuItem
        Caption = 'Paste(no lf)'
        OnClick = Pastenolf1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Find1: TMenuItem
        Caption = 'Find'
        ShortCut = 32851
        OnClick = Find1Click
      end
      object Findnext1: TMenuItem
        Caption = 'Find next'
        ShortCut = 16460
        OnClick = Findnext1Click
      end
      object Replace1: TMenuItem
        Caption = 'Replace'
        ShortCut = 16466
        OnClick = Replace1Click
      end
      object Goto1: TMenuItem
        Caption = 'Goto'
        ShortCut = 16455
        OnClick = Goto1Click
      end
      object J1: TMenuItem
        Caption = 'Jump'
        ShortCut = 16458
        OnClick = J1Click
      end
      object mnTojikigo: TMenuItem
        Caption = 'Find close'
        ShortCut = 16468
        OnClick = mnTojikigoClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object mnKouho: TMenuItem
        Caption = 'Suggestion'
        ShortCut = 45
        OnClick = mnKouhoClick
      end
      object Wordlist1: TMenuItem
        Caption = 'Word list'
        object mnWlMsx: TMenuItem
          Caption = 'MSX-BASIC'
          GroupIndex = 1
          RadioItem = True
          OnClick = mnWlMsxClick
        end
        object mnWlDbpro: TMenuItem
          Tag = 1
          Caption = 'DarkBASIC pro'
          GroupIndex = 1
          RadioItem = True
          OnClick = mnWlMsxClick
        end
        object mnWlAgk: TMenuItem
          Tag = 2
          Caption = 'AGK'
          GroupIndex = 1
          RadioItem = True
          OnClick = mnWlMsxClick
        end
        object mnWlCpc: TMenuItem
          Tag = 3
          Caption = 'CPC'
          GroupIndex = 1
          RadioItem = True
          OnClick = mnWlMsxClick
        end
      end
      object Bin2Hex1: TMenuItem
        Caption = 'Bin2Hex'
        OnClick = Bin2Hex1Click
      end
      object mnRenban: TMenuItem
        Caption = 'Number setup'
        ShortCut = 41036
        OnClick = mnRenbanClick
      end
      object mnKeisan: TMenuItem
        Caption = 'Calc'
        ShortCut = 16459
        OnClick = mnKeisanClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object SQL1: TMenuItem
        Caption = '&SQL'
        OnClick = SQL1Click
      end
      object Commit1: TMenuItem
        Caption = 'Commit'
        ShortCut = 49219
        OnClick = Commit1Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object Next1: TMenuItem
        Caption = 'Next file'
        ShortCut = 117
        OnClick = Next1Click
      end
      object Back1: TMenuItem
        Caption = 'Previous file'
        ShortCut = 8309
        OnClick = Back1Click
      end
      object Maximize1: TMenuItem
        Caption = 'Maximize'
        ShortCut = 116
        OnClick = Maximize1Click
      end
      object mnWrap: TMenuItem
        Caption = 'Word wrap'
        ShortCut = 16471
        OnClick = mnWrapClick
      end
      object Font1: TMenuItem
        Caption = 'Font...'
        OnClick = Font1Click
      end
      object Background1: TMenuItem
        Caption = 'Backgound color...'
        OnClick = Background1Click
      end
      object N19: TMenuItem
        Caption = '-'
      end
      object mnCommand: TMenuItem
        Caption = 'Run'
        ShortCut = 120
        OnClick = mnCommandClick
      end
      object mnSettarget: TMenuItem
        Caption = 'Set target'
        OnClick = mnSettargetClick
      end
      object SourceASMorBAS1: TMenuItem
        Caption = 'View source'
        ShortCut = 32884
        OnClick = SourceASMorBAS1Click
      end
      object N6: TMenuItem
        Caption = 'Console'
        ShortCut = 32849
        OnClick = N6Click
      end
      object Browse1: TMenuItem
        Caption = 'Run emulator'
        ShortCut = 16453
        OnClick = Browse1Click
      end
      object mnDiskManager: TMenuItem
        Caption = 'Disk manager'
        ShortCut = 16452
        OnClick = mnDiskManagerClick
      end
      object mnTextPerl: TMenuItem
        Caption = 'Perl'
        ShortCut = 16504
        OnClick = mnTextPerlClick
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object mnOption: TMenuItem
        Caption = 'Option...'
        ShortCut = 16463
        OnClick = mnOptionClick
      end
      object MSXoption1: TMenuItem
        Caption = 'MSX, CPC setting...'
        ShortCut = 16461
        OnClick = MSXoption1Click
      end
      object DarkBasicsetting1: TMenuItem
        Caption = 'DarkBasic setting...'
        OnClick = DarkBasicsetting1Click
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object mnCtrlF1: TMenuItem
        Tag = 1
        Caption = '1'
        ShortCut = 16496
        OnClick = mnCtrlFxClick
      end
      object mnCtrlF2: TMenuItem
        Tag = 2
        Caption = '2'
        OnClick = mnCtrlFxClick
      end
      object mnCtrlF3: TMenuItem
        Tag = 3
        Caption = '3'
        OnClick = mnCtrlFxClick
      end
      object mnCtrlF4: TMenuItem
        Tag = 4
        Caption = '4'
        ShortCut = 16499
        OnClick = mnCtrlFxClick
      end
      object mnCtrlF5: TMenuItem
        Tag = 5
        Caption = '5'
        ShortCut = 16500
        OnClick = mnCtrlFxClick
      end
    end
    object mnTag: TMenuItem
      AutoHotkeys = maManual
      Caption = 'Ta&g'
      object N17: TMenuItem
        Caption = '-'
      end
      object mnAlt: TMenuItem
        Caption = 'Alt'
        object mnShiftAlt: TMenuItem
          Caption = 'Shift+'
          object mnShiftAlt1: TMenuItem
            Tag = 11
            OnClick = mnAltXClick
          end
          object mnShiftAlt2: TMenuItem
            Tag = 12
            OnClick = mnAltXClick
          end
          object mnShiftAlt3: TMenuItem
            Tag = 13
            OnClick = mnAltXClick
          end
          object mnShiftAlt4: TMenuItem
            Tag = 14
            OnClick = mnAltXClick
          end
          object mnShiftAlt5: TMenuItem
            Tag = 15
            OnClick = mnAltXClick
          end
          object mnShiftAlt6: TMenuItem
            Tag = 16
            OnClick = mnAltXClick
          end
          object mnShiftAlt7: TMenuItem
            Tag = 17
            OnClick = mnAltXClick
          end
          object mnShiftAlt8: TMenuItem
            Tag = 18
            OnClick = mnAltXClick
          end
          object mnShiftAlt9: TMenuItem
            Tag = 19
            OnClick = mnAltXClick
          end
          object mnShiftAlt0: TMenuItem
            Tag = 10
            OnClick = mnAltXClick
          end
        end
        object mnAlt1: TMenuItem
          Tag = 1
          OnClick = mnAltXClick
        end
        object mnAlt2: TMenuItem
          Tag = 2
          OnClick = mnAltXClick
        end
        object mnAlt3: TMenuItem
          Tag = 3
          OnClick = mnAltXClick
        end
        object mnAlt4: TMenuItem
          Tag = 4
          OnClick = mnAltXClick
        end
        object mnAlt5: TMenuItem
          Tag = 5
          OnClick = mnAltXClick
        end
        object mnAlt6: TMenuItem
          Tag = 6
          OnClick = mnAltXClick
        end
        object mnAlt7: TMenuItem
          Tag = 7
          OnClick = mnAltXClick
        end
        object mnAlt8: TMenuItem
          Tag = 8
          OnClick = mnAltXClick
        end
        object mnAlt9: TMenuItem
          Tag = 9
          OnClick = mnAltXClick
        end
        object mnAlt0: TMenuItem
          OnClick = mnAltXClick
        end
      end
      object Color1: TMenuItem
        Caption = 'Color'
        ShortCut = 41033
        OnClick = Color1Click
      end
      object copyy1: TMenuItem
        Caption = 'Copy y'
        OnClick = copyy1Click
      end
      object copyyz1: TMenuItem
        Tag = 1
        Caption = 'Copy yz'
        OnClick = copyy1Click
      end
      object N20: TMenuItem
        Caption = '-'
      end
      object mnTagAssign: TMenuItem
        Caption = 'Assign...'
        OnClick = mnTagAssignClick
      end
    end
    object menuCol: TMenuItem
      Caption = '0:0'
    end
    object menuModify: TMenuItem
    end
    object mnKnj: TMenuItem
      AutoHotkeys = maManual
      object SJIS1: TMenuItem
        Caption = 'SJIS'
        OnClick = mnKnj1Click
      end
      object EUC1: TMenuItem
        Caption = 'EUC'
        OnClick = mnKnj1Click
      end
      object JIS1: TMenuItem
        Caption = 'JIS'
        OnClick = mnKnj1Click
      end
      object UTF81: TMenuItem
        Caption = 'UTF8'
        OnClick = mnKnj1Click
      end
      object Unicode1: TMenuItem
        Caption = 'Unicode'
        OnClick = mnKnj1Click
      end
    end
    object Tool1: TMenuItem
      Caption = 'T&ools'
      object SpriteEditor1: TMenuItem
        Tag = 16
        Caption = 'Sprite Editor'
        OnClick = SpriteEditor1Click
      end
      object CharacterEditor1: TMenuItem
        Tag = 8
        Caption = 'Character Editor'
        OnClick = SpriteEditor1Click
      end
      object GraphicEditor: TMenuItem
        Caption = 'Graphic Editor'
        OnClick = GraphicEditorClick
      end
      object PaletteEditor1: TMenuItem
        Caption = 'Palette Manager'
        OnClick = PaletteEditor1Click
      end
      object SoundEditor1: TMenuItem
        Caption = 'Sound Editor'
        OnClick = SoundEditor1Click
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object SpriteDataGenerator1: TMenuItem
        Tag = 1
        Caption = 'Sprite Data Generator'
        OnClick = SpriteDataGenerator1Click
      end
      object CharactorDataGenerator1: TMenuItem
        Tag = 2
        Caption = 'Character Data Generator'
        OnClick = SpriteDataGenerator1Click
      end
      object GraphicDataGenerator1: TMenuItem
        Tag = 3
        Caption = 'Graphic Data Generator'
        OnClick = SpriteDataGenerator1Click
      end
      object N12: TMenuItem
        Caption = '-'
      end
      object ScreenEdit1: TMenuItem
        Caption = 'Screen Editor'
        OnClick = ScreenEdit1Click
      end
      object Bin2Bas1: TMenuItem
        Caption = 'Bin to Src'
        OnClick = Bin2Bas1Click
      end
      object HextobitbusterHex1: TMenuItem
        Caption = 'Hex to Bitbuster hex'
        OnClick = HextobitbusterHex1Click
      end
      object BinaryConcat1: TMenuItem
        Caption = 'Binary Concat'
        OnClick = BinaryConcat1Click
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object mnHelp: TMenuItem
        Caption = 'Help'
        OnClick = mnHelpClick
      end
      object mnClass: TMenuItem
        Caption = 'MSX class reference'
        OnClick = mnClassClick
      end
      object CPCclass1: TMenuItem
        Caption = 'CPC class reference'
        OnClick = CPCclass1Click
      end
      object mnMmlHelp: TMenuItem
        Caption = 'MML reference'
        OnClick = mnMmlHelpClick
      end
      object mnAbout: TMenuItem
        Caption = 'Version'
        OnClick = mnAboutClick
      end
    end
  end
  object FindDialog1: TFindDialog
    Options = [frDown, frHideWholeWord]
    OnFind = FindDialog1Find
    Left = 120
    Top = 40
  end
  object ReplaceDialog1: TReplaceDialog
    Options = [frDown, frHideWholeWord]
    OnFind = ReplaceDialog1Find
    OnReplace = ReplaceDialog1Replace
    Left = 152
    Top = 40
  end
  object PopupMenu1: TPopupMenu
    Left = 56
    Top = 40
    object C1: TMenuItem
      Caption = '&Close'
      OnClick = Close1Click
    end
    object popHidetopbuttons: TMenuItem
      Caption = '&Hide top buttons'
      OnClick = popHidetopbuttonsClick
    end
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 24
    Top = 72
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bas'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 56
    Top = 72
  end
end
