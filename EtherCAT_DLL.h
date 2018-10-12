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

//=========Master==============	Master Initial & Get類
U16 _stdcall _ECAT_Master_Open(U16 *existcard);																		//開卡
U16 _stdcall _ECAT_Master_Initial(U16 CardNo);																		//Master初始化，並切入OP模式
U16 _stdcall _ECAT_Master_Reset(U16 CardNo);																			//關閉所有Master相關程序並釋放記憶體 Close all depend with master and release memory
U16 _stdcall _ECAT_Master_Close(void);																				//關卡
U16 _stdcall _ECAT_Master_Get_CardSeq(U16 CardNo_seq, U16 *CardNo);													//取得卡號
U16 _stdcall _ECAT_Master_Get_SlaveNum(U16 CardNo, U16 *SlaveNum);													//取得當前總Slave數
U16 _stdcall _ECAT_Master_Get_Slave_Info(U16 CardNo, U16 SeqID, U16 *NodeID, U32 *VendorID, U32 *ProductCode, U32 *RevisionNo, U32 *DCTime);	//讀取各模組資訊
U16 _stdcall _ECAT_Master_Get_DC_Status(U16 CardNo, U32 *State, I32 *DCTime, I32 *OffsetTime);							//讀取DC當前資訊
U16 _stdcall _ECAT_Master_Get_Connect_Status(U16 CardNo, U16 *Status);													//讀取連線狀態
U16 _stdcall _ECAT_Master_Get_Api_BufferLength(U16 CardNo, U16 NodeID, U16 *Length);									//讀取當前設定的循環週期時間
U16 _stdcall _ECAT_Master_Get_Cycle_SpendTime(U16 CardNo, F64 *Tx_Time, F64 *Tx_MaxTime, F64 *Rx_Time, F64 *Rx_MaxTime);	//讀取當前循環內消耗掉的時間及最大時間
U16 _stdcall _ECAT_Master_Check_Initial_Done(U16 CardNo, U16 *InitDone);												//詢問DLL層是否已Initial完成
U16 _stdcall _ECAT_Master_Get_Initial_ErrorCode(U16 CardNo);															//當_ECAT_Master_Check_Initial_Done為發生錯誤時，讀取錯誤資訊
U16 _stdcall _ECAT_Master_Check_Working_Counter(U16 CardNo, U16 *Abnormal_Flag, U16 *Working_Slave_Cnt);				//確認通訊是否正常以及當前通訊Slave辨識數量
U16 _stdcall _ECAT_Master_Set_Working_Counter_Value(U16 CardNo, U16 Value);												//超過設定的週期時間會觸發Abnormal_Flag，預設為1週期時間
U16 _stdcall _ECAT_Master_Get_Return_Code_Message(U16 ReturnCode, I8 *Message);											//將回傳錯誤代碼轉為對應的錯誤訊息
U16 _stdcall _ECAT_Master_Get_Hardware_ID(U16 CardNo, U16 *DeviceID);

//=========Master==============	Master Config
U16 _stdcall _ECAT_Master_Set_CycleTime(U16 CardNo, U16 Mode);													//設定循環週期時間(U16 CardNo, 需在Initial前設定)
U16 _stdcall _ECAT_Master_Get_CycleTime(U16 CardNo, U16 *CycleTime);											//讀取當前設定的循環週期時間
U16 _stdcall _ECAT_Master_Get_DLL_SeqID(U16 CardNo, U16 *SeqID);												//取得當前DLL使用的序列ID
U16 _stdcall _ECAT_Master_Get_SerialNo(U16 CardNo, U32 *SerialNo);												//取得PAC的Serial No
U16 _stdcall _ECAT_Master_NodeID_Alias_Enable(U16 CardNo, U16 Enable);											//設定是否使用自定義站號的功能

U16 _stdcall _ECAT_Autoconfig_Open_File(U16 CardNo, I8 *FilePath);												//Autoconfig from file
U16 _stdcall _ECAT_Autoconfig_Save_File(U16 CardNo, I8 *FilePath);												//Save Node File to file
U16 _stdcall _ECAT_Autoconfig_Set_Slave_DCTime(U16 CardNo, U16 NodeID, U16 Mode);								//設定各軸DC時間(us)
U16 _stdcall _ECAT_Autoconfig_Clear_ConfigFile(U16 CardNo);														//清除目前已載入的設定

U16 _stdcall _ECAT_Autoconfig_Set_NodeID_Alias(U16 CardNo, U16 NodeID, U16 MapNodeID);							//自定義站號
U16 _stdcall _ECAT_Autoconfig_Get_NodeID_Alias(U16 CardNo, U16 RealNodeID, U16 *MapNodeID);						//取得自定義站號
U16 _stdcall _ECAT_Autoconfig_Save_NodeID_Alias(U16 CardNo);													//對模組記憶體區塊實際寫入自定義站號(此API下達後會自動斷線並將所需資訊寫入模組記憶體，完成後模組需重啟電源)

//========Normal Slave========= Slave(全種類)通用
U16 _stdcall _ECAT_Slave_SDO_Send_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave通用指令，對該站下達SDO(CANopen格式)指令。
U16 _stdcall _ECAT_Slave_SDO_Read_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave通用指令，取得該站當前SDO(CANopen格式)資料。
U16 _stdcall _ECAT_Slave_SDO_Quick_Send_Message(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Index, U16 SubIndex, U16 Datasize, U8 *Data);	//Slave通用指令，對該站下達SDO(CANopen格式)指令，但不等待指令下達完畢
U16 _stdcall _ECAT_Slave_SDO_Quick_Read_Message(U16 CardNo, U16 NodeID, U16 SlotID, U16 Index, U16 SubIndex, U16 DataSize);		//Slave通用指令，對該站下達SDO讀取指令(CANopen格式)
U16 _stdcall _ECAT_Slave_SDO_Read_Response(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Done, U8 *Data, U32 *ErrorCode);			//Slave通用指令，對該站讀取回傳資料(CANopen格式)
U16 _stdcall _ECAT_Slave_SDO_Wait_All_Done(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo);				//Slave通用指令，對複數站下達等候當前累積的SDO指令全數完成
U16 _stdcall _ECAT_Slave_SDO_Check_Done(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Done);
U16 _stdcall _ECAT_Slave_SDO_Get_ErrorCode(U16 CardNo, U16 NodeID, U16 SlotNo, U32 *ErrorCode);				//讀取最後一筆當ERR_ECAT_SDO_Return_Error發生時的ErrorCode，ErrorCode列表可參考各模組定義
U16 _stdcall _ECAT_Slave_PDO_Get_OD_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 IOType, U16 ODIndex, U16 ODSubIndex, U16 ByteSize, U8 *Data);	//"Slave通用指令，對該站讀取某一OD碼的資料，該資料需有映射於PDO構成中, IOType 0:Rx 1:Tx"
U16 _stdcall _ECAT_Slave_PDO_Set_OD_Data(U16 CardNo, U16 NodeID, U16 SlotNo, U16 ODIndex, U16 ODSubIndex, U8 *Data); //"Slave通用指令，對該站下達某一OD碼的資料，該資料需有映射於PDO構成中, 僅Tx可使用"
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

//========Motion Salve========= Slave(Motion種類)通用
U16 _stdcall _ECAT_Slave_Motion_Get_MoveMode(U16 CardNo, U16 NodeID, U16 SlotNo, U8 *Mode);							//讀取當前MotionSlave的動作模式 0:空模式 1:PP 3:PV 4:PT 6:Home 8:CSP
U16 _stdcall _ECAT_Slave_Motion_Get_ControlWord(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ControllWord);				//讀取當前MotionSlave的ControlWord
U16 _stdcall _ECAT_Slave_Motion_Get_StatusWord(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *StatusWord);				//讀取當前MotionSlave的StatusWord
U16 _stdcall _ECAT_Slave_Motion_Get_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Command);						//讀取當前MotionSlave的Command
U16 _stdcall _ECAT_Slave_Motion_Get_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Position);					//讀取當前MotionSlave的Position
U16 _stdcall _ECAT_Slave_Motion_Get_Actual_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *ActualCommand);			//讀取當前MotionSlave的實際Command(不受VirtualCommand影響)
U16 _stdcall _ECAT_Slave_Motion_Get_Actual_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *ActualPosition);		//讀取當前MotionSlave的實際Position(不受VirtualCommand影響)
U16 _stdcall _ECAT_Slave_Motion_Get_Mdone(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Mdone);							//讀取當前MotionSlave的運動完成狀態(Motion Done)
U16 _stdcall _ECAT_Slave_Motion_Get_Speed(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Speed);  						//讀取當前MotionSlave的Command Speed 2017-04-19
U16 _stdcall _ECAT_Slave_Motion_Get_Current_Speed(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *Speed);					//讀取當前MotionSlave的Current Speed
U16 _stdcall _ECAT_Slave_Motion_Get_Torque(U16 CardNo, U16 NodeID, U16 SlotNo, I16 *Torque);						//讀取當前MotionSlave的Toruqe值
U16 _stdcall _ECAT_Slave_Motion_Get_Target_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *TargetCommand);			//SlaveMotion指令，取得當前目標位置的資料
U16 _stdcall _ECAT_Slave_Motion_Get_Buffer_Length(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *BufferLength);			//讀取當前指令Buffer數量

U16 _stdcall _ECAT_Slave_Motion_Set_MoveMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 OpMode);						//設定當前MotionSlave的動作模式 0:空模式 1:PP 3:PV 4:PT 6:Home 8:CSP
U16 _stdcall _ECAT_Slave_Motion_Set_Svon(U16 CardNo, U16 NodeID, U16 SlotNo, U16 On_Off);							//設定當前MotionSlave Sever On / Off
U16 _stdcall _ECAT_Slave_Motion_Ralm(U16 CardNo, U16 NodeID, U16 SlotNo);											//重置當前MotionSlave的錯誤狀態
U16 _stdcall _ECAT_Slave_Motion_Set_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Pos);							//設定當前MotionSlave的位置
U16 _stdcall _ECAT_Slave_Motion_Set_Command(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Cmd);							//設定當前MotionSlave的命令位置
U16 _stdcall _ECAT_Slave_Motion_Emg_Stop(U16 CardNo, U16 NodeID, U16 SlotNo);										//對當前MotionSlave下達急停指令
U16 _stdcall _ECAT_Slave_Motion_Sd_Stop(U16 CardNo, U16 NodeID, U16 SlotNo, F64 Tdec);								//對當前MotionSlave下達減速停止指令
U16 _stdcall _ECAT_Slave_Motion_Set_Alm_Reaction(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Fault_Type, U16 WR_Type);	//設定Alm時的反應機制 0:不理會, 1:上緣觸發, 2:永久停止	預設為 2 / 1
U16 _stdcall _ECAT_Slave_Motion_Set_Internal_Limit_Active_Reaction(U16 CardNo, U16 NodeID, U16 SlotID, U16 Internal_Limit_Active_Type);	//設定ila時的反應機制 0:不理會, 1:EMG, 2:MASK
U16 _stdcall _ECAT_Slave_Motion_Set_Command_Wait_Target_Reach(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Wait);  // 2016-10-27
U16 _stdcall _ECAT_Slave_Motion_Ignore_Sd_Stop_Wrong_Value(U16 CardNo, U8 Ignore);  // 2016-12-19

U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 TriggerMode, U16 Signal_Source);	//SlaveMotion指令，設定『觸發擷取』功能的行為模式
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_QuickStart(U16 CardNo, U16 NodeID, U16 SlotNo);									//SlaveMotion指令，快速致能『觸發擷取』功能
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_QuickDone(U16 CardNo, U16 NodeID, U16 SlotNo);									//SlaveMotion指令，快速重置『觸發擷取』功能
U16 _stdcall _ECAT_Slave_Motion_Set_TouchProbe_Disable(U16 CardNo, U16 NodeID, U16 SlotNo);										//SlaveMotion指令，關閉『觸發擷取』功能
U16 _stdcall _ECAT_Slave_Motion_Get_TouchProbe_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);							//SlaveMotion指令，取得當前『觸發擷取』功能的狀態
U16 _stdcall _ECAT_Slave_Motion_Get_TouchProbe_Position(U16 CardNo, U16 NodeID, U16 SlotNo, I32 *LatchPosition);				//SlaveMotion指令，取得當前擷取到的位置

//========Motion Salve CSP Command======== Slave(Motion種類) CSP模式運動指令
U16 _stdcall _ECAT_Slave_CSP_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Dist, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//單軸點對點運動
U16 _stdcall _ECAT_Slave_CSP_Start_V_Move(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Dir, I32 StrVel, I32 ConstVel, F64 Tacc, U16 SCurve);									//連續等速運動
U16 _stdcall _ECAT_Slave_CSP_Start_Arc_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//圓弧運動第一類
U16 _stdcall _ECAT_Slave_CSP_Start_Arc2_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *EndPoint, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//圓弧運動第二類
U16 _stdcall _ECAT_Slave_CSP_Start_Arc3_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, I32 *EndPoint, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//圓弧運動第三類
U16 _stdcall _ECAT_Slave_CSP_Start_Arc4_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *MidPoint, I32 *EndPoint, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);	//圓弧運動第四類
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 Spiral_Interval, F64 Angle, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);//二軸螺旋線運動第一類
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral2_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 *EndPoint, U16 Dir, U16 CycleNum, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);//二軸螺旋線運動第二類
U16 _stdcall _ECAT_Slave_CSP_Start_Sphere_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *Target1Point, I32 *Target2Point, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//三軸球弧運動
U16 _stdcall _ECAT_Slave_CSP_Start_Heli_Move(U16 CardNo, U16 *NodeID, U16 *SlotNo, I32 *CenterPoint, I32 Depth, I32 Pitch, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//螺旋線運動
U16 _stdcall _ECAT_Slave_CSP_Start_Msbrline_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, U16 ArcNodeBit, I32 *Target1Point, I32 *Target2Point, U16 Mode, F64 Parameter, F64 ArcAngle1, F64 ArcAngle2, F64 SpdRatio, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//MSBRLINE
U16 _stdcall _ECAT_Slave_CSP_Start_Mabrline_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *Target1Point, I32 *Target2Point, I32 StrVel, I32 FirstVel, I32 SecondVel, I32 EndVel, F64 Tacc_Step1, F64 Tacc_Step2, U16 Absflag);
U16 _stdcall _ECAT_Slave_CSP_Start_Multiaxes_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *Dist, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 IsAbs);	//多軸點對點運動
U16 _stdcall _ECAT_Slave_CSP_Start_2Segment_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 SegMode, I32 Dist, I32 Dist2, I32 StrVel, I32 MaxVel, I32 MaxVel2, I32 EndVel, F64 Tacc, F64 Tsec, F64 Tdec, U16 SCurve, U16 IsAbs);	//單軸兩段點對點運動
U16 _stdcall _ECAT_Slave_CSP_Start_Helix_Multiaxes_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, I32 *CenterPoint, I32 *Dist, I32 Depth, I32 Pitch, U16 Dir, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);	//多軸直線加Helix運動
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Helix_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 Spiral_Interval, F64 Angle, I32 Pitch, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);//三軸螺旋線運動第一類
U16 _stdcall _ECAT_Slave_CSP_Start_Spiral_Helix2_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *CenterPoint, I32 *EndPoint, U16 Dir, U16 CycleNum, I32 Pitch, I32 StrVel, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve, U16 Abs);//三軸螺旋線運動第二類
U16 _stdcall _ECAT_Slave_CSP_Start_Tank_Helix_Move(U16 CardNo, U16 *NodeID, U16 *SlotID, I32 *Point1, I32 *Point2, I32 *Point3, I32 *Point4, I32 Depth, I32 Pitch, I32 MaxVel, U16 FilterTime, U16 AMFNum, U16 Abs);//二軸方形繞圓運動
U16 _stdcall _ECAT_Slave_CSP_Reference_Pos_Move_Config(U16 CardNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, I32 ReferencePos, I16 Dir);

//========Motion Slave SuperImposed ========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_SuperImposed_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 VelocityDiff, F64 Tacc, F64 Tdec);
U16 _stdcall _ECAT_Slave_CSP_Start_HaltSuperImposed_Move(U16 CardNo, U16 NodeID, U16 SlotID, F64 Tdec);
U16 _stdcall _ECAT_Slave_CSP_Start_Get_Superimposed_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *State);

//========Motion Slave GearIn ========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_GearIn_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 RatioNumerator, U32 RatioDenominator, F64 Acceleration, F64 Deceleration, U16 GearIn_Mode);
//SourceType: 0->模組 Source, 1->Local Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_GearOut_Move(U16 CardNo, U16 NodeID, U16 SlotID);
U16 _stdcall _ECAT_Slave_CSP_Start_Get_GearIn_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *State);

//========Motion Slave PVT Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 *TargetVel, U16 Abs);	// 單軸PVT運動
U16 _stdcall _ECAT_Slave_CSP_Start_PVTComplete_Move(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 StrVel, I32 EndVel, U16 Abs); // 單軸PVTComplete運動
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Config(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 *TargetVel, U16 Abs);					// 單軸PVT運動
U16 _stdcall _ECAT_Slave_CSP_Start_PVTComplete_Config(U16 CardNo, U16 NodeID, U16 SlotID, I32 DataCnt, I32 *TargetPos, I32 *TargetTime, I32 StrVel, I32 EndVel, U16 Abs);	// 單軸PVTComplete運動
U16 _stdcall _ECAT_Slave_CSP_Start_PVT_Sync_Move(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray);

//========Motion Slave ECAM Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Engage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 EngageNodeID, U16 EngageSlotID, U16 SourceNo, I32 Engage_PreLed, I32 Cycle_PreLead, U16 Engage_Mode);
//SourceType: 0->模組DI, 1->Local DI, 2->模組 Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Position Edge, 1->DI+Negative Edge, 2->zero impulse signal+Position Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Compensate_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 CompensateNodeID, U16 CompensateSlotID, U16 SourceNo, I32 TargetPos, I32 Max_Compensate_Ratio, I32 Active_Range_Ratio, U16 CompensateTime, U16 Enable);
//SourceType: 0->模組DI, 1->Local DI, 2->模組 Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Position Edge, 1->DI+Negative Edge, 2->zero impulse signal+Position Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_DisEngage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 DisEngageNodeID, U16 DisEngageSlotID, U16 SourceNo, I32 DisEngage_Position, U16 DI_DisEngage, U16 DisEngage_TurnOff, U16 DisEngage_Mode);
//SourceType: 0->模組DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_SingleMove(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Abs);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Disable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Get_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);

U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Table_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 *DataArray, I32 Master_Pulse, F64 Slave_mm_Pulse, F64 Master_mm_Pulse);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Velocity_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 Percent[5], I32 SCurveRegion, I32 TotalLength, I32 Master_Pulse_P, F64 Slave_mm_Pulse, F64 Master_mm_Pulse, U16 Construct_Mode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Flying_Shears_Data(U16 CardNo, U16 ECAMNo, F64 GearNum_A, F64 GearNum_B, I32 KnifeNum, F64 SlaveDiameter, F64 EncoderDiameter, I32 EncoderPulseRev, I32 SlavePUURev, I32 CutLength, I32 RegionNum, I32 Region[3], I32 Slave_Prelead, I32 Master_Engage_Prelead, U16 PreLeadMode);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Intermittence_Print_Data(U16 CardNo, U16 ECAMNo, I32 RegionNum, I32 PrintLength, I32 BlankLength, F64 GearNum_A, F64 GearNum_B, I32 SlavePUURev, F64 SlaveDiameter, I32 MasterPulseRev, F64 MasterDiameter, I32 HoldingAreaDeg, I32 SCurveDeg, I32 SynIncreaseDeg);

U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 ECAMNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo);
//SourceType: 0->模組 Source, 1->Local Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Move_ChangeTable(U16 CardNo, U16 NodeID, U16 SlotID, U16 ECAMNo);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM_Set_Scale(U16 CardNo, U16 NodeID, U16 SlotID, F64 Percentage);

//========Motion Slave ECAM2 Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_Engage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 EngageNodeID, U16 EngageSlotID, U16 SourceNo, U16 Enable);
//SourceType: 0->模組DI, 1->Local DI, 2->模組 Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Positive Edge, 1->DI+Negative Edge, 2->zero impulse signal+Positive Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_Compensate_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 CompensateNodeID, U16 CompensateSlotID, U16 SourceNo, F64 TargetPos, F64 ActiveRangeRatio, F64 MaxVel, F64 Acceleration, F64 Deceleration, U16 Enable);
//SourceType: 0->模組DI, 1->Local DI, 2->模組 Latch, 3->Local Latch, 4->TouchProb(SourceNo: 0->DI+Positive Edge, 1->DI+Negative Edge, 2->zero impulse signal+Positive Edge, 3->zero impulse signal+Negative Edge)
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Set_DisEngage_Parameters(U16 CardNo, U16 NodeID, U16 SlotID, U16 SourceType, U16 DisEngageNodeID, U16 DisEngageSlotID, U16 SourceNo, U16 Enable);
//SourceType: 0->模組DI, 1->Local DI
//
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_RotaryCut_Initial(U16 CardNo, U16 RotCutNo, F64 RotaryAxisRadius, U16 RotaryAxisKnifeNum, F64 FeedAxisRadius, F64 CutLenth, F64 SyncStartPos, F64 SyncStopPos);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_RotaryCut_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 RotCutNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 RotaryAxis_PulseRev, I32 FeedAxis_PulseRev, I16 RotaryAxis_Dir, I16 FeedAxis_Dir);
//SourceType: 0->模組 Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_FlyingShear_Initial(U16 CardNo, U16 FlyingShearNo, F64 MasterRadius, F64 SlaveRadius, F64 CutLength, F64 MasterStartPosition, F64 MasterSyncPosition, F64 SlaveSyncPosition, F64 SlaveEndPosition, F64 SlaveWaitPosition, F64 SlaveVelocity, F64 SlaveAcceleration, F64 SlaveDeceleration);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_FlyingShear_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 FlyingShearNo, U16 MasterNodeID, U16 MasterSlotID, U16 SourceType, U16 SourceNo, I32 MasterAxis_PulseRev, I32 SlaveAxis_PulseRev, I16 MasterAxis_Dir, I16 SlaveAxis_Dir);
//SourceType: 0->模組 Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
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
//SourceType: 0->模組 Source, 1->Local Source, 2->Virtual Source, SourceNo: 0->Feedback, 1->Command
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_CamOut(U16 CardNo, U16 NodeID, U16 SlotID);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_Modify(U16 CardNo, U16 CamNo, U16 PointNo, F64 *Parameters);
U16 _stdcall _ECAT_Slave_CSP_Start_ECAM2_Profile_CamSet(U16 CardNo, U16 NodeID, U16 SlotID);

//========Motion Slave TableMotion Set========= Slave(Motion種類) CSP模式用
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

//========Motion Slave MotionBuffer Set========= Slave(Motion種類) CSP模式用
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

//========Motion Slave TouchProb Home Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Start_TouchProb_Home_Move(U16 CardNo, U16 NodeID, U16 SlotID, U16 TriggerSource, U16 TriggerEdge, U16 Direction, I32 Offset, I32 StrVel, I32 FirstVel, I32 SecondVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 SCurve);	//TriggerSource 0:DI, 1:zero impulse signal, TriggerEdge:0:Position Edge, 1:Negative Edge, HomeMode:0:Position Direction, 1:Negative Direction
U16 _stdcall _ECAT_Slave_CSP_Start_TouchProb_Home_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status);	//0:Done, 1:Busy, 99:Error

//========Motion Slave CSV Command====== Slave(Motion種類) CSV模式運動指令
U16 _stdcall _ECAT_Slave_CSV_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 Target_Velocity, F64 Acceleration, U16 Curve_Mode, U16 Acc_Type);
U16 _stdcall _ECAT_Slave_CSV_Multi_Start_Move(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo, I32 *Target_Velocity, F64 *Acceleration, U16 Curve_Mode, U16 Acc_Type);

//========Motion Slave CSV Command====== Slave(Motion種類) CSV模式運動指令
U16 _stdcall _ECAT_Slave_CST_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I16 Target_Torque, U32 Slope, U16 Curve_Mode);
U16 _stdcall _ECAT_Slave_CST_Multi_Start_Move(U16 CardNo, U16 AxisNum, U16 *NodeID, U16 *SlotNo, I16 *Target_Torque, U32 *Slope, U16 Curve_Mode);

//========Motion Slave CSP Set========= Slave(Motion種類) CSP模式設定用
U16 _stdcall _ECAT_Slave_CSP_Set_Gear(U16 CardNo, U16 NodeID, U16 SlotNo, F64 Numerator, F64 Denominator, I16 Enable);	//設定當前MotionSlave的軟體電子齒輪
U16 _stdcall _ECAT_Slave_CSP_Set_Softlimit(U16 CardNo, U16 NodeID, U16 SlotNo, I32 PosiLimit, I32 NegaLimit, U16 Mode);	//設定當前MotionSlave的軟體極限
U16 _stdcall _ECAT_Slave_CSP_TargetPos_Change(U16 CardNo, U16 NodeID, U16 SlotNo, I32 NewPos);							//P change
U16 _stdcall _ECAT_Slave_CSP_Velocity_Change(U16 CardNo, U16 NodeID, U16 SlotNo, I32 NewSpeed, F64 Tsec);				//V Change
U16 _stdcall _ECAT_Slave_CSP_TargetPos_Velocity_Change(U16 CardNo, U16 NodeID, U16 SlotID, I32 NewPos, I32 NewSpeed, F64 Tsec);		//P&V Change
U16 _stdcall _ECAT_Slave_CSP_Feedrate_Overwrite(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode, I32 NewSpeed, F64 Tsec);	//Feedrate Overwrite
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);						//致能Speed Continue的功能
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Set_Mode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);						//設定Speed Continue的Mode
U16 _stdcall _ECAT_Slave_CSP_Speed_Continue_Set_Combine_Ratio(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Ratio);			//設定Speed Continue的合成比率
U16 _stdcall _ECAT_Slave_CSP_Scurve_Rate(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Scurve_Rate);							//設定SCurve中的Tcurve的比例
U16 _stdcall _ECAT_Slave_CSP_Linear_Speed_Master(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode);							//設定速度設定的種類 0:向量速度 1:分量中最大速度
U16 _stdcall _ECAT_Slave_CSP_Mask_Axis(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotNoArray);
U16 _stdcall _ECAT_Slave_CSP_Sync_Config(U16 CardNo, U16 AxisNum, U16 *AxisArray, U16 *SlotArray, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Sync_Move(U16 CardNo);
U16 _stdcall _ECAT_Slave_CSP_Virtual_Set_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Virtual_Set_Command(U16 CardNo, U16 NodeID, U16 SlotID, I32 Command);

//========Motion Slave AMF Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Set_SingleAxis_NormalAMF_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 FilterTime, U16 Enable);
U16 _stdcall _ECAT_Slave_CSP_Set_NormalAMF_Enable(U16 CardNo, U16 FilterNum, U16 Enable);

//========Motion Slave DI Function Set========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Set_DITrigger_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 Polarity, U16 FilterTime);	//Polarity: 0->Low_High_Low, 1->High_Low_High
U16 _stdcall _ECAT_Slave_CSP_Get_DITrigger_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *TriggerStatus, U32 *TriggerCount);
U16 _stdcall _ECAT_Slave_CSP_Set_SLD_Enable(U16 CardNo, U16 NodeID, U16 SlotID, F64 Tdec, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->模組DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Set_TrSeg2_Enable(U16 CardNo, U16 NodeID, U16 SlotID, I32 Dist, I32 ConstVel, I32 EndVel, F64 Tacc, F64 Tdec, U16 Scurve, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->模組DI, 1->Local DI
U16 _stdcall _ECAT_Slave_CSP_Set_Velocity_Change_Enable(U16 CardNo, U16 NodeID, U16 SlotID, I32 NewSpeed, F64 Tsec, U16 SourceType, U16 DINodeID, U16 DISlotID, U16 SourceNo, U16 Enable);		//SourceType: 0->模組DI, 1->Local DI

//========Motion Slave CSP Get========= Slave(Motion種類) CSP模式取得用
U16 _stdcall _ECAT_Slave_CSP_Get_SoftLimit_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status); //Bit 0:M_Status, 1:P_status

//========Motion Slave CSP TargetReach========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Set_SoftTargetReach(U16 CardNo, U16 NodeID, U16 SlotID, U16 Window_Time, U32 Position_Window, U16 Enable); //Window_Time:ms, Position_Window:pulse
U16 _stdcall _ECAT_Slave_CSP_Get_SoftTargetReach_Status(U16 CardNo, U16 NodeID, U16 SlotID, U16 *Status); //0: Off, 1:On

//========Motion Slave CSP Pitch========= Slave(Motion種類) CSP模式取得用
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_InterVal(U16 CardNo, U16 NodeID, U16 SlotID, U32 InterVal);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Mode(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);	//0: 雙向, 1: 單向
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Org(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 OrgPos);	//0: 正向, 1: 負向
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Rel_Table(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 *Table, U16 Num);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Abs_Table(U16 CardNo, U16 NodeID, U16 SlotID, U16 Dir, I32 *Table, U16 Num);
U16 _stdcall _ECAT_Slave_CSP_Pitch_Set_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);

//========Motion Slave CSP Backlash========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Backlash_Set_Info(U16 CardNo, U16 NodeID, U16 SlotID, I16 Backlash, U16 AccStep, U16 ConstStep, U16 DecStep);
U16 _stdcall _ECAT_Slave_CSP_Backlash_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Mode);

//========Motion Slave CSP Gantry========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Follow_Enable(U16 CardNo, U16 GantryNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, U16 Enable);  // 2017-01-09
U16 _stdcall _ECAT_Slave_CSP_Gantry_Enable(U16 CardNo, U16 GantryNo, U16 MasterNodeID, U16 MasterSlotID, U16 SlaveNodeID, U16 SlaveSlotID, I32 Motor_Pulse_Per_Turn, F64 Motor_MaxTorque, F64 K_I, F64 K_VI, F64 Filter_Frequency, U16 Enable);
//Motor_MaxTorque = Motor_RotorInertia(馬達轉子慣量) / Motor_RatedTorque(馬達額定扭矩)

//========Motion Slave CSP Velocity Offset Gantry========= Slave(Motion種類) CSP模式用
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

//========Motion Slave CSP Velocity Compensate========= Slave(Motion種類) CSP模式用
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Info(U16 CardNo, U16 NodeID, U16 SlotID, I32 Velcoity_Offset_Normalize, I32 Pulse_Normalize, I32 Podition_Threshold, F64 PID_Kp, F64 PID_Ki, F64 PID_Kd);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_LPF_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 LPF_Mode, F64 LPF_Time);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Forward_Info(U16 CardNo, U16 NodeID, U16 SlotID, U16 Forward_Mode, U16 Forward_Time, F64 Forward_Kp);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_PIDAdv_Info(U16 CardNo, U16 NodeID, U16 SlotID, F64 PID_Output_Max, F64 PID_Output_Min, F64 PID_Ki_Max, F64 PID_Ki_Min);
U16 _stdcall _ECAT_Slave_CSP_Velocity_Compensate_Enable(U16 CardNo, U16 NodeID, U16 SlotID, U16 Enable);

//========Motion Slave Home =========== Slave(Motion種類) Home模式通用
U16 _stdcall _ECAT_Slave_Home_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Mode, I32 Offset, U32 FirstVel, U32 SecondVel, U32 Acceleration);	//尋邊運動設定
U16 _stdcall _ECAT_Slave_Home_Move(U16 CardNo, U16 NodeID, U16 SlotNo);																			//尋邊運動
U16 _stdcall _ECAT_Slave_Home_Status(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Status);																		//尋邊運動狀態

//========User Motion Control=========== Slave(Motion種類) Motion User Define
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Type(U16 CardNo, U16 GroupNo, U16 AxisNum, U16 *AxisNo, U16 *SlotNo, U16 MotionType);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Enable_Mode(U16 CardNo, U16 GroupNo, U16 Enable);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_Enable_Mode(U16 CardNo, U16 GroupNo, U16 *Enable);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Set_Data(U16 CardNo, U16 GroupNo, I32 *CmdPulse);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_DataCnt(U16 CardNo, U16 GroupNo, U16 *Counter);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Clear_Data(U16 CardNo, U16 GroupNo);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Ralm(U16 CardNo, U16 GroupNo);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Svon(U16 CardNo, U16 GroupNo, U16 ON_OFF);
U16 _stdcall _ECAT_Slave_User_Motion_Control_Get_Alm(U16 CardNo, U16 GroupNo, U16 *Alm);

//========Normal Slave - Record Data========== Slave(全種類)通用 - 擷取資料系列
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

//========Motion Slave PP Command========= Slave(Motion種類) PP模式運動指令
U16 _stdcall _ECAT_Slave_PP_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetPos, U32 ConstVel, U32 Acceleration, U32 Deceleration, U16 Abs_Rel);
U16 _stdcall _ECAT_Slave_PP_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U32 End_Vel, I32 Min_Range_Limit, I32 Max_Range_Limit, I32 Min_Soft_Limit, I32 Max_Soft_Limit);

//========Motion Slave PV Command=== Slave(Motion種類)	 Velocity模式運動指令
U16 _stdcall _ECAT_Slave_PV_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetVel, U32 Acceleration, U32 Deceleration);
U16 _stdcall _ECAT_Slave_PV_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U16 Max_Torque, U16 Velocity_Window, U16 Velocity_Window_Time, U16 Velocity_Threshold, U16 Velocity_Threshold_Time);

//========Motion Slave VL Command=== Slave(Motion種類)	 Velocity模式運動指令
U16 _stdcall _ECAT_Slave_VL_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I32 TargetVel, U32 Acceleration, U32 Deceleration);

//========Motion Slave PT Command===== Slave(Motion種類) Torque模式運動指令
U16 _stdcall _ECAT_Slave_PT_Start_Move(U16 CardNo, U16 NodeID, U16 SlotNo, I16 Target_Torque, U32 Slope);
U16 _stdcall _ECAT_Slave_PT_Advance_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 SetBit, U16 Max_Current, I16 Torque_Profile);

//========IO Slave===============	Slave(IO種類) 通用
U16 _stdcall _ECAT_Slave_DIO_Get_Input_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *value);	//讀取當前IOSlave(MN型)的訊號輸入
U16 _stdcall _ECAT_Slave_DIO_Get_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *value);	//讀取當前IOSlave(NT型)的訊號輸出
U16 _stdcall _ECAT_Slave_DIO_Set_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 value);	//設定當前IOSlave(NT型)的訊號輸出
U16 _stdcall _ECAT_Slave_DIO_Get_Single_Input_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 *value);	//讀取當前IOSlave(MN型)的訊號單點輸入
U16 _stdcall _ECAT_Slave_DIO_Get_Single_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 *value);	//讀取當前IOSlave(NT型)的訊號單點輸出
U16 _stdcall _ECAT_Slave_DIO_Set_Single_Output_Value(U16 CardNo, U16 NodeID, U16 SlotNo, U16 BitNum, U16 value);	//設定當前IOSlave(NT型)的訊號單點輸出
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
U16 _stdcall _ECAT_Slave_R1_EC8124_Get_Input_Value(U16 CardNo, U16 NodeID, U16 SlotID, U16 AIType, F64 *Value);	//AIType:0->回傳電壓值(V), 1->回傳電流值(mA)

//======ECAT Module R1-EC9144========
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_RangeMode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 RangeMode);
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable);
U16 _stdcall _ECAT_Slave_R1_EC9144_Get_Output_ReturnCode(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *ReturnCode);
U16 _stdcall _ECAT_Slave_R1_EC9144_Set_Output_Value(U16 CardNo, U16 NodeID, U16 SlotID, F64 Value);
U16 _stdcall _ECAT_Slave_R1_EC9144_Get_Output_Value(U16 CardNo, U16 NodeID, U16 SlotID, F64 *Value);

//======Delta Servo========
U16 _stdcall _ECAT_Slave_DeltaServo_Write_Parameter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, I32 WriteData);											// 寫入台達參數
U16 _stdcall _ECAT_Slave_DeltaServo_Read_Parameter(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, I32 *ReadData);												// 讀取台達參數
U16 _stdcall _ECAT_Slave_DeltaServo_Read_Parameter_Info(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Page, U16 Index, U16 *ParaType, U16 *DataSize, U16 *DataType);			// 讀取台達參數資訊
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Velocity_Limit(U16 CardNo, U16 NodeID, U16 SlotNo, U32 LimitValue);																// 設定台達驅動器速度限制
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Compare_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 Enable, U16 CompareSource, U16 SignalLength, U16 SignalPolarity);		// 設定並啟用台達Compare Trigger功能
U16 _stdcall _ECAT_Slave_DeltaServo_Get_Compare_Enable(U16 CardNo, U16 NodeID, U16 SlotNo, U16 *Enable, U16 *CompareSource, U16 *SignalLength, U16 *SignalPolarity);	// 讀取台達Compare Trigger設定狀態
U16 _stdcall _ECAT_Slave_DeltaServo_Set_Compare_Config(U16 CardNo, U16 NodeID, U16 SlotNo, U16 CompareNum, I32 *ComparePos);											// 設定台達Compare Trigger位置數量及座標

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
U16 _stdcall _ECAT_Master_MRAM_Write_Word_Data(U16 CardNo, U32 Index, U32 DataNum, U16 *Data);						// 將U16資料寫入PAC的MRam指定位址
U16 _stdcall _ECAT_Master_MRAM_Read_Word_Data(U16 CardNo, U32 Index, U32 DataNum, U16 *Data);							// 讀出PAC的MRam指定位址U16資料
U16 _stdcall _ECAT_Master_MRAM_Write_DWord_Data(U16 CardNo, U32 Index, U32 DataNum, U32 *Data);						// 將U32資料寫入PAC的MRam指定位址
U16 _stdcall _ECAT_Master_MRAM_Read_DWord_Data(U16 CardNo, U32 Index, U32 DataNum, U32 *Data);						// 讀出PAC的MRam指定位址U32資料

//======軸卡GPIO========
U16 _stdcall _ECAT_GPIO_Set_Output(U16 CardNo, U16 OnOff);
U16 _stdcall _ECAT_GPIO_Get_Output(U16 CardNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Get_Input(U16 CardNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Set_Digital_Filter(U16 CardNo, U16 Filter);
U16 _stdcall _ECAT_GPIO_Get_Digital_Filter(U16 CardNo, U16 *Filter);
U16 _stdcall _ECAT_GPIO_Set_Single_Output(U16 CardNo, U16 BitNo, U16 OnOff);
U16 _stdcall _ECAT_GPIO_Get_Single_Output(U16 CardNo, U16 BitNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Get_Single_Input(U16 CardNo, U16 BitNo, U16 *OnOff);
U16 _stdcall _ECAT_GPIO_Set_Output_Control_Mode(U16 CardNo, U16 Mode);  // 2016-06-02

//======軸卡Compare========
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


//======軸卡CE========
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
U16 _stdcall _ECAT_Master_Errorlog_API_Set_Enable(U16 CardNo, U16 Enable, U16 Mode, U16 Level);											//Mode=>0:單次 1:循環 ,Level=>0:ALL 1:Set 2:Get
U16 _stdcall _ECAT_Master_Errorlog_API_Get_Enable(U16 CardNo, U16* Enable, U16* Mode, U16* Level);										//取得目前API錯誤記錄設定狀態
U16 _stdcall _ECAT_Master_Errorlog_API_Get_FunIDToString(U16 CardNo, U16 FunID, I8* FunName);											//取得API編號名稱
U16 _stdcall _ECAT_Master_Errorlog_API_Clear(U16 CardNo);																				//清除所有API錯誤記錄
U16 _stdcall _ECAT_Master_Errorlog_API_Get_ErrorCnt(U16 CardNo, U16 *ErrorCnt);															//取得API錯誤記錄筆數
U16 _stdcall _ECAT_Master_Errorlog_API_Get_ErrorData(U16 CardNo, U16 *NodeID, U16 *SlotID, U16 *FunID, U16 *ErrorCode, F64 *ErrorTime);	//取得所有API錯誤記錄
U16 _stdcall _ECAT_Master_Errorlog_API_Get_Single_ErrorData(U16 CardNo, U16 Count, U16 *NodeID, U16 *SlotID, U16 *FunID, U16 *ErrorCode, F64 *ErrorTime);	//取得單筆API錯誤記錄
U16 _stdcall _ECAT_Master_Errorlog_API_DumpData(U16 CardNo, char *FilePath);																//紀錄所有API檔案
U16 _stdcall _ECAT_Master_Errorlog_Status_Set_Enable(U16 CardNo, U16 Enable, U16 RecordMask);											//啟動狀態錯誤記錄功能 RecordMask 0x01:斷線紀錄 0x02:Tx-Rx Cnt是否相同 0x04:Tx出去Rx回來的時間是否超過Cycle 0x08:花費時間(OnTick)是否超過Cycle 0x10:CPU溫度是否超過正常工作範圍
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_Enable(U16 CardNo, U16* Enable, U16* RecordMask);											//取得目前狀態錯誤記錄功能設定
U16 _stdcall _ECAT_Master_Errorlog_Status_Clear(U16 CardNo);																			//清除狀態錯誤記錄
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_ErrorCnt(U16 CardNo, U16 *ErrorCnt);														//取得目前記錄的狀態錯誤筆數
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_ErrorData(U16 CardNo, U16 *ErrorCode, U16 *ErrorData, F64 *ErrorTime);					//取得所有狀態錯誤記錄
U16 _stdcall _ECAT_Master_Errorlog_Status_Get_Single_ErrorData(U16 CardNo, U16 Count, U16 *ErrorCode, U16 *ErrorData, F64 *ErrorTime);					//取得單筆狀態錯誤記錄

//======DLL資訊========
U16 _stdcall _ECAT_Master_Get_DLL_Path(I8 *lpFilePath, U32 nSize, U32 *nLength);									//讀取DLL路徑
U16 _stdcall _ECAT_Master_Get_DLL_Version(I8 *lpBuf, U32 nSize, U32 *nLength);										//讀取DLL板本
U16 _stdcall _ECAT_Master_Get_DLL_ProductVersion(I8 *lpBuf, U32 nSize, U32 *nLength);								//讀取DLL產品板本
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