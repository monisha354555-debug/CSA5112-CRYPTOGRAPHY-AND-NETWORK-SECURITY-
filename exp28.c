import random
from math import gcd

def modinv(a, m): return pow(a, -1, m)

q, a = 353, 3                      # public values, gcd(a, q-1) = 1
x = random.randrange(2, q - 1)     # Alice's secret
y = random.randrange(2, q - 1)     # Bob's secret
X, Y = pow(x, a, q), pow(y, a, q)  # what they send each other

# Agreeing on a key: each recovers the other's secret using a^-1 mod (q-1)
ai = modinv(a, q - 1)
print(pow(Y, ai, q) == y, pow(X, ai, q) == x)    # True True
key = (x * y) % q                                 # both can compute this

# Eve sees X, Y, a, q, so she does the same thing and finds x and y.
print("Eve finds x:", pow(X, ai, q) == x)