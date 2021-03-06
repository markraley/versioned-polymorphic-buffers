#!/usr/bin/python3

# Software released under the MIT license (see project root for license file)

from pyamf import amf3
from vp_vectors.persist import *
from vp_vectors.vp_vectors import *

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
# vectors_A - test vector of pointer to struct

class Test_vector_A:
    def __init__(self):
        self.test_name = "vectors_A"
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
            self.o1.v.append(A(j, 'A-' + str(j)))

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
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i].i1 == self.o2.v[i].i1)
            assert(self.o1.v[i].s1 == self.o2.v[i].s1)


a = Test_vector_A()
a.serialize()
a.load()
a.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# vectors_B - test vector of struct

class Test_vector_B:
    def __init__(self):
        self.test_name = "vectors_B"
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
            self.o1.v.append(A(j, 'A-' + str(j)))

        write_Header(wc, self.h1)
        write_OuterB(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
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
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i].i1 == self.o2.v[i].i1)
            assert(self.o1.v[i].s1 == self.o2.v[i].s1)


b = Test_vector_B()
b.serialize()
b.load()
b.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# vectors_C - test vector of string

class Test_vector_C:
    def __init__(self):
        self.test_name = "vectors_C"
        self.count = 13
        self.base = 113

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterC()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterC()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = 101
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append('C-' + str(j))

        write_Header(wc, self.h1)
        write_OuterC(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
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
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i] == self.o2.v[i])


c = Test_vector_C()
c.serialize()
c.load()
c.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# vectors_D - test vector of pointer to string

class Test_vector_D:
    def __init__(self):
        self.test_name = "vectors_D"
        self.count = 13
        self.base = 113

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterD()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterD()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = 101
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append('D-' + str(j))

        write_Header(wc, self.h1)
        write_OuterD(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
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
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i] == self.o2.v[i])


d = Test_vector_D()
d.serialize()
d.load()
d.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# vectors_E - test vector of integer

class Test_vector_E:
    def __init__(self):
        self.test_name = "vectors_E"
        self.count = 76
        self.base = 112

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterE()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterE()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = 1121
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(j)

        write_Header(wc, self.h1)
        write_OuterE(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterE(rc)

        self.bytes_read = rc.bytes_read

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i] == self.o2.v[i])


e = Test_vector_E()
e.serialize()
e.load()
e.validate()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# vectors_E - test vector pointer to integer

class Test_vector_F:
    def __init__(self):
        self.test_name = "vectors_F"
        self.count = 76
        self.base = 112

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterE()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterE()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = 1121
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(j)

        write_Header(wc, self.h1)
        write_OuterF(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterF(rc)

        self.bytes_read = rc.bytes_read

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i] == self.o2.v[i])


f = Test_vector_F()
f.serialize()
f.load()
f.validate()

# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# vectors_G - test vector of pointer to polymorphic class

class Test_vector_G:
    def __init__(self):
        self.test_name = "vectors_G"
        self.count = 17
        self.base = 500

        self.h1 = Header()  # initialized and then serialized
        self.o1 = OuterG()

        self.h2 = Header()  # deserialized and validated
        self.o2 = OuterG()

        self.bytes_read = 0
        self.bytes_written = 0

    # initialize the data structures under test and serialize

    def serialize(self):
        wc = write_context()

        self.h1.version = 1
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(Derived1(j, 'D1-' + str(j)))
            self.o1.v.append(Derived2(j, 'D2-' + str(j)))

        write_Header(wc, self.h1)
        write_OuterG(wc, self.o1)

        out_file = out_dir+self.test_name+file_ext
        self.bytes_written = buffer_to_file(out_file, wc.encoder)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        rc = read_context(self.test_name)

        self.h2 = read_Header(rc)
        self.o2 = read_OuterG(rc)

        self.bytes_read = rc.bytes_read

    # compare the serialized and deserialized data structures against each other

    def validate(self):
        assert(self.h1.version == self.h2.version)
        assert(self.h1.test_name == self.h2.test_name)
        assert(self.bytes_read == self.bytes_written)
        assert(len(self.o1.v) == len(self.o2.v))

        for i in range(0, len(self.o1.v)):
            assert(self.o1.v[i].i1 == self.o2.v[i].i1)
            assert(self.o1.v[i].s1 == self.o2.v[i].s1)


g = Test_vector_G()
g.serialize()
g.load()
g.validate()

# ------------------------------------------------------------------------------

