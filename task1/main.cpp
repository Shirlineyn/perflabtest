#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<float> const &input)
{
	for (auto const& i: input)
	{
		std::cout << i << " ";
	}
	cout << endl;
}

float percentile(vector<float> const &input, float fraction)
{
	float r = fraction*(input.size() - 1);
	int index = (int)r;
	return input[index] + (input[index + 1] - input[index])*(r - index);

}

float median(vector<float> const &input)
{
	int size = input.size();
	if(size%2 == 1)
	{
		return input[(int)(size/2)];
	}
	else
	{
		return (input[(int)(size/2)] + input[(int)(size/2) - 1])/2;
	}
}

float average(vector<float> const &input)
{
	float sum = 0.0;
	for (auto const& i: input)
	{
		sum += i;
	}
	sum /= input.size();
	return sum;
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

	vector<float> data;
	int tmp;
	
	while(infile >> tmp)
	{
		data.push_back((int)tmp);
	}

	infile.close();

	sort(data.begin(), data.end());
	
	cout << fixed;
	cout.precision(2);

	cout << percentile(data, 0.9) << endl;
	cout << median(data) << endl;
	cout << data[data.size() - 1] << endl;
	cout << data[0] << endl;
	cout << average(data) << endl;


	return 0;
}
