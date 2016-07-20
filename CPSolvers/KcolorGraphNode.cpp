/*
 * kcolourGraph.cpp
 *
 *  Created on: 14/09/2015
 *      Author: dario
 */
#include "headers.h"
using namespace std;
#include <iostream>
const string pTab="..";

/*
 * Initialize the ID and set the current color to "[Uninstantiated]".
 */
KcolorGraphNode::KcolorGraphNode(int id){
	this->ID = id;
	this->defaultColor="[Uninstantiated]";
	this->AsignedColor = this->defaultColor;
}
KcolorGraphNode::KcolorGraphNode()
{
	this->ID = 0;
	this->defaultColor="[Uninstantiated]";
	this->AsignedColor = this->defaultColor;
}


/*
 * Check all constraints of current node and return a deque of pointers to the conflict nodes.
 */
deque<KcolorGraphNode *> KcolorGraphNode::checkPastConstraints(){

	//for each node in the list of constraints, check the color
	deque<KcolorGraphNode *> conflictNodes;

	cout << "Node: " << this->ID<< " -- "<<endl;
	for(int i=0;i<this->constraints.size();i++)
	{
		if(this->constraints[i]->AsignedColor!= this->constraints[i]->defaultColor)
		{
			cout << pTab <<"Constraint with node "<<this->constraints[i]->ID<< ": " <<this->constraints[i]->AsignedColor <<endl;
			if(this->AsignedColor == this->constraints[i]->AsignedColor)
				conflictNodes.push_back(this->constraints[i]);
		}
	}
	return conflictNodes;
}

/*
 * Check constraints of current node with past variables and print in the screen the conflict ones.
 */
void KcolorGraphNode::checkPastConstraintsPrint()
{
	cout << "------------ Checking all constraints ----------"<<endl;
	deque<KcolorGraphNode *>restriccionesIncumplidas = this->checkPastConstraints();

	if(restriccionesIncumplidas.size()>0){

		cout << "------->Node: " << this->ID << " - color: "<< this->AsignedColor <<" -- " << restriccionesIncumplidas.size() << " Conflict restrictions: "<< endl;

		for(int i=0;i<restriccionesIncumplidas.size();i++)
		{
			cout << "------------>Node: "<< restriccionesIncumplidas[i]->ID ;
			cout<< " Color: " << restriccionesIncumplidas[i]->AsignedColor <<endl;
		}
	}
	cout << "------------------------------------------------"<<endl;
}

/*
 * Check constraints of current node with past variables, return false when a constraint violated if found.
 */
bool KcolorGraphNode::checkPastConstraintsBreak()
{
	//for each node in the list of constraint, if one is violated return false.
	for(int i=0;i<constraints.size();i++)
	{

		//Short circuit evaluation
		//this->constraints[i]->AsignedColor is currently assigned and
		//is equal to the assigned color of the current node.
		if(this->constraints[i]->AsignedColor!= this->constraints[i]->defaultColor && this->AsignedColor == this->constraints[i]->AsignedColor)
		{
			return false;
		}
	}
	return true;
}

/*
 * Restore the temporal domain with the original domain of the current node.
 */
void KcolorGraphNode::restoreDomain()
{
	/*
	this->temporalColorDomain.clear();
	for(int i=0;i<this->originalColorDomain.size();i++)
	{
		this->temporalColorDomain.push_back(this->originalColorDomain[i]);
	}
	*/
	this->temporalColorDomain = this->getOriginalColorDomainCopy();


}

/*
 * Print in the screen the temporal domain of the current node.
 */
void KcolorGraphNode::printTemporalDomain(){
	cout <<"Domain of the node: " <<this->ID <<endl;
	for(int i=0;i<this->temporalColorDomain.size();i++)
	{
		cout << pTab << "Color: "<< this->temporalColorDomain[i] << endl;
	}
}

/*
 * Print in the screen the constraints of the current node.
 */
void KcolorGraphNode::printConstraints()
{
	cout <<"Domain of the node: " <<this->ID <<endl;
	for(int i=0;i<this->constraints.size();i++)
	{
		cout << pTab << "Arc constraint with node: "<< this->constraints[i]->ID << endl;
	}
}

void KcolorGraphNode::restoreValueDomain(std::string value)
{
	cout << pTab <<"Restoring value: "<<value << " in the domain of node "<<this->ID <<endl;
	this->temporalColorDomain.push_back(value);
}

void KcolorGraphNode::saveBackupTemporalDomain()
{
	//only save the backup one time: if there is already a backup => the node is being revisited because of backtrack
	//from another node.

	if(this->backupTemporalDomain.size()==0)
	{
		//reset temporal domain

		cout << pTab << "Saving backup of temporal domain of node: "<<this->ID<<endl;

		//Save temporal domain of current node, just in case of backtrack needed.
		this->backupTemporalDomain = this->temporalColorDomain;

	}
}

void KcolorGraphNode::restoreBakupTemporalDomain()
{
	cout << pTab << "Restoring backupTemporalDomain of node: "<<this->ID<<endl;

	this->temporalColorDomain = this->backupTemporalDomain;

	//reset temporal domain after the restore
	this->backupTemporalDomain.clear();
}
