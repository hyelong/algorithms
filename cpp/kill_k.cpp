/*
 * 1-100, starts from 1, kill whose value %5==0....until last one left.
 */
#include<iostream>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int value):val(value), next(0){}
};

int main(){
    Node *head = new Node(1);
    Node *temp = head;
    for(int i=2;i<=100;i++){
        temp->next = new Node(i);
        temp = temp->next;
    }
    
    temp->next = head;
    temp = head;
    Node* pre = new Node(0);
    pre->next = temp;
    int i = 0;
    while(temp->next!=temp) {
        i++;
        if(i%5==0){
            Node *t = temp;
            pre->next = temp->next;
            cout<<"delete: "<<t->val<<endl;
        }
        pre = temp;
        temp = temp->next;
    }
    cout<<temp->val<<endl;
    return 0;
}


