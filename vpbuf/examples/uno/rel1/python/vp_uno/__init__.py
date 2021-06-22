from pyamf import amf3

def write_int(ver, f, payload):
    f.writeInteger(payload)

def write_str(ver, f, payload):
    f.writeString(payload)
