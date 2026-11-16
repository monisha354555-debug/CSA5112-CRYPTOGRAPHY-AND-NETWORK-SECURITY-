import string
A = string.ascii_uppercase
ENG = [8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,
       6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074]

def chi_squared(s):
    n = len(s)
    return sum((s.count(A[i]) - n * ENG[i] / 100) ** 2 / (n * ENG[i] / 100) for i in range(26))

def additive_attack(ct, top=10):
    letters = "".join(c for c in ct.upper() if c.isalpha())
    results = []
    for shift in range(26):
        pt = "".join(A[(ord(c) - 65 - shift) % 26] for c in letters)
        results.append((chi_squared(pt), shift, pt))
    return sorted(results)[:top]            # lowest chi-squared = most English-like

ct = input("Ciphertext: ")
n = int(input("How many top plaintexts? "))
for score, shift, pt in additive_attack(ct, n):
    print(f"shift={shift:2d}  score={score:8.2f}  {pt}")