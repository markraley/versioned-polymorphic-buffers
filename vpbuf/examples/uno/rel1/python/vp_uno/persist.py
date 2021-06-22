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
    def __init__(self, id = -1):
        self.id = id

class Value(Card):
    def __init__(self, id = 0, value = -1, color = "not set"):
        self.id = id
        self.value = value
        self.color = color

    def get_name(self):
        return self.color + ' ' + str(self.value)

class Deck:
    def __init__(self):
        self.cards = []

class Action(Card):
    def __init__(self):
        self.color = "not set"

    def get_name(self):
        return self.color + " " + self.name

class Skip(Action):
    def __init__(self, id = -1, color = "not set"):
        self.id = -1
        self.color = color
        self.name = "Skip"

class Reverse(Action):
    def __init__(self, id = -1, color = "not set"):
        self.id = -1
        self.color = color
        self.name = "Reverse"

class DrawTwo(Action):
    def __init__(self, id = -1, color = "not set"):
        self.id = -1
        self.color = color
        self.name = "DrawTwo"

# ------------------------------------------------------------------------------

from vp_uno.vp_uno import *

def save_deck(file_name, deck):
    stream = amf3.util.BufferedByteStream()
    e = amf3.Encoder(stream)
    e.string_references = False # disables string caching

    output_buffer = amf3.DataOutput(e)

    h = Header(get_high_version(), 'VP_UNO')
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
