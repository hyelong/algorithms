#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
// there are two imporvement: 1, use bit instead of int as input;
// 2, only record next state is 1 
void gameOfLife(vector<vector<int>>& board) {
  int m = board.size();
	if(m == 0) return;
	int n = board[0].size();
	 
	unordered_set<int> next;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++){
			int lives = 0;
			for(int a=max(i-1, 0); a<=min(i+1, m-1); a++){
				for(int b=max(j-1, 0); b<=min(j+1, n-1); b++){
					lives+=board[a][b] & 1;
				}
			}
			if(lives==3 || lives==4 && board[i][j]==1){
				next.insert(i*n + j);
			}
		}
		
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++){
		    int key = i*n+j;
		    if(next.count(key)) board[i][j] = 1;
		    else board[i][j] = 0;
		}
}
    
int main(){

	return 0;
}
