#include <iostream>
#include <vector>
#include "headers.h"
using namespace std;
#include <stdlib.h>
#include <string>
#include <string.h>



bool handleParams(int argc, char* argv[], int &seed, string &problem, int &problemSize, string &algorithm, string &instanceFilename);
void defaultErrorMessage(int argc, char* argv[]);

int main(int argc,char* argv[])
{

	int seed, problemSize;
	string algorithm,problemType;
	string instanceFilename ="";

	bool resp = handleParams(argc,argv,seed, problemType, problemSize, algorithm,instanceFilename);
	if(resp)
	{
		srand(seed);
		//srand(time(NULL));

		if(algorithm == "bt")
		{
			BackTrack * bt;

			if(instanceFilename!="")
			{
				bt = new BackTrack(problemType,instanceFilename);
			}
			else
			{
				bt = new BackTrack(problemSize,problemType);
			}

			bt->Start();
		}
		else if(algorithm == "fc")
		{
			ForwardChecking * fc;

			if(instanceFilename!="")
			{
				fc = new ForwardChecking(problemType,instanceFilename);
			}
			else
			{
				fc = new ForwardChecking(problemSize,problemType);
			}
			fc->Start();
		}
		else if(algorithm == "mfc")
		{
			MinimalForwardChecking * mfc;

			if(instanceFilename!="")
			{
				//mfc = new MinimalForwardChecking(problemType,instanceFilename);
			}
			else
			{
				mfc = new MinimalForwardChecking(problemSize,problemType);
			}
			mfc->Start();
		}
		else
			defaultErrorMessage(argc,argv);

		return 0;
	}
}

bool handleParams(int argc, char* argv[], int &seed,string &problem, int &problemSize, string &algorithm, string &instanceFilename)
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
		   else if(strcmp(argv[i], "-if")==0)
		   {
			   instanceFilename = argv[++i];
			   paramsCollected++;
			   cout << "instance file name collected!"<<endl;
		   }
		   else if(strcmp(argv[i], "-a")==0)
		   {
			   algorithm = argv[++i];
			   paramsCollected++;
			   cout << "algorithm collected!"<<endl;
		   }
		}
		if(paramsCollected>=4)
			return true;
		else
		{
			return false;
			defaultErrorMessage(argc,argv);
		}
	}
	return true;

}
void defaultErrorMessage(int argc, char* argv[])
{
	cout << "Wrong number arguments." << endl
	   << "The syntax should be:" << endl
	   << "-s seed "
	   << "-p problem "
	   << "-ps problemSize "
	   << "-a algorithm "
	   << "-if instanceFileName (do not specify -ps option using this)"
	   << endl
	   << "Options for problem are: ColorGraph" <<endl
	   << "Options for algorithm are: bt, fc, mfc" << endl
	   << "Examples: " << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a fc" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a bt" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -a mfc" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -if instances/dsjc125.1.col -a mfc" << endl
	   << endl << endl
	   << "Current is:" << endl;

	   for (int i = 0; i < argc; ++i)
	   {
		   cout << " " << argv[i];
	   }
	   cout << endl;
}
