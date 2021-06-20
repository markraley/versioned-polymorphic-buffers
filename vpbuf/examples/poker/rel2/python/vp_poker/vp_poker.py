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

def write_int(ver, f, payload):
    f.writeInteger(payload)

def write_str(ver, f, payload):
    f.writeString(payload)

def write_Header(ver, f, payload):
	write_int(ver, f, payload.version)
	write_str(ver, f, payload.tag)

def write_Card(ver, f, payload):
	write_int(ver, f, payload.id)
	if (ver >= 1 and ver <= 1):
		write_str(ver, f, payload.name)

def write_Deck(ver, f, payload):
	count = len(payload.cards)
	write_int(ver, f, count)
	i = 0
	while (i < count):
		write_Card(ver, f, payload.cards[i])
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
	payload = Card()
	payload.id = read_int(ver, f)
	if (ver >= 1 and ver <= 1):
		payload.name = read_str(ver, f)
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

