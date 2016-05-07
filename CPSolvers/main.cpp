#include <iostream>
#include <vector>
#include "headers.h"
using namespace std;
#include <stdlib.h>


#include <map>
#include <ctime>
#include <algorithm>    // std::find
int main(int argc,char* argv[])
{
	srand(1);
	//srand(time(NULL));

	//BackTrack backTrack;
	//backTrack.StartKcolor();

	//ForwardChecking forwardChecking;
	//forwardChecking.StartKcolor();

	int n = 50000;
	//inserting n elements into array
	std::vector<int> vectorInt;
	std::multimap<int,int> mapInt;
	int min=-80000;
	int max= 80000;
	int value;
	cout << "Creating arrays..."<< endl;
	for(int i=0;i<n;i++)
	{
		value = min + (rand() % (int)(max - min + 1));
		vectorInt.push_back(value);
		mapInt.insert(std::make_pair(value,i));
	}
	cout << "array created"<<endl;

	//Find 500 element with specific tag.


	 int found = 0;
	 int notFound=0;


	 using namespace std;
     clock_t begin = clock();
     int elementosBuscar = 10000;
     cout << "finding..."<<endl;

	 std::vector<int>::iterator it;
	 for(int i=0;i<elementosBuscar;i++)
	 {
		 value = min + (rand() % (int)(max - min + 1));


		 it = std::find (vectorInt.begin(), vectorInt.end(), value);
		 if (it != vectorInt.end())
		 {
			 found++;
			 //std::cout << "Element found: " << *it << endl;
		 }

		 else
			 notFound++;
		     //std::cout << "Element not found in myvector\n";
	 }

/*

     std::multimap<int,int>::iterator it;
     for(int i=0;i<elementosBuscar;i++)
	 {
		 value = min + (rand() % (int)(max - min + 1));


		 it = mapInt.find(value);
		 if (it != mapInt.end())
		 {
			 found++;
			 //std::cout << "Element found: " << it->first << endl;
		 }

		 else
			 notFound++;
			 //std::cout << "Element not found in myvector\n";
	 }
*/
	 cout << "found: "<< found << endl;
	 cout << "not found: "<<notFound <<endl;
	 clock_t end = clock();
     double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
     cout << "time: "<<elapsed_secs <<endl;

	return 0;
}
