
#ifndef _SIXDOF_H_
#define _SIXDOF_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <Windows.h> 

#include "../config/inihelper.h"
#include "../TYPE_DEF.H"

//Բ����
#define PI 3.1415926

//�����ɶȺ����㷨��dll��������
#define DLL_NAME "Sixdofdll2010.dll"
//�����ɶȷ����㷨��������
#define FUNC_NAME "Control"
//�����������
#define FUNC_NAGIN  6
//�����������
#define FUNC_NAGOUT 6

//�׵�����
#define AXES_COUNT 6

//�����ɶ�X������
#define FREEDOM_X_INDEX     0
//�����ɶ�Y������
#define FREEDOM_Y_INDEX     1
//�����ɶ�Z������
#define FREEDOM_Z_INDEX     2
//�����ɶ�ROLL������
#define FREEDOM_ROLL_INDEX  3
//�����ɶ�PITCH������
#define FREEDOM_PITCH_INDEX 4
//�����ɶ�YAW������
#define FREEDOM_YAW_INDEX   5

//��λ����
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

//����λ����
#define UP_RANGE(x, max) ( (x)>(max) ? (max) : (x) )

//����λ����
#define DOWN_RANGE(x, min) ( (x)<(min) ? (min) : (x) )

//�Ƿ񳬳���Χ
#define IS_OUT_OF_RANGE(x, min, max)   ((x) <= (min) || (x) >= (max)) 

//������var�ĵ�nλ����
#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
//������var�ĵ�nλ��1
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
//��ȡ����var�ĵ�nλ��1
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
//������var�ĵ�nλ��1����0
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

//�������������ɶȱ���
typedef struct 
{
	//��λ0.1mm
	int16_t X;
	//��λ0.1mm
	int16_t Y;
	//��λ0.1mm
	int16_t Z;
	//��λ0.01��
	int16_t Roll;
	//��λ0.01��
	int16_t Pitch;
	//��λ0.01��
	int16_t Yaw;
}DataPackage;

//�����������ɶȱ���
typedef struct 
{
	//��λ1mm
	double X;
	//��λ1mm
	double Y;
	//��λ1mm
	double Z;
	//��λ1��
	double Roll;
	//��λ1��
	double Pitch;
	//��λ1��
	double Yaw;
}DataPackageDouble;

//�����ɶȱ���ģ����
template<class T>
class DataPackageType
{
public:
	// X��λ��
	unique_ptr<T> X;
	// Y��λ��
	unique_ptr<T> Y;
	// Z��λ��
	unique_ptr<T> Z;
	// �����
	unique_ptr<T> Roll;
	//������
	unique_ptr<T> Pitch;
	// ƫ����
	unique_ptr<T> Yaw;
	DataPackageType()
	{
		X = make_unique<T>(new T);
		Y = make_unique<T>(new T);
		Z = make_unique<T>(new T);
		Roll = make_unique<T>(new T);
		Pitch = make_unique<T>(new T);
		Yaw = make_unique<T>(new T);
	}
	~DataPackageType()
	{
		auto ptrX = X.release();
		delete ptrX;
		ptrX = nullptr;
		auto ptrY = Y.release();
		delete ptrY;
		ptrY = nullptr;
		auto ptrZ = Z.release();
		delete ptrZ;
		ptrZ = nullptr;
		auto ptrRoll = Roll.release();
		delete ptrRoll;
		ptrRoll = nullptr;
		auto ptrPitch = Pitch.release();
		delete ptrPitch;
		ptrPitch = nullptr;
		auto ptrYaw = Yaw.release();
		delete ptrYaw;
		ptrYaw = nullptr;
	}
};

//�����ɶ�ƽ̨״̬
typedef enum
{
	SIXDOF_STATUS_BOTTOM,	  //�����ɶ�ƽ̨״̬_�ײ�
	SIXDOF_STATUS_READY,	  //�����ɶ�ƽ̨״̬_����λ
	SIXDOF_STATUS_MIDDLE,	  //�����ɶ�ƽ̨״̬_���ڻ���
	SIXDOF_STATUS_RUN,	      //�����ɶ�ƽ̨״̬_��������
	SIXDOF_STATUS_ISRISING,	  //�����ɶ�ƽ̨״̬_��������
	SIXDOF_STATUS_ISFALLING   //�����ɶ�ƽ̨״̬_�����½�
}SixDofPlatformStatus;

//�����ɶ�ƽ̨״̬�ַ�������
extern char * SixDofStatusText[];

//��DataPackage����
void ResetDefaultData(DataPackage * data);
//��DataPackage��ӡΪ�ַ������
void PrintDataPackageToString(DataPackage data);

#endif

