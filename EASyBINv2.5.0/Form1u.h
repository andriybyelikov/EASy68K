//---------------------------------------------------------------------------

#ifndef Form1uH
#define Form1uH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <SHELLAPI.H>           // required for drag-n-drop from explorer
#include <Mask.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
#include "def.h"
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TActionList *ActionList1;
        TMainMenu *MainMenu1;
        TAction *Open;
        TMenuItem *File1;
        TImageList *ImageList1;
        TMenuItem *Open1;
        TMenuItem *Exit1;
        TMenuItem *Close1;
        TMenuItem *Help1;
        TMenuItem *About1;
        TAction *New;
        TAction *Exit;
        TAction *About;
        TAction *Help;
        TMenuItem *Help2;
        TMenuItem *N7;
        TMenuItem *N8;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label12;
        TGroupBox *S68File;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *S68endAddress;
        TLabel *Label4;
        TLabel *S68length;
        TRadioGroup *OutputSplit;
        TGroupBox *OutputData;
        TLabel *Label6;
        TLabel *Label7;
        TMaskEdit *OutputLength;
        TPanel *Panel2;
        TLabel *Label13;
        TLabel *Label14;
        TCSpinButton *RowSpin;
        TCSpinButton *PageSpin;
        TTimer *prompt;
        TPanel *Panel3;
        TLabel *Label18;
        TMaskEdit *Address1;
        TPanel *Panel5;
        TLabel *Label17;
        TMaskEdit *OutputFirstAddress;
        TLabel *Label5;
        TLabel *Label8;
        TLabel *Label19;
        TAction *OpenBin;
        TAction *SaveBin;
        TMenuItem *Save1;
        TMenuItem *N1;
        TMenuItem *OpenB;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label26;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *split0Lbl;
        TLabel *split1Lbl;
        TLabel *split2Lbl;
        TLabel *split3Lbl;
        TMenuItem *SaveSRecord1;
        TAction *SaveSRecord;
        TPanel *Panel6;
        TLabel *Label10;
        TLabel *Label22;
        TMaskEdit *Bytes;
        TButton *Copy;
        TPanel *Panel7;
        TLabel *Label9;
        TLabel *Label20;
        TPanel *FromPanel;
        TLabel *Label15;
        TMaskEdit *From;
        TLabel *Label11;
        TLabel *Label21;
        TPanel *Panel4;
        TLabel *Label16;
        TMaskEdit *To;
        TPanel *Panel8;
        TLabel *Label23;
        TMaskEdit *FillByte;
        TButton *Fill;
        TMaskEdit *startAddress;
        void NewExecute(TObject *Sender);
        void ExitExecute(TObject *Sender);
        void AboutExecute(TObject *Sender);
        void FormShow(TObject *Sender);
        void FormResize(TObject *Sender);
        void HelpExecute(TObject *Sender);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void OutputStartAddressKeyPress(TObject *Sender, char &Key);
        void Address1Change(TObject *Sender);
        void FormPaint(TObject *Sender);
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
        void CopyClick(TObject *Sender);
        void AddrKeyPress(TObject *Sender, char &Key);
        void FillClick(TObject *Sender);
        void Address1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void OpenBinFile(TObject *Sender);
        void SaveBinFile(TObject *Sender);
        void OutputSplitClick(TObject *Sender);
        void OpenExecute(TObject *Sender);
        void OutputFirstAddressChange(TObject *Sender);
        void OutputLengthChange(TObject *Sender);
        void SaveSRecFile(TObject *Sender);
        void startAddressEnter(TObject *Sender);
        void OutputFirstAddressEnter(TObject *Sender);
        void OutputLengthEnter(TObject *Sender);
        void FromEnter(TObject *Sender);
        void ToEnter(TObject *Sender);
        void BytesEnter(TObject *Sender);
        void FillByteEnter(TObject *Sender);
        void Address1Enter(TObject *Sender);
private:	// User declarations
        void WmDropFiles(TWMDropFiles& Message);     // handle drag-n-drop from explorer
        int row, col, rowHeight, colWidth;
        int textX, textY, nRows;
        bool promptVisible;
        int split;      // 0, 2, or 4 how binary output data is split

public:		// User declarations
        TForm1(TComponent* Owner);
        ~TForm1();
        void displayHelp(char * context);
        void OpenSRecordFile(AnsiString name);
        void erasePrompt();
        void drawPrompt();
        void gotoRC(TObject *Sender, int r, int c);



        // needed for HTML help
        HWND m_hWindow;
        AnsiString m_asHelpFile;
        DWORD m_Cookie;

        // message map for handling drag-n-drop from explorer
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WmDropFiles)
        END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

#endif
