#!/bin/pythot n

import argparse
from riffle_scrambler import riffle_scrambler

parser = argparse.ArgumentParser(description='Riffle Scrambler')
parser.add_argument('password', metavar='Password', type=str, help="Password to hash")
parser.add_argument('salt', metavar='Salt', type=str, help="Salt for given password")
parser.add_argument('--width', '-w', help='Width of grapth', type=int, default=12, required=False)
parser.add_argument('--depth', '-d', help='How many time grapth should be stacked', type=int, default=2, required=False)

args = parser.parse_args()

print(riffle_scrambler(args.salt.encode(), args.width, args.password.encode(), args.depth).decode())
