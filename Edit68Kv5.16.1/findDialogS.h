//---------------------------------------------------------------------------

#ifndef findDialogSH
#define findDialogSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "mainS.h"
//---------------------------------------------------------------------------
class TfindDialogFrm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *findText;
        TButton *findNextBtn;
        TButton *cancelBtn;
        TCheckBox *wholeWordChk;
        TLabel *Label2;
        TCheckBox *matchCaseChk;
        TLabel *Label3;
        void findNextBtnClick(TObject *Sender);
        void cancelBtnClick(TObject *Sender);
        void findTextChange(TObject *Sender);
        void FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TfindDialogFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfindDialogFrm *findDialogFrm;
//---------------------------------------------------------------------------
#endif
