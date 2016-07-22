#ifndef KCOLOR_GRAPH_PROBLEM
#define KCOLOR_GRAPH_PROBLEM


#include <deque>
#include "headers.h"
#include <string>
#include <map>

static int numberOfChecks;

class KcolorGraphProblem: public Problem
{
public:
		std::deque<KcolorGraphNode *> CurrentGraph;
		std::deque<KcolorGraphNode *> BestGraph;
		int BestOFValue;

		int numberOfInstantiations;

		KcolorGraphProblem();

		void initializeExample();
		void initializeExampleBackTrackGbj();
		void initialize(int size, int orderingHeuristicOption);



		void printAllDomains();
		void printAllConstraints();
		void printFinalResults();

		void saveBackupTemporalDomain(int backupNodeIndex);
		bool assignNextValue(int nodeIndex);
		bool assignNextValueAddingToBackup(int nodeIndex);
		bool pastConsistent(int n);


		/*
		* Checking if the current solution is better than the best.
		*/
		void checkSetBestSolution();




		/*Restoring domains*/
		virtual void restoreDomain(int nodeIndex);
		void restoreCompleteDomainsFromK(int k);
		void restoreBakupTemporalDomain(int backupNodeIndex);
		void restoreCheckForwardDeletions(int causeNodeIndex);

		/*filters*/
		/* Filters the domain of all connected nodes with current node */
		bool checkForward(int nodeIndex);
		bool minimalCheckForward(int nodeIndex);

		bool wakeUpMinimalFilters(int futureNodeIndex, int indexNodeEndFilter);


		void addNewNode(KcolorGraphNode * node){this->CurrentGraph.push_back(node);}
		int getProblemSize() { return this->CurrentGraph.size();}



		/* Ancestors and future connected variables*/
		void initializeAncestorsFutureConnectedVariables(); //Past and future connected variables in distinct lists.
		virtual int getMostRecentrlyInstancedInducedAncestorIndex(int nodeIndex);
		void induceAncestors(int inducingNodeIndex, int inducedNodeIndex);
		void restoreInducedAncestors(int inducedNodeIndex);

private:


		std::multimap<int,KcolorGraphDomainDeletion> history;
		std::pair <std::multimap<int,KcolorGraphDomainDeletion>::iterator, std::multimap<int,KcolorGraphDomainDeletion>::iterator> searchResult;

		/* maintain a history of deletions in temporal domains of any variable*/
		void addDomainDeletionToHistory(KcolorGraphNode *causeNode, KcolorGraphNode *filteredNode, std::string &value);
		void restoreAllDeletionsFromHistory(KcolorGraphNode *causeNode);


};
#endif

