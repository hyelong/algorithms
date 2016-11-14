#include <bitset>
#include <iostream>
#include <string>
using namespace std;

int main(){
	bitset<64> matrix[64];
	cout<<sizeof(int)<<endl;
	cout<<sizeof(matrix)<<endl;
	matrix[0].set(2);

	bitset<64> matrix1[64];
	
	swap(matrix1, matrix);

	cout<<(matrix1[0][2]==1)<<endl;

	cout<<matrix[0].size()<<endl;
	return 0;
}