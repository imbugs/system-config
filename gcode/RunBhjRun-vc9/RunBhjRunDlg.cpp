// RunBhjRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RunBhjRun.h"
#include "EkbEdit.h"
#include "RunBhjRunDlg.h"
#define ENABLE_BHJDEBUG
#include "bhjdebug.h" 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRunBhjRunDlg dialog

CRunBhjRunDlg::CRunBhjRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunBhjRunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRunBhjRunDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRunBhjRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRunBhjRunDlg)
	DDX_Control(pDX, IDC_CmdEdit, m_CmdEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRunBhjRunDlg, CDialog)
	//{{AFX_MSG_MAP(CRunBhjRunDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSE, CRunBhjRunDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDOK, &CRunBhjRunDlg::OnBnClickedOk)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunBhjRunDlg message handlers

BOOL CRunBhjRunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_CmdEdit.SetEventMask(ENM_CHANGE|m_CmdEdit.GetEventMask());

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_CmdEdit.createListBox();
	m_CmdEdit.setHistFile("RunBhjRun.txt");

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRunBhjRunDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRunBhjRunDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRunBhjRunDlg::OnBnClickedBrowse()
{
 
}

void CRunBhjRunDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	m_CmdEdit.weVeMoved();
	
}

void CRunBhjRunDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CDialog::OnWindowPosChanged(lpwndpos);
	BHJDEBUG(" OnWindowPosChanged");
	
	
	
}

static const char *
startError (int err)
{
  switch (err)
    {
    case 0:
      return "The operating system is out of memory or resources.";
    case ERROR_FILE_NOT_FOUND:
      return "The specified file was not found.";
    case ERROR_PATH_NOT_FOUND:
      return "The specified path was not found.";
    case ERROR_BAD_FORMAT:
      return "The .exe file is invalid (non-Win32 .exe or error in "
        ".exe image).";
    case SE_ERR_ACCESSDENIED:
      return "The operating system denied access to the specified file.";
    case SE_ERR_ASSOCINCOMPLETE:
      return "The file name association is incomplete or invalid.";
    case SE_ERR_DDEBUSY:
      return "The DDE transaction could not be completed because "
        "other DDE transactions were being processed.";
    case SE_ERR_DDEFAIL:
      return "The DDE transaction failed.";
    case SE_ERR_DDETIMEOUT:
      return "The DDE transaction could not be completed because the "
        "request timed out.";
    case SE_ERR_DLLNOTFOUND:
      return "The specified dynamic-link library was not found.";
    case SE_ERR_NOASSOC:
      return "There is no application associated with the given file "
        "name extension.";
    case SE_ERR_OOM:
      return "There was not enough memory to complete the operation.";
    case SE_ERR_SHARE:
      return "A sharing violation occurred.";
    default:
      return "An unknown error occurred.";
    }
}

void CRunBhjRunDlg::OnBnClickedOk()
{
	CString text;
	m_CmdEdit.GetWindowText(text);

	cstring file;
	cstring args;
	cmdline_to_file_and_args(text, file, args);

	ShowWindow(SW_HIDE);
	int ret = (int) ShellExecute(NULL, NULL, file.c_str(), args.c_str(), NULL, SW_SHOWNORMAL);
	if (ret <= 32) {
		fmt_messagebox("Error: can't start %s: %s", file.c_str(), startError(ret));
		OnOK();
		return;
	} else {
		m_CmdEdit.saveHist();
	}
	Sleep(1000);
	OnOK();
}

void CRunBhjRunDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	lpwndpos->x=0;
	lpwndpos->y=0;
	CDialog::OnWindowPosChanging(lpwndpos);

	// TODO: Add your message handler code here
}
