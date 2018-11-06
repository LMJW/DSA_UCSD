# Uses python3
def calc_fib(n,d):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    a = []
    a.append(0)
    a.append(1)
    flag = False
    r = d
    for i in range(1, n):
        a.append((a[i]+a[i-1])%d)
        if not flag and a[-1] == a[0]:
            r = i+1
            flag = True
        elif a[(i+1)%r] != a[-1] and a[-1] == a[0]:
            r = i+1
        if i == 3*r:
            break
    print(a, r)
    return a[n%d]


if __name__ == '__main__':
    i = input()
    a, b = map(int, i.split())
    print(calc_fib(a, b))