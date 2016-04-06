#include "headers.h"
using namespace std;
#include<iostream>
#include <stdlib.h>
#include <string>


/*
 * Initialize the whole instance of the problem
 */
void KcolorGraphProblem::initialize(int size, int orderingHeuristicOption){

	//Create n nodes
	deque<KcolorGraphNode*> colorGraph;
	this->CurrentColorGraph = colorGraph;

	int min,max;
	min = 1;
	max = size;
	int colorNumber;

	for(int i=0;i<size;i++) //create size number of nodes
	{


		KcolorGraphNode* node = new KcolorGraphNode(i+1);
		//Create a random number colors between 1 and N and push them to the node's original domain.
		colorNumber = min + (rand() % (int)(max - min + 1));
		for(int j=1;j<=colorNumber;j++)
		{

			node->originalColorDomain.push_back(std::to_string(j));
		}
		node->restoreDomain();
		this->CurrentColorGraph.push_back(node);
	}

	//-------------------------------------------------------------------------------------------
	//Initialize constraints from each node.
	int constraintNumber;
	bool useCandidateNode=true;
	for(int i=0;i<size;i++)
	{
		//loop in each node and select if has a link with current node.
		for(int j=0;j<size;j++)
		{
			if(j!=i)
			{
				constraintNumber = 0 + (rand() % (int)(100 + 1));
				if(constraintNumber>=50)
				{
					//note if the current has already a constraint with the selected note.
					useCandidateNode = true;
					for(int k=0;k<this->CurrentColorGraph[i]->constraints.size();k++)
					{
						if(this->CurrentColorGraph[i]->constraints[k]->ID == this->CurrentColorGraph[j]->ID)
						{
							useCandidateNode = false;
							break;
						}
					}
					if(useCandidateNode)
					{
						this->CurrentColorGraph[i]->constraints.push_back(this->CurrentColorGraph[j]);
						this->CurrentColorGraph[j]->constraints.push_back(this->CurrentColorGraph[i]);
					}
				}
			}
		}

	}

	//-------------------------------------------------------------------------------------

	this->BestOFValue = 0;


}


void KcolorGraphProblem::initializeExample()
{
	KcolorGraphNode* node1 = new KcolorGraphNode(1);
	KcolorGraphNode* node2 = new KcolorGraphNode(2);
	KcolorGraphNode* node3 = new KcolorGraphNode(3);
	KcolorGraphNode* node4 = new KcolorGraphNode(4);

	//setting the original domains of each node
	node1->originalColorDomain.push_back("Red");

	node2->originalColorDomain.push_back("Green");
	node2->originalColorDomain.push_back("Orange");

	node3->originalColorDomain.push_back("Blue");
	node3->originalColorDomain.push_back("Green");

	node4->originalColorDomain.push_back("Green");
	node4->originalColorDomain.push_back("Blue");
	node4->originalColorDomain.push_back("Red");

	//use original domains to restore for the first time.
	node1->restoreDomain();
	node2->restoreDomain();
	node3->restoreDomain();
	node4->restoreDomain();

	//-------------------------------------------------------------------------------------------
	//Initialize constraints from each node.
	node1->constraints.push_back(node2);
	node1->constraints.push_back(node3);
	node1->constraints.push_back(node4);
	//-------------
	node2->constraints.push_back(node1);
	node2->constraints.push_back(node3);
	node2->constraints.push_back(node4);
	//-------------
	node3->constraints.push_back(node1);
	node3->constraints.push_back(node2);
	node3->constraints.push_back(node4);
	//-------------
	node4->constraints.push_back(node1);
	node4->constraints.push_back(node2);
	node4->constraints.push_back(node3);
	//-------------------------------------------------------------------------------------



	//Initialize the current solution
	deque<KcolorGraphNode*> colorGraph;
	this->CurrentColorGraph = colorGraph;
	this->CurrentColorGraph.push_back(node1);
	this->CurrentColorGraph.push_back(node2);
	this->CurrentColorGraph.push_back(node3);
	this->CurrentColorGraph.push_back(node4);


	this->BestOFValue = 0;
}


/*
 * Restore the domain of all nodes from node k to the last.
 */
void KcolorGraphProblem::restoreDomainsFromK(int k){

	for(int i=k;i<this->CurrentColorGraph.size();i++)
	{
		//cout << "Restoring current domain of node: " << this->CurrentColorGraph[i]->ID << endl;
		this->CurrentColorGraph[i]->restoreDomain();
	}
}

/*
 * Check if the current solution is better than the best solution found.
 */
void KcolorGraphProblem::checkSetBestSolution() {

	//Pushing each different color in a deque in order to be able to count the colors and
	//print them in screen.
	deque<string> distinctColors;
	bool distinctColor=true;
	for(int i=0;i<this->CurrentColorGraph.size();i++){
		if(this->CurrentColorGraph[i]->Color != this->CurrentColorGraph[i]->defaultColor)
		{
			distinctColor = true;
			for(int j=0;j<distinctColors.size();j++)
			{
				if(this->CurrentColorGraph[i]->Color == distinctColors[j])
					distinctColor = false;
			}

			if(distinctColor)
				distinctColors.push_back(this->CurrentColorGraph[i]->Color);

		}
	}


	//Check if the current solution is the best solution.
	if(distinctColors.size()>this->BestOFValue)
	{
		//set best objective function value.
		this->BestOFValue =distinctColors.size();

		//Copy the current solution to the best solution.
		this->BestColorGraph.clear();
		for(int i=0;i<this->CurrentColorGraph.size();i++)
		{
			KcolorGraphNode *nodo1 = new KcolorGraphNode(this->CurrentColorGraph[i]->ID);
			nodo1->Color = this->CurrentColorGraph[i]->Color;
			this->BestColorGraph.push_back(nodo1);
		}


		cout << "Setting the best solution: "<<endl;
		cout << "Number of colors: " << distinctColors.size()<< endl;
		cout << "Configuration: " <<endl;
		for(int i=0;i<this->CurrentColorGraph.size();i++){
			cout <<"Node: " << this->CurrentColorGraph[i]->ID << " Color: "<< this->CurrentColorGraph[i]->Color<<endl;
		}
	}
}

/*
 * Check if the current instantiation of node n is consistent with previous nodes in the tree.
 */
bool KcolorGraphProblem::pastConsistent(int n)
{
	//Check if the graph is past consistent until the node n is equal to to check
	//the node n.
	return this->CurrentColorGraph[n]->checkConstraintsBreak();
}


/*
 * Print in screen the results of searching a solution.
 */
void KcolorGraphProblem::printFinalResults() {
	bool solucion;
	if(this->BestOFValue>0)
		solucion=true;
	if(solucion)
	{
		cout << "--------------------------------- Results of K-color Graph  ---------------------------------" <<endl;
		cout << "-----------The objective function value is:  " << this->BestOFValue << " (distinct colors)" <<endl;
		cout << "Printing the Graph " <<endl;
		for(int i=0;i<this->BestColorGraph.size();i++){
			cout << "----------------- Node: " << this->BestColorGraph[i]->ID << " - Color " <<this->BestColorGraph[i]->Color<<endl;
		}
	}
	else
		cout << "The graph doesn't have a solution"<<endl;
}
