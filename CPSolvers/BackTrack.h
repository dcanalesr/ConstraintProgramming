#include "headers.h"


class BackTrack{
public:
	BackTrack(int problemSize_,std::string problemType);
	BackTrack(string problemType, string instanceFilename);
	Problem* problem;
	int problemSize;

	void Start();
private:
	bool label(int n);
};
