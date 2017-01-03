#pragma once

//----------------------------------------------------------
// CGraphEx Control
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2017-01-03 20:14
//----------------------------------------------------------

#define WINCLASSNAME_GRAPHEX L"GRAPHEX_CLASS"

struct stCoordinate
{
	double x;
	double y;
};

struct stGraphData
{
	COLORREF clrGraphData;		// Color Graph Line
	COLORREF clrGraphPoint;	// Color Graph Point
	int nSizeGraph;		// Size Graph Line
	int nSizeGraphPoint;	// Size Graph Point
	bool bDrawGraph;		// Check Draw Graph
	bool bDrawGraphPoint;	// Check Draw Graph Point
	CArray<stCoordinate> arrGraphData;	// Graph Data Position Array
};

class CGraphEx : public CWnd
{
public:
	CGraphEx();
	virtual ~CGraphEx();

	//----- Set & Get Size -----//
	void SetSizeGraph		(CRect rcRect)	{ m_rcGrp = rcRect; Invalidate(FALSE); }
	void SetSizeGraph		(int nOrgX, int nOrgY, int nWidth, int nHeight) { m_rcGrp = CRect(nOrgX, nOrgY, nOrgX+nWidth, nOrgY+nHeight); Invalidate(FALSE); }
	void SetSizeGraphData	(int nIndex, int nSize)	{ if (nIndex <0 || nSize <0) return; m_pStGraphData[nIndex].nSizeGraph		= nSize; Invalidate(); }
	void SetSizeGraphPoint	(int nIndex, int nSize)	{ if (nIndex <0 || nSize <0) return; m_pStGraphData[nIndex].nSizeGraphPoint	= nSize; Invalidate(); }
	void SetSizeFrmBorder	(int nSize) { m_nSizeFrmBorder	= nSize; Invalidate(); }
	void SetSizeGrpBorder	(int nSize) { m_nSizeGrpBorder	= nSize; Invalidate(); }
	void SetSizeScale		(int nSize) { m_nSizeScale		= nSize; Invalidate(); }
	void SetSizeGrid		(int nSize) { m_nSizeGrid		= nSize; Invalidate(); }
	void SetSizeTextValue	(int nSize) { m_nSizeValue		= nSize; Invalidate(); }
	void SetSizeTextLabel	(int nSize) { m_nSizeLabel		= nSize; Invalidate(); }
	void SetSizeTextInfo	(int nSize) { m_nSizeInfo		= nSize; Invalidate(); }
	void SetSizeInfo		(int nWidth, int nHeight) { m_szInfo.cx = nWidth; m_szInfo.cy = nHeight; Invalidate(); }

	int GetSizeGraphData	(int idxGrp) { return m_pStGraphData[idxGrp].nSizeGraph; }
	int GetSizeGraphPoint	(int idxGrp) { return m_pStGraphData[idxGrp].nSizeGraphPoint; }
	int GetSizeFrmBorder	() { return m_nSizeFrmBorder;	}
	int GetSizeGrpBorder	() { return m_nSizeGrpBorder;	}
	int GetSizeScale		() { return m_nSizeScale;		}
	int GetSizeGrid			() { return m_nSizeGrid	;		}
	int GetSizeTextValue	() { return m_nSizeValue;		}
	int GetSizeTextLabel	() { return m_nSizeLabel;		}
	int GetSizeTextInfo		() { return m_nSizeInfo;		}
	
	//----- Set & Get Color -----//
	void SetColorFrmBkg		(COLORREF clrColor) { m_clrFrmBkg		= clrColor; Invalidate(); }
	void SetColorFrmBorder	(COLORREF clrColor) { m_clrFrmBorder	= clrColor; Invalidate(); }
	void SetColorGrpBkg		(COLORREF clrColor) { m_clrGrpBkg		= clrColor; Invalidate(); }
	void SetColorGrpBorder	(COLORREF clrColor) { m_clrGrpBorder	= clrColor; Invalidate(); }
	void SetColorScale		(COLORREF clrColor) { m_clrScale		= clrColor; Invalidate(); }
	void SetColorGrid		(COLORREF clrColor) { m_clrGrid			= clrColor; Invalidate(); }
	void SetColorTextValue	(COLORREF clrColor) { m_clrTextValue	= clrColor; Invalidate(); }
	void SetColorTextLabel	(COLORREF clrColor) { m_clrTextLabel	= clrColor; Invalidate(); }
	void SetColorTextOrigin (COLORREF clrColor) { m_clrTextOrigin	= clrColor; Invalidate(); }
	void SetColorTextInfo	(COLORREF clrColor) { m_clrTextInfo		= clrColor; Invalidate(); }
	void SetColorGraphData	(int nIndex, COLORREF clrColor) { if (nIndex <0) return; m_pStGraphData[nIndex].clrGraphData  = clrColor; Invalidate(); }
	void SetColorGraphPoint	(int nIndex, COLORREF clrColor) { if (nIndex <0) return; m_pStGraphData[nIndex].clrGraphPoint = clrColor; Invalidate(); }
	void SetColorInfoBkg	(COLORREF clrColor) { m_clrInfoBkg		= clrColor; Invalidate(); }

	void SetColorFrmBkg		(int nR, int nG, int nB) { m_clrFrmBkg		= RGB(nR, nG, nB); Invalidate(); }
	void SetColorFrmBorder	(int nR, int nG, int nB) { m_clrFrmBorder	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorGrpBkg		(int nR, int nG, int nB) { m_clrGrpBkg		= RGB(nR, nG, nB); Invalidate(); }
	void SetColorGrpBorder	(int nR, int nG, int nB) { m_clrGrpBorder	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorScale		(int nR, int nG, int nB) { m_clrScale		= RGB(nR, nG, nB); Invalidate(); }
	void SetColorGrid		(int nR, int nG, int nB) { m_clrGrid		= RGB(nR, nG, nB); Invalidate(); }
	void SetColorTextValue	(int nR, int nG, int nB) { m_clrTextValue	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorTextLabel	(int nR, int nG, int nB) { m_clrTextLabel	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorTextOrigin (int nR, int nG, int nB) { m_clrTextOrigin	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorTextInfo	(int nR, int nG, int nB) { m_clrTextInfo	= RGB(nR, nG, nB); Invalidate(); }
	void SetColorGraphData	(int nIndex, int nR, int nG, int nB) { if (nIndex <0) return; m_pStGraphData[nIndex].clrGraphData  = RGB(nR, nG, nB); Invalidate(); }
	void SetColorGraphPoint	(int nIndex, int nR, int nG, int nB) { if (nIndex <0) return; m_pStGraphData[nIndex].clrGraphPoint = RGB(nR, nG, nB); Invalidate(); }
	void SetColorInfoBkg	(int nR, int nG, int nB) { m_clrInfoBkg		= RGB(nR, nG, nB); Invalidate(); }
	
	COLORREF GetColorFrmBkg		() { return m_clrFrmBkg;	}
	COLORREF GetColorFrmBorder	() { return m_clrFrmBorder; }
	COLORREF GetColorGrpBkg		() { return m_clrGrpBkg;	}
	COLORREF GetColorGrpBorder	() { return m_clrGrpBorder; }
	COLORREF GetColorScale		() { return m_clrScale;		}
	COLORREF GetColorGrid		() { return m_clrGrid;		}
	COLORREF GetColorTextValue	() { return m_clrTextValue; }
	COLORREF GetColorTextLabel	() { return m_clrTextLabel; }
	COLORREF GetColorTextOrigin () { return m_clrTextOrigin;}
	COLORREF GetColorTextInfo	() { return m_clrTextInfo;	}
	COLORREF GetColorGraphData	(int idxGrp) { return m_pStGraphData[idxGrp].clrGraphData; }
	COLORREF GetColorGraphPoint	(int idxGrp) { return m_pStGraphData[idxGrp].clrGraphPoint; }
	COLORREF GetColorInfoBkg	() { return m_clrInfoBkg; }
	
	//----- Set Text -----//
	void SetTextLabelAxisX(CString strlabel) { m_strAxisX = strlabel; Invalidate(); }
	void SetTextLabelAxisY(CString strlabel) { m_strAxisY = strlabel; Invalidate(); }
	
	//----- Set & Get Enable Option -----//
	void SetEnableDrawGrid  (bool bEnable) { m_bDrawGrid   = bEnable; Invalidate(); }
	void SetEnableDrawScale (bool bAxisX, bool bAxisY) { m_bDrawScaleX = bAxisX; m_bDrawScaleY = bAxisY; Invalidate(); }
	void SetEnableShowValue (bool bAxisX, bool bAxisY) { m_bShowValueX = bAxisX; m_bShowValueY = bAxisY; Invalidate(); }
	void SetEnableShowLabel (bool bEnable) { m_bShowLabel  = bEnable; Invalidate(); }
	void SetEnableShowOrigin(bool bEnable) { m_bShowOrigin = bEnable; Invalidate(); }
	void SetEnableDrawGraph (int nIndex, bool bEnable)  { if (nIndex <0) return; m_pStGraphData[nIndex].bDrawGraph = bEnable; Invalidate(); }
	void SetEnableDrawGraphPoint (int nIndex, bool bEnable)  { if (nIndex <0) return; m_pStGraphData[nIndex].bDrawGraphPoint = bEnable; Invalidate(); }
	void SetEnableValueInteger(bool bEnable) { m_bShowInteger = bEnable; Invalidate(); }
	bool GetEnableDrawGraph (int nIndex)  { if (nIndex <0) return false; return m_pStGraphData[nIndex].bDrawGraph; }
	bool GetEnableDrawGraphPoint (int nIndex)  { if (nIndex <0) return false; return m_pStGraphData[nIndex].bDrawGraphPoint; }
	
	//----- Set Graph Data -----//
	void SetCountGraph(int nMax);
	void SetMaxValueAxis	(double dValueX, double dValueY) { if (dValueX < 0 || dValueY < 0) return; m_dMaxAxisX = dValueX; m_dMaxAxisY = dValueY; Invalidate();}
	void SetMaxValueAxisX	(double dValue) { if (dValue <0) return; m_dMaxAxisX = dValue; Invalidate();}
	void SetMaxValueAxisY	(double dValue) { if (dValue <0) return; m_dMaxAxisY = dValue; Invalidate();}
	void SetCountScaleAxisX	(int nScale) { if (nScale < 0) return; m_nCntScaleAxisX = nScale; Invalidate(); }
	void SetCountScaleAxisY	(int nScale) { if (nScale < 0) return; m_nCntScaleAxisY = nScale; Invalidate(); }
	void SetCountScale		(int nScaleX, int nScaleY) { if (nScaleX < 0 || nScaleY < 0) return; m_nCntScaleAxisX = nScaleX; m_nCntScaleAxisY = nScaleY; Invalidate(); }
	
	//----- Set & Get Font -----//
	void SetFontLabelAxisX(int nSize, CString strStyle);
	void SetFontLabelAxisY(int nSize, CString strStyle);
	void SetFontLabelAxisX(LOGFONT lftFont);
	void SetFontLabelAxisY(LOGFONT lftFont);

	void SetFontValueAxisX(int nSize, CString strStyle);
	void SetFontValueAxisY(int nSize, CString strStyle);
	void SetFontValueAxisX(LOGFONT lftFont);
	void SetFontValueAxisY(LOGFONT lftFont);

	void SetFontOrigin(int nSize, CString strStyle);
	void SetFontOrigin(LOGFONT lftFont);

	void SetFontInfo(int nSize, CString strStyle);
	void SetFontInfo(LOGFONT lftFont);

	LOGFONT GetFontLabelAxisX() { LOGFONT logFont; m_ftLabelAxisX.GetLogFont(&logFont); return logFont; }
	LOGFONT GetFontLabelAxisY() { LOGFONT logFont; m_ftLabelAxisY.GetLogFont(&logFont); return logFont; }
	LOGFONT GetFontValueAxisX() { LOGFONT logFont; m_ftValueAxisX.GetLogFont(&logFont); return logFont; }
	LOGFONT GetFontValueAxisY() { LOGFONT logFont; m_ftValueAxisY.GetLogFont(&logFont); return logFont; }
	LOGFONT GetFontOrigin	 () { LOGFONT logFont; m_ftOrigin	 .GetLogFont(&logFont); return logFont; }
	LOGFONT GetFontInfo		 () { LOGFONT logFont; m_ftInfo		 .GetLogFont(&logFont); return logFont; }

	//----- Add & Clear Graph Data -----//
	void SetGraphData(int nIndex, stCoordinate* pData, int nArrSize);
	void SetGraphData(int nIndex, int* pXdata, int* pYdata, int nArrSize);
	void ClearGraphData(int nIndex);
	void ClearAllGraphData();

private:
	stGraphData *m_pStGraphData;	// �׷��� ������ ����ü.
	COLORREF m_clrFrmBkg;			// ������ ���� ������.
	COLORREF m_clrFrmBorder;		// ������ ���� ������ ����.
	COLORREF m_clrGrpBkg;			// �׷��� ���� ������.
	COLORREF m_clrGrpBorder;		// �׷��� ���� ������ ����.
	COLORREF m_clrScale;			// ���м��� ����.
	COLORREF m_clrGrid;				// ���ڼ��� ����.
	COLORREF m_clrTextValue;		// Value Text�� ���ڻ���.
	COLORREF m_clrTextLabel;		// Label Text�� ���ڻ���.
	COLORREF m_clrTextOrigin;
	COLORREF m_clrTextInfo;
	COLORREF m_clrInfoBkg;			// ���콺�� ����Ű�� ����Ʈ�� ������ �����ִ� ������ ����.
	CString m_strAxisX;				// X�� Label�� ���ڿ�.
	CString m_strAxisY;				// Y�� Label�� ���ڿ�.
	CRect m_rcGrp;					// �׷��� ����.
	CRect m_rcFrm;					// ������ ����.
	CSize m_szInfo;					// ���콺�� ����Ű�� ����Ʈ�� ������ �����ִ� ����.
	double m_dMaxAxisX;				// X�� �ִ� ��.
	double m_dMaxAxisY;				// Y�� �ִ� ��.
	int m_nSizeFrmBorder;			// ������ ���� ���� ���� ����.
	int m_nSizeGrpBorder;			// �׷��� ���� ���� ���� ����.
	int m_nSizeScale;				// ���м��� ����.
	int m_nSizeGrid;				// ���ڼ��� ����.
	int m_nSizeValue;				// Value Text�� ����ũ��.
	int m_nSizeLabel;				// Label Text�� ����ũ��.
	int m_nSizeInfo;				// ���콺�� ����Ű�� ����Ʈ�� ������ �����ִ� ����ũ��.
	int m_nCntGraph;				// �׷����� ����.
	int m_nCntScaleAxisX;			// X������ �� ��� �� ������.
	int m_nCntScaleAxisY;			// Y������ �� ��� �� ������.
	bool m_bDrawGrid;				// ���ڼ��� �׸� ������.
	bool m_bDrawScaleX;				// X�� ���м��� �׸� ������.
	bool m_bDrawScaleY;				// Y�� ���м��� �׸� ������.
	bool m_bShowLabel;				// Label text�� �׸� ������.
	bool m_bShowValueX;				// X�� Value text�� �׸� ������.
	bool m_bShowValueY;				// Y�� Value text�� �׸� ������.
	bool m_bShowOrigin;				// ���� ǥ��.
	bool m_bShowInteger;			// ���� / �Ҽ������� �����͸� ������.

	CArray<CPoint> *m_pArrPosGrp;	// �׷����� �׷����� ��ǥ ����.
	bool	m_bDrawInfo;			// ���콺 ������ �׸� ������ Ȯ�� ��.
	CPoint	m_ptMouse;				// ���� ���콺�� ��ġ.
	int		m_nCurrGrpPoint;		// ���� ���콺�� ����Ű�� �ִ� Point�� ����.
	int		m_nCurrGrpData;			// ���� ���콺�� ����Ű�� �ִ� Graph�� ����.

	CFont m_ftLabelAxisX;
	CFont m_ftLabelAxisY;
	CFont m_ftValueAxisX;
	CFont m_ftValueAxisY;
	CFont m_ftOrigin;
	CFont m_ftInfo;
	
	void RegisterWindowClass(void);
	void DrawFrameBkg(CDC *pDC);
	void DrawFrameBorder(CDC *pDC);
	void DrawGraphBkg(CDC *pDC);
	void DrawGraphBorder(CDC *pDC);
	void DrawGraphData(CDC *pDC);
	void DrawScaleGridValue(CDC *pDC);
	void DrawLabelText(CDC *pDC);
	void DrawGraphDataInfo(CDC *pDC);

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};