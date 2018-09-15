
def rank(b, i):
    return b[:i].count(b[i])


def riffle_permutation(B):
    b = bin(B)[2:]
    b = '0' * (8 - len(b)) + b if len(b) < 8 else b[-8:]
    riffle_permutation_func = lambda i: rank(b, i) if b[i] == '0' else rank(b, i) + b.count('1')
    return [riffle_permutation_func(i) for i in range(8)]