// OGL_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OGL_MFC.h"
#include "OGL_MFCDlg.h"
#include "OGLControl.h"
#include "Child.h"
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HDC hdc;
HGLRC hrc;

#define DEFAULT_FOG_START -100.0
#define DEFAULT_FOG_END    100.0
float fogStart = DEFAULT_FOG_START;
float fogEnd = DEFAULT_FOG_END;
float fogDensity = 0.02;
GLint fogMode = GL_EXP;
static float fog_color[] = {0.8, 0.8, 0.8, 1.0};   		
GLfloat getFloat[1];
GLuint _index;

void _Triangle()
{
	   _index = glGenLists(2);
	::glNewList(_index,GL_COMPILE);
		glTranslatef(0,2,-2);
	//	glScalef(1.6,0.6,1.6);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);
	glEnd();	
    ::glEndList();
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGL_MFCDlg dialog

COGL_MFCDlg::COGL_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COGL_MFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COGL_MFCDlg)
	m_lux = TRUE;
	m_texture = FALSE;
	m_flat = FALSE;
	m_fog = FALSE;
	m_xScroll = 0;
	m_yScroll = 0;
	m_zScroll = 0;
	m_anim_xy = FALSE;
	m_triangle_choice = FALSE;
	m_Ortho = FALSE;
	m_Perspective = FALSE;
	m_texture = FALSE;
	m_cube = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COGL_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COGL_MFCDlg)
	DDX_Check(pDX, IDC_CHECK3, m_texture);
	DDX_Check(pDX, IDC_CHECK4, m_flat);
	DDX_Check(pDX, IDC_FOG, m_fog);
	DDX_Scroll(pDX, IDC_SCROLLBAR1, m_xScroll);
	DDX_Scroll(pDX, IDC_SCROLLBAR2, m_yScroll);
	DDX_Scroll(pDX, IDC_SCROLLBAR3, m_zScroll);
	DDX_Check(pDX, IDC_CHECK1, m_anim_xy);
	DDX_Check(pDX, IDC_CHECK8, m_triangle_choice);
	DDX_Control(pDX, IDC_BUTTON3, m_BackgroundColour1);
	DDX_Check(pDX, IDC_ORTHO, m_Ortho);
	DDX_Check(pDX, IDC_PERSPECTIVE, m_Perspective);
	DDX_Control(pDX, IDB_BITMAP1, m_BitmapViewer);
	DDX_Control(pDX, IDB_BITMAP2, m_Logo);
	DDX_Check(pDX, IDC_CHECK5, m_cube);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COGL_MFCDlg, CDialog)
	//{{AFX_MSG_MAP(COGL_MFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Point, OnPoint)
	ON_BN_CLICKED(IDC_CHECK1, OnAnim)
	ON_BN_CLICKED(IDC_RADIO10, OnFil)
	ON_BN_CLICKED(IDOK, OnReset)
	ON_BN_CLICKED(IDC_CHECK2, OnFiatLux)
	ON_BN_CLICKED(IDC_FILL, OnFill)
	ON_BN_CLICKED(IDC_CHECK3, OnTexture)
	ON_BN_CLICKED(IDC_CHECK4, OnFlat)
	ON_BN_CLICKED(IDC_FILTRE1, OnFiltre1)
	ON_BN_CLICKED(IDC_FILTRE2, OnFiltre2)
	ON_BN_CLICKED(IDC_FILTRE3, OnFiltre3)
	ON_BN_CLICKED(IDC_FILTRE4, OnFiltre4)
	ON_BN_CLICKED(IDC_FILTRE6, OnFiltre6)
	ON_BN_CLICKED(IDC_RADIO9, OnFiltre2x)
	ON_BN_CLICKED(IDC_RADIO11, OnFiltre4x)
	ON_BN_CLICKED(IDC_RADIO12, OnFiltre8x)
	ON_BN_CLICKED(IDC_CHECK8, OnTriangle)
	ON_BN_CLICKED(IDC_FOG, OnFog)
	ON_BN_CLICKED(IDB_BITMAP2, OnClick)
	ON_BN_CLICKED(IDC_BACKGRD, OnBackgrd)
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK11, OnBumpMap)
	ON_BN_CLICKED(IDC_BACK_COLOR, OnBackColor)
	ON_BN_CLICKED(IDC_PERSPECTIVE, OnPerspective)
	ON_BN_CLICKED(IDC_ORTHO, OnOrtho)
	ON_BN_CLICKED(IDC_BUTTON1, OnColor)
	ON_BN_CLICKED(IDC_BUTTON3, OnColorBack)
	ON_BN_CLICKED(IDC_BUTTON5, OnDialogChild)
	ON_BN_CLICKED(IDC_BUTTON4, OnNewWindow)
	ON_BN_CLICKED(IDC_CHECK5, OnCube)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGL_MFCDlg message handlers

BOOL COGL_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	SetWindowPos(&this->wndTopMost,200,0,0,0,SWP_NOMOVE|SWP_NOSIZE); // stay on top windows

//	SetWindowPos(NULL,0,0,500,300,SWP_NOZORDER|SWP_NOMOVE);	// Size of the dialog box
//	m_brush.CreateSolidBrush(RGB(m_ClearColorRedBack, m_ClearColorGreenBack, m_ClearColorBlueBack)); // background dialog color brush 	
	
	m_brush.CreateSolidBrush(RGB(225, 230, 250)); // background dialog color brush 
	m_BitmapViewer.SetBitmap(IDB_BITMAP1);	
	m_Logo.SetBitmap(IDB_BITMAP2);
// Opengl View
	CRect rect;              
	GetDlgItem(IDC_VIEW1)->GetWindowRect(rect);
	ScreenToClient(rect);
	openGLControl.Create(rect,this);

// Color picker
//	m_BackgroundColour.SetColor(0x000000FF);

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COGL_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COGL_MFCDlg::OnPaint() 
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
HCURSOR COGL_MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COGL_MFCDlg::OnPoint() 
{

     glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
     InvalidateRect(NULL,FALSE); 	
}

void COGL_MFCDlg::OnAnim() 
{


     InvalidateRect(NULL,FALSE);

}

void COGL_MFCDlg::OnFil() 
{
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	InvalidateRect(NULL,FALSE); 
}	
	
void COGL_MFCDlg::OnReset() 
{
	UpdateData();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
//	glClearColor(m_ClearColorRed, m_ClearColorGreen ,m_ClearColorBlue, 0.0f);
	glClearColor(0.0f, 0.0f , 0.0f, 0.0f);
	glDisable(GL_FOG);
    glDisable(GL_LIGHTING); 	
  	glDisable(GL_LIGHT0); 
	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	m_lux = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	m_texture = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
	m_flat = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
	m_fog = ((CButton*)GetDlgItem(IDC_FOG))->GetCheck();

	if((m_lux = TRUE) && (m_texture = TRUE) && (m_flat = TRUE) && (m_fog = TRUE))
	{
		m_lux = FALSE;
		m_texture = FALSE;
        m_flat = FALSE;
        m_fog = FALSE;
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(m_lux);
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(m_texture);
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(m_flat);
		((CButton*)GetDlgItem(IDC_FOG))->SetCheck(m_fog);
	}

	UpdateData(FALSE);
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiatLux() 
{
	m_lux = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	if(m_lux = TRUE &&  m_lux)
	{
	GLfloat LightAmbient[] =  { 0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 0.1f}; 
	GLfloat LightPosition[] = { 1.0f, 2.0f, 0.0f, 1.0f}; 
	GLfloat LightDiffuse[] = {1.0f,1.0f,1.0f,0.0};
	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT );
		// No attenuation.
	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0f ); 
	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION,  0.0f );
	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f );

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);        
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 

    }
    else
	{
	m_lux = FALSE;
    glDisable(GL_LIGHTING); 	
  	glDisable(GL_LIGHT0); 
	}
   InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFill() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	InvalidateRect(NULL,FALSE);		
}

void COGL_MFCDlg::OnTexture() 
{

	m_texture = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
	if(m_texture = TRUE &&  m_texture)
	{	
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		m_texture = FALSE;
		glDisable(GL_TEXTURE_2D);
	}
	InvalidateRect(NULL,FALSE);	
	
}

void COGL_MFCDlg::OnFlat() 
{
	m_flat = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
	if(m_flat= TRUE &&  m_flat)
	{
		glShadeModel(GL_FLAT);
	}
	else
	{
		m_flat = FALSE;
		glShadeModel(GL_SMOOTH);
	} 	

    InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre1() 
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre2() 
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre3() 
{

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	InvalidateRect(NULL,FALSE);	
}

void COGL_MFCDlg::OnFiltre4() 
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);	
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre6() 
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f) ; 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre2x() 
{
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f) ; 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	InvalidateRect(NULL,FALSE);	
}

void COGL_MFCDlg::OnFiltre4x() 
{
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f) ; 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnFiltre8x() 
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f) ; 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	InvalidateRect(NULL,FALSE);
}

void COGL_MFCDlg::OnTriangle() 
{
	
	glClear(GL_COLOR_BUFFER_BIT	 |  GL_DEPTH_BUFFER_BIT);
	_Triangle();

	m_triangle_choice = !m_triangle_choice;
	if(m_triangle_choice)
	{   	
		glCallList(_index); // call the list of objects
	}
	else
	{
		glDeleteLists(_index, 1);
	}
	InvalidateRect(NULL,TRUE);
}

void COGL_MFCDlg::OnFog() 
{

	
	m_fog = ((CButton*)GetDlgItem(IDC_FOG))->GetCheck();
	if(m_fog = TRUE &&  m_fog)
	{
	glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 2.825);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, -5.0);
    glFogf(GL_FOG_END, 9.0);
    glFogfv(GL_FOG_COLOR, fog_color);

		glClearColor(fog_color[0]+m_ClearColorRed, fog_color[1]+m_ClearColorGreen, fog_color[2]+m_ClearColorBlue,fog_color[3]); 	//	glPrint(18,3,"Program: Display list and fog",0);
		}
		else
		{
        m_fog = FALSE;
		glDisable(GL_FOG);
//		glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
		glClearColor(m_ClearColorRed, m_ClearColorGreen ,m_ClearColorBlue, 0.0f);
		}
		 
	InvalidateRect(NULL,TRUE);
}

void COGL_MFCDlg::OnClick() 
{
	// TODO: Add your control notification handler code here
	
}

void COGL_MFCDlg::OnBackgrd() 
{

}

void COGL_MFCDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
// TODO: Add your message handler code here and/or call default
    if(nIDCtl==IDC_BACK_COLOR)         //checking for the button 
    {
    CDC dc;
    RECT rect;
    dc.Attach(lpDrawItemStruct ->hDC);   // Get the Button DC to CDC
    
    rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
    
    dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0)); 

    dc.FillSolidRect(&rect,RGB(100,100,255));//Here you can define the required color to appear on the Button.
 
    UINT state=lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 

    if((state & ODS_SELECTED))
    {
        dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);

    }
    else
    {
        dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
    }

    dc.SetBkColor(RGB(100,100,255));   //Setting the Text Background color
    dc.SetTextColor(RGB(255,0,0));     //Setting the Text Color


    TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
    ZeroMemory(buffer,MAX_PATH );     //Intializing the buffer to zero
        ::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //Get the Caption of Button Window 
    
    dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//Redraw the  Caption of Button Window 
    
    dc.Detach();  // Detach the Button DC
    }            
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}




HBRUSH COGL_MFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return m_brush;
}

void COGL_MFCDlg::OnBumpMap() 
{
	// TODO: Add your control notification handler code here
	
}

void COGL_MFCDlg::OnBackColor() 
{
	// Simulating a Altkeystroke
	keybd_event(VK_MENU,0xb8,0 , 0);
	keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release


	COLORREF color = RGB((unsigned char)(m_ClearColorRed*255.0f),
		                   (unsigned char)(m_ClearColorGreen*255.0f),
											 (unsigned char)(m_ClearColorBlue*255.0f));
	CColorDialog dlg(color);
	if(dlg.DoModal() == IDOK)
	{
		color = dlg.GetColor();
		m_ClearColorRed   = (float)GetRValue(color)/255.0f;
		m_ClearColorGreen = (float)GetGValue(color)/255.0f;
		m_ClearColorBlue  = (float)GetBValue(color)/255.0f;
		InvalidateRect(NULL,FALSE);
	}

		glClearColor(m_ClearColorRed, m_ClearColorGreen ,m_ClearColorBlue, 0.0f);
 }

void COGL_MFCDlg::OnPerspective() 
{
	// TODO: Add your control notification handler code here
	InvalidateRect(NULL,TRUE);	
}

void COGL_MFCDlg::OnOrtho(UINT nType, int cx, int cy) 
{
	// TODO: Add your control notification handler code here
	CWnd::OnSize(nType, cx, cy);
	
	if (cy == 0)								
	{
		cy = 1;						
	}

	glViewport(0,0,cx,cy);		

    m_Perspective = ! m_Perspective;
	if(m_Perspective)
	{
		gluPerspective(45.0f,cx/cy,0.01f,35.0f);

	}
	else
	{
		glOrtho(-2.5f,2.5f,-2.5f,2.5f,2.5f,-2.5f);
	}	
	InvalidateRect(NULL,TRUE);	
}

void COGL_MFCDlg::OnColor() 
{

// TODO: Add your control notification handler code here
// Simulating a Altkeystroke
	keybd_event(VK_MENU,0xb8,0 , 0);
	keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release

	CColorDialog dlg;

	COLORREF color = RGB((unsigned char)(m_ClearColorRed*255.0f),
		                   (unsigned char)(m_ClearColorGreen*255.0f),
											 (unsigned char)(m_ClearColorBlue*255.0f));
	int retval = dlg.DoModal();

	if(retval == IDOK)

	color = dlg.GetColor();
	
	m_ClearColorRed   = (float)GetRValue(color)/255.0f;
	m_ClearColorGreen = (float)GetGValue(color)/255.0f;
	m_ClearColorBlue  = (float)GetBValue(color)/255.0f;
 
//	glClearColor(m_ClearColorRed, m_ClearColorGreen ,m_ClearColorBlue, 0.0f);
//	glColor3f(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue);
	TRACE("DoModal rend la main =%d\n",retval);	
}

void COGL_MFCDlg::OnColorBack() 
{
// Simulating a Altkeystroke
	keybd_event(VK_MENU,0xb8,0 , 0);
	keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); // Alt Release

	CColorButton CColor;
	
	// TODO: Add your control notification handler code here
	m_ClearColorRedBack  = (float)GetRValue(CColor.GetColor())/255.0f;
	m_ClearColorGreenBack = (float)GetGValue(CColor.GetColor())/255.0f;
	m_ClearColorBlueBack  = (float)GetBValue(CColor.GetColor())/255.0f;
	m_brush.CreateSolidBrush(RGB(m_ClearColorRedBack, m_ClearColorGreenBack, m_ClearColorBlueBack)); // background dialog color brush 	

//	InvalidateRect(NULL,TRUE);
}

void COGL_MFCDlg::OnDialogChild() 
{
	// TODO: Add your control notification handler code here
	CWnd::PostMessage(0x118);
	CChild dlg;

	int view=dlg.DoModal();
	TRACE("DoModal rend la main =%d\n",view);
}

void COGL_MFCDlg::OnNewWindow() 
{
	COGL_MFCDlg dlg;
	int ret = dlg.DoModal();
    TRACE("DoModal rend la main =%d\n",ret);	
}

void COGL_MFCDlg::OnCube() 
{
	m_cube = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();

	if (m_cube = TRUE)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidTeapot(30.0);	
	glLoadIdentity();
//		((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(m_lux);	// TODO: Add your control notification handler code here
		}
	else if (m_cube = FALSE)
	{
//	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(m_lux);
	glTranslatef (0,-1,0);
	glutSolidTeapot(30.0);
	}
	InvalidateRect(NULL,TRUE);
}
