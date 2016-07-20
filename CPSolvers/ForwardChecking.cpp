/*
 * ForwardChecking.cpp
 *
 *  Created on: 26/04/2016
 *      Author: dario
 */
#include "headers.h"
using namespace std;
#include <iostream>
#include <deque>
#include <string>


ForwardChecking::ForwardChecking(int problemSize_ ,std::string problemType, bool isOptimization_)
{
	this->isOptimization = isOptimization_;
	this->problemSize = problemSize_;




	this->problem = new KcolorGraphProblem();

	if(this->problemSize==4)
			this->problem->initializeExample();
	else
		this->problem->initialize(this->problemSize,1);

	if(this->problemSize<=20)
	{
		this->problem->printAllDomains();
		this->problem->printAllConstraints();
	}


}
ForwardChecking::ForwardChecking(string problemType, string instanceFilename, bool isOptimization_)
{
	this->isOptimization = isOptimization_;

	cout << "problemType: "<<problemType<<"."<<endl;

	FileHandler fileHandler(instanceFilename);

	this->problem = fileHandler.readInputFiles();
	this->problemSize = this->problem->getProblemSize();

}



/*
 * Initialize the Forward Checking algorithm: Generate a new problem and try to solve it.
 */
void ForwardChecking::Start(){

	cout << "\t\t\t\t Starting Forward Checking for K-coloring graph" << endl;

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
		}
		//checks if the graph finished instantiating all nodes.
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
bool ForwardChecking::label(int n)
{
	this->problem->saveBackupTemporalDomain(n);

	//go over each color of the graph "poping" each color.
	while(true)
	{
		//if there are no more colors in the domain of the variable: dead end.
		if(!this->problem->assignNextValue(n))
			break;
		else
		{
			//Check if the current assign is feasible
			//this->kproblem.CurrentColorGraph[n]->checkConstraintsPrint();
			//if(this->problem->pastConsistent(n))

			//this->kproblem.CurrentColorGraph.size() == n+1: last node reached.
			//the if have Short-circuit evaluation so if the current node is the last one, it's not needed
			//to call the method checkForward.
			if(problemSize== n+1 || this->problem->checkForward(n))
				return true;
		}
	}
	//Backtrack is needed, restore the backup made.
	if(n-1>=0)
	{
		this->problem->restoreBakupTemporalDomain(n);
		//Restore domain of variables filtered by node i-1.
		this->problem->restoreCheckForwardDeletions(n-1);
	}
	return false; //return false in the default case.
}
