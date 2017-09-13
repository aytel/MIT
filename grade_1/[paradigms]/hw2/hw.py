import os
import sys
from hashlib import sha1 as hasher

SZ = 2 ** 16


def hsh(filename):
    with open(filename, mode='rb') as filename:
        h = hasher()
        up = filename.read(SZ)
        while up:
            h.update(up)
            up = filename.read(SZ)
    return h.hexdigest()

if __name__ == '__main__':
    diff = dict()
    go = os.walk(sys.argv[1])
    for direct, _, files in go:
        for file in files:
            path = os.path.join(direct, file)
            if file[0] == '~' or file[0] == '.' or os.path.islink(path):
                continue
            cur = hsh(path)
            if cur not in diff:
                diff[cur] = []
            diff[cur].append(file + ':' + direct)
    for _, cl in diff.items():
        if len(cl) < 2:
            continue
        print('/'.join(cl))
