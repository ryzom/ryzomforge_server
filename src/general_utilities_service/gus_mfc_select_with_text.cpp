// gus_mfc_select_with_text.cpp : implementation file
//

#include "stdafx.h"
#include "gus_mfc_select_with_text.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGusMfcSelectWithText dialog


CGusMfcSelectWithText::CGusMfcSelectWithText(CWnd* pParent /*=NULL*/)
	: CDialog(CGusMfcSelectWithText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGusMfcSelectWithText)
	Text = _T("");
	ComboValue = _T("");
	//}}AFX_DATA_INIT
}


void CGusMfcSelectWithText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGusMfcSelectWithText)
	DDX_Control(pDX, IDC_COMBO1, Combo);
	DDX_Text(pDX, IDC_EDIT1, Text);
	DDX_CBString(pDX, IDC_COMBO1, ComboValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGusMfcSelectWithText, CDialog)
	//{{AFX_MSG_MAP(CGusMfcSelectWithText)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGusMfcSelectWithText message handlers

void CGusMfcSelectWithText::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

BOOL CGusMfcSelectWithText::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Combo.InsertString (-1, "aa");
	Combo.InsertString (-1, "bb");
	Combo.InsertString (-1, "cc");
	Combo.InsertString (-1, "dd");
	Combo.SetCurSel (1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
