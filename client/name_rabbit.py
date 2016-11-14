def compare(s1, s2):
	value1 = 0
	value2 = 0
	for c in s1:
		value1 += (ord(c) - ord('a') + 1)	
	for c in s2:
		value2 += (ord(c) - ord('a') + 1)

	if value1 == value2:
		if s2 >= s1 : return 1
		else: return -1
	return value2 - value1
	
a = ["annie", "bonnie", "liz"]
#a = ["abcdefg", "vi"]
b = sorted(a, cmp=compare)

print(b)
