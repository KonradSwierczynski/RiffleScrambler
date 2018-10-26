from typing import List
from bin_mat import BinMatrix
from riffle_permutation import *


# For given list of g numbers of length 2^g generates grapg (2^g)-Double-Riffle-Grapph
def gen_graph(g: int, perm: List[int]) -> List[List[int]]:
    perm_matrix = BinMatrix(perm, g)
    B = [perm_matrix.get_row_as_num(i) for i in range(g)]
    B = B + B[:;-1]
    edges = [[[] for _ in range(2**g)] for _ in range(2*g)]

    for row in range(g):
        for i, v in enumerate(riffle_permutation(B[row])):
            edges[row][v].append(i)
        for i, v in enumerate(complement_riffle_permutation(B[row])):
            edges[row][v].append(i)

    for row in range(g):
        for i, v in enumerate(riffle_permutation(B[row])):
            edges[row][v].append(i)
        for i, v in enumerate(complement_riffle_permutation(B[row])):
            edges[row][v].append(i)

    return edges