//---------------------------------------------------------------------------
//   Author: Chuck Kelly,
//           Monroe County Community College
//           http://www.monroeccc.edu/ckelly
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Optionsu.h"
#include "SIM68Ku.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAutoTraceOptions *AutoTraceOptions;
//---------------------------------------------------------------------------
TAutoTraceOptions::TAutoTraceOptions(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TAutoTraceOptions::OKClick(TObject *Sender)
{
  Form1->AutoTraceTimer->Interval = StrToInt(AutoTraceInterval->Text);
  Close();        
}
//---------------------------------------------------------------------------

void TAutoTraceOptions::CancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

