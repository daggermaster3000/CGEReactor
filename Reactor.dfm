object Frontreactor: TFrontreactor
  Left = 0
  Top = 0
  Caption = 'Frontreactor'
  ClientHeight = 800
  ClientWidth = 871
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 616
    Top = 192
    Width = 110
    Height = 13
    Caption = 'Measurement Progress'
  end
  object Label2: TLabel
    Left = 376
    Top = 69
    Width = 77
    Height = 13
    Caption = 'Pump1 Progress'
  end
  object Label3: TLabel
    Left = 376
    Top = 133
    Width = 77
    Height = 13
    Caption = 'Pump2 Progress'
  end
  object Pump3Progress: TLabel
    Left = 376
    Top = 197
    Width = 77
    Height = 13
    Caption = 'Pump3 Progress'
  end
  object StartInput: TButton
    Left = 8
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Start input'
    TabOrder = 0
    OnClick = StartInputClick
  end
  object StartReaction: TButton
    Left = 128
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Start reaction'
    TabOrder = 1
    OnClick = StartReactionClick
  end
  object Chart1: TChart
    Left = 8
    Top = 272
    Width = 848
    Height = 520
    Title.Font.Color = clBlack
    Title.Font.Height = -19
    Title.Font.Emboss.HorizSize = 16
    Title.Font.Emboss.VertSize = 16
    Title.Text.Strings = (
      'Redox potential')
    BottomAxis.Axis.Width = 0
    BottomAxis.Title.Caption = 'Time [s]'
    LeftAxis.Axis.Width = 0
    LeftAxis.Title.Caption = '[V]'
    LeftAxis.Title.Pen.Width = 21
    View3D = False
    View3DOptions.Orthogonal = False
    TabOrder = 2
    DefaultCanvas = 'TTeeCanvas3D'
    PrintMargins = (
      15
      26
      15
      26)
    ColorPaletteIndex = 1
    object Series1: TLineSeries
      SeriesColor = clBlue
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object Pump1Vol: TLabeledEdit
    Left = 8
    Top = 88
    Width = 75
    Height = 21
    EditLabel.Width = 46
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump1Vol'
    TabOrder = 3
  end
  object Reset: TButton
    Left = 264
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Reset'
    TabOrder = 4
    OnClick = ResetClick
  end
  object Pump1Steps: TLabeledEdit
    Left = 128
    Top = 88
    Width = 75
    Height = 21
    EditLabel.Width = 59
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump1Steps'
    TabOrder = 5
  end
  object Pump1TotSt: TLabeledEdit
    Left = 264
    Top = 88
    Width = 75
    Height = 21
    EditLabel.Width = 58
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump1TotSt'
    TabOrder = 6
  end
  object SampleIntervall: TLabeledEdit
    Left = 616
    Top = 88
    Width = 96
    Height = 21
    EditLabel.Width = 74
    EditLabel.Height = 13
    EditLabel.Caption = 'SampleIntervall'
    TabOrder = 7
  end
  object Duration: TLabeledEdit
    Left = 799
    Top = 88
    Width = 57
    Height = 21
    EditLabel.Width = 41
    EditLabel.Height = 13
    EditLabel.Caption = 'Duration'
    TabOrder = 8
  end
  object Pump2Vol: TLabeledEdit
    Left = 8
    Top = 152
    Width = 75
    Height = 21
    EditLabel.Width = 46
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump2Vol'
    TabOrder = 9
  end
  object Pump3Vol: TLabeledEdit
    Left = 8
    Top = 216
    Width = 75
    Height = 21
    EditLabel.Width = 46
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump3Vol'
    TabOrder = 10
  end
  object Pump2Steps: TLabeledEdit
    Left = 128
    Top = 152
    Width = 75
    Height = 21
    EditLabel.Width = 59
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump2Steps'
    TabOrder = 11
  end
  object Pump3Steps: TLabeledEdit
    Left = 128
    Top = 216
    Width = 75
    Height = 21
    EditLabel.Width = 59
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump3Steps'
    TabOrder = 12
  end
  object Pump2TotSt: TLabeledEdit
    Left = 264
    Top = 152
    Width = 75
    Height = 21
    EditLabel.Width = 58
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump2TotSt'
    TabOrder = 13
  end
  object Pump3TotSt: TLabeledEdit
    Left = 264
    Top = 216
    Width = 75
    Height = 21
    EditLabel.Width = 58
    EditLabel.Height = 13
    EditLabel.Caption = 'Pump3TotSt'
    TabOrder = 14
  end
  object Status: TLabeledEdit
    Left = 616
    Top = 152
    Width = 96
    Height = 21
    EditLabel.Width = 31
    EditLabel.Height = 13
    EditLabel.Caption = 'Status'
    TabOrder = 15
  end
  object ProgressBar1: TProgressBar
    Left = 376
    Top = 88
    Width = 209
    Height = 21
    BarColor = clBlue
    TabOrder = 16
  end
  object ProgressBar2: TProgressBar
    Left = 376
    Top = 152
    Width = 209
    Height = 21
    BarColor = clBlue
    TabOrder = 17
  end
  object ProgressBar3: TProgressBar
    Left = 376
    Top = 216
    Width = 209
    Height = 21
    BarColor = clBlue
    TabOrder = 18
  end
  object ProgressBar4: TProgressBar
    Left = 616
    Top = 216
    Width = 240
    Height = 21
    BarColor = clLime
    TabOrder = 19
  end
end
