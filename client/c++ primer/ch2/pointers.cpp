#include <iostream>
#include <cstdint>
using namespace std;

struct st{
	bool i;
	bool j;
	bool k;
	bool l;
	bool m;
};

int main(){
	int* i = new int(-1);
	char* pi = (char*)i;
	for(int i=0;i<4;i++){
		char c = *(pi+i);
		for(int j=0;j<8;j++){
			cout<<((c>>j)&1)<<" ";
		}
	}
	cout<<endl;
	return 0;
}