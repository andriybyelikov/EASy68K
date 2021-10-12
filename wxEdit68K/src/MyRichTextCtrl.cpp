#include <wx/string.h>

#include "MyRichTextCtrl.h"

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
