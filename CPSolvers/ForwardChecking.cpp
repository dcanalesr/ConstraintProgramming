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
void ForwardChecking::StartKcolor(){

	cout << "\t\t\t\t Starting Forward Checking for K-coloring graph" << endl;

	KcolorGraphProblem problem;

	this->kproblem = problem;
	int size = 15;
	this->kproblem.initializeExample();
	//this->kproblem.initialize(size,1);

	this->printAllDomainsKColorGraph();
	this->printAllConstraintsKColorGraph();

	if(size<10)
	{
		this->printAllDomainsKColorGraph();
		this->printAllConstraintsKColorGraph();
	}

	//for each node in the color graph.
	for(int i=0;i<this->kproblem.CurrentColorGraph.size();i++)
	{

		//saving backup of temporal domain of current node, in case of backtrack needed.
		this->kproblem.saveBackupTemporalDomain(this->kproblem.CurrentColorGraph[i]);

		//even the first variable couldn't be instantiated without conflicts.
		if(i<0)
		{
			cout << "First node couldn't be instantiated." << endl;
			break;
		}
		//Trying to label variable i.
		else if(!labelKColorNode(i))
		{
			//couldn't instantiate the current variable:
			if(i-1>0)
			{
				//Restore domain of variables filtered by node i-1.
				this->kproblem.restoreAllDeletionsFromHistory(this->kproblem.CurrentColorGraph[i-1]);

				//Backtrack is needed, restore the backup made.
				this->kproblem.restoreBakupTemporalDomain(this->kproblem.CurrentColorGraph[i]);

			}

			//return to the i-1 variable (-2 because the "for" will add 1 on the next loop).
			i-=2;
		}
		//check if the graph finished instantiating all nodes.
		if(i==this->kproblem.CurrentColorGraph.size()-1)
		{

			this->kproblem.checkSetBestSolution();
			i--;
			break; //REMOVE THIS IN ORDER TO GET A OPTIMIZATION PROBLEM.
		}
	}
	this->kproblem.printFinalResults();
}



/*
 * Try to instantiate the node n in the graph, if any color of the domain couldn't be used
 * return false. Return true when found a success instantiation.
 */
bool ForwardChecking::labelKColorNode(int n)
{
	//go over each color of the graph "poping" each color.
	while(true)
	{
		//if there are no more colors in the domain of the variable: dead end.
		if(this->kproblem.CurrentColorGraph[n]->temporalColorDomain.size()==0)
		{

			//restore the color of the node to "unpainted".
			this->kproblem.CurrentColorGraph[n]->AsignedColor = this->kproblem.CurrentColorGraph[n]->defaultColor;
			return false;
		}
		else
		{

			//assign next color available
			this->kproblem.CurrentColorGraph[n]->AsignedColor = this->kproblem.CurrentColorGraph[n]->temporalColorDomain[0];
			this->kproblem.CurrentColorGraph[n]->temporalColorDomain.pop_front();


			cout << "Instantiating the node: " << this->kproblem.CurrentColorGraph[n]->ID << " - color: " << this->kproblem.CurrentColorGraph[n]->AsignedColor <<endl;

			//this->kproblem.CurrentColorGraph[n]->checkConstraintsPrint();

			//Check if the current assign is feasible
			if(this->kproblem.pastConsistent(n))
			{
				//this->kproblem.CurrentColorGraph.size() != n-1: last node reached.
				//the if have Short-circuit evaluation so if the current node is the last one, it's not needed
				//to call the method checkForward.
				if(this->kproblem.CurrentColorGraph.size() == n+1 || this->kproblem.checkForward(n))
					return true;
			}
		}
	}
	return false; //return false in the default case.
}
/*
 * Print in the screen domains of all nodes in the graph.
 */
void ForwardChecking::printAllDomainsKColorGraph()
{
	for(int i=0;i<this->kproblem.CurrentColorGraph.size();i++)
	{
		this->kproblem.CurrentColorGraph[i]->printTemporalDomain();
	}
	cout << "------------------------------------------------"<<endl;
}

/*
 * Print in the screen constraints of all nodes in the graph.
 */
void ForwardChecking::printAllConstraintsKColorGraph()
{
	for(int i=0;i<this->kproblem.CurrentColorGraph.size();i++)
	{
		this->kproblem.CurrentColorGraph[i]->printConstraints();
	}
	cout << "------------------------------------------------"<<endl;
}

