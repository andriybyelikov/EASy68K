#ifndef EDITOR_GUI_DEFS_H
#define EDITOR_GUI_DEFS_H

#include <wx/colour.h>

// tab types
enum TabTypes { Assembly, Fixed };

// syntax highlight
typedef struct {
    wxColor color;
    bool bold;
    bool italic;
    bool underline;
} FontStyle;

const wxColor DEFAULT_CODE_COLOR = wxColor(0, 0, 0); // black
const wxColor DEFAULT_UNKNOWN_COLOR = wxColor(128, 128, 0); // olive
const wxColor DEFAULT_DIRECTIVE_COLOR = wxColor(0, 128, 0); // green
const wxColor DEFAULT_COMMENT_COLOR = wxColor(0, 0, 255); // blue
const wxColor DEFAULT_LABEL_COLOR = wxColor(128, 0, 128); // purple
const wxColor DEFAULT_STRUCTURE_COLOR = wxColor(128, 0, 0); // maroon
const wxColor DEFAULT_ERROR_COLOR = wxColor(255, 0, 0); // red
const wxColor DEFAULT_TEXT_COLOR = wxColor(0, 128, 128); // teal
const wxColor DEFAULT_BACK_COLOR = wxColor(255, 255, 255); // white

#endif
