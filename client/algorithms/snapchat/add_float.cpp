#include <iostream>
using namespace std;

string add_int(string s1, string s2){
	int len1 = s1.length();
	int len2 = s2.length();

	int carry = 0;
	string res="";
	
	int i=0;
	
	while(i<len1 || i<len2){
		int a = 0;
		int b = 0;
		if(i<len1){
			a = s1[len1-1-i]-'0';
		}
		if(i<len2){
			b = s2[len2-1-i]-'0';
		}
		int sum = a+b+carry;
		res = to_string(sum%10) + res;
		carry = sum/10;
		
		i++;
	}
	if(carry) res = "1" + res;
	return res;
}

string add_decimal(string s1, string s2){
	int len1 = s1.length();
	int len2 = s2.length();
	int n = max(len1, len2);
	if(len1 < n){
		int diff = n-len1;
		while(diff>0){
			s1 += '0';
		}
	}
	if(len2 < n){
		int diff = n-len2;
		while(diff>0){
			s2 += '0';
		}
	}
	int carry = 0;
	string res="";
	for(int i=n-1; i>=0; i--){
		int sum = s1[i]-'0' + s2[i]-'0' + carry; 
		res = to_string(sum%10) + res;
		carry = sum/10;
	}
	if(carry) res = "1."+res;
	else res = "0."+res;
	return res;
}

string add_float(string s1, string s2){
	int dot_pos1 = s1.find('.');
	int dot_pos2 = s2.find('.');
	string decimal_part = add_decimal(s1.substr(dot_pos1+1), s2.substr(dot_pos2+1));
	cout<<decimal_part<<endl;
	string int_part = add_int(s1.substr(0, dot_pos1), s2.substr(0, dot_pos2));
	cout<<int_part<<endl;
	if(decimal_part[0]=='1')
	int_part = add_int("1", int_part);
	
	return int_part + decimal_part.substr(1);
}

int main(){
	string s1 = "11.23";
	string s2 = "91.89";
	string res = add_float(s1, s2);
	cout<<res<<endl;
}
