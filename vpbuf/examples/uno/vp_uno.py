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

def write_int(ver, f, payload):
    f.writeInteger(payload)

def write_str(ver, f, payload):
    f.writeString(payload)

def write_Header(ver, f, payload):
	write_int(ver, f, payload.version)
	write_str(ver, f, payload.tag)

def write_Card(ver, f, payload):
	c = type(payload).__name__
	if (c == "Value"):
		write_int(ver, f,0)
		write_Value(ver, f, payload)
	if (c == "Wild"):
		write_int(ver, f,1)
		write_Wild(ver, f, payload)
	if (c == "Reverse"):
		write_int(ver, f,2)
		write_int(ver, f,0)
		write_Reverse(ver, f, payload)
	if (c == "Skip"):
		write_int(ver, f,2)
		write_int(ver, f,1)
		write_Skip(ver, f, payload)
	if (c == "DrawTwo"):
		write_int(ver, f,2)
		write_int(ver, f,2)
		write_DrawTwo(ver, f, payload)
	write_int(ver, f, payload.id)


def write_Value(ver, f, payload):
	write_int(ver, f, payload.value)
	write_int(ver, f, payload.color)
	write_str(ver, f, payload.name)

def write_Wild(ver, f, payload):
	write_str(ver, f, payload.wild_name)

def write_Action(ver, f, payload):
	write_str(ver, f, payload.action_name)


def write_Reverse(ver, f, payload):
	write_int(ver, f, payload.reverse_int)
	write_Action(ver, f, payload)

def write_Skip(ver, f, payload):
	write_int(ver, f, payload.skip_int)
	write_Action(ver, f, payload)

def write_DrawTwo(ver, f, payload):
	write_int(ver, f, payload.drawtwo_int)
	write_Action(ver, f, payload)

def write_Deck(ver, f, payload):
	count = len(payload.cards)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_Card(ver, f, payload.cards[i])
		i = i + 1
	count = len(payload.abc)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_Header(ver, f, payload.abc[i])
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
	payload.tag = read_str(ver, f)
	return payload

def read_Card(ver, f):
	t = read_int(ver, f)
	if (t == 0):
		payload = read_Value(ver, f)
	if (t == 1):
		payload = read_Wild(ver, f)
	if (t == 2):
		payload = read_Action(ver, f)
	payload.id = read_int(ver, f)
	return payload

def read_Value(ver, f):
	payload = Value()
	payload.value = read_int(ver, f)
	payload.color = read_int(ver, f)
	payload.name = read_str(ver, f)
	return payload

def read_Wild(ver, f):
	payload = Wild()
	payload.wild_name = read_str(ver, f)
	return payload

def read_Action(ver, f):
	t = read_int(ver, f)
	if (t == 0):
		payload = read_Reverse(ver, f)
	if (t == 1):
		payload = read_Skip(ver, f)
	if (t == 2):
		payload = read_DrawTwo(ver, f)
	payload.action_name = read_str(ver, f)
	return payload

def read_Reverse(ver, f):
	payload = Reverse()
	payload.reverse_int = read_int(ver, f)
	return payload

def read_Skip(ver, f):
	payload = Skip()
	payload.skip_int = read_int(ver, f)
	return payload

def read_DrawTwo(ver, f):
	payload = DrawTwo()
	payload.drawtwo_int = read_int(ver, f)
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
	payload.abc = []
	count = read_int(ver, f)
	i = 0
	while (i < count):
		t = read_Header(ver, f)
		payload.abc.append(t)
		i = i + 1
	return payload

