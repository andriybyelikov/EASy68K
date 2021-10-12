//---------------------------------------------------------------------------

#ifndef OptionsuH
#define OptionsuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAutoTraceOptions : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TBitBtn *OK;
        TUpDown *UpDown1;
        TEdit *AutoTraceInterval;
        TBitBtn *Cancel;
        TCheckBox *DisableDisplay;
        void OKClick(TObject *Sender);
        void CancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TAutoTraceOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAutoTraceOptions *AutoTraceOptions;
//---------------------------------------------------------------------------
#endif
