//---------------------------------------------------------------------------

#ifndef ReactorH
#define ReactorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <NIDAQmx.h>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrontreactor : public TForm
{
__published:	// IDE-managed Components
	TButton *StartInput;
	TButton *StartReaction;
	TChart *Chart1;
	TLineSeries *Series1;
	TLabeledEdit *Pump1Vol;
	TButton *Reset;
	TLabeledEdit *Pump1Steps;
	TLabeledEdit *Pump1TotSt;
	TLabeledEdit *SampleIntervall;
	TLabeledEdit *Duration;
	TLabeledEdit *Pump2Vol;
	TLabeledEdit *Pump3Vol;
	TLabeledEdit *Pump2Steps;
	TLabeledEdit *Pump3Steps;
	TLabeledEdit *Pump2TotSt;
	TLabeledEdit *Pump3TotSt;
	TLabeledEdit *Status;
	TProgressBar *ProgressBar1;
	TProgressBar *ProgressBar2;
	TProgressBar *ProgressBar3;
	TProgressBar *ProgressBar4;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Pump3Progress;
	void __fastcall ResetClick(TObject *Sender);
	void __fastcall StartInputClick(TObject *Sender);
	void __fastcall StartReactionClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
unsigned long reg;
 unsigned long control_bits;
 struct pump_info {int huebe, aktuelle_huebe, interval_ms, pump_bit; float vol, hub_vol;};
 struct pump_info all_pump_info[4];
 struct measure_params{int duration, samples; float sample_intervall;};
 struct measure_params scan_params; typedef TProgressBar* TProgressBars; TProgressBars PBars[3] = {ProgressBar1,ProgressBar2,ProgressBar3};

	__fastcall TFrontreactor(TComponent* Owner);
	float __fastcall TFrontreactor::measure(TObject *Sender);

};
//---------------------------------------------------------------------------
extern TEvent *PumpEvent[4];
extern PACKAGE TFrontreactor *Frontreactor;
extern TaskHandle taskHandle_DO;
extern TaskHandle taskHandle_DO_P;
//---------------------------------------------------------------------------
#endif
