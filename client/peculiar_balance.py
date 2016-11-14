def answer(x):
	res = []
	cur = 1
	while x > 0 :
		if x % 3 == 0 :
			res.append('-')
			x = x//3
		elif x % 3 == 1 :
			res.append('R')
			x -= cur
			x = x//3
		elif x % 3 == 2 :
			res.append('L')
			x += cur
			x = x//3
			
	return res
	
print(answer(26))
