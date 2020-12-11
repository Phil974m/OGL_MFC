// OGLControl.cpp : implementation file
//

#include "stdafx.h"
#include "OGL_MFC.h"
#include "OGLControl.h"
#include "OGL_MFCDlg.h"
#include <time.h>
#include <GL/glext.h>
#include <math.h>
#include "objets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

unsigned texture[2];
AUX_RGBImageRec *texture1;
AUX_RGBImageRec *texture2;
AUX_RGBImageRec *texture3;

char BufferChar[100];
int frames = 0;
float fps=0;

#ifndef M_PI            // PI  Definition          
#define M_PI 3.14159265 
#endif
#define M_PI180 0.0174532925

//COGL_MFCDlg MFCDlg;
/////////////////////////////////////////////////////////////////////////////
// OGLControl

OGLControl::OGLControl()
{
	dc = NULL;
	rotation = 0.0f;
	// Mouse
	m_LeftButtonDown = FALSE;
	m_RightButtonDown = FALSE;

	// Colors
	m_ClearColorRed   = 0.0f;
	m_ClearColorGreen = 0.0f;
	m_ClearColorBlue  = 0.0f;

	// Animation
	m_StepRotationX = 0.0f;
	m_StepRotationY = 5.0f;
	m_StepRotationZ = 0.0f;
	
	m_SpeedRotation = 1.0f / 5.0f;
	m_SpeedTranslation = 1.0f / 500.0f;

	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	m_zRotation = 0.0f;

//	m_xTranslateX = 0.0f;
//	m_zTranslateZ = 0.0f;

	m_xScaling = 1.0f;
	m_yScaling = 1.0f;
	m_zScaling = 1.0f;

	m_xTranslate = 0.0f;
	m_yTranslate = 0.0f;
	m_zTranslate = 0.0f;
	m_xPosition=0;
    m_zPosition=0;

//	m_ClearColorRed=0.6f;
//	m_ClearColorGreen=0.6f;
//	m_ClearColorBlue=0.6f;
}

OGLControl::~OGLControl()
{
		if (dc)
	{
		delete dc;
	}
}


BEGIN_MESSAGE_MAP(OGLControl, CWnd)
	//{{AFX_MSG_MAP(OGLControl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

PrintGLstring(void *font, char *string)
{  
    int i=0;
    while (string[i])
    glutBitmapCharacter(font,string[i++]);
	return true;
} 

float OGLControl::gettime(void)
{
    static float told=0.0f;
    float tnew,ris;
    tnew=glutGet(GLUT_ELAPSED_TIME);
    ris=tnew-told;
    told=tnew;
    return ris/1000.0;
}

void OGLControl::LoadTexture() 
{
//	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("020briques.bmp");
	glGenTextures (1, &texture[0]);
	glBindTexture (GL_TEXTURE_2D, texture[0]);
	glTexParameteri (GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	AUX_RGBImageRec *texture2;
	texture2 = auxDIBImageLoad("004tissu.bmp");
	// Crée la texture
	glGenTextures(1,&texture[1]);
	glBindTexture(GL_TEXTURE_2D,texture[1]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0, 3,texture2->sizeX,texture2->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE, texture2->data);	
	if (texture1!=NULL)
	{
		delete texture1;

		texture1= NULL;
	} 
};



void OGLControl::SolidTeapot_1()
{  
	COGL_MFCDlg* mfcdlg;
    mfcdlg = new COGL_MFCDlg;
	::glColor3f(0.243,0.544,0.933);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glutSolidTeapot(1.0);
    glColor3f(1.0,1.0,1.0);
//	glColor3f(mfcdlg->m_ClearColorRed,mfcdlg->m_ClearColorGreen,mfcdlg->m_ClearColorBlue);
    glRasterPos3f(0.0f,1.3f,0.5f);
    PrintGLstring(GLUT_BITMAP_HELVETICA_12,"Teapot 3");
//	mfcdlg->Invalidate();
}

void OGLControl::SolidTeapot_2()
{  
	COGL_MFCDlg* mfcdlg;
    mfcdlg = new COGL_MFCDlg;
	::glColor3f(0.643,0.544,0.233);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glutSolidTeapot(1.0);
    glColor3f(1.0,1.0,1.0);
//	glColor3f(mfcdlg->m_ClearColorRed,mfcdlg->m_ClearColorGreen,mfcdlg->m_ClearColorBlue);
    glRasterPos3f(0.0f,1.3f,0.5f);
    PrintGLstring(GLUT_BITMAP_HELVETICA_12,"Teapot 2");
//	mfcdlg->Invalidate();
}

void OGLControl::SolidTeapot_3()
{  
	COGL_MFCDlg* mfcdlg;
    mfcdlg = new COGL_MFCDlg;
	::glColor3f(0.643,0.044,0.933);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glutSolidTeapot(1.0);
    glColor3f(1.0,1.0,1.0);
//	glColor3f(mfcdlg->m_ClearColorRed,mfcdlg->m_ClearColorGreen,mfcdlg->m_ClearColorBlue);
    glRasterPos3f(0.0f,1.3f,0.5f);
    PrintGLstring(GLUT_BITMAP_HELVETICA_12,"Teapot 1");
//	mfcdlg->Invalidate();
}


void OGLControl::Triangle()
{
    glTranslatef(0.0,0.0,1.0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glRasterPos3f(0.0f,1.3f,0.6f);
    PrintGLstring(GLUT_BITMAP_HELVETICA_12,"Triangle");
}

void OGLControl::arrowhead()
{
//	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		// light red x axis arrow
		glColor3f(1.f,0.5f,.5f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		// light green y axis arrow
		glColor3f(.5f,1.f,0.5f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		// light blue z axis arrow
		glColor3f(.5f,.5f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	glBegin(GL_LINES);
		// x letter & arrowhead
		glColor3f(1.f,0.5f,.5f);
		glVertex3f(1.1f,0.1f,0.0f);
		glVertex3f(1.3f,-0.1f,0.0f);
		glVertex3f(1.3f,0.1f,0.0f);
		glVertex3f(1.1f,-0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// y letter & arrowhead
		glColor3f(.5f,1.f,0.5f);
		glVertex3f(-0.1f,1.3f,0.0f);
		glVertex3f(0.f,1.2f,0.0f);
		glVertex3f(0.1f,1.3f,0.0f);
		glVertex3f(0.f,1.2f,0.0f);
		glVertex3f(0.f,1.2f,0.0f);
		glVertex3f(0.f,1.1f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// z letter & arrowhead
		glColor3f(.5f,.5f,1.f);
		glVertex3f(0.0f,-0.1f,1.3f);
		glVertex3f(0.0f,0.1f,1.3f);
		glVertex3f(0.0f,0.1f,1.3f);
		glVertex3f(0.0f,-0.1f,1.1f);
		glVertex3f(0.0f,-0.1f,1.1f);
		glVertex3f(0.0f,0.1f,1.1f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();
//	glEnable(GL_LIGHTING);
}

void OGLControl::Axe_Central(void)
{		
//	    glEnable(GL_LIGHTING);
		glLineWidth(1.0f);
        
     glBegin(GL_LINES);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
        glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
        glVertex3f(0.05f,1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
        glVertex3f(0.0f,1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        glVertex3f(0.0f,0.0f,0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.05f,0.1f,1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
        glVertex3f(0.05f,0.1f,1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
        glVertex3f(-0.05f,-0.1f,1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
     glEnd();
//		glDisable(GL_LIGHTING);
}

void OGLControl::glGrid()
{
//		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glBegin(GL_LINES);

        float d = 50.0f;
		glColor3f(1.0,1.0,0.7);
        for(float i = -d; i <= d; i += 1.0f)
        {
            glVertex3f(i, 0.0f, -d);
            glVertex3f(i, 0.0f, d);
            glVertex3f(-d, 0.0f, i);
            glVertex3f(d, 0.0f, i);
        }

        glEnd();
		glDisable(GL_COLOR_MATERIAL);
//		glDisable(GL_LIGHTING);
}

void OGLControl::makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void OGLControl::floor()
{
   glRotatef(80,0.0,0.0,1.0);
   glTranslatef(0.0,-1,2.0);
   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                     GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                checkImage);

//   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);
   
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
   
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 1.0, -1.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.0, -1.0, -1.0);
   glEnd();
   glFlush();

   glColor3f(1.0,1.0,1.0);
   glRasterPos3f(0.0f,1.3f,0.9f);
   PrintGLstring(GLUT_BITMAP_HELVETICA_12,"Damier");

}
void OGLControl::AxeXYZ_2()
{
	glLoadIdentity();
//	glDisable(GL_LIGHTING);

	// draw carthesian axes
	glTranslatef(-2.0,-1.86,-0.1);

	glBegin(GL_LINES);
		// red x axis
		glColor3f(1.f,0.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// green y axis
		glColor3f(0.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// blue z axis
		glColor3f(0.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();
//	glEnable(GL_LIGHTING);
}

void OGLControl::InitGL()
{
	COGL_MFCDlg MFCDlg;

	glShadeModel(GL_SMOOTH);
	glClearColor(MFCDlg.m_ClearColorRed, MFCDlg.m_ClearColorGreen ,MFCDlg.m_ClearColorBlue, 0.0f);
//	glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
	glClearDepth(1.0f);							
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);

	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
//	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glCullFace(GL_BACK);

	glEnable(GL_MULTISAMPLE);
	glDisable(GL_LIGHTING); 	
  	glDisable(GL_LIGHT0);

//	float matCol[] = {1,0,0,0};
	float matCol[] = {1,0,1,0};
	 /* material properties for objects in scene */
  static GLfloat wall_mat[] =
  {1.f, 1.f, 1.f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,matCol);
		
}

void OGLControl::List()
{
	index = glGenLists(1);
	::glNewList(index,GL_COMPILE);

	::glRotatef(rotation,0.0f,1.0f,0.0f);

	glScalef(0.6,0.6,0.6);
//	::glColor3f(0.643,0.544,0.933);
	glTranslatef(0,-2,0);
	SolidTeapot_1();
	glTranslatef(0,3,0);
	SolidTeapot_2();
	glTranslatef(0,3,0);
	SolidTeapot_3();
//	Triangle();	
    floor();

    ::glEndList();
}

void OGLControl::Info()
{
	glLoadIdentity();
	fps = (fps + frames) / 2; 
    frames = 0;
    glColor3f(1.0f,1.0f,1.0f);
			
	glRasterPos3f(-2.4f,2.2f,0.0f);
    PrintGLstring(GLUT_BITMAP_HELVETICA_12,"SCENE 1.0");
   
	glRasterPos3f(-2.4f,2.0f,0.0f);	
	sprintf(BufferChar,"FPS: %.1f",fps);
	PrintGLstring(GLUT_BITMAP_HELVETICA_12,BufferChar);	
}

void OGLControl::DrawGLScene()
{
	// Useful in multidoc templates
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	glClear(GL_COLOR_BUFFER_BIT	 |  GL_DEPTH_BUFFER_BIT);

    if (!(frames%50))
    {
    fps=50.0/gettime();
	}

	glPushMatrix();
	glClearDepth( 1.0f);
	List();

	::glCallList(index); // call the list of objects

	glLoadIdentity();
	glRotatef(45,1.0,0.0,0.0);
	glScalef(0.5,0.5,0.7);
	glGrid();

	glLoadIdentity();
	glRotatef(45,1.0,0.0,0.0);
	glScalef(0.9,0.9,0.9);
	Axe_Central();
	AxeXYZ_2();
    arrowhead();

	::glDeleteLists(index, 1);

	Info();

	glPopMatrix();

	SwapBuffers(dc->m_hDC);
	glFlush();
	
	// Release
	::ReleaseDC(hWnd,hDC);

}
/////////////////////////////////////////////////////////////////////////////
// OGLControl message handlers
void OGLControl::Create(CRect rect, CWnd *parent) 
{

	CString className = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL);

	CreateEx(
		0,
		className,
		"OpenGL",
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rect,
		parent,
		0);
}

void OGLControl::OnPaint() 
{
	// Useful in multidoc templates
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	glPushMatrix();
////////////////////////////////////////////////////////
	/** OpenGL section **/

	openGLDevice.makeCurrent();

//	glLoadIdentity();
	//Translation
//   m_xTranslate = -m_xPosition;
//	 m_zTranslate = -m_zPosition;	

//	 m_yTranslate = 0.0f;
	//x y z rotation
	glRotatef(m_xRotation, 1.0, 0.0, 0.0);
	glRotatef(m_yRotation, 0.0, 1.0, 0.0);
	glRotatef(m_zRotation, 0.0, 0.0, 1.0);
	//Translation x y z	axis
	glTranslatef(m_xTranslate, m_yTranslate, m_zTranslate);
//	::glTranslatef(m_xTranslateX, 0.0f, m_zTranslateZ);
	glScalef(m_xScaling,m_yScaling,m_zScaling);
    glEnable(GL_LIGHTING);
	DrawGLScene();
	
//	rotation += 0.05f;

	if (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
////////////////////////////////////////////////////////
	glPopMatrix();

	// Double buffer
//	SwapBuffers(dc->m_hDC);
	glFlush();

	// Release
//	::ReleaseDC(hWnd,hDC);
}

void OGLControl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cy == 0)								
	{
		cy = 1;						
	}

	glViewport(0,0,cx,cy);	
	LoadTexture();

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();						
	
    glOrtho(-2.5f,2.5f,-2.5f,2.5f,2.5f,-2.5f);
//  glOrtho(-20.5f,20.5f,-20.5f,20.5f,20.5f,-20.5f);
//	gluPerspective(90.0f,cx/cy,0.01f,35.0f);
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();
}

BOOL OGLControl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CWnd::OnEraseBkgnd(pDC);
}


int OGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	dc = new CClientDC(this);

	openGLDevice.create(dc->m_hDC);
//	glClearColor(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue,1.0f);
	InitGL();
	
	return 0;
}


void OGLControl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LeftButtonDown = TRUE;
    m_LeftDownPos = point;	
	CWnd::OnLButtonDown(nFlags, point);
}

void OGLControl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RightButtonDown = FALSE; 
    m_LeftButtonDown = FALSE; 
	CWnd::OnLButtonUp(nFlags, point);
}

void OGLControl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	SwapBuffers(dc->m_hDC);
	CWnd::OnTimer(nIDEvent);
}



void OGLControl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	

	CPoint temp(point);
	ClientToScreen(&temp);

	// Left : x / y / ztranslation
	if(m_LeftButtonDown && m_RightButtonDown )
	{
		if(m_xyRotation)
		{
			m_yRotation  -= (float)(m_LeftDownPos.x - point.x)* m_SpeedRotation;//5.0f;
			m_xRotation  -= (float)(m_LeftDownPos.y - point.y)* m_SpeedRotation;//5.0f; 		
		}
	else
	{
		m_xRotation  -= (float)(m_LeftDownPos.y - point.y)* m_SpeedRotation;//5.0f;
		m_zRotation  -= (float)(m_LeftDownPos.x - point.x)* m_SpeedRotation;//5.0f; 		
	}

	m_LeftDownPos = point;
	m_RightDownPos = point;
	InvalidateRect(NULL,FALSE);
	}
	else 
	// Left & Right: x / y translation
	if(m_LeftButtonDown )
	{
		m_xTranslate -= (float)(m_LeftDownPos.x - point.x) * m_SpeedTranslation;//5.0;
		m_yTranslate += (float)(m_LeftDownPos.y - point.y) * m_SpeedTranslation;//5.0;
		m_LeftDownPos = point;	
		InvalidateRect(NULL,FALSE);
	}
	else
	//  z translation

	if(m_RightButtonDown)
	{
		m_zTranslate += (float)(m_RightDownPos.y - point.y) * m_SpeedTranslation;//5.0;
		m_RightDownPos = point;
		InvalidateRect(NULL,FALSE);
	}

	CWnd::OnMouseMove(nFlags, point);
	
}

BOOL OGLControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{

    CPoint temp(pt);
	ClientToScreen(&temp);
	if (m_MouseWheel==TRUE)
	{
	    m_xPosition -= zDelta*0.1*M_PI180;//*(float)sin(m_heading*M_PI180) * 1.05f;
		m_zPosition -= zDelta*0.1*M_PI180;//*(float)cos(m_heading*M_PI180) * 1.05f;
//	m_zPosition -= zDelta;
	}
	
	m_MouseWheel = TRUE;

	// TODO: Add your message handler code here and/or call default
	
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void OGLControl::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	m_RightButtonDown = TRUE;
//	m_LeftButtonDown = TRUE;

    m_RightDownPos = point;	
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnRButtonDown(nFlags, point);
}

void OGLControl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_RightButtonDown = FALSE; 
	m_LeftButtonDown = FALSE; 

	CWnd::OnRButtonUp(nFlags, point);
}

void OGLControl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


