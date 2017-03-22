#ifndef _COMPARE_FILE_H
#define _COMPARE_FILE_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

class KCompareFile
{
public:
	KCompareFile();
	~KCompareFile();

	bool		OpenFile(const char* file1,const char* file2);
	int			ReadFile();
	bool		Compare();
	template<typename Out>
	void split(const std::string &s, char delim, Out result);
	std::vector<std::string> split(const std::string &s, char delim);
private:
	string		m_str1;
	string		m_str2;
	char*		m_File1Name;
	char*		m_File2Name;
	ifstream	m_fileIn1;
	ifstream	m_fileIn2;
};

#endif