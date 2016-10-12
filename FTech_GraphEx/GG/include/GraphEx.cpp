// CGraphEx.cpp : implementation file
//

#include "stdafx.h"
#include "GraphEx.h"

// CGraphEx
CGraphEx::CGraphEx()
{
	RegisterWindowClass();
	m_clrFrmBkg			= RGB(41,41,41);
	m_clrFrmBorder		= RGB(128,128,255);
	m_clrGrpBkg			= RGB(71,71,71);
	m_clrGrpBorder		= RGB(128,128,255);
	m_clrGrid			= RGB(128,128,128);
	m_clrScale			= RGB(255,255,255);
	m_clrTextValue		= RGB(255,255,255);
	m_clrTextLabel		= RGB(200,200,200);
	m_clrTextOrigin		= RGB(255,255,255);
	m_clrInfoBkg		= RGB(128,128,128);
	m_clrTextInfo		= RGB(255,255,255);
	m_nSizeFrmBorder	= 4;
	m_nSizeGrpBorder	= 1;
	m_nSizeInfo			= 12;
	m_nSizeValue		= 14;
	m_nSizeLabel		= 15;
	m_nSizeGrid			= 1;

	m_rcGrp = CRect(0,0,0,0);
	m_szInfo = CSize(80,60);
	
	m_dMaxAxisX		 = 10.0;
	m_dMaxAxisY		 = 55.0;
	m_nCntScaleAxisX = 10;
	m_nCntScaleAxisY = 10;
	m_nCntGraph		 = 0;

	m_pStGraphData  = NULL;

	m_bDrawGrid		= true;
	m_bDrawScaleX	= true;
	m_bDrawScaleY	= true;
	m_bShowLabel	= true;
	m_bShowValueX	= true;
	m_bShowValueY	= true;
	m_bShowOrigin	= true;
	m_bShowInteger	= false;

	m_strAxisX = L"Label X";
	m_strAxisY = L"Label Y";

	m_nCurrGrpPoint = 0;
	m_nCurrGrpData	= 0;
	m_bDrawInfo = false;
	m_pArrPosGrp = NULL;
	m_ptMouse = CPoint(0,0);
}

CGraphEx::~CGraphEx()
{
	m_ftLabelAxisX	.DeleteObject();
	m_ftLabelAxisY	.DeleteObject();
	m_ftValueAxisX	.DeleteObject();
	m_ftValueAxisY	.DeleteObject();
	m_ftInfo		.DeleteObject();
	m_ftOrigin		.DeleteObject();

	if (m_pStGraphData != NULL)
	{
		for (int i=0; i<m_nCntGraph; i++)
		{
			if (m_pStGraphData[i].arrGraphData.GetSize() != 0)
				m_pStGraphData[i].arrGraphData.RemoveAll();
		}

		delete []m_pStGraphData;
		m_pStGraphData = NULL;
	}

	if (m_pArrPosGrp != NULL)
	{
		int i=0;
		do{
			if (m_pArrPosGrp[i].GetSize() != 0)
				m_pArrPosGrp[i].RemoveAll();

			i++;
		}while(i<m_nCntGraph);

		delete []m_pArrPosGrp;
		m_pArrPosGrp = NULL;
	}
}

void CGraphEx::RegisterWindowClass(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc      = ::DefWindowProc;
	wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
	wndcls.hInstance        = hInst;
	wndcls.hIcon            = NULL;
	wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
	wndcls.lpszMenuName     = NULL;
	wndcls.lpszClassName    = WINCLASSNAME_GRAPHEX;

	AfxRegisterClass(&wndcls);

}
void CGraphEx::PreSubclassWindow()
{
	GetClientRect(m_rcFrm);	

	m_rcGrp.SetRect(m_rcFrm.left + 75, m_rcFrm.top + 10, m_rcFrm.right - 35, m_rcFrm.bottom - 30);

	m_ftLabelAxisX	.CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	m_ftLabelAxisY	.CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	m_ftValueAxisX	.CreateFont(10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	m_ftValueAxisY	.CreateFont(10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	m_ftInfo		.CreateFont(5, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	m_ftOrigin		.CreateFont(10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"System");
	CWnd::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CGraphEx, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGraphEx message handlers

void CGraphEx::OnPaint() 
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap *pOldBitmap, bitmap;

	memDC.CreateCompatibleDC(&dc);

	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), SRCCOPY);

	//----- 메모리상에 그리는 부분 -----//
	DrawFrameBkg(&memDC);
	DrawFrameBorder(&memDC);
	DrawGraphBkg(&memDC);
	DrawGraphBorder(&memDC);
	DrawScaleGridValue(&memDC);
	DrawGraphData(&memDC);
	DrawLabelText(&memDC);
	DrawGraphDataInfo(&memDC);
	//---------------------------------//

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

void CGraphEx::SetGraphData(int nIndex, stCoordinate* pData, int nArrSize)
{
	if (m_pStGraphData == NULL) return;
	ClearGraphData(nIndex);

	if (pData == NULL) return;
	if (nIndex < 0 || nIndex > m_nCntGraph-1) return;

	double dStepAxisX = (double) m_rcGrp.Width () / (m_nCntScaleAxisX+1); //0과 Max의 눈금 때문에 +1을 함.
	double dStepAxisY = (double) m_rcGrp.Height() / (m_nCntScaleAxisY+1); 
	double dValueAxisX= m_dMaxAxisX / m_nCntScaleAxisX;
	double dValueAxisY= m_dMaxAxisY / m_nCntScaleAxisY;
	double y_start = m_rcGrp.top + dStepAxisY;
	double y_end   = m_rcGrp.top + dStepAxisY*(m_nCntScaleAxisY+1);
	double x_start = m_rcGrp.left;
	double x_end   = m_rcGrp.left + dStepAxisX*(m_nCntScaleAxisX);
	double x_pos=0.0, y_pos=0.0;

	if (m_pArrPosGrp[nIndex].GetSize() != 0)
		m_pArrPosGrp[nIndex].RemoveAll();

	for (int i=0; i<nArrSize; i++)
	{
		stCoordinate coordinate;
		coordinate.x = pData[i].x;
		coordinate.y = pData[i].y;
		m_pStGraphData[nIndex].arrGraphData.Add(coordinate);

		y_pos = y_start + (y_end - y_start)*(m_dMaxAxisY - pData[i].y)/m_dMaxAxisY;
		x_pos = x_start + (x_end - x_start)*(pData[i].x)/m_dMaxAxisX;

		m_pArrPosGrp[nIndex].Add(CPoint((int)x_pos,(int)y_pos));
	}
}

void CGraphEx::SetGraphData(int nIndex, int* pXdata, int* pYdata, int nArrSize)
{
	if (m_pStGraphData == NULL) return;
	ClearGraphData(nIndex);

	if (pXdata == NULL) return;
	if (pYdata == NULL) return;
	if (nIndex < 0 || nIndex > m_nCntGraph-1) return;

	double dStepAxisX = (double) m_rcGrp.Width () / (m_nCntScaleAxisX+1); //0과 Max의 눈금 때문에 +1을 함.
	double dStepAxisY = (double) m_rcGrp.Height() / (m_nCntScaleAxisY+1); 
	double dValueAxisX= m_dMaxAxisX / m_nCntScaleAxisX;
	double dValueAxisY= m_dMaxAxisY / m_nCntScaleAxisY;
	double y_start = m_rcGrp.top + dStepAxisY;
	double y_end   = m_rcGrp.top + dStepAxisY*(m_nCntScaleAxisY+1);
	double x_start = m_rcGrp.left;
	double x_end   = m_rcGrp.left + dStepAxisX*(m_nCntScaleAxisX);
	double x_pos=0.0, y_pos=0.0;

	if (m_pArrPosGrp[nIndex].GetSize() != 0)
		m_pArrPosGrp[nIndex].RemoveAll();

	for (int i=0; i<nArrSize; i++)
	{
		stCoordinate coordinate;
		coordinate.x = pXdata[i];
		coordinate.y = pYdata[i];
		m_pStGraphData[nIndex].arrGraphData.Add(coordinate);

		y_pos = y_start + (y_end - y_start)*(m_dMaxAxisY - pYdata[i])/m_dMaxAxisY;
		x_pos = x_start + (x_end - x_start)*(pXdata[i])/m_dMaxAxisX;

		m_pArrPosGrp[nIndex].Add(CPoint((int)x_pos,(int)y_pos));
	}
}

void CGraphEx::ClearGraphData(int nIndex)
{
	if (m_pStGraphData == NULL) return;
	if (nIndex < 0) return;

	if (m_pStGraphData[nIndex].arrGraphData.GetSize() > 0)
		m_pStGraphData[nIndex].arrGraphData.RemoveAll();

	Invalidate(FALSE);
}

void CGraphEx::ClearAllGraphData()
{
	if (m_pStGraphData == NULL) return;

	for (int i=0; i<m_nCntGraph; i++)
	{
		if (m_pStGraphData[i].arrGraphData.GetSize() > 0)
			m_pStGraphData[i].arrGraphData.RemoveAll();
	}

	Invalidate(FALSE);
}

void CGraphEx::SetCountGraph(int nMax)
{
	if (nMax <0) return;

	if (m_pStGraphData != NULL)
	{
		int i=0;
		do{
			if (m_pStGraphData[i].arrGraphData.GetSize() != 0)
				m_pStGraphData[i].arrGraphData.RemoveAll();

			i++;
		}while(i<m_nCntGraph);

		delete []m_pStGraphData;
		m_pStGraphData = NULL;
	}
	
	m_pStGraphData = new stGraphData[nMax];
	

	for (int i=0; i<nMax; i++)
	{
		m_pStGraphData[i].clrGraphData	= RGB(144 + 10* i,193 + 0.1 * i,215 + 5 * i);
		m_pStGraphData[i].clrGraphPoint  = RGB(72 + 10* i,147 + 0.1 * i,172 + 5 * i);
		m_pStGraphData[i].nSizeGraph	 = 1;
		m_pStGraphData[i].nSizeGraphPoint= 3;
		m_pStGraphData[i].bDrawGraph = true;
		m_pStGraphData[i].bDrawGraphPoint = true;
		m_pStGraphData[i].arrGraphData.RemoveAll();
	}

	if (m_pArrPosGrp != NULL)
	{
		int i=0;
		do{
			if (m_pArrPosGrp[i].GetSize() != 0)
				m_pArrPosGrp[i].RemoveAll();

			i++;
		}while(i<m_nCntGraph);

		delete []m_pArrPosGrp;
		m_pArrPosGrp = NULL;
	}

	m_pArrPosGrp = new CArray<CPoint>[nMax];

	m_nCntGraph = nMax;
}

void CGraphEx::DrawFrameBkg(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.Width(), rect.Height(),m_clrFrmBkg);
}

void CGraphEx::DrawFrameBorder(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID,m_nSizeFrmBorder,m_clrFrmBorder);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(rect.left,rect.top,rect.Width(),rect.Height());

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void CGraphEx::DrawGraphBkg(CDC *pDC)
{
	pDC->FillSolidRect(m_rcGrp.left, m_rcGrp.top, m_rcGrp.Width(), m_rcGrp.Height(), m_clrGrpBkg);
}

void CGraphEx::DrawGraphBorder(CDC *pDC)
{
	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID,m_nSizeGrpBorder,m_clrGrpBorder);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(m_rcGrp.left,m_rcGrp.top,m_rcGrp.right,m_rcGrp.bottom);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void CGraphEx::DrawGraphData(CDC *pDC)
{
	if (m_nCntGraph == 0) return;

	for (int i=0; i<m_nCntGraph; i++)
	{
		if (m_pStGraphData[i].bDrawGraph == false) continue;

		CPen data_pen, *pOldPen, point_pen;
		data_pen.CreatePen(PS_SOLID,m_pStGraphData[i].nSizeGraph,m_pStGraphData[i].clrGraphData);
		point_pen.CreatePen(PS_SOLID, m_pStGraphData[i].nSizeGraphPoint, m_pStGraphData[i].clrGraphPoint);
		pOldPen = (CPen*)pDC->SelectObject(&data_pen);
		
		int nSize = m_pStGraphData[i].arrGraphData.GetSize();

		// for 문을 빼기위해 멤버로 이중 포인터 PointF** 를 추가해 봤지만, Debug 및 Release 에서 실제 tact time의 차이는 크게 없음.
		// X축 4096개의 데이터로 처리해 보았지만 차이 없었음.
		for (int j=0; j<nSize; j++)
		{
			CPoint pt = m_pArrPosGrp[i].GetAt(j);
			
			if (j==0) pDC->MoveTo((int)pt.x, (int)pt.y);
			pDC->LineTo((int)pt.x, (int)pt.y);

			int size = m_pStGraphData[i].nSizeGraphPoint;

			CBrush brs(m_pStGraphData[i].clrGraphPoint);
			CBrush* pOldBrs=NULL;
			pOldBrs = pDC->SelectObject(&brs);
			pOldPen = pDC->SelectObject(&point_pen);
			pDC->Ellipse(pt.x-size, pt.y-size, pt.x+size, pt.y+size);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrs);
		}
		data_pen.DeleteObject();
		point_pen.DeleteObject();
	}

}

void CGraphEx::DrawGraphDataInfo(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CFont* pOldFont=NULL;

	if (m_bDrawInfo == false) return;
	
	float orgX=0,orgY=0;
	if (m_ptMouse.x+m_szInfo.cx > rect.right)
		orgX = (float)(rect.right - m_szInfo.cx);
	else
		orgX = (float)m_ptMouse.x;

	if (m_ptMouse.y+m_szInfo.cy > rect.bottom)
		orgY = (float)(rect.bottom - m_szInfo.cy);
	else
		orgY = (float)m_ptMouse.y;

	pDC->FillSolidRect((int)orgX+5, (int)orgY,m_szInfo.cx,m_szInfo.cy,m_clrInfoBkg);

	stCoordinate ptInfo = m_pStGraphData[m_nCurrGrpData].arrGraphData.GetAt(m_nCurrGrpPoint);
	CString strInfo=L"";
	strInfo.Format(L"Graph : %d",m_nCurrGrpData);
	
	pOldFont = pDC->SelectObject(&m_ftInfo);
	pDC->SetTextColor(m_pStGraphData[m_nCurrGrpData].clrGraphData);
	
	pDC->DrawText(strInfo, CRect((int)orgX+15, (int)orgY, (int)orgX+m_szInfo.cx, (int)orgY+m_szInfo.cy), DT_SINGLELINE | DT_LEFT);
	
	pDC->SelectObject(pOldFont);
	
	strInfo.Format(L"X: %.2f\r\nY: %.2f",ptInfo.x,ptInfo.y);
	
	pOldFont = pDC->SelectObject(&m_ftInfo);
	pDC->SetTextColor(m_clrTextInfo);

	pDC->DrawText(strInfo, CRect((int)orgX+15, (int)orgY+20, (int)orgX+m_szInfo.cx, (int)orgY+m_szInfo.cy), DT_LEFT | DT_VCENTER);

	pDC->SelectObject(pOldFont);
}

void CGraphEx::DrawScaleGridValue(CDC *pDC)
{
	double dStepAxisX = (double) m_rcGrp.Width () / (m_nCntScaleAxisX+1); //0과 Max의 눈금 때문에 +1을 함.
	double dStepAxisY = (double) m_rcGrp.Height() / (m_nCntScaleAxisY+1); 
	double dValueAxisX= m_dMaxAxisX / m_nCntScaleAxisX;
	double dValueAxisY= m_dMaxAxisY / m_nCntScaleAxisY;

	double dPosY=0.0,dPosX=0.0;
	CString textValue=L"";
	CRect rect=CRect(0,0,0,0);
	CFont* pOldFont = NULL;

	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID,m_nSizeGrid,m_clrGrid);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	pDC->SetBkColor(m_clrFrmBkg);
	// 세로 축 눈금을 그리기 위한 루프.
	for (int i=0; i<m_nCntScaleAxisY; i++)
	{
		dPosY = m_rcGrp.top + dStepAxisY * (i+1);
		if (m_bDrawScaleY)
		{
			pDC->MoveTo(m_rcGrp.left-1, int(dPosY));
			pDC->LineTo(m_rcGrp.left-6, int(dPosY));
		}
		if (m_bDrawGrid)
		{
			pDC->MoveTo(m_rcGrp.left+2, int(dPosY));
			pDC->LineTo(m_rcGrp.right-2, int(dPosY));
		}
		if (m_bShowValueY)
		{
			rect.SetRect(m_rcGrp.left - 45, int(dPosY - 8), m_rcGrp.left - 8, int(dPosY + 10));
			if (m_bShowInteger)
				textValue.Format(L"%d", (int)(m_dMaxAxisY - dValueAxisY*i));
			else
				textValue.Format(L"%.1f", m_dMaxAxisY - dValueAxisY*i);
			
			pOldFont = pDC->SelectObject(&m_ftValueAxisY);
			pDC->SetTextColor(m_clrTextValue);
			pDC->DrawText(textValue, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			pDC->SelectObject(pOldFont);
		}
	}
	if (m_bShowOrigin)
	{
		// 원점 표시를 위해 한번 더 출력.
		dPosY = m_rcGrp.top + dStepAxisY * (m_nCntScaleAxisY+1);
		rect.SetRect(m_rcGrp.left - 45 +15, int(dPosY - 8 +7), m_rcGrp.left - 8 +15, int(dPosY + 10 +7));
		if (m_bShowInteger)
			textValue.Format(L"0");
		else
			textValue.Format(L"0.0");
		
		pOldFont = pDC->SelectObject(&m_ftOrigin);
		pDC->SetTextColor(m_clrTextOrigin);
		pDC->DrawText(textValue, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		pDC->SelectObject(pOldFont);
	}

	// 가로 축 눈금을 그리기 위한 루프.
	for (int i=0; i<m_nCntScaleAxisX; i++)
	{
		dPosX = m_rcGrp.left + dStepAxisX * (i+1);

		if (m_bDrawScaleX)
		{
			pDC->MoveTo(int(dPosX), m_rcGrp.bottom+1);
			pDC->LineTo(int(dPosX), m_rcGrp.bottom+6);
		}
		if (m_bDrawGrid)
		{
			pDC->MoveTo(int(dPosX), m_rcGrp.top+2);
			pDC->LineTo(int(dPosX), m_rcGrp.bottom-2);
		}
		if (m_bShowValueX)
		{
			rect.SetRect(int(dPosX - 40), m_rcGrp.bottom + 8, int(dPosX + 40), m_rcGrp.bottom + 26);
			if (m_bShowInteger)
				textValue.Format(L"%d", (int)(dValueAxisX * (i+1)));
			else
				textValue.Format(L"%.1f", dValueAxisX * (i+1));

			pOldFont = pDC->SelectObject(&m_ftValueAxisX);
			pDC->SetTextColor(m_clrTextValue);
			pDC->DrawText(textValue, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			pDC->SelectObject(pOldFont);
		}
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void CGraphEx::DrawLabelText(CDC *pDC)
{
	double dStepAxisX = (double) m_rcGrp.Width () / (m_nCntScaleAxisX+1); //0과 Max의 눈금 때문에 +1을 함.
	CRect rect(0,0,0,0);
	CFont* pOldFont = NULL;

	pDC->SetBkColor(m_clrFrmBkg);
	// 세로 축 라벨 표시.
	if (m_bShowLabel)
	{
		double dPosY=0.0;
		dPosY = m_rcGrp.top ;
		rect.SetRect(m_rcGrp.left - 70, int(dPosY - 8), m_rcGrp.left - 8, int(dPosY + 10));

		pOldFont = pDC->SelectObject(&m_ftLabelAxisY);
		pDC->SetTextColor(m_clrTextLabel);
		pDC->DrawText(m_strAxisY, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		pDC->SelectObject(pOldFont);
	}
	// 세로 축 라벨 표시.
	if (m_bShowLabel)
	{
		double dPosX=0.0;
		dPosX = m_rcGrp.left + dStepAxisX * (m_nCntScaleAxisX+1);
		rect.SetRect(int(dPosX - 40), m_rcGrp.bottom + 8, int(dPosX + 40), m_rcGrp.bottom + 26);
		//pG->DrawString(m_strAxisX,m_strAxisX.GetLength(),&font,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),(REAL)rect.Height()),&formatAlign,&brs);
		pOldFont = pDC->SelectObject(&m_ftLabelAxisY);
		pDC->SetTextColor(m_clrTextLabel);
		pDC->DrawText(m_strAxisX, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		pDC->SelectObject(pOldFont);
	}
}

void CGraphEx::SetFontLabelAxisX(int nSize, CString strStyle)
{
	m_ftLabelAxisX.DeleteObject();
	m_ftLabelAxisX.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontLabelAxisY(int nSize, CString strStyle)
{
	m_ftLabelAxisY.DeleteObject();
	m_ftLabelAxisY.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontLabelAxisX(LOGFONT lftFont)
{
	m_ftLabelAxisX.DeleteObject();
	m_ftLabelAxisX.CreatePointFontIndirect(&lftFont);
	Invalidate();
}
void CGraphEx::SetFontLabelAxisY(LOGFONT lftFont)
{
	m_ftLabelAxisY.DeleteObject();
	m_ftLabelAxisY.CreatePointFontIndirect(&lftFont);
	Invalidate();
}	 
void CGraphEx::SetFontValueAxisX(int nSize, CString strStyle)
{
	m_ftValueAxisX.DeleteObject();
	m_ftValueAxisX.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontValueAxisY(int nSize, CString strStyle)
{
	m_ftValueAxisY.DeleteObject();
	m_ftValueAxisY.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontValueAxisX(LOGFONT lftFont)
{
	m_ftValueAxisX.DeleteObject();
	m_ftValueAxisX.CreatePointFontIndirect(&lftFont);
	Invalidate();
}
void CGraphEx::SetFontValueAxisY(LOGFONT lftFont)
{
	m_ftValueAxisY.DeleteObject();
	m_ftValueAxisY.CreatePointFontIndirect(&lftFont);
	Invalidate();
}
void CGraphEx::SetFontOrigin(int nSize, CString strStyle)
{
	m_ftOrigin.DeleteObject();
	m_ftOrigin.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontOrigin(LOGFONT lftFont)
{
	m_ftOrigin.DeleteObject();
	m_ftOrigin.CreatePointFontIndirect(&lftFont);
	Invalidate();
}
void CGraphEx::SetFontInfo(int nSize, CString strStyle)
{
	m_ftInfo.DeleteObject();
	m_ftInfo.CreateFont(nSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strStyle);

	Invalidate();
}
void CGraphEx::SetFontInfo(LOGFONT lftFont)
{
	m_ftInfo.DeleteObject();
	m_ftInfo.CreatePointFontIndirect(&lftFont);
	Invalidate();
}
// Picture Control을 상속받아 그래프를 생성하면 마우스 이벤트를 받지 못한다. 그래서 Custom Control을 사용.
void CGraphEx::OnMouseMove(UINT nFlags, CPoint point)
{
	bool bBreak=false;
	for (int j=0; j<m_nCntGraph; j++)
	{
		for (int i=0; i<m_pArrPosGrp[j].GetSize(); i++)
		{
			if (bBreak) break;
			int size = m_pStGraphData[j].nSizeGraphPoint;
			if (point.x > m_pArrPosGrp[j].GetAt(i).x-size && point.x < m_pArrPosGrp[j].GetAt(i).x+size &&
				point.y > m_pArrPosGrp[j].GetAt(i).y-size && point.y < m_pArrPosGrp[j].GetAt(i).y+size)
			{
				m_bDrawInfo = true;
				m_ptMouse = point;
				m_nCurrGrpPoint = i;
				m_nCurrGrpData = j;
				bBreak = true;
				break;
			}
			else
				m_bDrawInfo = false;
		}
	}
		
	Invalidate(false);

	CWnd::OnMouseMove(nFlags, point);
}


void CGraphEx::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect(m_rcFrm);	

	m_rcGrp.SetRect(m_rcFrm.left + 75, m_rcFrm.top + 10, m_rcFrm.right - 35, m_rcFrm.bottom - 30);
}

