/*
 * idea:
 * 1) If right subtree of node is not NULL, then succ lies in right subtree. Do following.
 * Go to right subtree and return the node with minimum key value in right subtree.
 * 2) If right sbtree of node is NULL, then succ is one of the ancestors. Do following.
 * Travel up using the parent pointer until you see a node which is left child of it’s parent. The parent of such a node is the succ.
 */

struct node
{
    int val;
    node* left;
    node* right;
    node* parent;
    node(int data):val(data){}
};

node* inorder_successor(node* root, node* n){
  if(n->right){
    node* temp = n->right;
    while(temp->left){
      temp = temp->left;
    }
    return temp;
  }

  node* parent = n->parent;
  while(parent && n = parent->right){
    n = parent;
    parent = parent->parent;
  }
  return parent;
}

int main(){

}
