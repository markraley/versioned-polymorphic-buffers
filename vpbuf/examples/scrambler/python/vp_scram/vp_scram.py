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

def init_reorder_map(map, ver, seed):
	map['Word'] = get_rlist_Word(ver, seed)
	map['Phrase'] = get_rlist_Phrase(ver, seed)

vlist_Word = [
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 ),
	( 3, 0 ),
	( 3, 0 ),
	( 3, 0 ),
	( 3, 0 )
]

def get_vlist_Word(ver):
	c, v = 0, []
	for p in vlist_Word:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Word = [
	( 2, 0, 'h1', EggScrambler )
]

def get_rlist_Word(ver, seed):
	for p in rlist_Word:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			return [p[2], p[3](get_vlist_Word(ver), seed)]
	return ['ident', IdentityScrambler(get_vlist_Word(ver))]

vlist_Phrase = [
	( 1, 0 ),
	( 1, 0 ),
	( 1, 0 )
]

def get_vlist_Phrase(ver):
	c, v = 0, []
	for p in vlist_Phrase:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			v.append(c)
			c += 1
	return v

rlist_Phrase = [
	( 3, 0, 'h2', HashBrowns )
]

def get_rlist_Phrase(ver, seed):
	for p in rlist_Phrase:
		if (p[1] == 0 and ver >= p[0]) or (ver >= p[0] and ver <= p[1]):
			return [p[2], p[3](get_vlist_Phrase(ver), seed)]
	return ['ident', IdentityScrambler(get_vlist_Phrase(ver))]

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.test_name)

def write_Word(ctx, payload):
	for i in ctx.reorder_map['Word'][1]():
		if i==0:
			write_str(ctx, payload.fragment1)
		elif i==1:
			write_str(ctx, payload.fragment2)
		elif i==2:
			write_str(ctx, payload.fragment3)
		elif i==3:
			write_str(ctx, payload.fragment4)
		elif i==4:
			write_str(ctx, ctx.salt_map['SaltShaker']())
		elif i==5:
			write_str(ctx, ctx.salt_map['SaltShaker']())
		elif i==6:
			write_str(ctx, ctx.salt_map['SaltShaker']())
		elif i==7:
			write_str(ctx, ctx.salt_map['SaltShaker']())

def write_Phrase(ctx, payload):
	for i in ctx.reorder_map['Phrase'][1]():
		if i==0:
			write_str(ctx, payload.word1)
		elif i==1:
			write_str(ctx, payload.word2)
		elif i==2:
			write_str(ctx, payload.word3)

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

def read_Word(ctx):
	payload = Word()
	for i in ctx.reorder_map['Word'][1]():
		if i==0:
			payload.fragment1 = read_str(ctx)
		elif i==1:
			payload.fragment2 = read_str(ctx)
		elif i==2:
			payload.fragment3 = read_str(ctx)
		elif i==3:
			payload.fragment4 = read_str(ctx)
		elif i==4:
			read_str(ctx)
		elif i==5:
			read_str(ctx)
		elif i==6:
			read_str(ctx)
		elif i==7:
			read_str(ctx)
	return payload

def read_Phrase(ctx):
	payload = Phrase()
	for i in ctx.reorder_map['Phrase'][1]():
		if i==0:
			payload.word1 = read_str(ctx)
		elif i==1:
			payload.word2 = read_str(ctx)
		elif i==2:
			payload.word3 = read_str(ctx)
	return payload

