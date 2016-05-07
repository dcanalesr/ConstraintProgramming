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
KcolorGraphNode::KcolorGraphNode(){
	this->ID = 0;
	this->defaultColor="[Uninstantiated]";
	this->AsignedColor = this->defaultColor;
}

/*
 * Check all constraints of current node and return a deque of pointers to the conflict nodes.
 */
deque<KcolorGraphNode *> KcolorGraphNode::checkConstraints(){

	//for each node in the list of constraints, check the color
	deque<KcolorGraphNode *> conflictNodes;

	cout << "Node: " << this->ID<< " -- "<<endl;
	for(int i=0;i<this->constraints.size();i++)
	{
		cout << pTab <<"Constraint with node "<<this->constraints[i]->ID<< ": " <<this->constraints[i]->AsignedColor <<endl;
		if(this->AsignedColor == this->constraints[i]->AsignedColor)
			conflictNodes.push_back(this->constraints[i]);
	}
	return conflictNodes;
}

/*
 * Check constraints of current node and print in the screen the conflict ones.
 */
void KcolorGraphNode::checkConstraintsPrint()
{
	cout << "------------ Checking all constraints ----------"<<endl;
	deque<KcolorGraphNode *>restriccionesIncumplidas = this->checkConstraints();

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
 * Check constraints of current node, return false when the constraint violated if found.
 */
bool KcolorGraphNode::checkConstraintsBreak() {
	//for each node in the list of constraint, if one is violated return false.
	for(int i=0;i<constraints.size();i++)
	{
		if(this->AsignedColor == this->constraints[i]->AsignedColor)
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
	this->temporalColorDomain.clear();
	for(int i=0;i<this->originalColorDomain.size();i++)
	{
		this->temporalColorDomain.push_back(this->originalColorDomain[i]);
	}

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
