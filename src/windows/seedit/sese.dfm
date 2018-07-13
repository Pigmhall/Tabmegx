object FrmSeSet: TFrmSeSet
  Left = 288
  Top = 249
  BorderStyle = bsDialog
  Caption = 'SE property'
  ClientHeight = 139
  ClientWidth = 264
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
    Top = 10
    Width = 51
    Height = 24
    Caption = 'Name'
  end
  object ChkNoise: TCheckBox
    Left = 16
    Top = 50
    Width = 97
    Height = 17
    Caption = 'Noise on'
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 96
    Top = 89
    Width = 75
    Height = 41
    Caption = 'Ok'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 180
    Top = 89
    Width = 75
    Height = 41
    Caption = 'Cancel'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object EdtName: TEdit
    Left = 72
    Top = 8
    Width = 169
    Height = 32
    TabOrder = 3
    Text = 'EdtName'
  end
end
