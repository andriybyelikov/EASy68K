//---------------------------------------------------------------------------

#ifndef Stack1H
#define Stack1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TStackFrm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label2;
        TCSpinButton *CSpinButton1;
        TComboBox *whichStack;
        void FormCreate(TObject *Sender);
        void FormPaint(TObject *Sender);
        void FormResize(TObject *Sender);
        void FormShow(TObject *Sender);
        void CSpinButton1UpClick(TObject *Sender);
        void CSpinButton1DownClick(TObject *Sender);
        void FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void whichStackChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TStackFrm(TComponent* Owner);
        void BringToFront();
        void DisplayStack();
        void updateDisplay();
};
//---------------------------------------------------------------------------
extern PACKAGE TStackFrm *StackFrm;
//---------------------------------------------------------------------------
#endif
