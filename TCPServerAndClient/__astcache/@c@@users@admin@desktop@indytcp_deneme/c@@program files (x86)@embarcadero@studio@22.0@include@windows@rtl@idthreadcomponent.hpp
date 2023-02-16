// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdThreadComponent.pas' rev: 35.00 (Windows)

#ifndef IdthreadcomponentHPP
#define IdthreadcomponentHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdThread.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idthreadcomponent
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdThreadComponent;
class DELPHICLASS TIdThreadEx;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdExceptionThreadComponentEvent)(TIdThreadComponent* Sender, System::Sysutils::Exception* AException);

typedef void __fastcall (__closure *TIdExceptionThreadComponentEventEx)(TIdThreadComponent* Sender, System::Sysutils::Exception* AException, bool &VHandled);

typedef void __fastcall (__closure *TIdNotifyThreadComponentEvent)(TIdThreadComponent* Sender);

class PASCALIMPLEMENTATION TIdThreadComponent : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	bool FActive;
	bool FLoop;
	System::Classes::TThreadPriority FPriority;
	Idthread::TIdThreadStopMode FStopMode;
	Idthread::TIdThread* FThread;
	System::UnicodeString FThreadName;
	TIdNotifyThreadComponentEvent FOnAfterExecute;
	TIdNotifyThreadComponentEvent FOnAfterRun;
	TIdNotifyThreadComponentEvent FOnBeforeExecute;
	TIdNotifyThreadComponentEvent FOnBeforeRun;
	TIdNotifyThreadComponentEvent FOnCleanup;
	TIdExceptionThreadComponentEvent FOnException;
	TIdNotifyThreadComponentEvent FOnRun;
	TIdNotifyThreadComponentEvent FOnStopped;
	TIdNotifyThreadComponentEvent FOnTerminate;
	TIdExceptionThreadComponentEventEx FOnHandleRunException;
	virtual void __fastcall DoAfterExecute();
	virtual void __fastcall DoAfterRun();
	virtual void __fastcall DoBeforeExecute();
	virtual void __fastcall DoBeforeRun();
	virtual void __fastcall DoCleanup();
	virtual void __fastcall DoException(Idthread::TIdThread* AThread, System::Sysutils::Exception* AException);
	virtual bool __fastcall DoHandleRunException(System::Sysutils::Exception* AException);
	virtual void __fastcall DoRun();
	virtual void __fastcall DoStopped(Idthread::TIdThread* AThread);
	virtual void __fastcall DoTerminate(System::TObject* Sender);
	bool __fastcall GetActive();
	System::TObject* __fastcall GetData();
	NativeUInt __fastcall GetHandle();
	System::Classes::TThreadPriority __fastcall GetPriority();
	int __fastcall GetReturnValue();
	Idthread::TIdThreadStopMode __fastcall GetStopMode();
	bool __fastcall GetStopped();
	bool __fastcall GetSuspended();
	System::UnicodeString __fastcall GetTerminatingException();
	System::TClass __fastcall GetTerminatingExceptionClass();
	bool __fastcall GetTerminated();
	virtual void __fastcall InitComponent();
	bool __fastcall IsRunning();
	virtual void __fastcall Loaded();
	virtual void __fastcall SetActive(const bool AValue);
	void __fastcall SetData(System::TObject* const AValue);
	void __fastcall SetLoop(const bool AValue);
	void __fastcall SetThreadName(const System::UnicodeString AValue);
	void __fastcall SetOnTerminate(const TIdNotifyThreadComponentEvent AValue);
	void __fastcall SetPriority(const System::Classes::TThreadPriority AValue);
	void __fastcall SetReturnValue(const int AValue);
	void __fastcall SetStopMode(const Idthread::TIdThreadStopMode AValue);
	
public:
	__fastcall virtual ~TIdThreadComponent();
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	void __fastcall Synchronize(System::Classes::TThreadMethod AMethod);
	virtual void __fastcall Terminate();
	virtual void __fastcall TerminateAndWaitFor();
	unsigned __fastcall WaitFor();
	__property System::TObject* Data = {read=GetData, write=SetData};
#ifndef _WIN64
	__property NativeUInt Handle = {read=GetHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt Handle = {read=GetHandle};
#endif /* _WIN64 */
	__property int ReturnValue = {read=GetReturnValue, write=SetReturnValue, nodefault};
	__property bool Stopped = {read=GetStopped, nodefault};
	__property bool Suspended = {read=GetSuspended, nodefault};
	__property System::UnicodeString TerminatingException = {read=GetTerminatingException};
	__property System::TClass TerminatingExceptionClass = {read=GetTerminatingExceptionClass};
	__property bool Terminated = {read=GetTerminated, nodefault};
	
__published:
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property bool Loop = {read=FLoop, write=SetLoop, nodefault};
	__property System::Classes::TThreadPriority Priority = {read=GetPriority, write=SetPriority, nodefault};
	__property Idthread::TIdThreadStopMode StopMode = {read=GetStopMode, write=SetStopMode, nodefault};
	__property System::UnicodeString ThreadName = {read=FThreadName, write=SetThreadName};
	__property TIdNotifyThreadComponentEvent OnAfterExecute = {read=FOnAfterExecute, write=FOnAfterExecute};
	__property TIdNotifyThreadComponentEvent OnAfterRun = {read=FOnAfterRun, write=FOnAfterRun};
	__property TIdNotifyThreadComponentEvent OnBeforeExecute = {read=FOnBeforeExecute, write=FOnBeforeExecute};
	__property TIdNotifyThreadComponentEvent OnBeforeRun = {read=FOnBeforeRun, write=FOnBeforeRun};
	__property TIdNotifyThreadComponentEvent OnCleanup = {read=FOnCleanup, write=FOnCleanup};
	__property TIdExceptionThreadComponentEvent OnException = {read=FOnException, write=FOnException};
	__property TIdExceptionThreadComponentEventEx OnHandleRunException = {read=FOnHandleRunException, write=FOnHandleRunException};
	__property TIdNotifyThreadComponentEvent OnRun = {read=FOnRun, write=FOnRun};
	__property TIdNotifyThreadComponentEvent OnStopped = {read=FOnStopped, write=FOnStopped};
	__property TIdNotifyThreadComponentEvent OnTerminate = {read=FOnTerminate, write=SetOnTerminate};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdThreadComponent(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdThreadComponent()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};


class PASCALIMPLEMENTATION TIdThreadEx : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	TIdThreadComponent* FThreadComponent;
	virtual void __fastcall AfterRun();
	virtual void __fastcall AfterExecute();
	virtual void __fastcall BeforeExecute();
	virtual void __fastcall BeforeRun();
	virtual void __fastcall Cleanup();
	virtual bool __fastcall HandleRunException(System::Sysutils::Exception* AException);
	virtual void __fastcall Run();
	
public:
	__fastcall TIdThreadEx(TIdThreadComponent* AThreadComponent);
public:
	/* TIdThread.Destroy */ inline __fastcall virtual ~TIdThreadEx() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Classes::TThreadPriority IdThreadComponentDefaultPriority = (System::Classes::TThreadPriority)(3);
static const Idthread::TIdThreadStopMode IdThreadComponentDefaultStopMode = (Idthread::TIdThreadStopMode)(0);
}	/* namespace Idthreadcomponent */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTHREADCOMPONENT)
using namespace Idthreadcomponent;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdthreadcomponentHPP
