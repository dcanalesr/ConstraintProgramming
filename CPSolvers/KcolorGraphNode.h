#include <deque>
#include "headers.h"
#include <string>

//Node class of the k color graph problem.


class KcolorGraphNode{
public:
	int ID;
	std::string AsignedColor;
	std::deque<std::string> originalColorDomain;
	std::deque<std::string> temporalColorDomain;
	std::deque<KcolorGraphNode *> constraints;
	std::string defaultColor;
	KcolorGraphNode(int id);
	KcolorGraphNode();
	std::deque<KcolorGraphNode *> checkConstraints();
	bool checkConstraintsBreak();
	void checkConstraintsPrint();
	void printTemporalDomain();
	void printConstraints();
	/* restore the node's domain */
	void restoreDomain();
	/*Restore a single value in the domain of the current node*/
	void restoreValueDomain(std::string value);
};
