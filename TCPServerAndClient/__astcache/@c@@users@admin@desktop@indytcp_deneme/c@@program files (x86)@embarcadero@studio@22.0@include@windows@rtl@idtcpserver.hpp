// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTCPServer.pas' rev: 35.00 (Windows)

#ifndef IdtcpserverHPP
#define IdtcpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtcpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdTCPNoOnExecute;
class DELPHICLASS TIdTCPServer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTCPNoOnExecute : public Idcustomtcpserver::EIdTCPServerError
{
	typedef Idcustomtcpserver::EIdTCPServerError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTCPNoOnExecute(const System::UnicodeString AMsg)/* overload */ : Idcustomtcpserver::EIdTCPServerError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTCPNoOnExecute(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idcustomtcpserver::EIdTCPServerError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTCPNoOnExecute(NativeUInt Ident)/* overload */ : Idcustomtcpserver::EIdTCPServerError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTCPNoOnExecute(System::PResStringRec ResStringRec)/* overload */ : Idcustomtcpserver::EIdTCPServerError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTCPNoOnExecute(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idcustomtcpserver::EIdTCPServerError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTCPNoOnExecute(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idcustomtcpserver::EIdTCPServerError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTCPNoOnExecute(const System::UnicodeString Msg, int AHelpContext) : Idcustomtcpserver::EIdTCPServerError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTCPNoOnExecute(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idcustomtcpserver::EIdTCPServerError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTCPNoOnExecute(NativeUInt Ident, int AHelpContext)/* overload */ : Idcustomtcpserver::EIdTCPServerError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTCPNoOnExecute(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idcustomtcpserver::EIdTCPServerError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTCPNoOnExecute(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idcustomtcpserver::EIdTCPServerError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTCPNoOnExecute(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idcustomtcpserver::EIdTCPServerError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTCPNoOnExecute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdTCPServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	virtual void __fastcall CheckOkToBeActive();
	
__published:
	__property OnExecute;
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdTCPServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdTCPServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTCPServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtcpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTCPSERVER)
using namespace Idtcpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtcpserverHPP
