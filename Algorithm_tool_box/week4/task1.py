# python3

def binsearch(i,j,arr,x):
    if i<=j:
        mid = i+(j-i)//2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            return binsearch(mid+1,j,arr,x)
        else:
            return binsearch(i, mid-1, arr, x)
    else:
        return -1


arr = list(map(int, input().split(" ")))
n, arr = arr[0], arr[1:]
tofind = list(map(int, input().split(" ")))[1:]

res = []
for i in tofind:
    res.append(str(binsearch(0,n-1,arr,i)))
print(" ".join(res))