#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define C_SIZE 5
#define D_TIME 16

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage: "<< argv[0] << " <inputdirectoryname>" << endl;
		return -1;
	}
	string dir(argv[1]);

	float sumlen[D_TIME] = {0.0};
	float tmp = 0.0;

	for (int i = 1; i < C_SIZE + 1; i++)
	{
		ifstream infile(dir + "/Cash" + to_string(i) + ".txt");
		for (int j = 0; j < D_TIME; j++)
		{
			infile >> tmp;
			sumlen[j] += tmp;
		}
		infile.close();
	}


	int maxindex = 0;
	float maxlen = 0.0;

	for (int i = 0; i < D_TIME; i++)
	{
		if(sumlen[i] > maxlen)
		{
			maxindex = i;
			maxlen = sumlen[i];
		}
	}
	cout << maxindex + 1 << endl;


	return 0;
}
