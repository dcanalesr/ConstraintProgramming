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
class KcolorGraphProblem: public Problem
{
public:
		std::deque<KcolorGraphNode *> CurrentGraph;
		std::deque<KcolorGraphNode *> BestGraph;
		int BestOFValue;

		KcolorGraphProblem();

		void initializeExample();
		void initialize(int size, int orderingHeuristicOption);


		void printAllDomains();
		void printAllConstraints();

		void saveBackupTemporalDomain(int backupNodeIndex);
		bool assignNextValue(int nodeIndex);
		bool pastConsistent(int n);
		void checkSetBestSolution();
		void printFinalResults();

		/*Restoring domains*/
		void restoreCompleteDomainsFromK(int k);
		void restoreBakupTemporalDomain(int backupNodeIndex);
		void restoreCheckForwardDeletions(int causeNodeIndex);

		/*filters*/
		/* Filters the domain of all connected nodes with current node */
		bool checkForward(int i);

	private:
		/* maintain a history of deletions in temporal domains of any variable*/
		void addDomainDeletionToHistory(int causeNodeIndex, int filteredNodeIndex, std::string value);
		void restoreAllDeletionsFromHistory(int causeNodeIndex);

private:
		std::deque<std::string> backupTemporalDomain;
		std::multimap<int,KcolorGraphDomainDeletion> history;
		std::pair <std::multimap<int,KcolorGraphDomainDeletion>::iterator, std::multimap<int,KcolorGraphDomainDeletion>::iterator> searchResult;
};

