/*
第一道题是print 2d array diagonally top-down, e.g..
[[1,2,3,4], [5,6,7,8], [9,10,11,12]] => 1, 2 5, 3 6 9, 4 7 10, 8 11, 12
*/

#include <iostream>
#include <vector>
using namespace std;

void print_diagonally(vector<vector<int>>& matrix){
	int m = matrix.size();
	int n = matrix[0].size();
	int len = m+n-2;
	for(int sum = 0;sum<=len;sum++){
		// i increases, j decreases
		for(int i=0;i<m;i++){
			int j = sum - i;
			if(j<0) break;
			if(j>=n) continue;
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

void print_zigzag(vector<vector<int>>& matrix){
	cout<<"-------------zigzag----------"<<endl;
	int m = matrix.size();
	int n = matrix[0].size();
	int len = m+n-2;
	for(int sum = 0;sum<=len;sum++){
		if(sum % 2 == 1){
			for(int i=0;i<m;i++){
				int j = sum - i;
				if(j<0) break;
				if(j>=n) continue;
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
		else{
			for(int j=0;j<n;j++){
				int i = sum - j;
				if(i < 0) break;
				if(i >= m) continue;
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
}

int main(){
	vector<vector<int>> matrix = {{1, 2, 3, 4},
								  {5, 6, 7, 8},
								  {9,10,11,12}};
	print_diagonally(matrix);
	print_zigzag(matrix);
	return 0;
}