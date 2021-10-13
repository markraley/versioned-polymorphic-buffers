// vpbuf generated code - do not modify
"use strict";
var persist = require("./persist");

module.exports = {
	factory: null, // must be set to class factory object

	init_reorder_map: function(map, ver) {
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
