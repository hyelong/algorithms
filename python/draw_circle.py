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
    x = 1
    while x*x<=r2:
        y = 0
        while y<=x:
            if (x-1)*(x-1)+(y - 1)*(y - 1)<r2 and x*x +y*y>r2:
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

# Midpoint algorithm
# Find the mid-point p of the two possible pixels i.e (x-0.5, y+1)
#
#If p lies inside or on the circle perimeter, we plot the pixel (x, y+1), otherwise if it’s outside we plot the pixel (x-1, y+1)
# Pk = (Xk — 0.5)2 + (yk + 1)2 – r2

# xk+1 = xk or xk-1 , yk+1= yk +1
# Pk+1 = (xk+1 – 0.5)2 + (yk+1 +1)2 – r2
# = (xk+1 – 0.5)2 + [(yk +1) + 1]2 – r2
# = (xk+1 – 0.5)2 + (yk +1)2 + 2(yk + 1) + 1 – r2
# = (xk+1 – 0.5)2 + [ – (xk – 0.5)2 +(xk – 0.5)2 ] + (yk + 1)2 – r2 + (yk + 1) + 1
# = Pk + (xk+1 – 0.5)2 – (xk – 0.5)2 + 2(yk + 1) + 1
# = Pk + (x2k+1 – x2k)2 + (xk+1 – xk)2 + 2(yk + 1) + 1
# = Pk + 2(yk +1) + 1, when Pk <=0 i.e the midpoint is inside the circle
# (xk+1 = xk)
# Pk + 2(yk +1) – 2(xk – 1) + 1, when Pk>0 I.e the mid point is outside the circle(xk+1 = xk-1)
def draw_circle3(r) :
    res = Set([])
    x = r
    y = 0
    p = 1 - r
    while (x > y) :
        y += 1
        if p <= 0 :
            p += 2 * y + 1
        else:
            x -= 1
            p += 2 * (y - x) + 1

        if (x < y):
            break

        res.add((x, y))
        res.add((y, x))
        res.add((-x, y))
        res.add((y, -x))
        res.add((x, -y))
        res.add((-y, x))
        res.add((-x, -y))
        res.add((-y, -x))

    return res
#res = draw_circle(49)
res = draw_circle3(5)
print(res)
