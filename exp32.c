import random, hashlib

def modinv(a, m): return pow(a, -1, m)
def H(m, q): return int.from_bytes(hashlib.sha256(m).digest(), 'big') % q

p, q, g = 283, 47, 64              # toy parameters (q divides p-1)
x = 17                             # private key
y = pow(g, x, p)                   # public key

def sign(m, k):
    r = pow(g, k, p) % q
    s = modinv(k, q) * (H(m, q) + x * r) % q
    return r, s

def verify(m, r, s):
    w = modinv(s, q)
    return (pow(g, H(m, q) * w % q, p) * pow(y, r * w % q, p) % p) % q == r

for _ in range(2):                  # same message, different signatures
    k = random.randrange(1, q)
    r, s = sign(b"hi", k)
    print(r, s, verify(b"hi", r, s))

# Reusing k leaks the private key:
k = 5
r1, s1 = sign(b"m1", k); r2, s2 = sign(b"m2", k)
kk = (H(b"m1", q) - H(b"m2", q)) * modinv((s1 - s2) % q, q) % q
print("recovered x:", (s1 * kk - H(b"m1", q)) * modinv(r1, q) % q)    # 17