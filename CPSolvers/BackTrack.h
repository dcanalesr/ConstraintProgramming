#include "headers.h"


class BackTrack{
public:
	KcolorGraphProblem kproblem;
	void StartKcolor();
	void printAllDomainsKColorGraph();
	void printAllConstraintsKColorGraph();
private:
	bool labelKColorNode(int n);
};
