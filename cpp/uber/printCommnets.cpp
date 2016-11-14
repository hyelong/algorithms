// This is the text editor interface. 
// Anything you type or change here will be seen by the other person in real time.

//NewsOnchat.
//React Native Js  from facebook

int x = 0;

/* sdlfsldflsk */

void functionA() {

}


/**slkdlksdlfk
   sldksklk */

// io stream
// file
// a big string

#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

void printComments(){
    string line;
    bool multi_line_start = false;
    while(getline(cin, line)){
        if(!multi_line_start){
            int pos = line.find("//");
            if(pos != string::npos){
                cout<<line.substr(pos+2)<<endl;
                continue;
            }
            pos = line.find("/*");
            if(pos != string::npos){
                int end = line.find("*/");
                if(end != string::npos){
                    cout<<line.substr(pos+2, end - pos -2 )<<endl; 
                }
                else{
                    cout<<line.substr(pos+2)<<endl;
                    multi_line_start = true;
                }
            }
        }
        else{
            int end1 = line.find("*/");
            if(end1 != string::npos){
                cout<<line.substr(0, end1-2)<<endl;
                multi_line_start = false;
            }
            else{
                cout<<line<<endl;
            }
        }
    }
}

int main(){
    printComments();
}
