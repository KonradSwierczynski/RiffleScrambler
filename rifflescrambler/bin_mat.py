#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 21 16:41:29 2018

@author: konrad
"""


# [a, b, c, d]
#  0  1  2  3
 

# Converts number to string of binary representation of a given length
def num_to_bin_str(num: int, length: int) -> str:
    b = bin(num)[2:]
    return '0' * (length - len(b)) + b if len(b) < length else b[-length:]


# Class for operating on binary representation matrix for given list of numbers
class BinMatrix:
    def __init__(self, number_list, binary_lenght):
        self.b_lenght = binary_lenght
        self.list = number_list

    def get_col_as_num(self, col_index):
        return self.list[col_index]

    def get_row_as_num(self, row_index):
        if row_index >= self.b_lenght or row_index < 0:
            raise KeyError

        row = ""
        for num in self.list:
            print(num_to_bin_str(num, self.b_lenght))
            row += num_to_bin_str(num, self.b_lenght)[self.b_lenght - row_index - 1]
        print(row)
        return int(row, 2)

# Example
# For given permutation perm = [0, 1, 2, ... , 15]
# Binary representation is as follows
# Colums represents numbers in given permutation col_{i} == perm[i]
# Rows
# Col:   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
# Row 0: 0  0  0  0  0  0  0  0  1  1  1  1  1  1  1  1
# Row 1: 0  0  0  0  1  1  1  1  0  0  0  0  1  1  1  1
# Row 2: 0  0  1  1  0  0  1  1  0  0  1  1  0  0  1  1
# Row 3: 0  1  0  1  0  1  0  1  0  1  0  1  0  1  0  1
