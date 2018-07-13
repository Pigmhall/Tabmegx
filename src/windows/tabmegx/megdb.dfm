object frmDb: TfrmDb
  Left = 314
  Top = 256
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'DarkBasic settings'
  ClientHeight = 124
  ClientWidth = 443
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label19: TLabel
    Left = 8
    Top = 14
    Width = 125
    Height = 16
    Caption = 'DarkBASIC pro dir'
  end
  object Label7: TLabel
    Left = 8
    Top = 48
    Width = 53
    Height = 16
    Caption = 'AGK dir'
  end
  object btnDBProDir: TButton
    Left = 400
    Top = 10
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 1
    OnClick = btnDBProDirClick
  end
  object btnAgkDir: TButton
    Left = 400
    Top = 44
    Width = 33
    Height = 30
    Caption = '...'
    TabOrder = 3
    OnClick = btnAgkDirClick
  end
  object edtAgkDir: TEdit
    Left = 120
    Top = 44
    Width = 281
    Height = 28
    TabOrder = 2
  end
  object edtDbproDir: TEdit
    Left = 144
    Top = 10
    Width = 257
    Height = 28
    TabOrder = 0
  end
  object Button1: TButton
    Left = 265
    Top = 84
    Width = 81
    Height = 33
    Caption = '&OK'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 353
    Top = 84
    Width = 81
    Height = 33
    Caption = '&Cancel'
    TabOrder = 5
    OnClick = Button2Click
  end
end
