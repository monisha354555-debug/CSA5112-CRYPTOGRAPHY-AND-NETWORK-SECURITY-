import random
from math import gcd

def factor_from_d(n, e, d):
    k = e * d - 1
    t, r = 0, k
    while r % 2 == 0:
        r //= 2; t += 1
    while True:
        g = random.randrange(2, n - 1)
        if gcd(g, n) > 1: return gcd(g, n)
        x = pow(g, r, n)
        if x in (1, n - 1): continue
        for _ in range(t):
            y = pow(x, 2, n)
            if y == 1 and x not in (1, n - 1): return gcd(x - 1, n)
            if y == n - 1: break
            x = y

print(factor_from_d(3599, 31, 3031))   # 59 or 61