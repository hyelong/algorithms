from collections import defaultdict

cache =  defaultdict(list)

def find(target):
    if target < 3: return [1,1,2][target]
    
    if target in cache.keys(): return cache[target]
        
    half = target/2
    if target & 1:
        cache[target] = find(half) + find(half-1) + 1
    else:
        cache[target] = find(half) + find(half+1)+half
    return cache[target]

def binarySearch(low, high, target, odd):
    if high <= low: return None
    mid = (low + high)/2
    mid += (odd != (mid & 1))
    res = find(mid)
    if res == target: return mid
    if res < target: 
        return binarySearch(mid+1, high, target, odd)
    else:
        return binarySearch(low, mid-1, target, odd)
        
def answer(str_S):
    low = 0
    high = int(str_S)
    return binarySearch(low, high, high, 1) or binarySearch(low, high, high, 0)
    


print(answer(7))      

    
        
        
