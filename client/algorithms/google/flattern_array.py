// res is a lacal variable
def flattern(arr):
	res = []
	for item in arr:
		if type(item) is list:
			temp = flattern(item)
			res += temp
		else:
			res.append(item)

	return res

//res is reference
def flattern2(arr, res):
	for item in arr:
		if type(item) is list:
			flattern2(item, res)
		else:
			res.append(item)


arr = [1,[2,3,[5,6]],4]
res = []
flattern2(arr, res)
print(res)