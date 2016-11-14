from math import pow

def answer(x):
    # your code here
    res = 0
    while x>=0:
        res += pow(7,x)
        x -= 1
    return int(res)
    
print(answer(1))
