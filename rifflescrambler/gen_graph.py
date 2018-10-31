from typing import List
from bin_mat import BinMatrix
from riffle_permutation import *


# For given list of 2^g numbers of length g generates graph (2^g)-Double-Riffle-Grapph
def gen_graph(g: int, perm: List[int]) -> List[List[int]]:
    print("\tCreating new Matrix...")
    perm_matrix = BinMatrix(perm, g)
    print("\tCreated. Genetrating rows...")
    B = [perm_matrix.get_row_as_num(i) for i in range(g)]
    print("\tRows generated.")
    edges = [[[] for _ in range(2**g)] for _ in range(2*g)]

    for row in range(g):
        for i, v in enumerate(riffle_permutation(B[row], 2**g)):
            edges[row][v].append(i)
            edges[2 * g - row - 1][i].append(v)
        for i, v in enumerate(complement_riffle_permutation(B[row], 2**g)):
            edges[row][v].append(i)
            edges[2 * g - row - 1][i].append(v)

    return edges
