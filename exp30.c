import hmac, hashlib

def E(k, block):                      # stand-in keyed block function
    return hmac.new(k, block, hashlib.sha256).digest()[:8]

def cbc_mac(k, msg):
    t = bytes(8)
    for i in range(0, len(msg), 8):
        t = E(k, bytes(a ^ b for a, b in zip(t, msg[i:i+8])))
    return t

k = b"secret"
X = b"ABCDEFGH"
T = cbc_mac(k, X)
forged = X + bytes(a ^ b for a, b in zip(X, T))     # X || (X xor T)
print(T.hex(), cbc_mac(k, forged).hex())            # identical tags