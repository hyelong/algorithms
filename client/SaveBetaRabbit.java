import java.util.*;

public class SaveBetaRabbit{
	public static void main(String[] args){
		int food = 12;
		int[][] grid = new int[][]{{0,2,5},{1,1,3},{2,1,1}};
		int res = answer(food, grid);
		System.out.println(res);
	}
	
public static int answer(int food, int[][] grid) { 

        // Your code goes here.
		if(grid.length==0) return food;
		int m = grid.length;
		int n = grid[0].length;
		int[][] temp = new int[m][n];
		for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
		temp[i][j] = grid[i][j];
		int MIN = getMin(temp);
		if(MIN>food) return -1;
		else if(MIN==food) return 0;
		
		temp = new int[m][n];
		for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
		temp[i][j] = grid[i][j];
		int MAX = getMax(temp);
		if(MAX<food) return food-MAX;
		else if(MAX==food) return 0;
		
		int[] res = new int[1];
		res[0] = food+1;
		helper(food, grid, 0,0,food, res);
		if(res[0]>food) return -1;
		return res[0];
	}
	
	static int getMin(int[][] grid){
	    int m = grid.length;
	    int n = grid[0].length;
	    for(int i=1;i<m;i++)
        {
            grid[i][0]=grid[i-1][0]+grid[i][0];
        }
        
        for(int i=1;i<n;i++)
        {
            grid[0][i]=grid[0][i-1]+grid[0][i];
        }
        
        for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
        {
            grid[i][j]=Math.min(grid[i-1][j],grid[i][j-1])+grid[i][j];
        }
        return grid[m-1][n-1];
	}
	static int getMax(int[][] grid){
	    int m = grid.length;
	    int n = grid[0].length;
	    for(int i=1;i<m;i++)
        {
            grid[i][0]=grid[i-1][0]+grid[i][0];
        }
        
        for(int i=1;i<n;i++)
        {
            grid[0][i]=grid[0][i-1]+grid[0][i];
        }
        
        for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
        {
            grid[i][j]=Math.max(grid[i-1][j],grid[i][j-1])+grid[i][j];
        }
        return grid[m-1][n-1];
	}
	
	
	static void helper(int food, int[][] grid, 
		int row_num, int col_num, int remain_food, int[] res){
		if(remain_food<0) return;
		if(row_num==grid.length-1 && col_num==grid[0].length-1){
			if(remain_food>=0)
				res[0] = Math.min(res[0],remain_food);
			return;
		}
		if(row_num+1 < grid.length)
			helper(food, grid, row_num+1, col_num, remain_food-grid[row_num+1][col_num], res);
		if(col_num+1 < grid[0].length)
			helper(food, grid, row_num, col_num+1, remain_food-grid[row_num][col_num+1], res);
	}
}
