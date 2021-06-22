#!/usr/bin/python3
# Software released under the MIT license (see project root for license file)

import sys
from pyamf import amf3
from vp_uno.persist import *
from vp_uno.vp_uno import *
from vp_uno.tools import *

import argparse

# ------------------------------------------------------------------------------

def main():
    # process args

    p = argparse.ArgumentParser()
    p.add_argument("deck_name")
    p.add_argument("count", nargs='?', default=1)

    args = p.parse_args()

    print('[vrange=',get_low_version(),'-',get_high_version(),
            ', python] DRAW ', args.count, ' cards', sep='')

    # load the specified deck

    deck = load_deck(args.deck_name)

    if (deck is None):
        exit(1)

    if (len(deck.cards) < int(args.count)):
        print('too few cards left')
    else:
        # modify the deck by removing cards

        print('card pop:', end='')
        for i in range(0, int(args.count)):
            c = deck.cards.pop()
            print(' ' + c.get_name(), end='')
        print()

        # write the modified deck back out

        save_deck(args.deck_name, deck)

        print('cards left', len(deck.cards))

if __name__ == '__main__':
    main()

# ------------------------------------------------------------------------------