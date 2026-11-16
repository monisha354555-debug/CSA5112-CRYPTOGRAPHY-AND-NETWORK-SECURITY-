import string
A = string.ascii_uppercase

def otp(text, key, decrypt=False):
    t = [c for c in text.upper() if c.isalpha()]
    return "".join(A[(ord(c) - 65 + (-k if decrypt else k)) % 26] for c, k in zip(t, key))

key = [9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9]
ct = otp("send more money", key)
print(ct)                                              # BEOKJDMSXZPMH
print(otp(ct, key, decrypt=True))                      # SENDMOREMONEY

# 14b: key that makes the same ciphertext decrypt to "cash not needed"
target = "cashnotneeded".upper()
print([(ord(c) - ord(p)) % 26 for c, p in zip(ct, target)])
# [25, 4, 22, 3, 22, 15, 19, 5, 19, 21, 12, 8, 4]