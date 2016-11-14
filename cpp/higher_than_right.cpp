/*
 * 给一个数组，代表曼哈顿上摩天大楼的高度，求哪些大楼能看到
 * 右侧的中央公园。其实就是看某个摩天大楼的高度是否大于其右
 * 侧所有大楼的高度（如果高度相等，则左侧的大楼会被右侧的大
 * 楼挡住，从而看不到中央公园）
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> can_see_right(vector<int> heights){
    stack<int> st;
    for(int height : heights){
        while(!st.empty() && st.top()<=height){
            st.pop();
        }
        st.push(height);
    }
    vector<int> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    return res;
}

int main(){
    vector<int> heights = {5,2,4,1,3};
    vector<int> res = can_see_right(heights);
    for(int i : res)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
