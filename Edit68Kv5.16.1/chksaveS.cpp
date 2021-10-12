//---------------------------------------------------------------------------
//   Author: Charles Kelly,
//           Monroe County Community College
//           http://www.monroeccc.edu/ckelly
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chksaveS.h"
#include "mainS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChkSave *ChkSave;
//---------------------------------------------------------------------------
TChkSave::TChkSave(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TChkSave::FormCreate(TObject *Sender)
{
  lblMessage->Caption = "Source has been modified. Save before exiting?";
  ChkSave->Caption = "Save source file?";        
}
//---------------------------------------------------------------------------
void TChkSave::btnOKClick(TObject *Sender)
{
  Main->mnuSaveClick(Sender);
  ChkSave->Close();
}
//---------------------------------------------------------------------------
void TChkSave::Button2Click(TObject *Sender)
{
  ChkSave->Close();
}
//---------------------------------------------------------------------------
