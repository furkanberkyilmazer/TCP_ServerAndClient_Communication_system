// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdLogEvent.pas' rev: 35.00 (Windows)

#ifndef IdlogeventHPP
#define IdlogeventHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdLogBase.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>
#include <IdIntercept.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idlogevent
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdLogEvent;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TLogItemStatusEvent)(System::Classes::TComponent* ASender, const System::UnicodeString AText);

typedef void __fastcall (__closure *TLogItemDataEvent)(System::Classes::TComponent* ASender, const System::UnicodeString AText, const System::UnicodeString AData);

class PASCALIMPLEMENTATION TIdLogEvent : public Idlogbase::TIdLogBase
{
	typedef Idlogbase::TIdLogBase inherited;
	
protected:
	TLogItemDataEvent FOnReceived;
	TLogItemDataEvent FOnSent;
	TLogItemStatusEvent FOnStatus;
	virtual void __fastcall LogStatus(const System::UnicodeString AText);
	virtual void __fastcall LogReceivedData(const System::UnicodeString AText, const System::UnicodeString AData);
	virtual void __fastcall LogSentData(const System::UnicodeString AText, const System::UnicodeString AData);
	
__published:
	__property TLogItemDataEvent OnReceived = {read=FOnReceived, write=FOnReceived};
	__property TLogItemDataEvent OnSent = {read=FOnSent, write=FOnSent};
	__property TLogItemStatusEvent OnStatus = {read=FOnStatus, write=FOnStatus};
public:
	/* TIdLogBase.Destroy */ inline __fastcall virtual ~TIdLogEvent() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdLogEvent(System::Classes::TComponent* AOwner)/* overload */ : Idlogbase::TIdLogBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdLogEvent()/* overload */ : Idlogbase::TIdLogBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idlogevent */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDLOGEVENT)
using namespace Idlogevent;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdlogeventHPP
