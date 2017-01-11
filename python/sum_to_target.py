def sum_to_target(start, arr, target):
    if target == 0 :
        return True
    if start >= len(arr) :
        return False

    for i in range(start, len(arr)):
        if sum_to_target(i+1, arr, target-arr[i]):
            return True
    return False


def sum_to_target2(start, arr, target):
    if target == 0 :
        return True
    if start >= len(arr) :
        return False
    return sum_to_target2(start+1, arr, target-arr[start]) or \
        sum_to_target2(start+1, arr, target)

res = sum_to_target2(0, [2,4,6,-9], -5)
print(res)
