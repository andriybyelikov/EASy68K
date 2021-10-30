#ifndef MY_RICH_TEXT_CTRL_H
#define MY_RICH_TEXT_CTRL_H

#include <wx/richtext/richtextctrl.h>

// Structure track all the info for the current file loaded into the editor
// these values are used by various parts of the program for different
// operations
struct FileInfo {
    wxString currentFile; // path of the file loaded in an editor
    int tabType;
    int tabSize;
    bool createList;
    bool listOpen;
    bool modified;
    bool isSource;
    bool hasName; // true if the file has a valid filename
};

#include "editor_gui_defs.h"

class MyRichTextCtrl : public wxRichTextCtrl
{
public:
    MyRichTextCtrl(wxWindow *parent);
    void NewProject(const wxString& type);
    void NewSourceFile();

    FileInfo m_project;

    FontStyle
        codeStyle,
        unknownStyle,
        directiveStyle,
        commentStyle,
        labelStyle,
        structureStyle,
        errorStyle,
        textStyle;
    wxColor backColor;
};

#endif
