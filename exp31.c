def cmac_subkeys(L, bits=128):
    Rb = 0x87 if bits == 128 else 0x1B      # constants: 128-bit -> 0x87, 64-bit -> 0x1B
    mask = (1 << bits) - 1
    def dbl(v):
        return ((v << 1) & mask) ^ (Rb if v >> (bits - 1) else 0)
    k1 = dbl(L)
    k2 = dbl(k1)
    return k1, k2

# L = E(K, 0^128). Example from RFC 4493 (AES-128 key 2b7e1516...):
L = int("7df76b0c1ab899b33e42f047b91b546f", 16)
for k in cmac_subkeys(L):
    print(f"{k:032x}")
# fbeed618357133667c85e08f7236a8de
# f7ddac306ae266ccf90bc11ee46d513b