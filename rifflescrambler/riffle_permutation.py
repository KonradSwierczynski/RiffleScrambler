from typing import List


# Rank on binary word B (b_0, b_1,...,b_{n-1}
# Count number of occurrences of bit B[index] in position before index
def rank(binary_word: str, index: int) -> int:
    return binary_word[:index].count(binary_word[index])


# Converts number to string of the given length binary form
def num_to_bin_str(num: int, length: int) -> str:
    bin_str = bin(num)[2:]
    return '0' * (length - len(bin_str)) + bin_str if len(bin_str) < length else bin_str[-length:]


# Calculates Riffle Permutation value for given binary word at given index
def riffle_permutation_value(binary_word: str, index: int) -> int:
    return rank(binary_word, index) if binary_word[index] == '0' else rank(binary_word, index) + binary_word.count('0')


# Calculates Riffle Permutation for given number B for given binary length
# Riffle Permutation example:
# 11100100 -> [4, 5, 6, 0, 1, 7, 2, 3]
def riffle_permutation(B: int, length: int) -> List[int]:
    binary_form = num_to_bin_str(B, length)
    return [riffle_permutation_value(binary_form, i) for i in range(length)]


# Calculates index of given value in Riffle Permutation indced by given number B
def inverted_riffle_permutation(B: int, length: int, searched_value: int) -> int:
    perm = riffle_permutation(B, length)
    return perm.index(searched_value)
