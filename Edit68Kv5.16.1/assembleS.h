//---------------------------------------------------------------------------

#ifndef assembleSH
#define assembleSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAssemblerBox : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblStatus;
        TButton *cmdExecute;
        TButton *cmdClose;
        TImage *Image1;
        TLabel *lblStatus2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *cmdLoadL68;
        void cmdExecuteClick(TObject *Sender);
        void cmdCloseClick(TObject *Sender);
        void FormClose(TObject *Sender, TCloseAction &Action);
        void FormShow(TObject *Sender);
        void cmdLoadL68Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TAssemblerBox(TComponent* Owner);
      
        AnsiString batFileEx; //simulator batch file path
        AnsiString ListF; //list file path
        
};
//---------------------------------------------------------------------------
extern PACKAGE TAssemblerBox *AssemblerBox;
//---------------------------------------------------------------------------
#endif
