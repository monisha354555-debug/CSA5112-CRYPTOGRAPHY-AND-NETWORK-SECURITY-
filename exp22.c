P10=[3,5,2,7,4,10,1,9,8,6]; P8=[6,3,7,4,8,5,10,9]
IP=[2,6,3,1,4,8,5,7];       IPI=[4,1,3,5,7,2,8,6]
EP=[4,1,2,3,2,3,4,1];       P4=[2,4,3,1]
S0=[[1,0,3,2],[3,2,1,0],[0,2,1,3],[3,1,3,2]]
S1=[[0,1,2,3],[2,0,1,3],[3,0,1,0],[2,1,0,3]]

def bits(s):   return [int(c) for c in s.replace(" ", "")]
def string(b): return "".join(map(str, b))
def perm(b, t): return [b[i-1] for i in t]
def xor(a, b):  return [x ^ y for x, y in zip(a, b)]
def sbox(S, b):
    v = S[(b[0] << 1) | b[3]][(b[1] << 1) | b[2]]
    return [v >> 1, v & 1]

def keys(key):
    k = perm(key, P10); l, r = k[:5], k[5:]
    l, r = l[1:] + l[:1], r[1:] + r[:1]; k1 = perm(l + r, P8)
    l, r = l[2:] + l[:2], r[2:] + r[:2]; k2 = perm(l + r, P8)
    return k1, k2

def fk(b, k):
    L, R = b[:4], b[4:]
    t = xor(perm(R, EP), k)
    return xor(L, perm(sbox(S0, t[:4]) + sbox(S1, t[4:]), P4)) + R

def sdes_enc(b, key):
    k1, k2 = keys(key)
    b = fk(perm(b, IP), k1); b = b[4:] + b[:4]
    return perm(fk(b, k2), IPI)

def sdes_dec(b, key):
    k1, k2 = keys(key)
    b = fk(perm(b, IP), k2); b = b[4:] + b[:4]
    return perm(fk(b, k1), IPI)

def blocks(s):
    s = s.replace(" ", "")
    return [bits(s[i:i+8]) for i in range(0, len(s), 8)]

def cbc_encrypt(pt, key, iv):
    prev, out = iv, []
    for p in pt:
        prev = sdes_enc(xor(p, prev), key); out.append(prev)
    return out

def cbc_decrypt(ct, key, iv):
    prev, out = iv, []
    for c in ct:
        out.append(xor(sdes_dec(c, key), prev)); prev = c
    return out

key = bits("01111 11101"); iv = bits("1010 1010")
ct = cbc_encrypt(blocks("0000 0001 0010 0011"), key, iv)
print([string(c) for c in ct])                      # 11110100 00001011
print([string(p) for p in cbc_decrypt(ct, key, iv)])  # 00000001 00100011