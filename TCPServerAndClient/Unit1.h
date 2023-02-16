//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TFormServer : public TForm
{
__published:	// IDE-managed Components
	TIdTCPServer *IdTCPServer1;
	TListBox *ListBox2;
	TCheckBox *CheckBox1;
	TRoundRect *RoundRectSendAll;
	TRoundRect *RoundRectConnectedClientsCount;
	TRoundRect *RoundRectAllClientList;
	TRoundRect *RoundRectDisconnectForAllClient;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCircle *Circle1;
	TImage *Image1;
	TRoundRect *RoundRectDisconnect;
	TLabel *Label6;
	TRectangle *Rectangle1;
	TEdit *Edit1;
	TLine *Line1;
	TListBox *ListBox1;
	TRoundRect *RoundRectSend;
	TLabel *Label5;
	void __fastcall IdTCPServer1Execute(TIdContext *AContext);
	void __fastcall IdTCPServer1Connect(TIdContext *AContext);
	void __fastcall IdTCPServer1Disconnect(TIdContext *AContext);
	void __fastcall btnTemizleClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CheckBox1Change(TObject *Sender);
	void __fastcall RoundRectSendAllClick(TObject *Sender);
	void __fastcall RoundRectConnectedClientsCountClick(TObject *Sender);
	void __fastcall RoundRectAllClientListClick(TObject *Sender);
	void __fastcall RoundRectDisconnectForAllClientClick(TObject *Sender);
	void __fastcall Circle1Click(TObject *Sender);
	void __fastcall RoundRectSendClick(TObject *Sender);
	void __fastcall RoundRectDisconnectClick(TObject *Sender);
	void __fastcall RoundRectSendAllMouseLeave(TObject *Sender);
	void __fastcall RoundRectSendAllMouseMove(TObject *Sender, TShiftState Shift, float X,
          float Y);
	void __fastcall RoundRectConnectedClientsCountMouseLeave(TObject *Sender);
	void __fastcall RoundRectConnectedClientsCountMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y);
	void __fastcall RoundRectAllClientListMouseLeave(TObject *Sender);
	void __fastcall RoundRectAllClientListMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y);
	void __fastcall RoundRectDisconnectForAllClientMouseLeave(TObject *Sender);
	void __fastcall RoundRectDisconnectForAllClientMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y);
	void __fastcall RoundRectSendMouseLeave(TObject *Sender);
	void __fastcall RoundRectSendMouseMove(TObject *Sender, TShiftState Shift, float X,
          float Y);
	void __fastcall RoundRectDisconnectMouseLeave(TObject *Sender);
	void __fastcall RoundRectDisconnectMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y);
	void __fastcall Circle1MouseLeave(TObject *Sender);
	void __fastcall Circle1MouseMove(TObject *Sender, TShiftState Shift, float X, float Y);


   // void __fastcall bagliOlanlariGetir();


private:	// User declarations
public:		// User declarations
	__fastcall TFormServer(TComponent* Owner);
	void  bagliOlanlariGetir();
	void  bagliOlanlariGonder();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormServer *FormServer;
//---------------------------------------------------------------------------
#endif
