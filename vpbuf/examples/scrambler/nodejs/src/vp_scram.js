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
		[ 2, 0 ],
		[ 5, 0 ],
		[ 3, 0 ],
		[ 4, 0 ]
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
		[ 2, 0, 'h1', persist.EggScrambler ]
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

	write_Egg: function(ctx, payload) {
		var v = ctx.reorder_map['Egg'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				ctx.write_String(payload.c1);
				break;
				case 1:
				ctx.write_String(payload.c2);
				break;
				case 2:
				ctx.write_String(payload.c3);
				break;
				case 3:
				this.write_Header(ctx, payload.h1)
				break;
				case 4:
				ctx.write_String(payload.c4);
				break;
				case 5:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
				case 6:
				ctx.write_String(ctx.salt_map['PepperShaker']());
				break;
			};
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

	read_Egg: function(ctx) {
		var payload = new this.factory.Egg();
		var v = ctx.reorder_map['Egg'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				payload.c1 = ctx.read_String();
				break;
				case 1:
				payload.c2 = ctx.read_String();
				break;
				case 2:
				payload.c3 = ctx.read_String();
				break;
				case 3:
				payload.h1 = this.read_Header(ctx)
				break;
				case 4:
				payload.c4 = ctx.read_String();
				break;
				case 5:
				assert.equal(this.read_String(ctx) , ctx.salt_map['SaltShaker']())
				break;
				case 6:
				assert.equal(this.read_String(ctx) , ctx.salt_map['PepperShaker']())
				break;
			};
		return payload;
	},

	version_check: function(ver) {
		return (ver < 1 || ver > 5) ? false : true;
	},
	get_high_version: function(ver) {
		return 5
	},
	get_low_version: function(ver) {
		return 1
	}
};
