/*
 * linkedlist,找出最大的两个, 然后swap，不是swap value，swap reference
 */

struct node{
  int index;
  int value;
  node* next;
  node(int i, int v){
      index = i;
      value = v;
      next = 0;
  }
};

void swap_two_bigs(node* head){
    if(!head || !head->next) return;
    node* biggest = 0, *second_biggest = 0;
    node *temp = head;
    while(temp){
        if(!biggest || temp->value > biggest->value) biggest = temp;
        else if(!second_biggest || temp->value > second_biggest->value ) second_biggest = temp;
        temp = temp->next;
    }
    
    temp = head;
    while(temp){
        if(temp == biggest){

        }
        else if(temp == second_biggest){

        }
    }
}

int main(){
    node *head = new node(1, 1);
    head->next = new node(2, 5);
    head->next->next = new node(3, 2);
    head->next->next->next = new node(4, 3);
    swap_two_bigs(head);
    return 0;
}
