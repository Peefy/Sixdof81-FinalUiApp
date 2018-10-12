
#include "stdAfx.h"
#include "delta.h"

#include "../EtherCAT_DLL.h"
#include "../EtherCAT_DLL_Err.h"

#include "../config/inihelper.h"

#include "sixdof.h"

MotionControl::MotionControl()
{
    this->CardNo = 0;
	this->DDAGroupNo = 1;
    this->ESCExistCards = 0;
    for (auto i = 0; i < ESCtMaxCardNum; ++i)
    {
        this->ESCCardNoList[i] = 0;
    }
    for (auto i = 0; i < AXES_NUM; ++i)
    {
        this->NodeId[i] = i;
        this->SlotId[i] = 0;
		this->DioSlotId[i] = 0;
    }
    this->disposed = false;
}

MotionControl::~MotionControl()
{
    if (this->disposed == false)
    {
        this->Close();
    }
}

bool MotionControl::InitCard()
{
    U16 uRet = 0;
    auto rt = _ECAT_Master_Open(&this->ESCExistCards);
	if (this->ESCExistCards == 0)
	{
		printf("No EtherCat can be found! Error Code = Ox%x\r\n", rt);
		return false;
	}
    else
    {
        for (auto uCount = 0; uCount < ESCtMaxCardNum; uCount++)
        {
            this->ESCCardNoList[uCount] = 99;
        }
        for (auto uCount = 0; uCount < this->ESCExistCards; uCount++)
        {
            uRet = _ECAT_Master_Get_CardSeq(uCount, &this->CardNo);
            uRet = _ECAT_Master_Initial(this->CardNo);
            if (uRet != 0)
            {
                printf("_ECAT_Master_Initial, ErrorCode = Ox%x\r\n" + uRet);
            }
            else
            {
                this->ESCCardNoList[uCount] = this->CardNo;
            }
        }
        this->CardNo = this->ESCCardNoList[0];
		printf("CardMo:%d\r\n", CardNo);
        return true;
    }
}

bool MotionControl::FindSlave()
{
    U16 nSID = 0, Cnt = 0;
    U16 uNID = 0, uSlaveNum = 0, uReMapNodeID = 0;
    U32 uVendorID = 0, uProductCode = 0, uRevisionNo = 0, uSlaveDCTime = 0;
    auto uRet = _ECAT_Master_Get_SlaveNum(this->CardNo, &this->SlaveNum);
    if (uRet != ERR_ECAT_NO_ERROR)
    {
        printf("_ECAT_Master_Get_SlaveNum, ErrorCode = Ox%x\r\n", uRet);
        return false;
    }
    else
    {
        if (this->SlaveNum == 0)
        {
            printf("Card NO: %d No slave found!", this->CardNo);
        }
        else
        {
            for (uNID = 0; uNID < this->SlaveNum; uNID++)
            {
                uRet = _ECAT_Master_Get_Slave_Info(this->CardNo, uNID, &uReMapNodeID, &uVendorID, &uProductCode, &uRevisionNo, &uSlaveDCTime);

                if (uVendorID == 0x1DD && uProductCode == 0x10305070) // A2E
                {
                    nSID = 0;
                    NodeId[uNID] = uNID;
                    SlotId[uNID] = nSID;
					printf("nodeId:%d slotId:%d\r\n", uNID, nSID);
                    Cnt++;
                }
                else if ((uVendorID == 0x1A05 || uVendorID == 0x1DD) && uProductCode == 0x0624) //Ec4Axis
                {
                    for (nSID = 0; nSID < 4; nSID++)
                    {
                        NodeId[uNID] = uNID;
                        SlotId[uNID] = nSID;
						printf("nodeId:%d slotId:%d\r\n", uNID, nSID);
                        Cnt++;
                    }
                }
                else if ((uVendorID == 0x1A05 || uVendorID == 0x1DD) && uProductCode == 0x5621) //EcAxis
                {
                    nSID = 0;
                    NodeId[uNID] = uNID;
                    SlotId[uNID] = nSID;
					printf("nodeId:%d slotId:%d\r\n", uNID, nSID);
                    Cnt++;
                }
                else if (uVendorID == 0x539 && uProductCode == 0x2200001) //Yaskawa
                {
                    nSID = 0;
                    NodeId[uNID] = uNID;
                    SlotId[uNID] = nSID;
					printf("nodeId:%d slotId:%d\r\n", uNID, nSID);
                    Cnt++;
                }
            }
        }
    }
    return true;
}

bool MotionControl::ServoAllOnOff(bool isOn)
{
	if(isOn == false)
	{
		for (auto i = 0; i < AXES_NUM; ++i)
		{
			_ECAT_Slave_Motion_Sd_Stop(CardNo, NodeId[i], SlotId[i], 0.2);
		}
		return true;
	}
    for (auto i = 0; i < AXES_NUM; ++i)
    {
		U16 on_off = isOn == true ? 1 : 0;
        auto g_uRet = _ECAT_Slave_Motion_Set_Svon(this->CardNo, this->NodeId[i], this->SlotId[i], on_off);
        if (g_uRet != ERR_ECAT_NO_ERROR)
        {
            printf("CS_ECAT_Slave_Motion_Set_Svon node:%d , Error Code = Ox%x\r\n",NodeId[i] ,g_uRet);
        }
    }
    return true;
}

void MotionControl::LockServo()
{
	for (auto i = 0; i < AXES_NUM; ++i)
	{
		U16 on_off = 0;
		auto g_uRet = _ECAT_Slave_Motion_Set_Svon(this->CardNo, this->NodeId[i], this->SlotId[i], on_off);
		if (g_uRet != ERR_ECAT_NO_ERROR) 
		{
			printf("CS_ECAT_Slave_Motion_Set_Svon node:%d , Error Code = Ox%x\r\n",NodeId[i] ,g_uRet);
		}
	}
}

bool MotionControl::ServoStop()
{
    U16 g_uRet;
    for (auto i = 0; i < AXES_NUM; ++i)
    {
        g_uRet = _ECAT_Slave_Motion_Sd_Stop(this->CardNo, this->NodeId[i], this->SlotId[i], MAX_ACC);
        if (g_uRet != ERR_ECAT_NO_ERROR)
        {
            printf("CS_ECAT_Slave_Motion_Sd_Stop, Error Code = Ox%x\r\n", g_uRet);
            return false;
        }
    }
    return true;
}

bool MotionControl::ServoSingleStop(int index)
{
	if (index < 0 || index >= AXES_NUM)
		ServoStop();
	U16 g_uRet;
	auto i = index;
	g_uRet = _ECAT_Slave_Motion_Sd_Stop(this->CardNo, this->NodeId[i], this->SlotId[i], MAX_ACC);
	if (g_uRet != ERR_ECAT_NO_ERROR)
	{
		printf("CS_ECAT_Slave_Motion_Sd_Stop, Error Code = Ox%x\r\n", g_uRet);
		return false;
	}
	return true;
}

bool MotionControl::ResetAlarmSingle(int index)
{
	if (index < 0 || index >= AXES_NUM)
	{
		return false;
	}
	auto i = index;
	auto g_uRet = _ECAT_Slave_Motion_Ralm(this->CardNo, this->NodeId[i], this->SlotId[i]);
	if (g_uRet != ERR_ECAT_NO_ERROR)
	{
		printf("CS_ECAT_Slave_Motion_Ralm, Error Code = Ox%x\r\n", g_uRet);
		return false;
	}
	return true;
}

bool MotionControl::ResetAlarm()
{
    for (auto i = 0; i < AXES_NUM; ++i)
    {
        auto g_uRet = _ECAT_Slave_Motion_Ralm(this->CardNo, this->NodeId[i], this->SlotId[i]);
        if (g_uRet != ERR_ECAT_NO_ERROR)
        {
            printf("CS_ECAT_Slave_Motion_Ralm, Error Code = Ox%x\r\n", g_uRet);
            return false;
        }
    }
    return true;
}

bool MotionControl::ResetStatus()
{
    for (auto i = 0; i < AXES_NUM; ++i)
    {
        auto g_uRet = _ECAT_Slave_Motion_Set_Position(this->CardNo, this->NodeId[i], this->SlotId[i], 0);
		g_uRet = _ECAT_Slave_Motion_Set_Command(this->CardNo, this->NodeId[i], this->SlotId[i], 0);
        if (g_uRet != ERR_ECAT_NO_ERROR)
        {
            printf("CS_ECAT_Slave_Motion_Set_Position, Error Code = Ox%x\r\n", g_uRet);
            return false;
        }
    }
    return true;
}

bool MotionControl::ServoSingleMove(int index, int pulse, int isAbs)
{
	if (index < 0 || index >= AXES_NUM)
	{
		return false;
	}
	auto i = index;
	auto status = _ECAT_Slave_CSP_Start_Move(this->CardNo, this->NodeId[i], this->SlotId[i],
		pulse, 0, RISE_VEL, 0, 0.1, 0.1, 2, isAbs);
	return true;
}

I32 last_pulse[AXES_NUM] = {0, 0, 0, 0, 0, 0};
I32 now_vel[AXES_NUM] = {0, 0, 0, 0, 0, 0};
I32 last_str_vel[AXES_NUM] = {0, 0, 0, 0, 0, 0};
U16 length = 0;
double time_pulse = 0;
double time_pulse_delta = 0.02;

void MotionControl::Control(I32 * pulse)
{
	for(auto i = 0;i < AXES_NUM;++i)
	{
		pulse[i] = (I32)(sin(time_pulse) * DIS_PER_R * 2);// + NowPluse[i];
		time_pulse += time_pulse_delta;

		pulse[i] = RANGE(pulse[i], -MAX_PULSE_NUM, MAX_PULSE_NUM);

		auto re = (I32)((pulse[i] - last_pulse[i]) * 5);
		now_vel[i] = re >= 0 ? re : -re;
		now_vel[i] = RANGE(now_vel[i], 0, MAX_VEL);

		auto status = _ECAT_Slave_CSP_Start_Move(this->CardNo,this->NodeId[i], this->SlotId[i],
			pulse[i], last_str_vel[i], now_vel[i], now_vel[i], 0.1, 0.1, 2, 1);

		last_pulse[i] = pulse[i];
		last_str_vel[i] = now_vel[i];
	}
}

void MotionControl::SixdofControl(I32* pulse)
{
	for (auto i = 0; i < AXES_NUM; ++i)
	{
		pulse[i] = RANGE(pulse[i], -MAX_PULSE_NUM, MAX_PULSE_NUM);

		auto re = (I32)((pulse[i] - last_pulse[i]) * 5);
		now_vel[i] = re >= 0 ? re : -re;
		now_vel[i] = RANGE(now_vel[i], 0, MAX_VEL);
		auto status = _ECAT_Slave_CSP_Start_Move(this->CardNo, this->NodeId[i], this->SlotId[i],
			pulse[i], last_str_vel[i], now_vel[i], now_vel[i], 0.1, 0.1, 2, 1);

		last_pulse[i] = pulse[i];
		last_str_vel[i] = now_vel[i];
	}
}

void MotionControl::Csp(I32 * pulse)
{
	U16 len = 0;
	_ECAT_Slave_Motion_Get_Buffer_Length(CardNo, NodeId[0], SlotId[0], &len);
	if(len < 20)
	{
		SixdofControl(pulse);
	}
}

void MotionControl::Rise()
{
	I32 RiseTargetPulse[AXES_NUM];
	for(auto i = 0;i < AXES_NUM;++i)
	{
		RiseTargetPulse[i] = DIS_PER_R * RISE_RPM;
	}
	auto status = _ECAT_Slave_CSP_Start_Multiaxes_Move(this->CardNo, AXES_NUM, this->NodeId, this->SlotId,
		RiseTargetPulse, 0, RISE_VEL, 0, 0.1, 0.1, 2, 1);
}

void MotionControl::Middle()
{
	I32 pulse_num = 0;
	for(auto i = 0;i < AXES_NUM;++i)
	{
		I32 actual_pos = 0;
		_ECAT_Slave_Motion_Get_Actual_Position(this->CardNo, this->NodeId[i], this->SlotId[i], &actual_pos);
		pulse_num += actual_pos;
	}
	I32 avr_pulse = pulse_num / AXES_NUM;
	I32 targetPulse[AXES_NUM];
	for(auto i = 0;i < AXES_NUM;++i)
	{
		targetPulse[i] = avr_pulse;
	}
	auto status = _ECAT_Slave_CSP_Start_Multiaxes_Move(this->CardNo, AXES_NUM, this->NodeId, this->SlotId,
		targetPulse, 0, MIDDLE_VEL, 0, 0.1, 0.1, 2, 1);
}

void MotionControl::Down()
{
	I32 targetPulse[AXES_NUM];
	for(auto i = 0;i < AXES_NUM;++i)
	{
		targetPulse[i] = -DIS_PER_R * DOWN_RPM;
	}
	auto status = _ECAT_Slave_CSP_Start_Multiaxes_Move(this->CardNo, AXES_NUM, this->NodeId, this->SlotId,
		targetPulse, 0, DOWN_VEL, 0, 0.1, 0.1, 2, 1);
}

void MotionControl::StepDown()
{
	I32 targetPulse[AXES_NUM];
	for(auto i = 0;i < AXES_NUM;++i)
	{
		targetPulse[i] = -DIS_PER_R * STEP_DOWN_RPM;
	}
	auto status = _ECAT_Slave_CSP_Start_Multiaxes_Move(this->CardNo, AXES_NUM, this->NodeId, this->SlotId,
		targetPulse, 0, DOWN_VEL, 0, 0.1, 0.1, 2, 1);
}

int MotionControl::GetDDACount()
{
	U16 count = 0;
	_ECAT_Slave_User_Motion_Control_Get_DataCnt(CardNo, DDAGroupNo,
		&count);
	return count;
}

bool MotionControl::SetDDAData(I32 * dis)
{
	_ECAT_Slave_User_Motion_Control_Set_Data(CardNo, DDAGroupNo,
		dis);
	return true;
}

I32 MotionControl::GetMotionAveragePulse()
{
	I32 pulse_num = 0;
	for(auto i = 0; i < AXES_NUM; ++i)
	{
		I32 actual_pos = 0;
		_ECAT_Slave_Motion_Get_Actual_Position(this->CardNo, this->NodeId[i], this->SlotId[i], &actual_pos);
		pulse_num += actual_pos;
	}
	I32 avr_pulse = pulse_num / AXES_NUM;
	AvrPulse = avr_pulse;
	return avr_pulse;
}

void MotionControl::RenewNowPulse()
{
	for(auto i = 0;i < AXES_NUM;++i)
	{
		I32 actual_pos = 0;
		_ECAT_Slave_Motion_Get_Actual_Position(this->CardNo, this->NodeId[i], this->SlotId[i], &actual_pos);
		NowPluse[i] = actual_pos;
	}
}

U16 MotionControl::GetBufferLength()
{
	U16 len = 0;
	auto reg = _ECAT_Slave_Motion_Get_Buffer_Length(CardNo, NodeId[0], SlotId[0], &len);
	return len;
}

void MotionControl::DisableDDA()
{
	U16 Status = 0;
	U16 GroupNo = 1;
	Status = _ECAT_Slave_User_Motion_Control_Set_Enable_Mode (this->CardNo, GroupNo,
		0);
}

void MotionControl::EnableDDA()
{
	U16 Status = 0;
	U16 GroupNo =1, Type=1, Mode =2, ON_OFF=1, Counter = 0;
	//LockServo();
	Status =_ECAT_Slave_User_Motion_Control_Set_Type (CardNo, GroupNo ,AXES_NUM ,
		this->NodeId, this->SlotId, Type);

	Status = _ECAT_Slave_User_Motion_Control_Set_Enable_Mode (this->CardNo, GroupNo,
		1);

}

void MotionControl::Close()
{
    if (this->ESCExistCards > 0)
    {
        for (int i = 0; i < this->ESCExistCards; i++)
        {
            if (this->ESCCardNoList[i] != 99)
                _ECAT_Master_Reset(this->ESCCardNoList[i]);
        }
        _ECAT_Master_Close();
    }
    this->disposed = true;
}

void MotionControl::MoveToZeroPulseNumber()
{
	this->RenewNowPulse();
	I32 targetPulse[AXES_NUM];
	for (auto i = 0; i < AXES_NUM; ++i)
	{
		targetPulse[i] = -NowPluse[i];
	}
	auto status = _ECAT_Slave_CSP_Start_Multiaxes_Move(this->CardNo, AXES_NUM, this->NodeId, this->SlotId,
		targetPulse, 0, RISE_VEL, 0, 0.1, 0.1, 2, 0);
}

bool MotionControl::GetLimitSwitch()
{
	return true;
}

bool MotionControl::IsAllAtBottom()
{
	for (auto i = 0;i < AXES_NUM;++i)
	{
		auto isAtBottom = IsAtBottoms[i];
		if (isAtBottom == false)
		{
			return false;
		}
	}
	return true;
}

void MotionControl::ReadAllSwitchStatus()
{
	U16 bitValue = 0;
	U16 ErrorCode = DOWN_ERROR_CODE;
	U8 ErrorRegister = DOWN_ERROR_REGISTER;
	for(auto i = 0; i < AXES_NUM; ++i)
	{ 
		U8 Data[5] = { 0 };
		auto re = _ECAT_Slave_Get_EMCY_Data(CardNo, NodeId[i], SlotId[i], &ErrorCode,
			&ErrorRegister, Data);
		if (Data[1] == DOWN_ALARM_CODE)
			IsAtBottoms[i] = true;
		else
			IsAtBottoms[i] = false;
	}
}

/*
六自由度平台状态机
SIXDOF_STATUS_BOTTOM,
SIXDOF_STATUS_READY,
SIXDOF_STATUS_MIDDLE,
SIXDOF_STATUS_RUN,
SIXDOF_STATUS_ISRISING,
SIXDOF_STATUS_ISFALLING,
*/
bool MotionControl::CheckStatus(SixDofPlatformStatus& status)
{
	char* str = "bottom";
	long pulse = 0;
	ReadAllSwitchStatus();
	switch (status)
	{
		case SIXDOF_STATUS_BOTTOM:
			str = "bottom";
			break;
		case SIXDOF_STATUS_READY:
			str = "ready";
			break;
		case SIXDOF_STATUS_MIDDLE:
			str = "middle";
			break;
		case SIXDOF_STATUS_RUN:
			str = "run";
			break;
		case SIXDOF_STATUS_ISRISING:
			str = "isrising";
			pulse = GetMotionAveragePulse();
			if (pulse >= (RISE_RPM - 1) * PULSE_PER_R)
			{
				status = SIXDOF_STATUS_READY;
			}			
			break;
		case SIXDOF_STATUS_ISFALLING:
			str = "isfalling";			
			if (IsAllAtBottom() == true)
			{
				status = SIXDOF_STATUS_BOTTOM;
			}
			break;
		default:
			break;
	}
	Status = status;
	RenewNowPulse();
	config::RecordStatusAndPulse(str, (int)status, NowPluse);
	return true;
}

bool selfTest = false;

bool MotionControl::PowerOnSelfTest(SixDofPlatformStatus laststatus, I32 * lastpulse)
{
	if(selfTest == true)
		return false;
	switch (laststatus)
	{
	case SIXDOF_STATUS_BOTTOM:
		Down();
		break;
	case SIXDOF_STATUS_READY:
		//下降
		//Down();
		break;
	case SIXDOF_STATUS_MIDDLE:
		//Down();
		break;
	case SIXDOF_STATUS_RUN:
		//回中
		for (auto i = 0; i < AXES_NUM; ++i)
		{
			auto status = _ECAT_Slave_CSP_Start_Move(this->CardNo, this->NodeId[i], this->SlotId[i],
				-lastpulse[i], 0, MIDDLE_VEL, 0, 0.5, 0.5, 2, 0);
		}
		//下降
		Down();
		break;
	case SIXDOF_STATUS_ISRISING:
		//下降
		Down();
		break;
	case SIXDOF_STATUS_ISFALLING:
		//下降
		Down();
		break;
	default:
		break;
	}
	selfTest = true;
	return true;
}