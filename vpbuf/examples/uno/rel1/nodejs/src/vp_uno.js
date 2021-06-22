// vpbuf generated code - do not modify
"use strict";
module.exports = {

	factory: null, // must be set to class factory object

	write_String: function(ver, wc, payload) {
		wc.write_String(payload);
	},

	write_Integer: function(ver, wc, payload) {
		wc.write_Integer(payload);
	},

	write_Header: function(ver, wc, payload) {
		wc.write_Integer(payload.version);
		wc.write_String(payload.tag);
	},

	write_Card: function(ver, wc, payload) {
		var c = payload.constructor.name;
		if (c == 'Value') {
			wc.write_Integer(0)
			this.write_Value(ver, wc, payload)
		}
		if (c == 'Reverse') {
			wc.write_Integer(1)
			wc.write_Integer(0)
			this.write_Reverse(ver, wc, payload)
		}
		if (c == 'Skip') {
			wc.write_Integer(1)
			wc.write_Integer(1)
			this.write_Skip(ver, wc, payload)
		}
		if (c == 'DrawTwo') {
			wc.write_Integer(1)
			wc.write_Integer(2)
			this.write_DrawTwo(ver, wc, payload)
		}
		wc.write_Integer(payload.id);
	},

	write_Value: function(ver, wc, payload) {
		wc.write_Integer(payload.value);
		wc.write_String(payload.color);
	},

	write_Action: function(ver, wc, payload) {
		wc.write_String(payload.color);
	},

	write_Reverse: function(ver, wc, payload) {
		this.write_Action(ver, wc, payload)
	},

	write_Skip: function(ver, wc, payload) {
		this.write_Action(ver, wc, payload)
	},

	write_DrawTwo: function(ver, wc, payload) {
		this.write_Action(ver, wc, payload)
	},

	write_Deck: function(ver, wc, payload) {
		wc.write_Integer(payload.cards.length);
		for (var i = 0; i < payload.cards.length; i++)
			this.write_Card(ver, wc, payload.cards[i]);
	},

	read_String: function(ver, rc) {
		return rc.read_String();
	},

	read_Integer: function(ver, rc) {
		return rc.read_Integer();
	},

	read_Header: function(ver, rc) {
		var payload = new this.factory.Header();
		payload.version = rc.read_Integer();
		payload.tag = rc.read_String();
		return payload;
	},

	read_Card: function(ver, rc) {
		var t = rc.read_Integer(ver, rc)
		var payload;
		if (t == 0) {
			payload = this.read_Value(ver, rc)
		}
		if (t == 1) {
			payload = this.read_Action(ver, rc)
		}
		payload.id = rc.read_Integer();
		return payload;
	},

	read_Value: function(ver, rc) {
		var payload = new this.factory.Value();
		payload.value = rc.read_Integer();
		payload.color = rc.read_String();
		return payload;
	},

	read_Action: function(ver, rc) {
		var t = rc.read_Integer(ver, rc)
		var payload;
		if (t == 0) {
			payload = this.read_Reverse(ver, rc)
		}
		if (t == 1) {
			payload = this.read_Skip(ver, rc)
		}
		if (t == 2) {
			payload = this.read_DrawTwo(ver, rc)
		}
		payload.color = rc.read_String();
		return payload;
	},

	read_Reverse: function(ver, rc) {
		var payload = new this.factory.Reverse();
		return payload;
	},

	read_Skip: function(ver, rc) {
		var payload = new this.factory.Skip();
		return payload;
	},

	read_DrawTwo: function(ver, rc) {
		var payload = new this.factory.DrawTwo();
		return payload;
	},

	read_Deck: function(ver, rc) {
		var payload = new this.factory.Deck();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Card(ver, rc);
			payload.cards.push(c);
		}
		return payload;
	},

	version_check: function(ver) {
		return (ver < 1 || ver > 1) ? false : true;
	},
	get_high_version: function(ver) {
		return 1
	},
	get_low_version: function(ver) {
		return 1
	}
};
