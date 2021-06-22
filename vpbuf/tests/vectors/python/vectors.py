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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(A(j, 'A-' + str(j)))

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = -99
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(A(j, 'A-' + str(j)))

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = 101
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append('C-' + str(j))

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = 101
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append('D-' + str(j))

        write_Header(1, e, self.h1)
        write_OuterD(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterD(1, decoder)

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = 1121
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(j)

        write_Header(1, e, self.h1)
        write_OuterE(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterE(1, decoder)

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = 1121
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(j)

        write_Header(1, e, self.h1)
        write_OuterF(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterF(1, decoder)

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
        stream = amf3.util.BufferedByteStream()
        e = amf3.Encoder(stream)
        e.string_references = False # disables string caching

        self.h1.version = 1
        self.h1.test_name = self.test_name

        for i in range(0, self.count):
            j = self.base + i
            self.o1.v.append(Derived1(j, 'D1-' + str(j)))
            self.o1.v.append(Derived2(j, 'D2-' + str(j)))

        write_Header(1, e, self.h1)
        write_OuterG(1, e, self.o1)

        self.bytes_written = buffer_to_file(out_dir + self.test_name + file_ext, e)

        print(self.test_name, self.bytes_written, 'bytes written')

    # deserialize the data structures under test

    def load(self):
        istream = file_to_buffer(out_dir + self.test_name + file_ext)
        decoder = amf3.Decoder(istream)

        self.bytes_read = len(istream)
        print(self.test_name, len(istream), 'bytes read')

        self.h2 = read_Header(1, decoder)
        self.o2 = read_OuterG(1, decoder)

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

