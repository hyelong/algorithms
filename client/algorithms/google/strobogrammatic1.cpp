/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/
#include <iostream>
#include <unordered_map>
using namespace std;

bool isStrobogrammatic(string num){
	unordered_map<char, char> lut; 
	lut['0'] = '0';
    lut['1'] = '1';
    lut['6'] = '9';
    lut['8'] = '8';
    lut['9'] = '6';

    int n = num.length(); 
    for (int l = 0, r = n - 1; l <= r; l++, r--)
        if (lut.find(num[l]) == lut.end() || lut[num[l]] != num[r])
            return false;
    return true;
}

int main(){
	string num = "6";
	bool res = isStrobogrammatic(num);
	cout<<res<<endl;
	return 0;
}
