#include "Test.h"

AssertionResult KUnitGTest::IsNullptr(const char* str)
{
	if (str != nullptr) {
		return testing::AssertionFailure() << "argument is " << str;
	}
	return AssertionSuccess();
}

TestCase const**KUnitGTest::GetSortedTestCases()
{
	UnitTest *unit_test = UnitTest::GetInstance();
	TestCase const** const test_case = new const TestCase *[unit_test->total_test_case_count()];
	for (int i = 0; i < unit_test->total_test_case_count(); i++)
	{
		test_case[i] = unit_test->GetTestCase(i);//将实例保存到 TestCase*数组中
	}
	auto StrSort = [](const TestCase *test1, const TestCase* test2)
	{return strcmp(test1->name(), test2->name()) < 0; };
	sort(test_case,
		test_case + unit_test->total_test_case_count(),
		StrSort);
	return test_case;
}

// Returns the test case by its name.  The caller doesn't own the returned
// pointer.
const TestCase*KUnitGTest::FindTestCase(const char *name)
{
	UnitTest *unit_test = UnitTest::GetInstance();
	for (int i = 0; i < unit_test->total_test_case_count(); i++)
	{
		const TestCase*test_case = unit_test->GetTestCase(i);
		if (0 == strcmp(test_case->name(), name))
		{
			return test_case;
		}
	}
	return nullptr;
}

// Returns the array of pointers to all tests in a particular test case
// sorted by the test name.  The caller is responsible for deleting the
// array.
TestInfo const**KUnitGTest::GetSortedTests(const TestCase* test_case)
{
	TestInfo const** const test_info = new const TestInfo *[test_case->total_test_count()];
	for (int i = 0; i < test_case->total_test_count(); i++)
	{
		test_info[i] = test_case->GetTestInfo(i);
	}
	auto StrSort = [](const TestInfo *testinfo1, const TestInfo * testinfo2)
	{return strcmp(testinfo1->name(), testinfo2->name()) < 0; };
	sort(test_info,
		test_info + test_case->total_test_count(),
		StrSort);
	return test_info;
}

void KUnitGTest::SetUp()
{
	panalyze = new KAnalyzeLog;
}

void KUnitGTest::TearDown()
{
	delete panalyze;
	panalyze = nullptr;
}

void KUnitGTest::DataObjectTest()
{
	EXPECT_NE(nullptr, panalyze->m_InPutString);
	EXPECT_NE(nullptr,panalyze->m_Search);
	EXPECT_NE(nullptr, panalyze->sTypeFirst);
	EXPECT_NE(nullptr, panalyze->sTypeLast);
	EXPECT_NE(nullptr, panalyze->m_LogInformation);
	EXPECT_NE(nullptr, panalyze->m_InPutString);
}
//类数据成员测试
TEST_F(KUnitGTest, DateObjectTest)
{
	DataObjectTest();
}
//类成员函数测试
TEST_F(KUnitGTest, FuctionReturnValue_0)
{
	char str3[] = "   jlksdjflk";
	char str4[] = "iew,irpeo  ";
	char str_3[] = "jlksdjflk";
	char str_4[] = "iew,irpeo";
	EXPECT_FALSE(IsNullptr(panalyze->DeleteFirstEmpty(panalyze, str3)));
	EXPECT_STREQ(str_3, panalyze->DeleteFirstEmpty(panalyze, str3));
	EXPECT_FALSE(IsNullptr(panalyze->DeleteLastEmpty(panalyze, str4)));
	EXPECT_STREQ(str_4, panalyze->DeleteLastEmpty(panalyze, str4));

	wchar_t str5[] = L"        jlksdjflk";
	wchar_t str6[] = L"iew,irpeo   ";
	wchar_t str_5[] = L"jlksdjflk";
	wchar_t str_6[] = L"iew,irpeo";
	EXPECT_FALSE(IsNullptr((char*)(panalyze->DeleteWFirstEmpty(panalyze, str5))));
	EXPECT_EQ(0, wcscmp(str_5, panalyze->DeleteWFirstEmpty(panalyze, str5)));//***************************
	//wcout << "**str5" << panalyze->DeleteWFirstEmpty(panalyze,str5) <<"****" << endl;
	EXPECT_FALSE(IsNullptr((char*)(panalyze->DeleteWLastEmpty(panalyze, str6))));
	//EXPECT_EQ(true, WcharCompare(str_6, panalyze->DeleteWLastEmpty(panalyze, str6)));//***************************
	EXPECT_EQ(0, wcscmp(str_6, panalyze->DeleteWLastEmpty(panalyze, str6)));
	//wcout << "**str6" << panalyze->DeleteWFirstEmpty(panalyze, str6) << "****" << endl;
	char str7[] = "0.3400500000";
	char str8[] = "505";
	char str9[] = "5.0000";
	char str10[] = "6.0";
	char str11[] = "0.000";
	char str12[] = "0.0";
	char str13[] = "41.0";
	EXPECT_STREQ("0.34005",panalyze->DeleteLastZero(panalyze,str7));
	EXPECT_STREQ("505",panalyze->DeleteLastZero(panalyze,str8));
	EXPECT_STREQ("5.0",panalyze->DeleteLastZero(panalyze,str9));
	EXPECT_STREQ("6.0",panalyze->DeleteLastZero(panalyze,str10));
	EXPECT_STREQ("0.0",panalyze->DeleteLastZero(panalyze,str11));
	EXPECT_STREQ("0.0",panalyze->DeleteLastZero(panalyze,str12));
	EXPECT_STREQ("41.0", panalyze->DeleteLastZero(panalyze, str13));
}
//test 23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_18_58_20.log 20170221-195053<INFO :0xf7334700>: [PROF] Scene (10, 1) Active total: 280 ms, region: 280 ms. Region: 1012/2288, Npc: 904, Player: 364.
TEST_F(KUnitGTest, FuctionReturnValue_1)
{
	char str[1024] = "23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_18_58_20.log 20170221-195053<INFO :0xf7334700>: [PROF] Scene (10, 1) Active total: 280 ms, region: 280 ms. Region: 1012/2288, Npc: 904, Player: 364.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//test 23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_10_42_35.log 20170221-105316<INFO :0xf72f4700>: [PROF] Frame(1356718) Delay 198ms
TEST_F(KUnitGTest, FuctionReturnValue_2)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_10_42_35.log 20170221-105316<INFO :0xf72f4700>: [PROF] Frame(1356718) Delay 198ms";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//test 23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_10_42_35.log 20170221-105316<INFO :0xf72f4700>: [PROF]   Main: total 197.93ms, max 197.93ms, min 197.93ms.
TEST_F(KUnitGTest, FuctionReturnValue_3)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_10_42_35.log 20170221-105316<INFO :0xf72f4700>: [PROF]   Main: total 197.93ms, max 197.93ms, min 197.93ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
TEST_F(KUnitGTest, FuctionReturnValue_4)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_10_42_35.log 20170221-105316<INFO :0xf72f4700>: [PROF]   C2S_184: total 133.55ms, max 91.86ms, min 0.71ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
// test 23.66kuozhan - gate0210_gm05_2017_02_21 / SO3GameServer_2017_02_21_16_44_38.log 20170221 - 165334 < INFO :0xf72f4700 > : [PROF]   R2S_132 : total 74.40ms, max 40.24ms, min 0.58ms.
TEST_F(KUnitGTest, FuctionReturnValue_5)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-165334<INFO :0xf72f4700>: [PROF]   R2S_132: total 74.40ms, max 40.24ms, min 0.58ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-165334<INFO :0xf72f4700>: [PROF] R2S RemoteLua : On_Castle_CheckMasterDes Time 40.2ms, nCount 1.
TEST_F(KUnitGTest, FuctionReturnValue_6)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-165334<INFO :0xf72f4700>: [PROF] R2S RemoteLua : On_Castle_CheckMasterDes Time 40.2ms, nCount 1.";
		panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-165532<INFO :0xf72f4700>: [PROF] C2S RemoteLua : On_FBRank_GetAllFBRankInfo Time 72.9ms, nCount 1.
TEST_F(KUnitGTest, FuctionReturnValue_7)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-165532<INFO :0xf72f4700>: [PROF] C2S RemoteLua : On_FBRank_GetAllFBRankInfo Time 72.9ms, nCount 1.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-170001<INFO :0xf72f4700>: [Traverse] Player CostTime: 1391.4423ms(0.2%), Npc CostTime: 2576.9912ms(0.4%)
TEST_F(KUnitGTest, FuctionReturnValue_8)
{
	char str[1024] = "23.66kuozhan-gate0210_gm05_2017_02_21/SO3GameServer_2017_02_21_16_44_38.log 20170221-170001<INFO :0xf72f4700>: [Traverse] Player CostTime: 1391.4423ms(0.2%), Npc CostTime: 2576.9912ms(0.4%)";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm14_2017_02_21/SO3GameServer_2017_02_21_23_02_32.log 20170221-234043<INFO :0xf7284700>: [PROF]   AICallAction: total 6.87ms, max 3.74ms, min 0.00ms.
TEST_F(KUnitGTest, FuctionReturnValue_9)
{
	char str[1024] = "23.66kuozhan-gate0210_gm14_2017_02_21/SO3GameServer_2017_02_21_23_02_32.log 20170221-234043<INFO :0xf7284700>: [PROF]   AICallAction: total 6.87ms, max 3.74ms, min 0.00ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm18_2017_02_21/SO3GameServer_2017_02_21_18_32_51.log 20170221-190826<INFO :0xf7310700>: [PROF]    AI Event slow 33.91ms, GameLoop: 1832076, AIType: 9920, AIScriptID: 378674810, State: 17, Event: 1
TEST_F(KUnitGTest, FuctionReturnValue_10)
{
	char str[1024] = "23.66kuozhan-gate0210_gm18_2017_02_21/SO3GameServer_2017_02_21_18_32_51.log 20170221-190826<INFO :0xf7310700>: [PROF]    AI Event slow 33.91ms, GameLoop: 1832076, AIType: 9920, AIScriptID: 378674810, State: 17, Event: 1";
		panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm18_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000312<INFO :0xf7310700>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018
TEST_F(KUnitGTest, FuctionReturnValue_11)
{
	char str[1024] = "23.66kuozhan-gate0210_gm18_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000312<INFO :0xf7310700>: [PROF]    AI CallAction slow 30ms, AIType: 9920, ActionKey: 2018";
		panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_20_57_01.log 20170221-215335<INFO :0xf7334700>: [PROF]   Main.C2S: total 131.61ms, max 131.61ms, min 131.61ms.
TEST_F(KUnitGTest, FuctionReturnValue_12)
{
	char str[1024] = "23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_20_57_01.log 20170221-215335<INFO :0xf7334700>: [PROF]   Main.C2S: total 131.61ms, max 131.61ms, min 131.61ms.";
		panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_20_57_01.log 20170221-215335<INFO :0xf7334700>: [PROF]   Main.World: total 12.86ms, max 12.86ms, min 12.86ms.
TEST_F(KUnitGTest, FuctionReturnValue_13)
{
	char str[1024] = "23.66kuozhan-gate0210_gm09_2017_02_21/SO3GameServer_2017_02_21_20_57_01.log 20170221-215335<INFO :0xf7334700>: [PROF]   Main.World: total 12.86ms, max 12.86ms, min 12.86ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm08_2017_02_21/SO3GameServer_2017_02_21_21_30_34.log 20170221-214203<ERROR:0xf7298700>: [Lua] [string "scripts/skill/苍云/套路及子技能/苍云_云城盾_..."]:180: attempt to call field 'GetKungfuMount' (a nil value)/**///23.66kuozhan - gate0210_gm08_2017_02_21 / SO3GameServer_2017_02_21_21_30_34.log 20170221 - 214203 < ERROR:0xf7298700 > : [Lua] Failed to call function CanCast, script : scripts / skill / 苍云 / 套路及子技能 / 苍云_云城盾_杨旌沙场.lua
TEST_F(KUnitGTest, FuctionReturnValue_14)
{
	char str[1024] = "23.66kuozhan-gate0210_gm08_2017_02_21/SO3GameServer_2017_02_21_21_30_34.log 20170221-214203<ERROR:0xf7298700>: [Lua] [string \"scripts / skill / 苍云 / 套路及子技能 / 苍云_云城盾_...\"]:180: attempt to call field 'GetKungfuMount' (a nil value)/**///23.66kuozhan - gate0210_gm08_2017_02_21 / SO3GameServer_2017_02_21_21_30_34.log 20170221 - 214203 < ERROR:0xf7298700 > : [Lua] Failed to call function CanCast, script : scripts / skill / 苍云 / 套路及子技能 / 苍云_云城盾_杨旌沙场.lua";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan - gate0210_gm13_2017_02_21 / SO3GameServer_2017_02_21_15_52_58.log 20170221 - 161959 < INFO : 0xf733e700 > : [PROF] BuffID : 9641 Time 17.7ms, nCount 2.
TEST_F(KUnitGTest, FuctionReturnValue_15)
{
	char str[1024] = "23.66kuozhan - gate0210_gm13_2017_02_21 / SO3GameServer_2017_02_21_15_52_58.log 20170221 - 161959 < INFO : 0xf733e700 > : [PROF] BuffID : 9641 Time 17.7ms, nCount 2.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_18_19_55.log 20170221-184331<INFO :0xf72f1700>: [PROF]   Main.World.Npc.NpcPartB: total 6.89ms, max 0.92ms, min 0.00ms.
TEST_F(KUnitGTest, FuctionReturnValue_16)
{
	char str[1024] = "23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_18_19_55.log 20170221-184331<INFO :0xf72f1700>: [PROF]   Main.World.Npc.NpcPartB: total 6.89ms, max 0.92ms, min 0.00ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm08_2017_02_21/SO3GameServer_2017_02_21_20_39_05.log 20170221-212010<INFO :0xf7298700>: [PROF]   Main.World.Character.PlayerBuff.PlayerBuffActivate: total 7.59ms, max 1.13ms, min 0.00ms.
TEST_F(KUnitGTest, FuctionReturnValue_17)
{
	char str[1024] = "23.66kuozhan-gate0210_gm08_2017_02_21/SO3GameServer_2017_02_21_20_39_05.log 20170221-212010<INFO :0xf7298700>: [PROF]   Main.World.Character.PlayerBuff.PlayerBuffActivate: total 7.59ms, max 1.13ms, min 0.00ms.";
	panalyze->Test(panalyze, str);
	char str1[1024];
	char str2[1024];
	memset(str1, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(str1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(str1), str2)));
	EXPECT_FALSE(IsNullptr(panalyze->GetProcessId(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLocalTime(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->LocalTimetoUTC(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetLogType(panalyze, 1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetLogName(panalyze, 1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetTime(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetCount(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMax(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetMin(panalyze)));
	EXPECT_FALSE(IsNullptr(panalyze->GetTotal(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetDelay(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetPlayerCostTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetNpc(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIType(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetActionKey(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetGameLoop(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIScriptID(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetAIEvent(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetState(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetRegion(panalyze)));

	EXPECT_TRUE(IsNullptr(panalyze->GetregionTime(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetPlayer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetFunction(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetScript(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetString(panalyze)));

	EXPECT_FALSE(IsNullptr(panalyze->GetServer(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetWhy(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetSubMap(panalyze)));
	EXPECT_TRUE(IsNullptr(panalyze->GetLineNumber(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000000<INFO :0xf7274700>: [PROF] Frame(729572) Cost 21ms
TEST_F(KUnitGTest, UnusualTest_1)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000000<INFO :0xf7274700>: [PROF] Frame(729572) Cost 21ms";
	panalyze->Test(panalyze, str);
	EXPECT_EQ(-1,panalyze->Search());
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000000<DEBUG:0xf7274700>: KGLOG_PROCESS_ERROR_RET_CODE(nDistance <= MAX_START_OUT_DISTANCE, 2) at line 23092 in void KPlayerServer::OnRoadTrackStartOut(char*, size_t, int, int)
TEST_F(KUnitGTest, UnusualTest_2)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000000<DEBUG:0xf7274700>: KGLOG_PROCESS_ERROR_RET_CODE(nDistance <= MAX_START_OUT_DISTANCE, 2) at line 23092 in void KPlayerServer::OnRoadTrackStartOut(char*, size_t, int, int)";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);

	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1),dest2)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<DEBUG:0xf7274700>: 閲嶉槼娲诲?
TEST_F(KUnitGTest, UnusualTest_3)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<DEBUG:0xf7274700>: 閲嶉槼娲诲?";
	panalyze->Test(panalyze, str);
	char dest[1024];
	memset(dest, 0, 1024);
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeFirst(dest)));
}
//23.66kuozhan - gate0210_gm07_2017_02_21 / SO3GameServer_2017_02_21_00_00_00.log 20170221 - 000001 < DEBUG:0xf7274700 > : [Activity] NORMAL_ON Activity : 130
TEST_F(KUnitGTest, UnusualTest_4)
{
	char str[1024] = "23.66kuozhan - gate0210_gm07_2017_02_21 / SO3GameServer_2017_02_21_00_00_00.log 20170221 - 000001 < DEBUG:0xf7274700 > : [Activity] NORMAL_ON Activity : 130";
	panalyze->Test(panalyze, str);
	char dest[1024];
	memset(dest, 0, 1024);
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeFirst(dest)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<DEBUG:0xf7274700>: 1_  D  _1
TEST_F(KUnitGTest, UnusualTest_5)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<DEBUG:0xf7274700>: 1_  D  _1";
	panalyze->Test(panalyze, str);
	char dest[1024];
	memset(dest, 0, 1024);
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeFirst(dest)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [Memory] Free Memory To System, cost time: 0.0016
TEST_F(KUnitGTest, UnusualTest_6)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [Memory] Free Memory To System, cost time: 0.0016";
	panalyze->Test(panalyze, str);
	char dest[1024];
	memset(dest, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest)));
	char dest2[1024];
	memset(dest2, 0, 1024);

	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [PlayerServer] Send total cost: 1263.0039ms
TEST_F(KUnitGTest, UnusualTest_7)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [PlayerServer] Send total cost: 1263.0039ms";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);

	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000013<INFO :0xd60f9b40>: New connection from 113.108.225.21:30275, index = 77
TEST_F(KUnitGTest, UnusualTest_8)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000013<INFO :0xd60f9b40>: New connection from 113.108.225.21:30275, index = 77";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);

	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000023<DEBUG:0xf7274700>: scripts/player/OnPlayerLogin/鐧婚檰鑴氭湰_甯搁┗鍔熻兘.lua : 934
TEST_F(KUnitGTest, UnusualTest_9)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000023<DEBUG:0xf7274700>: scripts/player/OnPlayerLogin/鐧婚檰鑴氭湰_甯搁┗鍔熻兘.lua : 934";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000025<INFO :0xf7274700>: [Script Time Stat] #0 TimeStat: 34.682ms.
TEST_F(KUnitGTest, UnusualTest_10)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000025<INFO :0xf7274700>: [Script Time Stat] #0 TimeStat: 34.682ms.";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [PlayerServer] Send total cost: 0.0000ms
TEST_F(KUnitGTest, UnusualTest_11)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [PlayerServer] Send total cost: 0.0000ms";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm21_2017_02_21/SO3GameServer_2017_02_21_23_32_17.log 20170221-234201<DEBUG:0xf728d700>: [Activity] NORMAL_OFF Activity:129
TEST_F(KUnitGTest, UnusualTest_12)
{
	char str[1024] = "23.66kuozhan-gate0210_gm21_2017_02_21/SO3GameServer_2017_02_21_23_32_17.log 20170221-234201<DEBUG:0xf728d700>: [Activity] NORMAL_OFF Activity:129";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_18_19_55.log 20170221-184331<INFO :0xf72f1700>: [PROF] KSO3World::Activate Loop 1808156 Time 267 ms.
TEST_F(KUnitGTest, UnusualTest_13)
{
	char str[1024] = "23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_18_19_55.log 20170221-184331<INFO :0xf72f1700>: [PROF] KSO3World::Activate Loop 1808156 Time 267 ms.";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.106kuozhan-gate0210_gm09_2017_03_12/SO3GameServer_2017_03_12_22_03_54.log 20170312-224302<ERROR:0xf7306700>: [Lua] Failed to call function CustomAction29, script: scripts/Map/英雄南诏皇宫/ai/特殊小怪/开关螺旋.lua
TEST_F(KUnitGTest, UnusualTest_14)
{
	char str[1024] = "23.106kuozhan-gate0210_gm09_2017_03_12/SO3GameServer_2017_03_12_22_03_54.log 20170312-224302<ERROR:0xf7306700>: [Lua] Failed to call function CustomAction29, script: scripts/Map/英雄南诏皇宫/ai/特殊小怪/开关螺旋.lua";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_12_24_53.log 20170221-123738<DEBUG:0xf72f1700>: [KRelayClient] Account Security, Change state, Role=4270391('鍗楀悤鐧借棌'), Acc=momaoxiaomiaomiao, State=1
TEST_F(KUnitGTest, UnusualTest_15)
{
	char str[1024] = "23.66kuozhan-gate0210_gm10_2017_02_21/SO3GameServer_2017_02_21_12_24_53.log 20170221-123738<DEBUG:0xf72f1700>: [KRelayClient] Account Security, Change state, Role=4270391('鍗楀悤鐧借棌'), Acc=momaoxiaomiaomiao, State=1";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_TRUE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
}
//23.66kuozhan-gate0210_gm06_2017_02_21/SO3GameServer_2017_02_21_19_31_20.log 20170221-194726<ERROR:0xf72df700>: [KScriptServer] Not found player:0 by Call. func:OnOutputWarningMessage
TEST_F(KUnitGTest, UnusualTest_16)
{
	char str[1024] = "23.66kuozhan-gate0210_gm06_2017_02_21/SO3GameServer_2017_02_21_19_31_20.log 20170221-194726<ERROR:0xf72df700>: [KScriptServer] Not found player:0 by Call. func:OnOutputWarningMessage";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}
//23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [Memory] Free Memory To System, cost time: 0.0016
TEST_F(KUnitGTest, UnusualTest_17)
{
	char str[1024] = "23.66kuozhan-gate0210_gm07_2017_02_21/SO3GameServer_2017_02_21_00_00_00.log 20170221-000001<INFO :0xf7274700>: [Memory] Free Memory To System, cost time: 0.0016";
	panalyze->Test(panalyze, str);
	char dest1[1024];
	memset(dest1, 0, 1024);
	char dest2[1024];
	memset(dest2, 0, 1024);
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeFirst(dest1)));
	EXPECT_FALSE(IsNullptr(panalyze->GetInPutTypeLast(panalyze, panalyze->GetInPutTypeFirst(dest1), dest2)));
	EXPECT_TRUE(IsNullptr(panalyze->GetProcessId(panalyze)));
}

GTEST_API_ int main(int argc,char*argv[])
{
	printf("Running main() from Test.cpp\n");
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
