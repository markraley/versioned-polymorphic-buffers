from vp_scram.persist import *

def version_check(ver):
	if (ver < 1 or ver > 3):
		return False
	else:
		return True

def get_high_version():
	return 3

def get_low_version():
	return 1

def init_reorder_map(rmap, ver, seed):
	get_rlist_Phrase(rmap, ver, seed)

vlist_Phrase = [
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 ),
	( 3, 0 )
]

def get_vlist_Phrase(ver):
	c, v = 0, []
	for p in vlist_Phrase:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Phrase = [
	( 3, 0, HashBrowns )
]

def get_rlist_Phrase(rmap, ver, seed):
	rmap['Phrase'] = CogStack(get_vlist_Phrase(ver))
	for p in rlist_Phrase:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			rmap['Phrase'].cogs.append(p[2](seed))

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.test_name)

def write_Phrase(ctx, payload):
	for i in ctx.reorder_map['Phrase']():
		if i==0:
			write_str(ctx, payload.word1)
		elif i==1:
			write_str(ctx, payload.word2)
		elif i==2:
			write_str(ctx, payload.word3)
		elif i==3:
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

def read_Phrase(ctx):
	payload = Phrase()
	for i in ctx.reorder_map['Phrase']():
		if i==0:
			payload.word1 = read_str(ctx)
		elif i==1:
			payload.word2 = read_str(ctx)
		elif i==2:
			payload.word3 = read_str(ctx)
		elif i==3:
			read_str(ctx)
	return payload

