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


/*
 * Initialize the Forward Checking algorithm: Generate a new problem and try to solve it.
 */
void ForwardChecking::Start(){

	cout << "\t\t\t\t Starting Forward Checking for K-coloring graph" << endl;



	this->problem = new KcolorGraphProblem();
	this->problemSize = 4;

	if(this->problemSize==4)
		this->problem->initializeExample();
	else
		this->problem->initialize(this->problemSize,1);

	if(this->problemSize<10)
	{
		this->problem->printAllDomains();
		this->problem->printAllConstraints();
	}

	//for each node in the color graph.
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
			if(i-1>0)
			{
				//Restore domain of variables filtered by node i-1.
				this->problem->restoreCheckForwardDeletions(i-1);
			}

			//return to the i-1 variable (-2 because the "for" will add 1 on the next loop).
			i-=2;
		}
		//checks if the graph finished instantiating all nodes.
		if(i==this->problemSize-1)
		{

			this->problem->checkSetBestSolution();
			i--;
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

	//saving backup of temporal domain of current node, in case of backtrack needed.
	this->problem->saveBackupTemporalDomain(n);

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
			{
				//this->kproblem.CurrentColorGraph.size() == n+1: last node reached.
				//the if have Short-circuit evaluation so if the current node is the last one, it's not needed
				//to call the method checkForward.
				if(problemSize== n+1 || this->problem->checkForward(n))
					return true;
			}
		}
	}
	//Backtrack is needed, restore the backup made.
	this->problem->restoreBakupTemporalDomain(n);
	return false; //return false in the default case.
}
