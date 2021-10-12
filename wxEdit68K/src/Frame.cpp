#include <wx/xrc/xmlres.h>

#include <wx/sizer.h>

#include <wx/menu.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/aboutdlg.h>
#include <wx/filefn.h>

#include <wx/filedlg.h>

#include "App.h"
#include "Frame.h"

Frame::Frame() : wxFrame()
{
    wxXmlResource::Get()->Load("../src/resource.xrc");
    wxXmlResource::Get()->LoadFrame(this, nullptr, "frame");

    this->openFiles = new wxPathList();

    // From the original implementation:
    iNewFiles   = 0;
    iListsOpen  = 0;
    iSourceOpen = 0;


    this->notebook = new MyAuiNotebook(this);

    this->SetIcon(wxIcon("../icons/about_icon.png"));

    this->SetSize(wxSize(
        wxGetDisplaySize().GetWidth()  * (float)2/3,
        wxGetDisplaySize().GetHeight() * (float)2/3
    ));
    this->Center();

    this->Show();
}

void Frame::OnFileNew(wxCommandEvent &evt)
{
    wxRichTextCtrl *richtext = new wxRichTextCtrl(this->notebook);

    wxFile *file = new wxFile("../template.NEW");
    wxString *content = new wxString();
    file->ReadAll(content);
    richtext->AppendText(content->GetData());
    
    this->notebook->AddPage(richtext, "untitled.x68");
    /*this->Layout();
    this->Refresh();*/
    this->openFiles->Add("untitled.x68");
}

void Frame::OnFileOpen(wxCommandEvent& evt)
{
    wxFileDialog openFileDialog(this, "Open X68 Source File", "", "",
        "X68 Source Files (*.X68)|*.X68", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
}

void Frame::OnFileSave(wxCommandEvent& evt)
{}

void Frame::OnFileSaveAs(wxCommandEvent& evt)
{
    wxFileDialog saveFileDialog(this, "Save X68 Source File", "", "",
        "X68 Source Files (*.X68)|*.X68", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
}

void Frame::OnFileClose(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    int page_index = this->notebook->GetPageIndex(current_page);
    this->notebook->DeletePage(page_index);
}

void Frame::OnFileQuit(wxCommandEvent& evt)
{
    this->Close();
}

void Frame::OnEditUndo(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->Undo();
    }
}

void Frame::OnEditRedo(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->Redo();
    }
}

void Frame::OnEditCut(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->Cut();
    }
}

void Frame::OnEditCopy(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->Copy();
    }
}

void Frame::OnEditPaste(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->Paste();
    }
}

void Frame::OnEditSelectAll(wxCommandEvent& evt)
{
    wxWindow *current_page = this->notebook->GetCurrentPage();
    wxRichTextCtrl *richtext = static_cast<wxRichTextCtrl *>(current_page);
    if (richtext != NULL) {
        richtext->SelectAll();
    }
}

void Frame::OnEditCommentSelection(wxCommandEvent& evt)
{}

void Frame::OnEditUncommentSelection(wxCommandEvent& evt)
{}

void Frame::OnProjectAssembleSource(wxCommandEvent& evt)
{}

void Frame::OnOptionsAssemblerOptions(wxCommandEvent& evt)
{}

void Frame::OnOptionsEditorOptions(wxCommandEvent& evt)
{
    wxDialog dlg;
    wxXmlResource::Get()->Load("../src/editor_options.xrc");
    wxXmlResource::Get()->LoadDialog(&dlg, this, "editor_options_dlg");

    wxRichTextCtrl *richtext = XRCCTRL(dlg, "editor_pre", wxRichTextCtrl);
    richtext->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL));
    richtext->SetValue(
        "* Syntax Highlight\n"
        "START  MOVE.B #1,D0\n"
        "       Unknown or Macro\n"
        "   if <NE> then\n"
        "   of <NE> tehn\n"
        "       DC.B 'HELLO'\n");
    richtext->Disable();

    dlg.ShowModal();
}

void Frame::OnHelpHelp(wxCommandEvent& evt)
{}

void Frame::OnHelpAbout(wxCommandEvent& event)
{
    wxAboutDialogInfo info;
    info.SetName(_("wxEASy68K Editor/Assembler"));
    info.SetDescription(_("The author of this software assumes no liabilty of its functionality and is not responsible for misuse by the user.  Use at your own risk.  This application is distributed under the GNU general public use license."));
    info.SetVersion(_("0.1.0-dev"));
    info.AddArtist(_("GUI design: Tim Larson"));
    info.AddDeveloper(_("Original assembler code: Paul McKee"));
    info.AddDeveloper(_("Modifications and New Features: Charles Kelly"));
    info.AddDeveloper(_("wxWidgets port: Andriy Byelikov"));
    wxAboutBox(info, NULL);
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_NEW, Frame::OnFileNew)
    EVT_MENU(wxID_OPEN, Frame::OnFileOpen)
    EVT_MENU(wxID_SAVE, Frame::OnFileSave)
    EVT_MENU(wxID_SAVEAS, Frame::OnFileSaveAs)
    EVT_MENU(wxID_CLOSE, Frame::OnFileClose)
    EVT_MENU(wxID_EXIT, Frame::OnFileQuit)
    EVT_MENU(wxID_UNDO, Frame::OnEditUndo)
    EVT_MENU(wxID_REDO, Frame::OnEditRedo)
    EVT_MENU(wxID_CUT, Frame::OnEditCut)
    EVT_MENU(wxID_COPY, Frame::OnEditCopy)
    EVT_MENU(wxID_PASTE, Frame::OnEditPaste)
    EVT_MENU(wxID_SELECTALL, Frame::OnEditSelectAll)
    EVT_MENU(XRCID("menu_options_editor_options"), Frame::OnOptionsEditorOptions)
    EVT_MENU(wxID_ABOUT, Frame::OnHelpAbout)
    EVT_MENU(XRCID("tool_new"), Frame::OnFileNew)
    EVT_MENU(XRCID("tool_open"), Frame::OnFileOpen)
    EVT_MENU(XRCID("tool_save"), Frame::OnFileSave)
    EVT_MENU(XRCID("tool_saveas"), Frame::OnFileSaveAs)
    EVT_MENU(XRCID("tool_close"), Frame::OnFileClose)
    EVT_MENU(XRCID("tool_undo"), Frame::OnEditUndo)
    EVT_MENU(XRCID("tool_redo"), Frame::OnEditRedo)
    EVT_MENU(XRCID("tool_cut"), Frame::OnEditCut)
    EVT_MENU(XRCID("tool_copy"), Frame::OnEditCopy)
    EVT_MENU(XRCID("tool_paste"), Frame::OnEditPaste)
wxEND_EVENT_TABLE()
