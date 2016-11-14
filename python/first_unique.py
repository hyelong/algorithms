'''find first unique character in a string'''
def find(s):
    char_set = [0]*128
    for c in s:
        char_set[ord(c)] += 1
    for c in s:
        if char_set[ord(c)]==1:
            return c

s = "aabbcdde"
print(find(s))
