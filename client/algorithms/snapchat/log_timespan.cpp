/*
.给一个单核CPU的log，parse log，每一行log三列分别是jobname(String)    start/end(boolean)    timeStamp(long)

name(String)    start/end(boolean)    timeStamp(long) 
f1                   start                        0
f2                   start                        2
f3                   start                        4
f3                   end                          5
f2                   end                          8
f1                   end                          9

上面log的意思是我们在0开始做f1
在2的时候切换到f2,
4的时候开始做f3，. 1point3acres.com/bbs
5的时候f3结束
要返回每个function要用的时间. visit 1point3acres.com for more.
这个input的返回就是
f1 ： 3
f2 ： 5
f3 ： 1
*/
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

struct entity
{
	string name;
	bool end;
	long time_stamp;
	entity(string n, bool e, long t):name(n), end(e), time_stamp(t){}
};

void print_log(vector<entity*> logs){
	stack<entity*> st;
	stack<pair<long, long>> intervals;
	for(entity* e : logs){
		if(!e->end)
			st.push(e);
		else{
			entity* last = st.top();
			st.pop();
			if(e->name==last->name){
				long start = last->time_stamp;
				long end = e->time_stamp;

				int inner_time_span = 0;
				while(!intervals.empty() && intervals.top().first > start){
					inner_time_span += intervals.top().second - intervals.top().first;
					intervals.pop();
				}

				cout<<e->name<<" : "<<"["<<start<<","<<end<<"] "<<end - start - inner_time_span<<endl;
				intervals.push({start, end});
			}
		}
	}
}

int main(){
	vector<entity*> logs;
	logs.push_back(new entity("f1", false, 0));
	logs.push_back(new entity("f1", false, 2));
	logs.push_back(new entity("f1", true, 4));
	logs.push_back(new entity("f3", false, 5));
	logs.push_back(new entity("f3", true, 8));
	logs.push_back(new entity("f1", true, 9));
	print_log(logs);

	return 0;
}
