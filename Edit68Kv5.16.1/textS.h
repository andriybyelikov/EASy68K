//---------------------------------------------------------------------------

#ifndef textSH
#define textSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <StrUtils.hpp>
#include "RichEditPlus.h"
#include <stack>
#include <vector>
#include "asm.h"
#include "mainS.h"
#include "optionsS.h"
#include "editorOptions.h"
#include "findDialogS.h"

using namespace std;

//---------------------------------------------------------------------------

// Information that is saved for one change in the editor for undo/redo.
struct UndoRedo
{
  int   start;          // where the change occurred. (0-n)
  int   length;         // length of characters changed
  AnsiString str;       // the original text
};

enum tokenT {UNKNOWN, CODE, OPCODE_FOUND, COMMENT, ERROR_STYLE, STRUCTURE };

class TTextStuff : public TForm
{
__published:	// IDE-managed Components
        TRichEditPlus *SourceText;
          TTimer *HighlightTimer; // code highlighting thread
          TPopupMenu *PopupMenu1; // richtext right-click popup menu
            TMenuItem *Undo1;
            TMenuItem *Redo1;
            TMenuItem *N2;
            TMenuItem *Cut1;
            TMenuItem *Copy1;
            TMenuItem *Paste1;
            TMenuItem *SelectAll1;
            TMenuItem *N1;
            TMenuItem *CommentSelection1;
            TMenuItem *UncommentSelection1;
            TMenuItem *N3;
            TMenuItem *EditorReload1;
        TStatusBar *StatusBar;
      TSplitter *Splitter3; // probably splits (sourcetext+statusbar) from error messages
        TListView *Messages; // error messages list
          TPopupMenu *PopupMenu2; // right click error messages list with single menuitem to clear error messages
            TMenuItem *ClearErrorMessages1;

        
        
        
        
        

        void SourceTextKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void SourceTextKeyPress(TObject *Sender, char &Key);
        void SourceTextKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void FormClose(TObject *Sender, TCloseAction &Action);
        void ClearErrorMessages(TObject *Sender);
        void MessagesDblClick(TObject *Sender);
        void SourceTextMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void SourceTextMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void FormShow(TObject *Sender);
        void tbNewClick(TObject *Sender);
        void tbPrintClick(TObject *Sender);
        void FormCloseQuery(TObject *Sender, bool &CanClose);
        void EditorOptions1Click(TObject *Sender);
        void SourceTextSelectionChange(TObject *Sender);
        void EditorReload1Click(TObject *Sender);
        void SourceTextMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void SourceTextProtectChange(TObject *Sender,
          int StartPos, int EndPos, bool &AllowChange);
        void SourceTextChange(TObject *Sender);
        void FormActivate(TObject *Sender);
        void HighlightTimerTimer(TObject *Sender);
        void SourceTextVertScroll(TObject *Sender);
        void FormResize(TObject *Sender);

public:		// User declarations

        TPoint CurPos; //saves the cursor position
        FileInfo Project; //project info structure
        bool InsertMode;        // tracks text insert mode

void NewProject(AnsiString Type); //reset all controls to new project
void NewSourceFile();


        TTextStuff(TComponent* Owner);


        void ProfileStart(unsigned int n);
        void ProfileEnd(unsigned int n);
        void ProfileClear();



        void LoadFile(AnsiString name);
        
        void UpdateStatusBar();
        void SetTabsAll();   // sets tabs of all SourceText
        void SetTabs(); //sets tabs of selected text in SourceText
        int GetFirstPos(int line); //returns start of line in Char positions
        int GetLastPos(int line); //returns end of line in Char positions
        
        void insertInSelection(AnsiString istr);
        void deleteFromSelection(AnsiString dstr);
        void replaceTabs();
        void commentSelection();
        void unCommentSelection();
        void indentSelection();
        void outdentSelection();
        void colorHighlight(int startLine, int endLine);
        int  getVisibleLineCount();
        bool highlightLine(tokenT &tokenType);
        char* highlightOperand();
        void setFontStyle(FontStyle fs);



        // undo items
        // function prototypes
        void SaveUndo(UndoRedo item, bool notRedo);
        void SaveRedo(UndoRedo item);
        void clearRedo();
        void clearUndoRedo();
        void Undo();
        void Redo();
        void exec_undo(UndoRedo &item);
        // undo/redo stacks
        stack<UndoRedo,vector<UndoRedo> > undoS;
        stack<UndoRedo,vector<UndoRedo> > redoS;

};
//---------------------------------------------------------------------------
extern PACKAGE TTextStuff *TextStuff;
//---------------------------------------------------------------------------
#endif
