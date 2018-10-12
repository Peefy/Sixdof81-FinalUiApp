
#ifndef COMMUNICATION_H_  
#define COMMUNICATION_H_  

#include <stdint.h>
#include <vector>
#include <string>

#include "SerialPort.h"

#define PI 3.1415926

//限位函数
#define RANGE(x,min,max)   (((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

#define HAEDER_ONE 'p'
#define HEADER_TWO 146

#define HEADER_COMMAND 0xAA

#define DEFAULT_POLE_LENGTH 0.25
#define POLE_COUNT 6

#define HOW_TO_STOP 0
#define HOW_TO_START 1
#define HOW_TO_RESET 2

#define BIT_CLEAN(var,n)        (var) &= ~(1<<(n))   
#define BIT_SET(var,n)          (var) |=  (1<<(n))   
#define BIT_GET(var,n)          (((var)>>(n))&0x01)  
#define BIT_SETval(var,n,val)   ( ((val) == (1)) ? BIT_SET(var,n) : BIT_CLEAN(var,n) )

#define SIN_INFO_T_DELTA 0.2

typedef enum
{
	COMMAND_RISE = 11,
	COMMAND_MIDDLE = 22,
	COMMAND_DOWN = 33,
}CommandType;

typedef struct 
{
	//单位0.1mm
    int16_t X;
	//单位0.1mm
    int16_t Y;
	//单位0.1mm
    int16_t Z;
	//单位0.01度
    int16_t Yaw;
	//单位0.01度
    int16_t Roll;
	//单位0.01度
    int16_t Pitch;
	//单位mm/s
    int16_t XYZSpeed;
	//单位0.1度/s
    int16_t AngleSpeed;
	byte ConsoleInitial;
	byte Reserved;
	byte CmdPcDataAck;
	byte Function;
	int16_t Crc;
	//byte Tail;
}DataPackage;

typedef struct
{
	byte Header;
	byte CommandType;
}ControlCommand;

void ResetDefaultData(DataPackage * data);
void ResetDefaultData(void);
void PrintDataPackageToString(DataPackage data);

typedef union
{
    DataPackage Data;
    unsigned char Buffers[sizeof(DataPackage)];
}ComPackage;

__interface ITranslate
{
public:
    DataPackage ProviedInfo();
    bool SendInfo(DataPackage data);
    bool Start();
    bool Stop();
};

extern DataPackage Default;
extern double DefaultPoleLength[POLE_COUNT];

    class Translate : public ITranslate
    {
    public:
        Translate();
        ~Translate();
                 
        virtual DataPackage ProviedInfo();
        virtual bool SendInfo(DataPackage data);
        virtual bool Start();
        virtual bool Stop();

        bool IsRecievedData;
		bool isStart;

		DataPackage ProviedTestSinInfo(double t);
		DataPackage ProviedTestSingleAxesSinInfo(double f, double t);
		DataPackage ProviedTestMultiAxesAxesSinInfo(double * val, double * hz);
		DataPackage ProviedTestMultiAxesAxesSinInfo(double * val, double * hz, double delta);

		double SinInfoT;

    private:
        UINT8 buffers[sizeof(DataPackage)];
        CSerialPort* serialPort;
        DataPackage recivedData;
        UINT32 pakageLength;
        UINT32 dataLength;
        INT32 status;       
        bool openPort();
        bool openPort(int i, int baud);
        bool closePort();
    };

#endif

