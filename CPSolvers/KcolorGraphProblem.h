#include <deque>

#include "headers.h"
#include <string>
#include <map>
class KcolorGraphProblem{
public:
		std::deque<KcolorGraphNode *> CurrentColorGraph;
		std::deque<KcolorGraphNode *> BestColorGraph;
		int BestOFValue;

		KcolorGraphProblem();
		void initialize(int size, int orderingHeuristicOption);
		void initializeExample();
		void checkSetBestSolution();
		void restoreDomainsFromK(int k);
		bool pastConsistent(int n);
		/* Filters the domain of all connected nodes with current node */
		bool checkForward(int i);
		void printFinalResults();
private:
		std::multimap<int,KcolorGraphDomainDeletion> history;
		void addDomainDeletionToHistory(KcolorGraphNode causeNode,KcolorGraphNode filteredNode,std::string value);
		void restoreAllDeletionsFromHistory(KcolorGraphNode causeNode);
};

