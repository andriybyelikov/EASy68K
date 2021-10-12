#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_richtext.h>

#include <wx/richtext/richtextctrl.h>

#include "App.h"
#include "Frame.h"

bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxXmlResource::Get()->InitAllHandlers();

    wxImage::AddHandler(new wxPNGHandler());

    wxXmlResource::Get()->AddHandler(new wxRichTextCtrlXmlHandler);

    new Frame();

    return true;
}

wxIMPLEMENT_APP(App);
