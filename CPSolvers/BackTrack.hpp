#include "headers.hpp"


class BackTrack{
public:
	BackTrack(int problemSize_,std::string problemType, bool isOptimization_, bool forCsv_);
	BackTrack(string problemType, string instanceFilename,bool isOptimization_, bool forCsv_);
	Problem* problem;
	int problemSize;
	bool forCsv;

	void Start();
private:
	bool label(int n);
	bool isOptimization;

};
