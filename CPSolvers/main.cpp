#include <iostream>
#include <vector>
#include "headers.hpp"
using namespace std;
#include <stdlib.h>
#include <string>
#include <string.h>



bool handleParams(int argc, char* argv[], int &seed, string &problem, int &problemSize, string &algorithm, string &instanceFilename, bool& isOptimization);
void defaultErrorMessage(int argc, char* argv[]);

int main(int argc,char* argv[])
{

	int seed, problemSize;
	string algorithm,problemType;
	string instanceFilename ="";

	bool isOptimization=false;

	bool resp = handleParams(argc,argv,seed, problemType, problemSize, algorithm,instanceFilename, isOptimization);


	if(resp)
	{
		srand(seed);
		//srand(time(NULL));

		if(algorithm == "bt")
		{
			BackTrack * bt;

			if(instanceFilename!="")
			{
				bt = new BackTrack(problemType,instanceFilename, isOptimization);
			}
			else
			{
				bt = new BackTrack(problemSize,problemType, isOptimization);
			}

			bt->Start();
		}
		else if(algorithm == "fc")
		{
			ForwardChecking * fc;

			if(instanceFilename!="")
			{
				fc = new ForwardChecking(problemType,instanceFilename, isOptimization);
			}
			else
			{
				fc = new ForwardChecking(problemSize,problemType, isOptimization);
			}
			fc->Start();
		}
		else if(algorithm == "mfc")
		{
			MinimalForwardChecking * mfc;

			if(instanceFilename!="")
			{
				mfc = new MinimalForwardChecking(problemType,instanceFilename,isOptimization);
			}
			else
			{
				mfc = new MinimalForwardChecking(problemSize,problemType,isOptimization);
			}
			mfc->Start();
		}
		else if(algorithm == "btgbj")
		{
			BackTrackGbj * btgbj;

			if(instanceFilename!="")
			{
				btgbj = new BackTrackGbj(problemType,instanceFilename, isOptimization);
			}
			else
			{
				btgbj = new BackTrackGbj(problemSize,problemType, isOptimization);
			}
			btgbj->Start();

		}
		else
			defaultErrorMessage(argc,argv);

		return 0;
	}
}

bool handleParams(int argc, char* argv[], int &seed,string &problem, int &problemSize, string &algorithm, string &instanceFilename, bool& isOptimization )
{

	const int kExpectedArgc = 11;
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

		   }
		   else if(strcmp(argv[i], "-p")==0)
		   {
			   problem = argv[++i];
			   paramsCollected++;

		   }
		   else if(strcmp(argv[i], "-ps")==0)
		   {
			   problemSize = atoi(argv[++i]);
			   paramsCollected++;

		   }
		   else if(strcmp(argv[i], "-if")==0)
		   {
			   instanceFilename = argv[++i];
			   paramsCollected++;
		   }
		   else if(strcmp(argv[i], "-is")==0)
		   {
			   int is=0;
			   is = atoi(argv[++i]);

			   if(is==0)
				   isOptimization=false;
			   else
				   isOptimization=true;

			   paramsCollected++;

		   }
		   else if(strcmp(argv[i], "-a")==0)
		   {
			   algorithm = argv[++i];
			   paramsCollected++;
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
	   << "-if instanceFileName (do not specify -ps option using this)"
	   << "-is isOptimization (=1 if it is optimization problem, 0 otherwise)"
	   << "-a algorithm "
	   << endl
	   << "Options for problem are: ColorGraph" <<endl
	   << "Options for algorithm are: bt, fc, mfc" << endl
	   << "Examples: " << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -is 0 -a fc" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -is 0 -a bt" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -ps 5 -is 0 -a mfc" << endl
	   << "./CPSolvers -s 1 -p ColorGraph -if instances/dsjc125.1.col -is 0 -a mfc" << endl
	   << endl << endl
	   << "Current is:" << endl;

	   for (int i = 0; i < argc; ++i)
	   {
		   cout << " " << argv[i];
	   }
	   cout << endl;
}
