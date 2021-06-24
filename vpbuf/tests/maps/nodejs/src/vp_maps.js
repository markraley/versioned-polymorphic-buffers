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
		wc.write_String(payload.test_name);
	},

	write_A: function(ver, wc, payload) {
		wc.write_Integer(payload.i1);
		wc.write_String(payload.s1);
	},

	write_OuterA: function(ver, wc, payload) {
		wc.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_Integer(ver, wc, k)
			this.write_A(ver, wc, v)
		}
	},

	write_OuterB: function(ver, wc, payload) {
		wc.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_String(ver, wc, k)
			this.write_A(ver, wc, v)
		}
	},

	write_OuterC: function(ver, wc, payload) {
		wc.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_Integer(ver, wc, k)
			this.write_String(ver, wc, v)
		}
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
		payload.test_name = rc.read_String();
		return payload;
	},

	read_A: function(ver, rc) {
		var payload = new this.factory.A();
		payload.i1 = rc.read_Integer();
		payload.s1 = rc.read_String();
		return payload;
	},

	read_OuterA: function(ver, rc) {
		var payload = new this.factory.OuterA();
		payload.lookup = {}
		var count = rc.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = rc.read_Integer()
			var t = this.read_A(ver, rc)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_OuterB: function(ver, rc) {
		var payload = new this.factory.OuterB();
		payload.lookup = {}
		var count = rc.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = this.read_String(ver, rc)
			var t = this.read_A(ver, rc)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_OuterC: function(ver, rc) {
		var payload = new this.factory.OuterC();
		payload.lookup = {}
		var count = rc.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = rc.read_Integer()
			var t = this.read_String(ver, rc)
			payload.lookup[k] = t
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
