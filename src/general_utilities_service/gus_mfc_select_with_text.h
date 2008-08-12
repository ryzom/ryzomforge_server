#if !defined(AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_)
#define AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gus_mfc_select_with_text.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGusMfcSelectWithText dialog

class CGusMfcSelectWithText : public CDialog
{
// Construction
public:
	CGusMfcSelectWithText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGusMfcSelectWithText)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	Combo;
	CString	Text;
	CString	ComboValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGusMfcSelectWithText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGusMfcSelectWithText)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_)
