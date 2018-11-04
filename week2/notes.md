# Fibonacci numbers

## Native algorithm

```python
def fibrecur(n):
    if n <=1:
        return n
    return fibrecur(n-1) + fibrecur(n-2)
```

## Efficient algorithm

```python
def fib(n):
    a = []
    a.append(0)
    a.append(1)
    c = 1
    t = a[c]+a[c-1]
    while t<n:
        a.append(t)
        c += 1
        t = a[c]+a[c-1]
    return a[c]
```

# Greatest Common divider

## Native algorithm

```python
def nativegcd(a,b):
    best = 0
    for d in range(1, a+b):
        if a%d==0 and b%d ==0:
            best = d
    return best
```

## Efficient algorithm (Euclidean algorithm)

In order to do this more efficiently, you need to know this:

> Let a' is the remainder when a is divided by b, then
> gcd(a,b) = gcd(a', b) = gcd(b, a')
>
> Proof:
> a = a' + b*q
> d divides a and b if and only if d divided both a' and b

Reduce about ```log(a*b)``` steps.

NOTE: In order to find efficient solution, you need to know something **interesting** about the structure of the solution.

```python
def EculideanGCD(a,b):
    if b == 0:
        return a
    return EculideanGCD(b, a%b)
```

# Big O notation

`a^(log_a(N)) = N`

[Logarithm rule cheatsheet](https://mathinsight.org/logarithm_basics)

# Overview of the course

- Algorithm is hard to teach, sometimes may need unique insight of the problem
- No generic procedure to solve all problems

## Three most common algorithm design technics

* Greedy algorithm
    - make one decision base on locally optimal decision.
* Divide and conquer
    - break big problem into small problems.
* Dynamic programming
    - large problem is depended on small problems.

## How to design algorithm

Step 1. Naive algorithm.
Step 2. Algorithm by the way of standard tools.
Step 3. optimize algorithm.

Step 4.Sometimes you need unique insight to make a magic algorithm.
