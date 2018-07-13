object frmPrin: TfrmPrin
  Left = 261
  Top = 146
  BorderStyle = bsDialog
  Caption = 'Print'
  ClientHeight = 81
  ClientWidth = 204
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'MS UI Gothic'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 21
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 185
    Height = 29
    TabOrder = 0
    Text = 'Edit1'
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 48
    Top = 40
    Width = 75
    Height = 41
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
end
