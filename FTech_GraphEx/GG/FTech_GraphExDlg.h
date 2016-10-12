
// FTech_GraphExDlg.h : header file
//

#pragma once
#include "include/GraphEx.h"
#include "afxcmn.h"

// CFTech_GraphExDlg dialog
class CFTech_GraphExDlg : public CDialogEx
{
// Construction
public:
	CFTech_GraphExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTech_GraphEx_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public :
	CGraphEx m_wndGrp;
	void InitControls();
	void CreatearrGraphData(int nCount);
// Implementation
protected:
	HICON m_hIcon;

	CSpinButtonCtrl m_SpGraphIndex;
	CSpinButtonCtrl m_SpGraphSize;
	CSpinButtonCtrl m_SpPointSize;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnDeltaposSpgraphindex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedClrbtnrectbkg();
	afx_msg void OnBnClickedClrbtnrectgraph();
	afx_msg void OnBnClickedClrbtngrid();
	afx_msg void OnBnClickedClrbtngraph();
	afx_msg void OnBnClickedClrbtnpoint();
	afx_msg void OnDeltaposSpsizegraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpsizepoint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnfontlabelaxisx();
	afx_msg void OnBnClickedBtnfontlabelaxisy();
	afx_msg void OnBnClickedBtnfontvalueaxisx();
	afx_msg void OnBnClickedBtnfontvalueaxisy();
	afx_msg void OnBnClickedChkdrawgrid();
	afx_msg void OnBnClickedChkdrawtextvalue();
	afx_msg void OnBnClickedChkdrawtextlabel();
	afx_msg void OnBnClickedChkvalueinteger();
	afx_msg void OnBnClickedChkdrawgraph();
	afx_msg void OnBnClickedChkdrawpoint();
};
