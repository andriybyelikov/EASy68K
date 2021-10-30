#include <wx/dialog.h>
#include <wx/clrpicker.h>
#include <wx/colour.h>
#include "MyAuiNotebook.h"

#include "MyRichTextCtrl.h"

#include "editor_gui_defs.h"

class EditorOptions : public wxDialog
{
public:
    EditorOptions(wxWindow *parent, MyAuiNotebook *notebook);
    void OnInitDialog(wxInitDialogEvent& event);

    void ColorPickerChanged(wxColourPickerEvent& evt);
    void SyntaxComboChange(wxCommandEvent& evt);
    void BoldClick(wxCommandEvent& event);
    void ItalicClick(wxCommandEvent& event);
    void UnderlineClick(wxCommandEvent& event);
    void ElementClick(wxCommandEvent& event);


    void SetSyntaxPreviewColor(wxColor color);
    void SetSyntaxPreviewStyle();
    
    bool inElementClick;
    bool styleChange;
    bool syntaxDisabled;

    MyAuiNotebook *notebook;

    FontStyle
        codeStyleTemp,
        unknownStyleTemp,
        directiveStyleTemp,
        commentStyleTemp,
        labelStyleTemp,
        structureStyleTemp,
        errorStyleTemp,
        textStyleTemp;
    wxColor backColorTemp;
private:
    void highlightPreview();
    wxDECLARE_EVENT_TABLE();
};
