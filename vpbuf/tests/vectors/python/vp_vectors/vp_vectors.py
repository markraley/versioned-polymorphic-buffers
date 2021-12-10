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

def init_reorder_map(rmap, ver, seed):
	get_rlist_A(rmap, ver, seed)

vlist_A = [
	( 1, 0 ),
	( 1, 0 )
]

def get_vlist_A(ver):
	c, v = 0, []
	for p in vlist_A:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_A = [
]

def get_rlist_A(rmap, ver, seed):
	rmap['A'] = CogStack(get_vlist_A(ver))
	for p in rlist_A:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			rmap['A'].cogs.append(p[2](seed))

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.test_name)

def write_A(ctx, payload):
	for i in ctx.reorder_map['A']():
		if i==0:
			write_int(ctx, payload.i1)
		elif i==1:
			write_str(ctx, payload.s1)

def write_OuterA(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_A(ctx, payload.v[i])
		i = i + 1

def write_OuterB(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_A(ctx, payload.v[i])
		i = i + 1

def write_OuterC(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_str(ctx, payload.v[i])
		i = i + 1

def write_OuterD(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_str(ctx, payload.v[i])
		i = i + 1

def write_OuterE(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_int(ctx, payload.v[i])
		i = i + 1

def write_OuterF(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_int(ctx, payload.v[i])
		i = i + 1

def write_Base(ctx, payload):
	c = type(payload).__name__
	if (c == "Derived1"):
		write_int(ctx,0)
		write_Derived1(ctx, payload)
	if (c == "Derived2"):
		write_int(ctx,1)
		write_Derived2(ctx, payload)


def write_Derived1(ctx, payload):
	write_int(ctx, payload.i1)
	write_str(ctx, payload.s1)

def write_Derived2(ctx, payload):
	write_int(ctx, payload.i1)
	write_str(ctx, payload.s1)

def write_OuterG(ctx, payload):
	count = len(payload.v)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_Base(ctx, payload.v[i])
		i = i + 1

def read_str(ctx):
   t = ctx.decoder.readInteger() # amf3
   assert(t == 6)
   return ctx.decoder.readString()

def read_int(ctx):
   t = ctx.decoder.readInteger() # amf3
   assert(t == 4)
   return ctx.decoder.readInteger()

def read_Header(ctx):
	payload = Header()
	payload.version = read_int(ctx)
	payload.test_name = read_str(ctx)
	return payload

def read_A(ctx):
	payload = A()
	for i in ctx.reorder_map['A']():
		if i==0:
			payload.i1 = read_int(ctx)
		elif i==1:
			payload.s1 = read_str(ctx)
	return payload

def read_OuterA(ctx):
	payload = OuterA()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_A(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterB(ctx):
	payload = OuterB()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_A(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterC(ctx):
	payload = OuterC()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_str(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterD(ctx):
	payload = OuterD()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_str(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterE(ctx):
	payload = OuterE()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_int(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_OuterF(ctx):
	payload = OuterF()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_int(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

def read_Base(ctx):
	t = read_int(ctx)
	if (t == 0):
		payload = read_Derived1(ctx)
	if (t == 1):
		payload = read_Derived2(ctx)
	return payload

def read_Derived1(ctx):
	payload = Derived1()
	payload.i1 = read_int(ctx)
	payload.s1 = read_str(ctx)
	return payload

def read_Derived2(ctx):
	payload = Derived2()
	payload.i1 = read_int(ctx)
	payload.s1 = read_str(ctx)
	return payload

def read_OuterG(ctx):
	payload = OuterG()
	payload.v = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_Base(ctx)
		payload.v.append(t)
		i = i + 1
	return payload

