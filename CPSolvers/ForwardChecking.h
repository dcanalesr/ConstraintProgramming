#include "headers.h"
#include <string>

using namespace std;

class ForwardChecking{
public:
	ForwardChecking(int problemSize_,std::string problemType);
	ForwardChecking(string problemType, string instanceFilename);
	Problem* problem;
	int problemSize;
	void Start();
private:
	bool label(int n); //trata de instanciar un nodo, si lo logra instanciar retorna true, sino false
};
