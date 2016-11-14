'''given two arrays [4,2,1,5,3],postions:[3,1,0,4,2], restore to[1,2,3,4,5]'''
def restore(arr, pos):
    for i in range(len(pos)):
        while pos[i] != i:
            j = pos[i]
            arr[i], arr[j] = arr[j], arr[i]
            pos[i], pos[j] = pos[j], pos[i]


arr=[4,2,1,5,3]
pos=[3,1,0,4,2]
restore(arr, pos)
print(arr)
