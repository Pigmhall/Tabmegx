object FrmCoord: TFrmCoord
  Left = 359
  Top = 342
  BorderStyle = bsDialog
  Caption = 'Option'
  ClientHeight = 178
  ClientWidth = 325
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
    Top = 8
    Width = 99
    Height = 24
    Caption = 'Screen size'
  end
  object Label2: TLabel
    Left = 8
    Top = 64
    Width = 80
    Height = 24
    Caption = 'View size'
  end
  object Label3: TLabel
    Left = 215
    Top = 12
    Width = 14
    Height = 24
    Caption = 'X'
  end
  object Label4: TLabel
    Left = 215
    Top = 68
    Width = 14
    Height = 24
    Caption = 'X'
  end
  object EdtWidth: TEdit
    Left = 147
    Top = 8
    Width = 62
    Height = 32
    TabOrder = 0
  end
  object EdtHeight: TEdit
    Left = 235
    Top = 8
    Width = 62
    Height = 32
    TabOrder = 1
  end
  object Button1: TButton
    Left = 114
    Top = 111
    Width = 79
    Height = 50
    Caption = 'OK'
    TabOrder = 2
    OnClick = Button1Click
  end
  object EdtSwx: TEdit
    Left = 147
    Top = 64
    Width = 62
    Height = 32
    TabOrder = 3
  end
  object EdtSwy: TEdit
    Left = 235
    Top = 64
    Width = 62
    Height = 32
    TabOrder = 4
  end
end
