// OGL_MFCDlg.h : header file
//
#include "ColorButton.h"
#include "OGLControl.h"
#include "BitmapViewer.h"

#if !defined(AFX_OGL_MFCDLG_H__3C099E38_939C_4274_A2E0_825E518008AB__INCLUDED_)
#define AFX_OGL_MFCDLG_H__3C099E38_939C_4274_A2E0_825E518008AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COGL_MFCDlg dialog
	// my OpenGL color definition
typedef struct
{
	GLfloat R;
	GLfloat G;
	GLfloat B;
} OPENGL_COLOR;


class COGL_MFCDlg : public CDialog
{
// Construction
public:
	COGL_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	OPENGL_COLOR BackgrounColor;

	// Colors
	float m_ClearColorRed;
	float m_ClearColorGreen;
	float m_ClearColorBlue;
	// Dialog background color
	float m_ClearColorRedBack;
	float m_ClearColorGreenBack;
	float m_ClearColorBlueBack;
public: 
    // Dialog Data
		
	//{{AFX_DATA(COGL_MFCDlg)
	enum { IDD = IDD_OGL_MFC_DIALOG };
	BOOL	m_points;
	BOOL	m_anim;
	BOOL    m_lux;
	BOOL	m_Fil;
	BOOL    m_reset;
	BOOL    m_fill;
	BOOL	m_texture;
	BOOL	m_flat;
	BOOL    m_triangle;
	BOOL	m_fog;
	int		m_xScroll;
	int		m_yScroll;
	int		m_zScroll;
	BOOL	m_anim_xy;
	BOOL	m_triangle_choice;
	CColorButton m_BackgroundColour;
	CColorButton m_BackgroundColour1;
	CColorButton m_getColor;
	BOOL m_animate;
	BOOL	m_Ortho;
	BOOL	m_Perspective;
	BOOL	m_cube;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGL_MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	OGLControl openGLControl;
	BitmapViewer m_BitmapViewer;
	BitmapViewer m_Logo;
	CBrush m_brush; 
	// Generated message map functions
	//{{AFX_MSG(COGL_MFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPoint();
	afx_msg void OnAnim();
	afx_msg void OnFil();
	afx_msg void OnReset();
	afx_msg void OnFiatLux();
	afx_msg void OnFill();
	afx_msg void OnTexture();
	afx_msg void OnFlat();
	afx_msg void OnFiltre1();
	afx_msg void OnFiltre2();
	afx_msg void OnFiltre3();
	afx_msg void OnFiltre4();
	afx_msg void OnFiltre6();
	afx_msg void OnFiltre2x();
	afx_msg void OnFiltre4x();
	afx_msg void OnFiltre8x();
	afx_msg void OnTriangle();
	afx_msg void OnFog();
	afx_msg void OnClick();
	afx_msg void OnBackgrd();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBumpMap();
	afx_msg void OnBackColor();
	afx_msg void OnPerspective();
	afx_msg void OnOrtho(UINT nType, int cx, int cy);
	afx_msg void OnColor();
	afx_msg void OnColorBack();
	afx_msg void OnDialogChild();
	afx_msg void OnNewWindow();
	afx_msg void OnCube();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGL_MFCDLG_H__3C099E38_939C_4274_A2E0_825E518008AB__INCLUDED_)

