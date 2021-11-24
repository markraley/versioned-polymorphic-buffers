// vpbuf generated code - do not modify
"use strict";
var persist = require("./persist");
const assert = require('chai').assert;

module.exports = {
	factory: null, // must be set to class factory object

	init_reorder_map: function(map, ver, seed) {
		map['A'] = this.get_rlist_A(ver, seed)
	},

	vlist_A: [
		[ 1, 0 ],
		[ 1, 0 ]
	],

	get_vlist_A: function(ver) {
		var v = [];
		this.vlist_A.forEach(function(p, i) {
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1])) {
				v.push(i);
			}
		});
		return v;
	},

	rlist_A: [
	],

	get_rlist_A: function (ver, seed) {
		for (var i = 0; i < this.rlist_A.length; i++) {
			var p = this.rlist_A[i]
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1]))
				return p[2](this.get_vlist_A(ver), seed)
		}
		return persist.IdentityScrambler(this.get_vlist_A(ver))
	},

	write_String: function(ctx, payload) {
		ctx.write_String(payload);
	},

	write_Integer: function(ctx, payload) {
		ctx.write_Integer(payload);
	},

	write_Header: function(ctx, payload) {
		ctx.write_Integer(payload.version);
		ctx.write_String(payload.test_name);
	},

	write_A: function(ctx, payload) {
		var v = ctx.reorder_map['A']();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				ctx.write_Integer(payload.i1);
				break;
				case 1:
				ctx.write_String(payload.s1);
				break;
			};
	},

	write_OuterA: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_A(ctx, payload.v[i]);
	},

	write_OuterB: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_A(ctx, payload.v[i]);
	},

	write_OuterC: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_String(ctx, payload.v[i]);
	},

	write_OuterD: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_String(ctx, payload.v[i]);
	},

	write_OuterE: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Integer(ctx, payload.v[i]);
	},

	write_OuterF: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Integer(ctx, payload.v[i]);
	},

	write_Base: function(ctx, payload) {
		var c = payload.constructor.name;
		if (c == 'Derived1') {
			ctx.write_Integer(0)
			this.write_Derived1(ctx, payload)
		}
		if (c == 'Derived2') {
			ctx.write_Integer(1)
			this.write_Derived2(ctx, payload)
		}
	},

	write_Derived1: function(ctx, payload) {
		ctx.write_Integer(payload.i1);
		ctx.write_String(payload.s1);
	},

	write_Derived2: function(ctx, payload) {
		ctx.write_Integer(payload.i1);
		ctx.write_String(payload.s1);
	},

	write_OuterG: function(ctx, payload) {
		ctx.write_Integer(payload.v.length);
		for (var i = 0; i < payload.v.length; i++)
			this.write_Base(ctx, payload.v[i]);
	},

	read_String: function(ctx) {
		return ctx.read_String();
	},

	read_Integer: function(ctx) {
		return ctx.read_Integer();
	},

	read_Header: function(ctx) {
		var payload = new this.factory.Header();
		payload.version = ctx.read_Integer();
		payload.test_name = ctx.read_String();
		return payload;
	},

	read_A: function(ctx) {
		var payload = new this.factory.A();
		var v = ctx.reorder_map['A']();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				payload.i1 = ctx.read_Integer();
				break;
				case 1:
				payload.s1 = ctx.read_String();
				break;
			};
		return payload;
	},

	read_OuterA: function(ctx) {
		var payload = new this.factory.OuterA();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_A(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterB: function(ctx) {
		var payload = new this.factory.OuterB();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_A(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterC: function(ctx) {
		var payload = new this.factory.OuterC();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_String(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterD: function(ctx) {
		var payload = new this.factory.OuterD();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_String(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterE: function(ctx) {
		var payload = new this.factory.OuterE();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Integer(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_OuterF: function(ctx) {
		var payload = new this.factory.OuterF();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Integer(ctx);
			payload.v.push(c);
		}
		return payload;
	},

	read_Base: function(ctx) {
		var t = ctx.read_Integer(ctx)
		var payload;
		if (t == 0) {
			payload = this.read_Derived1(ctx)
		}
		if (t == 1) {
			payload = this.read_Derived2(ctx)
		}
		return payload;
	},

	read_Derived1: function(ctx) {
		var payload = new this.factory.Derived1();
		payload.i1 = ctx.read_Integer();
		payload.s1 = ctx.read_String();
		return payload;
	},

	read_Derived2: function(ctx) {
		var payload = new this.factory.Derived2();
		payload.i1 = ctx.read_Integer();
		payload.s1 = ctx.read_String();
		return payload;
	},

	read_OuterG: function(ctx) {
		var payload = new this.factory.OuterG();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Base(ctx);
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
