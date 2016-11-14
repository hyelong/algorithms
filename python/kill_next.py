from collections import deque

q = deque()
for i in range(1,101):q.append(i)
j = 0
while len(q)>1:
    cur = q.popleft()
    j += 1
    if j%2==1: q.append(cur)

print q[0]

