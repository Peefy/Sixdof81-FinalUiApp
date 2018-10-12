#ifndef _Delta_EtherCAT_Master
#define _Delta_EtherCAT_Master

#include "Type_def.h"


#ifndef TYPE_DEF_MOTION_BUFFER
#define TYPE_DEF_MOTION_BUFFER
typedef struct  
{
	U16 NodeID;
	U16 SlotID;
	U16 BitNo;
}MOTION_BUFFER_IO_Information;

typedef struct  
{
	MOTION_BUFFER_IO_Information IO_Info;
	U16 Value;
}MOTION_BUFFER_IO_Set;
#endif
	
#if defined __cplusplus
	extern "C" {
#endif

//=========Master==============	Master Initial & Get��
U16 _stdcall _ECAT_Master_Open(U16 *existcard);																		//�}�d
U16 _stdcall _ECAT_Master_Initial(U16 CardNo);																		//Master��l�ơA�ä��JOP�Ҧ�
U16 _stdcall _ECAT_Master_Reset(U16 CardNo);																			//�����Ҧ�Master�����{�Ǩ�����O���� Close all depend with master and release memory
U16 _stdcall _ECAT_Master_Close(void);																				//���d
U16 _stdcall _ECAT_Master_Get_CardSeq(U16 CardNo_seq, U16 *CardNo);													//���o�d��
U16 _stdcall _ECAT_Master_Get_SlaveNum(U16 CardNo, U16 *SlaveNum);													//���o��e�`Slave��
U16 _stdcall _ECAT_Master_Get_Slave_Info(U16 CardNo, U16 SeqID, U16 *NodeID, U32 *VendorID, U32 *ProductCode, U32 *RevisionNo, U32 *DCTime);	//Ū���U�Ҳո�T
U16 _stdcall _ECAT_Master_Get_DC_Status(U16 CardNo, U32 *State, I32 *DCTime, I32 *OffsetTime);							//Ū��DC��e��T
U16 _stdcall _ECAT_Master_Get_Connect_Status(U16 CardNo, U16 *Status);													//Ū���s�u���A
U16 _stdcall _ECAT_Master_Get_Api_BufferLength(U16 CardNo, U16 NodeID, U16 *Length);									//Ū����e�]�w���`���g���ɶ�
U16 _stdcall _ECAT_Master_Get_Cycle_SpendTime(U16 CardNo, F64 *Tx_Time, F64 *Tx_MaxTime, F64 *Rx_Time, F64 *Rx_MaxTime);	//Ū����e�`�������ӱ����ɶ��γ̤j�ɶ�
U16 _stdcall _ECAT_Master_Check_Initial_Done(U16 CardNo, U16 *InitDone);												//�߰�DLL�h�O�_�wInitial����
U16 _stdcall _ECAT_Master_Get_Initial_ErrorCode(U16 CardNo);															//��_ECAT_Master_Check_Initial_Done���o�Ϳ��~�ɡAŪ�����~��T
U16 _stdcall _ECAT_Master_Check_Working_Counter(U16 CardNo, U16 *Abnormal_Flag, U16 *Working_Slave_Cnt);				//�T�{�q�T�O�_���`�H�η�e�q�TSlave���Ѽƶq
U16 _stdcall _ECAT_Master_Set_Working_Counter_Value(U16 CardNo, U16 Value);												//�W�L�]�w���g���ɶ��|Ĳ�oAbnormal_Flag�A�w�]��1�g���ɶ�
U16 _stdcall _ECAT_Master_Get_Return_Code_Message(U16 ReturnCode, I8 *Message);											//�N�^�ǿ��~�N�X�ର���������~�T��
U16 _stdcall _ECAT_Master_Get_Hardware_ID(U16 CardNo, U16 *DeviceID);

//=========Master==============	Master Config
U16 _stdcall _ECAT_Master_Set_CycleTime(U16 CardNo, U16 Mode);													//�]�w�`���g���ɶ�(U16 CardNo, �ݦbInitial�e�]�w)
U16 _stdcall _ECAT_Master_Get_CycleTime(U16 CardNo, U16 *CycleTime);											//Ū����e�]�w���`���g���ɶ�
U16 _stdcall _ECAT_Master_Get_DLL_SeqID(U16 CardNo, U16 *SeqID);												//���o��eDLL�ϥΪ��ǦCID
U16 _stdcall _ECAT_Master_Get_SerialNo(U16 CardNo, U32 *SerialNo);												//���oPAC��Serial No
U16 _stdcall _ECAT_Master_NodeID_Alias_Enable(U16 CardNo, U16 Enable);											//�]�w�O�_�ϥΦ۩w�q�������\��

U16 _stdcall _ECAT_Autoconfig_Open_File(U16 CardNo, I8 *FilePath);												//Autoconfig from file
U16 _stdcall _ECAT_Autoconfig_Save_File(U16 CardNo, I8 *FilePath);												//Save Node File to file
U16 _stdcall _ECAT_Autoconfig_Set_Slave_DCTime(U16 CardNo, U16 NodeID, U16 Mode);								//�]�w�U�bDC�ɶ�(us)
U16 _stdcall _ECAT_Autoconfig_Clear_ConfigFile(U16 CardNo);														//�M���ثe�w���J���]�w

U16 _stdcall _ECAT_Autoconfig_Set_NodeID_Alias(U16 CardNo, U16 NodeID, U16 MapNodeID);							//�۩w�q����
U16 _stdcall _ECAT_Autoconfig_Get_NodeID_Alias(U16 CardNo, U16 RealNodeID, U16 *MapNodeID);						//���o�۩w�q����
U16 _stdcall _ECAT_Autoconfig_Save_NodeID_Alias(U16 CardNo);													//��ҲհO����϶���ڼg�J�۩w�q����(��API�U�F��|�۰��_�u�ñN�һݸ�T�g�J�ҲհO����A������Ҳջݭ��ҹq��)

//========Normal Slave========= Slave(������)�q��
U16 _stdcall _ECAT_Slave_SDO_Send_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave�q�Ϋ��O�A��ӯ��U�FSDO(CANopen�榡)���O�C
U16 _stdcall _ECAT_Slave_SDO_Read_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave�q�Ϋ��O�A���o�ӯ���eSDO(CANopen�榡)��ơC
U16 _stdcall _ECAT_Slave_SDO_Quick_Send_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave�q�Ϋ��O�A��ӯ��U�FSDO(CANopen�榡)���O�A�������ݫ��O�U�F����
U16 _stdcall _ECAT_Slave_SDO_Quick_Read_Message(U16 CardNo, U16 NodeID, U16 SlotID, U16 Index, U16 SubIndex, U16 DataSize);		//Slave�q�Ϋ��O�A��ӯ��U�FSDOŪ�����O(CANopen�榡)
U16 _stdcall _ECAT_Slave_SDO_Read_Response(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Done, U8 *Data, U32 *ErrorCode);			//Slave�q�Ϋ��O�A��ӯ�Ū���^�Ǹ��(CANopen�榡)
U16 _stdcall _ECAT_Slave_SDO_Wait_All_Done(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo);				//Slave�q�Ϋ��O�A��ƼƯ��U�F���Է�e�ֿn��SDO���O���Ƨ���
U16 _stdcall _ECAT_Slave_SDO_Check_Done(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Done);
U16 _stdcall _ECAT_Slave_SDO_Get_ErrorCode(U16 CardNo, U16 NodeID, U16 SlotNo, U32 *ErrorCode);				//Ū���̫�@����ERR_ECAT_SDO_Return_Error�o�ͮɪ�ErrorCode�AErrorCode�C��i�ѦҦU�Ҳթw�q
U16 _stdcall _ECAT_Slave_PDO_Get_OD_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 IOType, U16 ODIndex, U16 ODSubIndex, U16 ByteSize, U8 *Data);	//"Slave�q�Ϋ��O�A��ӯ�Ū���Y�@OD�X����ơA�Ӹ�ƻݦ��M�g��PDO�c����, IOType 0:Rx 1:Tx"
U16 _stdcall _ECAT_Slave_PDO_Set_OD_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 ODIndex, U16 ODSubIndex, U8 *Data); //"Slave�q�Ϋ��O�A��ӯ��U�F�Y�@OD�X����ơA�Ӹ�ƻݦ��M�g��PDO�c����, ��Tx�i�ϥ�"
U16 _stdcall _ECAT_Slave_PDO_Get_Information(U16 CardNo, U16 NodeID, U16 SlotNo, U16 IOType, U16 *ODCnt, U16 *StartIndex);
U16 _stdcall _ECAT_Slave_PDO_Get_Detail_Mapping(U16 CardNo, U16 NodeID, U16 SlotNo, U16 IOType, U16 ODSeqID, U16 *ODIndex, U16 *ODsubIndex, U16 *ODBitSize, U16 *ODStartIndex);
U16 _stdcall _ECAT_Slave_PDO_Get_Rx_Data(U16 CardNo, U8 *Data);
U16 _stdcall _ECAT_Slave_PDO_Get_Tx_Data(U16 CardNo, U8 *Data);
U16 _stdcall _ECAT_Slave_PDO_Set_Tx_Detail_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 ODStartIndex, U16 Bytesize, U8 *Data);
U16 _stdcall _ECAT_Slave_PDO_Set_Tx_Data(U16 CardNo, U8 *Data);
U16 _stdcall _ECAT_Slave_Get_EMCY_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ErrorCode, U8 *ErrorRegister, U8 Data[5]);  // 2016-02-19
U16 _stdcall _ECAT_Slave_Get_Connect_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *OpState, U16 *AlarmStatus);  // 2016-03-29
U16 _stdcall _ECAT_Slave_Request_State(U16 CardNo, U16 NodeID, U16 SlotNo, U16 OpState);  // 2016-11-22
U16 _stdcall _ECAT_Slave_Get_ESC_Error_Counter(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Processing_Unit_Error_Counter, U16 *PDI_Error_Counter);

//========Motion Salve========= Slave(Motion����)�q��
U16 _stdcall _ECAT_Slave_Motion_Get_MoveMode(U16 CardNo, U16 NodeID, U16 SlotNo, U8 *Mode);							//Ū����eMotionSlave���ʧ@�Ҧ� 0:�żҦ� 1:PP 3:PV 4:PT 6:Home 8:CSP
U16 _stdcall _ECAT_Slave_Motion_Get_ControlWord(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ControllWord);				//Ū����eMotionSlave��ControlWord
U16 _stdcall _ECAT_Slave_Motion_Get_StatusWord(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *StatusWord);				//Ū����eMotionSlave��StatusWord
U16 _stdcall _ECAT_Slave_Motion_Get_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Command);						//Ū����eMotionSlave��Command
U16 _stdcall _ECAT_Slave_Motion_Get_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Position);					//Ū����eMotionSlave��Position
U16 _stdcall _ECAT_Slave_Motion_Get_Actual_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *ActualCommand);			//Ū����eMotionSlave�����Command(����VirtualCommand�v�T)
U16 _stdcall _ECAT_Slave_Motion_Get_Actual_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *ActualPosition);		//Ū����eMotionSlave�����Position(����VirtualCommand�v�T)
U16 _stdcall _ECAT_Slave_Motion_Get_Mdone(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Mdone);							//Ū����eMotionSlave���B�ʧ������A(Motion Done)
U16 _stdcall _ECAT_Slave_Motion_Get_Speed(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Speed);  						//Ū����eMotionSlave��Command Speed 2017-04-19
U16 _stdcall _ECAT_Slave_Motion_Get_Current_Speed(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Speed);					//Ū����eMotionSlave��Current Speed
U16 _stdcall _ECAT_Slave_Motion_Get_Torque(U16 CardNo, U16 NodeID, U16 SlotNo, I16 *Torque);						//Ū����eMotionSlave��Toruqe��
U16 _stdcall _ECAT_Slave_Motion_Get_Target_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *TargetCommand);			//SlaveMotion���O�A���o��e�ؼЦ�m�����
U16 _stdcall _ECAT_Slave_Motion_Get_Buffer_Length(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *BufferLength);			//Ū����e���OBuffer�ƶq

U16 _stdcall _ECAT_Slave_Motion_Set_MoveMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 OpMode);						//�]�w��eMotionSlave���ʧ@�Ҧ� 0:�żҦ� 1:PP 3:PV 4:PT 6:Home 8:CSP
U16 _stdcall _ECAT_Slave_Motion_Set_Svon(U16 CardNo, U16 NodeID, U16 SlotNo, U16 On_Off);							//�]�w��eMotionSlave Sever On / Off
U16 _stdcall _ECAT_Slave_Motion_Ralm(U16 CardNo, U16 NodeID, U16 SlotNo);											//���m��eMotionSlave�����~���A
U16 _stdcall _ECAT_Slave_Motion_Set_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Pos);							//�]�w��eMotionSlave����m
U16 _stdcall _ECAT_Slave_Motion_Set_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Cmd);							//�]�w��eMotionSlave���R�O��m
U16 _stdcall _ECAT_Slave_Motion_Emg_Stop(U16 CardNo, U16 NodeID, U16 SlotNo);										//���eMotionSlave�U�F�氱���O
U16 _stdcall _ECAT_Slave_Motion_Sd_Stop(U16 CardNo, U16 NodeID, U16 SlotNo, F64 Tdec);								//���eMotionSlave�U�F��t������O
U16 _stdcall _ECAT_Slave_Motion_Set_Alm_Reaction(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Fault_Type, U16 WR_Type);	//�]�wAlm�ɪ��������� 0:���z�|, 1:�W�tĲ�o, 2:�ä[����	�w�]�� 2 / 1
U16 _stdcall _ECAT_Slave_Motion_Set_Internal_Limit_Active_Reaction(U16 CardNo, U16 NodeID, U16 SlotID, U16 Internal_Limit_Active_Type);	//�]�wila�ɪ��������� 0:���z�|, 1:EMG, 2:MASK
U16 _stdcall _ECAT_Slave_Motion_Set_Command_Wait_Target_Reach(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Wait);  // 2016-10-27
U16 _stdcall _ECAT_Slave_Motion_Ignore_Sd_Stop_Wrong_Value(U16 CardNo, U8 Ignore);  // 2016-12-19

U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 TriggerMode, U16 Signal_Source);	//SlaveMotion���O�A�]�w�yĲ�o�^���z�\�઺�欰�Ҧ�
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_QuickStart(U16 CardNo, U16 NodeID, U16 SlotNo);									//SlaveMotion���O�A�ֳt�P��yĲ�o�^���z�\��
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_QuickDone(U16 CardNo, U16 NodeID, U16 SlotNo);									//SlaveMotion���O�A�ֳt���m�yĲ�o�^���z�\��
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_Disable(U16 CardNo, U16 NodeID, U16 SlotNo);										//SlaveMotion���O�A�����yĲ�o�^���z�\��
U16 _stdcall _ECAT_Slave_Motion_Get_TouchProbe_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);							//SlaveMotion���O�A���o��e�yĲ�o�^���z�\�઺���A
U16 _stdcall _ECAT_Slave_Motion_Get_TouchProbe_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *LatchPosition);				//SlaveMotion���O�A���o��e�^���쪺��m

//========Motion Salve CSP Command======== Slave(Motion����) CSP�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_CSP_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Dist, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//��b�I���I�B��
U16 _stdcall _ECAT_Slave_CSP_Start_V_Move(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Dir, I32 StrVel, I32 ConstVel, F64 Tacc, U16 SCurve);									//�s�򵥳t�B��
U16 _stdcall _ECAT_Slave_CSP_Start_Arc_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//�꩷�B�ʲĤ@��
U16 _stdcall _ECAT_Slave_CSP_Start_Arc2_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *EndPoint, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//�꩷�B�ʲĤG��
U16 _stdcall _ECAT_Slave_CSP_Start_Arc3_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, I32 *EndPoint, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//�꩷�B�ʲĤT��
U16 _stdcall _ECAT_Slave_CSP_Start_Arc4_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *MidPoint, I32 *EndPoint, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);	//�꩷�B�ʲĥ|��
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 Spiral_Interval, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);//�G�b���۽u�B�ʲĤ@��
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral2_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 *EndPoint, U16 Dir, U16 CycleNum, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);//�G�b���۽u�B�ʲĤG��
U16 _stdcall _ECAT_Slave_CSP_Start_Sphere_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *Target1Point, I32 *Target2Point, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//�T�b�y���B��
U16 _stdcall _ECAT_Slave_CSP_Start_Heli_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, I32 Depth, I32 Pitch, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//���۽u�B��
U16 _stdcall _ECAT_Slave_CSP_Start_Msbrline_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, U16 ArcNodeBit, I32 *Target1Point, I32 *Target2Point, U16 Mode, F64 Parameter, F64 ArcAngle1, F64 ArcAngle2, F64 SpdRatio, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//MSBRLINE
U16 _stdcall _ECAT_Slave_CSP_Start_Mabrline_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *Target1Point, I32 *Target2Point, I32 StrVel, I32 FirstVel, I32 SecondVel, I32 EndVel, F64 Tacc_Step1, F64 Tacc_Step2, U16 Absflag);
U16 _stdcall _ECAT_Slave_CSP_Start_Multiaxes_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *Dist, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//�h�b�I���I�B��
U16 _stdcall _ECAT_Slave_CSP_Start_2Segment_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 SegMode, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, I32 EndVel, F64 Tacc, F64 Tsec, F64 Tdec, U16 SCurve, U16 IsAbs);	//��b��q�I���I�B��
U16 _stdcall _ECAT_Slave_CSP_Start_Helix_Multiaxes_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *CenterPoint, I32 *Dist, I32 Depth, I32 Pitch, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);	//�h�b���u�[Helix�B��
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Helix_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 Spiral_Interval, F64 Angle, I32 Pitch, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);//�T�b���۽u�B�ʲĤ@��
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Helix2_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 *EndPoint, U16 Dir, U16 CycleNum, I32 Pitch, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);//�T�b���۽u�B�ʲĤG��
U16 _stdcall _ECAT_Slave_CSP_Start_Tank_Helix_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *Point1, I32 *Point2, I32 *Point3, I32 *Point4, I32 Depth, I32 Pitch, I32 MaxVel, U16 FilterTime, U16 AMFNum, U16 Abs);//�G�b���¶��B��
U16 _stdcall _ECAT_Slave_CSP_Reference_Pos_Move_Config(U16 CardNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, I32 ReferencePos, I16 Dir);

//========Motion Slave SuperImposed ========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_SuperImposed_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 VelocityDiff, F64 Tacc, F64 Tdec);
U16 _stdcall _ECAT_Slave_CSP_Start_HaltSuperImposed_Move(U16 CardNo, U16 NodeID, U16 SlotID, F64 Tdec);
U16 _stdcall _ECAT_Slave_CSP_Start_Get_Superimposed_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *State);

//========Motion Slave GearIn ========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_GearIn_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 RatioNumerator, U32 RatioDenominator, F64 Acceleration, F64 Deceleration, U16 GearIn_Mode);
//SourceType: 0->�Ҳ� Source, 1->Local Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_GearOut_Move(U16 CardNo, U16 NodeID, U16 SlotID);
U16 _stdcall _ECAT_Slave_CSP_Start_Get_GearIn_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *State);

//========Motion Slave PVT Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 *TargetVel, U16 Abs);	// ��bPVT�B��
U16 _stdcall _ECAT_Slave_CSP_Start_PVTComplete_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 StrVel, I32 EndVel, U16 Abs); // ��bPVTComplete�B��
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Config(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 *TargetVel, U16 Abs);					// ��bPVT�B��
U16 _stdcall _ECAT_Slave_CSP_Start_PVTComplete_Config(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 StrVel, I32 EndVel, U16 Abs);	// ��bPVTComplete�B��
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Sync_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray);

//========Motion Slave ECAM Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Engage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 EngageNodeID, U16 EngageSlotID, U16 SourceNo, I32 Engage_PreLed, I32 Cycle_PreLead, U16 Engage_Mode);
//SourceType: 0->�Ҳ�DI, 1->Local DI, 2->�Ҳ� Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Position Edge, 1->DI+Negative Edge, 2->zero impulse signal+Position Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Compensate_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 CompensateNodeID, U16 CompensateSlotID, U16 SourceNo, I32 TargetPos, I32 Max_Compensate_Ratio, I32 Active_Range_Ratio, U16 CompensateTime, U16 Enable);
//SourceType: 0->�Ҳ�DI, 1->Local DI, 2->�Ҳ� Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Position Edge, 1->DI+Negative Edge, 2->zero impulse signal+Position Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_DisEngage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 DisEngageNodeID, U16 DisEngageSlotID, U16 SourceNo, I32 DisEngage_Position, U16 DI_DisEngage, U16 DisEngage_TurnOff, U16 DisEngage_Mode);
//SourceType: 0->�Ҳ�DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_SingleMove(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Abs);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Disable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Get_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);

U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Table_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 *DataArray, I32 Master_Pulse, F64 Slave_mm_Pulse, F64 Master_mm_Pulse);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Velocity_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 Percent[5], I32 SCurveRegion, I32 TotalLength, I32 Master_Pulse_P, F64 Slave_mm_Pulse, F64 Master_mm_Pulse, U16 Construct_Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Flying_Shears_Data(U16 CardNo, U16 ECAMNo, F64 GearNum_A, F64 GearNum_B, I32 KnifeNum, F64 SlaveDiameter, F64 EncoderDiameter, I32 EncoderPulseRev, I32 SlavePUURev, I32 CutLength, I32 RegionNum, I32 Region[3], I32 Slave_Prelead, I32 Master_Engage_Prelead, U16 PreLeadMode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Intermittence_Print_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 PrintLength, I32 BlankLength, F64 GearNum_A, F64 GearNum_B, I32 SlavePUURev, F64 SlaveDiameter, I32 MasterPulseRev, F64 MasterDiameter, I32 HoldingAreaDeg, I32 SCurveDeg, I32 SynIncreaseDeg);

U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 ECAMNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo);
//SourceType: 0->�Ҳ� Source, 1->Local Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Move_ChangeTable(U16 CardNo, U16 NodeID, U16 SlotID, U16 ECAMNo);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Scale(U16 CardNo, U16 NodeID, U16 SlotID, F64 Percentage);

//========Motion Slave ECAM2 Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_Engage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 EngageNodeID, U16 EngageSlotID, U16 SourceNo, U16 Enable);
//SourceType: 0->�Ҳ�DI, 1->Local DI, 2->�Ҳ� Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Positive Edge, 1->DI+Negative Edge, 2->zero impulse signal+Positive Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_Compensate_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 CompensateNodeID, U16 CompensateSlotID, U16 SourceNo, F64 TargetPos, F64 ActiveRangeRatio, F64 MaxVel, F64 Acceleration, F64 Deceleration, U16 Enable);
//SourceType: 0->�Ҳ�DI, 1->Local DI, 2->�Ҳ� Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Positive Edge, 1->DI+Negative Edge, 2->zero impulse signal+Positive Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_DisEngage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 DisEngageNodeID, U16 DisEngageSlotID, U16 SourceNo, U16 Enable);
//SourceType: 0->�Ҳ�DI, 1->Local DI
//
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_RotaryCut_Initial(U16 CardNo, U16 RotCutNo, F64 RotaryAxisRadius, U16 RotaryAxisKnifeNum, F64 FeedAxisRadius, F64 CutLenth, F64 SyncStartPos, F64 SyncStopPos);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_RotaryCut_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 RotCutNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 RotaryAxis_PulseRev, I32 FeedAxis_PulseRev, I16 RotaryAxis_Dir, I16 FeedAxis_Dir);
//SourceType: 0->�Ҳ� Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_FlyingShear_Initial(U16 CardNo, U16 FlyingShearNo, F64 MasterRadius, F64 SlaveRadius, F64 CutLength, F64 MasterStartPosition, F64 MasterSyncPosition, F64 SlaveSyncPosition, F64 SlaveEndPosition, F64 SlaveWaitPosition, F64 SlaveVelocity, F64 SlaveAcceleration, F64 SlaveDeceleration);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_FlyingShear_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 FlyingShearNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 MasterAxis_PulseRev, I32 SlaveAxis_PulseRev, I16 MasterAxis_Dir, I16 SlaveAxis_Dir);
//SourceType: 0->�Ҳ� Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Disable(U16 CardNo, U16 NodeID, U16 SlotID);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Get_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Phasing(U16 CardNo, U16 NodeID, U16 SlotID, F64 Dist, F64 MaxVel, F64 Acceleration, F64 Deceleration);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_CamSwitch(U16 CardNo, U16 CamNo, U16 SwitchNum, U16 *Percent, U16 Cam_Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_CamSwitch_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);
//
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_Data(U16 CardNo, U16 CamNo, U16 DataNum, F64 *MasterPos_mm, F64 *SlavePos_mm, U16 *Curve_Type, F64 *Velocity_Scale);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Delete_Profile_Data(U16 CardNo, U16 CamNo);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_TableSelect(U16 CardNo, U16 NodeID, U16 SlotID, U16 CamNo, U16 Periodic, U16 MasterAbsolute, U16 SlaveAbsolute);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_CamIn(U16 CardNo, U16 NodeID, U16 SlotID, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, F64 MasterOffset, F64 SlaveOffset, F64 MasterScaling, F64 SlaveScaling, U16 StartMode, I32 MasterAxis_mm_Pulse, I32 SlaveAxis_mm_Pulse, F64 Slave_MaxVel_mm, F64 Slave_Acc_mm, F64 Slave_Dec_mm, I16 MasterAxis_Dir, I16 SlaveAxis_Dir);
//SourceType: 0->�Ҳ� Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_CamOut(U16 CardNo, U16 NodeID, U16 SlotID);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_Modify(U16 CardNo, U16 CamNo, U16 PointNo, F64 *Parameters);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_CamSet(U16 CardNo, U16 NodeID, U16 SlotID);

//========Motion Slave TableMotion Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_CycleMode_Data(U16 CardNo, U16 TableNo, I32 *PositionData, I32 DataSize, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 MaxVel, U16 FilterTime, U16 AMFNum, U16 CycleNum, I32 *IOControl);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_CycleMode_Move(U16 CardNo, U16 TableNo);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_BufferMode_Move(U16 CardNo, U16 TableNo, I32 *PositionData, I32 DataSize, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 MaxVel, U16 FilterTime, U16 AMFNum, I32 *IOControl);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Get_Length(U16 CardNo, U16 TableNo, I32 *cnt);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Get_CycleNum(U16 CardNo, U16 TableNo, I32 *cycle);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Feedrate_Overwrite(U16 CardNo, U16 TableNo, I32 ratio, F64 sec);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Feedhold(U16 CardNo, U16 TableNo, U16 On_Off, F64 sec);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Get_VectorSpeed(U16 CardNo, U16 TableNo, F64 *vectorspeed);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_Set_Blending_Ratio(U16 CardNo, U16 TableNo, U32 Ratio);

U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_ProfileMode_Parameter(U16 CardNo, U16 TableNo, I32 NanoSmoothDecectionLength, I32 RefTurnOnSpd, U16 CurveDecectionFlag, I32 CurveDecectionLength, F64 CurveDecectionAngle, I32 ArcRefSpeed, I32 ArcRefRadius);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_ProfileMode_Data(U16 CardNo, U16 TableNo, I32 *PositionData, I32 DataSize, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *MaxVel, I32 *AccDec, F64 InitialVel_Ratio, I32 *IOControl);  // 2016-11-02
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_ProfileMode_Data_Flying_Photography(U16 CardNo, U16 TableNo, I32 *PositionData, I32 DataSize, U16 *AxisArray, U16 *SlotArray, I32 *MaxVel, I32 *AccDecLimit, I32 Remain_Dist, I32 Stage2_Velocity, F64 InitialVel_Ratio, I32 *IOControl);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_ProfileMode_Move(U16 CardNo, U16 TableNo);
U16 _stdcall _ECAT_Slave_CSP_Start_TableMotion_IOControl_Mapping(U16 CardNo, U16 TableNo, U16 IOControlNum, U16 NodeID, U16 SlotID, U16 BitNo);

//========Motion Slave MotionBuffer Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_Crd_Parameters(U16 CardNo, U16 TableNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 SycMaxVel, I32 SycMaxAcc, U16 S_Curve_Time, U16 Max_IO_Advance_Time, U16 SetOriginFlag, I32 *OriginPos);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Crd_Parameters(U16 CardNo, U16 TableNo, U16 *AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *SycMaxVel, I32 *SycMaxAcc, U16 *S_Curve_Time, U16 *Max_IO_Advance_Time, U16 *SetOriginFlag, I32 *OriginPos);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Line_MultiAxis(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Line_MultiAxis_G00(U16 CardNo, U16 TableNo, I32 *TargetPosition, I32 SynTargetVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Arc_Radius(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *TargetPosition, I32 Radius, U16 CircleDir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Arc_CenterPos(U16 CardNo, U16 TableNo, U16 *Arc_Axis, I32 *TargetPosition, I32 *CenterPos, U16 CircleDir, I32 SynTargetVel, I32 SynEndVel, I32 SynAcc, U16 AbsMode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_IOControl(U16 CardNo, U16 TableNo, U16 IO_Control_Num, MOTION_BUFFER_IO_Set* IO_Array, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Advanced_IOControl(U16 CardNo, U16 TableNo, U16 IO_Control_Num, MOTION_BUFFER_IO_Set* IO_Array, U16 Time, U16 Mode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_SoftLimit_On(U16 CardNo, U16 TableNo, U16 AxisNo, I16 LimitType, U16 Mode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_SoftLimit_Off(U16 CardNo, U16 TableNo, U16 AxisNo, I16 LimitType, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Delay(U16 CardNo, U16 TableNo, F64 DelayTime, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Single_Step(U16 CardNo, U16 TableNo, U16 FifoNo, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Remain_Buffer_Size(U16 CardNo, U16 TableNo, I32 *RemainBufSize, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Clear_Buffer(U16 CardNo, U16 TableNo, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Start(U16 CardNo, U16 TableNo, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Stop(U16 CardNo, U16 TableNo, U16 FifoNo, U16 Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Feedrate_Override(U16 CardNo, U16 TableNo, F64 SynVelRatio);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Motion_Status(U16 CardNo, U16 TableNo, U16 *Status, I32 *BlockNum, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_UserSegNum(U16 CardNo, U16 TableNo, I32 SegNum, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_UserSegNum(U16 CardNo, U16 TableNo, I32 *SegNum, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_Stop_Deceleration(U16 CardNo, U16 TableNo, I32 DecSmoothStop, I32 DecAbruptStop);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Stop_Deceleration(U16 CardNo, U16 TableNo, I32 *DecSmoothStop, I32 *DecAbruptStop);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Position(U16 CardNo, U16 TableNo, I32 *Now_Position);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Get_Velocity(U16 CardNo, U16 TableNo, I32 *CurrentSpeed);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_BufGear(U16 CardNo, U16 TableNo, U16 AxisNo, U16 SlotNo, I32 Distance, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_BufMove(U16 CardNo, U16 TableNo, U16 AxisNo, U16 SlotNo, I32 Distance, I32 TargetVel, I32 Acceleration, U16 AbsMode, U16 BufMove_Mode, U16 FifoNo);
U16 _stdcall _ECAT_Slave_CSP_Start_MotionBuffer_Set_LookAhead_Parameters(U16 CardNo, U16 TableNo, I32 RefSwerveSpd, U16 ArcSpdModify, I32 ArcRefSpeed, I32 ArcRefRadius, U16 FifoNo);

//========Motion Slave TouchProb Home Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Start_TouchProb_Home_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 TriggerSource, U16 TriggerEdge, U16 Direction, I32 Offset, I32 StrVel, I32 FirstVel, I32 SecondVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve);	//TriggerSource 0:DI, 1:zero impulse signal, TriggerEdge:0:Position Edge, 1:Negative Edge, HomeMode:0:Position Direction, 1:Negative Direction
U16 _stdcall _ECAT_Slave_CSP_Start_TouchProb_Home_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);	//0:Done, 1:Busy, 99:Error

//========Motion Slave CSV Command====== Slave(Motion����) CSV�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_CSV_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Target_Velocity, F64 Acceleration, U16 Curve_Mode, U16 Acc_Type);
U16 _stdcall _ECAT_Slave_CSV_Multi_Start_Move(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo, I32 *Target_Velocity, F64 *Acceleration, U16 Curve_Mode, U16 Acc_Type);

//========Motion Slave CSV Command====== Slave(Motion����) CSV�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_CST_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I16 Target_Torque, U32 Slope, U16 Curve_Mode);
U16 _stdcall _ECAT_Slave_CST_Multi_Start_Move(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo, I16 *Target_Torque, U32 *Slope, U16 Curve_Mode);

//========Motion Slave CSP Set========= Slave(Motion����) CSP�Ҧ��]�w��
U16 _stdcall _ECAT_Slave_CSP_Set_Gear(U16 CardNo, U16 NodeID, U16 SlotNo, F64 Numerator, F64 Denominator, I16 Enable);	//�]�w��eMotionSlave���n��q�l����
U16 _stdcall _ECAT_Slave_CSP_Set_Softlimit(U16 CardNo, U16 NodeID, U16 SlotNo, I32 PosiLimit, I32 NegaLimit, U16 Mode);	//�]�w��eMotionSlave���n�鷥��
U16 _stdcall _ECAT_Slave_CSP_TargetPos_Change(U16 CardNo, U16 NodeID, U16 SlotNo, I32 NewPos);							//P change
U16 _stdcall _ECAT_Slave_CSP_Velocity_Change(U16 CardNo, U16 NodeID, U16 SlotNo, I32 NewSpeed, F64 Tsec);				//V Change
U16 _stdcall _ECAT_Slave_CSP_TargetPos_Velocity_Change(U16 CardNo, U16 NodeID, U16 SlotID, I32 NewPos, I32 NewSpeed, F64 Tsec);		//P&V Change
U16 _stdcall _ECAT_Slave_CSP_Feedrate_Overwrite(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode, I32 NewSpeed, F64 Tsec);	//Feedrate Overwrite
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);						//�P��Speed Continue���\��
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Set_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);						//�]�wSpeed Continue��Mode
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Set_Combine_Ratio(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Ratio);			//�]�wSpeed Continue���X����v
U16 _stdcall _ECAT_Slave_CSP_Scurve_Rate(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Scurve_Rate);							//�]�wSCurve����Tcurve�����
U16 _stdcall _ECAT_Slave_CSP_Linear_Speed_Master(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);							//�]�w�t�׳]�w������ 0:�V�q�t�� 1:���q���̤j�t��
U16 _stdcall _ECAT_Slave_CSP_Mask_Axis(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotNoArray);
U16 _stdcall _ECAT_Slave_CSP_Sync_Config(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Sync_Move(U16 CardNo);
U16 _stdcall _ECAT_Slave_CSP_Virtual_Set_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Virtual_Set_Command(U16 CardNo, U16 NodeID, U16 SlotID, I32 Command);

//========Motion Slave AMF Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Set_SingleAxis_NormalAMF_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 FilterTime, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Set_NormalAMF_Enable(U16 CardNo, U16 FilterNum, U16 Enable);

//========Motion Slave DI Function Set========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Set_DITrigger_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 Polarity, U16 FilterTime);	//Polarity: 0->Low_High_Low, 1->High_Low_High
U16 _stdcall _ECAT_Slave_CSP_Get_DITrigger_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *TriggerStatus, U32 *TriggerCount);
U16 _stdcall _ECAT_Slave_CSP_Set_SLD_Enable(U16 CardNo, U16 NodeID, U16 SlotID, F64 Tdec, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->�Ҳ�DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Set_TrSeg2_Enable(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Scurve, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->�Ҳ�DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Set_Velocity_Change_Enable(U16 CardNo, U16 NodeID, U16 SlotID, I32 NewSpeed, F64 Tsec, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->�Ҳ�DI, 1->Local DI

//========Motion Slave CSP Get========= Slave(Motion����) CSP�Ҧ����o��
U16 _stdcall _ECAT_Slave_CSP_Get_SoftLimit_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status); //Bit 0:M_Status, 1:P_status

//========Motion Slave CSP TargetReach========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Set_SoftTargetReach(U16 CardNo, U16 NodeID, U16 SlotID, U16 Window_Time, U32 Position_Window, U16 Enable); //Window_Time:ms, Position_Window:pulse
U16 _stdcall _ECAT_Slave_CSP_Get_SoftTargetReach_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status); //0: Off, 1:On

//========Motion Slave CSP Pitch========= Slave(Motion����) CSP�Ҧ����o��
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_InterVal(U16 CardNo, U16 NodeID, U16 SlotID, U32 InterVal);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Mode(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);	//0: ���V, 1: ��V
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Org(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 OrgPos);	//0: ���V, 1: �t�V
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Rel_Table(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 *Table, U16 Num);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Abs_Table(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 *Table, U16 Num);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);

//========Motion Slave CSP Backlash========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Backlash_Set_Info(U16 CardNo, U16 NodeID, U16 SlotID, I16 Backlash, U16 AccStep, U16 ConstStep, U16 DecStep);
U16 _stdcall _ECAT_Slave_CSP_Backlash_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);

//========Motion Slave CSP Gantry========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Follow_Enable(U16 CardNo, U16 GantryNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, U16 Enable);  // 2017-01-09
U16 _stdcall _ECAT_Slave_CSP_Gantry_Enable(U16 CardNo, U16 GantryNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, I32 Motor_Pulse_Per_Turn, F64 Motor_MaxTorque, F64 K_I, F64 K_VI, F64 Filter_Frequency, U16 Enable);
//Motor_MaxTorque = Motor_RotorInertia(���F��l�D�q) / Motor_RatedTorque(���F�B�w��x)

//========Motion Slave CSP Velocity Offset Gantry========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Velocity_Gantry_Info(U16 CardNo, U16 GantryNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, I32 Velcoity_Offset_Normalize, I32 Pulse_Normalize, I32 Podition_Threshold, F64 PID_Kp, F64 PID_Ki, F64 PID_Kd);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Gantry_LPF_Info(U16 CardNo, U16 GantryNo, U16 LPF_Mode, F64 LPF_Time);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Gantry_Forward_Info(U16 CardNo, U16 GantryNo, U16 Forward_Mode, U16 Forward_Time, F64 Forward_Kp);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Gantry_PIDAdv_Info(U16 CardNo, U16 GantryNo, F64 PID_Output_Max, F64 PID_Output_Min, F64 PID_Ki_Max, F64 PID_Ki_Min);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Gantry_Enable(U16 CardNo, U16 GantryNo, U16 Enable);

U16 _stdcall _ECAT_Slave_CSP_Gantry_Enable_PositionError(U16 CardNo, U16 GantryNo, U16 PositionErrorMode, I32 PositionError, U16 PassingCount, F64 Tdec, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Get_PositionError(U16 CardNo, U16 GantryNo, I32 *PositionError);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Get_Status(U16 CardNo, U16 GantryNo, U16 *Status, U16 *PassingLevel);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Set_Position(U16 CardNo, U16 GantryNo, I32 NewPosition);  // 2016-11-28
U16 _stdcall _ECAT_Slave_CSP_Gantry_Ralm(U16 CardNo, U16 GantryNo, I32 Velocity, F64 Tacc, F64 Tdec);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Ralm_Status(U16 CardNo, U16 GantryNo, U16 *Status);

U16 _stdcall _ECAT_Slave_CSP_Gantry_Set_Home_Config(U16 CardNo, U16 GantryNo, U16 Mode, I32 Offset, U32 FirstVel, U32 SecondVel, F64 Tacc, U16 Dir, I32 Shift);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Home_Move(U16 CardNo, U16 GantryNo);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Disable_Home_Move(U16 CardNo, U16 GantryNo);
U16 _stdcall _ECAT_Slave_CSP_Gantry_Home_Status(U16 CardNo, U16 GantryNo, U16* Status);

//========Motion Slave CSP Velocity Compensate========= Slave(Motion����) CSP�Ҧ���
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Info(U16 CardNo, U16 NodeID, U16 SlotID, I32 Velcoity_Offset_Normalize, I32 Pulse_Normalize, I32 Podition_Threshold, F64 PID_Kp, F64 PID_Ki, F64 PID_Kd);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_LPF_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 LPF_Mode, F64 LPF_Time);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Forward_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 Forward_Mode, U16 Forward_Time, F64 Forward_Kp);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_PIDAdv_Info(U16 CardNo, U16 NodeID, U16 SlotID, F64 PID_Output_Max, F64 PID_Output_Min, F64 PID_Ki_Max, F64 PID_Ki_Min);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);

//========Motion Slave Home =========== Slave(Motion����) Home�Ҧ��q��
U16 _stdcall _ECAT_Slave_Home_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode, I32 Offset, U32 FirstVel, U32 SecondVel, U32 Acceleration);	//�M��B�ʳ]�w
U16 _stdcall _ECAT_Slave_Home_Move(U16 CardNo, U16 NodeID, U16 SlotNo);																			//�M��B��
U16 _stdcall _ECAT_Slave_Home_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);																		//�M��B�ʪ��A

//========User Motion Control=========== Slave(Motion����) Motion User Define
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Type(U16 CardNo, U16 GroupNo, U16 AxisNum, U16 *AxisNo, U16 *SlotNo, U16 MotionType);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Enable_Mode(U16 CardNo, U16 GroupNo, U16 Enable);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_Enable_Mode(U16 CardNo, U16 GroupNo, U16 *Enable);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Data(U16 CardNo, U16 GroupNo, I32 *CmdPulse);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_DataCnt(U16 CardNo, U16 GroupNo, U16 *Counter);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Clear_Data(U16 CardNo, U16 GroupNo);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Ralm(U16 CardNo, U16 GroupNo);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Svon(U16 CardNo, U16 GroupNo, U16 ON_OFF);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_Alm(U16 CardNo, U16 GroupNo, U16 *Alm);

//========Normal Slave - Record Data========== Slave(������)�q�� - �^����ƨt�C
U16 _stdcall _ECAT_Slave_Record_Set_Type(U16 CardNo, U16 NodeID, U16 SlotNo, U16 MonitorIndex, U16 IOType, U16 OD_Index, U16 OD_SubIndex);
U16 _stdcall _ECAT_Slave_Record_Set_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_Record_Get_Data_Cnt(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Cnt);
U16 _stdcall _ECAT_Slave_Record_Read_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U32 *Data);
U16 _stdcall _ECAT_Slave_Record_Clear_Data(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_Record_Multi_Set_Enable(U16 CardNo, U16 NodeNum, U16 *NodeIDArray, U16 *SlotNoArray, U16 Enable);
U16 _stdcall _ECAT_Slave_Record_Multi_Clear_Data(U16 CardNo, U16 NodeNum, U16 *NodeIDArray, U16 *SlotNoArray);

//======MR_J4_ABS=======
U16 _stdcall _ECAT_Slave_MR_J4_ABS_Set_Mode(U16 CardNo, U16 GroupNo, U16 AxisNum, U16 DI_NodeID, U16 DI_SlotID, U16 DO_NodeID, U16 DO_SlotID);
U16 _stdcall _ECAT_Slave_MR_J4_ABS_Set_Enable(U16 CardNo, U16 GroupNo, U16 Enable);
U16 _stdcall _ECAT_Slave_MR_J4_ABS_Get_State(U16 CardNo, U16 GroupNo, U16 *State);
U16 _stdcall _ECAT_Slave_MR_J4_ABS_Get_Data(U16 CardNo, U16 GroupNo, U16 AxisIndex, I32 *Data);
U16 _stdcall _ECAT_Slave_MR_J4_ABS_Reset(U16 CardNo, U16 GroupNo, U16 AxisIndex);

//========Motion Slave PP Command========= Slave(Motion����) PP�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_PP_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetPos, U32 ConstVel, U32 Acceleration, U32 Deceleration, U16 Abs_Rel);
U16 _stdcall _ECAT_Slave_PP_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U32 End_Vel, I32 Min_Range_Limit, I32 Max_Range_Limit, I32 Min_Soft_Limit, I32 Max_Soft_Limit);

//========Motion Slave PV Command=== Slave(Motion����)	 Velocity�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_PV_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetVel, U32 Acceleration, U32 Deceleration);
U16 _stdcall _ECAT_Slave_PV_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U16 Max_Torque, U16 Velocity_Window, U16 Velocity_Window_Time, U16 Velocity_Threshold, U16 Velocity_Threshold_Time);

//========Motion Slave VL Command=== Slave(Motion����)	 Velocity�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_VL_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetVel, U32 Acceleration, U32 Deceleration);

//========Motion Slave PT Command===== Slave(Motion����) Torque�Ҧ��B�ʫ��O
U16 _stdcall _ECAT_Slave_PT_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I16 Target_Torque, U32 Slope);
U16 _stdcall _ECAT_Slave_PT_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U16 Max_Current, I16 Torque_Profile);

//========IO Slave===============	Slave(IO����) �q��
U16 _stdcall _ECAT_Slave_DIO_Get_Input_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *value);	//Ū����eIOSlave(MN��)���T����J
U16 _stdcall _ECAT_Slave_DIO_Get_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *value);	//Ū����eIOSlave(NT��)���T����X
U16 _stdcall _ECAT_Slave_DIO_Set_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 value);	//�]�w��eIOSlave(NT��)���T����X
U16 _stdcall _ECAT_Slave_DIO_Get_Single_Input_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 *value);	//Ū����eIOSlave(MN��)���T�����I��J
U16 _stdcall _ECAT_Slave_DIO_Get_Single_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 *value);	//Ū����eIOSlave(NT��)���T�����I��X
U16 _stdcall _ECAT_Slave_DIO_Set_Single_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 value);	//�]�w��eIOSlave(NT��)���T�����I��X
U16 _stdcall _ECAT_Slave_DIO_Set_Output_Error_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitMode);
U16 _stdcall _ECAT_Slave_DIO_Set_Output_Error_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitMode);

//=======AIO Slave===============
U16 _stdcall _ECAT_Slave_AIO_Get_Input_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Value);
U16 _stdcall _ECAT_Slave_AIO_Set_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Value);
U16 _stdcall _ECAT_Slave_AIO_Get_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Value);

//======ECAT Module R1-EC5604========
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Counter_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC5604_Get_Counter_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U32 *Value);
U16 _stdcall _ECAT_Slave_R1_EC5604_Reset_Counter_Value(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_R1_EC5604_Get_Overflow_Times(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Times);
U16 _stdcall _ECAT_Slave_R1_EC5604_Get_Underflow_Times(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Times);
U16 _stdcall _ECAT_Slave_R1_EC5604_Reset_Overflow_Times(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Output_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Output_Pulse_Width(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Width);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Force_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Value);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Method0_To_2_Compare_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U32 Value);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Method3_Compare_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U32 FirstValue, U32 SecondValue, U32 ReloadValue);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_PWM_Frequency(U16 CardNo, U16 NodeID, U16 SlotNo, U32 Frequency);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_PWM_Duty_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Duty);
U16 _stdcall _ECAT_Slave_R1_EC5604_Set_Output_Error_Handle_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);

//======ECAT Module R1-EC5614========
U16 _stdcall _ECAT_Slave_R1_EC5614_Set_MJ_Config(U16 CardNo, U16 MJNo, U16 MJType, U16 NodeID, U16 SlotNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *MaxSpeed, F64 *TAcc, F64 *Ratio);
U16 _stdcall _ECAT_Slave_R1_EC5614_Set_MJ_Enable(U16 CardNo, U16 MJNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5614_Get_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);
U16 _stdcall _ECAT_Slave_R1_EC5614_Get_MPG_Counter(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Counter);
U16 _stdcall _ECAT_Slave_R1_EC5614_Set_Mpg_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);

//======ECAT Module R1-EC5621========
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_Output_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_Input_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_ORG_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_QZ_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_Home_SpMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_MEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_PEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_Svon_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_Home_Slow_Down(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable, U16 SlowDoneTime, U16 WaitTime);
U16 _stdcall _ECAT_Slave_R1_EC5621_Get_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *IOStatus);
U16 _stdcall _ECAT_Slave_R1_EC5621_Get_Single_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNo, U16 *IOStatus);
U16 _stdcall _ECAT_Slave_R1_EC5621_Set_ALM_Clean_Time(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Ms);  // 2016-03-02

//======ECAT Module R1-EC0624========
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Latch_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Latch_Source(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Source);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Latch_Trigger_Edge(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Edge);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Latch_External_IO(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Select);
U16 _stdcall _ECAT_Slave_R1_EC0624_Get_Latch_Latest_Value(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Value);
U16 _stdcall _ECAT_Slave_R1_EC0624_Get_Latch_FIFO_Counter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Count);
U16 _stdcall _ECAT_Slave_R1_EC0624_Get_Latch_FIFO_Value(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Value);
U16 _stdcall _ECAT_Slave_R1_EC0624_Get_Latch_FIFO_Source(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Source);
U16 _stdcall _ECAT_Slave_R1_EC0624_Reset_Latch_FIFO(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_Output_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_GPIO_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_IO_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Inverse);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_Interval_Setting(U16 CardNo, U16 NodeID, U16 SlotNo, I32 StartPos, U16 Dir, U32 Interval, U32 TriggetCount);
U16 _stdcall _ECAT_Slave_R1_EC0624_Reset_Compare_Trigger_Counter(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_One_Shot(U16 CardNo, U16 NodeID, U16 SlotNo);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Trigger_Time(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Value);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_Source(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Source);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Compare_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Table_Compare_Level_Setting(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Level);
U16 _stdcall _ECAT_Slave_R1_EC0624_Set_Table_Compare_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 DataNum, I32 *TableData);
U16 _stdcall _ECAT_Slave_R1_EC0624_Get_Table_Compare_FIFO_Counter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Count);
U16 _stdcall _ECAT_Slave_R1_EC0624_Reset_Table_Compare_Counter(U16 CardNo, U16 NodeID, U16 SlotNo);

//======ECAT Module R1-ECx62x========
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_Output_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_Input_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_ORG_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_QZ_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_Home_SpMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_MEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_PEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_Svon_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_Home_Slow_Down(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable, U16 SlowDoneTime, U16 WaitTime);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Get_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *IOStatus);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Get_Single_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNo, U16 *IOStatus);
U16 _stdcall _ECAT_Slave_R1_ECx62x_Set_ALM_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);  // 2016-03-02

//======ECAT Module R1-EC70E2========
U16 _stdcall _ECAT_Slave_R1_EC70E2_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Eanble);

//======ECAT Module R1-EC70X2========
U16 _stdcall _ECAT_Slave_R1_EC70X2_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Eanble);

//======ECAT Module R1-EC8124========
U16 _stdcall _ECAT_Slave_R1_EC8124_Set_Input_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC8124_Set_Input_ConvstFreq_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_R1_EC8124_Set_Input_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC8124_Get_Input_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Mode);
U16 _stdcall _ECAT_Slave_R1_EC8124_Set_Input_AverageMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Avg_Times);
U16 _stdcall _ECAT_Slave_R1_EC8124_Get_Input_Value(U16 CardNo, U16 NodeID, U16 SlotID, U16 AIType, F64 *Value);	//AIType:0->�^�ǹq����(V), 1->�^�ǹq�y��(mA)

//======ECAT Module R1-EC9144========
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 RangeMode);
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC9144_Get_Output_ReturnCode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ReturnCode);
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_Value(U16 CardNo, U16 NodeID, U16 SlotID, F64 Value);
U16 _stdcall _ECAT_Slave_R1_EC9144_Get_Output_Value(U16 CardNo, U16 NodeID, U16 SlotID, F64 *Value);

//======Delta Servo========
U16 _stdcall _ECAT_Slave_DeltaServo_Write_Parameter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, I32 WriteData);											// �g�J�x�F�Ѽ�
U16 _stdcall _ECAT_Slave_DeltaServo_Read_Parameter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, I32 *ReadData);												// Ū���x�F�Ѽ�
U16 _stdcall _ECAT_Slave_DeltaServo_Read_Parameter_Info(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, U16 *ParaType, U16 *DataSize, U16 *DataType);			// Ū���x�F�ѼƸ�T
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Velocity_Limit(U16 CardNo, U16 NodeID, U16 SlotNo, U32 LimitValue);																// �]�w�x�F�X�ʾ��t�׭���
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Compare_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable, U16 CompareSource, U16 SignalLength, U16 SignalPolarity);		// �]�w�ñҥΥx�FCompare Trigger�\��
U16 _stdcall _ECAT_Slave_DeltaServo_Get_Compare_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Enable, U16 *CompareSource, U16 *SignalLength, U16 *SignalPolarity);	// Ū���x�FCompare Trigger�]�w���A
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Compare_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 CompareNum, I32 *ComparePos);											// �]�w�x�FCompare Trigger��m�ƶq�ήy��

//======Security========//0:ok, 1:fail, 2:busy, 3:no-check, 4:security timeout
U16 _stdcall _ECAT_Security_Check_Verifykey(U16 CardNo, U32 *VerifyKey);
U16 _stdcall _ECAT_Security_Get_Check_Verifykey_State(U16 CardNo, U16 *State);
U16 _stdcall _ECAT_Security_Write_Verifykey(U16 CardNo, U32 *VerifyKey);
U16 _stdcall _ECAT_Security_Get_Write_Verifykey_State(U16 CardNo, U16 *State);
U16 _stdcall _ECAT_Security_Check_UserPassword(U16 CardNo, U32 *UserPassword);
U16 _stdcall _ECAT_Security_Get_Check_UserPassword_State(U16 CardNo, U16 *State);
U16 _stdcall _ECAT_Security_Write_UserPassword(U16 CardNo, U32 *UserPassword);
U16 _stdcall _ECAT_Security_Get_Write_UserPassword_State(U16 CardNo, U16 *State);

//======MRAM======= Index:0~0x10000 Range:ByteNum
U16 _stdcall _ECAT_Master_MRAM_Write_Word_Data(U16 CardNo, U32 Index, U32 DataNum, U16 *Data);						// �NU16��Ƽg�JPAC��MRam���w��}
U16 _stdcall _ECAT_Master_MRAM_Read_Word_Data(U16 CardNo, U32 Index, U32 DataNum, U16 *Data);							// Ū�XPAC��MRam���w��}U16���
U16 _stdcall _ECAT_Master_MRAM_Write_DWord_Data(U16 CardNo, U32 Index, U32 DataNum, U32 *Data);						// �NU32��Ƽg�JPAC��MRam���w��}
U16 _stdcall _ECAT_Master_MRAM_Read_DWord_Data(U16 CardNo, U32 Index, U32 DataNum, U32 *Data);						// Ū�XPAC��MRam���w��}U32���

//======�b�dGPIO========
U16 _stdcall _ECAT_GPIO_Set_Output(U16 CardNo, U16 OnOff);
U16 _stdcall _ECAT_GPIO_Get_Output(U16 CardNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Get_Input(U16 CardNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Set_Digital_Filter(U16 CardNo, U16 Filter);
U16 _stdcall _ECAT_GPIO_Get_Digital_Filter(U16 CardNo, U16 *Filter);
U16 _stdcall _ECAT_GPIO_Set_Single_Output(U16 CardNo, U16 BitNo, U16 OnOff);
U16 _stdcall _ECAT_GPIO_Get_Single_Output(U16 CardNo, U16 BitNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Get_Single_Input(U16 CardNo, U16 BitNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Set_Output_Control_Mode(U16 CardNo, U16 Mode);  // 2016-06-02

//======�b�dCompare========
U16 _stdcall _ECAT_Compare_Set_Channel_Position(U16 CardNo, U16 CompareChannel, I32 Position);
U16 _stdcall _ECAT_Compare_Get_Channel_Position(U16 CardNo, U16 CompareChannel, I32 *Position);
U16 _stdcall _ECAT_Compare_Set_Ipulser_Mode(U16 CardNo, U16 Mode);	//0:AB phase, 1:CW/CCW
U16 _stdcall _ECAT_Compare_Set_Channel_Direction(U16 CardNo, U16 CompareChannel, U16 Dir);	//0:Normal, 1:Inverse
U16 _stdcall _ECAT_Compare_Set_Channel_Trigger_Time(U16 CardNo, U16 CompareChannel, U32 TimeUs);
U16 _stdcall _ECAT_Compare_Set_Channel_Trigger_Time_Multiple(U16 CardNo, U16 CompareChannel, U16 Multiple);  // 2016-03-29
U16 _stdcall _ECAT_Compare_Set_Channel_One_Shot(U16 CardNo, U16 CompareChannel);
U16 _stdcall _ECAT_Compare_Set_Channel_Source(U16 CardNo, U16 CompareChannel, U16 Source);
U16 _stdcall _ECAT_Compare_Set_Channel_Enable(U16 CardNo, U16 CompareChannel, U16 Enable);
//Dir 1: Negativeu, 0:Positive 
//TriggerCount 0:infinity trigger
U16 _stdcall _ECAT_Compare_Channel0_Position(U16 CardNo, I32 Start, U16 Dir, U16 Interval, U32 TriggerCount);
U16 _stdcall _ECAT_Compare_Set_Channel0_Trigger_By_GPIO(U16 CardNo, U16 Dir, U16 Interval, I32 TriggerCount);
U16 _stdcall _ECAT_Compare_Set_Channel1_Output_Enable(U16 CardNo, U16 OnOff);	//0: Off, 1:On
U16 _stdcall _ECAT_Compare_Set_Channel1_Output_Mode(U16 CardNo, U16 Mode);
U16 _stdcall _ECAT_Compare_Get_Channel1_IO_Status(U16 CardNo, U16 *IOStatus);
U16 _stdcall _ECAT_Compare_Set_Channel1_GPIO_Out(U16 CardNo, U16 OnOff);
U16 _stdcall _ECAT_Compare_Set_Channel1_Position_Table(U16 CardNo, I32 *PosTable, U32 TableSize);
U16 _stdcall _ECAT_Compare_Set_Channel1_Position_Table_Level(U16 CardNo, I32 *PosTable, U32 *LevelTable, U32 TableSize);
U16 _stdcall _ECAT_Compare_Get_Channel1_Position_Table_Count(U16 CardNo, U32 *pCount);
U16 _stdcall _ECAT_Compare_Set_Channel_Polarity(U16 CardNo, U16 Inverse);	//0:Normal, 1:Inverse
U16 _stdcall _ECAT_Compare_Reuse_Channel1_Position_Table(U16 CardNo);
U16 _stdcall _ECAT_Compare_Reuse_Channel1_Position_Table_Level(U16 CardNo);
// +2017-01-09
U16 _stdcall _ECAT_Compare_Channel0_Position_32Bit(U16 CardNo, I32 Start, U16 Dir, U32 Interval, U32 TriggerCount);
U16 _stdcall _ECAT_Compare_Set_Channel0_Trigger_By_GPIO_32Bit(U16 CardNo, U16 Dir, U32 Interval, I32 TriggerCount);
U16 _stdcall _ECAT_Compare_Set_Channel_Position_Table(U16 CardNo, U16 CompareChannel, I32 *PosTable, U32 TableSize);
U16 _stdcall _ECAT_Compare_Set_Channel_Position_Table_Level(U16 CardNo, U16 CompareChannel, I32 *PosTable, U32 *LevelTable, U32 TableSize);
U16 _stdcall _ECAT_Compare_Get_Channel_Position_Table_Count(U16 CardNo, U16 CompareChannel, U32 *Count);
U16 _stdcall _ECAT_Compare_Reuse_Channel_Position_Table(U16 CardNo, U16 CompareChannel);
U16 _stdcall _ECAT_Compare_Reuse_Channel_Position_Table_Level(U16 CardNo, U16 CompareChannel);
// -2017-01-09

// +2017-08-08
U16 _stdcall _ECAT_Comapre_2D_Set_Range(U16 CardNo, U16 CompareChannel, I32 Range);
U16 _stdcall _ECAT_Compare_2D_Set_Table(U16 CardNo, U16 Group, I32 *PosX, I32 *PosY, U32 TableSize);
U16 _stdcall _ECAT_Compare_2D_Set_Table_Level(U16 CardNo, U16 Group, I32 *PosX, I32 *PosY, U32 *LevelTable, U32 TableSize);

U16 _stdcall _ECAT_PWM_Set_Frequency(U16 CardNo, U32 Freq);
U16 _stdcall _ECAT_PWM_Set_Duty(U16 CardNo, U32 Duty);
U16 _stdcall _ECAT_PWM_Set_Control_Mode(U16 CardNo, U16 Mode);  // 0: Normal IO, 1: Compare PWM, 2: Software PWM
U16 _stdcall _ECAT_PWM_Soft_Enable(U16 CardNo, U16 OnOff);
// -2017-08-08


//======�b�dCE========
U16 _stdcall _ECAT_Card_CE_Operate_Enable(U16 CardNo, U16 Enable);
U16 _stdcall _ECAT_Card_CE_Write_PC_Data(U16 CardNo, U16 Index, U32 Data);
U16 _stdcall _ECAT_Card_CE_Read_PC_Data(U16 CardNo, U16 Index, U32 *Data);
U16 _stdcall _ECAT_Card_CE_Write_Device_Data(U16 CardNo, U16 Index, U32 Data);
U16 _stdcall _ECAT_Card_CE_Read_Device_Data(U16 CardNo, U16 Index, U32 *Data);
U16 _stdcall _ECAT_Card_CE_Write_PC_Struct(U16 CardNo, U32 *AddrOfStruct, U32 Size);
U16 _stdcall _ECAT_Card_CE_Read_PC_Struct(U16 CardNo, U32 *AddrOfStruct, U32 Size);
U16 _stdcall _ECAT_Card_CE_Write_Device_Struct(U16 CardNo, U32 *AddrOfStruct, U32 Size);
U16 _stdcall _ECAT_Card_CE_Read_Device_Struct(U16 CardNo, U32 *AddrOfStruct, U32 Size);
U16 _stdcall _ECAT_Card_Get_OS_Type(U16 CardNo, char pu8_Data[4]);  // 2016-08-03
U16 _stdcall _ECAT_Card_Get_Mac_Address(U16 CardNo, U16 Index, U8 MacAddr[6]);  // 2016-11-18


//======RTX========
U16 _stdcall _ECAT_Master_RTX_Open_Rtss(U16 CardNo, char *FilePath, U16 *Flag);
U16 _stdcall _ECAT_Master_RTX_Create_Shared_Memory(U16 CardNo, U32 MaxSize, char *SpaceName, void **location, HANDLE *Sharedmemory_Handle);
U16 _stdcall _ECAT_Master_RTX_Open_Shared_Memory(U16 CardNo, char *SpaceName, void **location, HANDLE *Sharedmemory_Handle);
U16 _stdcall _ECAT_Master_RTX_Create_Event(U16 CardNo, U16 ManualReset, U16 InitialState, char *EventName, HANDLE *Event_Handle);
U16 _stdcall _ECAT_Master_RTX_Open_Event(U16 CardNo, char *EventName, HANDLE *Event_Handle);
U16 _stdcall _ECAT_Master_RTX_Set_Event(U16 CardNo, HANDLE Event_Handle);
U16 _stdcall _ECAT_Master_RTX_Close_Handle(U16 CardNo, HANDLE A_Handle);

//======Errorlog========
U16 _stdcall _ECAT_Master_Errorlog_API_Set_Enable(U16 CardNo, U16 Enable, U16 Mode, U16 Level);											//Mode=>0:�榸 1:�`�� ,Level=>0:ALL 1:Set 2:Get
U16 _stdcall _ECAT_Master_Errorlog_API_Get_Enable(U16 CardNo, U16* Enable, U16* Mode, U16* Level);										//���o�ثeAPI���~�O���]�w���A
U16 _stdcall _ECAT_Master_Errorlog_API_Get_FunIDToString(U16 CardNo, U16 FunID, I8* FunName);											//���oAPI�s���W��
U16 _stdcall _ECAT_Master_Errorlog_API_Clear(U16 CardNo);																				//�M���Ҧ�API���~�O��
U16 _stdcall _ECAT_Master_Errorlog_API_Get_ErrorCnt(U16 CardNo, U16 *ErrorCnt);															//���oAPI���~�O������
U16 _stdcall _ECAT_Master_Errorlog_API_Get_ErrorData(U16 CardNo, U16 *NodeID, U16 *SlotID, U16 *FunID, U16 *ErrorCode, F64 *ErrorTime);	//���o�Ҧ�API���~�O��
U16 _stdcall _ECAT_Master_Errorlog_API_Get_Single_ErrorData(U16 CardNo, U16 Count, U16 *NodeID, U16 *SlotID, U16 *FunID, U16 *ErrorCode, F64 *ErrorTime);	//���o�浧API���~�O��
U16 _stdcall _ECAT_Master_Errorlog_API_DumpData(U16 CardNo, char *FilePath);																//�����Ҧ�API�ɮ�
U16 _stdcall _ECAT_Master_Errorlog_Status_Set_Enable(U16 CardNo, U16 Enable, U16 RecordMask);											//�Ұʪ��A���~�O���\�� RecordMask 0x01:�_�u���� 0x02:Tx-Rx Cnt�O�_�ۦP 0x04:Tx�X�hRx�^�Ӫ��ɶ��O�_�W�LCycle 0x08:��O�ɶ�(OnTick)�O�_�W�LCycle 0x10:CPU�ū׬O�_�W�L���`�u�@�d��
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_Enable(U16 CardNo, U16* Enable, U16* RecordMask);											//���o�ثe���A���~�O���\��]�w
U16 _stdcall _ECAT_Master_Errorlog_Status_Clear(U16 CardNo);																			//�M�����A���~�O��
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_ErrorCnt(U16 CardNo, U16 *ErrorCnt);														//���o�ثe�O�������A���~����
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_ErrorData(U16 CardNo, U16 *ErrorCode, U16 *ErrorData, F64 *ErrorTime);					//���o�Ҧ����A���~�O��
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_Single_ErrorData(U16 CardNo, U16 Count, U16 *ErrorCode, U16 *ErrorData, F64 *ErrorTime);					//���o�浧���A���~�O��

//======DLL��T========
U16 _stdcall _ECAT_Master_Get_DLL_Path(I8 *lpFilePath, U32 nSize, U32 *nLength);									//Ū��DLL���|
U16 _stdcall _ECAT_Master_Get_DLL_Version(I8 *lpBuf, U32 nSize, U32 *nLength);										//Ū��DLL�O��
U16 _stdcall _ECAT_Master_Get_DLL_ProductVersion(I8 *lpBuf, U32 nSize, U32 *nLength);								//Ū��DLL���~�O��
U16 _stdcall _ECAT_Master_Get_DLL_Path_Single(U16 CardNo, I8 *lpFilePath, U32 nSize, U32 *nLength);
U16 _stdcall _ECAT_Master_Get_DLL_Version_Single(U16 CardNo, I8 *lpBuf, U32 nSize, U32 *nLength);
U16 _stdcall _ECAT_Master_Get_DLL_ProductVersion_Single(U16 CardNo, I8 *lpBuf, U32 nSize, U32 *nLength);

//======SYN-TEK Module ESC-5614========
U16 _stdcall _ECAT_Slave_ESC5614_Set_MJ_Config(U16 CardNo, U16 MJNo, U16 MJType, U16 NodeID, U16 SlotNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *MaxSpeed, F64 *TAcc, F64 *Ratio);
U16 _stdcall _ECAT_Slave_ESC5614_Set_MJ_Enable(U16 CardNo, U16 MJNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC5614_Get_IO_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);
U16 _stdcall _ECAT_Slave_ESC5614_Get_MPG_Counter(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Counter);

//======SynTek Module ESC-5621========
U16 _stdcall _ECAT_Slave_ESC5621_Set_Output_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_ESC5621_Set_Input_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_ESC5621_Set_ORG_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC5621_Set_QZ_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC5621_Set_Home_SpMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_ESC5621_Set_MEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC5621_Set_PEL_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC5621_Set_Svon_Inverse(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);

//======SynTek Module ESC-70E2========
U16 _stdcall _ECAT_Slave_ESC70E2_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Eanble);

//======SynTek Module ESC-8124========
U16 _stdcall _ECAT_Slave_ESC8124_Set_Input_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_ESC8124_Set_Input_ConvstFreq_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);
U16 _stdcall _ECAT_Slave_ESC8124_Set_Input_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC8124_Get_Input_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Mode);
U16 _stdcall _ECAT_Slave_ESC8124_Set_Input_AverageMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Avg_Times);

//======SynTek Module ESC-9144========
U16 _stdcall _ECAT_Slave_ESC9144_Set_Output_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 RangeMode);
U16 _stdcall _ECAT_Slave_ESC9144_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_ESC9144_Get_Output_ReturnCode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ReturnCode);

#if defined __cplusplus
}
#endif

#endif