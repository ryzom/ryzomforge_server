// login_window.cpp : implementation file
//

#ifdef _WINDOWS

#include "stdafx.h"
#include "resource.h"
#include "login_window.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginWindow dialog


CLoginWindow::CLoginWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginWindow)
	Shard = _T("");
	Login = _T("");
	Password = _T("");
	//}}AFX_DATA_INIT
}


void CLoginWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginWindow)
	DDX_Text(pDX, IDC_EDIT1, Shard);
	DDX_Text(pDX, IDC_EDIT2, Login);
	DDX_Text(pDX, IDC_EDIT3, Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginWindow, CDialog)
	//{{AFX_MSG_MAP(CLoginWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginWindow message handlers

BOOL CLoginWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#endif
