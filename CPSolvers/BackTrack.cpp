/*
 * kColorBackTrack.cpp
 *
 *  Created on: 20/10/2015
 *      Author: dario
 */
#include "headers.h"
using namespace std;
#include<iostream>
#include <deque>

void BackTrack::StartKcolor(){

	cout << "\t\t\t\t Starting Backtrack for K-coloring graph" << endl;

	KcolorGraphProblem problem;

	this->kproblem = problem;
	int size = 5;
	this->kproblem.initialize(5);

	if(size<10)
	{
		this->printAllDomainsKColorGraph();
		this->printAllConstraintsKColorGraph();
	}

	//for each node in the color graph.
	for(int i=0;i<this->kproblem.CurrentColorGraph.size();i++)
	{
		cout << "Current node: "<<this->kproblem.CurrentColorGraph[i]->ID<<endl;

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
				this->kproblem.restoreDomainsFromK(i);

			//return to the i-1 variable (-2 because the "for" will add 1).
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
 * Print in the screen domains of all nodes in the graph.
 */
void BackTrack::printAllDomainsKColorGraph()
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
void BackTrack::printAllConstraintsKColorGraph()
{
	for(int i=0;i<this->kproblem.CurrentColorGraph.size();i++)
	{
		this->kproblem.CurrentColorGraph[i]->printConstraints();
	}
	cout << "------------------------------------------------"<<endl;
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
		if(this->kproblem.CurrentColorGraph[n]->temporalColorDomain.size()==0)
		{

			//restore the color of the node to "unpainted".
			this->kproblem.CurrentColorGraph[n]->Color = this->kproblem.CurrentColorGraph[n]->defaultColor;

			cout << "--------------------- No more colors in the domain of node: "<< this->kproblem.CurrentColorGraph[n]->ID <<endl;
			return false;
		}
		else
		{

			this->kproblem.CurrentColorGraph[n]->Color = this->kproblem.CurrentColorGraph[n]->temporalColorDomain[0];
			this->kproblem.CurrentColorGraph[n]->temporalColorDomain.pop_front();

			cout << "-----------------------------------------------------------------"<<endl;
			cout << "++Instantiating the node: " << this->kproblem.CurrentColorGraph[n]->ID << " - color: " << this->kproblem.CurrentColorGraph[n]->Color << "++"<<endl;

			this->kproblem.CurrentColorGraph[n]->checkConstraintsPrint();

			if(this->kproblem.CurrentColorGraph[n]->checkConstraintsBreak())
				return true;
		}
	}
	return false; //return false in the default case.
}

