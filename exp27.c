def encrypt_letters(msg, e, n):
    return [pow(ord(c) - 65, e, n) for c in msg.upper()]

def attack(cts, e, n):
    table = {pow(i, e, n): chr(65 + i) for i in range(26)}   # precompute 26 values
    return "".join(table[c] for c in cts)

e, n = 31, 3599
cts = encrypt_letters("HELLO", e, n)
print(attack(cts, e, n))     # HELLO