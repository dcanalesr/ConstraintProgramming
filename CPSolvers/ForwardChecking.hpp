#include "headers.hpp"
#include <string>

using namespace std;

class ForwardChecking{
public:
	ForwardChecking(int problemSize_,std::string problemType, bool isOptimization_ , bool forCsv_);
	ForwardChecking(string problemType, string instanceFilename, bool isOptimization_ , bool forCsv_);
	Problem* problem;
	int problemSize;

	void Start();
private:
	bool label(int n); //trata de instanciar un nodo, si lo logra instanciar retorna true, sino false
	bool isOptimization;
	bool forCsv;
};
