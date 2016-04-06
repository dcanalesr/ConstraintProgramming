#include "headers.h"


class BackTrack{
public:
	KcolorGraphProblem kproblem;
	void StartKcolor();
	void printAllDomainsKColorGraph();
	void printAllConstraintsKColorGraph();
private:
	bool labelKColorNode(int n); //trata de instanciar un nodo, si lo logra instanciar retorna true, sino false
};
