//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <NIDAQmx.h>
#include "RinseThread.h"
#include "PumpThreads.h"
#include "MeasureThread.h"

#include "Reactor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrontreactor *Frontreactor;

//Add threads here...
RinseThread *Rinse;
PumpThreads *Pump1;
PumpThreads *Pump2;
PumpThreads *Pump3;

MeasureThread *Measure;

TEvent *PumpEvent[4];
//Declare NIDAQ stuff
TaskHandle taskHandle_DO=0;
TaskHandle taskHandle_DO_P=0;
TaskHandle taskHandle_AI=0;

// Declare structures for our pumps
struct pump_info {int huebe, aktuelle_huebe, interval_ms, pump_bit;float vol, hub_vol;};
struct measure_params{int duration, samples; float sample_intervall;};



//---------------------------------------------------------------------------
__fastcall TFrontreactor::TFrontreactor(TComponent* Owner)
	: TForm(Owner)
{
int pump_id;

/*init the NIDAQ interfaces  */

DAQmxCreateTask("",&taskHandle_DO);
//Create digital output channels;
DAQmxCreateDOChan(taskHandle_DO,"Dev1/port0/line0:4","",DAQmx_Val_ChanForAllLines);
DAQmxStartTask(taskHandle_DO);
DAQmxCreateTask("",&taskHandle_DO_P);
DAQmxCreateDOChan(taskHandle_DO_P,"Dev1/port0/line5:7","",DAQmx_Val_ChanForAllLines);
DAQmxStartTask(taskHandle_DO_P);
//Create analog input channel;
DAQmxCreateTask("",&taskHandle_AI);
DAQmxCreateAIVoltageChan(taskHandle_AI,"Dev1/ai0","",DAQmx_Val_Diff,-10.0,10.0,
DAQmx_Val_Volts,NULL);
DAQmxStartTask(taskHandle_AI);

/*Init the experiment and the data structures*/

//Pump 1
pump_id = 1;
all_pump_info[pump_id].huebe = 20;
all_pump_info[pump_id].aktuelle_huebe = 20;
all_pump_info[pump_id].interval_ms = 200;
all_pump_info[pump_id].pump_bit =   0x20;

//Pump 2
pump_id = 2;
all_pump_info[pump_id].huebe = 20;
all_pump_info[pump_id].aktuelle_huebe = 20;
all_pump_info[pump_id].interval_ms = 200;
all_pump_info[pump_id].pump_bit =   0x40;

//Pump 3
pump_id = 3;
all_pump_info[pump_id].huebe = 20;
all_pump_info[pump_id].aktuelle_huebe = 20;
all_pump_info[pump_id].interval_ms = 200;
all_pump_info[pump_id].pump_bit =   0x80;


//Measurement params
scan_params.duration = 30;
scan_params.sample_intervall = 1000.;
scan_params.samples = scan_params.duration/scan_params.sample_intervall;

// Set up buttons and Edit Fields
Pump1Steps->Text=0;
Pump2Steps->Text=0;
Pump3Steps->Text=0;
Pump1Steps->Enabled=false;
Pump2Steps->Enabled=false;
Pump3Steps->Enabled=false;
Pump1TotSt->Enabled=false;
Pump2TotSt->Enabled=false;
Pump3TotSt->Enabled=false;
Pump1Vol->Text=20;
Pump2Vol->Text=20;
Pump3Vol->Text=20;
Pump1Vol->Enabled=false;
Pump2Vol->Enabled=false;
Pump3Vol->Enabled=false;

// Initialize Events

PumpEvent[1] = new TEvent(NULL, true, true, "Pump1Event", true);
PumpEvent[1]->ResetEvent();
PumpEvent[2] = new TEvent(NULL, true, true, "Pump2Event", true);
PumpEvent[2]->ResetEvent();
PumpEvent[3] = new TEvent(NULL, true, true, "Pump3Event", true);
PumpEvent[3]->ResetEvent();

// Init status
Status->Color=clYellow;
Status->Text="Idle";






}
//---------------------------------------------------------------------------

float __fastcall TFrontreactor::measure(TObject *Sender)
{
float64 voltage, avg=0.0;
 for(int i=0; i<5; i++)
 {
 DAQmxReadAnalogScalarF64(taskHandle_AI,10.0,&voltage, NULL);
 avg = avg + voltage;
 }
avg = avg/5.;
return avg;
}
//---------------------------------------------------------------------------
void __fastcall TFrontreactor::ResetClick(TObject *Sender)
{
 // Reset to basic setting of experiment
control_bits = 0x07;
DAQmxWriteDigitalScalarU32(taskHandle_DO, 1, 10.0, control_bits, NULL);
reg = 0x0;
DAQmxWriteDigitalScalarU32(taskHandle_DO_P, 1, 10.0, reg, NULL);//shutdown the whole experimentcontrol_bits = 0x00;DAQmxWriteDigitalScalarU32(taskHandle_DO, 1, 10.0, control_bits, NULL);reg = 0x0;DAQmxWriteDigitalScalarU32(taskHandle_DO_P, 1, 10.0, reg, NULL);PBars[0]->Position=0;PBars[1]->Position=0;
PBars[2]->Position=0;
ProgressBar4->Position=0; //reset progress bars

// Set up buttons and Edit Fields
Pump1Steps->Text=0;
Pump2Steps->Text=0;
Pump3Steps->Text=0;
Pump1Steps->Enabled=false;
Pump2Steps->Enabled=false;
Pump3Steps->Enabled=false;
Pump1TotSt->Enabled=false;
Pump2TotSt->Enabled=false;
Pump3TotSt->Enabled=false;
Pump1Vol->Text=20;
Pump2Vol->Text=20;
Pump3Vol->Text=20;
Pump1Vol->Enabled=false;
Pump2Vol->Enabled=false;
Pump3Vol->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFrontreactor::StartInputClick(TObject *Sender)
{
all_pump_info[1].huebe = 0;
all_pump_info[2].huebe = 0;
all_pump_info[3].huebe = 0;
all_pump_info[1].aktuelle_huebe = 0;
all_pump_info[2].aktuelle_huebe = 0;
all_pump_info[3].aktuelle_huebe = 0;
//enable input
Pump1Vol->Enabled=true;
Pump2Vol->Enabled=true;
Pump3Vol->Enabled=true;

Pump1Steps->Text=0;
Pump2Steps->Text=0;
Pump3Steps->Text=0;Duration->Enabled=true;SampleIntervall->Enabled=true;

Duration->Text=scan_params.duration;
SampleIntervall->Text=scan_params.sample_intervall;
Refresh();   //repaint the control in the GUI// Clear chart
Series1->Clear();

// Rinse while doing input
Rinse = new RinseThread(false);
Rinse->WaitFor();
//Show status
Frontreactor->Status->Color=clLime;
Frontreactor->Status->Text="Rinsing Done!";
Sleep(2000);
Status->Color=clYellow;
Status->Text="Idle";

// We allow to continue only with starting the experiment
StartInput->Enabled = false;
StartReaction->Enabled = true;
Refresh();}


//---------------------------------------------------------------------------
void __fastcall TFrontreactor::StartReactionClick(TObject *Sender)
{
int max_huebe, tot_ms, pump_id;

Status->Color=clBlue;
Status->Text="Pumping...";
//disable input
//Pump1Vol->enabled=false;
//Pump2Vol->enabled=false;
//Pump3Vol->enabled=false;

Refresh();

//Calculate pump parameters

// Pump 1
pump_id = 1;
all_pump_info[pump_id].vol = Pump1Vol->Text.ToInt();
all_pump_info[pump_id].huebe = (int)((float)all_pump_info[pump_id].vol/0.5);
all_pump_info[pump_id].aktuelle_huebe = all_pump_info[pump_id].huebe;
all_pump_info[1].aktuelle_huebe = 0;

// Pump 2
pump_id=2;
all_pump_info[pump_id].vol = Pump2Vol->Text.ToInt();
all_pump_info[pump_id].huebe = (int)((float)all_pump_info[pump_id].vol/0.5);
all_pump_info[pump_id].aktuelle_huebe = all_pump_info[pump_id].huebe;
all_pump_info[2].aktuelle_huebe = 0;

// Pump 3
pump_id=3;
all_pump_info[pump_id].vol = Pump3Vol->Text.ToInt();
all_pump_info[pump_id].huebe = (int)((float)all_pump_info[pump_id].vol/0.5);
all_pump_info[pump_id].aktuelle_huebe = all_pump_info[pump_id].huebe;
all_pump_info[3].aktuelle_huebe = 0;
Pump1TotSt->Text=all_pump_info[1].huebe;
Pump2TotSt->Text=all_pump_info[2].huebe;
Pump3TotSt->Text=all_pump_info[3].huebe;PBars[0]->Max=all_pump_info[1].huebe;
PBars[1]->Max=all_pump_info[2].huebe;
PBars[2]->Max=all_pump_info[3].huebe;

max_huebe = (all_pump_info[1].huebe > all_pump_info[2].huebe)
 ? all_pump_info[1].huebe : all_pump_info[2].huebe ;
max_huebe = (max_huebe > all_pump_info[3].huebe)
 ? max_huebe : all_pump_info[3].huebe ;

tot_ms=max_huebe*500;
all_pump_info[1].interval_ms = tot_ms/all_pump_info[1].huebe;   // To get the interval we just divide the total duration by the number of steps
all_pump_info[2].interval_ms = tot_ms/all_pump_info[2].huebe;
all_pump_info[3].interval_ms = tot_ms/all_pump_info[3].huebe;

// Start pump threads



Pump1 = new PumpThreads(true, 1);
Pump1->ThreadName = "Pump1";
//
Pump2 = new PumpThreads(true, 2);
Pump2->ThreadName = "Pump2";
//
Pump3 = new PumpThreads(true, 3);
Pump3->ThreadName = "Pump3";

// Scan Parameters
Duration->Enabled=false;
SampleIntervall->Enabled=false;

scan_params.duration= Duration->Text.ToInt();
scan_params.sample_intervall=SampleIntervall->Text.ToDouble();
scan_params.samples=scan_params.duration*1000/scan_params.sample_intervall+1.;

Chart1->BottomAxis->SetMinMax(0.,(double)scan_params.duration);
Refresh();

PumpEvent[1]->ResetEvent();
PumpEvent[2]->ResetEvent();
PumpEvent[3]->ResetEvent();

Measure = new MeasureThread(false);
Measure->ThreadName = "MeasureThread";


// We continue only after the rinsing has finished
Rinse->WaitFor();
Pump1->Resume();
Pump2->Resume();
Pump3->Resume();
StartReaction->Enabled=false;

}
//---------------------------------------------------------------------------


