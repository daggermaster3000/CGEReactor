//---------------------------------------------------------------------------

#ifndef PumpThreadsH
#define PumpThreadsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class PumpThreads : public TThread
{
  const char *  TName;
  int pump_id;

protected:
	void __fastcall Execute();
	void __fastcall UpdateSteps();

public:
        __property const char * ThreadName = {read=TName, write=TName};
        __fastcall PumpThreads(bool CreateSuspended, int pump_ID);

//	__fastcall PumpThreads(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif

