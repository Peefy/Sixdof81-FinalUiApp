
#ifndef _PANEL_H_
#define _PANEL_H_

#include <afxwin.h>         
#include <afxext.h>         
#include <afxdisp.h>        
#include <afxdtctl.h>		
#include <afxcontrolbars.h>

Gdiplus::Bitmap* GetPumpImage( float fMin,float fMax,float fValue, CString strUnit );

#endif
