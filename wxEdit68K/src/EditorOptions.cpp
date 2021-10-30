#include "EditorOptions.h"

#include <cstdio>
#include <wx/xrc/xmlres.h>
#include <wx/stattext.h>
#include <wx/string.h>

#include <wx/listbox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>




EditorOptions::EditorOptions(wxWindow *parent, MyAuiNotebook *notebook)
    : wxDialog()
{
    wxXmlResource::Get()->Load("../src/editor_options.xrc");
    wxXmlResource::Get()->LoadDialog(this, parent, "editor_options_dlg");

    wxRichTextCtrl *richtext = XRCCTRL(*this, "editor_pre", wxRichTextCtrl);
    richtext->SetFont(wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL));
    richtext->SetValue(
        "* Syntax Highlight\n"
        "START  MOVE.B #1,D0\n"
        "       Macro/Other\n"
        "   if <NE> then\n"
        "   of <NE> tehn\n"
        "       DC.B 'HELLO'\n");
    richtext->Disable();

    this->notebook = notebook;

    this->inElementClick = false;
    this->styleChange = false;
    this->syntaxDisabled = false;
}



void EditorOptions::OnInitDialog(wxInitDialogEvent& event)
{
    wxWindow *currentPage = this->notebook->GetCurrentPage();
    MyRichTextCtrl *richtext = static_cast<MyRichTextCtrl *>(currentPage);

    // set current file info font name and font size (legacy)

    XRCCTRL(*this, "current_tab_size", wxStaticText)->SetLabel(
        wxString::Format("%d", richtext->m_project.tabSize));
    if (richtext->m_project.tabType == Assembly) {
        XRCCTRL(*this, "current_tab_type", wxStaticText)->SetLabel("Assembly");
    } else { // richtext->m_project.tabType == Fixed
        XRCCTRL(*this, "current_tab_type", wxStaticText)->SetLabel("Fixed");
    }

    codeStyleTemp = richtext->codeStyle;
    unknownStyleTemp = richtext->unknownStyle;
    directiveStyleTemp = richtext->directiveStyle;
    commentStyleTemp = richtext->commentStyle;
    labelStyleTemp = richtext->labelStyle;
    structureStyleTemp = richtext->structureStyle;
    errorStyleTemp = richtext->errorStyle;
    textStyleTemp = richtext->textStyle;
    backColorTemp = richtext->backColor;

    this->highlightPreview();
}

void EditorOptions::highlightPreview()
{
    wxWindow *currentPage = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = XRCCTRL(*this, "editor_pre", wxRichTextCtrl);

    wxString lexemes[] = {
        "* Syntax Highlight", // comment
        "START",              // label
        "MOVE.B #1,D0",       // code
        "Macro/Other",        // macro/other
        "if <NE> then",       // structured
        "of <NE> tehn",       // structure error
        "DC.B",               // directive
        "'HELLO'"             // text
    };

    /*wxColor colors[] = {
        wxColor(0, 0, 255),
        wxColor(128, 0, 192),
        wxColor(0, 0, 0),
        wxColor(128, 128, 0),
        wxColor(128, 0, 0),
        wxColor(255, 0, 0),
        wxColor(0, 128, 0),
        wxColor(0, 128, 128)
    };*/

    const FontStyle *fs[] = {
        &this->commentStyleTemp,
        &this->labelStyleTemp,
        &this->codeStyleTemp,
        &this->unknownStyleTemp,
        &this->structureStyleTemp,
        &this->errorStyleTemp,
        &this->directiveStyleTemp,
        &this->textStyleTemp
    };

    for (int i = 0; i < 8; i++) {
        wxRichTextAttr attr;
        attr.SetTextColour(fs[i]->color);
        if (fs[i]->bold)
            attr.SetFontWeight(wxFONTWEIGHT_BOLD);
        else
            attr.SetFontWeight(wxFONTWEIGHT_NORMAL);
        if (fs[i]->italic)
            attr.SetFontStyle(wxFONTSTYLE_ITALIC);
        else
            attr.SetFontStyle(wxFONTSTYLE_NORMAL);
        attr.SetFontUnderlined(fs[i]->underline);
        int pos = richtext->GetValue().Find(lexemes[i]);
        int len = wxString(lexemes[i]).Length();
        richtext->SetStyleEx(
            wxRichTextRange(pos, pos + len), attr, wxRICHTEXT_SETSTYLE_NONE);
    }
    richtext->SetBackgroundColour(this->backColorTemp);

    richtext->Refresh();
}

void EditorOptions::ColorPickerChanged(wxColourPickerEvent& evt)
{
    SetSyntaxPreviewColor(evt.GetColour());
}

void EditorOptions::SetSyntaxPreviewColor(wxColor color)
{
    wxListBox *listbox = XRCCTRL(*this, "element_listbox", wxListBox);

    FontStyle *fs[] = {
        &this->codeStyleTemp,
        &this->commentStyleTemp,
        &this->directiveStyleTemp,
        &this->labelStyleTemp,
        &this->unknownStyleTemp,
        &this->structureStyleTemp,
        &this->errorStyleTemp,
        &this->textStyleTemp
    };

    int sel = listbox->GetSelection();
    if (sel == 8)
        this->backColorTemp = color;
    else
        fs[sel]->color = color;
    
    this->highlightPreview();

    this->styleChange = true;

    wxChoice *cb = XRCCTRL(*this, "presets_choice", wxChoice);
    cb->SetSelection(3); // custom

    this->syntaxDisabled = false;
}

void EditorOptions::SyntaxComboChange(wxCommandEvent& evt)
{
    wxListBox *listbox = XRCCTRL(*this, "element_listbox", wxListBox);
    wxCheckBox *bold = XRCCTRL(*this, "bold_checkbox", wxCheckBox);
    wxCheckBox *italic = XRCCTRL(*this, "italic_checkbox", wxCheckBox);
    wxCheckBox *underline = XRCCTRL(*this, "underline_checkbox", wxCheckBox);
    wxChoice *syntaxCombo = XRCCTRL(*this, "presets_choice", wxChoice);

    listbox->SetSelection(-1); // clear item selection
    bold->SetValue(false);
    italic->SetValue(false);
    underline->SetValue(false);
    this->syntaxDisabled = false;
    if (syntaxCombo->GetSelection() == 3) // if Custom
        return;
    
    // clear fontstyles

    FontStyle *fs[] = {
        &this->codeStyleTemp,
        &this->commentStyleTemp,
        &this->directiveStyleTemp,
        &this->labelStyleTemp,
        &this->unknownStyleTemp,
        &this->structureStyleTemp,
        &this->errorStyleTemp,
        &this->textStyleTemp
    };

    for (int i = 0; i < 8; i++) {
        fs[i]->bold = false;
        fs[i]->italic = false;
        fs[i]->underline = false;
    }

    switch (syntaxCombo->GetSelection()) {
    case 0: // Color 1
        this->codeStyleTemp.color = DEFAULT_CODE_COLOR;
        this->unknownStyleTemp.color = DEFAULT_UNKNOWN_COLOR;
        this->directiveStyleTemp.color = DEFAULT_DIRECTIVE_COLOR;
        this->commentStyleTemp.color = DEFAULT_COMMENT_COLOR;
        this->labelStyleTemp.color = DEFAULT_LABEL_COLOR;
        this->structureStyleTemp.color = DEFAULT_STRUCTURE_COLOR;
        this->errorStyleTemp.color = DEFAULT_ERROR_COLOR;
        this->textStyleTemp.color = DEFAULT_TEXT_COLOR;
        break;
    case 1: // Color 2
        this->codeStyleTemp.color = DEFAULT_CODE_COLOR;
        this->unknownStyleTemp.color = wxColor(128, 0, 128); // purple
        this->directiveStyleTemp.color = wxColor(0, 0, 255); // blue
        this->commentStyleTemp.color = wxColor(0, 128, 0); // green
        this->labelStyleTemp.color = wxColor(0, 0, 128); // navy
        this->structureStyleTemp.color = wxColor(0, 0, 255); // blue
        this->errorStyleTemp.color = wxColor(255, 0, 0); // red
        this->textStyleTemp.color = wxColor(128, 0, 0); // maroon
        break;
    case 2: // Mono
        this->codeStyleTemp.color = DEFAULT_CODE_COLOR;
        this->unknownStyleTemp.color = DEFAULT_CODE_COLOR;
        this->directiveStyleTemp.color = DEFAULT_CODE_COLOR;
        this->commentStyleTemp.color = DEFAULT_CODE_COLOR;
        this->labelStyleTemp.color = DEFAULT_CODE_COLOR;
        this->structureStyleTemp.color = DEFAULT_CODE_COLOR;
        this->errorStyleTemp.color = DEFAULT_CODE_COLOR;
        this->textStyleTemp.color = DEFAULT_CODE_COLOR;
        this->unknownStyleTemp.italic = true;
        this->unknownStyleTemp.underline = true;
        this->directiveStyleTemp.bold = true;
        this->commentStyleTemp.italic = true;
        this->labelStyleTemp.bold = true;
        this->structureStyleTemp.bold = true;
        this->errorStyleTemp.underline = true;
        break;
    default: // Disabled
        this->codeStyleTemp.color = DEFAULT_CODE_COLOR;
        this->unknownStyleTemp.color = DEFAULT_CODE_COLOR;
        this->directiveStyleTemp.color = DEFAULT_CODE_COLOR;
        this->commentStyleTemp.color = DEFAULT_CODE_COLOR;
        this->labelStyleTemp.color = DEFAULT_CODE_COLOR;
        this->structureStyleTemp.color = DEFAULT_CODE_COLOR;
        this->errorStyleTemp.color = DEFAULT_CODE_COLOR;
        this->textStyleTemp.color = DEFAULT_CODE_COLOR;
        this->syntaxDisabled = true;
    }

    this->highlightPreview();
    this->styleChange = true;
}

void EditorOptions::SetSyntaxPreviewStyle()
{
    wxListBox *listbox = XRCCTRL(*this, "element_listbox", wxListBox);
    wxCheckBox *bold = XRCCTRL(*this, "bold_checkbox", wxCheckBox);
    wxCheckBox *italic = XRCCTRL(*this, "italic_checkbox", wxCheckBox);
    wxCheckBox *underline = XRCCTRL(*this, "underline_checkbox", wxCheckBox);

    FontStyle *fs[] = {
        &this->codeStyleTemp,
        &this->commentStyleTemp,
        &this->directiveStyleTemp,
        &this->labelStyleTemp,
        &this->unknownStyleTemp,
        &this->structureStyleTemp,
        &this->errorStyleTemp,
        &this->textStyleTemp
    };

    int i = listbox->GetSelection();
    fs[i]->bold = bold->GetValue();
    fs[i]->italic = italic->GetValue();
    fs[i]->underline = underline->GetValue();

    this->highlightPreview();

    this->styleChange = true;

    wxChoice *cb = XRCCTRL(*this, "presets_choice", wxChoice);
    cb->SetSelection(3); // custom

    this->syntaxDisabled = false;
}

void EditorOptions::BoldClick(wxCommandEvent& event)
{
    if (!this->inElementClick)
        this->SetSyntaxPreviewStyle();
}

void EditorOptions::ItalicClick(wxCommandEvent& event)
{
    if (!this->inElementClick)
        this->SetSyntaxPreviewStyle();
}

void EditorOptions::UnderlineClick(wxCommandEvent& event)
{
    if (!this->inElementClick)
        this->SetSyntaxPreviewStyle();
}

void EditorOptions::ElementClick(wxCommandEvent& event)
{
    wxListBox *listbox = XRCCTRL(*this, "element_listbox", wxListBox);
    wxColourPickerCtrl *clrpicker = XRCCTRL(*this, "color_picker", wxColourPickerCtrl);
    wxCheckBox *bold = XRCCTRL(*this, "bold_checkbox", wxCheckBox);
    wxCheckBox *italic = XRCCTRL(*this, "italic_checkbox", wxCheckBox);
    wxCheckBox *underline = XRCCTRL(*this, "underline_checkbox", wxCheckBox);

    this->inElementClick = true;

    FontStyle *fs[] = {
        &this->codeStyleTemp,
        &this->commentStyleTemp,
        &this->directiveStyleTemp,
        &this->labelStyleTemp,
        &this->unknownStyleTemp,
        &this->structureStyleTemp,
        &this->errorStyleTemp,
        &this->textStyleTemp
    };

    int i = listbox->GetSelection();
    if (i != 8) {
        clrpicker->SetColour(fs[i]->color);
        bold->SetValue(fs[i]->bold);
        italic->SetValue(fs[i]->italic);
        underline->SetValue(fs[i]->underline);
    } else {
        clrpicker->SetColour(this->backColorTemp);
    }

    this->inElementClick = false;
}

wxBEGIN_EVENT_TABLE(EditorOptions, wxDialog)
    EVT_INIT_DIALOG(EditorOptions::OnInitDialog)
    EVT_CHOICE(XRCID("presets_choice"), EditorOptions::SyntaxComboChange)
    EVT_COLOURPICKER_CHANGED(XRCID("color_picker"),
        EditorOptions::ColorPickerChanged)
    EVT_CHECKBOX(XRCID("bold_checkbox"), EditorOptions::BoldClick)
    EVT_CHECKBOX(XRCID("italic_checkbox"), EditorOptions::ItalicClick)
    EVT_CHECKBOX(XRCID("underline_checkbox"), EditorOptions::UnderlineClick)
    EVT_LISTBOX(XRCID("element_listbox"), EditorOptions::ElementClick)
wxEND_EVENT_TABLE()
