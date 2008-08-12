// select_event_window.cpp : implementation file
//

#ifdef _WINDOWS

#include "stdafx.h"
#include "resource.h"
#include "select_event_window.h"
#include "nel/misc/variable.h"
#include "game_share/file_description_container.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectEventWindow dialog


CSelectEventWindow::CSelectEventWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectEventWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectEventWindow)
	Name = _T("");
	//}}AFX_DATA_INIT
}


void CSelectEventWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectEventWindow)
	DDX_Control(pDX, IDC_COMBO1, NameCombo);
	DDX_CBString(pDX, IDC_COMBO1, Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectEventWindow, CDialog)
	//{{AFX_MSG_MAP(CSelectEventWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectEventWindow message handlers

extern NLMISC::CVariable<std::string>	EventName;
extern NLMISC::CVariable<std::string>	EventDirectory;

BOOL CSelectEventWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CFileDescriptionContainer fdc;
	fdc.addFileSpec(EventDirectory.get()+"/*.worldedit");

	uint32 idx=0;
	for (uint32 i=0;i<fdc.size();++i)
	{
		NLMISC::CSString eventName= NLMISC::CFile::getFilenameWithoutExtension(fdc[i].FileName);
		NameCombo.InsertString (-1, eventName.c_str());
		if (eventName==EventName.get())
			idx= i;
	}
	NameCombo.SetCurSel (idx);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#endif
