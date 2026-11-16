def ctr_mode(data, key, start=0):          # same function encrypts and decrypts
    out = []
    for i, p in enumerate(data):
        keystream = sdes_enc(bits(format((start + i) % 256, '08b')), key)
        out.append(xor(p, keystream))
    return out

key = bits("01111 11101")
ct = ctr_mode(blocks("00000001 00000010 00000100"), key)
print([string(c) for c in ct])                       # 00111000 01001111 00110010
print([string(p) for p in ctr_mode(ct, key)])        # original plaintext