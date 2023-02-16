﻿//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
#include "string.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFormClient *FormClient;
//---------------------------------------------------------------------------
__fastcall TFormClient::TFormClient(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormClient::btnOkuClick(TObject *Sender)
{
   //	ListBox2->Items->Add(IdTCPClient1->Socket->ReadLn());
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::btnServerGonderClick(TObject *Sender)
{
   IdTCPClient1->Socket->WriteLn(Edit1->Text);
   ListBox2->Items->Add("Giden Mesaj : "+ Edit1->Text);
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::IdTCPClient1Connected(TObject *Sender)
{
	 IdThreadComponent1->Active=true;
	 ListBox2->Items->Add(IdTCPClient1->Socket->ReadLn());
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::btnBaglanClick(TObject *Sender)
{

	if (EditIP->Text!="" || EditPort->Text!="")
	{

	try {
	   IdTCPClient1->Host=EditIP->Text;
	   IdTCPClient1->Port = StrToInt(EditPort->Text);
	   IdTCPClient1->Connect();
	} catch (Exception *error) {
	ShowMessage("Hata mesaji: "+error->Message);
	}


	}
	else {
    ShowMessage("Ip ve Port Bilgisi giriniz.");
	}



}
//---------------------------------------------------------------------------
void __fastcall TFormClient::IdTCPClient1Disconnected(TObject *Sender)
{
   //ListBox2->Items->Add("Serverla Bağlantım kesildi.");
   //Intercept ile gerçekleştiriyoruz
}
//---------------------------------------------------------------------------


void __fastcall TFormClient::btnDurdurClick(TObject *Sender)
{
   IdTCPClient1->Disconnect();

}
//---------------------------------------------------------------------------

void __fastcall TFormClient::btnTemizleClick(TObject *Sender)
{
ListBox2->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::IdConnectionIntercept1Disconnect(TIdConnectionIntercept *ASender)

{
 ListBox2->Items->Add("Serverla Bağlantım kesildi.");
 ListBoxClients->Items->Clear();
 IdThreadComponent1->Active=false;
}
//---------------------------------------------------------------------------




void __fastcall TFormClient::Timer1Timer(TObject *Sender)
{
  /* if (!IdTCPClient1->Connected())
   {
	btnBaglan->Enabled=true;
	return;

   }
   btnBaglan->Enabled=false;
   if (IdTCPClient1->IOHandler->InputBufferIsEmpty())
   {
	return;
   }                                                   String gelenMesaj = IdTCPClient1->IOHandler->InputBufferAsString();
   ListBox2->Items->Add("Gelen Mesaj: " + gelenMesaj);
   */

   /*

	if(IdTCPClient1->Connected())
	{
		if(!IdTCPClient1->Socket->InputBufferIsEmpty())
		{

			// ListBox2->Items->Add("("+IdTCPClient1->Host+":"+IdTCPClient1->Port+"/"+IdTCPClient1->Socket->Binding->Port+") :"+ IdTCPClient1->Socket->ReadLn());
			ListBox2->Items->Add("Gelen Mesaj: "+ Form1->IdTCPClient1->Socket->ReadLn());
		}
		btnBaglan->Enabled=false;
	}
	else
	{
		btnBaglan->Enabled=true;

	}


   */
 
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::IdThreadComponent1Run(TIdThreadComponent *Sender)
{
  if(IdTCPClient1->Connected())
	{
		if(!IdTCPClient1->Socket->InputBufferIsEmpty())
		{
			// ListBox2->Items->Add("("+IdTCPClient1->Host+":"+IdTCPClient1->Port+"/"+IdTCPClient1->Socket->Binding->Port+") :"+ IdTCPClient1->Socket->ReadLn());

			String gelenMesaj=IdTCPClient1->Socket->ReadLn();
			String Clients;

			if (gelenMesaj=="C-ListeyiSifirla") {
               ListBoxClients->Clear();
			}
			else if(gelenMesaj[1]=='C' && gelenMesaj[2]=='-')
			{

			  for (int i = 3; i <= gelenMesaj.Length(); i++) {

				Clients += gelenMesaj[i];
			  }
			  ListBoxClients->Items->Add(Clients);

			}
			else
			{
               ListBox2->Items->Add("Gelen Mesaj: "+ gelenMesaj);
			}


		}
		btnBaglan->Enabled=false;
	}
	else
	{
		btnBaglan->Enabled=true;

	}
}
//---------------------------------------------------------------------------


void __fastcall TFormClient::btnClientGonderClick(TObject *Sender)
{

   if (ListBoxClients->Selected) {
	  IdTCPClient1->Socket->WriteLn("G-"+ListBoxClients->Selected->ItemData->Text+"-"+Edit1->Text);
	  ListBox2->Items->Add(ListBoxClients->Selected->ItemData->Text+" Gönderilen Mesaj : "+ Edit1->Text);
   }
   else
   {
       ShowMessage("Kişi Seçin!");
   }

}
//---------------------------------------------------------------------------

