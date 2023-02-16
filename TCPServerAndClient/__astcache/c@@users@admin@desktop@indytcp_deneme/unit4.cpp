﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IdTCPServer1Connect(TIdContext *AContext)
{
  AContext->Connection->Socket->WriteLn("Baglandi ("+IntToStr(AContext->Binding->PeerPort)+")");
   ListBox1->Items->Add("Baglanilan IP : "+AContext->Binding->PeerIP+
	" Port : " + IntToStr(AContext->Binding->Port)+" / "+IntToStr(AContext->Binding->PeerPort));
   bagliOlanlariGetir();
   bagliOlanlariGonder();
}
//---------------------------------------------------------------------------

void TForm2::bagliOlanlariGetir()
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
//---------------------------------------------------------------------------
void TForm2::bagliOlanlariGonder()
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
void __fastcall TForm2::IdTCPServer1Disconnect(TIdContext *AContext)
{
   	ListBox1->Items->Add("IP : "+AContext->Binding->PeerIP+
	"Port : " + IntToStr(AContext->Binding->Port)+"/"+IntToStr(AContext->Binding->PeerPort)+" ayrıldı.");
	bagliOlanlariGetir();
	bagliOlanlariGonder();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IdTCPServer1Execute(TIdContext *AContext)
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
									ListBox1->Items->Add("Clientlar birbirine mesaj yolladı.");
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

}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnSendAllClick(TObject *Sender)
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
void __fastcall TForm2::Button2Click(TObject *Sender)
{
    TList  *ClientsList;

   ClientsList = IdTCPServer1->Contexts->LockList();
   ListBox1->Items->Add(IntToStr(ClientsList->Count)+ " client(s) bağli");
   IdTCPServer1->Contexts->UnlockList();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
     TList  *ClientsList;
   int i;

  if (!IdTCPServer1->Contexts) {

  }
   else
  {
  ClientsList = IdTCPServer1->Contexts->LockList();
  try {
   ListBox1->Items->Add("Bağlı clientlar: ");
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
void __fastcall TForm2::Button4Click(TObject *Sender)
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
                            ListBox1->Items->Add("Bağlantı kesildi" + Context->Binding->PeerIP + " : " + IntToStr(Context->Binding->PeerPort));
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
void __fastcall TForm2::btnTemizleClick(TObject *Sender)
{
  ListBox1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnGonderClick(TObject *Sender)
{

 TList  *ClientsList;
 ClientsList = IdTCPServer1->Contexts->LockList();
  if (!IdTCPServer1->Contexts) {

  }
  else{


		 try {


			  int i = ListBox2->ItemIndex;
			  TIdContext *Context=(TIdContext*)ClientsList->Items[i];

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
		ShowMessage("Mesaj göndermek istediğiniz client ı seçiniz.");
		 }


  }
   IdTCPServer1->Contexts->UnlockList();


}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{


   TList  *ClientsList;

   int i;

   try {

		  if (IdTCPServer1->Contexts)
		  {
					ClientsList = IdTCPServer1->Contexts->LockList();

					 int index = ListBox2->ItemIndex;
					try {

							TIdContext *Context=(TIdContext*)ClientsList->Items[index];
							ListBox1->Items->Add("Bağlantı kesildi" + Context->Binding->PeerIP + " : " + IntToStr(Context->Binding->PeerPort));
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
void __fastcall TForm2::CheckBox1Click(TObject *Sender)
{
 if(CheckBox1->Checked)
   {
	 IdTCPServer1->Active=true;
   }
   else
   {
     IdTCPServer1->Active=false;
   }
}
//---------------------------------------------------------------------------
