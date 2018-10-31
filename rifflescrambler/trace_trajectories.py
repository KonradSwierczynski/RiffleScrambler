from typing import List
from bin_mat import BinMatrix
from riffle_permutation import inverted_riffle_permutation


# For given permutation of length 2^g generates g numbers (trajectories) of length 2^g
def trace_trajectories(B: List[int]) -> List[int]:
    mat = BinMatrix(B)
    trajectories = [mat.get_row_as_num(0)]
    for i in range(1, len(B)):
        trajectories.append(inverted_riffle_permutation())

    pass


def trace_trajectories_(B):
    trajectories = [B[0]]
    for i in range(1, len(B)):
        trajectories.append(inverted_riffle_permutation(trajectories[i - 1], B[i]))
    return trajectories
