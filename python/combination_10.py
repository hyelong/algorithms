def print_sum_combine(n):
    res = []
    ans = []
    helper(n, 0, res, ans)
    return res

def helper(n, cur, res, ans):
    if cur > n: return
    if cur==n:
        res.append(ans)
        return
    for i in range(n):
        if len(ans)>0 and ans[-1]>i+1 : continue
        helper(n, cur+i+1, res, ans+[i+1])

res = print_sum_combine(4)
print(res)

