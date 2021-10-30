#include "AssemblerOptions.h"

#include <wx/xrc/xmlres.h>
#include <wx/button.h>

AssemblerOptions::AssemblerOptions(wxWindow *parent) : wxDialog()
{
    wxXmlResource::Get()->Load("../src/assembler_options.xrc");
    wxXmlResource::Get()->LoadDialog(this, parent, "assembler_options_dlg");
}

void AssemblerOptions::OnInitDialog(wxInitDialogEvent& event)
{
    // focus assembler options tab/notebookpage

    // load up template
    // if template exists in load template content
    // set template editor font to same as current file editor font size and name

    // initialize template modified boolean to false
}

void AssemblerOptions::OnOK(wxCommandEvent& event)
{}

void AssemblerOptions::OnCancel(wxCommandEvent& event)
{}

void AssemblerOptions::OnSave(wxCommandEvent& event)
{
    // flush save edited template to file
}

wxBEGIN_EVENT_TABLE(AssemblerOptions, wxDialog)
    EVT_INIT_DIALOG(AssemblerOptions::OnInitDialog)
    //EVT_BUTTON(wxID_OK, AssemblerOptions::OnOK)
    //EVT_BUTTON(wxID_CANCEL, AssemblerOptions::OnCancel)
    EVT_BUTTON(XRCID("save_template"), AssemblerOptions::OnSave)
wxEND_EVENT_TABLE()
