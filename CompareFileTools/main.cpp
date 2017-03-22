#include "KCompareFile.h"


int main()
{
	KCompareFile CompareFile;

	const char filename1[] = "mydx.txt";
	const char filename2[] = "pyd.txt";
	bool flag = CompareFile.OpenFile(filename1,filename2);
	if (flag)
	{
		while (1)
		{
			int result = CompareFile.ReadFile();
		//	cout << "**********************************************************************" << result << endl;
			if (result == 0)
			{
				break;
			}
			else if (result == -1)
			{
				break;
			}
			else
			{
				CompareFile.Compare();
			}
		}
	}

	//getchar();
	return true;
}