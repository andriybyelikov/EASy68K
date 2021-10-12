//---------------------------------------------------------------------------
//   Author: Charles Kelly
//           www.easy68k.com
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FullscreenOptions.h"
#include "extern.h"

//FullScreenMonitor

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFullscreenOptions *frmFullscreenOptions;
//---------------------------------------------------------------------------

TfrmFullscreenOptions::TfrmFullscreenOptions(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void TfrmFullscreenOptions::FormShow(TObject *Sender)
{
  txtScreenNumber->Text = static_cast<int>(FullScreenMonitor) + 1;
  txtScreenNumber->SetFocus();
  txtScreenNumberChange(NULL);
}

//---------------------------------------------------------------------------

void TfrmFullscreenOptions::txtScreenNumberChange(
      TObject *Sender)
{
  int scrNumber = txtScreenNumber->Text.ToIntDef(-1);

  if ((scrNumber >= 1) && (scrNumber <= GetSystemMetrics(SM_CMONITORS))){
    cmdOk->Enabled = true;
  }else{
    cmdOk->Enabled = false;
  }
}
//---------------------------------------------------------------------------

void TfrmFullscreenOptions::cmdOkClick(TObject *Sender)
{
  FullScreenMonitor = static_cast<char>(txtScreenNumber->Text.ToInt() - 1);
  Close();
}
//---------------------------------------------------------------------------

void TfrmFullscreenOptions::cmdCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

