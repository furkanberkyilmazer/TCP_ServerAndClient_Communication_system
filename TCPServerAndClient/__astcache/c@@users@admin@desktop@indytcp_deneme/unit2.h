//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdContext.hpp>
#include <IdIntercept.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdGlobal.hpp>
#include <IdLogBase.hpp>
#include <IdLogEvent.hpp>
#include <IdInterceptThrottler.hpp>
#include <IdThreadComponent.hpp>
//---------------------------------------------------------------------------
class TFormClient : public TForm
{
__published:	// IDE-managed Components
	TButton *btnBaglan;
	TEdit *Edit1;
	TButton *btnServerGonder;
	TButton *btnOku;
	TIdTCPClient *IdTCPClient1;
	TTimer *Timer1;
	TEdit *EditIP;
	TEdit *EditPort;
	TButton *btnDurdur;
	TButton *btnTemizle;
	TListBox *ListBox2;
	TIdIOHandlerStack *IdIOHandlerStack1;
	TIdConnectionIntercept *IdConnectionIntercept1;
	TIdThreadComponent *IdThreadComponent1;
	TListBox *ListBoxClients;
	TButton *btnClientGonder;
	void __fastcall btnOkuClick(TObject *Sender);
	void __fastcall btnServerGonderClick(TObject *Sender);
	void __fastcall IdTCPClient1Connected(TObject *Sender);
	void __fastcall btnBaglanClick(TObject *Sender);
	void __fastcall IdTCPClient1Disconnected(TObject *Sender);
	void __fastcall btnDurdurClick(TObject *Sender);
	void __fastcall btnTemizleClick(TObject *Sender);
	void __fastcall IdConnectionIntercept1Disconnect(TIdConnectionIntercept *ASender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall IdThreadComponent1Run(TIdThreadComponent *Sender);
	void __fastcall btnClientGonderClick(TObject *Sender);














private:	// User declarations
public:		// User declarations
	__fastcall TFormClient(TComponent* Owner);
    String oncekiMesaj="";
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClient *FormClient;
//---------------------------------------------------------------------------
#endif
