# Uses python3
def calc_fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    a, b = 0,1
    for i in range(2, n+1):
        a, b = b%10, (a+b)%10
    return b

n = int(input())
print(calc_fib(n)%10)
