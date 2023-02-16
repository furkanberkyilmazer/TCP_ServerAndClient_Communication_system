// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdServerIOHandlerSocket.pas' rev: 35.00 (Windows)

#ifndef IdserveriohandlersocketHPP
#define IdserveriohandlersocketHPP

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
#include <IdIOHandlerSocket.hpp>
#include <IdYarn.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idserveriohandlersocket
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdServerIOHandlerSocket;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TIdIOHandlerSocketClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TIdIOHandlerSocketClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TIdServerIOHandlerSocket : public Idserveriohandler::TIdServerIOHandler
{
	typedef Idserveriohandler::TIdServerIOHandler inherited;
	
protected:
	TIdIOHandlerSocketClass IOHandlerSocketClass;
	virtual void __fastcall InitComponent();
	
public:
	virtual Idiohandler::TIdIOHandler* __fastcall Accept(Idsockethandle::TIdSocketHandle* ASocket, Idthread::TIdThread* AListenerThread, Idyarn::TIdYarn* AYarn);
	virtual void __fastcall Init();
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdServerIOHandlerSocket() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerIOHandlerSocket(System::Classes::TComponent* AOwner)/* overload */ : Idserveriohandler::TIdServerIOHandler(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerIOHandlerSocket()/* overload */ : Idserveriohandler::TIdServerIOHandler() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idserveriohandlersocket */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSERVERIOHANDLERSOCKET)
using namespace Idserveriohandlersocket;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdserveriohandlersocketHPP
