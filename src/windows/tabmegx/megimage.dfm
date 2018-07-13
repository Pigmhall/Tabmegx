object FrmImage: TFrmImage
  Left = 275
  Top = 291
  Width = 447
  Height = 315
  BorderStyle = bsSizeToolWin
  Caption = 'Img'
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 21
  object Label1: TLabel
    Left = 184
    Top = 4
    Width = 121
    Height = 21
    Caption = #30456#23550#65411#65438#65384#65434#65400#65412#65432
  end
  object ListBox1: TListBox
    Left = 0
    Top = 0
    Width = 169
    Height = 249
    ItemHeight = 21
    TabOrder = 0
    OnClick = ListBox1Click
    OnDblClick = ListBox1DblClick
    OnKeyDown = ListBox1KeyDown
    OnKeyPress = ListBox1KeyPress
  end
  object Edit1: TEdit
    Left = 253
    Top = 0
    Width = 112
    Height = 29
    TabOrder = 1
    OnKeyDown = Edit1KeyDown
  end
  object ScrollBox1: TScrollBox
    Left = 176
    Top = 28
    Width = 262
    Height = 254
    TabOrder = 2
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 81
      Height = 81
      Stretch = True
    end
  end
  object FileListBox1: TFileListBox
    Left = 136
    Top = 96
    Width = 81
    Height = 41
    ItemHeight = 21
    TabOrder = 3
    Visible = False
  end
  object Button1: TButton
    Left = 0
    Top = 254
    Width = 41
    Height = 33
    Caption = #8593
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 41
    Top = 254
    Width = 41
    Height = 33
    Caption = #8595
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 82
    Top = 254
    Width = 41
    Height = 33
    Caption = 'OK'
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 123
    Top = 254
    Width = 41
    Height = 33
    Caption = #215
    TabOrder = 7
    OnClick = Button4Click
  end
end
