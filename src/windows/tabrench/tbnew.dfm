object frmNew: TfrmNew
  Left = 297
  Top = 163
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'New'
  ClientHeight = 201
  ClientWidth = 273
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 21
  object Label1: TLabel
    Left = 12
    Top = 28
    Width = 48
    Height = 21
    Caption = 'Width'
  end
  object Label2: TLabel
    Left = 8
    Top = 76
    Width = 56
    Height = 21
    Caption = 'Height'
  end
  object edtW: TEdit
    Left = 80
    Top = 24
    Width = 73
    Height = 29
    TabOrder = 0
    Text = '8'
  end
  object edtH: TEdit
    Left = 80
    Top = 72
    Width = 73
    Height = 29
    TabOrder = 1
    Text = '8'
  end
  object udW: TUpDown
    Left = 153
    Top = 24
    Width = 104
    Height = 29
    Associate = edtW
    Min = 8
    Max = 128
    Increment = 8
    Orientation = udHorizontal
    Position = 8
    TabOrder = 2
    Wrap = False
  end
  object udH: TUpDown
    Left = 153
    Top = 72
    Width = 104
    Height = 29
    Associate = edtH
    Min = 8
    Max = 128
    Increment = 8
    Orientation = udHorizontal
    Position = 8
    TabOrder = 3
    Wrap = False
  end
  object Button1: TButton
    Left = 144
    Top = 127
    Width = 75
    Height = 50
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = Button1Click
  end
  object OK: TButton
    Left = 48
    Top = 128
    Width = 75
    Height = 49
    Caption = 'OK'
    TabOrder = 5
    OnClick = OKClick
  end
end
