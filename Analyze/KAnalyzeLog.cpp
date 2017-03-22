#include "KAnalyzeLog.h"

KAnalyzeLog::KAnalyzeLog()
{
	this->m_InPutString = new char[1024];
	this->m_Search = new char[1024];
	this->sTypeFirst = new char[512];
	this->sTypeLast = new char[512];
	memset(this->m_InPutString, 0, 1024);
	memset(this->m_Search, 0, 1024);
	memset(this->sTypeFirst, 0, 512);
	memset(this->sTypeLast, 0, 512);
	this->LOCAL_TIME.year = 0;
	this->LOCAL_TIME.month = 0;
	this->LOCAL_TIME.day = 0;
	this->LOCAL_TIME.hour = 0;
	this->LOCAL_TIME.minute = 0;
	this->LOCAL_TIME.second = 0;
	this->m_LogInformation = new char[1024];
	memset(this->m_LogInformation, 0, 1024);
	char pstr1[] = "C2S RemoteLua";
	char pstr2[] = "R2S RemoteLua";
	char pstr3[] = "Main.C2S";
	char pstr4[] = "Main.World";
	char pstr5[] = "C2S_";
	char pstr6[] = "R2S_";
	char pstr7[] = "Main";
	this->m_LogType.push_back(pstr1);
	this->m_LogType.push_back(pstr2);
	this->m_LogType.push_back(pstr3);
	this->m_LogType.push_back(pstr4);
	this->m_LogType.push_back(pstr5);
	this->m_LogType.push_back(pstr6);
	this->m_LogType.push_back(pstr7);
}

KAnalyzeLog::~KAnalyzeLog()
{
	delete m_InPutString;
	delete m_Search;
	delete m_LogInformation;
	delete sTypeFirst;
	delete sTypeLast;
}

void KAnalyzeLog::OutPut(KAnalyzeLog *pAnalyze, int iIndex)//输出结果
{
	if (pAnalyze != nullptr && pAnalyze->m_Search != nullptr)
	{
		char* ProcessId = pAnalyze->GetProcessId(pAnalyze);
		char *type = pAnalyze->GetLogType(pAnalyze, iIndex);
		char type_str[1024];
		memset(type_str, 0, 1024);
		if (ProcessId != nullptr && *ProcessId != '\0' && type != nullptr)
		{// "host": "23.66kuozhan_gate0210",
			char* processid = pAnalyze->GetProcessId(pAnalyze);
			cout << '{' << flush;
			processid = pAnalyze->DeleteFirstEmpty(pAnalyze, processid);
			processid = pAnalyze->DeleteLastEmpty(pAnalyze, processid);
			cout << "\"host\": \""<<processid << '"'<<flush;
			
			char *LogType = pAnalyze->GetLogType(pAnalyze, iIndex);
			if (LogType != nullptr && *LogType != '\0')
			{
				LogType = pAnalyze->DeleteFirstEmpty(pAnalyze, LogType);
				LogType = pAnalyze->DeleteLastEmpty(pAnalyze, LogType);
			}
			strcpy(type_str, LogType);//保存当前类型
			cout << ", \"type\": \"" << LogType << '"' << flush;

			char *LogName = pAnalyze->GetLogName(pAnalyze, iIndex);
			if (LogName != nullptr && *LogName != '\0')
			{
				LogName = pAnalyze->DeleteFirstEmpty(pAnalyze, LogName);
				LogName = pAnalyze->DeleteLastEmpty(pAnalyze, LogName);
				cout << ", \"what\": \"" << LogName << '"' << flush;
			}
			char* pLocalTime = pAnalyze->GetLocalTime(pAnalyze);
			pAnalyze->StringToInt(pAnalyze, pLocalTime);
			char *UTC = pAnalyze->LocalTimetoUTC(pAnalyze);
			char *utc = pAnalyze->DeleteFirstEmpty(pAnalyze, UTC);
			if (utc != nullptr && *utc != '\0')
			{
				utc = pAnalyze->DeleteFirstEmpty(pAnalyze, utc);
				utc = pAnalyze->DeleteLastEmpty(pAnalyze, utc);
			
				if (*utc >= '0' && *utc <= '9')
				{
					cout << ", \"@timestamp\": \"" << utc << '"' << flush;
				}
				free(UTC);
			}
			char* Time = pAnalyze->GetTime(pAnalyze);
		//	char* time2 = pAnalyze->DeleteFirstEmpty(pAnalyze, Time);
				
			if (Time != nullptr && *Time != '\0')
			{
				Time = pAnalyze->DeleteFirstEmpty(pAnalyze, Time);
				Time = pAnalyze->DeleteLastEmpty(pAnalyze, Time);
				Time = pAnalyze->DeleteLastZero(pAnalyze, Time);
				if (*Time >= '0' && *Time <= '9')
				{
					//**************************************************
					//char ch = '.';
					if (strstr(Time, "."))
					{
						cout << ", \"time\": " << Time << flush;
					}
					else
					{
						cout << ", \"time\": " << Time <<".0"<< flush;
					}
				
				}
			}
			char* nCount = pAnalyze->GetCount(pAnalyze);
			//char* count = pAnalyze->DeleteFirstEmpty(pAnalyze, nCount);
			if (nCount != nullptr && *nCount != '\0')
			{
				
				nCount = pAnalyze->DeleteFirstEmpty(pAnalyze, nCount);
				nCount = pAnalyze->DeleteLastEmpty(pAnalyze,nCount);
				if (*nCount >= '0' && *nCount <= '9')
				{
					cout << ", \"count\": " << nCount << flush;
				}
			}
			char* Total = pAnalyze->GetTotal(pAnalyze);
			//char *total = pAnalyze->DeleteFirstEmpty(pAnalyze, Total);
			if (Total != nullptr && *Total != '\0')
			{
			
				Total = pAnalyze->DeleteFirstEmpty(pAnalyze, Total);
				Total = pAnalyze->DeleteLastEmpty(pAnalyze,Total);
				Total = pAnalyze->DeleteLastZero(pAnalyze, Total);
				//\*********************************************
				char _str1[1024]="sceneprof";
				int result = strcmp(type_str, _str1);
				if (result == 0)
				{
					if (*Total >= '0' && *Total <= '9')
					{
						cout << ", \"totaltime\": " << Total << flush;
					}
				}
				else
				{
					if (*Total >= '0' && *Total <= '9')
					{
						cout << ", \"total\": " << Total << flush;
					}
				}
			}
			char* Max = pAnalyze->GetMax(pAnalyze);
			char*max = pAnalyze->DeleteFirstEmpty(pAnalyze, Max);
			
			if (max != nullptr && *max != '\0')
			{
				
				max = pAnalyze->DeleteFirstEmpty(pAnalyze, max);
				max = pAnalyze->DeleteLastEmpty(pAnalyze, max);
				max = pAnalyze->DeleteLastZero(pAnalyze, max);
				if (*max >= '0' && *max <= '9')
				{
					cout << ", \"max\": " << max << flush;
				}
			}
			char* Min = pAnalyze->GetMin(pAnalyze);
			char*min = pAnalyze->DeleteFirstEmpty(pAnalyze, Min);
			
			if (min != nullptr && *min != '\0')
			{
				min = pAnalyze->DeleteFirstEmpty(pAnalyze, min);
				min = pAnalyze->DeleteLastEmpty(pAnalyze, min);
				min = pAnalyze->DeleteLastZero(pAnalyze, min);
				if (*min >= '0' && *min <= '9')
				{
					cout << ", \"min\": " << min << flush;
				}
			}
			char *delay = pAnalyze->GetDelay(pAnalyze);
				
			if (delay != nullptr && *delay != '\0')
			{
				delay = pAnalyze->DeleteFirstEmpty(pAnalyze, delay);
				delay = pAnalyze->DeleteLastEmpty(pAnalyze, delay);
				delay = pAnalyze->DeleteLastZero(pAnalyze, delay);
				cout << ", \"time\": " << delay << flush;
			}
			char *playerCost = pAnalyze->GetPlayerCostTime(pAnalyze);
				
			if (playerCost != nullptr && *playerCost != '\0')
			{
		
				playerCost = pAnalyze->DeleteFirstEmpty(pAnalyze, playerCost);
				playerCost = pAnalyze->DeleteLastEmpty(pAnalyze,playerCost);
				playerCost = pAnalyze->DeleteLastZero(pAnalyze, playerCost);
				if (strstr(this->m_Search, "[ScriptCost]"))
				{
					cout << ", \"time\": " << playerCost << flush;
				}
				else
				{
					cout << ", \"player\": " << playerCost << flush;
				}
			}
			char *Npc = pAnalyze->GetNpc(pAnalyze);
			if (Npc != nullptr && *Npc != '\0')
			{
				Npc = pAnalyze->DeleteFirstEmpty(pAnalyze, Npc);
				Npc = pAnalyze->DeleteLastEmpty(pAnalyze, Npc);
				Npc = pAnalyze->DeleteLastZero(pAnalyze, Npc);
				cout << ", \"npc\": " << Npc << flush;
			}
			char *AItype = pAnalyze->GetAIType(pAnalyze);
			if (AItype != nullptr && *AItype != '\0')
			{
				AItype = pAnalyze->DeleteFirstEmpty(pAnalyze, AItype);
				AItype = pAnalyze->DeleteLastEmpty(pAnalyze, AItype);
				AItype = pAnalyze->DeleteLastZero(pAnalyze, AItype);
				cout << ", \"aitype\": \"" << AItype << '"' << flush;
			}
			char *ActionKey = pAnalyze->GetActionKey(pAnalyze);
			if (ActionKey != nullptr && *ActionKey != '\0')
			{
				ActionKey = pAnalyze->DeleteFirstEmpty(pAnalyze, ActionKey);
				ActionKey = pAnalyze->DeleteLastEmpty(pAnalyze, ActionKey);
				ActionKey = pAnalyze->DeleteLastZero(pAnalyze, ActionKey);
				cout << ", \"aiactionkey\": \"" << ActionKey << '"' << flush;
			}

			char*GameLoop = pAnalyze->GetGameLoop(pAnalyze);
			if (GameLoop != nullptr && *GameLoop != '\0')
			{
				GameLoop = pAnalyze->DeleteFirstEmpty(pAnalyze, GameLoop);
				GameLoop = pAnalyze->DeleteLastEmpty(pAnalyze, GameLoop);
				GameLoop = pAnalyze->DeleteLastZero(pAnalyze, GameLoop);
				cout << ", \"gameloop\": \"" << GameLoop << '"' << flush;
			}
			char *AIScriptID = pAnalyze->GetAIScriptID(pAnalyze);
			
			if (AIScriptID != nullptr && *AIScriptID != '\0')
			{
				AIScriptID = pAnalyze->DeleteFirstEmpty(pAnalyze, AIScriptID);
				AIScriptID = pAnalyze->DeleteLastEmpty(pAnalyze, AIScriptID);
				AIScriptID = pAnalyze->DeleteLastZero(pAnalyze, AIScriptID);
				cout << ", \"aiscriptid\": \"" << AIScriptID << '"' << flush;
			}

			//***********************************************************
			char *AIEvent = pAnalyze->GetAIEvent(pAnalyze);
			
			if (AIEvent != nullptr && *AIEvent != '\0')
			{	
				AIEvent = pAnalyze->DeleteFirstEmpty(pAnalyze, AIEvent);
				AIEvent = pAnalyze->DeleteLastEmpty(pAnalyze, AIEvent);
				AIEvent = pAnalyze->DeleteLastZero(pAnalyze, AIEvent);
				cout << ", \"aievent\": \"" << AIEvent << '"' << flush;
			}
			char *State = pAnalyze->GetState(pAnalyze);
				
			if (State != nullptr && *State != '\0')
			{
				State = pAnalyze->DeleteFirstEmpty(pAnalyze, State);
				State = pAnalyze->DeleteLastEmpty(pAnalyze, State);
				State = pAnalyze->DeleteLastZero(pAnalyze, State);
				cout << ", \"aistate\": \"" << State << '"' << flush;
			}
			char *Region = pAnalyze->GetRegion(pAnalyze);
			
			if (Region != nullptr && *Region != '\0')
			{
				Region = pAnalyze->DeleteFirstEmpty(pAnalyze, Region);
				Region = pAnalyze->DeleteLastEmpty(pAnalyze,Region);
				Region = pAnalyze->DeleteLastZero(pAnalyze, Region);
				cout << ", \"region\": \"" << Region << '"' << flush;
			}
			char *regionTime = pAnalyze->GetregionTime(pAnalyze);
			
			if (regionTime != nullptr && *regionTime != '\0')
			{
				regionTime = pAnalyze->DeleteFirstEmpty(pAnalyze, regionTime);
				regionTime = pAnalyze->DeleteLastEmpty(pAnalyze, regionTime);
				regionTime = pAnalyze->DeleteLastZero(pAnalyze, regionTime);
				cout << ", \"regiontime\": " << regionTime << flush;
			}
			char *Player = pAnalyze->GetPlayer(pAnalyze);
			
			if (Player != nullptr && *Player != '\0')
			{
				Player = pAnalyze->DeleteFirstEmpty(pAnalyze, Player);
				Player = pAnalyze->DeleteLastEmpty(pAnalyze, Player);
				Player = pAnalyze->DeleteLastZero(pAnalyze, Player);
				cout << ", \"player\": " << Player << flush;
			}
			char *Function = pAnalyze->GetFunction(pAnalyze);
			
			if (Function != nullptr && *Function != '\0')
			{
				Function = pAnalyze->DeleteFirstEmpty(pAnalyze, Function);
				Function = pAnalyze->DeleteLastEmpty(pAnalyze, Function);
				cout << ", \"function\": \"" << Function << '"' << flush;
			}

			char *Script = pAnalyze->GetScript(pAnalyze);
			if (Script)
			{
#ifdef _WIN32
				int len = MultiByteToWideChar(CP_UTF8, 0, Script, -1, NULL, 0);
				if (len == 0) {
					cout << "shibai" << endl;
				}
				wchar_t * pwBuf = new wchar_t[len * 2 + 1];
				wmemset(pwBuf, 0, len * 2 + 1);
				MultiByteToWideChar(CP_UTF8, 0, Script, -1, pwBuf, len);
				setlocale(0, "chs");
				if (pwBuf && *pwBuf != '\0')
				{
					pwBuf = pAnalyze->DeleteWFirstEmpty(pAnalyze, pwBuf);
					pwBuf = pAnalyze->DeleteWLastEmpty(pAnalyze, pwBuf);
					wprintf(L", \"script\": \"%ls\"", pwBuf);
				}
				delete pwBuf;
#else
				Script = pAnalyze->DeleteFirstEmpty(pAnalyze, Script);
				Script = pAnalyze->DeleteLastEmpty(pAnalyze, Script);
				cout << ", \"script\": \"" << Script << '"' << flush;

#endif
			//	if (Script != nullptr && *Script != '\0')
			//	{
			//		cout << ", \"script\": \"" << Script << '"' << flush;
			//	}
			}
			char *string = pAnalyze->GetString(pAnalyze);
			if (string)
			{
#ifdef _WIN32
				int len = MultiByteToWideChar(CP_UTF8, 0, string, -1, NULL, 0);
				if (len == 0) {
					cout << "shibai" << endl;
				}
				wchar_t * pwBuf = new wchar_t[len * 2 + 1];
				wmemset(pwBuf, 0, len * 2 + 1);
				MultiByteToWideChar(CP_UTF8, 0, string, -1, pwBuf, len);
				setlocale(0, "chs");
				if (pwBuf && *pwBuf != '\0')
				{
					pwBuf = pAnalyze->DeleteWFirstEmpty(pAnalyze, pwBuf);
					pwBuf = pAnalyze->DeleteWLastEmpty(pAnalyze, pwBuf);
					wprintf(L", \"file\": \"string \\\"%ls\\\"\"", pwBuf);//, "file": "string \"pwbuf\" "
				}
				delete pwBuf;
#else
				string = pAnalyze->DeleteFirstEmpty(pAnalyze, string);
				string = pAnalyze->DeleteLastEmpty(pAnalyze, string);
				cout << ", \"file\": \"string \\\"" << string << "\\\"\"" << flush;
#endif
			}
			char *why = pAnalyze->GetWhy(pAnalyze);
			if (why != nullptr && *why != '\0')
			{
				why = pAnalyze->DeleteFirstEmpty(pAnalyze, why);
				why = pAnalyze->DeleteLastEmpty(pAnalyze, why);
				cout << ", \"why\": \"" << why << '"' << flush;
			}
			char *line = pAnalyze->GetLineNumber(pAnalyze);
			if (line != nullptr && *line != '\0')
			{
				line = pAnalyze->DeleteFirstEmpty(pAnalyze, line);
				line = pAnalyze->DeleteLastEmpty(pAnalyze, line);
				cout << ", \"line\": \"" << line << '"' << flush;
			}
			char *map = pAnalyze->GetMap(pAnalyze);
			if (map != nullptr && *map != '\0')
			{
				map = pAnalyze->DeleteFirstEmpty(pAnalyze, map);
				map = pAnalyze->DeleteLastEmpty(pAnalyze, map);
				map = pAnalyze->DeleteLastZero(pAnalyze, map);
				cout << ", \"map\": \"" << map << '"' << flush;
			}
			char *Submap = pAnalyze->GetSubMap(pAnalyze);
			if (Submap != nullptr && *Submap != '\0')
			{
				Submap = pAnalyze->DeleteFirstEmpty(pAnalyze, Submap);
				Submap = pAnalyze->DeleteLastEmpty(pAnalyze, Submap);
				Submap = pAnalyze->DeleteLastZero(pAnalyze, Submap);
				cout << ", \"submap\": \"" << Submap << '"' << flush;
			}
			char *server = pAnalyze->GetServer(pAnalyze);
			if (server != nullptr && *server != '\0')
			{
				server = pAnalyze->DeleteFirstEmpty(pAnalyze, server);
				server = pAnalyze->DeleteLastEmpty(pAnalyze,server);
				cout << ", \"server\": \"" << server << '"' << flush;
			}
			cout << ", \"@version\": \"1\"}" << endl;
		}
	}
}

int KAnalyzeLog::InPut()//输入内容
{
	int nResult = 0;
	memset(sTypeFirst, 0, 512);
	memset(this->m_InPutString, 0, 1024);
	memset(sTypeLast, 0, 512);
//	cout << "请输入需要查找的内容：" << endl;
	//gets_s(this->m_InPutString,1024);
	if (cin.peek() == EOF)
	{
		//cout << "结束" << endl;
		exit(0);
	}
	cin.getline(m_InPutString, 1024);
	//fgets(this->m_InPutString, 1024, stdin);
	int length = strlen(this->m_InPutString);
	strncpy(m_Search, m_InPutString, length);
	m_Search[length] = '\0';
	char *pstr1 = this->GetInPutTypeFirst(sTypeFirst);
	if (pstr1 == nullptr)
	{
	//	cout << "InPut Error" << endl;
		return -1;
	}
	char *pstr2 = this->GetInPutTypeLast(this, pstr1,sTypeLast);
	if (pstr2)
	{
		while (true)//不断循环保证去除第一个非空格符之前的所有空格
		{
			if (*pstr2 == ' ')
			{
				pstr2 = this->DeleteFirstEmpty(this, pstr2);
			}
			else
			{
				break;
			}
		}
		nResult = this->InsertNewType(pstr2);
		return nResult;//返回新插入元素的下标
	}
	else
	{
		memset(sTypeFirst, 0, 512);
		memset(sTypeLast, 0, 512);
		memset(this->m_InPutString, 0, 1024);
		return -1;
	}
}

int KAnalyzeLog::InsertNewType(char* type)//插入次新类型//手工分类
{
	char *pstr = type;
	vector<char *>::iterator it ;
	it = find(this->m_LogType.begin(),this->m_LogType.end(),pstr);
	if (it != m_LogType.end())
	{
		int index = it - this->m_LogType.begin();//计算元素所在下标
		return index;
	}
	else
	{
		this->m_LogType.push_back(type);
		int length = this->m_LogType.size();
		return length - 1; 
	}
}

char* KAnalyzeLog::GetInPutTypeFirst(char *destination)//获取输入字符串类型
{
	if (m_InPutString)
	{
		if (strstr(m_InPutString, "Frame") && strstr(m_InPutString, "Delay"))
		{
			char str[] = "Frame";
			strncpy(destination, str, strlen(str));//拷贝类型
			destination[strlen(str)] = '\0';
			return destination;
		}
		else if (strstr(m_InPutString, "[Lua]") && strstr(m_InPutString, "function"))
		{
			char str[] = "function";
			strncpy(destination, str, strlen(str));//拷贝类型
			destination[strlen(str)] = '\0';
			return destination;
		}
		char *pstr1 = m_InPutString;
		char*pstr2 = m_InPutString;
		//-223847<INFO :0xd6179b40>: Shutdown connection: 202
		while (pstr1++ && *pstr1 != '\0')
		{
			if (*pstr1 == '>' && *(pstr1 + 1) == ':')
			{
				pstr2 = pstr1 + 2;
				while (pstr2++ && *pstr2 != '\0')
				{
					if (*pstr2 == ':')
					{
//23.66kuozhan-gate0210_gm01_2017_02_21/SO3GameServer_2017_02_21_01_04_02.log 20170221-015159<INFO :0xf733e700>: [PROF] Frame(837082) Cost 25ms
						strncpy(destination, pstr1 + 2, pstr2 - (pstr1 + 2));//拷贝类型
						return destination;
					}
				}
				if (*pstr2 == '\0')
				{
					return nullptr;
				}
				break;
			}
		}
		if (*pstr1 == '\0')
		{
			return nullptr;
		}
	}
	return nullptr;
}

char* KAnalyzeLog::GetInPutTypeLast(KAnalyzeLog *pAnalyze, char* Source, char *destination)//最后一次获取类型
{
	if (Source)
	{//: [PROF]   Main.World: total 18.97ms, max 18.97ms, min 18.97ms.
		if (strstr(m_InPutString, "Frame") && strstr(m_InPutString, "Delay"))
		{
			char str[] = "Delay";
			strncpy(destination, str, strlen(str));//拷贝类型
			destination[strlen(str)] = '\0';
			return destination;
		}
		else if (strstr(m_InPutString, "[Lua]") && strstr(m_InPutString, "function"))
		{
			char str[] = "[Lua]";
			strncpy(destination, str, strlen(str));//拷贝类型
			destination[strlen(str)] = '\0';
			return destination;
		}
		char* pstr1 = Source;
		char* pstr2 = nullptr;
		char* pstr3 = destination;
		while (pstr1 && *pstr1 != '\0')
		{
			if (*pstr1 == '[')
			{
				pstr2 = pstr1 + 1;
				while (pstr2++ && *pstr2 != '\0')
				{
					if (*pstr2 == ']')
					{
						pstr2++;
						strcpy(destination, pstr2);
					//	cout <<"*************" <<destination << endl;
						return pstr3;
					}
				}
				if (*pstr2 == '\0')//字符串只有左括号没有右括号，不是所需类型
				{
					return nullptr;
				}
			}
			pstr1++;
		}
		if (*pstr1 == '\0')
		{
			return nullptr;
		}
	}
	return nullptr;
}

int KAnalyzeLog::Search()//查找字符串
{
	int iIndex = this->InPut();
	if (iIndex < 0)
	{
		return -1;
	}
	else
	{
		if (strstr(this->m_Search, "Frame") && strstr(this->m_Search, "Cost"))
		{
			return -1;
		}
		else if (strstr(this->m_Search, "CasterID") && strstr(this->m_Search, "BuffID") && strstr(this->m_Search, "ErrorID"))
		{
			return -1;
		}
		else if (strstr(this->m_Search, "[Lua]") && (!strstr(this->m_Search, "Failed")) && (!strstr(this->m_Search, "function")))
		{
			return -1;
		}
		else if (strstr(this->m_Search, this->m_LogType[iIndex]))//如果找到所需字符串
		{
			this->OutPut(this, iIndex);
			return 0;
		}
		return -1;
	}
}

char* KAnalyzeLog::GetProcessId(KAnalyzeLog *pAnalyze)//#进程
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = pAnalyze->m_Search;
	char *pstr2 = pAnalyze->m_Search;
	//23.66kuozhan - gate0210_gm18_2017_02_21 
	if (strstr(pAnalyze->m_Search, "Delay") && strstr(pAnalyze->m_Search, "Delay"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "min") && strstr(pAnalyze->m_Search, "max"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "total") && strstr(pAnalyze->m_Search, "max"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "Time") && strstr(pAnalyze->m_Search, "nCount"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "Player CostTime") && strstr(pAnalyze->m_Search, "Npc CostTime"))
	{
		while (pstr2++ && *pstr2 != '_')
		{

		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "slow") && strstr(pAnalyze->m_Search, "GameLoop"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "slow") && strstr(pAnalyze->m_Search, "ActionKey"))
	{
		while (pstr2++ && *pstr2 != '_')
		{

		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "region") && strstr(pAnalyze->m_Search, "Npc"))
	{
		while (pstr2++ && *pstr2 != '_')
		{
		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "[Lua]") && strstr(pAnalyze->m_Search, "function") && strstr(pAnalyze->m_Search, "[Lua] [string"))
	{
		while (pstr2++ && *pstr2 != '_')
		{

		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "[ScriptCost]") && strstr(pAnalyze->m_Search, "CostTime"))
	{
		while (pstr2++ && *pstr2 != '_')
		{

		}
		strncpy(this->m_LogInformation, pstr1, pstr2 - pstr1);
		this->m_LogInformation[pstr2 - pstr1] = '\0';
		char *pstr = this->m_LogInformation;
		while (pstr++ && *pstr != '\0')
		{
			if (*pstr == '-')
			{
				*pstr = '_';
			}
		}
		return this->m_LogInformation;
	}
	else
	{
		return nullptr;
	}

}

char* KAnalyzeLog::GetLocalTime(KAnalyzeLog *pAnalyze)//UTC时间
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = nullptr;
	char *pstr2 = nullptr;
	char *pstr = strstr(pAnalyze->m_Search,".log");
	if (pstr)
	{
		pstr1 = pstr + 4;
		pstr2 = pstr1;
		while (*pstr2++ != '<' && *pstr2 != '\0')
		{
		}
		if (*pstr2 == '\0')
		{
			return nullptr;
		}
		else
		{
			strncpy(pAnalyze->m_LogInformation, pstr1, pstr2 - pstr1 - 1);
			pAnalyze->m_LogInformation[pstr2 - pstr1 - 1] = '\0';
			return pAnalyze->m_LogInformation;
		}
	}
	else
	{
		return nullptr;
	}
}

void  KAnalyzeLog::StringToInt(KAnalyzeLog *pAnalyze, char* Source)
//把时间字符串转换成数字
{
	if (pAnalyze == nullptr || Source == nullptr)
	{
		return;
	}
	else
	{//.log 20170221-053719<INFO :0xf
		char *pTemp = (char*)malloc(64);
		memset(pTemp, 0, 64);
		char *pstr = Source;
		while (1)//去除第一个非空格符前的所有空格
		{
			if (*pstr == ' ') 
			{
				pstr = this->DeleteFirstEmpty(pAnalyze, Source);
			}
			else
			{
				break;
			}
		}
		strncpy(pTemp, pstr, 4);
		this->LOCAL_TIME.year = atoi(pTemp);//年
		memset(pTemp, 0, 64);
		pstr = pstr + 4;
		strncpy(pTemp, pstr, 2);
		this->LOCAL_TIME.month = atoi(pTemp);//月
		pstr = pstr + 2;
		memset(pTemp, 0, 64);
		strncpy(pTemp, pstr, 2);
		this->LOCAL_TIME.day = atoi(pTemp);//日
		pstr = pstr + 3;
		memset(pTemp, 0, 64);
		strncpy(pTemp, pstr, 2);

		this->LOCAL_TIME.hour = atoi(pTemp);//时//20170221-053719<INFO :0xf
		pstr = pstr + 2;
		memset(pTemp, 0, 64);
		strncpy(pTemp, pstr, 2);
		this->LOCAL_TIME.minute = atoi(pTemp);//分
		pstr = pstr + 2;
		memset(pTemp, 0, 64);
		strncpy(pTemp, pstr, 2);
		this->LOCAL_TIME.second = atoi(pTemp);//秒
		free(pTemp);
	}
}

char* KAnalyzeLog::LocalTimetoUTC(KAnalyzeLog *pAnalyze)//本地时间转UTC时间
{
	if (pAnalyze == nullptr)
	{
		return nullptr;
	}
	else
	{
		char *time = (char*)malloc(512);
		memset(time, 0, 512);
		TM.tm_year = this->LOCAL_TIME.year - 1900;
		TM.tm_mon = this->LOCAL_TIME.month - 1;
		TM.tm_mday = this->LOCAL_TIME.day;
		TM.tm_hour = this->LOCAL_TIME.hour;
		TM.tm_min = this->LOCAL_TIME.minute;
		TM.tm_sec = this->LOCAL_TIME.second;
		TM.tm_isdst = -1;
		time_t t_ = mktime(&this->TM); //已经减了8个时区  //从1970年到现在的秒数
		tm *gtm = nullptr;
		gtm = gmtime(&t_);//转化为格林威治时间
		strftime(time, 64, "%Y-%m-%dT%H:%M:%SZ", gtm);
		/*sprintf(time,"%d-%d-%dT%d:%d:%dZ",gtm->tm_year,gtm->tm_mon,gtm->tm_mday,
		gtm->tm_hour,gtm->tm_min,gtm->tm_sec);*/
		return time;
	}
	return nullptr;
}

char* KAnalyzeLog::GetLogType(KAnalyzeLog *pAnalyze, int iIndex)//日志类型
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	size_t length = 0;
	char ptemp[] = "Main";
	if (strstr(pAnalyze->m_Search, ptemp))//含有Main的
	{
		char *ptotal = strstr(pAnalyze->m_Search, "total");
		if (ptotal)
		{
			char pstr[] = "slowloop";
			length = strlen(pstr);
			strncpy(pAnalyze->m_LogInformation, pstr, length);
			pAnalyze->m_LogInformation[length] = '\0';
			return pAnalyze->m_LogInformation;
		}
	}
	else if (strstr(pAnalyze->m_Search, "R2S_"))//含有R2S_
	{
		char pstr[] = "r2sproto";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if(strstr(pAnalyze->m_Search, "C2S_"))//含有C2S_
	{
		char pstr[] = "c2sproto";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);//
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "C2S_"))//含有C2S_
	{
		char pstr[] = "c2sproto";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);//
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "Delay"))//含有Delay
	{
		char pstr[] = "framedelay";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "[ScriptCost]"))//含有ScriptCost
	{
		char pstr[] = "scriptcost";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "AICallAction"))//含有AICallAction
	{
		char pstr[] = "slowloop";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "AI Event slow"))//含有AICallAction
	{
		char pstr[] = "aieventslow";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "AI CallAction slow"))//含有AICallAction
	{
		char pstr[] = "aicallactionslow";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;

	}
	else if (strstr(pAnalyze->m_Search, "BuffID"))//含有BuffID
	{
		char pstr[] = "buffidprof";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	else if (strstr(pAnalyze->m_Search, "[Lua]") && strstr(pAnalyze->m_Search, "function"))//含有[Lua]
	{
		char pstr[] = "luaerror";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "Scene") && strstr(pAnalyze->m_Search, "Active"))//含有Scene Active
	{
		char pstr[] = "sceneprof";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "[Traverse] Player"))//含有Delay
	{
		char pstr[] = "traversecost";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "R2S RemoteLua"))//含有Delay
	{
		char pstr[] = "r2slua";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "C2S RemoteLua"))//含有Delay
	{
		char pstr[] = "c2slua";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "SkillHit"))//含有Delay
	{
		char pstr[] = "slowloop";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "PlayerLogin"))//含有Delay
	{
		char pstr[] = "slowloop";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else if (strstr(pAnalyze->m_Search, "SkillApply"))//含有Delay
	{
		char pstr[] = "slowloop";
		length = strlen(pstr);
		strncpy(pAnalyze->m_LogInformation, pstr, length);
		pAnalyze->m_LogInformation[length] = '\0';
		return pAnalyze->m_LogInformation;
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

char* KAnalyzeLog::GetLogName(KAnalyzeLog *pAnalyze,int iIndex)
{
	//cout << "pAnalyze->m_LogType[iIndex]" << pAnalyze->m_LogType[iIndex] << endl;
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pHead = pAnalyze->m_LogInformation;
	char *pstr1 = nullptr;
	char *pstr2 = nullptr;
	char ptemp[] = "Main";
	char *pCurrent = strstr(pAnalyze->m_Search, ptemp);
	char *pcurrent1 = nullptr;
	char str[512];
	char *pstr = str;
	memset(str, 0, 512);
	if (pCurrent != nullptr)//含有Main的
	{
		char *ptotal = strstr(pAnalyze->m_Search,"total");
		if (ptotal)
		{
			char *ptr = pCurrent;
			while (ptr++ && *ptr != ':')
			{
			}
			strncpy(pAnalyze->m_LogInformation, pCurrent, ptr - pCurrent);
			pAnalyze->m_LogInformation[ptr - pCurrent] = '\0';
			return pHead;
		}
		else
		{
			return nullptr;
		}
	}
	pCurrent = strstr(pAnalyze->m_Search, "R2S_");
	if (pCurrent)//含有R2S_
	{
		char *ptr = pCurrent;
		while ((*pstr++ = *pCurrent++) != ':')
		{
		}
		*pstr = '\0';
		strncpy(pAnalyze->m_LogInformation, ptr, pCurrent - ptr -1);
		pAnalyze->m_LogInformation[pCurrent - ptr - 1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "C2S_");
	if (pCurrent)//含有C2S_
	{
		char *ptr = pCurrent;
		while ((*pstr++ = *pCurrent++) != ':')
		{
		}
		*pstr = '\0';
		strncpy(pAnalyze->m_LogInformation, ptr, pCurrent - ptr - 1);
		pAnalyze->m_LogInformation[pCurrent - ptr - 1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "AICallAction");
	if (pCurrent)//含有AICallAction
	{
		while ((*pstr++ = *pCurrent++) != ':')
		{
		}
		*pstr = '\0';
		size_t length = strlen(str);
		strncpy(pAnalyze->m_LogInformation, str, length - 1);
		pAnalyze->m_LogInformation[length - 1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "[Traverse] Player");
	if (pCurrent)//含有[Traverse] Player
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "[Lua]");
	pcurrent1 = strstr(pAnalyze->m_Search, "function");
	if (pcurrent1 && pCurrent)//含有[Lua] 
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "Scene");
	pcurrent1 = strstr(pAnalyze->m_Search, "Active");
	if (pCurrent && pcurrent1)//含有Scene Active
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "[ScriptCost]");
	if (pCurrent)//含有ScriptCost
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "AI CallAction slow");
	if (pCurrent)//含有AI CallAction slow
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "AI Event slow");
	if (pCurrent)//含有AI CallAction slow
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "Delay");
	if (pCurrent)//含有Delay
	{
		return nullptr;
	}
	pCurrent = strstr(pAnalyze->m_Search, "BuffID");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pCurrent = pCurrent + strlen("BuffID") + 1;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent > '0' && *pCurrent <= '9')
			{
				break;
			}
		}
		pstr1 = pCurrent;
		pstr2 = pCurrent;
		while (pstr2++ && *pstr2 != '\0')
		{
			if (*pstr2 < '0' || *pstr2 > '9')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pstr2 - pstr1);
		pAnalyze->m_LogInformation[pstr2 - pstr1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "PlayerLogin");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pstr1 = pCurrent;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent == ':')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pCurrent - pstr1);
		pAnalyze->m_LogInformation[pCurrent - pstr1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "SkillApply");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pstr1 = pCurrent;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent == ':')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pCurrent - pstr1);
		pAnalyze->m_LogInformation[pCurrent - pstr1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "SkillHit");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pstr1 = pCurrent;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent == ':')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pCurrent - pstr1);
		pAnalyze->m_LogInformation[pCurrent - pstr1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "C2S RemoteLua");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pstr1 = pCurrent;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent == ':')
			{
				break;
			}
		}
		pCurrent = pCurrent + 1;
		pstr1 = pCurrent;
		while (pCurrent++ && *(pCurrent) != '\0')
		{
			if (*(pCurrent) == ' ')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pCurrent - pstr1);
		pAnalyze->m_LogInformation[pCurrent - pstr1] = '\0';
		return pHead;
	}
	pCurrent = strstr(pAnalyze->m_Search, "R2S RemoteLua");
	if (pCurrent)//含有// [PROF] BuffID: 11221 Time 54.1ms, nCount 1.
	{
		pstr1 = pCurrent;
		while (pCurrent++ && *pCurrent != '\0')
		{
			if (*pCurrent == ':')
			{
				break;
			}
		}
		pCurrent = pCurrent + 1;
		pstr1 = pCurrent;
		while (pCurrent++ && *(pCurrent) != '\0')
		{
			if (*(pCurrent) == ' ')
			{
				break;
			}
		}
		strncpy(pAnalyze->m_LogInformation, pstr1, pCurrent - pstr1);
		pAnalyze->m_LogInformation[pCurrent - pstr1] = '\0';
		return pHead;
	}
	/*
	else
	{
		char str[512];
		memset(str, 0, 512);
		char *pstr = strstr(pAnalyze->m_Search, pAnalyze->m_LogType[iIndex]);
		pstr1 = pstr;
		if (pstr != nullptr)
		{
			while (pstr1++ && pstr1 != '\0')
			{
				if (*pstr1 == ':')
				{
					pstr2 = pstr1 + 2;
					pstr1 = pstr2;
					while ( pstr++ && *pstr2++ != ' ')
					{
					}
					strncpy(pAnalyze->m_LogInformation, pstr1, pstr2-pstr1 -1);
					pAnalyze->m_LogInformation[pstr2 - pstr1-1] = '\0';
					return pHead;
				}
			}
		}
		*/
	return nullptr;
}

char* KAnalyzeLog::GetTime(KAnalyzeLog *pAnalyze)//时间
{
	char *pstr1 = nullptr;
	char *pstr2 = nullptr;
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-002825<INFO :0xf7274700>: [PROF] C2S RemoteLua : On_Recharge_CheckFriendsInvite Time 13.7ms, nCount 1.

	if (strstr(pAnalyze->m_Search, "CostTime"))
	{
		return nullptr;
	}
	pstr1 = strstr(pAnalyze->m_Search, "AI CallAction slow");
	if (pstr1)
	{
		pstr2 = strstr(pAnalyze->m_Search, "slow");
		pstr1 = strlen("slow") + pstr2;
		pstr2 = pstr1;
		while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2 + 1, pstr1 - pstr2 - 1);
		pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = '\0';
		return pAnalyze->m_LogInformation;
	}
	pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	if (pstr1)
	{
		pstr2 = strstr(pAnalyze->m_Search, "slow");
		pstr1 = strlen("slow") + pstr2;
		pstr2 = pstr1;
		while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2 + 1, pstr1 - pstr2 - 1);
		pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = '\0';
		return pAnalyze->m_LogInformation;
	}
	pstr1 = strstr(pAnalyze->m_Search, "Time");
	if (pstr1 != nullptr)
	{
		if (*(pstr1 - 1) == ' ' && *(pstr1 + 4) == ' ' && (*(pstr1+5) >= '0' && *(pstr1 + 5)<= '9'))
		{
			pstr2 = pstr1 + 5;
			pstr1 = pstr2;
			while (pstr1 && *pstr1++ != 'm' && *pstr1 != '\0')//F] BuffID: 9641 Time 17.7ms, nCount 2.
			{
			}
			strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2 - 1);
			pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = 0;
			return pAnalyze->m_LogInformation;
		}
		else
		{
			char str[1024];
			memset(str, 0, 1024);
			strcpy(str, pstr1 + 5);
			pstr1 = strstr(str,"Time");
			if (pstr1)
			{
				pstr2 = pstr1 + 5;
				if (*pstr2 >= '0' && *pstr2 <= '9')
				{
					pstr1 = pstr2;
					while (pstr1 && *pstr1++ != 'm' && *pstr1 != '\0')//F] BuffID: 9641 Time 17.7ms, nCount 2.
					{
					}
					strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2 - 1);
					pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = 0;
					return pAnalyze->m_LogInformation;
				}
			}
		}
	}
	return nullptr;
}

char* KAnalyzeLog::GetCount(KAnalyzeLog *pAnalyze)//总次数
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-002825<INFO :0xf7274700>: [PROF] C2S RemoteLua : On_Recharge_CheckFriendsInvite Time 13.7ms, nCount 1.

	char *pstr1 = strstr(pAnalyze->m_Search, "nCount");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = pstr1;
		while (pstr1 && *pstr1++ != '.' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2 + 6, pstr1 - (pstr2 + 6) - 1);
		pAnalyze->m_LogInformation[pstr1 - (pstr2 + 6) - 1] = 0;
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetMax(KAnalyzeLog *pAnalyze)//最大
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "max");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = pstr1 + 4;
		pstr1 = pstr2;
		while (pstr1 && *pstr1++ != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2 - 1);
		pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = 0;
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetMin(KAnalyzeLog *pAnalyze)//最小
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "min");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = pstr1 + 4;
		pstr1 = pstr2;
		while (pstr1 && *pstr1++ != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2 - 1);
		pAnalyze->m_LogInformation[pstr1 - pstr2 - 1] = 0;
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetTotal(KAnalyzeLog *pAnalyze)//获取总数
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "total");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr1 += 6;
		pstr2 = pstr1;
		while (pstr1 && *pstr1++ != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2-1);
		pAnalyze->m_LogInformation[pstr1 - pstr2-1] = 0;
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetDelay(KAnalyzeLog *pAnalyze)//获取延时
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//INFO :0xf72a1700>: [PROF] Frame(2082560) Delay 232ms
	char *pstr1 = strstr(pAnalyze->m_Search, "Delay");
	char *pstr2 = strstr(pAnalyze->m_Search, "Frame");

	if (pstr2 && pstr1)
	{
		pstr2 = pstr1 + strlen("Delay");
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = 0;
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}
//f7274700>: [Traverse] Player CostTime: 2207.6870ms(0.4%), Npc CostTime: 22688.6973ms(3.8%)
char * KAnalyzeLog::GetPlayerCostTime(KAnalyzeLog *pAnalyze)
{

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//INFO :0xf72a1700>: [PROF] Frame(2082560) Delay 232ms
	char *pstr1 = strstr(pAnalyze->m_Search, "CostTime");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{//se] Player CostTime: 1394.5444ms(0.2%), Npc Cost
		pstr2 = pstr1 + strlen("CostTime") + 2;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char * KAnalyzeLog::GetNpc(KAnalyzeLog *pAnalyze)
{

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//INFO :0xf72a1700>: [PROF] Frame(2082560) Delay 232ms
	char *pstr1 = strstr(pAnalyze->m_Search, "Npc");
	char *pstr2 = pstr1;

	if (pstr1 != nullptr)
	{
		char *pstr1 = strstr(pAnalyze->m_Search, "Npc CostTime:");
		if (pstr1)
		{
			pstr2 = pstr1 + strlen("Npc CostTime:") + 1;
			pstr1 = pstr2;
			while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
			{
			}
			strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);//
			pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
			return pAnalyze->m_LogInformation;
		}
		else if (strstr(pAnalyze->m_Search, "Scene") && strstr(pAnalyze->m_Search, "Active"))
		{
			pstr1 = pstr2 + strlen("Npc") + 1;
			pstr2 = pstr1;
			while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
			{
			}
			strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
			pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
			return pAnalyze->m_LogInformation;
		}
	}
	return nullptr;
}

char *KAnalyzeLog::GetAIType(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI CallAction slow");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = strstr(pAnalyze->m_Search, "AIType") + strlen("AIType") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	if (pstr1)
	{
		pstr2 = strstr(pAnalyze->m_Search, "AIType") + strlen("AIType") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetActionKey(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI CallAction slow");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = strstr(pAnalyze->m_Search, "ActionKey") + strlen("ActionKey") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != '\0' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char*KAnalyzeLog::GetGameLoop(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = strstr(pAnalyze->m_Search, "GameLoop") + strlen("GameLoop") + 2;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2 );
		pAnalyze->m_LogInformation[pstr1 - pstr2 ] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetAIScriptID(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = strstr(pAnalyze->m_Search, "AIScriptID") + strlen("AIScriptID") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetAIEvent(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	char *pstr2 = pstr1+strlen("AI Event slow");

	if (pstr1 != nullptr)
	{
		pstr1 = strstr(pstr2, "Event") + strlen("Event") + 1;
		pstr2 = pstr1;
		while (pstr1++ && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetState(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "AI Event slow");
	char *pstr2 = nullptr;

	if (pstr1 != nullptr)
	{
		pstr2 = strstr(pAnalyze->m_Search, "State") + strlen("State") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetRegion(KAnalyzeLog *pAnalyze)
{
	// Scene (10, 1) Active total: 121 ms, region: 121 ms. Region: 1116/2288, Npc: 959, Player: 360.

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "Scene");
	char *pstr2 = strstr(pAnalyze->m_Search, "Active");

	if (pstr1 && pstr2)
	{
		pstr2 = strstr(pAnalyze->m_Search, "Region") + strlen("Region") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetregionTime(KAnalyzeLog *pAnalyze)
{
	// Scene (10, 1) Active total: 121 ms, region: 121 ms. Region: 1116/2288, Npc: 959, Player: 360.

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "Scene");
	char *pstr2 = strstr(pAnalyze->m_Search, "Active");

	if (pstr1 && pstr2)
	{
		pstr2 = strstr(pAnalyze->m_Search, "region") + strlen("region") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != 'm' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetPlayer(KAnalyzeLog *pAnalyze)
{
	// Scene (10, 1) Active total: 121 ms, region: 121 ms. Region: 1116/2288, Npc: 959, Player: 360
	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "Scene");
	char *pstr2 = strstr(pAnalyze->m_Search, "Active");
	if (pstr1 && pstr2)
	{
		pstr2 = strstr(pAnalyze->m_Search, "Player") + strlen("Player") + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != '.' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetFunction(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "[Lua]");
	char *pstr2 = strstr(pAnalyze->m_Search, "function");
	//[Lua] Failed to call function CustomAction30, script: scripts/Map/英雄持国回忆录/ai/四人众.lua
	if (pstr1 && pstr2)
	{
		pstr1 = pstr2 + strlen("function") + 1;
		pstr2 = pstr1;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char *KAnalyzeLog::GetScript(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "[Lua]");
	char *pstr2 = strstr(pAnalyze->m_Search, "function");
	//[Lua] Failed to call function CustomAction30, script: scripts/Map/英雄持国回忆录/ai/四人众.lua
	if (pstr1 && pstr2)
	{
		pstr1 = strstr(pAnalyze->m_Search, "[Lua] [string");
		if (pstr1)
		{
			char pstr[1024];
			memset(pstr, 0, 1024);
			pstr1 = strstr(pstr2, "script:") + strlen("script:");
			pstr2 = strstr(pstr2, ".lua");

			pstr2 = pstr2 + 4;
			strncpy(pAnalyze->m_LogInformation, pstr1, pstr2 - pstr1);
			pAnalyze->m_LogInformation[pstr2 - pstr1] = '\0';
			return pAnalyze->m_LogInformation;
		}
		else
		{
			return  nullptr;
		}
	}
	return nullptr;
}

char *KAnalyzeLog::GetString(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "[Lua]");
	char *pstr2 = strstr(pAnalyze->m_Search, "function");
	//[Lua] Failed to call function CustomAction30, script: scripts/Map/英雄持国回忆录/ai/四人众.lua
	//>: [Lua] [string "scripts/skill/苍云/套路及子技能/苍云_云城盾_..."]:
	if (pstr1 && pstr2)
	{
		pstr1 = strstr(pAnalyze->m_Search, "[Lua] [string");
		if (pstr1)
		{
			pstr1 = pstr1 + strlen("[Lua] [string") + 1;
			pstr2 = pstr1;
			while (pstr1++ && *pstr1 != '\0')
			{
				if (*pstr1 == '"' && *(pstr1 + 1) == ']')
				{
					break;
				}
			}
			pstr2 = pstr2 + 1;
			strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
			pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
			return pAnalyze->m_LogInformation;
		}
		else
		{
			return nullptr;
		}
	}
	return nullptr;
}

char* KAnalyzeLog::GetServer(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = pAnalyze->m_Search;
	char *pstr2 = pAnalyze->m_Search;
	//23.66kuozhan - gate0210_gm18_2017_02_21 
	while (pstr2++)
	{
		if (*(pstr2) == '_')
		{
			pstr1 = pstr2 + 1;
			while ((*pstr1++) != '_' && *pstr1 != '\0')//等于'_'时结束循环
			{
			}
			break;
		}
	}
	pstr2 = pstr2 + 1;
	strncpy(this->m_LogInformation, pstr2, pstr1 - pstr2-1);
	this->m_LogInformation[pstr1 - pstr2-1] = '\0';
	return this->m_LogInformation;
}

char* KAnalyzeLog::GetWhy(KAnalyzeLog *pAnalyze)
{
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "[Lua]");
	char *pstr2 = strstr(pAnalyze->m_Search, "function");
	//[Lua] Failed to call function CustomAction30, script: scripts/Map/英雄持国回忆录/ai/四人众.lua
	//>: [Lua] [string "scripts/skill/苍云/套路及子技能/苍云_云城盾_..."]:
	if (pstr1 && pstr2)
	{
		pstr1 = strstr(pAnalyze->m_Search, "[Lua] [string");
		if (pstr1)
		{
			pstr1 = pstr1 + strlen("[Lua] [string") + 1;
			while (pstr1++ && *pstr1 != '\0')
			{
				if (*pstr1 == '"' && *(pstr1 + 1) == ']')
				{
					break;
				}
			}
			pstr2 = pstr1 + 1;
			while (pstr2++)
			{
				if (*pstr2 == ':' && *(pstr2 + 1) == ' ')
				{
					break;
				}
			}
			pstr2 = pstr2 + 1;
			pstr1 = pstr2;
			while (pstr2++)
			{
				if (*pstr2 == '/')
				{
					break;
				}
			}
			strncpy(pAnalyze->m_LogInformation, pstr1, pstr2 - pstr1);
			pAnalyze->m_LogInformation[pstr2 - pstr1] = '\0';
			return pAnalyze->m_LogInformation;
		}
		else
		{
			return nullptr;
		}
	}
	return nullptr;
}

char* KAnalyzeLog::DeleteLastZero(KAnalyzeLog *pAnalyze ,char * Source)
{
	if (pAnalyze)
	{
		char *pstr = Source;
		char *pstr1 = Source;
		char *pHead = Source;
		int flag = 0;
		while (pstr++ && * pstr!='\0' )
		{
			if (*pstr == '.')
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			while (1)
			{
				pstr1 = pHead + strlen(pHead);
				if (*(pstr1 - 1) == '0' && *(pstr1 - 2) == '.')
				{
					return pHead;
				}
				else if (*(pstr1 - 1) == '0' && *(pstr1 -2) != '.')
				{
					*(pstr1 - 1) = '\0';
				}
				else
				{
					return pHead;
				}
			}
		}
		else
		{
			return Source;
		}
	}
	else
	{
		return nullptr;
	}
}

char* KAnalyzeLog::DeleteFirstEmpty(KAnalyzeLog *pAnalyze, char* Source)//如果字符串首位置字符是空格则去除空格
{
	char* pHead = Source;
	if (Source != nullptr && pAnalyze != nullptr)
	{
		char *pstr1 = nullptr;
		while (true)
		{
			pstr1 = pHead;
			if (*pstr1 == ' ')
			{
				while (*pstr1 = *(pstr1 + 1))
				{
					pstr1++;
				}
			}
			else
			{
				return pHead;
			}
		}
	}
	return Source;
}

char* KAnalyzeLog::DeleteLastEmpty(KAnalyzeLog *pAnalyze, char* Source)
{
	if (pAnalyze)
	{
		char *pstr = nullptr;
		char *pHead = Source;
		while (true)
		{
			pstr = pHead + strlen(pHead) - 1;//移动到最后一个字符
			if (*pstr == ' ')//如果最后一个字符是空格
			{
				*pstr = '\0';
			}
			else
			{
				return pHead;
			}
		}
	}
	else
	{
		return nullptr;
	}
}

wchar_t* KAnalyzeLog::DeleteWFirstEmpty(KAnalyzeLog *pAnalyze, wchar_t *Source)
{
	if (Source != nullptr)
	{
		while (true)
		{
			wchar_t *pstr1 = Source;
			if (*Source == L' ')
			{
				while (*pstr1 = *(pstr1 + 1))
				{
					pstr1++;
				}
			}
			else
			{
				break;
			}
		}
	}
	return Source;
}

wchar_t* KAnalyzeLog::DeleteWLastEmpty(KAnalyzeLog *pAnalyze, wchar_t* Source)
{
	if (pAnalyze)
	{
		wchar_t *pstr = nullptr;
		wchar_t *pHead = Source;
		while (true)
		{
			pstr = pHead;
			while (pstr++ && *pstr != L'\0')
			{
			}//移动到最后一个字符
			if (*(pstr - 1) == L' ')//如果最后一个字符是空格
			{
				*(pstr - 1) = L'\0';
			}
			else
			{
				break;
			}
		}
		return Source;
	}
	else
	{
		return nullptr;
	}
}

char* KAnalyzeLog::GetMap(KAnalyzeLog *pAnalyze)
{
	// Scene (10, 1) Active total: 121 ms, region: 121 ms. Region: 1116/2288, Npc: 959, Player: 360.

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "Scene");
	char *pstr2 = strstr(pAnalyze->m_Search, "Active");

	if (pstr1 && pstr2)
	{
		pstr2 = strstr(pAnalyze->m_Search, "Scene (") + strlen("Scene (");
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetSubMap(KAnalyzeLog *pAnalyze)
{
	// Scene (10, 1) Active total: 121 ms, region: 121 ms. Region: 1116/2288, Npc: 959, Player: 360.

	memset(pAnalyze->m_LogInformation, 0, 1024);
	//>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
	char *pstr1 = strstr(pAnalyze->m_Search, "Scene");
	char *pstr2 = strstr(pAnalyze->m_Search, "Active");

	if (pstr1 && pstr2)
	{
		pstr2 = strstr(pAnalyze->m_Search, "Scene (") + strlen("Scene (");
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ',' && *pstr1 != '\0')
		{
		}
		pstr2 = pstr1 + 1;
		pstr1 = pstr2;
		while (pstr1++ && *pstr1 != ')' && *pstr1 != '\0')
		{
		}
		strncpy(pAnalyze->m_LogInformation, pstr2, pstr1 - pstr2);
		pAnalyze->m_LogInformation[pstr1 - pstr2] = '\0';
		return pAnalyze->m_LogInformation;
	}
	return nullptr;
}

char* KAnalyzeLog::GetLineNumber(KAnalyzeLog *pAnalyze)
{
	//[Lua] [string "scripts/Craft/item/智能BUFF.lua"]:113: attempt to index a nil value/**/
	memset(pAnalyze->m_LogInformation, 0, 1024);
	char *pstr1 = strstr(pAnalyze->m_Search, "[Lua]");
	char *pstr2 = strstr(pAnalyze->m_Search, "function");
	//[Lua] Failed to call function CustomAction30, script: scripts/Map/英雄持国回忆录/ai/四人众.lua
	//>: [Lua] [string "scripts/skill/苍云/套路及子技能/苍云_云城盾_..."]:
	if (pstr1 && pstr2)
	{
		pstr1 = strstr(pAnalyze->m_Search, "[Lua] [string");
		if (pstr1)
		{
			pstr1 = pstr1 + strlen("[Lua] [string") + 1;
			while (pstr1++ && *pstr1 != '\0')
			{
				if (*pstr1 == '"' && *(pstr1 + 1) == ']')
				{
					break;
				}
			}
			pstr2 = pstr1 + 1;
			while (pstr2++)
			{
				if (*pstr2 == ':')
				{
					break;
				}
			}
			pstr2 = pstr2 + 1;
			pstr1 = pstr2;
			while (pstr2++)
			{
				if (*pstr2 == ':')
				{
					break;
				}
			}
			strncpy(pAnalyze->m_LogInformation, pstr1, pstr2 - pstr1);
			pAnalyze->m_LogInformation[pstr2 - pstr1] = '\0';
			return pAnalyze->m_LogInformation;
		}
		else
		{
			return nullptr;
		}
	}
	return nullptr;
}

void KAnalyzeLog::Test(KAnalyzeLog * pAnalyze, char *Source)
{
	size_t length = strlen(Source);
	strncpy(pAnalyze->m_Search, Source, length);
	strncpy(pAnalyze->m_InPutString, Source, length);
	pAnalyze->m_InPutString[length] = '\0';
	pAnalyze->m_Search[length] = '\0';
}
