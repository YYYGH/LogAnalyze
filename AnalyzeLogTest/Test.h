#ifndef _MY_TEST_H_
#define _MY_TEST_H_

#include "include/gtest/gtest.h"
#include "KAnalyzeLog.h"


//using ::testing::InitGoogleTest;
using namespace testing;
using namespace std;
class KAnalyzeLog;
class KUnitGTest :public Test
{
public:
	//~KUnitTest() = delete;
	static TestCase const**			GetSortedTestCases();
	static const TestCase*			FindTestCase(const char *name);
	static TestInfo const**			GetSortedTests(const TestCase* test_case);
	virtual void SetUp();
	virtual void TearDown();
	AssertionResult IsNullptr(const char* str);
	void DataObjectTest();
	KAnalyzeLog *panalyze;
	//KAnalyzeLog kanalyze;
};
#endif
