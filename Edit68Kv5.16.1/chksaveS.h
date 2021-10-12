//---------------------------------------------------------------------------

#ifndef chksaveSH
#define chksaveSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TChkSave : public TForm
{
__published:	// IDE-managed Components
        TButton *btnOK;
        TButton *Button2;
        TLabel *lblMessage;
        void FormCreate(TObject *Sender);
        void btnOKClick(TObject *Sender);
        void Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TChkSave(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChkSave *ChkSave;
//---------------------------------------------------------------------------
#endif
