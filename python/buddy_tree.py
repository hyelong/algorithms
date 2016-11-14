def setbit_down(A, pos, n):
    if pos>n:
        return
    if A[pos] == 1:
        return
    A[pos] = 1
    setbit_down(A, 2*pos+1, n)
    setbit_down(A, 2*pos+2, n)

def setbit_down1(A, pos, n):
    if pos>=n:
        return
    if 2*pos+1<=n and A[2*pos+1]==0:
        A[2*pos+1]=1
        setbit_down1(A,2*pos+1, n)
    if 2*pos+2<=n and A[2*pos+2]==0:
        A[2*pos+2]=1
        setbit_down1(A, 2*pos+2,n)

def setbit_down2(A, pos, n):
    if pos>n:return
    st = []
    cur = pos
    while cur>=0 and cur<=n or len(st)>0:
        while cur>=0 and cur<=n:
            st.append(cur)
            A[cur]=1
            print(cur)
            cur = 2*cur+1
        temp = st.pop()
        if temp*2+2<=n:
            cur = temp*2+2
        else: cur = -1

if __name__=='__main__':
    A = [0,0,1,1,0,1,1,1,1,1,0,1]
    setbit_down2(A, 1, len(A)-1)
    print(A)
