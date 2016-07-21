#include <deque>
#include "headers.h"
#include <string>
#include <map>


//Node class of the k color graph problem.

using namespace std;

class KcolorGraphNode{
public:
	int ID;
	std::string AsignedColor;
	std::string defaultColor;
	std::deque<std::string> originalColorDomain;
	std::deque<std::string> temporalColorDomain;
	std::deque<KcolorGraphNode *> constraints;

	KcolorGraphNode(int id);
	KcolorGraphNode();
	std::deque<KcolorGraphNode *> checkPastConstraints();
	bool checkPastConstraintsBreak();
	void checkPastConstraintsPrint();
	void printTemporalDomain();
	void printConstraints();

	void saveBackupTemporalDomain();
	void restoreBakupTemporalDomain();

	/* restore the node's domain */
	void restoreDomain();



	/*Restore a single value in the domain of the current node*/
	void restoreValueDomain(std::string value);

	std::deque<std::string> getOriginalColorDomainCopy() { return this->originalColorDomain;}
	std::deque<std::string> getTemporalColorDomainCopy() { return this->temporalColorDomain;}

	void initializeAncestorsFutureConnectedVariables();


	void printAncestors();
	void printFutureConnectedVariables();
	void printInducedAncestors();

	void induceAncestors(KcolorGraphNode * futureNode);
	void restoreInducedAncestors();

	/*
	 * Find and return most recently instanced ancestor. If current node hasn't instanciated ancestors, return null
	 */
	KcolorGraphNode * getMosRecentInstancedInducedAncestor();


	std::map<int,KcolorGraphNode *> ancestors;
	std::map<int,KcolorGraphNode *> inducedAncestors;

	std::map<int,KcolorGraphNode *> futureConnectedVariables;

private:
	std::deque<std::string> backupTemporalDomain;


};
