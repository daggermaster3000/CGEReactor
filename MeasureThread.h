//---------------------------------------------------------------------------

#ifndef MeasureThreadH
#define MeasureThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class MeasureThread : public TThread
{
const char * TName;
protected:
	void __fastcall Execute();
	void __fastcall UpdateChart();
public:
	__fastcall MeasureThread(bool CreateSuspended);
	__property char * ThreadName = {read=TName, write=TName};
};
//---------------------------------------------------------------------------
#endif
