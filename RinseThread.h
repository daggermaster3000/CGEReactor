//---------------------------------------------------------------------------

#ifndef RinseThreadH
#define RinseThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class RinseThread : public TThread
{
private:
protected:
	void __fastcall Execute();
	void __fastcall Synch();
public:
	__fastcall RinseThread(bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
