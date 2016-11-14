#include<queue>
#include<iostream>
using namespace std;

int main(){
    queue<int> q;
    for(int i=1;i<=100;i++) q.push(i);

    int j=0;
    while(q.size()>1){
        int cur = q.front();
        q.pop();
        j++;
        if(j%2==1) q.push(cur);
    }
    cout<<q.front()<<endl;
    return 0;
}


