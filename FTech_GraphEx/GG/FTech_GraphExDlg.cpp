
// FTech_GraphExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_GraphEx.h"
#include "FTech_GraphExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_GraphExDlg dialog




CFTech_GraphExDlg::CFTech_GraphExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_GraphExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTech_GraphExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SpGraphIndex, m_SpGraphIndex);
	DDX_Control(pDX, IDC_SpSizeGraph, m_SpGraphSize);
	DDX_Control(pDX, IDC_SpSizePoint, m_SpPointSize);
	DDX_Control(pDX, IDC_CS_GRAPH, m_wndGrp);
}

BEGIN_MESSAGE_MAP(CFTech_GraphExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_WM_DESTROY()
ON_NOTIFY(UDN_DELTAPOS, IDC_SpGraphIndex, &CFTech_GraphExDlg::OnDeltaposSpgraphindex)
ON_BN_CLICKED(IDC_ClrBtnRectBkg, &CFTech_GraphExDlg::OnBnClickedClrbtnrectbkg)
ON_BN_CLICKED(IDC_ClrBtnRectGraph, &CFTech_GraphExDlg::OnBnClickedClrbtnrectgraph)
ON_BN_CLICKED(IDC_ClrBtnGrid, &CFTech_GraphExDlg::OnBnClickedClrbtngrid)
ON_BN_CLICKED(IDC_ClrBtnGraph, &CFTech_GraphExDlg::OnBnClickedClrbtngraph)
ON_BN_CLICKED(IDC_ClrBtnPoint, &CFTech_GraphExDlg::OnBnClickedClrbtnpoint)
ON_NOTIFY(UDN_DELTAPOS, IDC_SpSizeGraph, &CFTech_GraphExDlg::OnDeltaposSpsizegraph)
ON_NOTIFY(UDN_DELTAPOS, IDC_SpSizePoint, &CFTech_GraphExDlg::OnDeltaposSpsizepoint)
ON_BN_CLICKED(IDC_BtnFontLabelAxisX, &CFTech_GraphExDlg::OnBnClickedBtnfontlabelaxisx)
ON_BN_CLICKED(IDC_BtnFontLabelAxisY, &CFTech_GraphExDlg::OnBnClickedBtnfontlabelaxisy)
ON_BN_CLICKED(IDC_BtnFontValueAxisX, &CFTech_GraphExDlg::OnBnClickedBtnfontvalueaxisx)
ON_BN_CLICKED(IDC_BtnFontValueAxisY, &CFTech_GraphExDlg::OnBnClickedBtnfontvalueaxisy)
ON_BN_CLICKED(IDC_ChkDrawGrid, &CFTech_GraphExDlg::OnBnClickedChkdrawgrid)
ON_BN_CLICKED(IDC_ChkDrawTextValue, &CFTech_GraphExDlg::OnBnClickedChkdrawtextvalue)
ON_BN_CLICKED(IDC_ChkDrawTextLabel, &CFTech_GraphExDlg::OnBnClickedChkdrawtextlabel)
ON_BN_CLICKED(IDC_ChkValueInteger, &CFTech_GraphExDlg::OnBnClickedChkvalueinteger)
ON_BN_CLICKED(IDC_ChkDrawGraph, &CFTech_GraphExDlg::OnBnClickedChkdrawgraph)
ON_BN_CLICKED(IDC_ChkDrawPoint, &CFTech_GraphExDlg::OnBnClickedChkdrawpoint)
END_MESSAGE_MAP()


// CFTech_GraphExDlg message handlers

BOOL CFTech_GraphExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitControls();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFTech_GraphExDlg::InitControls()
{
	SetDlgItemText(IDC_EdMaxValueAxisX, L"10.0");
	SetDlgItemText(IDC_EdMaxValueAxisY, L"55.0");
	SetDlgItemInt(IDC_EdCountScaleAxisX, 10);
	SetDlgItemInt(IDC_EdCountScaleAxisY, 10);
	SetDlgItemText(IDC_EdLabelAxisX, L"Label X");
	SetDlgItemText(IDC_EdLabelAxisY, L"Label Y");

	SetDlgItemInt(IDC_EdCountGraph, 0);

	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnRectBkg);
	clrDlg->SetColor(m_wndGrp.GetColorFrmBkg());

	clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnRectGraph);
	clrDlg->SetColor(m_wndGrp.GetColorGrpBkg());

	clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnGrid);
	clrDlg->SetColor(m_wndGrp.GetColorGrid());

	GetDlgItem(IDC_EdGraphIndex)->EnableWindow(FALSE);
	GetDlgItem(IDC_SpGraphIndex)->EnableWindow(FALSE);
	GetDlgItem(IDC_ClrBtnGraph)->EnableWindow(FALSE);
	GetDlgItem(IDC_ClrBtnPoint)->EnableWindow(FALSE);
	GetDlgItem(IDC_EdSizeGraph)->EnableWindow(FALSE);
	GetDlgItem(IDC_SpSizeGraph)->EnableWindow(FALSE);
	GetDlgItem(IDC_EdSizePoint)->EnableWindow(FALSE);
	GetDlgItem(IDC_SpSizePoint)->EnableWindow(FALSE);
	GetDlgItem(IDC_ChkDrawGraph)->EnableWindow(FALSE);
	GetDlgItem(IDC_ChkDrawPoint)->EnableWindow(FALSE);

	CheckDlgButton(IDC_ChkDrawGrid,1);
	CheckDlgButton(IDC_ChkDrawTextValue,1);
	CheckDlgButton(IDC_ChkDrawTextLabel,1);

	SetDlgItemText(IDC_EdGraphIndex,L"");
	SetDlgItemText(IDC_EdSizeGraph,L"");
	SetDlgItemText(IDC_EdSizePoint,L"");
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_GraphExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_GraphExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CFTech_GraphExDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN :
			if (pMsg->hwnd == GetDlgItem(IDC_EdMaxValueAxisX)->m_hWnd)
			{
				int value = GetDlgItemInt(IDC_EdMaxValueAxisX);
				m_wndGrp.SetMaxValueAxisX(value);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdMaxValueAxisY)->m_hWnd)
			{
				int value = GetDlgItemInt(IDC_EdMaxValueAxisY);
				m_wndGrp.SetMaxValueAxisY(value);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdCountScaleAxisX)->m_hWnd)
			{
				int value = GetDlgItemInt(IDC_EdCountScaleAxisX);
				m_wndGrp.SetCountScaleAxisX(value);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdCountScaleAxisY)->m_hWnd)
			{
				int value = GetDlgItemInt(IDC_EdCountScaleAxisY);
				m_wndGrp.SetCountScaleAxisY(value);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdLabelAxisX)->m_hWnd)
			{
				CString text;
				GetDlgItemText(IDC_EdLabelAxisX,text);
				m_wndGrp.SetTextLabelAxisX(text);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdLabelAxisY)->m_hWnd)
			{
				CString text;
				GetDlgItemText(IDC_EdLabelAxisY,text);
				m_wndGrp.SetTextLabelAxisY(text);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_EdCountGraph)->m_hWnd)
			{
				int value = GetDlgItemInt(IDC_EdCountGraph);
				if (value > 0)
				{
					m_wndGrp.SetCountGraph(value);
					CreatearrGraphData(value);

					m_SpGraphIndex.SetRange(0,value-1);
					UDACCEL accels[] = {{0,1}};
					m_SpGraphIndex.SetAccel(1,accels);

					SetDlgItemInt(IDC_EdGraphIndex,0);

					GetDlgItem(IDC_EdGraphIndex)->EnableWindow(TRUE);
					GetDlgItem(IDC_SpGraphIndex)->EnableWindow(TRUE);
					GetDlgItem(IDC_ClrBtnGraph)->EnableWindow(TRUE);
					GetDlgItem(IDC_ClrBtnPoint)->EnableWindow(TRUE);
					GetDlgItem(IDC_EdSizeGraph)->EnableWindow(TRUE);
					GetDlgItem(IDC_SpSizeGraph)->EnableWindow(TRUE);
					GetDlgItem(IDC_EdSizePoint)->EnableWindow(TRUE);
					GetDlgItem(IDC_SpSizePoint)->EnableWindow(TRUE);
					GetDlgItem(IDC_ChkDrawGraph)->EnableWindow(TRUE);
					GetDlgItem(IDC_ChkDrawPoint)->EnableWindow(TRUE);

					CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawGraph);
					pBtn->SetCheck(1);
					pBtn = (CButton*)GetDlgItem(IDC_ChkDrawPoint);
					pBtn->SetCheck(1);

					CMFCColorButton* clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnGraph);
					COLORREF clr = m_wndGrp.GetColorGraphData(value);
					clrDlg->SetColor(clr);

					clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnPoint);
					clr = m_wndGrp.GetColorGraphPoint(value);
					clrDlg->SetColor(clr);

					int size = m_wndGrp.GetSizeGraphData(value);
					SetDlgItemInt(IDC_EdSizeGraph, size);

					size = m_wndGrp.GetSizeGraphPoint(value);
					SetDlgItemInt(IDC_EdSizePoint, size);
				}
				else
				{
					GetDlgItem(IDC_EdGraphIndex)->EnableWindow(FALSE);
					GetDlgItem(IDC_SpGraphIndex)->EnableWindow(FALSE);
					GetDlgItem(IDC_ClrBtnGraph)->EnableWindow(FALSE);
					GetDlgItem(IDC_ClrBtnPoint)->EnableWindow(FALSE);
					GetDlgItem(IDC_EdSizeGraph)->EnableWindow(FALSE);
					GetDlgItem(IDC_SpSizeGraph)->EnableWindow(FALSE);
					GetDlgItem(IDC_EdSizePoint)->EnableWindow(FALSE);
					GetDlgItem(IDC_SpSizePoint)->EnableWindow(FALSE);
					GetDlgItem(IDC_ChkDrawGraph)->EnableWindow(FALSE);
					GetDlgItem(IDC_ChkDrawPoint)->EnableWindow(FALSE);
				}
			}
			
			return TRUE;
		case VK_ESCAPE :
			return TRUE;
			
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFTech_GraphExDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_wndGrp.DestroyWindow();
}


void CFTech_GraphExDlg::OnDeltaposSpgraphindex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	

	UpdateData();

	int max   = GetDlgItemInt(IDC_EdCountGraph);
	int index = GetDlgItemInt(IDC_EdGraphIndex);
	CString temp;
	
	// Up button
	if (pNMUpDown->iDelta >0)
	{
		index ++;
		if (index == max)
			index --;
	}
	// Down button
	else
	{
		index--;
		if (index<0)
			index=0;
	}

	CMFCColorButton* clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnGraph);
	COLORREF clr = m_wndGrp.GetColorGraphData(index);
	clrDlg->SetColor(clr);

	clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnPoint);
	clr = m_wndGrp.GetColorGraphPoint(index);
	clrDlg->SetColor(clr);

	bool enable = m_wndGrp.GetEnableDrawGraph(index);
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawGraph);
	pBtn->SetCheck(enable);

	enable = m_wndGrp.GetEnableDrawGraphPoint(index);
	pBtn = (CButton*)GetDlgItem(IDC_ChkDrawPoint);
	pBtn->SetCheck(enable);

	int size = m_wndGrp.GetSizeGraphData(index);
	SetDlgItemInt(IDC_EdSizeGraph, size);

	size = m_wndGrp.GetSizeGraphPoint(index);
	SetDlgItemInt(IDC_EdSizePoint, size);

	temp.Format(L"%d",index);
	SetDlgItemText(IDC_EdGraphIndex,temp);

	UpdateData(false);

	*pResult = 0;
}


void CFTech_GraphExDlg::OnBnClickedClrbtnrectbkg()
{
	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnRectBkg);
	m_wndGrp.SetColorFrmBkg(clrDlg->GetColor());
}


void CFTech_GraphExDlg::OnBnClickedClrbtnrectgraph()
{
	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnRectGraph);
	m_wndGrp.SetColorGrpBkg(clrDlg->GetColor());
}


void CFTech_GraphExDlg::OnBnClickedClrbtngrid()
{
	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnGrid);
	m_wndGrp.SetColorGrid(clrDlg->GetColor());
}

void CFTech_GraphExDlg::OnBnClickedClrbtngraph()
{
	int value = GetDlgItemInt(IDC_EdGraphIndex);
	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnGraph);
	m_wndGrp.SetColorGraphData(value, clrDlg->GetColor());
}

void CFTech_GraphExDlg::OnBnClickedClrbtnpoint()
{
	int value = GetDlgItemInt(IDC_EdGraphIndex);
	CMFCColorButton *clrDlg = (CMFCColorButton*)GetDlgItem(IDC_ClrBtnPoint);
	m_wndGrp.SetColorGraphPoint(value, clrDlg->GetColor());
}

void CFTech_GraphExDlg::OnDeltaposSpsizegraph(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData();

	int max   = GetDlgItemInt(IDC_EdCountGraph);
	int index = GetDlgItemInt(IDC_EdGraphIndex);
	int Width  = GetDlgItemInt(IDC_EdSizeGraph);
	CString temp;

	// Up button
	if (pNMUpDown->iDelta <0)
	{
		Width ++;
		
	}
	// Down button
	else
	{
		Width--;
		if (Width < 0)
			Width = 0;
	}

	m_wndGrp.SetSizeGraphData(index,Width);

	temp.Format(L"%d",Width);
	SetDlgItemText(IDC_EdSizeGraph,temp);

	UpdateData(false);

	*pResult = 0;
}

void CFTech_GraphExDlg::OnDeltaposSpsizepoint(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData();

	int max   = GetDlgItemInt(IDC_EdCountGraph);
	int index = GetDlgItemInt(IDC_EdGraphIndex);
	int size  = GetDlgItemInt(IDC_EdSizePoint);
	CString temp;

	// Up button
	if (pNMUpDown->iDelta <0)
	{
		size ++;

	}
	// Down button
	else
	{
		size--;
		if (size < 0)
			size = 0;
	}

	m_wndGrp.SetSizeGraphPoint(index,size);

	temp.Format(L"%d",size);
	SetDlgItemText(IDC_EdSizePoint,temp);

	UpdateData(false);

	*pResult = 0;
}

void CFTech_GraphExDlg::OnBnClickedBtnfontlabelaxisx()
{
	LOGFONT font = m_wndGrp.GetFontLabelAxisX();
	COLORREF clr = m_wndGrp.GetColorTextLabel();
	
	CFontDialog ftDlg(&font);
	if (ftDlg.DoModal() == IDOK)
	{
		int size = ftDlg.GetSize();
		ftDlg.GetCurrentFont(&font);
		clr = ftDlg.GetColor();
		
		font.lfHeight = size;
		m_wndGrp.SetFontLabelAxisX(font);
		m_wndGrp.SetFontLabelAxisY(font);
		m_wndGrp.SetColorTextLabel(clr);
	}
}

void CFTech_GraphExDlg::OnBnClickedBtnfontlabelaxisy()
{
	LOGFONT font = m_wndGrp.GetFontOrigin();
	COLORREF clr = m_wndGrp.GetColorTextOrigin();

	CFontDialog ftDlg(&font);
	if (ftDlg.DoModal() == IDOK)
	{
		int size = ftDlg.GetSize();
		ftDlg.GetCurrentFont(&font);
		clr = ftDlg.GetColor();

		font.lfHeight = size;
		m_wndGrp.SetFontOrigin(font);
		m_wndGrp.SetColorTextOrigin(clr);
	}
}

void CFTech_GraphExDlg::OnBnClickedBtnfontvalueaxisx()
{
	LOGFONT font = m_wndGrp.GetFontValueAxisX();
	COLORREF clr = m_wndGrp.GetColorTextValue();

	CFontDialog ftDlg(&font);
	if (ftDlg.DoModal() == IDOK)
	{
		int size = ftDlg.GetSize();
		ftDlg.GetCurrentFont(&font);
		clr = ftDlg.GetColor();

		font.lfHeight = size;
		m_wndGrp.SetFontValueAxisX(font);
		m_wndGrp.SetFontValueAxisY(font);
		m_wndGrp.SetColorTextValue(clr);
	}
}

void CFTech_GraphExDlg::OnBnClickedBtnfontvalueaxisy()
{
	LOGFONT font = m_wndGrp.GetFontInfo();
	COLORREF clr = m_wndGrp.GetColorTextInfo();

	CFontDialog ftDlg(&font);
	if (ftDlg.DoModal() == IDOK)
	{
		int size = ftDlg.GetSize();
		ftDlg.GetCurrentFont(&font);
		clr = ftDlg.GetColor();

		font.lfHeight = size;
		m_wndGrp.SetFontInfo(font);
		m_wndGrp.SetColorTextInfo(clr);
	}
}


void CFTech_GraphExDlg::OnBnClickedChkdrawgrid()
{
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawGrid);
	int status = pBtn->GetCheck();
	m_wndGrp.SetEnableDrawGrid(status);
}


void CFTech_GraphExDlg::OnBnClickedChkdrawtextvalue()
{
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawTextValue);
	int status = pBtn->GetCheck();
	m_wndGrp.SetEnableShowValue(status,status);
}


void CFTech_GraphExDlg::OnBnClickedChkdrawtextlabel()
{
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawTextLabel);
	int status = pBtn->GetCheck();
	m_wndGrp.SetEnableShowLabel(status);
}


void CFTech_GraphExDlg::OnBnClickedChkvalueinteger()
{
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkValueInteger);
	int status = pBtn->GetCheck();
	m_wndGrp.SetEnableValueInteger(status);
}

// 데이터 입력 부분 수정 안 함.
void CFTech_GraphExDlg::CreatearrGraphData(int nCount)
{
	CString tmp;
	GetDlgItemText(IDC_EdMaxValueAxisX,tmp);
	double maxX = _ttof(tmp);

	GetDlgItemText(IDC_EdMaxValueAxisY,tmp);
	double maxY = _ttof(tmp);

	int countX = GetDlgItemInt(IDC_EdCountScaleAxisX);

	srand( (unsigned)time( NULL ) ); 
	int scale = GetDlgItemInt(IDC_EdCountScaleAxisX);
	for (int i=0; i<nCount; i++)
	{
		for (int j=0; j<countX; j++)
		{
			double randomY = rand()%(int)maxY;

			//m_wndGrp.SetGraphData(i,maxX/scale + maxX/scale*j,randomY);
			//m_wndGrp.SetGraphData(0,pData,10)
		}
	}
}

void CFTech_GraphExDlg::OnBnClickedChkdrawgraph()
{
	int index = GetDlgItemInt(IDC_EdGraphIndex);
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawGraph);
	int status = pBtn->GetCheck();

	m_wndGrp.SetEnableDrawGraph(index,status);
}


void CFTech_GraphExDlg::OnBnClickedChkdrawpoint()
{
	int index = GetDlgItemInt(IDC_EdGraphIndex);
	CButton *pBtn = (CButton*)GetDlgItem(IDC_ChkDrawPoint);
	int status = pBtn->GetCheck();

	m_wndGrp.SetEnableDrawGraphPoint(index,status);
}
