#ifndef JSONHELPER_H
#define JSONHELPER_H
/*
#include "json/json.h"
#include <map>
#include <string.h>
#include <memory.h>
#include <exception>
#include <string>
using namespace std;
//map����ת��Ϊjson�ַ���
int map2JsonString(map<string, vector<double> > m, char *pJasonData)
{
	try
	{
		Json::Value jvalue;
		map<string, vector<double> > ::iterator it;
		for (it = m.begin(); it != m.end(); ++it)
		{
			string key = it->first;
			vector<double> value = it->second;
			for (int i = 0; i < value.size(); i++)
			{
				string  num = to_string(value[i]);
				jvalue[key].append(num);
			}
		}
		// JSONת��ΪJSON�ַ������Ѹ�ʽ����
		std::string strOut = jvalue.toStyledString();
		strcpy(pJsonData, strOut.c_str());
	}
	catch (std::exception &ex){
		printf("map2JsonString exception %s.\n", ex.what());
		return -1;
	}
	return 0;
}

//json�ַ���ת��Ϊmap
int jsonString2Map(char *pJsonData, map<string, vector<double> > m)
{
	try
	{
		bool bRet = false;
		Json::Reader read;
		Json::Value value;
		// JSON�ַ���ת��ΪJSON����
		bRet = reader.parse(pJsonData, value);
		if (bRet == false)
		{
			printf("jsonString2Map reader parse error.\n");
			return -1;
		}

		Json:Value::Members member = value.getMemberNames();
		for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter) 
		{
			cout << (*iter) << endl; 
		}
	}
	catch (std::exception &ex)
	{
		printf("jsonString2Map exception %s.\n", ex.what());
		return -1;
	}
	return 0;
}
*/
#endif