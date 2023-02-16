//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadToServerThread.h"
#include "Unit2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
void __fastcall TReadToServerThread::UpdateCaption()
{
		Form1->Caption = "Updated in a thread";
}
//---------------------------------------------------------------------------

__fastcall TReadToServerThread::TReadToServerThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TReadToServerThread::Execute()
{

	FreeOnTerminate = true;
	while(1){
	if(Form1->IdTCPClient1->Connected())
	{
		if(!Form1->IdTCPClient1->Socket->InputBufferIsEmpty())
		{
			// ListBox2->Items->Add("("+IdTCPClient1->Host+":"+IdTCPClient1->Port+"/"+IdTCPClient1->Socket->Binding->Port+") :"+ IdTCPClient1->Socket->ReadLn());
			 Form1->ListBox2->Items->Add("Gelen Mesaj: "+ Form1->IdTCPClient1->Socket->ReadLn());
		}
		Form1->btnBaglan->Enabled=false;
	}
	else
	{
		Form1->btnBaglan->Enabled=true;

	}
	}
	//Synchronize();
}
//---------------------------------------------------------------------------
