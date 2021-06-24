from vp_maps.persist import *

def version_check(ver):
	if (ver < 1 or ver > 1):
		return False
	else:
		return True

def get_high_version():
	return 1

def get_low_version():
	return 1

def write_int(ver, f, payload):
    f.writeInteger(payload)

def write_str(ver, f, payload):
    f.writeString(payload)

def write_Header(ver, f, payload):
	write_int(ver, f, payload.version)
	write_str(ver, f, payload.test_name)

def write_A(ver, f, payload):
	write_int(ver, f, payload.i1)
	write_str(ver, f, payload.s1)

def write_OuterA(ver, f, payload):
	write_int(ver, f, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_int(ver, f, k)
		write_A(ver, f, v)

def write_OuterB(ver, f, payload):
	write_int(ver, f, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_str(ver, f, k)
		write_A(ver, f, v)

def write_OuterC(ver, f, payload):
	write_int(ver, f, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_int(ver, f, k)
		write_str(ver, f, v)

def read_int(ver, f):
   t = f.readInteger()
   assert(t == 4)
   return f.readInteger()

def read_str(ver, f):
   t = f.readInteger()
   assert(t == 6)
   return f.readString()

def read_Header(ver, f):
	payload = Header()
	payload.version = read_int(ver, f)
	payload.test_name = read_str(ver, f)
	return payload

def read_A(ver, f):
	payload = A()
	payload.i1 = read_int(ver, f)
	payload.s1 = read_str(ver, f)
	return payload

def read_OuterA(ver, f):
	payload = OuterA()
	payload.lookup = {}
	count = read_int(ver, f)
	i = 0
	while (i < count):
		k = int()
		k = read_int(ver, f)
		t = A()
		t = read_A(ver, f)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_OuterB(ver, f):
	payload = OuterB()
	payload.lookup = {}
	count = read_int(ver, f)
	i = 0
	while (i < count):
		k = str()
		k = read_str(ver, f)
		t = A()
		t = read_A(ver, f)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_OuterC(ver, f):
	payload = OuterC()
	payload.lookup = {}
	count = read_int(ver, f)
	i = 0
	while (i < count):
		k = int()
		k = read_int(ver, f)
		t = str()
		t = read_str(ver, f)
		payload.lookup[k] = t
		i = i + 1

	return payload

