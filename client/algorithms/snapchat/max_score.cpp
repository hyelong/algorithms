/*
第二题 ：给了一个Person class， 有score和nextSnap两个属性，每个Person有一个朋友的list，也就是nextSnap，
输入是（Person， maxStep）， 在maxStep步数以内算max score，注意的是下一个Friend可能会指向上一个Person，要注意回溯的问题
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Person{
    int score;
    vector<Person*> nextSnap;
    Person(int val) : score(val){}
};

void find_max_score(Person *person, int max_step, int  step, 
		int& max_score, unordered_set<Person*>& visited){
	if(visited.count(person)) return;
	if(step == max_step) return;
	max_score = max(max_score, person->score);
	for(auto next : person->nextSnap){
		find_max_score(next, max_step, step+1, max_score, visited);
	}
}

int main(){
	Person *person = new Person(1); 
	person->nextSnap.push_back(new Person(2));
	person->nextSnap.push_back(new Person(3));
	person->nextSnap.push_back(new Person(4));
	person->nextSnap[0]->nextSnap.push_back(new Person(5));
	person->nextSnap[0]->nextSnap.push_back(new Person(6));
	person->nextSnap[0]->nextSnap[0]->nextSnap.push_back(new Person(7));
	person->nextSnap[0]->nextSnap.push_back(person);
	int max_step = 3;
	int max_score = 0;
	unordered_set<Person*> visited;
	find_max_score(person, max_step, 0, max_score, visited);
	cout<<max_score<<endl;
	return 0;
}