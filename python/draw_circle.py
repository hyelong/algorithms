from sets import Set

def draw_circle(r2):
    res = Set([])
    x =1
    while x*x<=r2:
        y = 0
        while y<=x:
            if x*x + y*y == r2:
                res.add((x,y))
                res.add((y,x))
                res.add((-x, y))
                res.add((y, -x))
                res.add((x,-y))
                res.add((-y, x))
                res.add((-x, -y))
                res.add((-y, -x))
            y += 1
        x += 1
    return res

def draw_circle2(r2):
    res = Set([])
    x =1
    while x*x<=r2:
        y = 0
        while y<=x:
            if (x-1)*(x-1)+(y-1)*(y-1)<r2 and x*x +y*y>r2:
                res.add((x,y))
                res.add((y,x))
                res.add((-x, y))
                res.add((y, -x))
                res.add((x,-y))
                res.add((-y, x))
                res.add((-x, -y))
                res.add((-y, -x))
            y += 1
        x += 1
    return res

#res = draw_circle(49)
res = draw_circle2(25)
print(res)
