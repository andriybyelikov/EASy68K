#include "MyAuiNotebook.h"
#include <wx/aui/dockart.h>

MyAuiNotebook::MyAuiNotebook(wxWindow *parent) : wxAuiNotebook(parent)
{
    this->m_mgr.SetFlags(wxAUI_MGR_VENETIAN_BLINDS_HINT);
    wxFont font(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    this->SetFont(font);
}
