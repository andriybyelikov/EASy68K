#ifndef ASSEMBLER_OPTIONS_H
#define ASSEMBLER_OPTIONS_H

#include <wx/dialog.h>

// assembler options
class AssemblerOptions : public wxDialog
{
public:
    AssemblerOptions(wxWindow *parent);
    void OnInitDialog(wxInitDialogEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif
