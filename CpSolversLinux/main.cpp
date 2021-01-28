#include <iostream>
#include <vector>
#include "headers.hpp"
using namespace std;
#include <stdlib.h>
#include <string>
#include <string.h>



bool handleParams(int argc, char* argv[], int &seed, string &problem, int &problemSize, string &algorithm, string &instanceFilename, bool& isOptimization, bool &forCsv);
void defaultErrorMessage(int argc, char* argv[]);

int main(int argc,char* argv[])
{

	int seed, problemSize;
	string algorithm,problemType;
	string instanceFilename ="";

	bool isOptimization=false;
	bool forCsv = false;

	bool resp = handleParams(argc,argv,seed, problemType, problemSize, algorithm,instanceFilename, isOptimization, forCsv);


	if(resp)
	{
		srand(seed);
		//srand(time(NULL));

		if(algorithm == "bt")
		{
			BackTrack * bt;

			if(instanceFilename!="")
			{
				bt = new BackTrack(problemType,instanceFilename, isOptimization, forCsv);

			}
			else
			{
				bt = new BackTrack(problemSize,problemType, isOptimization, forCsv);
			}
			bt->Start();
		}
		else if(algorithm == "fc")
		{
			ForwardChecking * fc;

			if(instanceFilename!="")
			{
				fc = new ForwardChecking(problemType,instanceFilename, isOptimization, forCsv);
			}
			else
			{
				fc = new ForwardChecking(problemSize,problemType, isOptimization, forCsv);
			}
			fc->Start();
		}
		else if(algorithm == "mfc")
		{
			MinimalForwardChecking * mfc;

			if(instanceFilename!="")
			{
				mfc = new MinimalForwardChecking(problemType,instanceFilename,isOptimization, forCsv);
			}
			else
			{
				mfc = new MinimalForwardChecking(problemSize,problemType,isOptimization, forCsv);
			}
			mfc->Start();
		}
		else if(algorithm == "btgbj")
		{
			BackTrackGbj * btgbj;

			if(instanceFilename!="")
			{
				btgbj = new BackTrackGbj(problemType,instanceFilename, isOptimization, forCsv);
			}
			else
			{
				btgbj = new BackTrackGbj(problemSize,problemType, isOptimization, forCsv);
			}
			btgbj->Start();

		}
		else if(algorithm == "btcbj")
		{
			BackTrackCbj * btcbj;

			if(instanceFilename!="")
			{
				btcbj = new BackTrackCbj(problemType,instanceFilename, isOptimization, forCsv);
			}
			else
			{
				btcbj = new BackTrackCbj(problemSize,problemType, isOptimization, forCsv);
			}
			btcbj->Start();

		}
		else
			defaultErrorMessage(argc,argv);

		return 0;
	}
}

bool handleParams(int argc, char* argv[], int &seed,string &problem, int &problemSize, string &algorithm, string &instanceFilename, bool& isOptimization,bool &forCsv)
{

	const int kExpectedArgc = 11;
	if (argc < kExpectedArgc)
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
		   else if(strcmp(argv[i], "-csv")==0)
		   {
			   forCsv = true;
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
	   << "-ps problemSize do not specify -if option using this)"
	   << "-if instanceFileName (do not specify -ps option using this)"
	   << "-is isOptimization"
	   << "-a algorithm "
	   << "-csv (optional to print quiet results with comma separated)"
	   << endl
	   << "Options for problem are: ColorGraph" <<endl
	   << "Options for algorithm are: bt, fc, mfc, btgbj, btcbj " << endl
	   << "Options for isOptimization are: 1 if it is optimization problem, 0 otherwise"
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
