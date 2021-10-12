//---------------------------------------------------------------------------

#ifndef BREAKPOINTSuH
#define BREAKPOINTSuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBreaksFrm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *RegGroupBox;
        TStringGrid *RegStringGrid;
        TComboBox *RegSelectCombo;
        TComboBox *RegOperatorCombo;
        TMaskEdit *RegValueMaskEdit;
        TGroupBox *AddrGroupBox;
        TStringGrid *AddrStringGrid;
        TMaskEdit *AddrSelectMaskEdit;
        TMaskEdit *AddrValueMaskEdit;
        TComboBox *AddrOperatorCombo;
        TComboBox *AddrReadWriteCombo;
        TButton *RegSetButton;
        TButton *RegClearButton;
        TButton *RegClearAllButton;
        TButton *AddrSetButton;
        TButton *AddrClearButton;
        TButton *AddrClearAllButton;
        TGroupBox *ExprGroupBox;
        TStringGrid *ExprStringGrid;
        TComboBox *ExprEnabledCombo;
        TButton *ExprSetButton;
        TButton *ExprClearButton;
        TButton *ExprClearAllButton;
        TButton *ExprRegAppendButton;
        TButton *ExprAddrAppendButton;
        TMaskEdit *ExprRegMaskEdit;
        TMaskEdit *ExprAddrMaskEdit;
        TButton *ExprAndAppendButton;
        TButton *ExprOrAppendButton;
        TButton *ExprBackspaceButton;
        TEdit *ExprExprEdit;
        TMaskEdit *ExprCountMaskEdit;
        TComboBox *RegSizeCombo;
        TComboBox *AddrSizeCombo;
        TButton *ExprLParenAppendButton;
        TButton *ExprRParenAppendButton;
        TLabel *debugLabel1;
        TLabel *debugLabel2;
        TLabel *debugLabel3;
        TLabel *debugLabel4;
        TLabel *debugLabel5;
        TLabel *debugLabel6;
        TLabel *debugLabel7;
        void RegStringGridClick(TObject *Sender);
        void AddrStringGridClick(TObject *Sender);
        void ExprStringGridClick(TObject *Sender);
        void RegSetButtonClick(TObject *Sender);
        void AddrSetButtonClick(TObject *Sender);
        void ExprSetButtonClick(TObject *Sender);
        void ExprRegAppendButtonClick(TObject *Sender);
        void ExprAddrAppendButtonClick(TObject *Sender);
        void ExprAndAppendButtonClick(TObject *Sender);
        void ExprOrAppendButtonClick(TObject *Sender);
        void ExprBackspaceButtonClick(TObject *Sender);
        void RegClearButtonClick(TObject *Sender);
        void RegClearAllButtonClick(TObject *Sender);
        void AddrClearButtonClick(TObject *Sender);
        void AddrClearAllButtonClick(TObject *Sender);
        void RegValueKeyPress(TObject *Sender, char &Key);
        void AddrSelectKeyPress(TObject *Sender, char &Key);
        void AddrValueKeyPress(TObject *Sender, char &Key);
        void ExprCountKeyPress(TObject *Sender, char &Key);
        void ExprClearButtonClick(TObject *Sender);
        void ExprClearAllButtonClick(TObject *Sender);
        void RegStringGridDblClick(TObject *Sender);
        void AddrStringGridDblClick(TObject *Sender);
        void ExprStringGridDblClick(TObject *Sender);
        void RegColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void AddrColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void ExprColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void RegRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void RegTopLeftChanged(TObject *Sender);
        void AddrTopLeftChanged(TObject *Sender);
        void AddrRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void ExprRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
        void ExprTopLeftChanged(TObject *Sender);
        void ExprLParenAppendButtonClick(TObject *Sender);
        void ExprRParenAppendButtonClick(TObject *Sender);
        void FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        TBreaksFrm(TComponent* Owner);
        void BringToFront();
        int sbpoint(int loc);
        int cbpoint(int loc);
        void setRegButtons();
        void setAddrButtons();
        void setExprButtons();
        int precedence(int op_prec);
        void resetDebug();
};
//---------------------------------------------------------------------------
extern PACKAGE TBreaksFrm *BreaksFrm;
//---------------------------------------------------------------------------
#endif
