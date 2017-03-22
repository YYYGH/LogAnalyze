#ifndef _ANALYZE_LOG_H_
#define _ANALYZE_LOG_H_

#include <vector>
#include <fstream> 
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <clocale>
#include <algorithm>
using namespace std;

#ifdef _WIN32
#include <ctime> //win32下的头文件
#include <windows.h>
#include<winnls.h>
#endif

#ifdef linux
#include <sys/time.h>  //Linux下的头文件
#include <unistd.h>
#endif


using namespace std;


struct LocalTime;
class KAnalyzeLog;
struct LogInformation;
struct LocalTime
{
	int				year;
	int				month;
	int				day;
	int				hour;
	int				minute;
	int				second;
};
class KAnalyzeLog
{
public:
	KAnalyzeLog();
	~KAnalyzeLog();

	void						OutPut(KAnalyzeLog *pAnalyze, int iIndex);//输出结果
	int							InPut();//输入内容
	int							InsertNewType(char* type);//插入新类型
	int							Search();//硬盘查找字符串
	char*						GetInPutTypeFirst(char *destiation);//第一次获取输入字符串类型
	char*						GetInPutTypeLast(KAnalyzeLog *pAnalyze, char* Source, char *destiation);//最后一次获取类型
	void						StringToInt(KAnalyzeLog *pAnalyze, char* Source);//把时间字符串转换成数字
	//输出 
	char*						DeleteFirstEmpty(KAnalyzeLog *pAnalyze, char* Source);//如果字符串首位置字符是空格则去除空格
	char*						DeleteLastEmpty(KAnalyzeLog *pAnalyze, char* Source);
	wchar_t*					DeleteWLastEmpty(KAnalyzeLog *pAnalyze, wchar_t* Source);
	wchar_t*					DeleteWFirstEmpty(KAnalyzeLog *pAnalyze, wchar_t *Source);
	char*						GetProcessId(KAnalyzeLog *pAnalyze);//#进程
	char*						GetLocalTime(KAnalyzeLog *pAnalyze);//获取本地时间
	char*						LocalTimetoUTC(KAnalyzeLog *pAnalyze);//本地时间转UTC时间
	char*						GetLogType(KAnalyzeLog *pAnalyze, int iIndex);//日志类型
	char*						GetLogName(KAnalyzeLog *pAnalyze, int iIndex);//名称 
	char*						GetTime(KAnalyzeLog *pAnalyze);//时间
	char*						GetCount(KAnalyzeLog *pAnalyze);//总次数
	char*						GetMax(KAnalyzeLog *pAnalyze);//最大
	char*						GetMin(KAnalyzeLog *pAnalyze);//最小
	char*						GetTotal(KAnalyzeLog *pAnalyze);//获取总数
	char*						GetDelay(KAnalyzeLog *pAnalyze);//获取延时
	char*						GetPlayerCostTime(KAnalyzeLog *pAnalyze);
	char*						GetNpc(KAnalyzeLog *pAnalyze);
	char*						GetAIType(KAnalyzeLog *pAnalyze);
	char*						GetActionKey(KAnalyzeLog *pAnalyze);
	char*						GetGameLoop(KAnalyzeLog *pAnalyze);
	char*						GetAIScriptID(KAnalyzeLog *pAnalyze);
	char*						GetAIEvent(KAnalyzeLog *pAnalyze);
	char*						GetState(KAnalyzeLog *pAnalyze);
	char*						GetRegion(KAnalyzeLog *pAnalyze);
	char*						GetregionTime(KAnalyzeLog *pAnalyze);
	char*						GetPlayer(KAnalyzeLog *pAnalyze);
	char*						GetFunction(KAnalyzeLog *pAnalyze);
	char*						GetScript(KAnalyzeLog *pAnalyze);
	char*						GetString(KAnalyzeLog *pAnalyze);
	char*						GetServer(KAnalyzeLog *pAnalyze);
	char*						GetWhy(KAnalyzeLog *pAnalyze);
	char*						DeleteLastZero(KAnalyzeLog *pAnalyze, char *Source);
	char*						GetMap(KAnalyzeLog *pAnalyze);
	char*						GetSubMap(KAnalyzeLog *pAnalyze);
	char*						GetLineNumber(KAnalyzeLog *pAnalyze);
	void						Test(KAnalyzeLog * pAnalyze, char *Source);

private:
	char*						m_InPutString;
	char*						m_Search;
	vector<char*>				m_LogType;
	LocalTime					LOCAL_TIME;
	char*						m_LogInformation;
	tm							TM;
	char*						sTypeFirst;
	char*						sTypeLast;
};

#endif
