object frmNew: TfrmNew
  Left = 192
  Top = 107
  BorderStyle = bsDialog
  Caption = 'New'
  ClientHeight = 99
  ClientWidth = 234
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 24
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 217
    Height = 32
    TabOrder = 0
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 8
    Top = 48
    Width = 75
    Height = 41
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 88
    Top = 48
    Width = 75
    Height = 41
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = Button2Click
  end
end
