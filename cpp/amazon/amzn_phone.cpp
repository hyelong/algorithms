/*
# Write a function that takes as input an array of objects.  The objects will be either integers or character
# representations of +, -, and * (let's ignore division at the moment).  It should return the result by
# applying the arithmetical operations defined in the Reverse Polish Notation of the array (also known as
# postfix notation).

# Examples:

# [1, 3, +] =>        1 + 3  =>  4
#
# [6, 3, -] =>        6 - 3 => 3
#
# [2, 3, +, 5, *]  => (2 + 3) * 5 => 5 * 5 => 25
#
# [2, 3, 5, *, +]  => 2 + (3 * 5) => 2 + 15 => 17

[2,1,1,+]
[2,1,+,+]
[2,1,!]
*/

int calculate(int v1, int v2, string op){
    if(op=="+") return v1+v2;
    if(op=="-") return v1-v2;
    if(op=="*") return v1*v2;
    if(op=="/") return v1/v2;
}

bool isOp(string op){
    return op=="+" || op=="-" || op=="*" || op=="/";
}

bool isNumber(string s){
    return true;
}

int eval(vector<string>& expression){
    int n = expression.size();
    if(n==0) return 0;
    if(n==1) return stoi(expression[0]);
    stack<int> _stack;
    int res = 0;
    for(int i=0;i<n;i++){
        if(isOp(expression[i])){
            if(_stack.size() < 2) throw "input has too many operators, please check!";
            
            int v2 = _stack.top();
            _stack.pop();
            
            int v1 = _stack.top();
            _stack.pop();
            res = calculate(v1, v2, expression[i]);
            _stack.push(res);
        }
        else{
            if(!isNumber(expression[i])) throw "not supported operands or operator";
            _stack.push(stoi(expression[i]));
        }
    }
    if(_stack.size()!=1) throw "input has too less operators, please check!";
    return res;
}





/* ------------------------------------------------------------------------- */

class Node{
  int abstract eval(){
  }
  int abstract isOp(){
  }
}

class Operand implements Node{
    int eval(){
    }
    
    
}

class Long implements Operand {
    int eval(){
    }
}

class Decimal impliments Operand {
    int eval(){
    }
}

class Operator implements Node{
    bool isOp(){
        return true;
    }
}

class BinaryOperator implements Operator {
    Node left, right;
}

class Plus implements BinaryOperator {
    int eval(){
        return left.eval() + right.eval();
    }
}

class Minus implements BinaryOperator {
    int eval(Node left, Node right){
        return left.eval() - right.eval();
    }
}

class Multiply implements BinaryOperator {
    
}

class Div implements BinaryOperator {
}

int eval(vector<Node>& expression){
    int n = expression.size();
    for(int i=0;i<n;i++){
        if(expression[i].isOp()){
            Node v2 = _stack.top();
            _stack.pop();
            Node v1 = _stack.top();
            _stack.pop();
            expression[i].eval(v1, v2);
        }
    }
}

class Factorial implements UnaryOperator {
    int eval(Node lhs){
        return factorial(lhs);
    }
}


