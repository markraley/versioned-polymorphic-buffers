// vp_buf auto generated code
"use strict";
const persist = require("./persist");

module.exports = {

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
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_A(ver, wc, payload.v[i]);
	},

	write_OuterB: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_A(ver, wc, payload.v[i]);
	},

	write_OuterC: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_String(ver, wc, payload.v[i]);
	},

	write_OuterD: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_String(ver, wc, payload.v[i]);
	},

	write_OuterE: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Integer(ver, wc, payload.v[i]);
	},

	write_OuterF: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Integer(ver, wc, payload.v[i]);
	},

	write_Base: function(ver, wc, payload) {
		var c = payload.constructor.name;
		if (c == 'Derived1') {
			wc.write_Integer(0)
			this.write_Derived1(ver, wc, payload)
		}
		if (c == 'Derived2') {
			wc.write_Integer(1)
			this.write_Derived2(ver, wc, payload)
		}
	},

	write_Derived1: function(ver, wc, payload) {
		wc.write_Integer(payload.i1);
		wc.write_String(payload.s1);
	},

	write_Derived2: function(ver, wc, payload) {
		wc.write_Integer(payload.i1);
		wc.write_String(payload.s1);
	},

	write_OuterG: function(ver, wc, payload) {
		wc.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Base(ver, wc, payload.v[i]);
	},

	read_String: function(ver, rc) {
		return rc.read_String();
	},

	read_Integer: function(ver, rc) {
		return rc.read_Integer();
	},

	read_Header: function(ver, rc) {
		var payload = new persist.Header();
		payload.version = rc.read_Integer();
		payload.test_name = rc.read_String();
		return payload;
	},

	read_A: function(ver, rc) {
		var payload = new persist.A();
		payload.i1 = rc.read_Integer();
		payload.s1 = rc.read_String();
		return payload;
	},

	read_OuterA: function(ver, rc) {
		var payload = new persist.OuterA();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_A(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterB: function(ver, rc) {
		var payload = new persist.OuterB();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_A(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterC: function(ver, rc) {
		var payload = new persist.OuterC();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_String(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterD: function(ver, rc) {
		var payload = new persist.OuterD();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_String(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterE: function(ver, rc) {
		var payload = new persist.OuterE();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Integer(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterF: function(ver, rc) {
		var payload = new persist.OuterF();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Integer(ver, rc);
			payload.v.push(c);
		}
		return payload;
	},

	read_Base: function(ver, rc) {
		var t = rc.read_Integer(ver, rc)
		var payload;
		if (t == 0) {
			payload = this.read_Derived1(ver, rc)
		}
		if (t == 1) {
			payload = this.read_Derived2(ver, rc)
		}
		return payload;
	},

	read_Derived1: function(ver, rc) {
		var payload = new persist.Derived1();
		payload.i1 = rc.read_Integer();
		payload.s1 = rc.read_String();
		return payload;
	},

	read_Derived2: function(ver, rc) {
		var payload = new persist.Derived2();
		payload.i1 = rc.read_Integer();
		payload.s1 = rc.read_String();
		return payload;
	},

	read_OuterG: function(ver, rc) {
		var payload = new persist.OuterG();
		var count = rc.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Base(ver, rc);
			payload.v.push(c);
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
