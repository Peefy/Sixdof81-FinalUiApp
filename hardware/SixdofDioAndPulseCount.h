
#ifndef _SIXDOF_DIO_AND_PULSE_COUNT_H_
#define _SIXDOF_DIO_AND_PULSE_COUNT_H_

#include <memory>

// ����Ӳ��3��忨��ͷ�ļ�
#include "UserPCI1723.h"
#include "UserPCI1750.h"
#include "UserPCI2394.h"

using namespace std;

// PCI2394����ɼ�������
#define SIXDOF_PCI2394_NUM 2
// �����ɶ�ƽ̨�������
#define SXIDOF_MOTION_NUM 6

// �����ɶ�ƽ̨������IO��������������ģ�������Ƶ����װ��(����֤�̰߳�ȫ)
class SixdofDioAndCount
{
public:
	SixdofDioAndCount();
	~SixdofDioAndCount();
	// ��ʼ���忨
	bool Init();
	// ��ʼ���忨��Ĭ��IO
	void InitStatus();
	// �رհ忨
	bool Close();
	// �������а忨
	bool Test();
	// ��ȡ���е���������������
	ULONG * ReadPulseCount();
	// ���е����������������
	void ClearPulseCount();
	// ���õ����բ����
	void SetMotionLockBit(int index, bool bit);
	// ���õ����բ����
	void SetMotionLockBit(bool* bits);
	// ���õ��ʹ�ܿ���
	void SetMotionEnableBit(int index, bool bit);
	// ���õ��ʹ�ܿ���
	void SetMotionEnableBit(bool* bits);
	// ��ȡ�ӽ�����״̬
	void ReadKBit(int index, bool* bit);
	// ��ȡ�ӽ�����״̬
	void ReadKBit(bool* bits);
	// ���õ���ٶ�
	void SetMotionVel(double * vels);
	// ���õ���ٶ�
	void SetMotionVel(int index, double vel);
	// ʹ�����е��
    void EnableAllMotor(bool isEnable);
	// ������忨����ģʽ - ʹ�ܵ��
	void BigMotionEnable(int index, bool bit);
	// ������忨����ģʽ - ʹ�����е��
	void BigMotionEnable(bool* bits);
	// ������忨����ģʽ - ��ȡ�ӽ�����״̬
	void BigMotionReadKBit(int index, bool* bit);
	// ������忨����ģʽ - ��ȡ�ӽ�����״̬
	void BigMotionReadKBit(bool* bits);
	// ������忨����ģʽ - ʹ�����е��
	void BigMotionEnableAllMotor(bool isEnable);
	// ������忨����ģʽ - ��ȡ�Ƿ񱨾�
	bool BigMotionReadAlarm();
	// ������忨����ģʽ - ��������
	void Start(bool isStart);
	// ������忨����ģʽ - �رտ���
	void CheckStart(bool isStart);
	// ������忨����ģʽ - 
	bool BigMotionTest();

private:
	// �Ƿ��ͷ�������Դ
	bool disposed;
	// �������������
	ULONG pulseCounts[SXIDOF_MOTION_NUM];	
	// PCI2394
	UserPCI2394 pci2394Cards[SIXDOF_PCI2394_NUM];
	// PCI1723
	UserPCI1723 pci1723Card;
	// PCI1750
	UserPCI1750 pci1750Card;
	// ���ݳ�ʼ��
	void DataInit();
};

#endif
