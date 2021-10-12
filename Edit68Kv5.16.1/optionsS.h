//---------------------------------------------------------------------------

#ifndef optionsSH
#define optionsSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TOptions : public TForm
{
__published:	// IDE-managed Components
        TButton *cmdOK;
        TButton *cmdCancel;
        TPageControl *PageControl;
        TTabSheet *tbsAssOpt;
        TGroupBox *GroupBox1;
        TCheckBox *chkGenList;
        TCheckBox *chkGenSRec;
        TCheckBox *chkSave;
        TGroupBox *GroupBox2;
        TCheckBox *chkCrossRef;
        TCheckBox *chkMacEx;
        TCheckBox *chkConstantsEx;
        TTabSheet *TabSheet1;
        TButton *Save;
        TRichEdit *Template;
        TCheckBox *chkStrucEx;
        TCheckBox *chkShowWarnings;
        TCheckBox *chkBitfield;
        void cmdCancelClick(TObject *Sender);
        void cmdOKClick(TObject *Sender);
        void FormShow(TObject *Sender);
        void SaveClick(TObject *Sender);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        TOptions(TComponent* Owner);
        void SaveSettings();   //saves editor settings to file
        void LoadSettings();   //loads editor settings from file
        void defaultSettings(); // sets editor defaults
        bool bSave;  //checks if editor should save before assemble
        int iSelStart;
};
//---------------------------------------------------------------------------
extern PACKAGE TOptions *Options;
//---------------------------------------------------------------------------
#endif
