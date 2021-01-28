#ifndef KCOLOR_GRAPH_PROBLEM
#define KCOLOR_GRAPH_PROBLEM


#include <deque>
#include "headers.hpp"
#include <string>
#include <map>

static int numberOfChecks;

#include <string>
#include <iostream>

class KcolorGraphProblem: public Problem
{
public:
		std::deque<KcolorGraphNode *> CurrentGraph;
		std::deque<KcolorGraphNode *> BestGraph;
		int BestOFValue;
		int numberOfInstantiations;
		int numberOfConstraints;
		float meanOfConstraintsPerNode;
		int numberOfNodesUnderMeanConstraints;
		int numberOfNodesOverMeanConstraints;
		float meanOfDomainSizePerNode;
		int numberOfNodesUnderMeanDomainSize;
		int numberOfNodesOverMeanDomainSize;



		KcolorGraphProblem();

		void initializeExample();
		void initializeExampleBackTrackGbj();
		void initialize(int size, int orderingHeuristicOption);

		void computeProblemTopographyStatistics();

		void printAllDomains();
		void printAllConstraints();
		void printFinalResults(bool forCsv);
		void printFinalResultsCSV();

		void saveBackupTemporalDomain(int backupNodeIndex);
		bool assignNextValue(int nodeIndex);
		bool assignNextValueAddingToBackupDomain(int nodeIndex);

		bool pastConsistent(int nodeIndex);
		bool pastConsistentAddingToConflictSet(int nodeIndex);


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
		virtual int getMostRecentlyInstancedInducedAncestorIndex(int nodeIndex);
		int getMostRecentlyInstancedInducedConflictIndex(int nodeIndex);

		void induceAncestors(int futureNodeIndex, int inducedNodeIndex);
		void induceConflictSet(int futureNodeIndex, int inducedNodeIndex);


		void restoreInducedAncestors(int inducedNodeIndex);
		void restoreInducedConflictSet(int inducedNodeIndex);

private:


		std::multimap<int,KcolorGraphDomainDeletion> history;
		std::pair <std::multimap<int,KcolorGraphDomainDeletion>::iterator, std::multimap<int,KcolorGraphDomainDeletion>::iterator> searchResult;

		/* maintain a history of deletions in temporal domains of any variable*/
		void addDomainDeletionToHistory(KcolorGraphNode *causeNode, KcolorGraphNode *filteredNode, std::string &value);
		void restoreAllDeletionsFromHistory(KcolorGraphNode *causeNode);


};
#endif

