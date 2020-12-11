; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COGL_MFCDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OGL_MFC.h"

ClassCount=5
Class1=COGL_MFCApp
Class2=COGL_MFCDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDR_TOOLBAR1
Resource2=IDR_MAINFRAME
Class4=OGLControl
Resource3=IDD_OGL_MFC_DIALOG
Resource4=IDD_ABOUTBOX
Class5=CChild
Resource5=IDD_DIALOG_CHILD

[CLS:COGL_MFCApp]
Type=0
HeaderFile=OGL_MFC.h
ImplementationFile=OGL_MFC.cpp
Filter=N
LastObject=COGL_MFCApp

[CLS:COGL_MFCDlg]
Type=0
HeaderFile=OGL_MFCDlg.h
ImplementationFile=OGL_MFCDlg.cpp
Filter=D
LastObject=COGL_MFCDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=OGL_MFCDlg.h
ImplementationFile=OGL_MFCDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_OGL_MFC_DIALOG]
Type=1
Class=COGL_MFCDlg
ControlCount=61
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_CHECK1,button,1476460547
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO1,button,1342177289
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_RADIO3,button,1342177289
Control12=IDC_VIEW1,static,1207959556
Control13=IDC_STATIC,button,1342177287
Control14=IDC_FILTRE1,button,1342177289
Control15=IDC_FILTRE2,button,1342177289
Control16=IDC_FILTRE3,button,1342177289
Control17=IDC_FILTRE4,button,1342177289
Control18=IDC_FILTRE6,button,1342177289
Control19=IDC_STATIC,button,1342177287
Control20=IDC_Point,button,1342177289
Control21=IDC_RADIO10,button,1342177289
Control22=IDC_CHECK2,button,1342242819
Control23=IDC_CHECK3,button,1342242819
Control24=IDC_FILL,button,1342177289
Control25=IDC_CHECK4,button,1342242819
Control26=IDB_BITMAP1,static,1342177294
Control27=IDC_STATIC,button,1342177287
Control28=IDC_RADIO9,button,1342177289
Control29=IDC_RADIO11,button,1342177289
Control30=IDC_RADIO12,button,1342177289
Control31=IDC_STATIC,button,1342177287
Control32=IDC_CHECK5,button,1342242819
Control33=IDC_CHECK6,button,1342242819
Control34=IDC_CHECK7,button,1476460547
Control35=IDC_CHECK8,button,1476460547
Control36=IDC_CHECK9,button,1476460547
Control37=IDC_CHECK10,button,1476460547
Control38=IDC_STATIC,button,1342177287
Control39=IDC_RADIO13,button,1342177289
Control40=IDC_OPEN,button,1476460544
Control41=IDC_BUTTON2,button,1476460544
Control42=IDC_STATIC,button,1342177287
Control43=IDC_FOG,button,1342242819
Control44=IDC_SLIDER1,msctls_trackbar32,1476460568
Control45=IDC_SCROLLBAR1,scrollbar,1476395008
Control46=IDC_SCROLLBAR2,scrollbar,1476395008
Control47=IDC_SCROLLBAR3,scrollbar,1476395008
Control48=IDB_BITMAP2,static,1342177294
Control49=IDC_SLIDER2,msctls_trackbar32,1476460568
Control50=IDC_CHECK11,button,1476460547
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_BACK_COLOR,button,1342242955
Control54=IDC_BUTTON3,button,1342242816
Control55=IDC_PERSPECTIVE,button,1476460547
Control56=IDC_ORTHO,button,1476460547
Control57=IDC_BUTTON1,button,1342242816
Control58=IDC_BUTTON4,button,1342242816
Control59=IDC_BUTTON5,button,1342242816
Control60=IDC_BUTTON6,button,1342242816
Control61=IDC_EDIT1,edit,1350631552

[CLS:OGLControl]
Type=0
HeaderFile=OGLControl.h
ImplementationFile=OGLControl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=ID_BUTTON32771

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_BUTTON32771
CommandCount=1

[DLG:IDD_DIALOG_CHILD]
Type=1
Class=CChild
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CChild]
Type=0
HeaderFile=Child.h
ImplementationFile=Child.cpp
BaseClass=CDialog
Filter=D
LastObject=CChild
VirtualFilter=dWC

