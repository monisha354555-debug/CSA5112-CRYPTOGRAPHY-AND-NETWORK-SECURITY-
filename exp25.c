from math import gcd
e, n = 31, 3599
m = 59 * 7                      # example plaintext block sharing factor 59 with n
c = pow(m, e, n)
p = gcd(c, n)                   # gcd(c, n) = gcd(m, n), since c = m^e mod n
print(p, n // p)               # 59 61: n is factored, so the private key follows