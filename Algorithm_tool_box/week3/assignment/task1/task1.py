# Uses python3

def michange(x):
    d = [10,5,1]
    i = 0
    count = 0
    while x != 0:
        while x>= d[i]:
            x-=d[i]
            count+=1
        i+=1
    return count

n = int(input())
print(michange(n))