#if !defined(AFX_LOGIN_WINDOW_H__90C99A3B_72C0_4A0E_A681_825B9D77F9BB__INCLUDED_)
#define AFX_LOGIN_WINDOW_H__90C99A3B_72C0_4A0E_A681_825B9D77F9BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// login_window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginWindow dialog

class CLoginWindow : public CDialog
{
// Construction
public:
	CLoginWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginWindow)
	enum { IDD = IDD_DIALOG2 };
	CString	Shard;
	CString	Login;
	CString	Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginWindow)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_WINDOW_H__90C99A3B_72C0_4A0E_A681_825B9D77F9BB__INCLUDED_)
