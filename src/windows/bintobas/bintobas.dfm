object Form1: TForm1
  Left = 221
  Top = 118
  Width = 529
  Height = 283
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'bin to src'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 20
  object Memo1: TMemo
    Left = 0
    Top = 51
    Width = 521
    Height = 205
    Align = alClient
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    WordWrap = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 521
    Height = 51
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 82
      Top = 7
      Width = 49
      Height = 20
      Caption = 'Return'
    end
    object Label2: TLabel
      Left = 199
      Top = 6
      Width = 51
      Height = 20
      Caption = 'Format'
    end
    object Button1: TButton
      Left = 3
      Top = 3
      Width = 75
      Height = 44
      Caption = 'Open'
      TabOrder = 0
      OnClick = Button1Click
    end
    object edtNum: TEdit
      Left = 136
      Top = 8
      Width = 49
      Height = 28
      TabOrder = 1
      Text = '64'
    end
    object RadioButton1: TRadioButton
      Left = 258
      Top = 8
      Width = 73
      Height = 17
      Caption = 'BASIC'
      Checked = True
      TabOrder = 2
      TabStop = True
    end
    object chkCcz80: TRadioButton
      Left = 259
      Top = 27
      Width = 73
      Height = 17
      Caption = 'ccZ80'
      TabOrder = 3
    end
    object Button2: TButton
      Left = 443
      Top = 2
      Width = 75
      Height = 44
      Caption = 'Quit'
      TabOrder = 4
      OnClick = Button2Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 160
    Top = 184
  end
end
