#include <iostream>
#include <vector>
#include "headers.h"
using namespace std;
#include <stdlib.h>


int main(int argc,char* argv[])
{
	srand(1);
	//srand(time(NULL));

	//BackTrack backTrack;
	//backTrack.StartKcolor();

	ForwardChecking forwardChecking;
	forwardChecking.StartKcolor();

	return 0;
}
