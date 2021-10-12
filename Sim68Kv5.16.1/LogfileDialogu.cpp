//---------------------------------------------------------------------------
//   Author: Chuck Kelly,
//           Monroe County Community College
//           http://www.monroeccc.edu/ckelly
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogfileDialogu.h"
#include "extern.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLogfileDialog *LogfileDialog;
//---------------------------------------------------------------------------
TLogfileDialog::TLogfileDialog(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TLogfileDialog::setMessage(AnsiString str)
{
  Message->Caption = str;
}
