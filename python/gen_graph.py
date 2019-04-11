from typing import List
from bin_mat import BinMatrix
from riffle_permutation import riffle_permutation, complement_riffle_permutation


# For given list of 2^g numbers of length g generates graph (2^g)-Double-Riffle-Grapph
def gen_graph(g: int, perm: List[int]) -> List[List[int]]:
    perm_matrix = BinMatrix(perm, g)
    B = [perm_matrix.get_row_as_num(i) for i in range(g)]
    edges = [[[] for _ in range(2**g)] for _ in range(2*g)]

    for row in range(g):
        for i, v in enumerate(riffle_permutation(B[row], 2**g)):
            edges[row][v].append(i)
            edges[2 * g - row - 1][i].append(v)
        for i, v in enumerate(complement_riffle_permutation(B[row], 2**g)):
            edges[row][v].append(i)
            edges[2 * g - row - 1][i].append(v)

    return edges
