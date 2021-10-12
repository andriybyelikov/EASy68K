//---------------------------------------------------------------------------

#ifndef Preview_dlgH
#define Preview_dlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPreviewDlg : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        void FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TPreviewDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPreviewDlg *PreviewDlg;
//---------------------------------------------------------------------------
#endif
