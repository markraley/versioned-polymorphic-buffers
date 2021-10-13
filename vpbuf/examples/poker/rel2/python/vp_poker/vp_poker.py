from vp_poker.persist import *

def version_check(ver):
	if (ver < 1 or ver > 2):
		return False
	else:
		return True

def get_high_version():
	return 2

def get_low_version():
	return 1

def init_reorder_map(map, ver):
	pass

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.tag)

def write_Card(ctx, payload):
	write_int(ctx, payload.id)
	if (ctx.ver >= 1 and ctx.ver <= 1):
		write_str(ctx, payload.name)

def write_Deck(ctx, payload):
	count = len(payload.cards)
	write_int(ctx, count)
	i = 0
	while (i < count):
		write_Card(ctx, payload.cards[i])
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
	payload.tag = read_str(ctx)
	return payload

def read_Card(ctx):
	payload = Card()
	payload.id = read_int(ctx)
	if (ctx.ver >= 1 and ctx.ver <= 1):
		payload.name = read_str(ctx)
	return payload

def read_Deck(ctx):
	payload = Deck()
	payload.cards = []
	count = read_int(ctx)
	i = 0
	while (i < count):
		t = read_Card(ctx)
		payload.cards.append(t)
		i = i + 1
	return payload

