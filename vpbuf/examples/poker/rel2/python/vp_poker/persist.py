# Software released under the MIT license (see project root for license file)

from pyamf import amf3

# ------------------------------------------------------------------------------

suit_arr = [ 'Diamonds', 'Clubs', 'Hearts', 'Spades' ]
rank_arr = [ 'Ace',   'Two',   'Three', 'Four',
             'Five',  'Six',   'Seven',
             'Eight', 'Nine',  'Ten',
             'Jack',  'Queen', 'King' ]

class Header():
    def __init__(self, version = 1, tag = "not set"):
        self.version = version
        self.tag = tag

class Card:
    def __init__(self, name = "", id = -1):
        self.name = name
        self.id = id

    def get_name(self):
        i = self.id - 1
        return rank_arr[i % len(rank_arr)] + ' of ' + suit_arr[i // len(rank_arr)]

class Deck:
    def __init__(self):
        self.cards = []

# ------------------------------------------------------------------------------

from vp_poker.vp_poker import *

def save_deck(file_name, deck):
    stream = amf3.util.BufferedByteStream()
    e = amf3.Encoder(stream)
    output_buffer = amf3.DataOutput(e)

    h = Header(get_high_version(), 'VP_POKER')
    write_Header(1, e, h) # header version is always 1

    write_Deck(get_high_version(), e, deck)

    f = open(file_name, "wb")
    bytes = output_buffer.stream.getvalue()
    f.write(bytes)
    f.close()

    print('write: ', file_name,
            ', version=', get_high_version(), sep='', end='')
    print(', cards=', len(deck.cards), sep='', end='')
    print(', bytes=', len(bytes), sep='')

    return(len(bytes))

# ------------------------------------------------------------------------------

def load_deck(file_name):
    f_in = open(file_name, "rb")
    istream = amf3.util.BufferedByteStream(f_in)
    bytes_read = len(istream)

    decoder = amf3.Decoder(istream)
    header = read_Header(1, decoder)

    if (not version_check(header.version)):
        print('version test failed')
        return None

    deck = read_Deck(header.version, decoder)

    f_in.close()

    print('read: ', file_name,
            ', version=', header.version, sep='', end='')
    print(', cards=', len(deck.cards), sep='', end='')
    print(', bytes=', bytes_read, sep='')

    return(deck)

# ------------------------------------------------------------------------------
