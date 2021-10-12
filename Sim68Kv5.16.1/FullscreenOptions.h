//---------------------------------------------------------------------------

#ifndef FullscreenOptionsH
#define FullscreenOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmFullscreenOptions : public TForm
{
__published:	// IDE-managed Components
        TEdit *txtScreenNumber;
        TLabel *Label1;
        TButton *cmdOk;
        TButton *cmdCancel;
        void FormShow(TObject *Sender);
        void txtScreenNumberChange(TObject *Sender);
        void cmdOkClick(TObject *Sender);
        void cmdCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TfrmFullscreenOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFullscreenOptions *frmFullscreenOptions;
//---------------------------------------------------------------------------
#endif
