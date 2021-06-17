#!/usr/bin/python3

from pyamf import amf3
from vp_poker.persist import *
from vp_poker.vp_poker import *
from vp_poker.tools import *

import argparse

# ------------------------------------------------------------------------------

def main():
    # process args

    p = argparse.ArgumentParser()
    p.add_argument("deck_name")
    p.add_argument("count", nargs='?', default=1)

    args = p.parse_args()

    # load the specified deck

    deck = load_deck(args.deck_name)

    if (deck is None):
        exit(1)

    if (len(deck.cards) < int(args.count)):
        print('too few cards left')
    else:
        # modify the deck by removing cards

        for i in range(0, int(args.count)):
            c = deck.cards.pop()
            print('draw:', c.get_name())

        # write the modified deck back out

        save_deck(args.deck_name, deck)

if __name__ == '__main__':
    main()

# ------------------------------------------------------------------------------