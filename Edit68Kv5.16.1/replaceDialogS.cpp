//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "replaceDialogS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TreplaceDialogFrm *replaceDialogFrm;
//---------------------------------------------------------------------------
TreplaceDialogFrm::TreplaceDialogFrm(TComponent* Owner)
        : TForm(Owner)
{
  replaceAll = false;
}
//---------------------------------------------------------------------------
void TreplaceDialogFrm::findNextBtnClick(TObject *Sender)
{
  Main->FindDialogFind(findText->Text, wholeWordChk->Checked, matchCaseChk->Checked);
}
//---------------------------------------------------------------------------
void TreplaceDialogFrm::cancelBtnClick(TObject *Sender)
{
  this->Close();        
}
//---------------------------------------------------------------------------
void TreplaceDialogFrm::findTextChange(TObject *Sender)
{
  if (findText->Text == "") {
    findNextBtn->Enabled = false;
    replaceBtn->Enabled = false;
    replaceAllBtn->Enabled = false;
  } else {
    findNextBtn->Enabled = true;
    findNextBtn->Default = true;
    replaceBtn->Enabled = true;
    replaceAllBtn->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void TreplaceDialogFrm::replaceBtnClick(TObject *Sender)
{
  replaceAll = false;
  Main->ReplaceDialogReplace();
}
//---------------------------------------------------------------------------
void TreplaceDialogFrm::replaceAllBtnClick(TObject *Sender)
{
  replaceAll = true;
  Main->ReplaceDialogReplace();
}
//---------------------------------------------------------------------------
