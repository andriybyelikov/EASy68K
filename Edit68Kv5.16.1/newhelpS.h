//---------------------------------------------------------------------------

#ifndef newhelpSH
#define newhelpSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TNewHelp : public TForm
{
__published:	// IDE-managed Components
        TCppWebBrowser *Help;
        void FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TNewHelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewHelp *NewHelp;
//---------------------------------------------------------------------------
#endif
