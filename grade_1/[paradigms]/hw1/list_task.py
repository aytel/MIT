# Remove equal adjacent elements
#
# Example input: [1, 2, 2, 3]
# Example output: [1, 2, 3]


def remove_adjacent(lst):
    res = []
    for i in lst:
        if (len(res) != 0 and res[len(res) - 1] == i):
            continue
        res.append(i)
    return res


# Merge two sorted lists in one sorted list in linear time
#
# Example input: [2, 4, 6], [1, 3, 5]
# Example output: [1, 2, 3, 4, 5, 6]
def linear_merge(lst1, lst2):
    res = []
    pn1 = 0
    pn2 = 0
    while (pn1 != len(lst1) and pn2 != len(lst2)):
        if (pn1 == len(lst1)):
            res.append(lst2[pn2])
            pn2 += 1
            continue
        if (pn2 == len(lst2)):
            res.append(lst1[pn1])
            pn1 += 1
            continue
        if (lst1[pn1] < lst2[pn2]):
            res.append(lst1[pn1])
            pn1 += 1
        else:
            res.append(lst2[pn2])
            pn2 += 1
    return res
