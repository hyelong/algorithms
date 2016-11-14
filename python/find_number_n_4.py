
def find(arr):
    n = len(arr)
    candidates = [arr[n/4],arr[n/2],arr[3*n/4]]

def find_first_index(arr, value):
    left, right = 0, len(arr)-1
    while left < right :
        mid = left + (right-left)/2
        if arr[mid] < value:
            left = mid + 1
        elif arr[mid] > value:
            right = mid - 1
        else:
            right = mid
    return left


arr = [1,2,2,2,2,2,4]
first = find_first_index(arr, 2)
last = find_first_index(arr, 3)-1
print("first index:"+str(first))
print("last index:"+str(last))
