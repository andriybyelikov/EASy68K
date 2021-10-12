//---------------------------------------------------------------------------
/*
Program: 68K Editor IDE
Written By: Tim Larson
Program Start Date: January 24, 2002
Modified By: Charles Kelly

*******
PURPOSE
*******
I have designed this program for my CIS 258 Assembly Language Programming using
the 68000 class at Monroe County Community College.


***********
Description
***********

The 68K Editor is a 68000 code editing program that has an integrated assembler.
The IDE allows you to write programs and easily assemble them using a familar
Windows look.  It is designed to work with the 68000 Simulator, written by Charles
Kelly, to run the assembled programs.

------------------------------------------------------------------------------*/


#include <vcl.h>
#include <vcl\Printers.hpp>
#include <fstream.h>

#pragma hdrstop

#include "HtmlHelp.h"
#include "help.h"
#include "mainS.h"
#include "optionsS.h"
#include "editorOptions.h"
#include "assembleS.h"
#include "listS.h"
#include "aboutS.h"
#include "textS.h"
#include "chksaveS.h"
#include "findDialogS.h"
#include "asm.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"
TMain *Main;

extern bool listFlag;           // create Listing file
extern bool objFlag;            // create S-Record file
extern bool CEXflag;            // expand constants
extern bool BITflag;            // True to assemble bitfield instructions
extern bool CREflag;            // display symbol table in listing
extern bool MEXflag;            // macro expansion
extern bool SEXflag;            // structured expansion
extern bool WARflag;            // display warnings
extern tabTypes tabType;
extern bool maximizedEdit;      // true starts child edit window maximized

void SaveFont(TTextStuff *);

//---------------------------------------------------------------------------
bool LoadHtmlHelp()
{
  try {
    HKEY HHKey;
    DWORD PathSize = 255;
    char Path[255];
    bool R = false;

    // try to get the location of hhctrl.ocx from the registry and load it
    if (::RegOpenKeyExA(HKEY_CLASSES_ROOT, HHPathRegKey, 0, KEY_QUERY_VALUE, (void **)&HHKey) == ERROR_SUCCESS)
    {
      if (::RegQueryValueExA(HHKey, "", NULL, NULL, (LPBYTE)Path, &PathSize) == ERROR_SUCCESS)
      {
        HHLibrary = ::LoadLibrary(Path);
      }
      ::RegCloseKey(HHKey);
    }

    // if hhctrl.ocx did not load let LoadLibrary look for it
    if (HHLibrary == 0)
    {
      HHLibrary = ::LoadLibrary("hhctrl.ocx");
    }

    // if hhctrl.ocx loaded set __HtmlHelp to point to HtmlHelp function
    if (HHLibrary != 0)
    {
      __HtmlHelp = (HTML_HELP_PROC) ::GetProcAddress(HHLibrary, "HtmlHelpA");
      R = (__HtmlHelp != NULL);
      if (!R)
      {
        ::FreeLibrary(HHLibrary);
        HHLibrary = 0;
      }
    }
    return R;
  }
  catch(...) {
    ShowMessage("Error loading Html Help");
    return false;
  }
}


//---------------------------------------------------------------------------
TMain::TMain(TComponent* Owner)
        : TForm(Owner)
{

  // initialize helpfile location -- m_asHelpFile is an AnsiString type private
  // member of the TForm1 class

  m_asHelpFile = ExtractFilePath(Application->ExeName) + "help.chm";
  m_asHelpFile = ExpandFileName(m_asHelpFile);

  // make sure the helpfile exists and display a message if not
  if (!FileExists(m_asHelpFile))
    ShowMessage("Help file not found\n" + m_asHelpFile);

  // Load the HTML Help library
  if (!LoadHtmlHelp())
  {
    ShowMessage("HTML Help was not detected on this computer. EASy68K help may not work correctly.");
  }

  // With dynamic loading it's advised to use HH_INITIALIZE. See the comments
  // for OnClose for more information on why...
  if (HHLibrary != 0)
    __HtmlHelp(NULL, NULL, HH_INITIALIZE, (DWORD)&m_Cookie);

  DragAcceptFiles(Handle, true);        // enable drag-n-drop from explorer
}

//---------------------------------------------------------------------------
// Shows save as dialog.
// Proper flags are set for the FileInfo structure (Project).
void TMain::mnuSaveAsClick(TObject *Sender)
{
  //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;

  if(Active->Project.HasName) //if file has been named
    // default to current name
    SaveDialog->FileName = Active->Project.CurrentFile;

  if(SaveDialog->Execute())
  {
    if (FileExists(SaveDialog->FileName))
      if (Application->MessageBox("File exists! OK to overwrite?","Caution!",MB_YESNO) == IDNO)
        return;
    AnsiString ext = ExtractFileExt(SaveDialog->FileName);
    Active->Project.CurrentFile = SaveDialog->FileName;
    if(ext == ".X68") //make sure the file structure is set for a source file to allow assembly
    {
      Active->Project.IsSource = true;
      //Active->Project.SourceOpen = true;
    }
    else if(ext == "*.*") //setup the form for a list
    {
      Active->Project.IsSource = false;
      //Active->Project.SourceOpen = false;
    }
    Active->SourceText->Lines->SaveToFile(Active->Project.CurrentFile);
    SaveFont(Active);           // save font and tab info to file if source
    //Active->clearUndoRedo();

    //update modified StatusBar item
    Active->SourceText->Modified = false;
    Active->UpdateStatusBar();
    Active->Caption = ExtractFileName(Active->Project.CurrentFile);
    Active->Project.HasName = true;
    //Application->Title = Main->Caption + "-" + Active->Caption; //<---taskbar
  }
}

//---------------------------------------------------------------------------
//Saves file, if file has not been named yet then the SaveAs function is called
void TMain::mnuSaveClick(TObject *Sender)
{
  //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;
  if(Active->Project.HasName) //file has been named so save it
  {
    Active->SourceText->Lines->SaveToFile(Active->Project.CurrentFile);
    SaveFont(Active);
    // Active->clearUndoRedo();

    //update modified StatusBar item
    Active->SourceText->Modified = false;
    Active->UpdateStatusBar();
  }
  else  //file has not been previously saved so call the Save As dialog
  {
    mnuSaveAsClick(Sender);
  }
}

//---------------------------------------------------------------------------
// Add font and tab info to .X68 source file
void SaveFont(TTextStuff *active)
{
  fstream file;
  try {
    if (active->Project.IsSource) {
      AnsiString ext = UpperCase(ExtractFileExt(active->Project.CurrentFile));
      if (ext == ".X68") {              // if .X68 file
        file.open(active->Project.CurrentFile.c_str(), ios::app | ios::out);  //open source file for append
        file << "\n"
             << "*~Font name~" << active->SourceText->Font->Name.c_str() << "~\n"
             << "*~Font size~" << active->SourceText->Font->Size         << "~\n"
             << "*~Tab type~"  << active->Project.TabType                << "~\n"
             << "*~Tab size~"  << active->Project.TabSize                << "~\n";
        file.close();
      }
    }
  }
  catch( ... ) {
    MessageDlg("Error in SaveFont()",mtInformation, TMsgDlgButtons() << mbOK,0);
    return;
  }
}

//---------------------------------------------------------------------------
// Opens file in a new window.
// Proper FileInfo structure (Project) flags are set after the file is opened.
void TMain::OpenFile(AnsiString name)
{

  // check to see if file exists
  if (FileExists(name) == false) {      // if file does not exist
    TMsgDlgButtons temp_set;
    temp_set << mbOK;
    MessageDlg("File Access Error.  Please verify the file name and that you have the proper permissions to open the file.", mtError,temp_set,0);
    return;
  }

  TTextStuff *TextStuff;

  // check to see if file is already open
  for(int i = MDIChildCount-1; i >= 0; i--) {
    TextStuff = (TTextStuff*)MDIChildren[i];
    if(TextStuff->Project.CurrentFile == name) { // if file already open
      if (TextStuff->Project.Modified) {         // if it is modified
        TMsgDlgButtons temp_set;
        temp_set << mbYes << mbNo;
        AnsiString asBuffer = ExtractFileName(name) + " is already open. Do you want to discard changes and reopen?";
        int iMsg = MessageDlg(asBuffer, mtConfirmation, temp_set, 0);
        if(iMsg == mrNo) {  //do not load file
          TextStuff->BringToFront();
          return;
        }
      }
      // close current open file so it will be replaced
      TextStuff->Project.Modified = false;
      TextStuff->SourceText->Modified = false;
      TextStuff->Close();   // close current
    }
  }

  //create the window
  TextStuff = new TTextStuff(Application);
  TextStuff->LoadFile(name);
}

//--------------------------------------------------------------------------
// Open Click
void TMain::mnuOpenClick(TObject *Sender)
{
  OpenDialog->Title = "Open File";
  Main->SetFocus();
  if(OpenDialog->Execute()) {
    OpenFile(OpenDialog->FileName);
  }
}

//--------------------------------------------------------------------------
// handler for drag-n-drop from explorer
void TMain::WmDropFiles(TWMDropFiles& Message)
{
  AnsiString fileName;
  char buff[MAX_PATH];                  // filename buffer
  HDROP hDrop = (HDROP)Message.Drop;
  int numFiles = DragQueryFile(hDrop, -1, NULL, NULL);  // number of files dropped
  for (int i=0;i < numFiles;i++) {      // loop for all files dropped
    DragQueryFile(hDrop, i, buff, sizeof(buff));        // get name of file i
    fileName = buff;
    if (FileExists(fileName)) {
      OpenFile(fileName);               // open specified file
    }
  }
  DragFinish(hDrop);                    // free memory Windows allocated
}

//--------------------------------------------------------------------------
// Assembles active source file window. Makes a check to see if the file
// loaded is a source file before loading it into assembler.
void TMain::mnuDoAssemblerClick(TObject *Sender)
{
  AnsiString sourceFile, tempFile;

  //grab active child window
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;
  //if(Active->Project.IsSource) //only try to assemble a source file
  //{
    // if autosave and source has been modified
    if(Options->bSave && Active->SourceText->Modified)
    {
      Main->mnuSaveClick(Sender); //save source file
    }
    Active->Messages->Items->Clear();

    try //try to assemble the file
    {
      // set assembler option flags
      listFlag = Options->chkGenList->Checked;
      objFlag  = Options->chkGenSRec->Checked;
      CEXflag  = Options->chkConstantsEx->Checked;
      BITflag  = Options->chkBitfield->Checked;
      CREflag  = Options->chkCrossRef->Checked;
      MEXflag  = Options->chkMacEx->Checked;
      SEXflag  = Options->chkStrucEx->Checked;
      WARflag  = Options->chkShowWarnings->Checked;

      // use path of selected source file as temp working directory
      SetCurrentDir(ExtractFilePath(Active->Project.CurrentFile));
      sourceFile = ExtractFilePath(Active->Project.CurrentFile) + "EASy68Ks.tmp";
      tempFile = ExtractFilePath(Active->Project.CurrentFile) + "EASy68Km.tmp";
      Active->SourceText->Lines->SaveToFile(sourceFile);
      assembleFile(sourceFile.c_str(), tempFile.c_str(), Active->Project.CurrentFile);
      DeleteFile(sourceFile);              // delete temporary files
      DeleteFile(tempFile);
      AssemblerBox->ShowModal();
    }
    catch(...) //if there is an error then cancel assemble
    {
      TMsgDlgButtons temp_set;
      temp_set << mbOK;
      MessageDlg("File Access Error.  Please verify that you have write permission to the folder where the selected file is located.", mtError,temp_set,0);
    }
}

//---------------------------------------------------------------------------
// Create a new source file
void TMain::mnuNewClick(TObject *Sender)
{
  //create the source window
  TTextStuff *TextStuff;
  TextStuff = new TTextStuff(Application);

  TextStuff->NewSourceFile();
}
//---------------------------------------------------------------------------

void TMain::tbAssembleClick(TObject *Sender)
{
  mnuDoAssemblerClick(Sender);
}

//---------------------------------------------------------------------------
void TMain::mnuHelpClick(TObject *Sender)
{
  displayHelp("INTRO");
}

//---------------------------------------------------------------------------
void TMain::displayHelp(char* context)
{
  HWND H = ::GetDesktopWindow();  //this->Handle;  //::GetDesktopWindow();
  if (HHLibrary != 0)
    m_hWindow = __HtmlHelp(H, m_asHelpFile.c_str(), HH_HELP_CONTEXT, getHelpContext(context));
  else
    ShowMessage("HTML Help was not detected on this computer. The HTML help viewer may be downloaded from msdn.microsoft.com");

}

//---------------------------------------------------------------------------

void TMain::mnuFindClick(TObject *Sender)
{
  //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;

  //if text selected in the source window use it for find text
  if(Active->SourceText->SelText != "")        // if text selected
    findDialogFrm->findText->Text = Active->SourceText->SelText;
  findDialogFrm->Show();
}

//---------------------------------------------------------------------------
// Searches the active source window for the given text, displays message
// if it is not found.
void TMain::FindDialogFind(AnsiString findText, bool wholeWord, bool matchCase) {

  TMsgDlgButtons temp_set; //message dialog stuff
  temp_set << mbOK;

  TSearchTypes st;
  int FoundAt, StartPos, ToEnd; //tracks positions of text

  //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;

  //set appropriate search flags
  if (matchCase) //->Options.Contains(frMatchCase))
    st << stMatchCase;
  if (wholeWord) //Options.Contains(frWholeWord))
    st << stWholeWord;

  // begin the search after the current selection if there is one
  // otherwise, begin at the start of the text
  if (Active->SourceText->SelLength)
    StartPos = Active->SourceText->SelStart + Active->SourceText->SelLength;
  else
    StartPos = 0;

  // ToEnd is the length from StartPos
  // to the end of the text in the rich edit control
  ToEnd = Active->SourceText->Text.Length() - StartPos;

  FoundAt = Active->SourceText->FindText(findText,StartPos,ToEnd,st);

  if(FoundAt != -1)
  {
    Main->SetFocus(); //return focus
    Active->SourceText->SelStart = FoundAt;
    Active->SourceText->SelLength = findText.Length();
  }
  else
  {
    MessageDlg("End of document reached.", mtInformation, temp_set, 0);
    Active->SourceText->SelLength = 0;
  }
}

//---------------------------------------------------------------------------

void TMain::tbFindClick(TObject *Sender)
{
  mnuFindClick(Sender);
}

//---------------------------------------------------------------------------

void TMain::mnuFindAndReplace1Click(TObject *Sender)
{
  //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;
  replaceDialogFrm->findText->Text = Active->SourceText->SelText;
  replaceDialogFrm->replaceText->Text = Active->SourceText->SelText;
  replaceDialogFrm->Show();
}
//---------------------------------------------------------------------------

void TMain::ReplaceDialogReplace()
{
  int startSave, lengthSave;

   //grab active mdi child
  TTextStuff *Active = (TTextStuff*)this->ActiveMDIChild;

  if(Active->SourceText->SelLength == 0)
  {
    FindDialogFind(replaceDialogFrm->findText->Text,
                   replaceDialogFrm->wholeWordChk->Checked,
                   replaceDialogFrm->matchCaseChk->Checked);
  }

  do {
    if(Active->SourceText->SelLength != 0)
    {
      startSave = Active->SourceText->SelStart;
      lengthSave = max(1, replaceDialogFrm->replaceText->Text.Length());
      Active->SourceText->SelText = replaceDialogFrm->replaceText->Text;
      Active->SourceText->SelStart = startSave;
      Active->SourceText->SelLength = lengthSave;
      FindDialogFind(replaceDialogFrm->findText->Text,
                     replaceDialogFrm->wholeWordChk->Checked,
                     replaceDialogFrm->matchCaseChk->Checked);
    }
  } while ( replaceDialogFrm->replaceAll  &&
            Active->SourceText->SelLength != 0 );
}

//---------------------------------------------------------------------------

//search for text item specified in find dialog
void TMain::FindNext()
{
  FindDialogFind(findDialogFrm->findText->Text, findDialogFrm->wholeWordChk->Checked, findDialogFrm->matchCaseChk->Checked);
}

//---------------------------------------------------------------------------
void TMain::Edit1Click(TObject *Sender)
//need to prevent user from "find next" if no windows are open or no find
//text has been input yet
{
  if(Main->MDIChildCount == 0 || findDialogFrm->findText->Text == "")
  {
    mnuFindNext->Enabled = false;
  }
  else
  {
    mnuFindNext->Enabled = true;
  }
}
//---------------------------------------------------------------------------

void TMain::mnuFindNextClick(TObject *Sender)
{
  FindNext();
}
//---------------------------------------------------------------------------

// Intialize variables

void TMain::FormShow(TObject *Sender)
{
  AnsiString fileName;

  Options->LoadSettings();  //load editor settings from file

  if (ParamCount() > 0)         // if parameters are present
  {
    fileName = ParamStr(1);     // get file name

    if (FileExists(fileName)) {
      OpenFile(fileName);       // open specified file
    }
    else
      mnuNewClick(Sender);      // open new edit window
  }
   else
     mnuNewClick(Sender);        // open new edit window

  Main->Caption = TITLE;
  if (maximizedEdit) {
    TTextStuff *Active = (TTextStuff*)Main->ActiveMDIChild;
    Active->WindowState = wsMaximized;
  }

}
//---------------------------------------------------------------------------


void TMain::mnuAssemblerOptionsClick(TObject *Sender)
{
  Options->Show();
}
//---------------------------------------------------------------------------

void TMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  try{
    Options->SaveSettings();  //save editor settings to file

    if (HHLibrary != 0)
    {
      __HtmlHelp(0, NULL, HH_CLOSE_ALL, 0);
      Sleep(0);
      __HtmlHelp(NULL, NULL, HH_UNINITIALIZE, (DWORD)m_Cookie);
      ::FreeLibrary(HHLibrary);
      HHLibrary = 0;
    }
  }
  catch(...)
  {
    // Adobe reader can cause errors in help if it is not installed properly.
    // Just ignore any error and close.
    ShowMessage("Html Help may not have closed correctly");
  }
}
//---------------------------------------------------------------------------

void TMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == VK_F1)
     displayHelp("MAIN");
}
//---------------------------------------------------------------------------
// Paste the clipboard to the current child. Format the pasted text.

void TMain::EditPaste1Execute(TObject *Sender)
{
  if (Clipboard()->HasFormat(CF_TEXT) == false) // if clipboard empty
    return;

  TTextStuff *Active = (TTextStuff*)Main->ActiveMDIChild;

  if(Active->ActiveControl->Focused()) {
    int selStart = Active->SourceText->SelStart;

    // create a REPASTESPECIAL structure to use in the
    // EM_PASTESPECIAL message
    REPASTESPECIAL reps = { 0, 0 };

    // tell the Rich Edit control to insert unformatted text (CF_TEXT)
    ::SendMessage(Active->SourceText->Handle, EM_PASTESPECIAL, CF_TEXT, (LPARAM) &reps);

    int selLength = Active->SourceText->SelStart - selStart;
    Active->SourceText->SelStart = selStart;
    Active->SourceText->SelLength = selLength;

    ::UpdateWindow(Active->SourceText->Handle);   // force Richtext box to update

    Active->SetTabs();            // set tabs

    Active->SourceText->SelStart = selStart + selLength;
  } else if(findDialogFrm->findText->Focused()) { // if find dialog selected
    findDialogFrm->findText->Text = Clipboard()->AsText;
  } else if(replaceDialogFrm->findText->Focused()) {  // if replace findText selected
    replaceDialogFrm->findText->Text = Clipboard()->AsText;
  } else if(replaceDialogFrm->replaceText->Focused()) {  // if replace replaceText selected
    replaceDialogFrm->replaceText->Text = Clipboard()->AsText;
  }  
}
//---------------------------------------------------------------------------

void TMain::EditCommentAdd1Execute(TObject *Sender)
{
  TTextStuff *Active = (TTextStuff*)Main->ActiveMDIChild;
  Active->commentSelection();
}
//---------------------------------------------------------------------------

void TMain::EditUncomment1Execute(TObject *Sender)
{
  TTextStuff *Active = (TTextStuff*)Main->ActiveMDIChild;
  Active->unCommentSelection();
}
//---------------------------------------------------------------------------

void TMain::Reload1Click(TObject *Sender)
{
  TTextStuff *Active = (TTextStuff*)Main->ActiveMDIChild;
  Active->EditorReload1Click(Sender);
}
//---------------------------------------------------------------------------
