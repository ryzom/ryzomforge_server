#if !defined(AFX_UPLOAD_WINDOW_H__B7E0FE64_6036_4E15_A4C8_4C20DBB45C0C__INCLUDED_)
#define AFX_UPLOAD_WINDOW_H__B7E0FE64_6036_4E15_A4C8_4C20DBB45C0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// upload_window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUploadWindow dialog

class CUploadWindow : public CDialog
{
// Construction
public:
	CUploadWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUploadWindow)
	enum { IDD = IDD_DIALOG4 };
	CComboBox	EventCombo;
	CComboBox	ShardCombo;
	CString	Shard;
	CString	Event;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUploadWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUploadWindow)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPLOAD_WINDOW_H__B7E0FE64_6036_4E15_A4C8_4C20DBB45C0C__INCLUDED_)
