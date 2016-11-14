#include <iostream>
using namespace std;

int countWords(const char *str){
    bool inword = false;
    int count = 0;
    while(*str){
        if(!inword && isalpha(*str)){
            inword = true;
            count++;
        }
        else if(inword && !isalpha(*str)) inword = false;
        str++;
    }
    return count;
}

int main(){
    const char *str="Hello, my name is john";
    int res = countWords(str);
    cout<<res<<endl;
    return 0;
}
