#include "headers.hpp"
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>

string ptab = "....";

//TODO: Implement destruction of dynamic pointers to nodes generated with new.

KcolorGraphProblem::KcolorGraphProblem()
{
	this->BestOFValue = 50000000;
	this->numberOfInstantiations=0;
	numberOfChecks=0;

	this->numberOfDeadEnds=0;
	this->numberOfConstraints=0;
	this->meanOfConstraintsPerNode=0;
	this->numberOfNodesUnderMeanConstraints=0;
	this->numberOfNodesOverMeanConstraints=0;
	this->meanOfDomainSizePerNode=0;
	this->numberOfNodesUnderMeanDomainSize=0;
	this->numberOfNodesOverMeanDomainSize=0;

}

/*
 * Initialize the whole instance of the problem
 */
void KcolorGraphProblem::initialize(int size, int orderingHeuristicOption)
{

	//Create n nodes
	//deque<KcolorGraphNode*> colorGraph;
	//this->CurrentGraph = colorGraph;

	int min, max;
	min = 1;
	max = size;
	int colorNumber;

	for (int i = 0; i < size; i++) //create size number of nodes
	{

		KcolorGraphNode* node = new KcolorGraphNode(i);
		//Create a random number colors between 1 and N and push them to the node's original domain.
		colorNumber = min + (rand() % (int) (max - min + 1));
		for (int j = 0; j < colorNumber; j++)
		{

			node->originalColorDomain.push_back(std::to_string(j));
		}
		node->restoreDomain();
		this->CurrentGraph.push_back(node);
	}

	//-------------------------------------------------------------------------------------------
	//Initialize constraints from each node.
	int constraintNumber;
	bool useCandidateNode = true;
	for (int i = 0; i < size; i++)
	{
		//loop in each node and select if has a link with current node.
		for (int j = 0; j < size; j++)
		{
			if (j != i)
			{
				constraintNumber = 0 + (rand() % (int) (100 + 1));
				if (constraintNumber >= 50)
				{
					//note if the current has already a constraint with the selected note.
					useCandidateNode = true;
					for (int k = 0;
							k < this->CurrentGraph[i]->constraints.size(); k++)
					{
						if (this->CurrentGraph[i]->constraints[k]->ID == this->CurrentGraph[j]->ID)
						{
							useCandidateNode = false;
							break;
						}
					}
					if (useCandidateNode)
					{
						this->CurrentGraph[i]->constraints.push_back(
								this->CurrentGraph[j]);
						this->CurrentGraph[j]->constraints.push_back(
								this->CurrentGraph[i]);
					}
				}
			}
		}

	}

	//-------------------------------------------------------------------------------------

}

void KcolorGraphProblem::computeProblemTopographyStatistics()
{


	//Compute number of total constraints
	//compute mean of constraints per node
	//compute mean size of domains.


	for(int i=0;i<this->CurrentGraph.size();i++)
	{
		this->numberOfConstraints += this->CurrentGraph[i]->constraints.size();
		this->meanOfConstraintsPerNode += this->CurrentGraph[i]->constraints.size();
		this->meanOfDomainSizePerNode += this->CurrentGraph[i]->originalColorDomain.size();
	}

	this->meanOfConstraintsPerNode = this->meanOfConstraintsPerNode/this->CurrentGraph.size();
	this->meanOfDomainSizePerNode = this->meanOfDomainSizePerNode / this->CurrentGraph.size();


	//compute number of nodes with more constraints than the mean per node.
	//compute number of nodes with less constraints than the mean per node.

	//compute number of nodes with domains greater than the mean.
	//compute number of nodes with domains bigger than the mean.


	for(int i=0;i<this->CurrentGraph.size();i++)
	{
		if(this->CurrentGraph[i]->constraints.size() < this->meanOfConstraintsPerNode)
			++this->numberOfNodesUnderMeanConstraints;
		else
			++this->numberOfNodesOverMeanConstraints;

		if(this->CurrentGraph[i]->originalColorDomain.size() < this->meanOfDomainSizePerNode)
			++this->numberOfNodesUnderMeanDomainSize;
		else
		{
			++this->numberOfNodesOverMeanDomainSize;
		}

	}
}



void KcolorGraphProblem::initializeExample()
{
	/*
	 * This example was used in the paper of "Minimal Forward Checking" in https://www.researchgate.net/publication/3562041_Minimal_forward_checking
	 */

	cout << "-- Initializing premade example of size 4 from Paper of 'Minimal Forward Checking'"<<endl;

	KcolorGraphNode* node1 = new KcolorGraphNode(0);
	KcolorGraphNode* node2 = new KcolorGraphNode(1);
	KcolorGraphNode* node3 = new KcolorGraphNode(2);
	KcolorGraphNode* node4 = new KcolorGraphNode(3);

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
	this->CurrentGraph = colorGraph;
	this->CurrentGraph.push_back(node1);
	this->CurrentGraph.push_back(node2);
	this->CurrentGraph.push_back(node3);
	this->CurrentGraph.push_back(node4);

}

void KcolorGraphProblem::initializeExampleBackTrackGbj()
{

	cout << "-- Initializing premade example of size 7  (rina dechter example) for 'Back Track + GBJ'"<<endl;

	KcolorGraphNode* node1 = new KcolorGraphNode(0);
	KcolorGraphNode* node2 = new KcolorGraphNode(1);
	KcolorGraphNode* node3 = new KcolorGraphNode(2);
	KcolorGraphNode* node4 = new KcolorGraphNode(3);
	KcolorGraphNode* node5 = new KcolorGraphNode(4);
	KcolorGraphNode* node6 = new KcolorGraphNode(5);
	KcolorGraphNode* node7 = new KcolorGraphNode(6);


	//setting the original domains of each node
	node1->originalColorDomain.push_back("red");
	node1->originalColorDomain.push_back("blue");
	node1->originalColorDomain.push_back("green");

	node2->originalColorDomain.push_back("Blue");
	node2->originalColorDomain.push_back("Green");

	node3->originalColorDomain.push_back("Red");
	node3->originalColorDomain.push_back("Blue");

	node4->originalColorDomain.push_back("Red");
	node4->originalColorDomain.push_back("Blue");

	node5->originalColorDomain.push_back("Blue");
	node5->originalColorDomain.push_back("Green");

	node6->originalColorDomain.push_back("Red");
	node6->originalColorDomain.push_back("Green");
	node6->originalColorDomain.push_back("Teal");

	node7->originalColorDomain.push_back("Red");
	node7->originalColorDomain.push_back("Blue");


	//use original domains to restore for the first time.
	node1->restoreDomain();
	node2->restoreDomain();
	node3->restoreDomain();
	node4->restoreDomain();
	node5->restoreDomain();
	node6->restoreDomain();
	node7->restoreDomain();


	//-------------------------------------------------------------------------------------------
	//Initialize constraints from each node.
	node1->constraints.push_back(node2);
	node1->constraints.push_back(node3);
	node1->constraints.push_back(node4);
	//-------------
	node2->constraints.push_back(node1);
	node2->constraints.push_back(node6);

	//-------------
	node3->constraints.push_back(node1);
	node3->constraints.push_back(node7);

	//-------------
	node4->constraints.push_back(node1);
	node4->constraints.push_back(node7);

	//-------------
	node5->constraints.push_back(node6);
	node5->constraints.push_back(node7);

	//-------------
	node6->constraints.push_back(node2);
	node6->constraints.push_back(node5);

	//-------------
	node7->constraints.push_back(node1);
	node7->constraints.push_back(node3);
	node7->constraints.push_back(node4);
	node7->constraints.push_back(node5);

	//-------------------------------------------------------------------------------------

	//Initialize the current solution
	deque<KcolorGraphNode*> colorGraph;
	this->CurrentGraph = colorGraph;
	this->CurrentGraph.push_back(node1);
	this->CurrentGraph.push_back(node2);
	this->CurrentGraph.push_back(node3);
	this->CurrentGraph.push_back(node4);
	this->CurrentGraph.push_back(node5);
	this->CurrentGraph.push_back(node6);
	this->CurrentGraph.push_back(node7);
}



/*
 * Restore the domain of all nodes from node k to the last.
 */
void KcolorGraphProblem::restoreCompleteDomainsFromK(int k)
{

	for (int i = k; i < this->CurrentGraph.size(); i++)
	{
		//cout << "Restoring current domain of node: " << this->CurrentColorGraph[i]->ID << endl;
		this->CurrentGraph[i]->restoreDomain();
	}
}

/*
 * Check if the current solution is better than the best solution found.
 */
void KcolorGraphProblem::checkSetBestSolution()
{

	//Pushing each different color in a deque in order to be able to count the colors and
	//print them in screen.
	deque<string> distinctColors;
	bool distinctColor = true;
	for (int i = 0; i < this->CurrentGraph.size(); i++)
	{
		if (this->CurrentGraph[i]->AsignedColor != this->CurrentGraph[i]->defaultColor) //is diferent from default
		{
			distinctColor = true;
			for (int j = 0; j < distinctColors.size(); j++)
			{
				//checking if the current color is in the list of distinct colors
				if (this->CurrentGraph[i]->AsignedColor == distinctColors[j])
				{
					distinctColor = false;
					break;
				}
			}

			if (distinctColor) //if isn't in the list of distinct colors: it is added.
				distinctColors.push_back(this->CurrentGraph[i]->AsignedColor);

		}
	}


	//Check if the current solution is the best solution.
	if (distinctColors.size() < this->BestOFValue)
	{
		//set best objective function value.
		this->BestOFValue = distinctColors.size();

		//Copy the current solution to the best solution.
		this->BestGraph.clear();
		for (int i = 0; i < this->CurrentGraph.size(); i++)
		{
			KcolorGraphNode *nodo1 = new KcolorGraphNode( this->CurrentGraph[i]->ID);
			nodo1->AsignedColor = this->CurrentGraph[i]->AsignedColor;
			this->BestGraph.push_back(nodo1);
		}

		cout << "Setting the best solution: " << distinctColors.size() << endl;

		/*
		cout << "Configuration: " << endl;
		for (int i = 0; i < this->CurrentGraph.size(); i++)
		{
			cout << "Node: " << this->CurrentGraph[i]->ID << " Color: "
					<< this->CurrentGraph[i]->AsignedColor << endl;
		}
		*/
	}
}

/*
 * Check if the current instantiation of node n is consistent with previous nodes in the tree.
 */
bool KcolorGraphProblem::pastConsistent(int nodeIndex)
{
	//Check if the graph is past consistent until the node n is equal the node n.
	return this->CurrentGraph[nodeIndex]->checkPastConstraintsBreak();
}

bool KcolorGraphProblem::pastConsistentAddingToConflictSet(int nodeIndex)
{
	return this->CurrentGraph[nodeIndex]->checkPastConstraintsBreakAddingToConflictSet();
}



/*
 * Filters the domain future variable of the node i, based on the current color of that node.
 */
bool KcolorGraphProblem::checkForward(int nodeIndex)
{
	std::map<int,KcolorGraphNode *>::iterator futureIt;

	KcolorGraphNode * checkNode = this->CurrentGraph[nodeIndex];

	for(futureIt = checkNode->futureConnectedVariables.begin(); futureIt!= checkNode->futureConnectedVariables.end();++futureIt)
	{
		KcolorGraphNode * futureNode = futureIt->second;

		cout << ptab << "filtering domain of the node ID:" << futureNode->ID << endl;

		//for each color in the domain of that node look his temporalDomain
		for (int k = 0; k < futureNode->temporalColorDomain.size(); k++)
		{
			//if the current assigned color == color of the domain.
			++numberOfChecks;
			//cout << "------------------------------------------------------------------->Number of checks: "<< numberOfChecks << " - with color: "<<futureNode->temporalColorDomain[k]<<endl;
			if (checkNode->AsignedColor == futureNode->temporalColorDomain[k])
			{

				//cout << ptab << ptab<< "Deleting value: " << this->CurrentGraph[nodeIndex]->constraints[j]->temporalColorDomain[k] << " of the node: ID:"<<this->CurrentGraph[nodeIndex]->constraints[j]->ID<< endl;

				//Add the deleted value to history
				this->addDomainDeletionToHistory(checkNode, futureNode, futureNode->temporalColorDomain[k]);

				//delete in temporalColorDomain
				futureNode->temporalColorDomain.erase(futureNode->temporalColorDomain.begin() + k);

				futureNode->printTemporalDomain();


				//If there is a node in the constraints that reach 0 colors in his domains, the future node j
				//will reach a dead end.
				if (futureNode->temporalColorDomain.size() == 0)
				{
					cout << ptab << ptab << ptab << "Domain of the node: ID:" << futureNode->ID << " empty " << endl;

					this->restoreAllDeletionsFromHistory(checkNode);

					return false;
				}
				k--;//one color was deleted in the domain of the futureNode -> k should stay the same.
			}
		}

	}
	//return true only if all domains of the future variables could be filtered successfully
	return true;
}

bool KcolorGraphProblem::minimalCheckForward(int nodeIndex)
{

	std::map<int,KcolorGraphNode *>::iterator futureIt;

	KcolorGraphNode * checkNode = this->CurrentGraph[nodeIndex];

	//for each node from node i+1, filter the domains of the future nodes.
	for(futureIt = checkNode->futureConnectedVariables.begin(); futureIt!= checkNode->futureConnectedVariables.end();++futureIt)
	{
		KcolorGraphNode * futureNode = futureIt->second;


		cout << ptab << " Node:" <<checkNode->ID << " searching for valid value in domain of node:"<<futureNode->ID <<endl;
		//for each color in the domain of that node look his temporalDomain
		for (int k = 0; k < futureNode->temporalColorDomain.size(); k++)
		{



			//if the current assigned color == color of the domain.
			++numberOfChecks;
			//cout << "------------------------------------------------------------------->Number of checks: "<< numberOfChecks << " - with color: "<<futureNode->temporalColorDomain[k]<< "-> ";
			if (checkNode->AsignedColor == futureNode->temporalColorDomain[k])
			{
				cout << ptab << ptab<< "Deleting value:" << futureNode->temporalColorDomain[k] << "(node "<<futureNode->ID<<")"<< endl;

				//Add the deleted value to history

				this->addDomainDeletionToHistory(checkNode,futureNode,futureNode->temporalColorDomain[k]);
				futureNode->temporalColorDomain.erase(futureNode->temporalColorDomain.begin()+ k);



				/*
				 * Waking up all minimal check Forward from node0 to before the node who deleted the value.
				 */
				if(checkNode->ID-1>=0 && futureNode->temporalColorDomain.size()!=0)
					this->wakeUpMinimalFilters(futureNode->ID, checkNode->ID);





				//If there is a node in the constraints that reach 0 colors in his domains, the future node j
				//will reach a dead end.
				if (futureNode->temporalColorDomain.size() == 0)
				{
					cout << ptab << ptab << ptab << "Domain of the node: ID:" << futureNode->ID << " empty " << endl;

					this->restoreAllDeletionsFromHistory(checkNode);

					return false;
				}
				k--;//one color was deleted in the domain of the futureNode -> k should stay the same.
			}
			else
			{
				//If this line is reached, one value consistent has been found.
				//Because this is minimal forward checking, the algorithm stop filtering for this node here.
				cout << ptab << ptab << ptab << "Value:" << futureNode->temporalColorDomain[k] << " valid! " << " (node: "<<futureNode->ID<<")"<< endl;
				break;
			}
		}

	}
	//return true only if all domains of the future variables could be filtered successfully
	return true;

}

/*
 * Perform a minimal check forward from node0  until before nodeEnd. If the future node run out of
 */
bool KcolorGraphProblem::wakeUpMinimalFilters(int futureNodeIndex, int indexNodeEndFilter)
{
	KcolorGraphNode * futureNode = this->CurrentGraph[futureNodeIndex];

	cout << endl<<ptab << "**** Waking up filterings for Node:" << futureNode->ID << endl;

	KcolorGraphNode * checkNode;
	
	std::map<int,KcolorGraphNode *>::iterator ancestorIt;
	for(ancestorIt = futureNode->ancestors.begin(); (ancestorIt->first < indexNodeEndFilter) && ancestorIt != futureNode->ancestors.end();++ancestorIt)
	{


		checkNode = ancestorIt->second;
		cout << ptab << ptab << ptab<<" Node: " <<checkNode->ID << " searching for valid value in domain of node: "<<futureNode->ID<< endl;;

		//for each color in the domain of that node look his temporalDomain
		for (int k = 0; k < futureNode->temporalColorDomain.size(); k++)
		{



			//if the current assigned color == color of the domain.
			++numberOfChecks;
			//cout << "------------------------------------------------------------------->Number of checks: "<< numberOfChecks << " - with color: "<<futureNode->temporalColorDomain[k]<< "-> ";

			if (checkNode->AsignedColor == futureNode->temporalColorDomain[k])
			{
				cout << ptab << ptab<< "Deleting value: " << futureNode->temporalColorDomain[k] << " of the node: ID:"<<futureNode->ID<< endl;

				//Add the deleted value to history

				this->addDomainDeletionToHistory(checkNode,futureNode,futureNode->temporalColorDomain[k]);
				futureNode->temporalColorDomain.erase(futureNode->temporalColorDomain.begin()+ k);


				//If there is a node in the constraints that reach 0 colors in his domains, the future node j
				//will reach a dead end.
				if (futureNode->temporalColorDomain.size() == 0)
				{
					cout << ptab << ptab << ptab << "Domain of the node: ID:" << futureNode->ID << " empty, returning false " << endl;
					cout << endl<<ptab << "**** END OF WAKING UP *******" << endl;
					return false;
				}
				k--;//one color was deleted in the domain of the futureNode -> k should stay the same.

			}
			else
			{
				//If this line is reached, one value consistent has been found.
				//Because this is minimal forward checking, the algorithm stop filtering for this node here.
				cout << ptab << ptab << ptab << "Value:" << futureNode->temporalColorDomain[k] << " valid!, stoping the search" << endl;
				break;
			}

		}



	}
	//return true only if all domains of the future variables could be filtered successfully
	cout <<ptab << "Returning true"<< endl;


	cout << endl<<ptab << "**** END OF WAKING UP *******" << endl;
	return true;

}



/*
 * Print in screen the results of searching a solution.
 */
void KcolorGraphProblem::printFinalResults(bool forCsv)
{
	this->computeProblemTopographyStatistics();

	if(forCsv)
		this->printFinalResultsCSV();
	else
	{

		float finaltime = Control::elapsedTime();


		cout << "--------------------------------- Results of K-color Graph  ---------------------------------"<<endl;
		cout << "--------------------"<<endl;
		cout << "Graph Information: "<< endl;
		cout << "- Number of nodes of the graph: "<< this->CurrentGraph.size()<<endl;
		cout << "- Number of constraints of the graph: "<< this->numberOfConstraints << endl;
		cout << "- Mean of constraints per node: "<< this->meanOfConstraintsPerNode << endl;
		cout << "- Number of nodes with number of constraints under/over the mean of constraints: "<< this->numberOfNodesUnderMeanConstraints << "/"<< this->numberOfNodesOverMeanConstraints << endl;
		cout << "- Mean of domain size per node: "<< this->meanOfDomainSizePerNode << endl;
		cout << "- Number of nodes with domain size under/over the mean of domain size: "<< this->numberOfNodesUnderMeanDomainSize << "/"<< this->numberOfNodesOverMeanDomainSize << endl;
		cout << "--------------------"<<endl;
		cout << "- Number of instantiations done: "<< this->numberOfInstantiations<<endl;
		cout << "- Number of domain checks done: "<< numberOfChecks <<endl;
		cout << "- Number of deads ends found: " << this->numberOfDeadEnds << endl;
		cout << "- Elapsed time of algorithm: "<< finaltime<<endl;



		bool solucion=false;
		if (this->BestOFValue < 50000000)
			solucion = true;
		if (solucion)
		{

			cout << "- The objective function value is:  " << this->BestOFValue << " (distinct colors)" << endl;
			cout << "- Printing the Graph: " << endl;
			for (int i = 0; i < this->BestGraph.size(); i++)
			{
				cout << "Node: " << this->BestGraph[i]->ID
						<< " - Color " << this->BestGraph[i]->AsignedColor << endl;
			}
		}
		else
		{
			cout << "- The graph doesn't have a solution" << endl;
		}
	}
}


void KcolorGraphProblem::printFinalResultsCSV()
{
	float finaltime = Control::elapsedTime();


	/*
	cout << "'Number of Nodes','Number of constraints','Mean of constraints', "
	     <<"'Nodes under mean of constraints','Nodes under mean of constraints'"
		 <<"'Mean domain size"
		 <<"'Nodes under mean of domain size','Nodes under mean domain size'"
		 <<"'Instantiations', 'Checks', 'Dead ends', 'Time','Solution found'"
		 <<endl;
	*/

	cout <<this->CurrentGraph.size()<<","
		 <<this->numberOfConstraints << ","
		 <<this->meanOfConstraintsPerNode << ","
	 	 <<this->numberOfNodesUnderMeanConstraints << ","
	 	 <<this->numberOfNodesOverMeanConstraints << ","
		 <<this->meanOfDomainSizePerNode << ","
		 <<this->numberOfNodesUnderMeanDomainSize << ","
		 <<this->numberOfNodesOverMeanDomainSize << ","
		 <<this->numberOfInstantiations << ","
		 <<numberOfChecks << ","
		 <<this->numberOfDeadEnds<<","
		 <<finaltime << ",";


	bool solucion=false;
	if (this->BestOFValue < 50000000)
		cout<< "Yes"<<endl;
	else
	{
		cout << "No"<<endl;
	}

}


/*
 * Assuming a node "causeNode" is applying a filter on "filteredNode".
 * Add the deletion of the value "value" in the temporal domain of the node "filteredNode" to the history with
 * a key to the node "causeNode"
 */
void KcolorGraphProblem::addDomainDeletionToHistory(KcolorGraphNode *causeNode, KcolorGraphNode *filteredNode, std::string &value)
{

	//cout << ptab << ptab << "Adding - \"node: " << causeNode->ID << " deleted: " << value << " in node: " << filteredNode->ID << "\" - to the history " << endl;
	KcolorGraphDomainDeletion deletion(value, filteredNode);
	history.insert(
			std::pair<char, KcolorGraphDomainDeletion>(causeNode->ID,
					deletion));
}

void KcolorGraphProblem::initializeAncestorsFutureConnectedVariables()
{
	for(int i=0;i<this->CurrentGraph.size();i++){
		this->CurrentGraph[i]->initializeAncestorsFutureConnectedVariables();
	}

}



int KcolorGraphProblem::getMostRecentlyInstancedInducedAncestorIndex(int nodeIndex)
{

	KcolorGraphNode * node = this->CurrentGraph[nodeIndex]->getMosRecentInstancedInducedAncestor();
	if(node==NULL)
		return -1;
	else
		return node->ID;

}
int KcolorGraphProblem::getMostRecentlyInstancedInducedConflictIndex(int nodeIndex)
{
	KcolorGraphNode * node = this->CurrentGraph[nodeIndex]->getMostRecentInstancedInducedConflict();
	if(node==NULL)
		return -1;
	else
		return node->ID;
}

void KcolorGraphProblem::induceAncestors(int futureNodeIndex, int inducedNodeIndex)
{
	cout << "Inducing ancestors from node: "<< futureNodeIndex << " to: " <<inducedNodeIndex<< endl;

	/*
	this->CurrentGraph[inducedNodeIndex]->printInducedAncestors();
	this->CurrentGraph[futureNodeIndex]->printInducedAncestors();
	*/
	this->CurrentGraph[inducedNodeIndex]->induceAncestors(this->CurrentGraph[futureNodeIndex]);


	//this->CurrentGraph[inducedNodeIndex]->printInducedAncestors();
}

void KcolorGraphProblem::induceConflictSet(int futureNodeIndex, int inducedNodeIndex)
{
	cout << "Inducing conflict set from node: "<< futureNodeIndex << " to: " <<inducedNodeIndex<< endl;

	this->CurrentGraph[inducedNodeIndex]->induceConflictSet(this->CurrentGraph[futureNodeIndex]);
}


void KcolorGraphProblem::restoreInducedAncestors(int inducedNodeIndex)
{
	cout <<"-Restoring induced ancestors of node:" << inducedNodeIndex << endl;
	this->CurrentGraph[inducedNodeIndex]->restoreInducedAncestors();

}

void KcolorGraphProblem::restoreInducedConflictSet(int inducedNodeIndex)
{
	cout << "-Restoring induced conflict set of node:" << inducedNodeIndex << endl;

	this->CurrentGraph[inducedNodeIndex]->inducedConflictSet.clear();
}



/*
 * Restore the deleted values made from node in the position "causeNodeIndex" in all subsequent variables.
 */
void KcolorGraphProblem::restoreAllDeletionsFromHistory( KcolorGraphNode *causeNode)
{

	cout << ptab << ptab << "Restoring all deleted values made from node: " << causeNode->ID << " found in the history." << endl;
	this->searchResult = this->history.equal_range(causeNode->ID);

	for (std::multimap<int, KcolorGraphDomainDeletion>::iterator it = this->searchResult.first; it != this->searchResult.second; ++it)
	{
		cout << ptab << ptab << "Restoring the deletion: '" << causeNode->ID
				<< " deleted value " << it->second.value << " on node: "
				<< it->second.node->ID << endl;
		it->second.node->temporalColorDomain.push_front(it->second.value);
	}
	this->history.erase(causeNode->ID);
}

/*
 * Save a backup of the temporal domain of the node in the position "backupIndex".
 * Note: this operation clear previous stored temporal domains.
 */
void KcolorGraphProblem::saveBackupTemporalDomain(int backupNodeIndex)
{
	KcolorGraphNode* nodeBackup = this->CurrentGraph[backupNodeIndex];
	nodeBackup->saveBackupTemporalDomain();

}

/*
 * Restore the temporal domain of node in the position "backupIndex" using the backup saved.
 * Note: After this operation clear temporal domain backup is cleared.
 */
void KcolorGraphProblem::restoreBakupTemporalDomain(int backupNodeIndex)
{
	KcolorGraphNode* nodeBackup = this->CurrentGraph[backupNodeIndex];
	nodeBackup->restoreBakupTemporalDomain();
}

/*
 * Print the domains of all variables.
 */
void KcolorGraphProblem::printAllDomains()
{
	for (int i = 0; i < this->CurrentGraph.size(); i++)
	{
		this->CurrentGraph[i]->printTemporalDomain();
	}
	cout << "------------------------------------------------" << endl;
}

/*
 * Try to assign a value to the node in the position "nodeIndex", if there are no more values in temporal domain
 * assign the default color and return false.
 * Return true in case of successive assignment.
 */
bool KcolorGraphProblem::assignNextValue(int nodeIndex)
{
	if (this->CurrentGraph[nodeIndex]->temporalColorDomain.size() == 0)
	{
		//There are no more values in the current temporal domain: Restore the default value of the node.
		this->CurrentGraph[nodeIndex]->AsignedColor = this->CurrentGraph[nodeIndex]->defaultColor;
		return false;
	}
	else
	{
		//assign next color available
		++numberOfChecks;
		this->CurrentGraph[nodeIndex]->AsignedColor = this->CurrentGraph[nodeIndex]->temporalColorDomain[0];

		this->CurrentGraph[nodeIndex]->temporalColorDomain.pop_front();
		cout << "Instantiating the node: " << this->CurrentGraph[nodeIndex]->ID << " - color: " << this->CurrentGraph[nodeIndex]->AsignedColor << endl;

		++this->numberOfInstantiations;

		return true;
	}
}

bool KcolorGraphProblem::assignNextValueAddingToBackupDomain(int nodeIndex)
{
	if (this->CurrentGraph[nodeIndex]->temporalColorDomain.size() == 0)
	{
		//There are no more values in the current temporal domain: Restore the default value of the node.
		this->CurrentGraph[nodeIndex]->AsignedColor = this->CurrentGraph[nodeIndex]->defaultColor;
		return false;
	}
	else
	{
		//assign next color available
		this->CurrentGraph[nodeIndex]->AsignedColor = this->CurrentGraph[nodeIndex]->temporalColorDomain[0];

		this->CurrentGraph[nodeIndex]->backupTemporalDomain.push_back(this->CurrentGraph[nodeIndex]->AsignedColor);


		this->CurrentGraph[nodeIndex]->temporalColorDomain.pop_front();
		cout << "Instantiating the node: " << this->CurrentGraph[nodeIndex]->ID << " - color: " << this->CurrentGraph[nodeIndex]->AsignedColor << endl;



		++this->numberOfInstantiations;

		return true;
	}
	return true;
}

void KcolorGraphProblem::restoreCheckForwardDeletions(int causeNodeIndex)
{
	this->restoreAllDeletionsFromHistory(this->CurrentGraph[causeNodeIndex]);
}

/*
 * Print constraints of all variables.
 */
void KcolorGraphProblem::printAllConstraints()
{
	for (int i = 0; i < this->CurrentGraph.size(); i++)
	{
		this->CurrentGraph[i]->printConstraints();
	}
	cout << "------------------------------------------------" << endl;
}

void KcolorGraphProblem::restoreDomain(int nodeIndex)
{
	cout << "-Restoring domain of node:" << nodeIndex << endl;

	this->CurrentGraph[nodeIndex]->restoreDomain();
}
