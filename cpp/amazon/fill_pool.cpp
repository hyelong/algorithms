/*
 *给了一个游泳池,要求出多少时间水池放满水。
 有以下参数.
 size 泳池的容量.
 pipe[] 放水的水管,里面每个元素是注水速度,每分钟多少升水。比如pipet[3] = 20 就说 明第3根管子每分钟20L水
 events[] events又是一个新的class,在下面.
 class events
 { 
    enum(start,end) ev;
    time;
    pipeID;
 }

 一个events array比如:
 Action Time PipiID 
 start  10   1
 start  30   2
 end    110  1
 start  150  3
 end    200  2

 要求写一个function, get_time_fillup_pool.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct event{
    int event_type;
    int time;
    int pipeId;
    event(int type, int t, int id):event_type(type), time(t),pipeId(id){}
};

int get_time_fillup_pool(int pool_size, vector<int>& pipets, vector<event>& events){
    unordered_map<int, event> opened_pipes;
    for(event e : events){
        int sum = 0;
        int cur_time = e.time;
        for(auto it=opened_pipes.begin();it<opened_pipes.end();it++){
            event opened = it->second;
            sum += (cur_time - opened.time)*pipets[opened.pipeId];
        }
        if(e.event_type==1) opened_pipes.erase(e.pipeId);
        if(sum>=pool_size) return e.time;
    }
    return -1;
}

int main(){
    
    return 0;
}
