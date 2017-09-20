import numpy as np


def mul(a, b):
    length = len(a)
    if length <= 128:
        return np.dot(a, b)
    hf = length // 2
    a11 = a[:hf, :hf]
    a12 = a[:hf, hf:]
    a21 = a[hf:, :hf]
    a22 = a[hf:, hf:]
    b11 = b[:hf, :hf]
    b12 = b[:hf, hf:]
    b21 = b[hf:, :hf]
    b22 = b[hf:, hf:]
    p1 = mul((a11 + a22), (b11 + b22))
    p2 = mul((a21 + a22), b11)
    p3 = mul(a11, (b12 - b22))
    p4 = mul(a22, (b21 - b11))
    p5 = mul((a11 + a12), b22)
    p6 = mul((a21 - a11), (b11 + b12))
    p7 = mul((a12 - a22), (b21 + b22))
    res11 = p1 + p4 - p5 + p7
    res12 = p3 + p5
    res21 = p2 + p4
    res22 = p1 - p2 + p3 + p6
    return np.vstack([np.hstack([res11, res12]), np.hstack([res21, res22])])


def read_matrix(n, sz):
    mtrx = np.zeros((sz, sz), dtype=np.int)
    for i in range(n):
        mtrx[i][:n] = np.array(list(map(int, input().split())), int)
    return mtrx


def print_matrix(mtrx, n):
    for i in range(n):
        print(' '.join(map(str, c[i][:n])))


if __name__ == '__main__':
    n = int(input())
    sz = 1
    while (sz < n):
        sz *= 2

    a = read_matrix(n, sz)
    b = read_matrix(n, sz)

    c = mul(a, b)

    print_matrix(c, n)
