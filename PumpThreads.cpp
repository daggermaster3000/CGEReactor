//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include <NIDAQmx.h>
#include "Reactor.h"

#include "PumpThreads.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall PumpThreads::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall PumpThreads::PumpThreads(bool CreateSuspended, int pump_ID)
		: TThread(CreateSuspended), pump_id(pump_ID)
{
}
//---------------------------------------------------------------------------
void __fastcall PumpThreads::Execute()
{

 int i;
 NameThreadForDebugging(System::String(ThreadName));
 Frontreactor->PBars[pump_id-1]->BarColor=clBlue;
 for (Frontreactor->all_pump_info[pump_id].aktuelle_huebe=1; Frontreactor->all_pump_info[pump_id].aktuelle_huebe <= Frontreactor->all_pump_info[pump_id].huebe; Frontreactor->all_pump_info[pump_id].aktuelle_huebe++) {
  i++;
  Frontreactor->reg= Frontreactor->reg | Frontreactor->all_pump_info[pump_id].pump_bit;
  DAQmxWriteDigitalScalarU32(taskHandle_DO_P, 1, 10.0, Frontreactor->reg, NULL);
		Sleep(100);
  Frontreactor->reg=Frontreactor->reg & ~Frontreactor->all_pump_info[pump_id].pump_bit;
		DAQmxWriteDigitalScalarU32(taskHandle_DO_P, 1, 10.0, Frontreactor->reg, NULL);
		if (Frontreactor->all_pump_info[pump_id].aktuelle_huebe
							== (int)(2*Frontreactor->all_pump_info[pump_id].huebe/3))
			PumpEvent[pump_id]->SetEvent();

		Synchronize(& UpdateSteps);
		Sleep(Frontreactor->all_pump_info[pump_id].interval_ms-100 );
  //Update progress bar
  Frontreactor->PBars[pump_id-1]->Position=i;
  if (i >= 2*Frontreactor->all_pump_info[pump_id].huebe/3) {
	  Frontreactor->PBars[pump_id-1]->BarColor=clLime;
  }

 }
 Frontreactor->PBars[pump_id-1]->BarColor=clRed;
}
//---------------------------------------------------------------------------
void __fastcall PumpThreads::UpdateSteps()
{
Frontreactor->Pump1Steps->Text=Frontreactor->all_pump_info[1].aktuelle_huebe;
Frontreactor->Pump2Steps->Text=Frontreactor->all_pump_info[2].aktuelle_huebe;
Frontreactor->Pump3Steps->Text=Frontreactor->all_pump_info[3].aktuelle_huebe;
}
//---------------------------------------------------------------------------