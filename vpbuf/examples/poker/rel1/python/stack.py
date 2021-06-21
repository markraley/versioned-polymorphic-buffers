#!/usr/bin/python3

# Software released under the MIT license (see project root for license file)

from pyamf import amf3
from vp_poker.persist import *
from vp_poker.vp_poker import *
from vp_poker.tools import *

import argparse

# ------------------------------------------------------------------------------

def build_poker_deck(card_count):
    deck = Deck()

    count = 0
    for s in suit_arr:
        for r in rank_arr:
            count += 1
            if (count > card_count):
                return deck;
            deck.cards.append(Card(r + " of " + s, count))

    return deck

# ------------------------------------------------------------------------------

def main():
    # process args

    p = argparse.ArgumentParser()
    p.add_argument("deck_name")
    p.add_argument("count", nargs='?', default=3)

    args = p.parse_args()

    print('[vrange=',get_low_version(),':',get_high_version(),
            ', python] STACK ', args.count, ' cards', sep='')

    deck = build_poker_deck(int(args.count))

    save_deck(args.deck_name, deck)

if __name__ == '__main__':
    main()

# ------------------------------------------------------------------------------