#include "headers.h"


class ForwardChecking{
public:
	Problem* problem;
	int problemSize;
	void Start();
private:
	bool label(int n); //trata de instanciar un nodo, si lo logra instanciar retorna true, sino false
};
