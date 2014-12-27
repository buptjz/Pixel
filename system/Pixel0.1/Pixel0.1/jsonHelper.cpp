#define _CRT_SECURE_NO_WARNINGS
#include "jsonHelper.h"
#include "json/json.h"
#include <memory.h>
#include <exception>
using namespace std;

//map����ת��Ϊjson�ַ���
int map2JsonString(map<string, vector<double> > &m, string &jsonString)
{
	try
	{
		Json::Value jvalue;
		map<string, vector<double> > ::iterator it;
		for (it = m.begin(); it != m.end(); ++it)
		{
			string key = it->first;
			vector<double> value = it->second;
			for (size_t i = 0; i < value.size(); i++)
			{
				//string  num = to_string(static_cast<long double>(value[i]));
				jvalue[key].append(value[i]);
			}
		}
		// JSONת��ΪJSON�ַ������Ѹ�ʽ����
		jsonString = jvalue.toStyledString();
	}
	catch (std::exception &ex){
		printf("map2JsonString exception %s.\n", ex.what());
		return -1;
	}
	return 0;
}

//json�ַ���ת��Ϊmap
int jsonString2Map(string& jsonString, map<string, vector<double> > &m)
{
	try
	{
		bool bRet = false;
		Json::Reader reader;
		Json::Value value;
		Json::Value arrayObj;
		// JSON�ַ���ת��ΪJSON����
		bRet = reader.parse(jsonString, value);
		if (bRet == false)
		{
			printf("jsonString2Map reader parse error.\n");
			return -1;
		}
		Json::Value::Members  member = value.getMemberNames();
		for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter)
		{
			vector<double> v;
			string key = *iter;
			arrayObj = value[key];
			for (size_t i = 0; i < arrayObj.size(); i++)
			{
				v.push_back(arrayObj[i].asDouble());
			}
			m[key] = v;
		}
	}
	catch (std::exception &ex)
	{
		printf("jsonString2Map exception %s.\n", ex.what());
		return -1;
	}
	return 0;
}

//Mat�������л�Ϊjson�ַ���
int mat2jsonString(const Mat&  M, string &jsonString)
{
	try
	{
		if (M.empty()){
			return 0;
		}
		Json::Value jvalue;
		int cols = M.cols;
		int rows = M.rows;
		int chan = M.channels();
		int eSiz = (M.dataend - M.datastart) / (cols*rows*chan);
		//string temp = to_string(static_cast<long double>(cols));
	/*	jvalue["cols"] = to_string(static_cast<long double>(cols));
		jvalue["rows"] = to_string(static_cast<long double>(rows));
		jvalue["chan"] = to_string(static_cast<long double>(chan));
		jvalue["eSiz"] = to_string(static_cast<long double>(eSiz));*/
		jvalue["cols"] = cols;
		jvalue["rows"] = rows;
		jvalue["chan"] = chan;
		jvalue["eSiz"] = eSiz; 
		size_t size = cols*rows*chan*eSiz;
		char* data = new char[size+1];
		data[size] = '\0';
		if (M.isContinuous())
		{
			/*
			errno_t  err = memcpy_s(data, size + 1, (char*)M.data, size);
			if (err)
			{
				printf("mat2jsonString : Error executing memcpy_s.\n");
				return -1;
			}
			*/
			memcpy(data, (char*)M.data, size);
			//strncpy_s(data, size+1, (char*)M.data, size);
			//strncpy(data, (char*)M.data, (size_t)(cols*rows*chan*eSiz));
		}
		else
		{
			cout << "Mat is not continuous!";
			return -1;
		}
		jvalue["data"] = data;
		jsonString = jvalue.toStyledString();
	}
	catch (std::exception &ex)
	{
		printf("mat2JsonString exception %s.\n", ex.what());
		return -1;
	}
	
	return 0;
}

//json�ַ������л�ΪMat
int jsonString2Mat(string &jsonString, Mat& M)
{
	try
	{
		bool bRet = false;
		Json::Reader reader;
		Json::Value value;
		Json::Value arrayObj;
		// JSON�ַ���ת��ΪJSON����
		bRet = reader.parse(jsonString, value);
		if (bRet == false)
		{
			printf("jsonString2Mat reader parse error.\n");
			return -1;
		}
		int cols;
		int rows;
		int chan;
		int eSiz;
		string data;
		
		cols = value["cols"].asInt();
		rows = value["rows"].asInt();
		chan = value["chan"].asInt();
		eSiz = value["eSiz"].asInt();
		data = value["data"].asString();
		// Determine type of the matrix 
		int type = 0;
		switch (eSiz){
		case sizeof(char) :
			type = CV_8UC(chan);
			break;
		case sizeof(float) :
			type = CV_32FC(chan);
			break;
		case sizeof(double) :
			type = CV_64FC(chan);
			break;
		}

		// Alocate Matrix.
		M = Mat(rows, cols, type, Scalar(1));
		if (M.isContinuous())
		{
			//strncpy_s((char*)M.data, data.size()-1, data.c_str(),data.size());
			/*		
			errno_t  err =  memcpy_s((char*)M.data, data.size() - 1, data.c_str(), data.size());
			if (err)
			{
				printf("mat2jsonString : Error executing memcpy_s.\n");
				return -1;
			}
			*/
			memcpy((char*)M.data, data.c_str(), data.size()-1);
		}
	}
	catch (std::exception &ex)
	{
		printf("jsonString2Mat exception %s.\n", ex.what());
		return -1;
	}
	return 0;
}


string rect2JsonString(const Rect &rect)
{
	map<string, vector<double> > m;
	vector<double> v;
	double x = (double)rect.x;
	double y = (double)rect.y;
	double w = (double)rect.width;
	double h = (double)rect.height;
	v.push_back(x);
	v.push_back(y);
	v.push_back(w);
	v.push_back(h);
	m["position"] = v;
	string res;
	map2JsonString(m, res);
	return res;
}

Rect jsonString2Rect(string &str)
{
	map<string, vector<double> > m;
	jsonString2Map(str, m);
	vector<double> v = m["position"];
	int x = (int)v[0];
	int y = (int)v[1];
	int w = (int)v[2];
	int h = (int)v[3];
	Rect* rect = new Rect(x, y, w, h);

	return *rect;
}