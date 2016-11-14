#include<iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode *next=NULL;
    ListNode(int value):val(value){}
};

void removeNode(int val, ListNode** head){
    while(*head){
        if((*head)->val==val){
            ListNode *nextNode = (*head)->next;
            delete *head;
            (*head) = nextNode;
        }
        else{
            head = &(*head)->next;
        }
    }
}

void print(ListNode *head){
    while(head){
        cout<<head->val<<endl;
        head = head->next;
    }
}
int main(){
    ListNode *head = new ListNode(0);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    removeNode(1, &head);
    print(head);
    return 0;
}
