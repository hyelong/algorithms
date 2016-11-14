#include <iostream>
#include <queue>
using namespace std;

int main(){
    queue<int> q;
    int i = 1;
    while(i<=100) q.push(i++);
    i=0;
    while(q.size()>1){
        i++;
        int num = q.front();
        q.pop();
        if(i%5 != 0) q.push(num);
    }
    cout<<q.front()<<endl;
    return 0;
}
