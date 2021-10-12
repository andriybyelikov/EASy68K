//---------------------------------------------------------------------------

#ifndef editorOptionsH
#define editorOptionsH

//---------------------------------------------------------------------------
class TEditorOptionsForm : public TForm
{
__published:	// IDE-managed Components
        

        void cmdCancelClick(TObject *Sender);
        void cmdOKClick(TObject *Sender);
        void FormShow(TObject *Sender);
        void cbFontChange(TObject *Sender);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void AutoIndentClick(TObject *Sender);
        void AutoIndentKeyPress(TObject *Sender, char &Key);
        void RealTabsClick(TObject *Sender);
        void RealTabsKeyPress(TObject *Sender, char &Key);
        void cmdHelpClick(TObject *Sender);
        void StaticTextClick(TObject *Sender);
        void ItalicClick(TObject *Sender);
        void UnderlineClick(TObject *Sender);
        void ElementClick(TObject *Sender);
        void BoldClick(TObject *Sender);
        void FormClose(TObject *Sender, TCloseAction &Action);
        void SyntaxComboChange(TObject *Sender);
public:		// User declarations
        TEditorOptionsForm(TComponent* Owner);
        void setSyntaxPreviewColor(TColor color);
        void setSyntaxPreviewStyle();
        void highlightPreview();
};

#endif
