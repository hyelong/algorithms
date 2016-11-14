#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main(){

	istream_iterator<int> in_iter(cin), eos;
	vector<int> vec(in_iter, eos);
	for(int num : vec){
		cout<< num*num << ' ';
	}
	cout<<endl;
	return 0;
}