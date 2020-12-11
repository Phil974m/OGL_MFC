// OGL_MFC.h : main header file for the OGL_MFC application
//

#if !defined(AFX_OGL_MFC_H__354EBFE7_086D_48C6_A2FF_4246EEBA038F__INCLUDED_)
#define AFX_OGL_MFC_H__354EBFE7_086D_48C6_A2FF_4246EEBA038F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COGL_MFCApp:
// See OGL_MFC.cpp for the implementation of this class
//

class COGL_MFCApp : public CWinApp
{
public:

	COGL_MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGL_MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COGL_MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGL_MFC_H__354EBFE7_086D_48C6_A2FF_4246EEBA038F__INCLUDED_)
