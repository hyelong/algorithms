from sets import Set

def draw_circle(r2):
    res = Set([])
    x = 0
    while x*x<=r2:
        y = 0
        while y*y<=r2:
            if x*x + y*y == r2:
                res.add((x,y))
                res.add((x,-y))
            y += 1
        x += 1

    x = -1
    while x*x<=r2:
        y = -1
        while y*y<=r2:
            if x*x + y*y == r2:
                res.add((x,y))
                res.add((x, -y))
            y -= 1
        x -= 1

    return res

res = draw_circle(25)
for i in res:
    print(i),
print('')
