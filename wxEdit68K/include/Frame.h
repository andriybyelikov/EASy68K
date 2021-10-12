#include <wx/frame.h>
#include "MyAuiNotebook.h"

class Frame: public wxFrame
{
public:
    Frame();

    void OnFileNew(wxCommandEvent& evt);
    void OnFileOpen(wxCommandEvent& evt);
    void OnFileSave(wxCommandEvent& evt);
    void OnFileSaveAs(wxCommandEvent& evt);
    void OnFileClose(wxCommandEvent& evt);
    void OnFileQuit(wxCommandEvent& evt);

    void OnEditUndo(wxCommandEvent& evt);
    void OnEditRedo(wxCommandEvent& evt);
    void OnEditCut(wxCommandEvent& evt);
    void OnEditCopy(wxCommandEvent& evt);
    void OnEditPaste(wxCommandEvent& evt);
    void OnEditSelectAll(wxCommandEvent& evt);
    void OnEditCommentSelection(wxCommandEvent& evt);
    void OnEditUncommentSelection(wxCommandEvent& evt);
    //void OnEditFind(wxCommandEvent& evt);
    //void OnEditFindNext(wxCommandEvent& evt);
    //void OnEditFindAndReplace(wxCommandEvent& evt);

    void OnProjectAssembleSource(wxCommandEvent& evt);

    void OnOptionsAssemblerOptions(wxCommandEvent& evt);
    void OnOptionsEditorOptions(wxCommandEvent& evt);

    void OnHelpHelp(wxCommandEvent& evt);
    void OnHelpAbout(wxCommandEvent& evt);

private:
    MyAuiNotebook *notebook;
    wxPathList *openFiles;

    // From the original implementation:
    int iNewFiles;   // Keeps track of how many new files have been opened and
                     // the number is used with the naming of new files ex.
                     // "untitled1"
    int iListsOpen;  // Tracks how many list files are open
    int iSourceOpen; // Track how many source files are open

    wxDECLARE_EVENT_TABLE();
};
