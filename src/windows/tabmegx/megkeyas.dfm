object FrmKeyas: TFrmKeyas
  Left = 204
  Top = 219
  BorderStyle = bsToolWindow
  Caption = 'Assign'
  ClientHeight = 341
  ClientWidth = 444
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 11
    Top = 24
    Width = 27
    Height = 12
    Caption = 'Alt+1'
  end
  object Label2: TLabel
    Left = 247
    Top = 0
    Width = 30
    Height = 12
    Caption = 'Shift+'
  end
  object Label3: TLabel
    Left = 11
    Top = 50
    Width = 27
    Height = 12
    Caption = 'Alt+2'
  end
  object Label4: TLabel
    Left = 11
    Top = 76
    Width = 27
    Height = 12
    Caption = 'Alt+3'
  end
  object Label5: TLabel
    Left = 11
    Top = 102
    Width = 27
    Height = 12
    Caption = 'Alt+4'
  end
  object Label6: TLabel
    Left = 11
    Top = 128
    Width = 27
    Height = 12
    Caption = 'Alt+5'
  end
  object Label7: TLabel
    Left = 11
    Top = 154
    Width = 27
    Height = 12
    Caption = 'Alt+6'
  end
  object Label8: TLabel
    Left = 11
    Top = 180
    Width = 27
    Height = 12
    Caption = 'Alt+7'
  end
  object Label9: TLabel
    Left = 11
    Top = 206
    Width = 27
    Height = 12
    Caption = 'Alt+8'
  end
  object Label10: TLabel
    Left = 11
    Top = 232
    Width = 27
    Height = 12
    Caption = 'Alt+9'
  end
  object Label11: TLabel
    Left = 11
    Top = 258
    Width = 27
    Height = 12
    Caption = 'Alt+0'
  end
  object Label12: TLabel
    Left = 13
    Top = 288
    Width = 21
    Height = 12
    Caption = 'Alt+'
  end
  object EdtCtrl1: TEdit
    Left = 51
    Top = 20
    Width = 182
    Height = 20
    TabOrder = 0
  end
  object EdtSCtrl1: TEdit
    Left = 244
    Top = 19
    Width = 191
    Height = 20
    TabOrder = 1
  end
  object EdtSCtrl2: TEdit
    Left = 244
    Top = 45
    Width = 191
    Height = 20
    TabOrder = 3
  end
  object EdtCtrl2: TEdit
    Left = 51
    Top = 46
    Width = 182
    Height = 20
    TabOrder = 2
  end
  object EdtSCtrl3: TEdit
    Left = 244
    Top = 71
    Width = 191
    Height = 20
    TabOrder = 5
  end
  object EdtCtrl3: TEdit
    Left = 51
    Top = 72
    Width = 182
    Height = 20
    TabOrder = 4
  end
  object EdtSCtrl4: TEdit
    Left = 244
    Top = 97
    Width = 191
    Height = 20
    TabOrder = 7
  end
  object EdtCtrl4: TEdit
    Left = 51
    Top = 98
    Width = 182
    Height = 20
    TabOrder = 6
  end
  object EdtSCtrl5: TEdit
    Left = 244
    Top = 123
    Width = 191
    Height = 20
    TabOrder = 9
  end
  object EdtCtrl5: TEdit
    Left = 51
    Top = 124
    Width = 182
    Height = 20
    TabOrder = 8
  end
  object EdtSCtrl6: TEdit
    Left = 244
    Top = 149
    Width = 191
    Height = 20
    TabOrder = 11
  end
  object EdtCtrl6: TEdit
    Left = 51
    Top = 150
    Width = 182
    Height = 20
    TabOrder = 10
  end
  object EdtSCtrl7: TEdit
    Left = 244
    Top = 175
    Width = 191
    Height = 20
    TabOrder = 13
  end
  object EdtCtrl7: TEdit
    Left = 51
    Top = 176
    Width = 182
    Height = 20
    TabOrder = 12
  end
  object EdtSCtrl8: TEdit
    Left = 244
    Top = 201
    Width = 191
    Height = 20
    TabOrder = 15
  end
  object EdtCtrl8: TEdit
    Left = 51
    Top = 202
    Width = 182
    Height = 20
    TabOrder = 14
  end
  object EdtSCtrl9: TEdit
    Left = 244
    Top = 227
    Width = 191
    Height = 20
    TabOrder = 17
  end
  object EdtCtrl9: TEdit
    Left = 51
    Top = 228
    Width = 182
    Height = 20
    TabOrder = 16
  end
  object EdtSCtrl0: TEdit
    Left = 244
    Top = 253
    Width = 191
    Height = 20
    TabOrder = 19
  end
  object EdtCtrl0: TEdit
    Left = 51
    Top = 254
    Width = 182
    Height = 20
    TabOrder = 18
  end
  object Button1: TButton
    Tag = 1
    Left = 223
    Top = 311
    Width = 66
    Height = 23
    Caption = '&OK'
    TabOrder = 24
    OnClick = Button1Click
  end
  object Button2: TButton
    Tag = 1
    Left = 294
    Top = 311
    Width = 67
    Height = 23
    Caption = '&Cancel'
    TabOrder = 25
    OnClick = Button2Click
  end
  object ComboBox1: TComboBox
    Tag = 1
    Left = 42
    Top = 284
    Width = 42
    Height = 20
    AutoComplete = False
    Style = csDropDownList
    ItemHeight = 12
    TabOrder = 20
    OnChange = ComboBox1Change
    Items.Strings = (
      'A'
      'B'
      'C'
      'D'
      'F'
      'H'
      'J'
      'K'
      'M'
      'N'
      'O'
      'P'
      'R'
      'T'
      'U'
      'W'
      'X'
      'Y'
      'Z')
  end
  object EdtAltX: TEdit
    Left = 90
    Top = 283
    Width = 142
    Height = 20
    TabOrder = 21
  end
  object Button3: TButton
    Tag = 1
    Left = 392
    Top = 282
    Width = 43
    Height = 21
    Caption = 'Apply'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    ParentFont = False
    TabOrder = 23
    OnClick = Button3Click
  end
  object EdtShiftAltX: TEdit
    Left = 242
    Top = 282
    Width = 147
    Height = 20
    TabOrder = 22
  end
  object BtnHtml: TButton
    Tag = 1
    Left = 49
    Top = 310
    Width = 71
    Height = 15
    Caption = 'HTML Preset'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    ParentFont = False
    TabOrder = 26
    OnClick = BtnHtmlClick
  end
  object Button4: TButton
    Tag = 1
    Left = 366
    Top = 311
    Width = 67
    Height = 23
    Caption = '&Help'
    TabOrder = 27
    OnClick = Button4Click
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 144
    Top = 290
    object N1: TMenuItem
      Caption = 'Special String'
      object n2: TMenuItem
        Caption = '\n(return)'
        OnClick = mnStrSp
      end
      object t1: TMenuItem
        Tag = 1
        Caption = '\t(tab)'
        OnClick = mnStrSp
      end
      object v1: TMenuItem
        Tag = 2
        Caption = '\v(|)'
        OnClick = mnStrSp
      end
      object CLIP1: TMenuItem
        Tag = 3
        Caption = '%CLIP%(clipboard)'
        OnClick = mnStrSp
      end
      object N3: TMenuItem
        Tag = 4
        Caption = '%SELTEXT%(selected text)'
        OnClick = mnStrSp
      end
      object INPUT1: TMenuItem
        Tag = 5
        Caption = '%INPUT%(input box)'
        OnClick = mnStrSp
      end
      object DATE1: TMenuItem
        Tag = 6
        Caption = '%DATE%(today)'
        OnClick = mnStrSp
      end
      object TIME1: TMenuItem
        Tag = 7
        Caption = '%TIME%(now)'
        OnClick = mnStrSp
      end
    end
  end
end
