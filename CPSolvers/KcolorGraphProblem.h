#include <deque>

#include "headers.h"

class KcolorGraphProblem{
public:
		std::deque<KcolorGraphNode *> CurrentColorGraph;
		std::deque<KcolorGraphNode *> BestColorGraph;
		int BestOFValue;


		void initialize(int size, int orderingHeuristicOption);
		void initializeExample();
		void checkSetBestSolution();
		void restoreDomainsFromK(int k);
		bool pastConsistent(int n);
		/* Filters the domain of all connected nodes with current node */
		bool checkForward(int i);
		void printFinalResults();
};

