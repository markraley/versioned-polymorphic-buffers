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

class write_context:
    def __init__(self, ver = 1):
        self.stream = amf3.util.BufferedByteStream()
        self.encoder = amf3.Encoder(self.stream)
        self.encoder.string_references = False # disables string caching

        self.reorder_map = {}
        self.ver = ver
        self.set_version(ver)

        self.salt_map = {}
        self.salt_map["SaltShaker"] = SaltShaker(ver)
        self.salt_map["PepperShaker"] = PepperShaker(ver)

    def set_version(self, ver):
        self.ver = ver
        init_reorder_map(self.reorder_map, ver, 1)

class read_context:
    def __init__(self, test_name, ver = 1):
        self.istream = file_to_buffer(out_dir + test_name + file_ext)
        self.decoder = amf3.Decoder(self.istream)
        self.bytes_read = len(self.istream)
        print(test_name, len(self.istream), 'bytes read')
        self.reorder_map = {}
        self.ver = ver
        self.set_version(ver)

    def set_version(self, ver):
        self.ver = ver
        init_reorder_map(self.reorder_map, ver, 1)

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
        wc = write_context()

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[j] = A(j, 'A-' + str(j))

        write_Header(wc, self.h1)
        write_OuterA(wc, self.o1)

        out_file = out_dir + self.test_name + file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterA(rc)

        self.bytes_read = rc.bytes_read

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
        wc = write_context()

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[str(j)] = A(j, 'B-' + str(j))

        write_Header(wc, self.h1)
        write_OuterB(wc, self.o1)

        out_file = out_dir + self.test_name + file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterB(rc)

        self.bytes_read = rc.bytes_read

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
        self.o1 = OuterC()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterC()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[j] = 'C-' + str(j)

        write_Header(wc, self.h1)
        write_OuterC(wc, self.o1)

        out_file = out_dir + self.test_name + file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterC(rc)

        self.bytes_read = rc.bytes_read

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
# maps_D -

class Test_maps_D:
    def __init__(self):
        self.test_name = "maps_D"
        self.count = 10
        self.base = 50000

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterD()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterD()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[str(j)] = D1(j, 'D1-' + str(j))

        write_Header(wc, self.h1)
        write_OuterD(wc, self.o1)

        out_file = out_dir + self.test_name + file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterD(rc)

        self.bytes_read = rc.bytes_read

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)
        assert(len(self.o1.lookup) == len(self.o2.lookup))

        for k in self.o1.lookup.keys():
            assert(self.o1.lookup[k].i == self.o2.lookup[k].i)
            assert(self.o1.lookup[k].s == self.o2.lookup[k].s)

            assert(self.o1.lookup[k].apod.i1 == self.o2.lookup[k].apod.i1)
            assert(self.o1.lookup[k].apod.s1 == self.o2.lookup[k].apod.s1)

            assert(self.o1.lookup[k].aref.i1 == self.o2.lookup[k].aref.i1)
            assert(self.o1.lookup[k].aref.s1 == self.o2.lookup[k].aref.s1)

a = Test_maps_D()
a.serialize()
a.load()
a.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# maps_E -

class Test_maps_E:
    def __init__(self):
        self.test_name = "maps_E"
        self.count = 10
        self.base = 50000

        self.h1 = Header()  # initialized and then serialized
        self.o1 = Omlette()

        self.h2 = Header()  # deserialized and validated
        self.o2 = Omlette()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.lookup[j] = Egg(j, 'EGG-' + str(j))

        write_Header(wc, self.h1)
        write_Omlette(wc, self.o1)

        out_file = out_dir + self.test_name + file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_Omlette(rc)

        self.bytes_read = rc.bytes_read

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)

        assert(len(self.o1.lookup) == len(self.o2.lookup))

        for k in self.o1.lookup.keys():
            assert(self.o1.lookup[k].i1 == self.o2.lookup[k].i1)
            assert(self.o1.lookup[k].s1 == self.o2.lookup[k].s1)

e = Test_maps_E()
e.serialize()
e.load()
e.validate()
