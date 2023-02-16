// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdScheduler.pas' rev: 35.00 (Windows)

#ifndef IdschedulerHPP
#define IdschedulerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdThread.hpp>
#include <IdTask.hpp>
#include <IdYarn.hpp>
#include <IdThreadSafe.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idscheduler
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdScheduler;
//-- type declarations -------------------------------------------------------
typedef Idthreadsafe::TIdThreadSafeObjectList TIdYarnThreadList;

typedef System::Classes::TList TIdYarnList;

class PASCALIMPLEMENTATION TIdScheduler : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	Idthreadsafe::TIdThreadSafeObjectList* FActiveYarns;
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdScheduler();
	virtual Idyarn::TIdYarn* __fastcall AcquireYarn() = 0 ;
	virtual void __fastcall Init();
	virtual void __fastcall ReleaseYarn(Idyarn::TIdYarn* AYarn);
	virtual void __fastcall StartYarn(Idyarn::TIdYarn* AYarn, Idtask::TIdTask* ATask) = 0 ;
	virtual void __fastcall TerminateYarn(Idyarn::TIdYarn* AYarn) = 0 ;
	virtual void __fastcall TerminateAllYarns();
	__property Idthreadsafe::TIdThreadSafeObjectList* ActiveYarns = {read=FActiveYarns};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdScheduler(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdScheduler()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idscheduler */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSCHEDULER)
using namespace Idscheduler;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdschedulerHPP
