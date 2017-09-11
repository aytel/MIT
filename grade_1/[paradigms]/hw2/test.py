import os
from hashlib import sha1 as hasher

SZ = 2 ** 16


def hsh(filename):
    with open(filename, mode='rb') as filename:
        h = hasher()
        up = filename.read(SZ)
        while up:
            h.update(up)
            up = filename.read(SZ)
    filename.close()
    return h.hexdigest()

diff = dict()

go = os.walk('.')

for direct, _, files in go:
    for file in files:
        path = os.path.join(direct, file)
        if file[0] == '~' or file[0] == '.' or os.path.islink(path):
            continue
        cur = hsh(direct + '\\' + file)
        if cur not in diff:
            diff[cur] = []
        diff[cur].append((direct, file))

for _, cl in diff.items():
    if len(cl) < 2:
        continue
    for direct, file in cl:
        print(file, ':', direct, sep='', end=' / ')
    print()
