# Uses python3

def gcd_naive(a, b):
    if b>a:
        a,b = b,a
    def _gcd(a,b):
        if b == 0:
            return a
        return _gcd(b, a%b)
    return _gcd(a,b)

if __name__ == "__main__":
    i = input()
    a, b = map(int, i.split())
    print(gcd_naive(a, b))
