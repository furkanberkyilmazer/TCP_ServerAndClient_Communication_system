// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdLogBase.pas' rev: 35.00 (Windows)

#ifndef IdlogbaseHPP
#define IdlogbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdIntercept.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idlogbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdLogBase;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdLogBase : public Idintercept::TIdConnectionIntercept
{
	typedef Idintercept::TIdConnectionIntercept inherited;
	
protected:
	bool FActive;
	bool FLogTime;
	bool FReplaceCRLF;
	virtual void __fastcall InitComponent();
	virtual void __fastcall LogStatus(const System::UnicodeString AText) = 0 ;
	virtual void __fastcall LogReceivedData(const System::UnicodeString AText, const System::UnicodeString AData) = 0 ;
	virtual void __fastcall LogSentData(const System::UnicodeString AText, const System::UnicodeString AData) = 0 ;
	virtual void __fastcall SetActive(bool AValue);
	virtual void __fastcall Loaded();
	System::UnicodeString __fastcall ReplaceCR(const System::UnicodeString AString);
	
public:
	virtual void __fastcall Open();
	virtual void __fastcall Close();
	virtual void __fastcall Connect(System::Classes::TComponent* AConnection);
	__fastcall virtual ~TIdLogBase();
	virtual void __fastcall Disconnect();
	virtual void __fastcall Receive(Idglobal::TIdBytes &ABuffer);
	virtual void __fastcall Send(Idglobal::TIdBytes &ABuffer);
	
__published:
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property bool LogTime = {read=FLogTime, write=FLogTime, default=1};
	__property bool ReplaceCRLF = {read=FReplaceCRLF, write=FReplaceCRLF, default=1};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdLogBase(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdConnectionIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdLogBase()/* overload */ : Idintercept::TIdConnectionIntercept() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idlogbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDLOGBASE)
using namespace Idlogbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdlogbaseHPP
