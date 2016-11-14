#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

int main()
{
	srand(time(NULL));
	
	unsigned long long stay = 0;
	unsigned long long change = 0;
	long i=0;
	while(true)
	{
		vector<bool> boxes(3, false);
		boxes[0] = true; // Place a car
		random_shuffle(boxes.begin(), boxes.end());
		
		if(boxes[0])
		{
			stay++;
			cout << "STAY wins\n";
		}
		else
		{
			change++;
			cout << "CHANGE wins\n";
		}
		cout << "STAY: " << (double)stay/(stay + change) * 100  << "%; "
		     << "CHANGE: " << (double)change/(stay + change) * 100  << "%\n" << endl;
		if(i%1000==0)
			sleep(1);
		i++;
	}
}
