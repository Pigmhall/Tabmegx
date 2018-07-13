object frmData: TfrmData
  Left = 285
  Top = 182
  BorderStyle = bsDialog
  Caption = 'Data'
  ClientHeight = 195
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 24
  object Label1: TLabel
    Left = 8
    Top = 20
    Width = 43
    Height = 24
    Caption = 'Type'
  end
  object lblParam1: TLabel
    Left = 8
    Top = 61
    Width = 63
    Height = 24
    Caption = 'param1'
  end
  object lblRange1: TLabel
    Left = 193
    Top = 61
    Width = 61
    Height = 24
    Caption = '0~4095'
  end
  object lblParam2: TLabel
    Left = 8
    Top = 99
    Width = 63
    Height = 24
    Caption = 'param2'
  end
  object lblRange2: TLabel
    Left = 193
    Top = 99
    Width = 61
    Height = 24
    Caption = '0~4095'
  end
  object lblParam3: TLabel
    Left = 8
    Top = 138
    Width = 63
    Height = 24
    Caption = 'param3'
  end
  object lblRange3: TLabel
    Left = 193
    Top = 138
    Width = 61
    Height = 24
    Caption = '0~4095'
  end
  object btnOk: TButton
    Left = 153
    Top = 144
    Width = 75
    Height = 41
    Caption = 'Ok'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 233
    Top = 144
    Width = 75
    Height = 41
    Caption = 'Cancel'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object cmbType: TComboBox
    Left = 81
    Top = 16
    Width = 105
    Height = 32
    Style = csDropDownList
    ItemHeight = 24
    TabOrder = 2
    OnChange = cmbTypeChange
    Items.Strings = (
      'Volume'
      'Tone'
      'Noise'
      'Tone+'
      'Volume+'
      'Wait'
      'Loop'
      'Register')
  end
  object edtParam1: TEdit
    Left = 81
    Top = 57
    Width = 105
    Height = 32
    TabOrder = 3
    Text = 'edtParam1'
  end
  object edtParam2: TEdit
    Left = 81
    Top = 95
    Width = 105
    Height = 32
    TabOrder = 4
    Text = 'Edit1'
  end
  object edtParam3: TEdit
    Left = 81
    Top = 134
    Width = 105
    Height = 32
    TabOrder = 5
    Text = 'Edit1'
  end
end
