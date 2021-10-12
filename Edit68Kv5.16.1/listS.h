//---------------------------------------------------------------------------

#ifndef listSH
#define listSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TListFile : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *List;
        TSplitter *Splitter1;
        void FormClose(TObject *Sender, TCloseAction &Action);
        void ListKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void ListKeyPress(TObject *Sender, char &Key);
        void ListKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void ListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void ListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        TListFile(TComponent* Owner);
        TPoint CurPos;
};
//---------------------------------------------------------------------------
extern PACKAGE TListFile *ListFile;
//---------------------------------------------------------------------------
#endif
