//---------------------------------------------------------------------------

#ifndef optionsSH
#define optionsSH
//---------------------------------------------------------------------------
class TOptions : public TForm
{
__published:	// IDE-managed Components
TButton *Save;
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
public:		// User declarations
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
