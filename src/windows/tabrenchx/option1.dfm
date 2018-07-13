object FrmOption: TFrmOption
  Left = 196
  Top = 107
  BorderStyle = bsDialog
  Caption = 'Option'
  ClientHeight = 273
  ClientWidth = 231
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 18
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 40
    Height = 18
    Caption = 'Width'
  end
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 45
    Height = 18
    Caption = 'Height'
  end
  object Label3: TLabel
    Left = 8
    Top = 96
    Width = 57
    Height = 18
    Caption = 'Dot size'
  end
  object LblWindow: TLabel
    Left = 8
    Top = 136
    Width = 95
    Height = 18
    Caption = 'Window Size:'
  end
  object EdtWidth: TEdit
    Left = 70
    Top = 13
    Width = 121
    Height = 26
    TabOrder = 0
    Text = 'EdtWidth'
    OnChange = EdtWidthChange
  end
  object EdtHeight: TEdit
    Left = 70
    Top = 53
    Width = 121
    Height = 26
    TabOrder = 1
    Text = 'EdtHeight'
    OnChange = EdtWidthChange
  end
  object EdtDotSize: TEdit
    Left = 94
    Top = 93
    Width = 121
    Height = 26
    TabOrder = 2
    Text = 'EdtDotSize'
    OnChange = EdtWidthChange
  end
  object Button1: TButton
    Left = 16
    Top = 208
    Width = 97
    Height = 41
    Caption = 'OK'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 208
    Width = 97
    Height = 41
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = Button2Click
  end
  object chk256: TCheckBox
    Left = 16
    Top = 176
    Width = 177
    Height = 17
    Caption = 'Save as 256 colors'
    TabOrder = 5
  end
end
