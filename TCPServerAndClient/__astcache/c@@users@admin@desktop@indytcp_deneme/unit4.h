﻿//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TIdTCPServer *IdTCPServer1;
	TButton *btnSendAll;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TEdit *Edit1;
	TListBox *ListBox1;
	TListBox *ListBox2;
	TButton *btnGonder;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TButton *btnTemizle;
	void __fastcall IdTCPServer1Connect(TIdContext *AContext);
	void __fastcall IdTCPServer1Disconnect(TIdContext *AContext);
	void __fastcall IdTCPServer1Execute(TIdContext *AContext);
	void __fastcall btnSendAllClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall btnTemizleClick(TObject *Sender);
	void __fastcall btnGonderClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	void  bagliOlanlariGetir();
	void  bagliOlanlariGonder();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
