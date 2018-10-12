
#include "stdafx.h"
#include "inihelper.h"

#include "../json/json.h"
#include "../json/reader.h"
#include "../json/writer.h"

#define JSON_FILE_NAME "config.json"
#define JSON_STOP_AND_MIDDLE_KEY "stopAndMiddle"

#define FILE_NAME "config.ini"
#define RECORD_FILE_NAME "record.txt"
#define RECORD_DOUBLE_FILE_NAME "recorddouble.txt"
#define DUGU_CONFIG_NAME "duguconfig.ini"
#define SERIALPORT_APPNAME "serialport"
#define SERIALPORT_BAUD_KEY  "baudrate"
#define SERIALPORT_ISUSE_KEY "isuse"

#define DEFAULT_SERIAL_BAUD     57600
#define DEFAULT_SERIAL_BAUD_STR  "57600"
#define DEFAULT_SERIAL_ISUSE_STR  true
#define DEFAULT_PORT_NUM 1

#define DEFAULT_LENGTH_TO_PULSE_SCALE 40000

using namespace std;

namespace config {

    void ReadAll(bool& result, int& baud, int& portnum)
    {
        ifstream fin(FILE_NAME);
        fin >> result;
        fin >> baud;
        fin >> portnum;
        fin.close();
    }

    void GenerateDefaultConfigFile()
    {
        ofstream fout(FILE_NAME);
        fout << DEFAULT_SERIAL_ISUSE_STR << endl;
        fout << DEFAULT_SERIAL_BAUD << endl;
        fout << DEFAULT_PORT_NUM << endl;
		fout << DEFAULT_LENGTH_TO_PULSE_SCALE << endl;
        fout.flush();
        fout.close();
    }

	int ReadScale()
	{
		bool result; int baud; int portnum;
		int scale = DEFAULT_LENGTH_TO_PULSE_SCALE;
		ifstream fin(FILE_NAME);
		fin >> result;
		fin >> baud;
		fin >> portnum;
		fin >> scale;
		fin.close();
		return scale;
	}

	void RecordStatusAndPulse(char* status, int statusInt, I32* pulse)
	{
		try
		{
			ofstream fout(RECORD_FILE_NAME);
			fout << (int)statusInt << endl;
			fout << pulse[0] << endl;
			fout << pulse[1] << endl;
			fout << pulse[2] << endl;
			fout << pulse[3] << endl;
			fout << pulse[4] << endl;
			fout << pulse[5] << endl;
			fout.flush();
			fout.close();
		}
		catch (exception& ex)
		{

		}
	}

	void RecordStatusAndPulse(char* status, int statusInt, double* pulse)
	{
		try
		{
			ofstream fout(RECORD_DOUBLE_FILE_NAME);
			fout << (int)statusInt << endl;
			fout << pulse[0] << endl;
			fout << pulse[1] << endl;
			fout << pulse[2] << endl;
			fout << pulse[3] << endl;
			fout << pulse[4] << endl;
			fout << pulse[5] << endl;
			fout.flush();
			fout.close();
		}
		catch (exception& ex)
		{

		}
	}

	void ReadStatusAndPulse(int& statusInt, I32* pulse)
	{
		try
		{
			ifstream fin(RECORD_DOUBLE_FILE_NAME);
			fin >> statusInt;
			fin >> pulse[0];
			fin >> pulse[1];
			fin >> pulse[2];
			fin >> pulse[3];
			fin >> pulse[4];
			fin >> pulse[5];
			fin.close();
		}
		catch (exception& ex)
		{

		}
	}

	void ReadStatusAndPulse(int& statusInt, double* pulse)
	{
		try
		{
			ifstream fin(RECORD_FILE_NAME);
			fin >> statusInt;
			fin >> pulse[0];
			fin >> pulse[1];
			fin >> pulse[2];
			fin >> pulse[3];
			fin >> pulse[4];
			fin >> pulse[5];
			fin.close();
		}
		catch (exception& ex)
		{

		}
	}

	template<typename T>
	T ParseJsonFromFile(const char* filename, const char* key)
	{
		// 解析json用Json::Reader   
		Json::Reader reader;
		// Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array...   
		Json::Value root;

		std::ifstream is;
		is.open(filename, std::ios::binary);
		JSONCPP_STRING doc;
		std::getline(is, doc, (char)EOF);
		doc.replace(doc.begin(), doc.begin() + 3, "");
		if (reader.parse(doc.c_str(), root))
		{
			Json::Value val;
			val = root.get(key, NULL);
			if (std::is_same<T, bool>::value)
				return val.asBool();
			else if (std::is_same<T, int>::value)
				return val.asInt();
			else if (std::is_same<T, double>::value)
				return val.asDouble();
			else
				return NULL;
		}
		is.close();
		return NULL;
	}

	bool ReadIsAutoStopAndMiddle()
	{
		auto result = ParseJsonFromFile<bool>(JSON_FILE_NAME, JSON_STOP_AND_MIDDLE_KEY);
		if (result == NULL)
			return true;
		return result;
	}

}


