#include <initializer_list>
#include <vector>
#include <iostream>
using namespace std;

class NestedInteger{
public:
	NestedInteger(int v):value(v){
		isInt = true;
	}

	NestedInteger(initializer_list<NestedInteger> l):li(l){}

	bool isInteger(){
		return isInt;
	}
	vector<NestedInteger> getList(){
		return li;
	}
	int getInteger(){
		return value;
	}
private:
	int value;
	vector<NestedInteger> li;
	bool isInt = false;
};

void print(NestedInteger v){
	for(auto item : v.getList()){
		if(item.isInteger()) 
			cout<<item.getInteger()<<endl;
		else{
			print(item);
		}
	}
}




int main(){
	NestedInteger v = {{1,2},3,{4,5,{6,7}}};
	print(v);

	return 0;
}