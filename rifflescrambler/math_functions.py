from bin_mat import BinMatrix
from riffle_permutation import riffle_permutation, inverted_riffle_permutation


def trace_trajectories(B):
    mat = BinMatrix(B)
    trajectories = [mat.get_row_as_num(0)]
    for i in range(1, len(B)):
        trajectories.append(inverted_riffle_permutation())

    pass


def trace_trajectories_(B):
    trajectories = [B[0]]
    for i in range(1, len(B)):
        print(i, B[i-1], B[i], inverted_riffle_permutation(B[i - 1], B[i]), sep=" : ")
        trajectories.append(inverted_riffle_permutation(trajectories[i - 1], B[i]))
    return trajectories

# riffle_shuffle(8, 2, lambda x, y: (x + y) % 2)
