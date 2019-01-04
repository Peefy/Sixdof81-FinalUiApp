
#include "stdafx.h"
#include "panel.h"

using namespace Gdiplus;

#define FONT_WIDTH_SIZE  100
#define FONT_HEIGHT_SIZE 30

Gdiplus::Bitmap* GetPumpImage( float fMin,float fMax,float fValue, CString strUnit )
{
	const float PI = 3.141592653;
	if(fMin>fValue)
	{
		fMin=fValue;
	}
	if(fValue>fMax)
	{
		fMax=fValue;
	}
	int nWidth,nHeight;
	nWidth=nHeight=200;
	Gdiplus::Rect rect(0,0,nWidth,nHeight);
	int nTable=5;		//	大格
	int nScale=5;		//	每小段里面的小格
	//	每段颜色
	Gdiplus::Color TableColor[]=
	{
		Gdiplus::Color::Green,
		Gdiplus::Color::Blue,
		Gdiplus::Color::Cyan,
		Gdiplus::Color::Yellow,
		Gdiplus::Color::Red
	};
	//	张开的弧度
	float fRadian=60;
	//	同心圆半径
	int nRadius[]=
	{
		200,
		160,
		90
	};
	//	圆心
	Gdiplus::Point ptCenter(nWidth/2,nHeight+20);
	//	刻度线长度
	int nLongScal=15;
	int nShortScal=10;
	//	背景色
	Gdiplus::Color bkColor=Gdiplus::Color::SkyBlue;
	//	刻度字体,大小,颜色
	Gdiplus::Color ScaleColor=Gdiplus::Color::Blue;
	Gdiplus::REAL	ScaleSize=16;
	CString ScaleFont=_T("Times New Roman");

	Gdiplus::Bitmap *pImage = new Gdiplus::Bitmap(nWidth,nHeight);
	Gdiplus::Graphics *pGraph = Graphics::FromImage(pImage);
	Gdiplus::StringFormat format;
	//	消除锯齿
	format.SetAlignment( StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);
	pGraph->SetTextRenderingHint(TextRenderingHintAntiAlias);
	pGraph->Clear(Gdiplus::Color::Transparent);
	Gdiplus::Color LineColor=Gdiplus::Color::Chocolate;
	Gdiplus::Pen LinePen(LineColor,1);
	//	画三段弧
	rect=Gdiplus::Rect(ptCenter.X-nRadius[0],ptCenter.Y-nRadius[0],2*nRadius[0],2*nRadius[0]);
	pGraph->DrawArc(&LinePen,rect,180+(90-fRadian/2),fRadian);
	rect=Gdiplus::Rect(ptCenter.X-nRadius[1],ptCenter.Y-nRadius[1],2*nRadius[1],2*nRadius[1]);
	pGraph->DrawArc(&LinePen,rect,180+(90-fRadian/2),fRadian);
	rect=Gdiplus::Rect(ptCenter.X-nRadius[2],ptCenter.Y-nRadius[2],2*nRadius[2],2*nRadius[2]);
	pGraph->DrawArc(&LinePen,rect,180+(90-fRadian/2),fRadian);

	//	标刻度

	//	分段
	for(int i=0;i<=nTable*nScale;i++)
	{
		Gdiplus::Point p1,p0;
		double f0=((180-fRadian)/2+fRadian/(nTable*nScale)*i)/180*PI;
		p1.X=ptCenter.X+nRadius[1]*cos(f0);
		p1.Y=ptCenter.Y-nRadius[1]*sin(f0);
		if(i%nTable==0)
		{

			{
				p0.X=ptCenter.X+(nRadius[1]+nLongScal)*cos(f0);
				p0.Y=ptCenter.Y-(nRadius[1]+nLongScal)*sin(f0);

				CString str;
				str.Format(_T("%.0f"),fMax-(fMax-fMin)/(nTable*nScale)*i);
				//	获取文本所占的大小
				CSize size = CSize(FONT_WIDTH_SIZE, FONT_HEIGHT_SIZE);// GetOutPutTextSize(pGraph,str,ScaleFont,ScaleSize);
				Gdiplus::RectF textrc;
				textrc.X=p0.X-size.cx/2;
				textrc.Y=p0.Y-size.cy;
				textrc.Width=size.cx;
				textrc.Height=size.cy;
				pGraph->DrawString(
					str,
					-1,
					&Gdiplus::Font(ScaleFont,ScaleSize),
					textrc,
					&format,
					&Gdiplus::SolidBrush(ScaleColor)
					);
				Gdiplus::Point p2,p3;
				int nGap=5;
				p3.X=ptCenter.X+(nRadius[0]+0)*cos(f0);
				p3.Y=ptCenter.Y-(nRadius[0]+0)*sin(f0);
				p2.X=ptCenter.X+(nRadius[0]-nGap)*cos(f0);
				p2.Y=ptCenter.Y-(nRadius[0]-nGap)*sin(f0);
				pGraph->DrawLine(&LinePen,p2,p3);
			}

		}
		else
		{
			p0.X=ptCenter.X+(nRadius[1]+nShortScal)*cos(f0);
			p0.Y=ptCenter.Y-(nRadius[1]+nShortScal)*sin(f0);
		}

		pGraph->DrawLine(&LinePen,p0,p1);
	}

	CString strDataFont=_T("Times New Roman");
	int DataSize = 30;
	Gdiplus::Color DataColor=Gdiplus::Color::Red;

	//	单位
	Gdiplus::RectF UnitRc;
	CSize size = CSize(FONT_WIDTH_SIZE, FONT_HEIGHT_SIZE); //CGraphCurveView::GetOutPutTextSize(pGraph,strUnit,strDataFont,DataSize);
	UnitRc.X=ptCenter.X-size.cx/2;
	UnitRc.Y=ptCenter.Y-(nRadius[0]-nRadius[1]+nRadius[2]+size.cy/2);
	UnitRc.Width=size.cx;
	UnitRc.Height=size.cy;
	pGraph->DrawString(
		strUnit,
		-1,
		&Gdiplus::Font(strDataFont,DataSize),
		UnitRc,
		&format,
		&Gdiplus::SolidBrush(DataColor)
		);

	//	数据
	CString strData;
	strData.Format(_T("%.0f"),fValue);
	size= CSize(FONT_WIDTH_SIZE, FONT_HEIGHT_SIZE);//CGraphCurveView::GetOutPutTextSize(pGraph,strData,strDataFont,DataSize);
	Gdiplus::RectF DataRc;
	DataRc.X=ptCenter.X-size.cx/2;
	DataRc.Y=ptCenter.Y-(nRadius[2]-nLongScal);
	DataRc.Width=size.cx;
	DataRc.Height=size.cy;
	pGraph->DrawString(
		strData,
		-1,
		&Gdiplus::Font(strDataFont,DataSize),
		DataRc,
		&format,
		&Gdiplus::SolidBrush(DataColor)
		);

	//	画指针
	Gdiplus::Pen PointPen(Gdiplus::Color::Green,2);
	Gdiplus::Point p0,p1;
	double f0=((180-fRadian)/2+fRadian/(fMax-fMin)*(-fValue+fMax))/180*PI;
	p0.X=ptCenter.X+(nRadius[2]*cos(f0));
	p0.Y=ptCenter.Y-(nRadius[2]*sin(f0));
	p1.X=ptCenter.X+((nRadius[1]+nShortScal/2)*cos(f0));
	p1.Y=ptCenter.Y-((nRadius[1]+nShortScal/2)*sin(f0));
	pGraph->DrawLine(&PointPen,p0,p1);

	delete pGraph;
	return pImage;

}
