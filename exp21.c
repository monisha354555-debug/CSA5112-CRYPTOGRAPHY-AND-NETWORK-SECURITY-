def pad(data: bytes, bs: int = 8) -> bytes:
    n = bs - len(data) % bs              # always adds 1..bs bytes
    return data + b'\x80' + b'\x00' * (n - 1)   # a 1 bit, then zero bits

def unpad(data: bytes) -> bytes:
    s = data.rstrip(b'\x00')
    assert s.endswith(b'\x80'), "bad padding"
    return s[:-1]

print(pad(b"12345678"))   # a full block still gets a whole padding block
print(pad(b"abc"))
print(unpad(pad(b"12345678")))