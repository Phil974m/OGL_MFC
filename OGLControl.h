#if !defined(AFX_OGLCONTROL_H__BA7D2281_D759_40FC_A31D_32A166D002F3__INCLUDED_)
#define AFX_OGLCONTROL_H__BA7D2281_D759_40FC_A31D_32A166D002F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OGLControl.h : header file
//
#include "OpenGLDevice.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <GL\glext.h>
#include <gl\glaux.h>

typedef struct tagVertex
{
    double east;
	double north;
	double elev;
}VERTEX, *LPVERTEX;
/////////////////////////////////////////////////////////////////////////////
// OGLControl window

class OGLControl : public CWnd
{
protected:
	VERTEX m_StartPoint;
	VERTEX m_EndPoint;
	VERTEX m_MovePoint;
// Construction
public:
	OGLControl();
//	void SetClearColor(void) {	glClearColor(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue,1.0f); }
// Attributes
public:

// Operations
public:
// Mouse 
	BOOL m_LeftButtonDown;
	BOOL m_RightButtonDown;
	BOOL m_MouseWheel;
	BOOL m_MouseMove;
	BOOL m_xyRotation;

	CPoint m_CursorPosition;
	CPoint m_LeftDownPos;
	CPoint m_RightDownPos;

	float m_xRotation;
	float m_yRotation;
	float m_zRotation;

	float m_xTranslate;
	float m_yTranslate;
	float m_zTranslate;

//	float m_xTranslateX; 
//	float m_zTranslateZ;

	// Scale
	float m_xScaling;
	float m_yScaling;
	float m_zScaling;

	float m_SpeedTranslation;
	float m_SpeedRotation;

	// Colors
	float m_ClearColorRed;
	float m_ClearColorGreen;
	float m_ClearColorBlue;

	// Animation
	float m_StepRotationX;
	float m_StepRotationY;
	float m_StepRotationZ;

	GLuint index;

	//Translation
	float m_heading;
	float m_xPosition;
 	float m_zPosition;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OGLControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Create(CRect rect,CWnd* parent);
	virtual ~OGLControl();
	float  rotation_x;
	void List();
	void DrawGLScene();
	void Triangle();
	void LoadTexture();
	float gettime(void);
	void SolidTeapot_1();
	void SolidTeapot_2();
	void SolidTeapot_3();

	void arrowhead();
	void glGrid();
	void Info();

	// Generated message map functions
protected:
	void Axe_Central(void);
	void floor(void);
	void makeCheckImage(void);
	void AxeXYZ_2();
	void InitGL();
	OpenGLDevice openGLDevice;
	CClientDC* dc;
	float rotation;



	//{{AFX_MSG(OGLControl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLCONTROL_H__BA7D2281_D759_40FC_A31D_32A166D002F3__INCLUDED_)
