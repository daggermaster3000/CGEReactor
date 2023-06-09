//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "RinseThread.h"
#include "Reactor.h"

#include "MeasureThread.h"
#pragma package(smart_init)

RinseThread *Rinse;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall MeasureThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall MeasureThread::MeasureThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall MeasureThread::Execute()
{
  NameThreadForDebugging(System::String(ThreadName));
  float64 volt=0.0;
	int j;
	TWaitResult  ResultP1, ResultP2, ResultP3;

	// Wait until all pumps have reached two thirds of their volume
	while(((ResultP1 = PumpEvent[1]->WaitFor(100)) !=  wrSignaled)  ||
			 ((ResultP2 = PumpEvent[2]->WaitFor(100))  !=  wrSignaled) ||
			 ((ResultP3 = PumpEvent[3]->WaitFor(100))  !=  wrSignaled) )
			 {if(Terminated) exit; }

	//  Do the scan
	Frontreactor->Status->Color=clLime;
	Frontreactor->Status->Text="Measuring...";
	//set max for progress bar
	Frontreactor->ProgressBar4->Max=Frontreactor->scan_params.samples;
    //Get the data
	for(j=0;j<Frontreactor->scan_params.samples;j++)
	{
	volt = Frontreactor->measure(this);
	Frontreactor->Series1->AddXY((float64)(j*Frontreactor->scan_params.sample_intervall)/1000.,volt,"");
	if(Terminated) exit;
	Sleep(Frontreactor->scan_params.sample_intervall);
    Frontreactor->ProgressBar4->Position=j;
	} //end loop j

	// Rinse after reaction
	Rinse = new RinseThread(false);
	//Rinse->ThreadName = "RinseAfterReaction";
	Rinse->WaitFor();

	// New measuremensts can be started only after rinsing has completed
	Frontreactor->StartInput->Enabled=true;
	Synchronize(&UpdateChart);
	Frontreactor->Status->Color=clLime;
	Frontreactor->Status->Text="Experiment Completed";
}
//---------------------------------------------------------------------------

void __fastcall MeasureThread::UpdateChart(){
	Frontreactor->Refresh();
}