object frmP8: TfrmP8
  Left = 431
  Top = 267
  BorderStyle = bsToolWindow
  Caption = 'p8tbl'
  ClientHeight = 167
  ClientWidth = 380
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 12
  object spnum: TLabel
    Left = 0
    Top = 3
    Width = 33
    Height = 12
    Caption = 'spnum'
  end
  object Label1: TLabel
    Left = 3
    Top = 153
    Width = 14
    Height = 12
    Caption = 'Ok'
  end
  object Memo1: TMemo
    Left = 0
    Top = 32
    Width = 137
    Height = 113
    TabOrder = 0
    Visible = False
    WordWrap = False
  end
  object edtSpn: TEdit
    Left = 32
    Top = 0
    Width = 49
    Height = 20
    TabOrder = 1
    Text = '0'
  end
  object Set: TButton
    Left = 88
    Top = 0
    Width = 41
    Height = 25
    Caption = 'Set'
    TabOrder = 2
    OnClick = SetClick
  end
  object Button1: TButton
    Left = 155
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Paste'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 230
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Copy'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 305
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 5
    OnClick = Button3Click
  end
end
