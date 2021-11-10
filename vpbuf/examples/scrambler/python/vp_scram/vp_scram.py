from vp_scram.persist import *

def version_check(ver):
	if (ver < 1 or ver > 5):
		return False
	else:
		return True

def get_high_version():
	return 5

def get_low_version():
	return 1

def init_reorder_map(map, ver, seed):
	map['Egg'] = get_rlist_Egg(ver, seed)

vlist_Egg = [
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 ),
	( 2, 0 ),
	( 5, 0 ),
	( 3, 0 ),
	( 4, 0 )
]

def get_vlist_Egg(ver):
	c, v = 0, []
	for p in vlist_Egg:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Egg = [
	( 2, 0, 'h1', EggScrambler )
]

def get_rlist_Egg(ver, seed):
	for p in rlist_Egg:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			return [p[2], p[3](get_vlist_Egg(ver), seed)]
	return ['ident', IdentityScrambler(get_vlist_Egg(ver))]

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.test_name)

def write_Egg(ctx, payload):
	for i in ctx.reorder_map['Egg'][1]():
		if i==0:
			write_str(ctx, payload.c1)
		elif i==1:
			write_str(ctx, payload.c2)
		elif i==2:
			write_str(ctx, payload.c3)
		elif i==3:
			write_Header(ctx, payload.h1)
		elif i==4:
			write_str(ctx, payload.c4)
		elif i==5:
			write_str(ctx, ctx.salt_map['SaltShaker']())
		elif i==6:
			write_str(ctx, ctx.salt_map['PepperShaker']())

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

def read_Egg(ctx):
	payload = Egg()
	for i in ctx.reorder_map['Egg'][1]():
		if i==0:
			payload.c1 = read_str(ctx)
		elif i==1:
			payload.c2 = read_str(ctx)
		elif i==2:
			payload.c3 = read_str(ctx)
		elif i==3:
			payload.h1 = read_Header(ctx)
		elif i==4:
			payload.c4 = read_str(ctx)
		elif i==5:
			assert(read_str(ctx) == ctx.salt_map['SaltShaker']())
		elif i==6:
			assert(read_str(ctx) == ctx.salt_map['PepperShaker']())
	return payload

