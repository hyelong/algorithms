/*big integer subtraction*/
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;

string subtract(string a, string b){
	if(a.size()<b.size()) return "-"+subtract(b, a);
	if(a<b) return "-"+subtract(b, a);
    string res;
    int len = max(a.size(), b.size());
    int carry = 0;
    for(int i = 0; i<len; i++){
        int va = 0;
        int vb = 0;
        if(i<a.size())  va = a[a.size()-1-i] - '0';
        if(i<b.size())  vb = b[b.size()-1-i] - '0';
        res += (va - vb - carry + 10) % 10 + '0';
        carry = (va - vb - carry + 10) < 10;
    }
    while(res.back()=='0') res.pop_back();
    if(res == "") return "0";
    reverse(res.begin(), res.end());
    return res;
}

string subtract(string a, string b){
	if(a.size()<b.size()) return "-"+subtract(b, a);
	if(a<b) return "-"+subtract(b, a);
    string res;
    int len = max(a.size(), b.size());
    int carry = 0;
    for(int i = 0; i<len; i++){
        int va = 0;
        int vb = 0;
        if(i<a.size())  va = a[a.size()-1-i] - '0';
        if(i<b.size())  vb = b[b.size()-1-i] - '0';
        res += (va - vb - carry + 10) % 10 + '0';
        carry = (va - vb - carry + 10) < 10;
    }
    while(res.back()=='0') res.pop_back();
    if(res == "") return "0";
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    string res = subtract("12","300");
    cout<<res<<endl;
    unsigned long milliseconds_since_epoch = chrono::duration_cast<chrono::milliseconds>
        (chrono::system_clock::now().time_since_epoch()).count();
    cout<<milliseconds_since_epoch<<endl;
    return 0;
}
