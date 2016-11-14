def answer(t, n):
  # your code here
  return helper(t,n,0)
    
cache = {}
def helper(t, n, cur):
	if cur == n-1 : return 1
	if t <= 0 : return 0
	key = 1000*t + cur
	if key in cache: return cache[key]
	count = 0
	if cur > 0:
		  count += helper(t-1, n, cur-1)
	if cur < n-1:
		  count += helper(t-1, n, cur+1)
	count += helper(t-1, n, cur)

	count = count % 123454321
	cache[key] = count
	return count
    
print(answer(900,800))
