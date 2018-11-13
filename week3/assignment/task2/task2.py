# Uses python3

n, bag = map(int, input().split(" "))
val = []
vol = []
for i in range(n):
    x, y = map(int, input().split(" "))
    val.append(x/y)
    vol.append(y)
vv = list(zip(val, vol))
vv = sorted(vv, key = lambda t: t[0], reverse=True)
total = 0
for i in vv:
    if i[1]< bag:
        total += i[1]*i[0]
        bag -= i[1]
    else:
        total += bag*i[0]
        bag = 0
    if bag == 0:
        break

print(total)