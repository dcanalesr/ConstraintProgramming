#include <iostream>
#include <vector>
#include "headers.h"
using namespace std;
#include <stdlib.h>
#include <string>
#include <string.h>



bool handleParams(int argc, char* argv[], int &seed, string &problem, int &problemSize, string &algorithm);
void defaultErrorMessage(int argc, char* argv[]);

int main(int argc,char* argv[])
{

	int seed, problemSize;
	string algorithm,problem;

	bool resp = handleParams(argc,argv,seed, problem, problemSize, algorithm);
	if(resp)
	{
		srand(seed);
		//srand(time(NULL));

		if(algorithm == "bt"){
			BackTrack backTrack(problemSize,problem);
			backTrack.Start();
		}
		else if(algorithm == "fc")
		{
			ForwardChecking forwardChecking(problemSize,problem);
			forwardChecking.Start();
		}
		else if(algorithm == "mfc")
		{
			ForwardChecking forwardChecking(problemSize,problem);
			forwardChecking.Start();
		}
		else
			defaultErrorMessage(argc,argv);

		return 0;
	}
}

bool handleParams(int argc, char* argv[], int &seed,string &problem, int &problemSize, string &algorithm)
{

	const int kExpectedArgc = 9;
	if (argc != kExpectedArgc)
	{
		defaultErrorMessage(argc,argv);
	    return false;
	}
	else
	{
		int paramsCollected =0;
		for (int i = 0; i < argc; ++i)
		{
		   if(strcmp(argv[i], "-s")==0)
		   {
			   seed = atoi(argv[++i]);
			   paramsCollected++;
			   cout << "seed collected!"<<endl;
		   }
		   else if(strcmp(argv[i], "-p")==0)
		   {
			   problem = argv[++i];
			   paramsCollected++;
			   cout << "problem collected!"<<endl;
		   }
		   else if(strcmp(argv[i], "-ps")==0)
		   {
			   problemSize = atoi(argv[++i]);
			   paramsCollected++;
			   cout << "problem size collected!"<<endl;
		   }
		   else if(strcmp(argv[i], "-a")==0)
		   {
			   algorithm = argv[++i];
			   paramsCollected++;
			   cout << "algorithm collected!"<<endl;
		   }
		}
		if(paramsCollected==4)
			return true;
		else
		{
			return false;
			defaultErrorMessage(argc,argv);
		}
	}

}
void defaultErrorMessage(int argc, char* argv[])
{
	cout << "Wrong number arguments." << endl
	   << "The syntax should be:" << endl
	   << "-s seed "
	   << "-p problem "
	   << "-ps problemSize "
	   << "-a algorithm "
	   << endl
	   << "Options for problem are: ColorGraph" <<endl
	   << "Options for algorithm are: bt, fc, mfc" << endl
	   << "Examples: " << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a fc" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a bt" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a mfc" << endl
	   << endl << endl
	   << "Current is:" << endl;

	   for (int i = 0; i < argc; ++i)
	   {
		   cout << " " << argv[i];
	   }
	   cout << endl;
}
