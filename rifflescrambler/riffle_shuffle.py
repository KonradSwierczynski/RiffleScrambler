from typing import List, Callable


# Checks for zero in lower triangular of given matrix
def is_zero_in_lower_triangular(matrix: List[List[int]]) -> bool:
    for i in range(0, len(matrix)):
        for j in range(1, i):
            if matrix[i][j] == 0:
                return True
    return False


# Calculates pseudorandom permutation for given salt using given hash function
# Uses Riffle Shuffle permutation algorithm
def riffle_shuffle(length: int, salt: int, hash_func: Callable[[int, int], int]) -> List[int]:
    permutation = list(range(0, length ))
    M = [[0] * length for _ in range(length)]
    loops = 0
    while is_zero_in_lower_triangular(M):
        loops += 1
        stack_0 = []
        stack_1 = []
        for w in range(length):
            b = hash_func(salt, w)
            if b:
                stack_0.append(permutation[w])
            else:
                stack_1.append(permutation[w])
        for i in stack_0:
            for j in stack_1:
                M[max(i, j)][min(i, j)] = 1
        permutation = stack_0 + stack_1
    return permutation


# Returns 0 or 1 randomly, dummy simulation of hash function
# Not secure
def random_bit(*args, **kwargs) -> int:
    import random
    return random.randint(0, 1)