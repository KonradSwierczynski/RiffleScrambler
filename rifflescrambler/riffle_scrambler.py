from riffle_shuffle import riffle_shuffle, random_bit
from gen_graph import gen_graph
import hashlib


def riffle_scrambler(salt, g, x, depth, hash_func):
    print("Generating permutation...")
    perm = riffle_shuffle(2 ** g, salt, hash_func)
    print("Generated Permutation")
    edges = gen_graph(g, perm)

    element = hash_func(x)
    first_row = [element]
    for _ in range(2**g - 1):
        element = hash_func(element)
        first_row.append(element)

    for r in range(depth):
        if r % 10 == 0:
            print("Depth: ", r)
        for j in range(2 * g):
            second_row = [0 for _ in range(2 ** g)]

            second_row[0] = hash_func(first_row[2 ** g - 1])
            for v in edges[j][0]:
                second_row[0] = hash_func(second_row[0], first_row[v])

            for i in range(1, 2 ** g):
                second_row[i] = hash_func(second_row[i - 1])
                for v in edges[j][i]:
                    second_row[i] = hash_func(second_row[i], first_row[v])
            first_row = second_row

    return second_row[-1]


def hash_func(*args):
    val = b''
    for x in args:
        val += x

    return hashlib.sha1(val).hexdigest().encode()


