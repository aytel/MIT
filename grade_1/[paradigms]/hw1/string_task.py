# Given a string, if its length is at least 3,
# add 'ing' to its end.
# Unless it already ends in 'ing', in which case
# add 'ly' instead.
# If the string length is less than 3, leave it unchanged.
# Return the resulting string.
#
# Example input: 'read'
# Example output: 'reading'


def verbing(s):
    if (len(s) > 2):
        if (s[len(s) - 3:len(s)] == 'ing'):
            s += 'ly'
        else:
            s += 'ing'
    return s


# Given a string, find the first appearance of the
# substring 'not' and 'bad'. If the 'bad' follows
# the 'not', replace the whole 'not'...'bad' substring
# with 'good'.
# Return the resulting string.
#
# Example input: 'This dinner is not that bad!'
# Example output: 'This dinner is good!'


def not_bad(s):
    p1 = s.find('not')
    p2 = s.find('bad')
    if (p1 != len(s) and p2 != len(s) and p1 < p2):
        return s[0:p1] + 'good' + s[p2 + 3:len(s)]
    return s


# Consider dividing a string into two halves.
# If the length is even, the front and back halves are the same length.
# If the length is odd, we'll say that the extra char goes in the front half.
# e.g. 'abcde', the front half is 'abc', the back half 'de'.
#
# Given 2 strings, a and b, return a string of the form
#  a-front + b-front + a-back + b-back
#
# Example input: 'abcd', 'xy'
# Example output: 'abxcdy'


def front_back(a, b):
    ah = (len(a) - 1) // 2 + 1
    bh = (len(b) - 1) // 2 + 1
    af = a[0:ah]
    asc = a[ah:len(a)]
    bf = b[0:bh]
    bsc = b[bh:len(b)]
    return af + bf + asc + bsc
