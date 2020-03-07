#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct segment
{
	int intime;
	int outtime;
};

int timetonum(string timestr)
{
	string h;
	h = timestr.substr(0, timestr.find(":"));
	timestr.erase(0, timestr.find(":") + 1);

	return stoi(timestr) + 60*(stoi(h) - 8);
}

string numtotime(int timeint)
{
	string h = to_string((int)(timeint/60 + 8));
	string m = to_string(timeint%60);
	if(m.length() == 1)
	{
		m = "0" + m;
	}
	
	return h + ":" + m;
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage: "<< argv[0] << " <inputfilename>.txt" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	if(!infile.is_open())
	{
		cout << "Can't open the file! Exiting..." << endl;
		return -2;
	}

	vector<int> indata;
	vector<int> outdata;
	string tmpin, tmpout;
	
	while((infile >> tmpin) && (infile >> tmpout))
	{
		indata.push_back(timetonum(tmpin));
		outdata.push_back(timetonum(tmpout));
	}
	infile.close();
	
	sort(indata.begin(), indata.end());
	sort(outdata.begin(), outdata.end());


	
	int currpeople = 0;
	int maxpeople = 0;
	int currtime = 0;
	vector<segment> maxsegs;
	segment currseg;

	currseg.intime = 0;


	while(!indata.empty() && !outdata.empty())
	{
		while(indata[0] == outdata[0])
		{
			indata.erase(indata.begin());
			outdata.erase(outdata.begin());
		}
		//indata empties first
		if(indata[0] < outdata[0])
		{
			currpeople++;
			if(currpeople == maxpeople)
			{
				currseg.intime = indata[0];
			}
			else if(currpeople > maxpeople)
			{
				maxpeople = currpeople;
				maxsegs.clear();
				currseg.intime = indata[0];
			}
			indata.erase(indata.begin());

		}
		else
		{
			if(currpeople == maxpeople)
			{
				currseg.outtime = outdata[0];
				maxsegs.push_back(currseg);
			}
			currpeople--;
			outdata.erase(outdata.begin());
		}
	}
	if(currpeople == maxpeople)
	{
		currseg.outtime = outdata[0];
		maxsegs.push_back(currseg);
	}

	while(!maxsegs.empty())
	{
		currseg = maxsegs[0];
		maxsegs.erase(maxsegs.begin());
		cout << numtotime(currseg.intime) << " " << numtotime(currseg.outtime) << endl;
	}
	


	return 0;
}
