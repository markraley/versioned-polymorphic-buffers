#!/usr/bin/python3

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

    deck = build_poker_deck(int(args.count))

    bytes_written = save_deck(args.deck_name, deck)

    print('card count', len(deck.cards))
    print(bytes_written, 'bytes written')

if __name__ == '__main__':
    main()

# ------------------------------------------------------------------------------