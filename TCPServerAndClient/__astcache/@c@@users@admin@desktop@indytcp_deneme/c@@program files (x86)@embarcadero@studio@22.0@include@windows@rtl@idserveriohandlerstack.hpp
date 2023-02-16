// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdServerIOHandlerStack.pas' rev: 35.00 (Windows)

#ifndef IdserveriohandlerstackHPP
#define IdserveriohandlerstackHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdSocketHandle.hpp>
#include <IdGlobal.hpp>
#include <IdThread.hpp>
#include <IdServerIOHandler.hpp>
#include <IdStackConsts.hpp>
#include <IdIOHandler.hpp>
#include <IdScheduler.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdServerIOHandlerSocket.hpp>
#include <IdYarn.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idserveriohandlerstack
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdServerIOHandlerStack;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdServerIOHandlerStack : public Idserveriohandlersocket::TIdServerIOHandlerSocket
{
	typedef Idserveriohandlersocket::TIdServerIOHandlerSocket inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	virtual Idiohandler::TIdIOHandler* __fastcall MakeClientIOHandler(Idyarn::TIdYarn* ATheThread);
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdServerIOHandlerStack() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerIOHandlerStack(System::Classes::TComponent* AOwner)/* overload */ : Idserveriohandlersocket::TIdServerIOHandlerSocket(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerIOHandlerStack()/* overload */ : Idserveriohandlersocket::TIdServerIOHandlerSocket() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idserveriohandlerstack */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSERVERIOHANDLERSTACK)
using namespace Idserveriohandlerstack;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdserveriohandlerstackHPP
