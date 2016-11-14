'''
s is coins set
n is total amount
'''
def count(s, n):
    m = len(s)
    dp = [0]*(n+1)

    dp[0] = 1
    for i in xrange(m):
        for j in xrange(s[i], n+1):
            dp[j] += dp[j-s[i]]

    return dp[n]

s = [2, 1, 3]
print(count(s, 4))

