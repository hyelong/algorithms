/*
Given an integer array, adjust each integers so that the difference of 
every adjcent integers are not greater than a given number target. 

If the array before adjustment is A, the array after adjustment is B, 
you should minimize the sum of |A[i]-B[i]| 

You can assume each number in the array is a positive integer and not greater than 100 

Given [1,4,2,3] and target=1, one of the solutions is [2,3,2,3], 
the adjustment cost is 2 and it's minimal. Return 2.
*/
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

int MinAdjustmentCost(vector<int>& A, int target) {
    if (A.size() == 0) {
        return 0;
    }
    
    int size = A.size();
    vector<vector<int>> table(size, vector<int>(101));

    for (int i = 0; i < size; i++) {
        for (int j = 1; j <= 100; j++) {
            table[i][j] = INT_MAX;
            if (i == 0) {
                // The first element.
                table[i][j] = abs(j - A[i]);
            } else {
                for (int k = 1; k <= 100; k++) {
                    // 不符合条件 
                    if (abs(j - k) > target) {
                        continue;
                    }
                    
                    int dif = abs(j - A[i]) + table[i - 1][k];
                    table[i][j] = min(table[i][j], dif);
                }
            }
        }
    }
    
    int ret = INT_MAX;
    for (int i = 1; i <= 100; i++) {
        ret = min(ret, table[size - 1][i]);
    }
    
    return ret;
}

int main(){
	vector<int> arr = {1,4,2,3};
	int target = 1;
	int res = MinAdjustmentCost(arr, target);
	cout << res << endl;
	return 0;
}