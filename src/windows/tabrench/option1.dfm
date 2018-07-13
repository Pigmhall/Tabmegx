object FrmOption: TFrmOption
  Left = 86
  Top = 99
  BorderStyle = bsDialog
  Caption = 'Option'
  ClientHeight = 435
  ClientWidth = 227
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 24
  object Label1: TLabel
    Left = 8
    Top = 32
    Width = 48
    Height = 24
    Caption = 'Width'
  end
  object Label2: TLabel
    Left = 8
    Top = 72
    Width = 55
    Height = 24
    Caption = 'Height'
  end
  object Label3: TLabel
    Left = 8
    Top = 128
    Width = 66
    Height = 24
    Caption = 'Dot size'
  end
  object LblWindow: TLabel
    Left = 8
    Top = 288
    Width = 115
    Height = 24
    Caption = 'Window Size:'
  end
  object Label4: TLabel
    Left = 8
    Top = 168
    Width = 48
    Height = 24
    Caption = 'Width'
  end
  object Label5: TLabel
    Left = 8
    Top = 208
    Width = 55
    Height = 24
    Caption = 'Height'
  end
  object Label6: TLabel
    Left = 8
    Top = 8
    Width = 78
    Height = 13
    Caption = 'Default size'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 8
    Top = 106
    Width = 47
    Height = 13
    Caption = 'Screen'
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 8
    Top = 248
    Width = 53
    Height = 24
    Caption = 'Button'
  end
  object Label9: TLabel
    Left = 127
    Top = 248
    Width = 14
    Height = 24
    Caption = 'X'
  end
  object EdtWidth: TEdit
    Left = 70
    Top = 29
    Width = 121
    Height = 32
    TabOrder = 0
    Text = 'EdtWidth'
  end
  object EdtHeight: TEdit
    Left = 70
    Top = 69
    Width = 121
    Height = 32
    TabOrder = 1
    Text = 'EdtHeight'
  end
  object EdtDotSize: TEdit
    Left = 94
    Top = 125
    Width = 121
    Height = 32
    TabOrder = 2
    Text = 'EdtDotSize'
    OnChange = EdtWidthChange
  end
  object Button1: TButton
    Left = 11
    Top = 385
    Width = 97
    Height = 41
    Caption = 'OK'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 115
    Top = 385
    Width = 97
    Height = 41
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = Button2Click
  end
  object chk256: TCheckBox
    Left = 8
    Top = 320
    Width = 177
    Height = 17
    Caption = 'Save as 256(Win)'
    TabOrder = 5
  end
  object chkPng: TCheckBox
    Left = 8
    Top = 352
    Width = 177
    Height = 17
    Caption = 'Save as PNG'
    TabOrder = 6
  end
  object EdtWidth2: TEdit
    Left = 70
    Top = 165
    Width = 121
    Height = 32
    TabOrder = 7
    Text = 'EdtWidth'
    OnChange = EdtWidthChange
  end
  object EdtHeight2: TEdit
    Left = 70
    Top = 205
    Width = 121
    Height = 32
    TabOrder = 8
    Text = 'EdtHeight2'
    OnChange = EdtWidthChange
  end
  object EdtButtonW: TEdit
    Left = 72
    Top = 245
    Width = 49
    Height = 32
    TabOrder = 9
    Text = 'EdtDotSize'
    OnChange = EdtWidthChange
  end
  object EdtButtonH: TEdit
    Left = 144
    Top = 245
    Width = 49
    Height = 32
    TabOrder = 10
    Text = 'EdtDotSize'
    OnChange = EdtWidthChange
  end
end
