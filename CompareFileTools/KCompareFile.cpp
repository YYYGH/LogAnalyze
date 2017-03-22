#include "KCompareFile.h"

KCompareFile::KCompareFile()
{
}

KCompareFile::~KCompareFile()
{
	this->m_fileIn1.close();
	this->m_fileIn2.close();
}

bool KCompareFile::OpenFile(const char* file1, const char* file2)
{
	this->m_fileIn1.open(file1, ios::in);
	int flag = this->m_fileIn1.flags();
	if (flag == ios::failbit)
	{
		cout << "open file1 fail" << endl;
		return false;
	}
	this->m_fileIn2.open(file2, ios::in);
	flag = this->m_fileIn2.flags();
	if (flag == ios::failbit)
	{
		cout << "open file2 fail" << endl;
		return false;
	}
	return true;
}

int KCompareFile::ReadFile()
{
	char str1[1024];
	char str2[1024];
	int flag1;
	int flag2;
	memset(str1, 0, 1024);
	memset(str2, 0, 1024);
	m_fileIn1.getline(str1,1024);
	flag1 = m_fileIn1.flags();
	m_fileIn2.getline(str2,1024);
	flag2 = m_fileIn2.flags();
	if (m_fileIn1.eof() && m_fileIn2.eof())
	{
		cout << "end" << endl;
		return 0;
	}
	else if (!m_fileIn1.eof() && m_fileIn2.eof())
	{
		cout << "unequal" << endl;
		return -1;
	}
	else if (m_fileIn1.eof() && !m_fileIn2.eof())
	{
		cout << "unequal" << endl;
		return -1;
	}
	else
	{
		//cout << "*********************************" << endl;
		this->m_str1 = str1;
		this->m_str2 = str2;
		return 1;
	}
}
template<typename Out>
void KCompareFile::split(const std::string &s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		*(result++) = item;
	}
}
std::vector<std::string> KCompareFile::split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

bool KCompareFile::Compare()
{
	//去除{ }
	
	auto first1 = m_str1.find_first_of('{');
	m_str1.replace(first1, 1, " ");
	first1 = m_str1.find_last_of('}');
	m_str1.replace(first1, 1, "\0");
	//去除所有空格
	auto begin1 = m_str1.find(' ', 0);
	while (begin1 != string::npos)
	{
		m_str1.replace(begin1, 1, "");
		begin1 = m_str1.find(' ', begin1);
	}
	//去除{ }
	auto first2 = m_str2.find_first_of('{');
	m_str2.replace(first2, 1, " ");
	first2 = m_str2.find_last_of('}');
	m_str2.replace(first2, 1, "\0");
	//去除所有空格
	auto begin2 = m_str2.find(' ', 0);
	while (begin2 != string::npos)
	{
		m_str2.replace(begin2, 1, "");
		begin2 = m_str2.find(' ', begin2);
	}
	vector<string> vStr1 = this->split(m_str1, ',');
	vector<string> vStr2 = this->split(m_str2, ',');
	auto beginv = vStr2.begin();
	auto endv = vStr2.end();
	for (auto i : vStr1)
	{
		//cout << i << endl;
		auto it = find(beginv, endv, i);
		if (it != endv)
		{
#if 0
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			cout << *it << endl;
			cout << i << endl;
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
#endif
		}
		else
		{
			cout << "########################################################################" << endl;
			//cout << *it << endl;
			cout <<"not have:"<< i << endl;
			cout << "m_str1:" << m_str1.c_str() <<"********"<< endl;
			cout << "m_str2:" << m_str2.c_str() << "********" << endl;
			for (auto j: vStr1)
			{
				cout << j << endl;
			}
			cout << "_______________________________________________________________"<<endl;
			for (auto j : vStr2)
			{
				cout << j << flush;
			}
			cout << endl;
			cout << "########################################################################" << endl;
		}
	}
	return true;
}