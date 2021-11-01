#include <wx/string.h>

#include "MyRichTextCtrl.h"

MyRichTextCtrl::MyRichTextCtrl(wxWindow *parent) : wxRichTextCtrl(parent)
{
    this->m_project.tabSize = 0;
    this->m_project.tabType = 0;

    // don't use C compound literals in C++
    // the following code may work in GCC but MSVC does not accept it
    /*codeStyle = (FontStyle){*wxBLACK, false, false, false};
    unknownStyle = (FontStyle){ *wxBLACK, false, false, false };
    directiveStyle = (FontStyle){ *wxBLACK, false, false, false };
    commentStyle = (FontStyle){ *wxBLACK, false, false, false };
    labelStyle = (FontStyle){ *wxBLACK, false, false, false };
    structureStyle = (FontStyle){ *wxBLACK, false, false, false };
    errorStyle = (FontStyle){ *wxBLACK, false, false, false };
    textStyle = (FontStyle){ *wxBLACK, false, false, false };*/
    backColor = *wxWHITE;
}


void MyRichTextCtrl::NewProject(const wxString &type)
{
    if (type == "Source") {
    } else if (type == "List") {

    }
}

void MyRichTextCtrl::NewSourceFile()
{
    NewProject("Source");
}
