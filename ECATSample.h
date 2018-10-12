// ECATSample.h : main header file for the ECATSAMPLE application
//

#if !defined(AFX_ECATSAMPLE_H__E1216843_B0FB_4EFF_9B57_A8250F9208AB__INCLUDED_)
#define AFX_ECATSAMPLE_H__E1216843_B0FB_4EFF_9B57_A8250F9208AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CECATSampleApp:
// See ECATSample.cpp for the implementation of this class
//

class CECATSampleApp : public CWinApp
{
public:
	CECATSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECATSampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CECATSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECATSAMPLE_H__E1216843_B0FB_4EFF_9B57_A8250F9208AB__INCLUDED_)
