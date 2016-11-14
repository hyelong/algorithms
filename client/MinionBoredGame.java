package com.google.challenges; 
import java.util.*;

public class MinionBoredGame {   
    public static int answer(int t, int n) { 

        // Your code goes here.
        Map<Integer, Integer> cache = new HashMap<Integer, Integer>();
        return helper(t,n,0,cache);
    } 
    
    public static int helper(int t, int n, int cur, Map<Integer, Integer> cache){
        if(cur==n-1) return 1;
        if(t<=0) return 0;
        int key = 1000*t+cur;
        if(cache.containsKey(key)) return cache.get(key);
        int count = 0;
        if (cur > 0)
		  count += helper(t-1, n, cur-1, cache);
	    if (cur < n-1)
		  count += helper(t-1, n, cur+1, cache);
	    count += helper(t-1, n, cur, cache);
	    count = count % 123454321;
	    cache.put(key, count);
	    return count;
    }
}
