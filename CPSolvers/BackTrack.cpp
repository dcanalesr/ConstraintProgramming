/*
 * kColorBackTrack.cpp
 *
 *  Created on: 20/10/2015
 *      Author: dario
 */
#include "headers.h"
using namespace std;
#include <iostream>
#include <deque>


/*
 * Initialize the BackTrack algorithm: Generate a new problem and try to solve it.
 */
void BackTrack::StartKcolor(){

	cout << "\t\t\t\t Starting Backtrack for K-coloring graph" << endl;

	KcolorGraphProblem problem;

	this->kproblem = problem;
	int size = 15;
	this->kproblem.initializeExample();
	//this->kproblem.initialize(size,1);

	if(size<10)
	{
		this->printAllDomainsKColorGraph();
		this->printAllConstraintsKColorGraph();
	}

	//for each node in the color graph.
	for(int i=0;i<this->kproblem.CurrentGraph.size();i++)
	{

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
				//Restore domain of variables from i to the last.
				this->kproblem.restoreCompleteDomainsFromK(i);

			//return to the i-1 variable (-2 because the "for" will add 1 on the next loop).
			i-=2;
		}
		//check if the graph finished instantiating all nodes.
		if(i==this->kproblem.CurrentGraph.size()-1)
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
bool BackTrack::labelKColorNode(int n)
{
	//go over each color of the graph "poping" each color.
	while(true)
	{
		//if there are no more colors in the domain of the variable: dead end.
		if(this->kproblem.CurrentGraph[n]->temporalColorDomain.size()==0)
		{

			//restore the color of the node to "unpainted".
			this->kproblem.CurrentGraph[n]->AsignedColor = this->kproblem.CurrentGraph[n]->defaultColor;
			return false;
		}
		else
		{

			this->kproblem.CurrentGraph[n]->AsignedColor = this->kproblem.CurrentGraph[n]->temporalColorDomain[0];
			this->kproblem.CurrentGraph[n]->temporalColorDomain.pop_front();


			cout << "Instantiating the node: " << this->kproblem.CurrentGraph[n]->ID << " - color: " << this->kproblem.CurrentGraph[n]->AsignedColor <<endl;

			//this->kproblem.CurrentColorGraph[n]->checkConstraintsPrint();

			//Check if the current assign is feasible
			if(this->kproblem.pastConsistent(n))
				return true;
		}
	}
	return false; //return false in the default case.
}
/*
 * Print in the screen domains of all nodes in the graph.
 */
void BackTrack::printAllDomainsKColorGraph()
{
	for(int i=0;i<this->kproblem.CurrentGraph.size();i++)
	{
		this->kproblem.CurrentGraph[i]->printTemporalDomain();
	}
	cout << "------------------------------------------------"<<endl;
}

/*
 * Print in the screen constraints of all nodes in the graph.
 */
void BackTrack::printAllConstraintsKColorGraph()
{
	for(int i=0;i<this->kproblem.CurrentGraph.size();i++)
	{
		this->kproblem.CurrentGraph[i]->printConstraints();
	}
	cout << "------------------------------------------------"<<endl;
}
