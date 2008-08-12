#if !defined(AFX_SELECT_EVENT_WINDOW_H__180943CF_A130_4CA6_831C_1E9DF35AF2F3__INCLUDED_)
#define AFX_SELECT_EVENT_WINDOW_H__180943CF_A130_4CA6_831C_1E9DF35AF2F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// select_event_window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectEventWindow dialog

class CSelectEventWindow : public CDialog
{
// Construction
public:
	CSelectEventWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectEventWindow)
	enum { IDD = IDD_DIALOG3 };
	CComboBox	NameCombo;
	CString	Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectEventWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectEventWindow)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECT_EVENT_WINDOW_H__180943CF_A130_4CA6_831C_1E9DF35AF2F3__INCLUDED_)
