def egcd(a, b):
    if b == 0: return a, 1, 0
    g, x, y = egcd(b, a % b)
    return g, y, x - (a // b) * y

def modinv(a, m):
    g, x, _ = egcd(a, m)
    if g != 1: raise ValueError("no inverse")
    return x % m

e, n = 31, 3599
p = next(i for i in range(2, int(n**0.5) + 1) if n % i == 0)   # trial and error
q = n // p
phi = (p - 1) * (q - 1)
d = modinv(e, phi)
print(p, q, phi, d)      # 59 61 3480 3031