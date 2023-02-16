// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSchedulerOfThread.pas' rev: 35.00 (Windows)

#ifndef IdschedulerofthreadHPP
#define IdschedulerofthreadHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdBaseComponent.hpp>
#include <IdGlobal.hpp>
#include <IdScheduler.hpp>
#include <IdThread.hpp>
#include <IdTask.hpp>
#include <IdYarn.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idschedulerofthread
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdYarnOfThread;
class DELPHICLASS TIdSchedulerOfThread;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdYarnOfThread : public Idyarn::TIdYarn
{
	typedef Idyarn::TIdYarn inherited;
	
protected:
	Idscheduler::TIdScheduler* FScheduler;
	Idthread::TIdThreadWithTask* FThread;
	
public:
	__fastcall TIdYarnOfThread(Idscheduler::TIdScheduler* AScheduler, Idthread::TIdThreadWithTask* AThread);
	__fastcall virtual ~TIdYarnOfThread();
	__property Idthread::TIdThreadWithTask* Thread = {read=FThread};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdSchedulerOfThread : public Idscheduler::TIdScheduler
{
	typedef Idscheduler::TIdScheduler inherited;
	
protected:
	int FMaxThreads;
	System::Classes::TThreadPriority FThreadPriority;
	Idthread::TIdThreadWithTaskClass FThreadClass;
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdSchedulerOfThread();
	virtual Idthread::TIdThreadWithTask* __fastcall NewThread();
	TIdYarnOfThread* __fastcall NewYarn(Idthread::TIdThreadWithTask* AThread = (Idthread::TIdThreadWithTask*)(0x0));
	virtual void __fastcall StartYarn(Idyarn::TIdYarn* AYarn, Idtask::TIdTask* ATask);
	virtual void __fastcall TerminateYarn(Idyarn::TIdYarn* AYarn);
	__property Idthread::TIdThreadWithTaskClass ThreadClass = {read=FThreadClass, write=FThreadClass};
	
__published:
	__property int MaxThreads = {read=FMaxThreads, write=FMaxThreads, nodefault};
	__property System::Classes::TThreadPriority ThreadPriority = {read=FThreadPriority, write=FThreadPriority, default=3};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSchedulerOfThread(System::Classes::TComponent* AOwner)/* overload */ : Idscheduler::TIdScheduler(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSchedulerOfThread()/* overload */ : Idscheduler::TIdScheduler() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idschedulerofthread */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSCHEDULEROFTHREAD)
using namespace Idschedulerofthread;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdschedulerofthreadHPP
