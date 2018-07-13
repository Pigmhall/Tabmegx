object FrmNumber: TFrmNumber
  Left = 229
  Top = 197
  BorderStyle = bsDialog
  Caption = 'Number'
  ClientHeight = 85
  ClientWidth = 156
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 6
    Top = 6
    Width = 6
    Height = 12
    Caption = '1'
  end
  object Edit1: TEdit
    Left = 5
    Top = 24
    Width = 117
    Height = 20
    TabOrder = 0
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 41
    Top = 51
    Width = 50
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 97
    Top = 51
    Width = 50
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = Button2Click
  end
end
