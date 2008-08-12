// shard_select_window.cpp : implementation file
//

#ifdef _WINDOWS

#include "stdafx.h"
#include "resource.h"
#include "shard_select_window.h"
#include "nel/misc/variable.h"
#include "nel/misc/path.h"
#include "../em_event_manager.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShardSelectWindow dialog


CShardSelectWindow::CShardSelectWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CShardSelectWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShardSelectWindow)
	ShardName = _T("");
	//}}AFX_DATA_INIT
}


void CShardSelectWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShardSelectWindow)
	DDX_Control(pDX, IDC_COMBO3, ShardNameCombo);
	DDX_CBString(pDX, IDC_COMBO3, ShardName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShardSelectWindow, CDialog)
	//{{AFX_MSG_MAP(CShardSelectWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShardSelectWindow message handlers

extern NLMISC::CVariable<std::string> Shard;

BOOL CShardSelectWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Build the list of shards that we're logged into

	NLMISC::CVectorSString shardNames;
	CEventManager::getInstance()->getShards(shardNames);
	uint32 shardIdx=0;
	for (uint32 i=0;i<shardNames.size();++i)
	{
		ShardNameCombo.InsertString (-1, shardNames[i].c_str());
		if (shardNames[i]==::Shard.get())
			shardIdx= i;
	}
	ShardNameCombo.SetCurSel (shardIdx);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#endif
