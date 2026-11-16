# State: 5x5 lanes of 64 bits. Rate 1024 bits = 16 lanes, capacity = 9 lanes (all zero).
state = [[False] * 5 for _ in range(5)]
for i in range(16):
    state[i // 5][i % 5] = True            # lanes holding P0 (nonzero)

def all_nonzero(s): return all(s[y][x] for y in range(5) for x in range(5))

rounds = 0
while not all_nonzero(state):
    rounds += 1
    C = [any(state[y][x] for y in range(5)) for x in range(5)]       # theta column parity
    state = [[state[y][x] or C[(x - 1) % 5] or C[(x + 1) % 5]
              for x in range(5)] for y in range(5)]
print("rounds needed:", rounds)    # 1