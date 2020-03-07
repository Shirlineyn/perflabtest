#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool is_intriangle(vector<float> dot, vector<float> A, vector<float> B, vector<float> C)
{
	float i = (A[0] - dot[0])*(B[1] - A[1]) - (B[0] - A[0])*(A[1] - dot[1]);
	float j = (B[0] - dot[0])*(C[1] - B[1]) - (C[0] - B[0])*(B[1] - dot[1]);
	float k = (C[0] - dot[0])*(A[1] - C[1]) - (A[0] - C[0])*(C[1] - dot[1]);

	return ( ((i > 0) && (j > 0) && (k > 0)) || ((i < 0) && (j < 0) && (k < 0)) );
}

float range(vector<float> A, vector<float> B)
{
	return sqrt((A[0] - B[0])*(A[0] - B[0]) + (A[1] - B[1])*(A[1] - B[1]));
}

bool is_onsegment(vector<float> dot, vector<float> A, vector<float> B)
{
	float i = (A[0] - dot[0])*(B[1] - A[1]) - (B[0] - A[0])*(A[1] - dot[1]);
	return( (i == 0) && (max(range(dot, A), range(dot,B)) < range(A,B)));
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Usage: "<< argv[0] << " <inputfile1name>.txt <inputfile2name>.txt" << endl;
		return -1;
	}

	ifstream infile1(argv[1]);
	ifstream infile2(argv[2]);

	if(!infile1.is_open() || !infile2.is_open())
	{
		cout << "Can't open the file! Exiting..." << endl;
		return -2;
	}

	vector<float> A(2, 0.0);
	vector<float> B(2, 0.0);
	vector<float> C(2, 0.0);
	vector<float> D(2, 0.0);

	infile1 >> A[0] >> A[1] >> B[0] >> B[1] >> C[0] >> C[1] >> D[0] >> D[1];
	infile1.close();
	
	vector<float> dot(2, 0.0);
	while( (infile2 >> dot[0]) && (infile2 >> dot[1]) )
	{
		if( ( (dot[0] == A[0]) && (dot[1] == A[1]) ) || ( (dot[0] == B[0]) && (dot[1] == B[1]) ) || 
			( (dot[0] == C[0]) && (dot[1] == C[1]) ) || ( (dot[0] == D[0]) && (dot[1] == D[1]) ) )
		{
			cout << 0 << endl;
		}
		else if(is_onsegment(dot, A, B) || is_onsegment(dot, B, C) || is_onsegment(dot, C, D) || is_onsegment(dot, D, A))
		{
			cout << 1 << endl;
		}
		else if(is_intriangle(dot, A, B, C) || is_intriangle(dot, C, D, A))
		{
			cout << 2 << endl;
		}
		else
		{
			cout << 3 << endl;
		}
	}
	infile2.close();

	return 0;
}
