// vpbuf generated code - do not modify
"use strict";
var persist = require("./persist");
const assert = require('chai').assert;

module.exports = {
	factory: null, // must be set to class factory object

	init_reorder_map: function(map, ver, seed) {
		map['Egg'] = this.get_rlist_Egg(ver, seed)
	},

	vlist_Egg: [
		[ 1, 0 ],
		[ 1, 0 ],
		[ 1, 0 ],
		[ 1, 0 ]
	],

	get_vlist_Egg: function(ver) {
		var v = [];
		this.vlist_Egg.forEach(function(p, i) {
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1])) {
				v.push(i);
			}
		});
		return v;
	},

	rlist_Egg: [
		[ 1, 0, 'h1', persist.EggScrambler ]
	],

	get_rlist_Egg: function (ver, seed) {
		for (var i = 0; i < this.rlist_Egg.length; i++) {
			var p = this.rlist_Egg[i]
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1]))
				return [p[2], p[3](this.get_vlist_Egg(ver), seed)]
		}
		return ['ident', persist.IdentityScrambler(this.get_vlist_Egg(ver))]
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
		ctx.write_Integer(payload.i1);
		ctx.write_String(payload.s1);
	},

	write_OuterA: function(ctx, payload) {
		ctx.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_Integer(ctx, k)
			this.write_A(ctx, v)
		}
	},

	write_OuterB: function(ctx, payload) {
		ctx.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_String(ctx, k)
			this.write_A(ctx, v)
		}
	},

	write_OuterC: function(ctx, payload) {
		ctx.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_Integer(ctx, k)
			this.write_String(ctx, v)
		}
	},

	write_D1: function(ctx, payload) {
		this.write_A(ctx, payload.apod)
		ctx.write_Integer(payload.i);
		ctx.write_String(payload.s);
		this.write_A(ctx, payload.aref)
	},

	write_OuterD: function(ctx, payload) {
		ctx.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_String(ctx, k)
			this.write_D1(ctx, v)
		}
	},

	write_Egg: function(ctx, payload) {
		var v = ctx.reorder_map['Egg'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				ctx.write_Integer(payload.i1);
				break;
				case 1:
				ctx.write_String(payload.s1);
				break;
				case 2:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
				case 3:
				ctx.write_String(ctx.salt_map['PepperShaker']());
				break;
			};
	},

	write_Omlette: function(ctx, payload) {
		ctx.write_Integer(Object.keys(payload.lookup).length)
		for (const [k, v] of Object.entries(payload.lookup)) {
			this.write_Integer(ctx, k)
			this.write_Egg(ctx, v)
		}
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
		payload.i1 = ctx.read_Integer();
		payload.s1 = ctx.read_String();
		return payload;
	},

	read_OuterA: function(ctx) {
		var payload = new this.factory.OuterA();
		payload.lookup = {}
		var count = ctx.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = ctx.read_Integer()
			var t = this.read_A(ctx)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_OuterB: function(ctx) {
		var payload = new this.factory.OuterB();
		payload.lookup = {}
		var count = ctx.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = this.read_String(ctx)
			var t = this.read_A(ctx)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_OuterC: function(ctx) {
		var payload = new this.factory.OuterC();
		payload.lookup = {}
		var count = ctx.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = ctx.read_Integer()
			var t = this.read_String(ctx)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_D1: function(ctx) {
		var payload = new this.factory.D1();
		payload.apod = this.read_A(ctx)
		payload.i = ctx.read_Integer();
		payload.s = ctx.read_String();
		payload.aref = this.read_A(ctx)
		return payload;
	},

	read_OuterD: function(ctx) {
		var payload = new this.factory.OuterD();
		payload.lookup = {}
		var count = ctx.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = this.read_String(ctx)
			var t = this.read_D1(ctx)
			payload.lookup[k] = t
		}

		return payload;
	},

	read_Egg: function(ctx) {
		var payload = new this.factory.Egg();
		var v = ctx.reorder_map['Egg'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				payload.i1 = ctx.read_Integer();
				break;
				case 1:
				payload.s1 = ctx.read_String();
				break;
				case 2:
				assert.equal(this.read_String(ctx) , ctx.salt_map['SaltShaker']())
				break;
				case 3:
				assert.equal(this.read_String(ctx) , ctx.salt_map['PepperShaker']())
				break;
			};
		return payload;
	},

	read_Omlette: function(ctx) {
		var payload = new this.factory.Omlette();
		payload.lookup = {}
		var count = ctx.read_Integer()
		for (var i = 0; i < count; i++) {
			var k = ctx.read_Integer()
			var t = this.read_Egg(ctx)
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
