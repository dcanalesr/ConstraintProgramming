#include "headers.hpp"


class BackTrack{
public:
	BackTrack(int problemSize_,std::string problemType, bool isOptimization_);
	BackTrack(string problemType, string instanceFilename,bool isOptimization_);
	Problem* problem;
	int problemSize;

	void Start();
private:
	bool label(int n);
	bool isOptimization;

};
