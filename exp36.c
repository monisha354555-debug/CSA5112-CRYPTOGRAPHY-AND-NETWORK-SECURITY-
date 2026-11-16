from math import gcd

def affine_encrypt(text, a, b):
    assert gcd(a, 26) == 1, "a must be coprime with 26"
    return "".join(chr((a * (ord(c) - 65) + b) % 26 + 65) for c in text.upper() if c.isalpha())

def affine_decrypt(ct, a, b):
    ai = pow(a, -1, 26)
    return "".join(chr(ai * (ord(c) - 65 - b) % 26 + 65) for c in ct)

print([a for a in range(1, 26) if gcd(a, 26) == 1])
# [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
c = affine_encrypt("HELLO", 5, 8)
print(c, affine_decrypt(c, 5, 8))