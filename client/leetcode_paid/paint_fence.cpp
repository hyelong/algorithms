/*
Problem Description:

There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.
Note:
n and k are non-negative integers.
*/

int numWays(int n, int k) {
    if(k==0 || n == 0 || (n>2 && k==1) ) return 0;
    int sameColor = 0;
    int diffColor = k;
    int total = diffColor + sameColor;
    for(int i=2; i<=n; i++){
        sameColor = diffColor; 
        diffColor = (k-1)*total;
        total = (diffColor+sameColor);
    }
    return total;
}

int main(){
    numWays(10, 5);
    return 0;
}