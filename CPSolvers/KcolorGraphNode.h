#include <deque>

#include "headers.h"
#include <string>

//Node class of the k color graph problem.


class KcolorGraphNode{
public:
	int ID;
	std::string Color;
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
	/* restore the node's domain */
	void restoreDomain();
};
