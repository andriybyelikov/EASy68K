//---------------------------------------------------------------------------

#ifndef Memory1H
#define Memory1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMemoryFrm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TPanel *Panel2;
        TLabel *Label2;
        TCSpinButton *RowSpin;
        TCSpinButton *PageSpin;
        TLabel *Label3;
        TTimer *prompt;
        TButton *Copy;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TButton *Fill;
        TLabel *Label8;
        TCheckBox *LiveCheckBox;
        TSaveDialog *SaveDialog;
        TPanel *Panel3;
        TLabel *Label18;
        TMaskEdit *Address1;
        TLabel *Label24;
        TPanel *FromPanel;
        TLabel *Label15;
        TMaskEdit *From;
        TLabel *Label9;
        TPanel *Panel4;
        TLabel *Label16;
        TMaskEdit *To;
        TMaskEdit *Bytes;
        TLabel *Label10;
        TLabel *Label11;
        TSpeedButton *Save;
        void FormCreate(TObject *Sender);
        void FormPaint(TObject *Sender);
        void FormResize(TObject *Sender);
        void RowSpinUpClick(TObject *Sender);
        void RowSpinDownClick(TObject *Sender);
        void PageSpinUpClick(TObject *Sender);
        void PageSpinDownClick(TObject *Sender);
        void FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void Address1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void promptTimer(TObject *Sender);
        void FormKeyPress(TObject *Sender, char &Key);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void CopyClick(TObject *Sender);
        void AddrKeyPress(TObject *Sender, char &Key);
        void FillClick(TObject *Sender);
        void Address1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void Address1Change(TObject *Sender);
        void SaveClick(TObject *Sender);
private:	// User declarations
        int row, col, rowHeight, colWidth;
        int textX, textY, nRows;
        bool promptVisible;
public:		// User declarations
        TMemoryFrm(TComponent* Owner);
        void BringToFront();
        void erasePrompt();
        void gotoRC(TObject *Sender, int r, int c);
        void drawPrompt();
        void LivePaint(unsigned int);

};

//---------------------------------------------------------------------------
extern PACKAGE TMemoryFrm *MemoryFrm;
//---------------------------------------------------------------------------
#endif
