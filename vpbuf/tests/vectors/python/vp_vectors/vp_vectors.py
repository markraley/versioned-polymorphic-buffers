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
