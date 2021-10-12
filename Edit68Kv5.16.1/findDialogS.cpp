//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "findDialogS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfindDialogFrm *findDialogFrm;
//---------------------------------------------------------------------------
TfindDialogFrm::TfindDialogFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfindDialogFrm::findNextBtnClick(TObject *Sender)
{
  Main->FindDialogFind(findText->Text, wholeWordChk->Checked, matchCaseChk->Checked);
}
//---------------------------------------------------------------------------

void TfindDialogFrm::cancelBtnClick(TObject *Sender)
{
  this->Close();
}

//---------------------------------------------------------------------------

void TfindDialogFrm::findTextChange(TObject *Sender)
{
  if (findText->Text == "") {
    findNextBtn->Enabled = false;
    findNextBtn->Default = false;
  } else {
    findNextBtn->Enabled = true;
    findNextBtn->Default = true;
  }
}

//---------------------------------------------------------------------------

void TfindDialogFrm::FormShow(TObject *Sender)
{
  if (findText->Text == "") {
    findNextBtn->Enabled = false;
    findNextBtn->Default = false;
  } else {
    findNextBtn->Enabled = true;
    findNextBtn->Default = true;
    findNextBtn->SetFocus();
  }
}
//---------------------------------------------------------------------------

