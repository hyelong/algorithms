import math

cache = {}
def choose(n, k):
	if n-k < 0 :
		return 0
	if (n, k) in cache:
	    return cache[(n,k)]
	cache[(n,k)] =  math.factorial(n)/( math.factorial(k)* math.factorial(n-k))
	
	return cache[(n,k)]
	
def connect_ways(n, k, dp):
	if k < n-1 or k > ((n*(n-1))/2): 
		return 0

	if dp[n][k]>0: return dp[n][k]
	
	disconnect_ways = 0
	for i in xrange(1, n):
		sub_sum = 0 
		total = ((n-i)*(n-i-1))/2
		for j in xrange(0, k+1):
			sub_sum += choose(total, j)*connect_ways(i, k-j,dp)  
		disconnect_ways += choose(n,i)*i/n*sub_sum
		
	t = (n*(n-1))/2
	dp[n][k] = choose(t, k) - disconnect_ways
	return dp[n][k]

n, k = 21, 210
dp = [[0 for x in range(k)] for y in range(n)]

print(connect_ways(6,5,dp))
	
