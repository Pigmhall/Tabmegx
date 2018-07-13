object frmColor: TfrmColor
  Left = 248
  Top = 171
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'color'
  ClientHeight = 233
  ClientWidth = 373
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
  object lblR: TLabel
    Left = 8
    Top = 22
    Width = 13
    Height = 21
    Caption = 'R'
  end
  object lblG: TLabel
    Left = 8
    Top = 70
    Width = 14
    Height = 21
    Caption = 'G'
  end
  object lblB: TLabel
    Left = 8
    Top = 118
    Width = 13
    Height = 21
    Caption = 'B'
  end
  object Image1: TImage
    Left = 24
    Top = 160
    Width = 57
    Height = 57
  end
  object tbR: TTrackBar
    Left = 64
    Top = 16
    Width = 289
    Height = 41
    Max = 7
    Orientation = trHorizontal
    PageSize = 1
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TabStop = False
    ThumbLength = 30
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = tbRChange
  end
  object tbG: TTrackBar
    Left = 64
    Top = 64
    Width = 289
    Height = 41
    Max = 7
    Orientation = trHorizontal
    PageSize = 1
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 1
    TabStop = False
    ThumbLength = 30
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = tbRChange
  end
  object tbB: TTrackBar
    Left = 64
    Top = 112
    Width = 289
    Height = 41
    Max = 7
    Orientation = trHorizontal
    PageSize = 1
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 2
    TabStop = False
    ThumbLength = 30
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = tbRChange
  end
  object OK: TButton
    Left = 160
    Top = 168
    Width = 75
    Height = 49
    Caption = 'OK'
    TabOrder = 3
    OnClick = OKClick
  end
  object Button1: TButton
    Left = 272
    Top = 167
    Width = 75
    Height = 50
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = Button1Click
  end
end
