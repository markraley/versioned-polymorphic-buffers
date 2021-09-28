from vp_vectors.persist import *

def version_check(ver):
	if (ver < 1 or ver > 1):
		return False
	else:
		return True

def get_high_version():
	return 1

def get_low_version():
	return 1

def init_reorder_map(map, ver):
	map['Header'] = get_rlist_Header(ver)

vlist_Header = [
	( 1, 0 ),
	( 1, 0 )
]

def get_vlist_Header(ver):
	c, v = 0, []
	for p in vlist_Header:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Header = [
	( 1, 0, 'h1', flip )
]

def get_rlist_Header(ver):
	for p in rlist_Header:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			return [p[2], p[3](get_vlist_Header(ver))]
	return None

def write_int(ver, wc, payload):
    wc.encoder.writeInteger(payload) # amf3

def write_str(ver, wc, payload):
    wc.encoder.writeString(payload) # amf3

def write_Header(ver, f, payload):
	for i in f.reorder_map['Header'][1]():
		if i==0:
			write_int(ver, f, payload.version)
		elif i==1:
			write_str(ver, f, payload.test_name)

def write_A(ver, f, payload):
	write_int(ver, f, payload.i1)
	write_str(ver, f, payload.s1)

def write_OuterA(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_A(ver, f, payload.v[i])
		i = i + 1

def write_OuterB(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_A(ver, f, payload.v[i])
		i = i + 1

def write_OuterC(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_str(ver, f, payload.v[i])
		i = i + 1

def write_OuterD(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_str(ver, f, payload.v[i])
		i = i + 1

def write_OuterE(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_int(ver, f, payload.v[i])
		i = i + 1

def write_OuterF(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_int(ver, f, payload.v[i])
		i = i + 1

def write_Base(ver, f, payload):
	c = type(payload).__name__
	if (c == "Derived1"):
		write_int(ver, f,0)
		write_Derived1(ver, f, payload)
	if (c == "Derived2"):
		write_int(ver, f,1)
		write_Derived2(ver, f, payload)


def write_Derived1(ver, f, payload):
	write_int(ver, f, payload.i1)
	write_str(ver, f, payload.s1)

def write_Derived2(ver, f, payload):
	write_int(ver, f, payload.i1)
	write_str(ver, f, payload.s1)

def write_OuterG(ver, f, payload):
	count = len(payload.v)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_Base(ver, f, payload.v[i])
		i = i + 1

def read_int(ver, rc):
   t = rc.decoder.readInteger() # amf3
   assert(t == 4)
   return rc.decoder.readInteger()

def read_str(ver, rc):
   t = rc.decoder.readInteger() # amf3
   assert(t == 6)
   return rc.decoder.readString()

def read_Header(ver, f):
	payload = Header()
	for i in f.reorder_map['Header'][1]():
		if i==0:
			payload.version = read_int(ver, f)
		elif i==1:
			payload.test_name = read_str(ver, f)
	return payload

def read_A(ver, f):
	payload = A()
	payload.i1 = read_int(ver, f)
	payload.s1 = read_str(ver, f)
	return payload

def read_OuterA(ver, f):
	payload = OuterA()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_A(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterB(ver, f):
	payload = OuterB()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_A(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterC(ver, f):
	payload = OuterC()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_str(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterD(ver, f):
	payload = OuterD()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_str(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterE(ver, f):
	payload = OuterE()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_int(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterF(ver, f):
	payload = OuterF()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_int(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

def read_Base(ver, f):
	t = read_int(ver, f)
	if (t == 0):
		payload = read_Derived1(ver, f)
	if (t == 1):
		payload = read_Derived2(ver, f)
	return payload

def read_Derived1(ver, f):
	payload = Derived1()
	payload.i1 = read_int(ver, f)
	payload.s1 = read_str(ver, f)
	return payload

def read_Derived2(ver, f):
	payload = Derived2()
	payload.i1 = read_int(ver, f)
	payload.s1 = read_str(ver, f)
	return payload

def read_OuterG(ver, f):
	payload = OuterG()
	payload.v = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_Base(ver, f)
		payload.v.append(t)
		i = i + 1
	return payload

