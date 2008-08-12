#if !defined(AFX_SHARD_SELECT_WINDOW_H__C3A4EE4F_3A1C_4894_8078_810C8468B0A3__INCLUDED_)
#define AFX_SHARD_SELECT_WINDOW_H__C3A4EE4F_3A1C_4894_8078_810C8468B0A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// shard_select_window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShardSelectWindow dialog

class CShardSelectWindow : public CDialog
{
// Construction
public:
	CShardSelectWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShardSelectWindow)
	enum { IDD = IDD_DIALOG5 };
	CComboBox	ShardNameCombo;
	CString	ShardName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShardSelectWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShardSelectWindow)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARD_SELECT_WINDOW_H__C3A4EE4F_3A1C_4894_8078_810C8468B0A3__INCLUDED_)
