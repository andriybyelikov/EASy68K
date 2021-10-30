#ifndef editorOptionsH
#define editorOptionsH

//---------------------------------------------------------------------------
class TEditorOptionsForm : public TForm
{
__published:	// IDE-managed Components
        void cmdOKClick(TObject *Sender);


        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void cmdHelpClick(TObject *Sender);
        void AutoIndentClick(TObject *Sender);
        void AutoIndentKeyPress(TObject *Sender, char &Key);
        void RealTabsClick(TObject *Sender);
        void RealTabsKeyPress(TObject *Sender, char &Key);

        void FormClose(TObject *Sender, TCloseAction &Action);
};

#endif
