import random, string
A = string.ascii_uppercase
ENG = [8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,
       6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074]
ORDER = "ETAOINSHRDLCUMWFGYPBVKJXQZ"          # English letters, most to least common
COMMON = ["THE","WAS","HAD","WITH","THAT","HAVE","FROM","OF","IT","IS","TO","WE",
          "AND","ING","ION","ENT","FOR","THA","TER","HER","ERE","HAT","TIO","ALL","ITH","VER","OUR","NOT"]
BIGRAMS = ["TH","HE","IN","ER","AN","RE","ND","ON","EN","AT","ES","OR","TE","OF","ED","IS","IT","AL","AR","ST"]

def score(pt):
    s = sum(pt.count(t) * 3 for t in COMMON) + sum(pt.count(b) for b in BIGRAMS)
    s -= 0.5 * sum(abs(pt.count(A[i]) * 100 / len(pt) - ENG[i]) for i in range(26))
    return s

def decode(ct, m): return "".join(m.get(c, c) for c in ct)

def freq_attack(ct, top=10, iters=20000):
    ct = "".join(c for c in ct.upper() if c.isalpha())
    ranked = sorted(A, key=lambda c: -ct.count(c))
    cur = dict(zip(ranked, ORDER))           # start: match letters by frequency rank
    cur_score = score(decode(ct, cur))
    seen = {decode(ct, cur): cur_score}
    for _ in range(iters):                   # hill climbing: swap two mappings
        a, b = random.sample(A, 2)
        new = dict(cur); new[a], new[b] = new[b], new[a]
        pt = decode(ct, new); sc = score(pt); seen[pt] = sc
        if sc >= cur_score: cur, cur_score = new, sc
    return sorted(seen.items(), key=lambda x: -x[1])[:top]

ct = input("Ciphertext: ")
n = int(input("How many top plaintexts? "))
for pt, sc in freq_attack(ct, n):
    print(f"{sc:8.1f}  {pt}")