import numpy as np

n = int(input())
sz = 1
while (sz < n):
    sz *= 2

a = np.array([[0 for _ in range(sz)] for _ in range(sz)], int)
b = np.array([[0 for _ in range(sz)] for _ in range(sz)], int)
c = np.array([[0 for _ in range(sz)] for _ in range(sz)], int)

for i in range(n):
    a[i][:n] = np.array(list(map(int, input().split())), int)

for i in range(n):
    b[i][:n] = np.array(list(map(int, input().split())), int)

def mul(a, b, ln):
    res = np.array([[0 for _ in range(ln)] for _ in range(ln)], int)
    if ln == 1:
        res[0, 0] = a[0, 0] * b[0, 0]
        return res
    hf = ln // 2
    a11 = a[:hf, :hf]
    a12 = a[:hf, hf:]
    a21 = a[hf:, :hf]
    a22 = a[hf:, hf:]
    b11 = b[:hf, :hf]
    b12 = b[:hf, hf:]
    b21 = b[hf:, :hf]
    b22 = b[hf:, hf:]
    p1 = mul((a11 + a22), (b11 + b22), hf)
    p2 = mul((a21 + a22), b11, hf)
    p3 = mul(a11, (b12 - b22), hf)
    p4 = mul(a22, (b21 - b11), hf)
    p5 = mul((a11 + a12), b22, hf)
    p6 = mul((a21 - a11), (b11 + b12), hf)
    p7 = mul((a12 - a22), (b21 + b22), hf)
    res[:hf, :hf] = p1 + p4 - p5 + p7
    res[:hf, hf:] = p3 + p5
    res[hf:, :hf] = p2 + p4
    res[hf:, hf:] = p1 - p2 + p3 + p6
    return res


c = mul(a, b, sz)

for i in range(n):
    print(' '.join(map(str, c[i])))
