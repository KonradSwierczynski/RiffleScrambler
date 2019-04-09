from typing import List


# Rank on binary word B (b_0, b_1,...,b_{n-1}
# Count number of occurrences of bit B[index] in position before index
zeros = 0
ones = 0
total_zeros = 0
def rank(binary_word: str, index: int) -> int:
    global zeros
    global ones
    if binary_word[index] == '1':
        ones += 1
        return ones - 1
    else:
        zeros += 1
        return zeros - 1


# Converts number to string of the given length binary form
def num_to_bin_str(num: int, length: int) -> str:
    bin_str = bin(num)[2:]
    return '0' * (length - len(bin_str)) + bin_str if len(bin_str) < length else bin_str[-length:]


# Calculates Riffle Permutation value for given binary word at given index
def riffle_permutation_value(binary_word: str, index: int) -> int:
    return rank(binary_word, index) if binary_word[index] == '0' else rank(binary_word, index) + total_zeros


# Prepare cache value to run riffle permutation
def zero_counters(text: str):
    global zeros
    global ones
    global total_zeros
    zeros = 0
    ones = 0
    total_zeros = text.count('0')


# Calculates Riffle Permutation for given number B for given binary length
# Riffle Permutation example:
# 11100100 -> [4, 5, 6, 0, 1, 7, 2, 3]
def riffle_permutation(B: int, length: int) -> List[int]:
    binary_form = num_to_bin_str(B, length)
    zero_counters(binary_form)
    return [riffle_permutation_value(binary_form, i) for i in range(length)]


# Calculates Riffle Permutation for complement of given number B in given lenght
def complement_riffle_permutation(B: int, length: int) -> List[int]:
    binary_form = num_to_bin_str(B, length)
    binary_form = binary_complement(binary_form)
    zero_counters(binary_form)
    return [riffle_permutation_value(binary_form, i) for i in range(length)]


# Calculates complement for given string containing zeros and ones
# by switching '0' to '1' and '1' to '0'
def binary_complement(binary_string: str) -> str:
    return binary_string.replace('0', 'x').replace('1', '0').replace('x', '1')



def inverted(perm: List[int], val: int) -> int:
    return perm.index(val)


# Calculates index of given value in Riffle Permutation indced by given number B
def inverted_riffle_permutation(B: int, length: int, searched_value: int) -> int:
    perm = riffle_permutation(B, length)
    return perm.index(searched_value)

