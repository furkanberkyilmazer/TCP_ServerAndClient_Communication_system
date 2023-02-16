//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFormServer *FormServer;
//---------------------------------------------------------------------------
__fastcall TFormServer::TFormServer(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormServer::IdTCPServer1Connect(TIdContext *AContext)
{
   AContext->Connection->Socket->WriteLn("Baglandi ("+IntToStr(AContext->Binding->PeerPort)+")");
   ListBox1->Items->Add("Baglanilan IP : "+AContext->Binding->PeerIP+
	" Port : " + IntToStr(AContext->Binding->Port)+" / "+IntToStr(AContext->Binding->PeerPort));
   bagliOlanlariGetir();
   bagliOlanlariGonder();
}
//---------------------------------------------------------------------------
void __fastcall TFormServer::IdTCPServer1Disconnect(TIdContext *AContext)
{

	ListBox1->Items->Add("IP : "+AContext->Binding->PeerIP+
	"Port : " + IntToStr(AContext->Binding->Port)+"/"+IntToStr(AContext->Binding->PeerPort)+" ayrýldý.");
	bagliOlanlariGetir();
	bagliOlanlariGonder();


}
//---------------------------------------------------------------------------

void __fastcall TFormServer::IdTCPServer1Execute(TIdContext *AContext)
{
	 String s;

	 s=AContext->Connection->IOHandler->ReadLn();
	 if ( s != NULL ) {


		if(s[1]=='G'&&s[2]=='-')
		{
			  TList  *ClientsList;
			  ClientsList = IdTCPServer1->Contexts->LockList();
			  String clientName;
			  String msg;

			  for (int i = 3; i <= s.Length(); i++) {
					if(s[i]=='-')
					  break;
				  clientName+=s[i];
			  }
			  for (int j = clientName.Length()+4; j <= s.Length(); j++) {
				   msg+=s[j];
			  }


			   TIdContext *Context=(TIdContext*)ClientsList->Items[ListBox2->Items->IndexOf(clientName)];
								try {
									Context->Connection->IOHandler->WriteLn(" ("+AContext->Binding->PeerIP+
	":" +IntToStr(AContext->Binding->PeerPort)+") "+msg);
									ListBox1->Items->Add("Clientlar birbirine mesaj yolladý.");
									Context->Connection->IOHandler->WriteBufferFlush();

							}
							catch (Exception&e) {

							}

						  IdTCPServer1->Contexts->UnlockList();

		}
		else{
            ListBox1->Items->Add("("+AContext->Binding->PeerIP+
	 " : " + IntToStr(AContext->Binding->PeerPort)+") :"+ s);
		}




	 }

	 //	AContext->Connection->Socket->WriteLn("Calisiyor");
}
//---------------------------------------------------------------------------






void TFormServer::bagliOlanlariGetir()
{
  TList  *ClientsList;
  int i;
  ListBox2->Clear();

  if (!IdTCPServer1->Contexts) {

  }
  else{

  ClientsList = IdTCPServer1->Contexts->LockList();
  try {
   //ListBox1->Items->Add("Tüm clientlara gonder : "+Edit1->Text);
   for (i = 0; i < ClientsList->Count; i++) {
		 try {
			  /*TIdContext *AContext;
			  AContext(ClientsList[i])->Connection->     */
			  TIdContext *Context=(TIdContext*)ClientsList->Items[i];
			  bool connected = false;
				try {
					connected = Context->Connection->Connected();
				}
				catch (Exception&e) {

					continue;
				}
			  if (!connected)
		continue;
				try {
				//Context->Connection->IOHandler->WriteLn(Edit1->Text);
				ListBox2->Items->Add("("+Context->Binding->PeerIP+
	" : " + IntToStr(Context->Binding->PeerPort)+")");
				Context->Connection->IOHandler->WriteBufferFlush();
			}
			catch (Exception&e) {

			}
		} catch (...) {
		 }
   }
  } catch (...) {
  }
  }
   IdTCPServer1->Contexts->UnlockList();


}


void __fastcall TFormServer::btnTemizleClick(TObject *Sender)
{
ListBox1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::Button1Click(TObject *Sender)
{
 // IdTCPServer1->Active=false;
 // IdTCPServer1->OnDisconnect();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::CheckBox1Change(TObject *Sender)
{
   if(CheckBox1->IsChecked)
   {
	 IdTCPServer1->Active=true;
   }
   else
   {
     IdTCPServer1->Active=false;
   }
}
//---------------------------------------------------------------------------
void TFormServer::bagliOlanlariGonder()
{

  TList  *ClientsList;
  int i;

  if (!IdTCPServer1->Contexts) {

  }
  else{

  ClientsList = IdTCPServer1->Contexts->LockList();
  try {


   for (i = 0; i < ClientsList->Count; i++) {
		 try {


			  TIdContext *Context=(TIdContext*)ClientsList->Items[i];
			  bool connected = false;
				try {
					connected = Context->Connection->Connected();
				}
				catch (Exception&e) {

					continue;
				}
			  if (!connected)
		continue;
				try {

							 Context->Connection->IOHandler->WriteLn("C-ListeyiSifirla");
							 for (int j=0; j < 10; j++) {


								 try {


									  TIdContext *Context2=(TIdContext*)ClientsList->Items[j];
									  bool connected = false;
										try {
											connected = Context2->Connection->Connected();
										}
										catch (Exception&e) {

											continue;
										}
									  if (!connected)
								continue;
										try {
										Context->Connection->IOHandler->WriteLn("C-("+Context2->Binding->PeerIP+
	" : " + IntToStr(Context2->Binding->PeerPort)+")");



									}
									catch (Exception&e) {

									}
								} catch (...) {
								 }
								}
				//Context->Connection->IOHandler->WriteLn("C-"+ IntToStr(Context->Binding->PeerPort));
				Context->Connection->IOHandler->WriteBufferFlush();


			}
			catch (Exception&e) {

			}
		} catch (...) {
		 }
   }
  } catch (...) {
  }
  }
   IdTCPServer1->Contexts->UnlockList();

}

//---------------------------------------------------------------------------
void __fastcall TFormServer::RoundRectSendAllClick(TObject *Sender)
{
 TList  *ClientsList;
  int i;

  if (!IdTCPServer1->Contexts) {

  }
  else{

  ClientsList = IdTCPServer1->Contexts->LockList();
  try {


   for (i = 0; i < ClientsList->Count; i++) {
		 try {


			  TIdContext *Context=(TIdContext*)ClientsList->Items[i];
			  bool connected = false;
				try {
					connected = Context->Connection->Connected();
				}
				catch (Exception&e) {

					continue;
				}
			  if (!connected)
		continue;
				try {
				Context->Connection->IOHandler->WriteLn(Edit1->Text);
				ListBox1->Items->Add("Serverdan ("+Context->Binding->PeerIP+
	" : " + IntToStr(Context->Binding->PeerPort)+") :"+ Edit1->Text);
				Context->Connection->IOHandler->WriteBufferFlush();


			}
			catch (Exception&e) {

			}
		} catch (...) {
		 }
   }
  } catch (...) {
  }
  }
   IdTCPServer1->Contexts->UnlockList();

}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectConnectedClientsCountClick(TObject *Sender)

{
       TList  *ClientsList;

   ClientsList = IdTCPServer1->Contexts->LockList();
   ListBox1->Items->Add(IntToStr(ClientsList->Count)+ " client(s) baðli");
   IdTCPServer1->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectAllClientListClick(TObject *Sender)
{
    TList  *ClientsList;
   int i;

  if (!IdTCPServer1->Contexts) {

  }
   else
  {
  ClientsList = IdTCPServer1->Contexts->LockList();
  try {
   ListBox1->Items->Add("Baðlý clientlar: ");
   for (i = 0; i < ClientsList->Count; i++) {
	  TIdContext *Context=(TIdContext*)ClientsList->Items[i];
	  ListBox1->Items->Add(Context->Binding->PeerIP+" : "+IntToStr(Context->Binding->PeerPort));
   }
  } catch (...) {
  }
  }
	  IdTCPServer1->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectForAllClientClick(TObject *Sender)

{
     TList  *ClientsList;
   int i;
   try {
			if (!IdTCPServer1->Contexts) {

		  }
		  else
		  {
		  ClientsList = IdTCPServer1->Contexts->LockList();

			  for (i = 0; i < ClientsList->Count; i++) {

					try {

							TIdContext *Context=(TIdContext*)ClientsList->Items[i];
							ListBox1->Items->Add("Baðlantý kesildi" + Context->Binding->PeerIP + " : " + IntToStr(Context->Binding->PeerPort));
							Context->Connection->Disconnect();
							Context->Connection->IOHandler->InputBuffer->Clear();


						}
						catch (...){
						}
			  }

		  }
  }
	catch (...) {
  }
  IdTCPServer1->Contexts->UnlockList();


}
//---------------------------------------------------------------------------

void __fastcall TFormServer::Circle1Click(TObject *Sender)
{
ListBox1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectSendClick(TObject *Sender)
{
TList  *ClientsList;
 ClientsList = IdTCPServer1->Contexts->LockList();
  if (!IdTCPServer1->Contexts) {

  }
  else{


		 try {


			  int index = ListBox2->Selected->Index;
			  TIdContext *Context=(TIdContext*)ClientsList->Items[index];

			  bool connected = false;
				try {
					connected = Context->Connection->Connected();

				}
				catch (Exception&e) {


				}
			  if (connected)
			  {
							try {
							Context->Connection->IOHandler->WriteLn(Edit1->Text);
							ListBox1->Items->Add("Serverdan ("+Context->Binding->PeerIP+
				" : " + IntToStr(Context->Binding->PeerPort)+") :"+ Edit1->Text);
							Context->Connection->IOHandler->WriteBufferFlush();

						}
									catch (Exception&e) {

						}
			  }
		} catch (...) {
		ShowMessage("Mesaj göndermek istediðiniz client ý seçiniz.");
		 }


  }
   IdTCPServer1->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectClick(TObject *Sender)
{


   TList  *ClientsList;

   int i;

   try {

		  if (IdTCPServer1->Contexts)
		  {
					ClientsList = IdTCPServer1->Contexts->LockList();

					 int index = ListBox2->Selected->Index;
					try {

							TIdContext *Context=(TIdContext*)ClientsList->Items[index];
							ListBox1->Items->Add("Baðlantý kesildi" + Context->Binding->PeerIP + " : " + IntToStr(Context->Binding->PeerPort));
                            Context->Connection->IOHandler->InputBuffer->Clear();
							Context->Connection->Disconnect();



						}
						catch (...){
						}


		  }
  }
	catch (...) {
  }
  IdTCPServer1->Contexts->UnlockList();

}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectSendAllMouseLeave(TObject *Sender)
{
  RoundRectSendAll->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectSendAllMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y)
{
	RoundRectSendAll->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectConnectedClientsCountMouseLeave(TObject *Sender)

{
   RoundRectConnectedClientsCount->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectConnectedClientsCountMouseMove(TObject *Sender,
          TShiftState Shift, float X, float Y)
{
	RoundRectConnectedClientsCount->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectAllClientListMouseLeave(TObject *Sender)
{
   RoundRectAllClientList->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectAllClientListMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y)
{
   RoundRectAllClientList->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectForAllClientMouseLeave(TObject *Sender)

{
	RoundRectDisconnectForAllClient->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectForAllClientMouseMove(TObject *Sender,
          TShiftState Shift, float X, float Y)
{
	RoundRectDisconnectForAllClient->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectSendMouseLeave(TObject *Sender)
{
	RoundRectSend->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectSendMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y)
{
	 RoundRectSend->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectMouseLeave(TObject *Sender)
{
	RoundRectDisconnect->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::RoundRectDisconnectMouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y)
{
	RoundRectDisconnect->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::Circle1MouseLeave(TObject *Sender)
{
		Circle1->Fill->Color=(TColor)0xFFE0E0E0;
}
//---------------------------------------------------------------------------

void __fastcall TFormServer::Circle1MouseMove(TObject *Sender, TShiftState Shift,
          float X, float Y)
{
		Circle1->Fill->Color=(TColor)0xAFE0E0E0;
}
//---------------------------------------------------------------------------

