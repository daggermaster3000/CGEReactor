//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <NIDAQmx.h>
#include "Reactor.h"
#include "RinseThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall RinseThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall RinseThread::RinseThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
void __fastcall RinseThread::Synch()
{
Frontreactor->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall RinseThread::Execute()
{
Frontreactor->Status->Color=clAqua;
Frontreactor->Status->Text="Rinsing...";

Frontreactor->control_bits = 0x1f;       //Rinse with exhaust open
DAQmxWriteDigitalScalarU32(taskHandle_DO, 1, 10.0,Frontreactor->control_bits, NULL);
Synchronize(Synch);
if (Terminated) exit;
Sleep(2000);
Frontreactor->control_bits = 0x0f;   //Exhausting with valve open
DAQmxWriteDigitalScalarU32(taskHandle_DO, 1, 10.0,Frontreactor->control_bits, NULL);
Synchronize(Synch);
if (Terminated) exit;
Sleep(15000);
Synchronize(Synch);
Frontreactor->control_bits = 0x07;  //Return to basic state
DAQmxWriteDigitalScalarU32(taskHandle_DO, 1, 10.0,
		Frontreactor->control_bits, NULL);

}
//---------------------------------------------------------------------------
