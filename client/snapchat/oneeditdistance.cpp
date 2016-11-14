#include <cstring>
#include <iostream>
using namespace std;

bool isOneEditDistance(char* s, char* t) {
    while (*s == *t && *s) ++s, ++t;
    int a = strlen(s), b = strlen(t);
    return *s != *t && *(s+(a>=b)) == *(t+(b>=a));
}

int main(){
	char s[] = "snapchat";
	char t[] = "snapchat1";
	bool res = isOneEditDistance(s,t);
	cout<<res<<endl;
	return 0;
}