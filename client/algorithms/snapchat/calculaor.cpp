#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int precedence(string op){
    if(op=="*"||op=="/") return 2;
    if(op=="+" || op=="-") return 1;
    return 0;
}

vector<string> convertToRPN(vector<string> &expression) {
    vector<string> rpolish;
    stack<string> ops;
    for(string exp : expression){
        if(isdigit(exp[0])){
            //if it is a number
            rpolish.push_back(exp);
        }
        else if(exp=="("){
            ops.push(exp);
        }
        else if(exp==")"){
            while(!ops.empty() && ops.top()!="("){
                rpolish.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else{
            while(!ops.empty() && precedence(ops.top())>=precedence(exp)){
                rpolish.push_back(ops.top());
                ops.pop();
            }
            ops.push(exp);
        }
    }

    while(!ops.empty()){
        rpolish.push_back(ops.top());
        ops.pop();
    }
    return rpolish;
}

int caculate(int v1, int v2, string op)
{
        if(op== "+")
        return v1+v2;
        if(op== "-")
        return v1-v2; 
        if(op== "*")
        return v1*v2;
        if(op== "/")
        return v1/v2;
    
}
bool isOp(string c)
{
    return c=="+"||c=="-"||c=="*"||c=="/";
}

int evalRPN(vector<string> &tokens) {
    int n = tokens.size();
    if(n==0) return 0;
    if(n==1) return stoi(tokens[0]);
    stack<int> _stack;
    int result=0;
    for(int i=0;i<n;i++)
    {
        if(isOp(tokens[i]))
        {
            int v2 = _stack.top();
            _stack.pop();
            int v1 = _stack.top();
            _stack.pop();
            result = caculate(v1,v2,tokens[i]);
            _stack.push(result);
        }
        else
        {
            _stack.push(stoi(tokens[i]));
        }
    }
    return result;
}

vector<string> parse(string s){
	vector<string> res;
	string num="";
	for(int i=0;i<s.length();i++){
		if(isdigit(s[i])){
			num+=s[i];
		}
		else{
			if(s[i]==' ') continue;
			if(num!=""){
				res.push_back(num);
				num = "";
			}
			
			res.push_back(string(1, s[i]));
		}
	}
	if(num!="") res.push_back(num);
	return res;
}

int main(){
	string s = "(2+1)*(31-1)/2";
	vector<string> expression = parse(s);

	vector<string> res = convertToRPN(expression);
	int value = evalRPN(res);

	cout<<value<<endl;
	return 0;
}
