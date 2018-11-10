from riffle_shuffle import riffle_shuffle, faster_riffle_shuffle
from gen_graph import gen_graph
import hashlib

def hash_func(*args):
    val = b''
    for x in args:
        val += x

    return hashlib.sha1(val).hexdigest().encode()

def riffle_scrambler(salt, g, x, depth):
    print("Generating permutation...")
    # perm = riffle_shuffle(2 ** g, salt, hash_func)
    perm = faster_riffle_shuffle(2 ** g, salt)
    print("Generated Permutation")
    print("Generating graph...")
    edges = gen_graph(g, perm)
    print("Generated graph")

    return evaluate_graph(edges, g, x, depth, hash_func)


def evaluate_graph(edges, g, x, depth, hash_func):
    element = hash_func(x)
    first_row = [element]
    for _ in range(2**g - 1):
        element = hash_func(element)
        first_row.append(element)

    for r in range(depth):
        if r % 5 == 0:
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





if __name__ == '__main__':
    import cProfile
    cProfile.run("print(riffle_scrambler(b'salt', 14, b'test', 10))")
    # print(gen_graph(2, [3, 1, 0, 2]))
    # salt 14 test 10 fae26723f07b3e53ef88b9dda3a6706bc733d948

