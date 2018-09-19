
def rank(b, i):
    return b[:i].count(b[i])


def riffle_permutation(B):
    b = bin(B)[2:]
    b = '0' * (8 - len(b)) + b if len(b) < 8 else b[-8:]
    riffle_permutation_func = lambda i: rank(b, i) if b[i] == '0' else rank(b, i) + b.count('1')
    return [riffle_permutation_func(i) for i in range(8)]


def value_zero_in_lower_triangular(M):
    for i in range(1, len(M)):
        for j in range(1, i):
            if M[i][j] == 0:
                return True
    return False


def riffle_shuffle(n, seed, hash_func):
    perm = list(range(1, n + 1))
    M = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, i):
            M[i][j] = 0

    while value_zero_in_lower_triangular(M):
        s0 = []
        s1 = []
        for w in range(1, n + 1):
            b = hash_func(seed, w)
            if b:
                s0.append(perm[w - 1])
            else:
                s1.append(perm[w - 1])
        for i in s0:
            for j in s1:
                M[max(i, j)][min(i, j)] = 1
        perm = s0 + s1
        print(perm)

    return perm


def trace_trajectories(B):
    trajectories = [B[0]]
    for i in range(1, len(B)):
        pass
        # trajectoreis.append(inverted_riffle_permutation(B[i - 1], B[i]))

riffle_shuffle(8, 2, lambda x, y: (x + y) % 2)
