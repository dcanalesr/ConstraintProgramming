#include <deque>

#include "headers.h"
#include <string>
#include <map>


class KcolorGraphDomainDeletion{
public:
	KcolorGraphDomainDeletion(std::string value_,KcolorGraphNode *node_): value(value_),node(node_){}
	std::string value;
	KcolorGraphNode *node;
};
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
		void restoreAllDeletionsFromHistory(KcolorGraphNode *causeNode);
		void addDomainDeletionToHistory(KcolorGraphNode * causeNode, KcolorGraphNode *filteredNode, std::string value);
		void saveBackupTemporalDomain(KcolorGraphNode *nodeBackup);
		void restoreBakupTemporalDomain(KcolorGraphNode *nodeBackup);
private:
		std::deque<std::string> backupTemporalDomain;
		std::multimap<int,KcolorGraphDomainDeletion> history;
		std::pair <std::multimap<int,KcolorGraphDomainDeletion>::iterator, std::multimap<int,KcolorGraphDomainDeletion>::iterator> searchResult;
};

