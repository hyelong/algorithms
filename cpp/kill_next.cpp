/*
 * 1-100, 1 kill 2, 3 kill 4....until last one left.
 */
#include<iostream>
using namespace std;

struct Node{
    int val;
    Node* next=0;
    Node(int value):val(value){}
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
    while(temp->next!=temp) {
        Node* t = temp->next;
        temp->next = temp->next->next;
        temp = temp->next;
        cout<<"delete: "<<t->val<<endl;
        delete t;
    }
    cout<<temp->val<<endl;
    return 0;
}


