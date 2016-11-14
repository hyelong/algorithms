#include <iostream>
#include <climits>
#include <sstream>
using namespace std;

bool isop(char c){
    return c=='+'||c=='-'||c=='*';
}
int diffWaysToCompute(string input) {
    int n=input.length();
    
    int res;
    int mx=INT_MIN;
    for(int i=0;i<n;i++){
        if(!isop(input[i])) continue;
        int left = diffWaysToCompute(input.substr(0,i));
        int right = diffWaysToCompute(input.substr(i+1));
        char op = input[i];
        if(op=='+'){
            res=(left+right);
        }else if(op=='-'){
            res=(left-right);
        }else{
            res=(left*right);
        }
        mx = max(mx, res);
    }
    if(mx==INT_MIN) return stoi(input);
    return mx;
}

int main(){
    string input = "2*3-4*5";
    cout<<diffWaysToCompute(input)<<endl;


    return 0;
}