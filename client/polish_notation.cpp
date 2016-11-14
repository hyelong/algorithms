/*
非Reverse的Polish Notation，而且输入是一整个string。
给的例子是 (+ (* 2 3) (/ (+ 4 5) 3)) returns 9 
观察例子可以看到括号都会和数字或者运算符在一个token里，然后不同的token被空格隔开，运算符和数字一定不在一个token里。
*/

#include <iostream>
#include <stack>

using namespace std;

bool isop(const char op){
	return op=='+'||op=='-'||op=='*'||op=='/';
}

int calculate(const int op1, const int op2, const char op){
	int res;
	if(op=='+'){
		res = op1 + op2;
	}
	else if(op == '-'){
		res = op1 - op2;
	}
	else if(op == '*'){
		res = op1 * op2;
	}
	else {
		res = op1 / op2;
	}
	return res;
}
int evalPolishNotation(string s){
	int n = s.length();
	stack<int> st;
	string value;
	for(int i=n-1;i>=0;i--){
		if(isdigit(s[i])){
			value = s[i]+value;
		}
		else{
			if(value.length()>0 && isdigit(value[0])){
				st.push(stoi(value));
				value = "";
			}
			
			if(isop(s[i])){
				int op1 = st.top();
				st.pop();
				int op2 = st.top();
				st.pop();
				int res = calculate(op1, op2, s[i]);
				st.push(res);
			}
		}
	}
	return st.top();
}

int main(){
	string s = "(+ (* 2 3) (/ (+ 4 5) 3))";
	int res = evalPolishNotation(s);
	cout<<res<<endl;
	return 0;
}
