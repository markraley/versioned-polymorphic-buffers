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

def init_reorder_map(rmap, ver, seed):
	get_rlist_Egg(rmap, ver, seed)

vlist_Egg = [
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 )
]

def get_vlist_Egg(ver):
	c, v = 0, []
	for p in vlist_Egg:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Egg = [
	( 1, 0, EggScrambler ),
	( 2, 0, EggScrambler )
]

def get_rlist_Egg(rmap, ver, seed):
	rmap['Egg'] = CogStack(get_vlist_Egg(ver))
	for p in rlist_Egg:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			rmap['Egg'].cogs.append(p[2](seed))

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.test_name)

def write_A(ctx, payload):
	write_int(ctx, payload.i1)
	write_str(ctx, payload.s1)

def write_OuterA(ctx, payload):
	write_int(ctx, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_int(ctx, k)
		write_A(ctx, v)

def write_OuterB(ctx, payload):
	write_int(ctx, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_str(ctx, k)
		write_A(ctx, v)

def write_OuterC(ctx, payload):
	write_int(ctx, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_int(ctx, k)
		write_str(ctx, v)

def write_D1(ctx, payload):
	write_A(ctx, payload.apod)
	write_int(ctx, payload.i)
	write_str(ctx, payload.s)
	write_A(ctx, payload.aref)

def write_OuterD(ctx, payload):
	write_int(ctx, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_str(ctx, k)
		write_D1(ctx, v)

def write_Egg(ctx, payload):
	for i in ctx.reorder_map['Egg']():
		if i==0:
			write_int(ctx, payload.i1)
		elif i==1:
			write_str(ctx, payload.s1)
		elif i==2:
			write_str(ctx, ctx.salt_map['SaltShaker']())
		elif i==3:
			write_str(ctx, ctx.salt_map['PepperShaker']())

def write_Omlette(ctx, payload):
	write_int(ctx, len(payload.lookup))
	for k, v in iter(payload.lookup.items()):
		write_int(ctx, k)
		write_Egg(ctx, v)

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
	payload.i1 = read_int(ctx)
	payload.s1 = read_str(ctx)
	return payload

def read_OuterA(ctx):
	payload = OuterA()
	payload.lookup = {}
	count = read_int(ctx)
	i = 0
	while (i < count):
		k = int()
		k = read_int(ctx)
		t = A()
		t = read_A(ctx)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_OuterB(ctx):
	payload = OuterB()
	payload.lookup = {}
	count = read_int(ctx)
	i = 0
	while (i < count):
		k = str()
		k = read_str(ctx)
		t = A()
		t = read_A(ctx)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_OuterC(ctx):
	payload = OuterC()
	payload.lookup = {}
	count = read_int(ctx)
	i = 0
	while (i < count):
		k = int()
		k = read_int(ctx)
		t = str()
		t = read_str(ctx)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_D1(ctx):
	payload = D1()
	payload.apod = read_A(ctx)
	payload.i = read_int(ctx)
	payload.s = read_str(ctx)
	payload.aref = read_A(ctx)
	return payload

def read_OuterD(ctx):
	payload = OuterD()
	payload.lookup = {}
	count = read_int(ctx)
	i = 0
	while (i < count):
		k = str()
		k = read_str(ctx)
		t = D1()
		t = read_D1(ctx)
		payload.lookup[k] = t
		i = i + 1

	return payload

def read_Egg(ctx):
	payload = Egg()
	for i in ctx.reorder_map['Egg']():
		if i==0:
			payload.i1 = read_int(ctx)
		elif i==1:
			payload.s1 = read_str(ctx)
		elif i==2:
			assert(read_str(ctx) == ctx.salt_map['SaltShaker']())
		elif i==3:
			assert(read_str(ctx) == ctx.salt_map['PepperShaker']())
	return payload

def read_Omlette(ctx):
	payload = Omlette()
	payload.lookup = {}
	count = read_int(ctx)
	i = 0
	while (i < count):
		k = int()
		k = read_int(ctx)
		t = Egg()
		t = read_Egg(ctx)
		payload.lookup[k] = t
		i = i + 1

	return payload

