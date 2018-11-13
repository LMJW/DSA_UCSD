# python3

def findmax(a, b):
    a = sorted(a)
    b = sorted(b)
    n = len(a)
    res = 0
    for i in range(n):
        res += a[i]*b[i]
    return res

n = int(input())
a = list(map(int, input().split(" ")))
b = list(map(int, input().split(" ")))

print(findmax(a,b))