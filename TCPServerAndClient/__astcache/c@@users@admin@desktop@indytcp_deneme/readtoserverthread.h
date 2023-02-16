//---------------------------------------------------------------------------

#ifndef ReadToServerThreadH
#define ReadToServerThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TReadToServerThread : public TThread
{
private:
protected:
    void __fastcall UpdateCaption();
	void __fastcall Execute();
public:
	__fastcall TReadToServerThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
