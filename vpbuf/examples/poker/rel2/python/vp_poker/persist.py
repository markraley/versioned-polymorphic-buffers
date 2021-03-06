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
        return (rank_arr[i % len(rank_arr)]
                    + ' of ' + suit_arr[i // len(rank_arr)])

class Deck:
    def __init__(self):
        self.cards = []

# ------------------------------------------------------------------------------

def buffer_to_file(file_name, encoder):
    output_buffer = amf3.DataOutput(encoder)
    f = open(file_name, "wb")
    bytes = output_buffer.stream.getvalue()
    f.write(bytes)
    f.close()
    return len(bytes)

def file_to_buffer(file_name):
    f_in = open(file_name, "rb")
    istream = amf3.util.BufferedByteStream(f_in)
    f_in.close()
    return istream

# ------------------------------------------------------------------------------

class write_context:
    def __init__(self, ver = 1):
        self.stream = amf3.util.BufferedByteStream()
        self.encoder = amf3.Encoder(self.stream)
        self.encoder.string_references = False # disables string caching
        self.reorder_map = {}
        self.ver = ver
        self.set_version(ver)

    def set_version(self, ver):
        self.ver = ver

class read_context:
    def __init__(self, file_name, ver = 1):
        self.istream = file_to_buffer(file_name)
        self.decoder = amf3.Decoder(self.istream)
        self.bytes_read = len(self.istream)
        print(file_name, len(self.istream), 'bytes read')
        self.reorder_map = {}
        self.ver = ver
        self.set_version(ver)

    def set_version(self, ver):
        self.ver = ver

# ------------------------------------------------------------------------------

from vp_poker.vp_poker import *

def save_deck(file_name, deck):
    wc = write_context(1) # header version is always 1

    h = Header(get_high_version(), 'VP_POKER')
    write_Header(wc, h)

    wc.set_version(get_high_version())
    write_Deck(wc, deck)

    bytes_written = buffer_to_file(file_name, wc.encoder)

    print('write: ', file_name,
            ', version=', get_high_version(), sep='', end='')
    print(', cards=', len(deck.cards), sep='', end='')
    print(', bytes=', bytes_written, sep='')

    return(bytes_written)

# ------------------------------------------------------------------------------

def load_deck(file_name):
    rc = read_context(file_name)

    header = read_Header(rc)

    if (not version_check(header.version)):
        print('version test failed')
        return None

    rc.set_version(header.version)
    deck = read_Deck(rc)

    bytes_read = rc.bytes_read

    print('read: ', file_name,
            ', version=', header.version, sep='', end='')
    print(', cards=', len(deck.cards), sep='', end='')
    print(', bytes=', bytes_read, sep='')

    return(deck)

# ------------------------------------------------------------------------------
