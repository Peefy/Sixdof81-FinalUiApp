
#include "stdafx.h"
#include "sixdofopenglhelper.h"
#include <math.h>

#define ZERO_POINT_X -0.1
#define ZERO_POINT_Y -0.1
#define ZERO_POINT_Z -0.1

#define IS_LOOK_AT 1

#define BED_HEIGHT     0.10F
#define CUBE_HEIGHT    0.19F 
#define CUBE_WIDTH     0.3F
#define TOTAL_HEIGHT   1.41F  
#define HEAD_HEIGHT    0.12F

#define TOP_BAN_LENGTH 3.20F
#define TOP_BAN_WIDTH  1.72F 

#define POLE_BLUE_REAL_HEIGHT 1.2764F
#define POLE_BLUE_HEIGHT 1.275F
#define POLE_BLUE_RADIUS 0.055F 

#define DFLT_VIEW_LATITUDE  10.0 
#define DFLT_LIGHT_LATITUDE 10.0 
#define DFLT_VIEW_LONGITUDE 10.0 
#define DFLT_VIEWPOINT_X    1.0 
#define DFLT_VIEWPOINT_Y    0.0 
#define DFLT_VIEWPOINT_Z    0.0 
#define DFLT_VIEW_DISTANCE  40.0

#define INIT_Z 0.4
#define GL_MAX_XYZ 100.0

float Roll = 0;
float Yaw = 0; 
float Pitch = 0;
float SCALE_FACTOR = 0.4;

float Tran_X;
float Tran_Y; 
float Tran_Z = INIT_Z; 

void OpenGL_SetData(double x, double y, double z, double roll, double yaw, double pitch)
{
	Tran_X = x * INIT_Z / GL_MAX_XYZ;
	Tran_Y = y * INIT_Z / GL_MAX_XYZ;
	Tran_Z = z * INIT_Z / GL_MAX_XYZ + INIT_Z;
	Roll = -roll;
	Yaw = yaw;
	Pitch = -pitch;
}

void OpenGL_SetRoll(double angle)
{
	Roll = -angle;
}

void OpenGL_SetYaw(double angle)
{
	Yaw = angle;
}

void OpenGL_SetPitch(double angle)
{
	Pitch = -angle;
}

GLUquadricObj *object; 

void MyFrameDisplayWithRotate(void);

int OpenGLControlInit(int panelHandle, int pictureBox)
{
	int OpenglCtrl = -1;
	return OpenglCtrl;
}

void DrawCubeWithColor(float length, float r, float b, float g)
{

	object = gluNewQuadric(); 
	gluQuadricNormals(object, GLU_SMOOTH); // 使用平滑法线
	gluQuadricTexture(object, GL_TRUE); 
	glPushMatrix();
	//画第一个面 
	glColor3f(r,b,g); //     
	glRectf(0,0,length,length);
	//画第二个面 
	glRotatef(-90,0,1,0);
	glRectf(0,0,length,length);  
	glRotatef(90,0,1,0);
	//画第三个面 
	glRotatef(90,1,0,0);
	glRectf(0,0,length,length);  
	glRotatef(-90,1,0,0);
	//画第四个面 
	glTranslatef(0,0,length);
	glRectf(0,0,length,length);    
	//画第五个面
	glTranslatef(length,length,-length); 
	glRotatef(180,0,0,1);
	glRotatef(-90,0,1,0);
	glRectf(0,0,length,length);  
	glRotatef(90,0,1,0);
	//画第六个面
	glRotatef(90,1,0,0); 
	glRectf(0,0,length,length);   
	glRotatef(-90,1,0,0); 
	//绘图回到原点
	glRotatef(-180,0,0,1);
	glTranslatef(-length,-length,0); 

	glPopMatrix();
	gluDeleteQuadric(object);	 

}

void DrawSolidBoxWithColor(float a, float b, float c, float red, float blue,float green)
{

	object = gluNewQuadric(); 
	gluQuadricNormals(object, GLU_SMOOTH); // 使用平滑法线
	gluQuadricTexture(object, GL_TRUE); 
	glPushMatrix();
	//画第一个面 
	glColor3f(red,blue,green); //     
	glRectf(0,0,a,b);
	//画第二个面 
	glRotatef(-90,0,1,0);
	glRectf(0,0,c,b);  
	glRotatef(90,0,1,0);
	//画第三个面 
	glRotatef(90,1,0,0);
	glRectf(0,0,a,c);  
	glRotatef(-90,1,0,0);
	//画第四个面 
	glTranslatef(0,0,c);
	glRectf(0,0,a,b);    
	//画第五个面
	glTranslatef(a,b,-c); 
	glRotatef(180,0,0,1);
	glRotatef(-90,0,1,0);
	glRectf(0,0,c,b);  
	glRotatef(90,0,1,0);
	//画第六个面
	glRotatef(90,1,0,0); 
	glRectf(0,0,a,c);   
	glRotatef(-90,1,0,0); 
	//绘图回到原点
	glRotatef(-180,0,0,1);
	glTranslatef(-a,-b,0); 

	glPopMatrix();
	gluDeleteQuadric(object);	 


}

void DrawBall(float radius,float red,float blue,float green)
{
	object = gluNewQuadric();
	glPushMatrix(); 
	gluSphere(object,radius,50,50);
	glPopMatrix(); 
	gluDeleteQuadric(object);
}

GLfloat Pi = 3.1415926536f;
const int n = 1000;
void DrawCylinder(float baseRadius,float height)
{
	int i = 0;
	float R = baseRadius;
	object = gluNewQuadric();
	glPushMatrix(); 

	glColor3f(1.0f,1.0f,1.0f); 
	gluCylinder(object,baseRadius,baseRadius,height,32,32);//画圆柱

	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();

	GL_TRANS(0,0,height);
	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	GL_TRANS(0,0,-height);

	glPopMatrix(); 
	gluDeleteQuadric(object);
}

void DrawCylinderWithTwoColors(float baseRadius,float heightBlue,float heightWhite)
{
	int i = 0;
	float R = baseRadius;
	float height = heightBlue + heightWhite;
	object = gluNewQuadric();
	glPushMatrix(); 

	glColor3f(0.1f,0.2f,0.9f); 
	gluCylinder(object,baseRadius,baseRadius,heightBlue,32,32);//画圆柱

	//画圆
	R = baseRadius / 1.5;
	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	glColor3f(1.0f,1.0f,1.0f);
	GL_TRANS(0,0,heightBlue);
	gluCylinder(object,R,R,heightWhite,32,32);//画圆柱   

	//画圆 
	GL_TRANS(0,0,heightWhite);
	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	GL_TRANS(0,0,-height);

	glPopMatrix(); 
	gluDeleteQuadric(object);
}

void DrawCylinderWithTwoPoints(float x1,float y1,float z1,float x2,float y2,float z2,float blueHeight,
							   float baseRadius,int isJudgeAngleY)
{

	int i = 0;
	float R = baseRadius;  
	float x_temp = x2 - x1;
	float y_temp = y2 - y1;
	float z_temp = z2 - z1;
	float x_sub = x1 - x2;
	float y_sub = y1 - y2; 
	float z_sub = z1 - z2 ;
	float height = sqrt(x_sub * x_sub + y_sub * y_sub + z_sub * z_sub);
	double angle_temp = atan(y_temp / x_temp); 	
	double angle_z = angle_temp * 180 / Pi;
	double angle_y = 0;
	angle_temp = acos(z_temp / height);
	angle_y = angle_temp * 180.0 / Pi; 
	isJudgeAngleY = x_temp <= 0;
	if(isJudgeAngleY != 0)
		angle_y = -angle_y;	

	object = gluNewQuadric();
	glPushMatrix(); 

	glColor3f(0.1f,0.2f,0.9f); 

	GL_TRANS(x1,y1,z1);
	GL_ROTATE_Z(angle_z);
	GL_ROTATE_Y(angle_y);
	gluCylinder(object,baseRadius,baseRadius,blueHeight,32,32);//画圆柱

	//画圆
	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();

	glColor3f(1.0f,1.0f,1.0f); 
	GL_TRANS(0,0,blueHeight);
	R = baseRadius * 0.6;
	gluCylinder(object,R,R,height - blueHeight,32,32);//画圆柱  

	GL_TRANS(0,0,height - blueHeight); 
	//画圆 
	glBegin(GL_POLYGON);
	for(i=0; i<n; ++i)
		glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	GL_TRANS(0,0,-height);

	glPopMatrix(); 
	gluDeleteQuadric(object);
}

void GetCenterPointFromThreePoints(float x1,float y1,float z1,float x2,float y2 ,float z2,
								   float x3,float y3,float z3,float* center_x,float* center_y,
								   float* center_z)
{

	double a1, b1, c1, d1;
	double a2, b2, c2, d2;
	double a3, b3, c3, d3;

	a1 = (y1*z2 - y2*z1 - y1*z3 + y3*z1 + y2*z3 - y3*z2);
	b1 = -(x1*z2 - x2*z1 - x1*z3 + x3*z1 + x2*z3 - x3*z2);
	c1 = (x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2);
	d1 = -(x1*y2*z3 - x1*y3*z2 - x2*y1*z3 + x2*y3*z1 + x3*y1*z2 - x3*y2*z1);

	a2 = 2 * (x2 - x1);
	b2 = 2 * (y2 - y1);
	c2 = 2 * (z2 - z1);
	d2 = x1 * x1 + y1 * y1 + z1 * z1 - x2 * x2 - y2 * y2 - z2 * z2;

	a3 = 2 * (x3 - x1);
	b3 = 2 * (y3 - y1);
	c3 = 2 * (z3 - z1);
	d3 = x1 * x1 + y1 * y1 + z1 * z1 - x3 * x3 - y3 * y3 - z3 * z3;

	*center_x = -(b1*c2*d3 - b1*c3*d2 - b2*c1*d3 + b2*c3*d1 + b3*c1*d2 - b3*c2*d1)
		/(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
	*center_y =  (a1*c2*d3 - a1*c3*d2 - a2*c1*d3 + a2*c3*d1 + a3*c1*d2 - a3*c2*d1)
		/(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
	*center_z = -(a1*b2*d3 - a1*b3*d2 - a2*b1*d3 + a2*b3*d1 + a3*b1*d2 - a3*b2*d1)
		/(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);

}

void DrawBanFormThreePoints(float x1, float y1, float z1, float x2, float y2, float z2,
							float x3, float y3, float z3)
{

}

void PointRotatef(float angle, float x, float y, float z,
				  float old_x, float old_y, float old_z,
				  float* new_x, float* new_y, float* new_z)
{
	float c = cos(angle * Pi / 180.0);
	float s = sin(angle * Pi / 180.0);
	(*new_x) = (x*x*(1-c)+c) * old_x + (x*y*(1-c)-z*s) * old_y + (x*z*(1-c)+y*s) * old_z;
	(*new_y) = (y*x*(1-c)+z*s) * old_x + (y*y*(1-c)+c) * old_y + (y*z*(1-c)-x*s) * old_z;
	(*new_z) = (x*z*(1-c)-y*s) * old_x + (y*z*(1-c)+x*s) * old_y + (z*z*(1-c)+c) * old_z;
}

void PointRotatef_X(float angle,
					float old_x, float old_y, float old_z,
					float* new_x, float* new_y, float* new_z)
{
	float c = cos(angle * Pi / 180.0);
	float s = sin(angle * Pi / 180.0);
	(*new_x) = old_x;
	(*new_y) = old_y * c - old_z * s;
	(*new_z) = old_z * c + old_y * s;
}

void PointRotatef_Y(float angle,
					float old_x, float old_y, float old_z,
					float* new_x, float* new_y, float* new_z)
{
	float c = cos(-angle * Pi / 180.0);
	float s = sin(-angle * Pi / 180.0);
	(*new_x) = old_x * c - old_z * s;
	(*new_y) = old_y;
	(*new_z) = old_z * c + old_x * s;
}

void PointRotatef_Z(float angle,
					float old_x, float old_y, float old_z,
					float* new_x, float* new_y, float* new_z)
{
	float c = cos(angle * Pi / 180.0);
	float s = sin(angle * Pi / 180.0);
	(*new_x) = old_x * c - old_y * s;
	(*new_y) = old_y * c + old_x * s ;
	(*new_z) = old_z;
}

void PointTrans_XYZ(float dis_x, float dis_y, float dis_z, 
					float old_x, float old_y, float old_z,
					float* new_x, float* new_y, float* new_z)
{
	(*new_x) = old_x + dis_x;
	(*new_y) = old_y + dis_y ;
	(*new_z) = old_z + dis_z;
}

void OpenGlLightInit()
{
	GLfloat specularLight0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0,  GL_AMBIENT,  specularLight0);
	glEnable(GL_LIGHT0);     
	glPushAttrib(GL_ALL_ATTRIB_BITS); 
	glMatrixMode(GL_PROJECTION); 
	glPushMatrix(); 
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix(); 
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH);  
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_BLEND); 
	glEnable(GL_LINE_SMOOTH); 
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight0); 
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);  
	glEnable(GL_LIGHTING);   	
}

void RenderSixdofImage()
{
	MyFrameDisplayWithRotate();
}

//改变上述大小后需要重新计算一下这个 c语言计算不方便 用宏定义
//y = sin(15) * CUBE_WIDTH / 2.0 * sqrt(2);
//x = cos(15) * CUBE_WIDTH / 2.0 * sqrt(2);  
//用matlab计算
double SIN_15_CUBE_Y = 0.0549F;
double COS_15_CUBE_X = 0.2049F;

//底座六棱柱的坐标
const float BedPointX[] = {0.0, 1.5588, 1.5588, 0.0 , -0.5196  ,-0.5196};
const float BedPointY[] = {1.2, 0.3,    -0.3  , -1.2, -0.9,     0.9}; 
const int BedPointCount = 6;
//六个杆的底部坐标
float BottomPolePointX[] = {-0.3147,-0.0549,1.4088,1.4088,-0.0549,-0.3147};
float BottomPolePointY[] = {0.8451,0.9951,0.15,-0.15,-0.9951,-0.8451}; 
float BottomPoleZ = BED_HEIGHT + CUBE_WIDTH / 2.0;
//六个杆的顶部坐标
float TopPolePointX[] = {-0.6696,0.45,0.75,0.75,0.45,-0.6696};
float TopPolePointY[] = {0.15,0.71,0.71,-0.71,-0.71,-0.15}; 
float TopPoleZ = TOTAL_HEIGHT - CUBE_WIDTH / 2.0; 
//杆的旋转角度 单位（deg）
//用matlab计算
float PoleAngleZ[] = {242.9523,-29.4520 , -40.3655 , 220.3655 , 209.4520 , 117.0477}; 
float PoleAngleY[] = {37.6944,29.8598 , -40.5664 ,  40.5664 , -29.8598 ,  37.6944};
//6个杆长
const float PoleHeight[] = {1.2764,1.1646,1.3296,1.3296,1.1646,1.2764};  

void MyFrameDisplayWithRotate(void)
{
	int i;
	float height;

	SIN_15_CUBE_Y = sin(15 / 180 * Pi) * CUBE_WIDTH / 2 * sqrt(2.0);
	COS_15_CUBE_X = cos(15 / 180 * Pi) * CUBE_WIDTH / 2 * sqrt(2.0);

#if IS_LOOK_AT
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();   //坐标原点归位

	glTranslatef(ZERO_POINT_X, ZERO_POINT_Y, ZERO_POINT_Z);

	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);

	glRotatef(-15, 1, 0, 0);
	glRotatef(-45, 0, 0, 1);

#endif

	glScalef(SCALE_FACTOR,SCALE_FACTOR,SCALE_FACTOR);

	GL_TRANS(0,0,-0.8);

	GL_PUSH_DRAW_POINT;
	glColor3f(0.6f,0.4f,0.8f);
	//底座 六棱柱 上底面

	glBegin(GL_POLYGON);
	for(i = 0;i < BedPointCount ;++i)
		glVertex3f(BedPointX[i],BedPointY[i],0.0f); 	
	glEnd();
	//下底面
	glBegin(GL_POLYGON);
	for(i = 0;i < BedPointCount ;++i)
		glVertex3f(BedPointX[i],BedPointY[i],BED_HEIGHT); 	
	glEnd();

	//6个侧面
	for(i = 0;i < BedPointCount - 1;++i) 
	{
		glBegin(GL_POLYGON); 
		glVertex3f(BedPointX[i],BedPointY[i],0.0f); 
		glVertex3f(BedPointX[i],BedPointY[i],BED_HEIGHT);
		glVertex3f(BedPointX[i + 1],BedPointY[i + 1],BED_HEIGHT);
		glVertex3f(BedPointX[i + 1],BedPointY[i + 1],0.0f); 
		glEnd();
	}
	glBegin(GL_POLYGON); 
	glVertex3f(BedPointX[0],BedPointY[0],0.0f); 
	glVertex3f(BedPointX[0],BedPointY[0],BED_HEIGHT);
	glVertex3f(BedPointX[BedPointCount - 1],BedPointY[BedPointCount - 1],BED_HEIGHT);
	glVertex3f(BedPointX[BedPointCount - 1],BedPointY[BedPointCount - 1],0.0f); 
	glEnd();
	GL_POP_DRAW_POINT;

	//3个长方体底座
	GL_PUSH_DRAW_POINT;
	glColor3f(0.1f,0.4f,0.8f); 
	GL_TRANS(BedPointX[0],BedPointY[0],BED_HEIGHT);
	GL_ROTATE_Z(-150);
	DrawSolidBoxWithColor(CUBE_WIDTH * 2,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	GL_PUSH_DRAW_POINT;
	glColor3f(0.1f,0.4f,0.8f); 
	GL_TRANS(BedPointX[3],BedPointY[3],BED_HEIGHT);
	GL_ROTATE_Z(60);
	DrawSolidBoxWithColor(CUBE_WIDTH,CUBE_WIDTH * 2 ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	GL_PUSH_DRAW_POINT;
	glColor3f(0.1f,0.4f,0.8f); 
	GL_TRANS(BedPointX[1],BedPointY[1],BED_HEIGHT);
	GL_ROTATE_Z(180);
	DrawSolidBoxWithColor(CUBE_WIDTH,CUBE_WIDTH * 2 ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	//3个长方体顶座
	height = TOTAL_HEIGHT - CUBE_HEIGHT;
	GL_PUSH_DRAW_POINT;
	//important: Rotate
	glTranslatef(Tran_X,Tran_Y,Tran_Z);
	GL_ROTATE_X(Roll); 
	GL_ROTATE_Y(Pitch);
	GL_ROTATE_Z(Yaw);

	GL_PUSH_DRAW_POINT;						   
	GL_TRANS(BedPointX[4],-CUBE_WIDTH, height);
	GL_ROTATE_Z(90);
	DrawSolidBoxWithColor(CUBE_WIDTH * 2,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	GL_PUSH_DRAW_POINT;
	GL_TRANS(BedPointX[1] / 2.0 ,(BedPointY[0] + BedPointY[1]) / 2.0 ,height);
	GL_ROTATE_Z(-30);
	DrawSolidBoxWithColor(CUBE_WIDTH ,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_ROTATE_Z(90); 
	DrawSolidBoxWithColor(CUBE_WIDTH ,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	GL_PUSH_DRAW_POINT;
	GL_TRANS(BedPointX[2] / 2.0 ,(BedPointY[2] + BedPointY[3]) / 2.0 ,height);
	GL_ROTATE_Z(-60);
	DrawSolidBoxWithColor(CUBE_WIDTH,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_ROTATE_Z(-90);
	DrawSolidBoxWithColor(CUBE_WIDTH,CUBE_WIDTH ,CUBE_HEIGHT,0.1,0.4,0.8);
	GL_POP_DRAW_POINT;

	//顶板
	glColor3f(1.0f,1.0f,1.0f); 
	GL_PUSH_DRAW_POINT;

	GL_TRANS(CUBE_WIDTH * 1.3,0,TOTAL_HEIGHT);
	DrawSolidBoxWithColor(TOP_BAN_LENGTH / 2.0,TOP_BAN_WIDTH / 2.0,HEAD_HEIGHT,1.0,1.0,1.0);
	GL_ROTATE_Z(90);
	DrawSolidBoxWithColor(TOP_BAN_WIDTH / 2.0,TOP_BAN_LENGTH / 2.0,HEAD_HEIGHT,1.0,1.0,1.0); 
	GL_ROTATE_Z(90);
	DrawSolidBoxWithColor(TOP_BAN_LENGTH / 2.0,TOP_BAN_WIDTH/ 2.0 ,HEAD_HEIGHT,1.0,1.0,1.0); 
	GL_ROTATE_Z(90);
	DrawSolidBoxWithColor(TOP_BAN_WIDTH /2.0 ,TOP_BAN_LENGTH / 2.0,HEAD_HEIGHT,1.0,1.0,1.0); 

	GL_POP_DRAW_POINT; 

	GL_POP_DRAW_POINT; 	
	//6个杆

	glColor3f(1.0f,1.0f,1.0f); 
	GL_PUSH_DRAW_POINT;

	BottomPolePointX[0] = BedPointX[5] + COS_15_CUBE_X;
	BottomPolePointY[0] = BedPointY[5] - SIN_15_CUBE_Y; 

	BottomPolePointX[1] = BedPointX[0] - SIN_15_CUBE_Y;
	BottomPolePointY[1] = BedPointY[0] - COS_15_CUBE_X;

	BottomPolePointX[2] = BedPointX[1] - CUBE_WIDTH / 2.0;
	BottomPolePointY[2] = BedPointY[1] - CUBE_WIDTH / 2.0;		

	BottomPolePointX[3] = BottomPolePointX[2];
	BottomPolePointY[3] = -BottomPolePointY[2];	

	BottomPolePointX[4] = BottomPolePointX[1];
	BottomPolePointY[4] = -BottomPolePointY[1];	

	BottomPolePointX[5] = BottomPolePointX[0];
	BottomPolePointY[5] = -BottomPolePointY[0];	

	TopPolePointX[0] = BedPointX[4] - CUBE_WIDTH / 2.0;
	TopPolePointY[0] = CUBE_WIDTH / 2.0;

	TopPolePointX[1] = BedPointX[1] / 2.0 - SIN_15_CUBE_Y;  
	TopPolePointY[1] = (BedPointY[0] + BedPointY[1]) / 2.0  + COS_15_CUBE_X;   

	TopPolePointX[2] = BedPointX[1] / 2.0  + COS_15_CUBE_X;   
	TopPolePointY[2] = (BedPointY[0] + BedPointY[1]) / 2.0  - SIN_15_CUBE_Y; 

	TopPolePointX[3] = TopPolePointX[2];
	TopPolePointY[3] = -TopPolePointY[2];

	TopPolePointX[4] = TopPolePointX[1];
	TopPolePointY[4] = -TopPolePointY[1]; 

	TopPolePointX[5] = TopPolePointX[0];
	TopPolePointY[5] = -TopPolePointY[0]; 
	GL_POP_DRAW_POINT;

	for(i = 0;i < BedPointCount ;++i) 
	{
		float x_temp = TopPolePointX[i];
		float y_temp = TopPolePointY[i];
		float z_temp = TopPoleZ;

		float axis_x[3] = {1,0,0};
		float axis_y[3] = {0,1,0};
		float axis_z[3] = {0,0,1};

		int isJudgeAngle = 0;

		PointRotatef(Roll,axis_x[0],axis_x[1],axis_x[2],x_temp,y_temp,z_temp,&x_temp,
			&y_temp,&z_temp);

		PointRotatef_X(Roll,axis_y[0],axis_y[1],axis_y[2],&axis_y[0],&axis_y[1],&axis_y[2]);
		PointRotatef_X(Roll,axis_z[0],axis_z[1],axis_z[2],&axis_z[0],&axis_z[1],&axis_z[2]);

		PointRotatef(Pitch,axis_y[0],axis_y[1],axis_y[2],x_temp,y_temp,z_temp,&x_temp,
			&y_temp,&z_temp);   

		PointRotatef_Y(Pitch,axis_z[0],axis_z[1],axis_z[2],&axis_z[0],&axis_z[1],&axis_z[2]);  

		PointRotatef(Yaw,axis_z[0],axis_z[1],axis_z[2],x_temp,y_temp,z_temp,&x_temp,
			&y_temp,&z_temp);

		PointTrans_XYZ(Tran_X,Tran_Y,Tran_Z,x_temp,y_temp,z_temp,&x_temp,
			&y_temp,&z_temp);

		GL_PUSH_DRAW_POINT; 
		DrawCylinderWithTwoPoints(BottomPolePointX[i],BottomPolePointY[i],BottomPoleZ,
			x_temp,y_temp,z_temp,POLE_BLUE_HEIGHT,POLE_BLUE_RADIUS,
			isJudgeAngle);

		GL_POP_DRAW_POINT; 
	}
	GL_POP_DRAW_POINT;

}
