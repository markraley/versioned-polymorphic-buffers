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

def init_reorder_map(map, ver):
	pass

def write_int(ver, wc, payload):
    wc.encoder.writeInteger(payload) # amf3

def write_str(ver, wc, payload):
    wc.encoder.writeString(payload) # amf3

def write_Header(ver, f, payload):
	write_int(ver, f, payload.version)
	write_str(ver, f, payload.tag)

def write_Card(ver, f, payload):
	c = type(payload).__name__
	if (c == "Value"):
		write_int(ver, f,0)
		write_Value(ver, f, payload)
	if (c == "Reverse"):
		write_int(ver, f,1)
		write_int(ver, f,0)
		write_Reverse(ver, f, payload)
	if (c == "Skip"):
		write_int(ver, f,1)
		write_int(ver, f,1)
		write_Skip(ver, f, payload)
	if (c == "DrawTwo"):
		write_int(ver, f,1)
		write_int(ver, f,2)
		write_DrawTwo(ver, f, payload)
	write_int(ver, f, payload.id)


def write_Value(ver, f, payload):
	write_int(ver, f, payload.value)
	write_str(ver, f, payload.color)

def write_Action(ver, f, payload):
	write_str(ver, f, payload.color)


def write_Reverse(ver, f, payload):
	write_Action(ver, f, payload)

def write_Skip(ver, f, payload):
	write_Action(ver, f, payload)

def write_DrawTwo(ver, f, payload):
	write_Action(ver, f, payload)

def write_Deck(ver, f, payload):
	count = len(payload.cards)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_Card(ver, f, payload.cards[i])
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
	payload.version = read_int(ver, f)
	payload.tag = read_str(ver, f)
	return payload

def read_Card(ver, f):
	t = read_int(ver, f)
	if (t == 0):
		payload = read_Value(ver, f)
	if (t == 1):
		payload = read_Action(ver, f)
	payload.id = read_int(ver, f)
	return payload

def read_Value(ver, f):
	payload = Value()
	payload.value = read_int(ver, f)
	payload.color = read_str(ver, f)
	return payload

def read_Action(ver, f):
	t = read_int(ver, f)
	if (t == 0):
		payload = read_Reverse(ver, f)
	if (t == 1):
		payload = read_Skip(ver, f)
	if (t == 2):
		payload = read_DrawTwo(ver, f)
	payload.color = read_str(ver, f)
	return payload

def read_Reverse(ver, f):
	payload = Reverse()
	return payload

def read_Skip(ver, f):
	payload = Skip()
	return payload

def read_DrawTwo(ver, f):
	payload = DrawTwo()
	return payload

def read_Deck(ver, f):
	payload = Deck()
	payload.cards = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_Card(ver, f)
		payload.cards.append(t)
		i = i + 1
	return payload

