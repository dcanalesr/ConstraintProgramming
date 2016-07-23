#include "headers.hpp"
using namespace std;
#include <iostream>
#include <deque>


BackTrack::BackTrack(int problemSize_,std::string problemType, bool isOptimization_)
{

	this->isOptimization = isOptimization_;
	this->problemSize = problemSize_;



	if(problemType =="ColorGraph")
		this->problem = new KcolorGraphProblem();
	else
		this->problem = new KcolorGraphProblem();

	cout << "problemType: "<<problemType<<"."<<endl;


	if(this->problemSize==4)
			this->problem->initializeExample();
	else if(this->problemSize==7)
				this->problem->initializeExampleBackTrackGbj();
	else
		this->problem->initialize(this->problemSize,1);

	if(this->problemSize<=10)
	{
		this->problem->printAllDomains();
		this->problem->printAllConstraints();
	}



	this->problem->initializeAncestorsFutureConnectedVariables();

}

BackTrack::BackTrack(string problemType, string instanceFilename, bool isOptimization_)
{
	this->isOptimization = isOptimization_;


	cout << "problemType: "<<problemType<<"."<<endl;

	FileHandler fileHandler(instanceFilename);

	this->problem = fileHandler.readInputFiles();
	this->problemSize = this->problem->getProblemSize();

	this->problem->printAllConstraints();

	this->problem->initializeAncestorsFutureConnectedVariables();


}


/*
 * Initialize the BackTrack algorithm: Generate a new problem and try to solve it.
 */
void BackTrack::Start(){

	cout << "\t\t\t\t Starting Backtrack for K-coloring graph" << endl;


	Control::resetElapsedTime();

	//for each node in the graph.
	for(int i=0;i<this->problemSize;i++)
	{

		//even the first variable couldn't be instantiated without conflicts.
		if(i<0)
		{
			cout << "First node couldn't be instantiated." << endl;
			break;
		}


		//Trying to label variable i.
		else if(!label(i))
		{
			//return to the i-1 variable (-2 because the "for" will add 1 on the next loop).
			i-=2;
			++this->problem->numberOfDeadEnds;
		}
		//check if the graph finished instantiating all nodes.

		if(i==this->problemSize-1)
		{


			this->problem->checkSetBestSolution();
			i--;
			if(!this->isOptimization)
				break; //REMOVE THIS IN ORDER TO GET A OPTIMIZATION PROBLEM.
		}
	}


	this->problem->printFinalResults();
}






/*
 * Try to instantiate the node n in the graph, if any color of the domain couldn't be used
 * return false. Return true when found a success instantiation.
 */
bool BackTrack::label(int n)
{
	//go over each color of the graph "poping" each color.
	while(true)
	{
		//if there are no more colors in the domain of the variable: dead end.
		if(!this->problem->assignNextValue(n))
			break;
		else
		{
			//this->kproblem.CurrentColorGraph[n]->checkConstraintsPrint();

			//Check if the current assign is feasible
			if(this->problem->pastConsistent(n))
				return true;
		}
	}
	//Backtrack is needed, restore the backup made.
	if(n-1>=0)
	{
		this->problem->restoreDomain(n);
	}
	return false; //return false in the default case.
}
