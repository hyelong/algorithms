#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
//bool operator<(const Interval a, const Interval b){return a.start<b.start;};

struct interval_cmp {
    bool operator()(const Interval& a, const Interval& b) const {
        return a.end <= b.end;
    }
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), 
            [](const Interval &a, const Interval &b){
                return a.start < b.start;
            });

        for (auto a : intervals) {
            if(rooms.size()==0){
                rooms.push_back(vector<Interval>(1, a));
            }
            else{
                bool add_new = true;
                for(auto& room : rooms){
                    if(room.back().end<=a.start){
                        room.push_back(a);
                        add_new = false;
                        break;
                    }
                }
                if(add_new){
                    rooms.push_back(vector<Interval>(1, a));
                }
            }
        }

        for(auto room : rooms){
            for(auto meeting : room){
                cout<<meeting.start<<"->"<<meeting.end<<";";
            }
            cout<<endl;
        }
        int res = rooms.size();
        return res;
    }
private:
    vector<vector<Interval>> rooms;
};

int main(){
    Solution sol;
    vector<Interval> v = {{0,30}, {5, 10}, {15, 18}, {6,14}, {18, 20}, {11,16}};
    auto res = sol.minMeetingRooms(v);

    cout<<res<<endl;

 
    return 0;
}