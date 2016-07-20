#include <deque>
#include "headers.h"
#include <string>
#include <map>


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


		/*
		 * Checking if the current solution is better than the best.
		 */
		void checkSetBestSolution();


		void printFinalResults();

		/*Restoring domains*/
		virtual void restoreDomain(int nodeIndex);
		void restoreCompleteDomainsFromK(int k);
		void restoreBakupTemporalDomain(int backupNodeIndex);
		void restoreCheckForwardDeletions(int causeNodeIndex);

		/*filters*/
		/* Filters the domain of all connected nodes with current node */
		bool checkForward(int nodeIndex);
		bool minimalCheckForward(int nodeIndex);


		void addNewNode(KcolorGraphNode * node){this->CurrentGraph.push_back(node);}

		int getProblemSize() { return this->CurrentGraph.size();}

		int numberOfInstantiations;

		void initializeAncestors();
		virtual int getMostRecentrlyInstancedAncestorIndex(int nodeIndex);

		void induceAncestors(int inducingNodeIndex, int inducedNodeIndex);

private:


		std::multimap<int,KcolorGraphDomainDeletion> history;
		std::pair <std::multimap<int,KcolorGraphDomainDeletion>::iterator, std::multimap<int,KcolorGraphDomainDeletion>::iterator> searchResult;

		/* maintain a history of deletions in temporal domains of any variable*/
		void addDomainDeletionToHistory(KcolorGraphNode *causeNode, KcolorGraphNode *filteredNode, std::string &value);
		void restoreAllDeletionsFromHistory(KcolorGraphNode *causeNode);



};

