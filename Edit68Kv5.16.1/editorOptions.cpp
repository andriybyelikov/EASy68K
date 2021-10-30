//---------------------------------------------------------------------------
//   Author: Charles Kelly,
//           Monroe County Community College
//           http://www.monroeccc.edu/ckelly
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "editorOptions.h"
#include "textS.h"
#include "asm.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TEditorOptionsForm *EditorOptionsForm;

extern tabTypes tabType;
extern bool autoIndent;
extern bool realTabs;

extern FontStyle codeStyle;
extern FontStyle unknownStyle;
extern FontStyle directiveStyle;
extern FontStyle commentStyle;
extern FontStyle labelStyle;
extern FontStyle structureStyle;
extern FontStyle errorStyle;
extern FontStyle textStyle;
extern TColor backColor;

extern bool highlightDisabled;

//---------------------------------------------------------------------------
void TEditorOptionsForm::cmdOKClick(TObject *Sender)
{
  AnsiString str;
  TPoint CurPos; //saves the cursor position
  bool modifiedSave;
  TTextStuff *Active;
  int eventMask;
  int selStart, selLength;

  try {

    // Set font for active window only
    Active = (TTextStuff*)Main->ActiveMDIChild;
    //disable all RichEdit events
    eventMask = ::SendMessage(Active->SourceText->Handle,EM_SETEVENTMASK,0,0);
    ::SendMessage(Active->SourceText->Handle,WM_SETREDRAW,false,0);

    selStart = Active->SourceText->SelStart;
    selLength = Active->SourceText->SelLength;
    Active->SourceText->SelectAll();                    // Select all text
    Active->SourceText->SelAttributes->Protected = false;      // turn off protection
    Active->SourceText->SelAttributes->Name = cbFont->Text;
    Active->SourceText->SelAttributes->Size = StrToInt(cbSize->Text);
    Active->SourceText->Font->Name = cbFont->Text;      // set font name
    Active->SourceText->Font->Size = StrToInt(cbSize->Text);

    if (EditorOptionsForm->AssemblyTabs->Checked == true)
      Active->Project.TabType = Assembly;
    else
      Active->Project.TabType = Fixed;

    // limit tab sizes
    if (FixedTabSize->Value < FixedTabSize->MinValue)
      FixedTabSize->Value = FixedTabSize->MinValue;
    else if (FixedTabSize->Value > FixedTabSize->MaxValue )
      FixedTabSize->Value = FixedTabSize->MaxValue;
    // Some users were requesting tab size of 6. By commenting out the following
    // line they will be able to manually enter the number 6 in the tab size
    // text box but the spacing will not be correct for all font sizes.
    //FixedTabSize->Value -= (FixedTabSize->Value % FixedTabSize->Increment);

    Active->Project.TabSize = FixedTabSize->Value;
    Active->SourceText->SelectAll();      // Select all text
    Active->SetTabs();                    // set tabs

    ::SendMessage(Active->SourceText->Handle,WM_SETREDRAW,true,0);
    ::InvalidateRect(Active->SourceText->Handle,0,true);

    Active->SourceText->SelectAll();                    // Select all text
    Active->SourceText->SelAttributes->Protected = true;      // protect all text
    Active->SourceText->SelStart = selStart;
    Active->SourceText->SelLength = selLength;
    Active->SourceText->Modified = modifiedSave;  // restore modified

    // enable RichEdit events
    ::SendMessage(Active->SourceText->Handle,EM_SETEVENTMASK,0,eventMask);

    // Set color and syntax style for all text windows
    for (int i = Main->MDIChildCount-1; i >= 0; i--)
    {
      Active = (TTextStuff*)Main->MDIChildren[i];
      modifiedSave = Active->SourceText->Modified;     // save modified

      //disable all RichEdit events
      eventMask = ::SendMessage(Active->SourceText->Handle,EM_SETEVENTMASK,0,0);
      ::SendMessage(Active->SourceText->Handle,WM_SETREDRAW,false,0);

      if (styleChange) {
        highlightDisabled = false;
        // save font styles
        codeStyle = codeStyleTemp;
        unknownStyle = unknownStyleTemp;
        directiveStyle = directiveStyleTemp;
        commentStyle = commentStyleTemp;
        labelStyle = labelStyleTemp;
        structureStyle = structureStyleTemp;
        errorStyle = errorStyleTemp;
        textStyle = textStyleTemp;
        if (syntaxDisabled) {
          Active->SourceText->SelectAll();
          Active->SourceText->SelAttributes->Color = codeStyle.color;
          Active->SourceText->SelAttributes->Style = TFontStyles();   // clear styles
        } else
          Active->colorHighlight(0,Active->SourceText->Lines->Count);
        highlightDisabled = syntaxDisabled;
        backColor = backColorTemp;
        Active->SourceText->Color = backColor;
      }

      // force update
      ::SendMessage(Active->SourceText->Handle,WM_SETREDRAW,true,0);
      ::InvalidateRect(Active->SourceText->Handle,0,true);

      Active->SourceText->SelectAll();                    // Select all text
      Active->SourceText->SelAttributes->Protected = true;      // protect all text
      Active->SourceText->SelStart = selStart;
      Active->SourceText->SelLength = selLength;
      Active->SourceText->Modified = modifiedSave;  // restore modified

      // enable RichEdit events
      ::SendMessage(Active->SourceText->Handle,EM_SETEVENTMASK,0,eventMask);

      Active->UpdateStatusBar();
    }
  } catch( ... ) {
    MessageDlg("Error in NewProject()." ,mtWarning, TMsgDlgButtons() << mbOK,0);
  }

  Close();      // close Editor Options
}

//---------------------------------------------------------------------------


void TEditorOptionsForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == VK_F1)
     Main->displayHelp("EDIT_OPTIONS");

}
//---------------------------------------------------------------------------

void TEditorOptionsForm::AutoIndentClick(TObject *Sender)
{
  autoIndent = AutoIndent->Checked;
}
//---------------------------------------------------------------------------

void TEditorOptionsForm::AutoIndentKeyPress(TObject *Sender,
      char &Key)
{
  autoIndent = AutoIndent->Checked;
}
//---------------------------------------------------------------------------

void TEditorOptionsForm::RealTabsClick(TObject *Sender)
{
  realTabs = RealTabs->Checked;
}
//---------------------------------------------------------------------------

void TEditorOptionsForm::RealTabsKeyPress(TObject *Sender,
      char &Key)
{
  realTabs = RealTabs->Checked;
}
//---------------------------------------------------------------------------


void TEditorOptionsForm::cmdHelpClick(TObject *Sender)
{
  Main->displayHelp("EDIT_OPTIONS");
}
//---------------------------------------------------------------------------

void TEditorOptionsForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  styleChange = false;
}
//---------------------------------------------------------------------------
