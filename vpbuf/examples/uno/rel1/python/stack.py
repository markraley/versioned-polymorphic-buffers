#!/usr/bin/python3

# Software released under the MIT license (see project root for license file)

from pyamf import amf3
from vp_uno.persist import *
from vp_uno.vp_uno import *
from vp_uno.tools import *

import argparse

# ------------------------------------------------------------------------------

def build_poker_deck(card_count):
    deck = Deck()
    build_arr = []

    count = 0
    for c in color_arr:

        for k in range(0,2):
            build_arr.append(Skip(++count, c))
            build_arr.append(Reverse(++count, c))
            build_arr.append(DrawTwo(++count, c))

        build_arr.append(Value(++count, 0, c))

        for k in range(1,10):
            build_arr.append(Value(++count, k, c))
            build_arr.append(Value(++count, k, c))

    deck.cards = build_arr[len(build_arr) - card_count:]

    return deck

# ------------------------------------------------------------------------------

def main():
    # process args

    p = argparse.ArgumentParser()
    p.add_argument("deck_name")
    p.add_argument("count", nargs='?', default=3)

    args = p.parse_args()

    print('[vrange=',get_low_version(),'-',get_high_version(),
            ', python] STACK ', args.count, ' cards', sep='')

    deck = build_poker_deck(int(args.count))

    save_deck(args.deck_name, deck)

if __name__ == '__main__':
    main()

# ------------------------------------------------------------------------------