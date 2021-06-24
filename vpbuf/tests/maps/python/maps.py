#!/usr/bin/python3

# Software released under the MIT license (see project root for license file)

from pyamf import amf3
from vp_maps.persist import *
from vp_maps.vp_maps import *

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

out_dir = "./out/"
file_ext = ".dat"

# ------------------------------------------------------------------------------
# maps_A -

class Test_maps_A:
    def __init__(self):
        self.test_name = "maps_A"
        self.count = 10
        self.base = 50000

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterA()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterA()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[j] = A(j, 'A-' + str(j))

        write_Header(1, e, self.h1)
        write_OuterA(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterA(1, decoder)

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)

        assert(len(self.o1.lookup) == len(self.o2.lookup))

        for k in self.o1.lookup.keys():
            assert(self.o1.lookup[k].i1 == self.o2.lookup[k].i1)
            assert(self.o1.lookup[k].s1 == self.o2.lookup[k].s1)

a = Test_maps_A()
a.serialize()
a.load()
a.validate()

# ------------------------------------------------------------------------------
# maps_B -

class Test_maps_B:
    def __init__(self):
        self.test_name = "maps_B"
        self.count = 10
        self.base = 50000

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterB()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterB()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[str(j)] = A(j, 'B-' + str(j))

        write_Header(1, e, self.h1)
        write_OuterB(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterB(1, decoder)

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)

        assert(len(self.o1.lookup) == len(self.o2.lookup))

        for k in self.o1.lookup.keys():
            assert(self.o1.lookup[k].i1 == self.o2.lookup[k].i1)
            assert(self.o1.lookup[k].s1 == self.o2.lookup[k].s1)

a = Test_maps_B()
a.serialize()
a.load()
a.validate()

# ------------------------------------------------------------------------------
# maps_C -

class Test_maps_C:
    def __init__(self):
        self.test_name = "maps_C"
        self.count = 10
        self.base = 50000

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterB()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterB()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[j] = 'C-' + str(j)

        write_Header(1, e, self.h1)
        write_OuterC(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterC(1, decoder)

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)
        assert(len(self.o1.lookup) == len(self.o2.lookup))

        for k in self.o1.lookup.keys():
            assert(self.o1.lookup[k] == self.o2.lookup[k])


a = Test_maps_C()
a.serialize()
a.load()
a.validate()

# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------

