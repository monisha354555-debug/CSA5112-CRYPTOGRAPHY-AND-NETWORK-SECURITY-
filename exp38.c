from math import gcd

def mat_mul(X, Y, m=26):
    return [[sum(X[i][k] * Y[k][j] for k in range(len(Y))) % m
             for j in range(len(Y[0]))] for i in range(len(X))]

def mat_inv(M, m=26):                       # Gauss-Jordan mod m
    n = len(M)
    a = [row[:] + [int(i == j) for j in range(n)] for i, row in enumerate(M)]
    for col in range(n):
        piv = next((r for r in range(col, n) if gcd(a[r][col], m) == 1), None)
        if piv is None: raise ValueError("matrix not invertible mod 26")
        a[col], a[piv] = a[piv], a[col]
        iv = pow(a[col][col], -1, m)
        a[col] = [x * iv % m for x in a[col]]
        for r in range(n):
            if r != col:
                f = a[r][col]
                a[r] = [(x - f * y) % m for x, y in zip(a[r], a[col])]
    return [row[n:] for row in a]

# Hill: C = K * P (blocks as columns). Recover K from n known pairs: K = C * P^-1
K = [[9, 4], [5, 7]]                         # secret key
P = [[7, 11], [4, 15]]                       # two plaintext blocks as columns
C = mat_mul(K, P)                            # attacker sees P and C
print("Known-plaintext:", mat_mul(C, mat_inv(P)))        # [[9, 4], [5, 7]]

# Chosen plaintext: use P = identity, then ciphertext columns ARE the key
I = [[1, 0], [0, 1]]
print("Chosen-plaintext:", mat_mul(K, I))                # [[9, 4], [5, 7]]