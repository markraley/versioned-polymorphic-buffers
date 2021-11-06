from vp_uno.persist import *

def version_check(ver):
	if (ver < 1 or ver > 1):
		return False
	else:
		return True

def get_high_version():
	return 1

def get_low_version():
	return 1

def init_reorder_map(map, ver, seed):
	pass

def write_str(ctx, payload):
    ctx.encoder.writeString(payload) # amf3

def write_int(ctx, payload):
    ctx.encoder.writeInteger(payload) # amf3

def write_Header(ctx, payload):
	write_int(ctx, payload.version)
	write_str(ctx, payload.tag)

def write_Card(ctx, payload):
	c = type(payload).__name__
	if (c == "Value"):
		write_int(ctx,0)
		write_Value(ctx, payload)
	if (c == "Reverse"):
		write_int(ctx,1)
		write_int(ctx,0)
		write_Reverse(ctx, payload)
	if (c == "Skip"):
		write_int(ctx,1)
		write_int(ctx,1)
		write_Skip(ctx, payload)
	if (c == "DrawTwo"):
		write_int(ctx,1)
		write_int(ctx,2)
		write_DrawTwo(ctx, payload)
	write_int(ctx, payload.id)


def write_Value(ctx, payload):
	write_int(ctx, payload.value)
	write_str(ctx, payload.color)

def write_Action(ctx, payload):
	write_str(ctx, payload.color)


def write_Reverse(ctx, payload):
	write_Action(ctx, payload)

def write_Skip(ctx, payload):
	write_Action(ctx, payload)

def write_DrawTwo(ctx, payload):
	write_Action(ctx, payload)

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
	t = read_int(ctx)
	if (t == 0):
		payload = read_Value(ctx)
	if (t == 1):
		payload = read_Action(ctx)
	payload.id = read_int(ctx)
	return payload

def read_Value(ctx):
	payload = Value()
	payload.value = read_int(ctx)
	payload.color = read_str(ctx)
	return payload

def read_Action(ctx):
	t = read_int(ctx)
	if (t == 0):
		payload = read_Reverse(ctx)
	if (t == 1):
		payload = read_Skip(ctx)
	if (t == 2):
		payload = read_DrawTwo(ctx)
	payload.color = read_str(ctx)
	return payload

def read_Reverse(ctx):
	payload = Reverse()
	return payload

def read_Skip(ctx):
	payload = Skip()
	return payload

def read_DrawTwo(ctx):
	payload = DrawTwo()
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

