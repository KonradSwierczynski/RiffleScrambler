from typing import List, Callable
import hashlib


# Checks for zero in lower triangular of given matrix
def is_zero_in_lower_triangular(matrix: List[List[int]]) -> bool:
    for i in range(0, len(matrix)):
        for j in range(1, i):
            if matrix[i][j] == 0:
                return True
    return False


# Calculates pseudorandom permutation for given salt using given hash function
# Uses Riffle Shuffle permutation algorithm
def riffle_shuffle(length: bytes, salt: int, hash_func: Callable[[bytes, bytes], bytes]) -> List[int]:
    permutation = list(range(0, length))
    M = [[0] * length for _ in range(length)]
    loops = 0
    while is_zero_in_lower_triangular(M):
        loops += 1
        stack_0 = []
        stack_1 = []
        for w in range(length):
            b = bytes_last_bit(hash_func(salt, int_to_bytes(w), int_to_bytes(loops)))
            if b:
                stack_0.append(permutation[w])
            else:
                stack_1.append(permutation[w])
        for i in stack_0:
            for j in stack_1:
                M[max(i, j)][min(i, j)] = 1
        permutation = stack_0 + stack_1
    return permutation




class PermElement:
    def __init__(self, id):
        self._id = id
        self._value_b = 0

    def get_bit_b(self, index):
        return (self._value_b >> index) & 1

    def set_bit_b(self, index, value=True):
        if value:
            self._value_b |= 1 << index

    def get_id(self):
        return self._id

    def get_value_b(self):
        return self._value_b


class PRNG:
    def __init__(self, salt: bytes):
        self._position = 0
        self._calculate_next_buffor(salt)

    def get_next_bit(self):
        if self._position == len(self._buffor):
            self._position = 0
            self._calculate_next_buffor()
        next_bit = self._buffor[self._position] == '1'
        self._position += 1
        return next_bit

    def _calculate_next_buffor(self, salt=None):
        from bitstring import Bits
        if salt:
            self._hash = hashlib.sha1(salt)
        else:
            self._hash.update(self._hash.digest())
        self._buffor = Bits(f'0x{self._hash.hexdigest()}').bin


def faster_riffle_shuffle(length: int, salt: bytes) -> List[int]:
    permutation = [PermElement(i) for i in range(length)]
    prng = PRNG(salt)
    good_permutation = False
    iterations = 0
    while not good_permutation:
        num_of_ones = 0
        for perm_elem in permutation:
            new_bit = prng.get_next_bit()
            num_of_ones += new_bit
            perm_elem.set_bit_b(iterations, new_bit)
            # perm_elem.add_bit(new_bit)

        new_perm = [None] * length
        last_index = 0
        last_zero_index = num_of_ones
        for i in range(length):
            if permutation[i].get_bit_b(iterations):
                new_perm[last_index] = permutation[i]
                last_index += 1
            else:
                new_perm[last_zero_index] = permutation[i]
                last_zero_index += 1
            # if permutation[i].get_first_bit():
            #     new_perm[last_index] = permutation[i]
            #     last_index += 1
            # else:
            #     new_perm[last_zero_index] = permutation[i]
            #     last_zero_index += 1

        permutation = new_perm
        good_permutation = True
        for i in range(1, length):
            if permutation[i].get_value_b() == permutation[i - 1].get_value_b():
                good_permutation = False
                break
            # if permutation[i].get_value() == permutation[i - 1].get_value():
            #     good_permutation = False
            #     break
        iterations += 1
    print(iterations)
    return [perm_elem.get_id() for perm_elem in permutation]

if __name__ == '__main__':
    import cProfile

    cProfile.run("print(faster_riffle_shuffle(2 ** 18, b'test'))")



def int_to_bytes(x):
    return x.to_bytes((x.bit_length() + 7) // 8, 'big')


def hexdigest_last_bit(hexdigest):
    return int(bin(int(hexdigest[-1], 16))[-1], 2)


def bytes_last_bit(bytes):
    from bitstring import BitArray
    b_arr = BitArray(bytes)
    return int(b_arr.bin[-1], 2)

# Returns 0 or 1 randomly, dummy simulation of hash function
# Not secure
def random_bit(*args, **kwargs) -> int:
    import random
    return random.randint(0, 1)
