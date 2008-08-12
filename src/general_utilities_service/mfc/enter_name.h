#if !defined(AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_)
#define AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// enter_name.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CEnterName dialog

class CEnterName : public CDialog
{
// Construction
public:
	CEnterName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterName)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	Combo;
	CString	Text;
	CString	ComboValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterName)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTER_NAME_H__A736DB78_36B8_49D8_AAB9_FEF984F5E96B__INCLUDED_)
