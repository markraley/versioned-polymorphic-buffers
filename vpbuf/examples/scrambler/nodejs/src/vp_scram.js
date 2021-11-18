// vpbuf generated code - do not modify
"use strict";
var persist = require("./persist");
const assert = require('chai').assert;

module.exports = {
	factory: null, // must be set to class factory object

	init_reorder_map: function(map, ver, seed) {
		map['Word'] = this.get_rlist_Word(ver, seed)
		map['Phrase'] = this.get_rlist_Phrase(ver, seed)
	},

	vlist_Word: [
		[ 1, 0 ],
		[ 1, 0 ],
		[ 1, 0 ],
		[ 1, 0 ],
		[ 3, 0 ],
		[ 3, 0 ],
		[ 3, 0 ],
		[ 3, 0 ]
	],

	get_vlist_Word: function(ver) {
		var v = [];
		this.vlist_Word.forEach(function(p, i) {
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1])) {
				v.push(i);
			}
		});
		return v;
	},

	rlist_Word: [
		[ 2, 0, 'h1', persist.EggScrambler ]
	],

	get_rlist_Word: function (ver, seed) {
		for (var i = 0; i < this.rlist_Word.length; i++) {
			var p = this.rlist_Word[i]
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1]))
				return [p[2], p[3](this.get_vlist_Word(ver), seed)]
		}
		return ['ident', persist.IdentityScrambler(this.get_vlist_Word(ver))]
	},

	vlist_Phrase: [
		[ 1, 0 ],
		[ 1, 0 ],
		[ 1, 0 ]
	],

	get_vlist_Phrase: function(ver) {
		var v = [];
		this.vlist_Phrase.forEach(function(p, i) {
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1])) {
				v.push(i);
			}
		});
		return v;
	},

	rlist_Phrase: [
		[ 3, 0, 'h2', persist.HashBrowns ]
	],

	get_rlist_Phrase: function (ver, seed) {
		for (var i = 0; i < this.rlist_Phrase.length; i++) {
			var p = this.rlist_Phrase[i]
			if ((p[1] == 0 && ver >= p[0]) || (ver >= p[0] && ver <= p[1]))
				return [p[2], p[3](this.get_vlist_Phrase(ver), seed)]
		}
		return ['ident', persist.IdentityScrambler(this.get_vlist_Phrase(ver))]
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

	write_Word: function(ctx, payload) {
		var v = ctx.reorder_map['Word'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				ctx.write_String(payload.fragment1);
				break;
				case 1:
				ctx.write_String(payload.fragment2);
				break;
				case 2:
				ctx.write_String(payload.fragment3);
				break;
				case 3:
				ctx.write_String(payload.fragment4);
				break;
				case 4:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
				case 5:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
				case 6:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
				case 7:
				ctx.write_String(ctx.salt_map['SaltShaker']());
				break;
			};
	},

	write_Phrase: function(ctx, payload) {
		var v = ctx.reorder_map['Phrase'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				ctx.write_String(payload.word1);
				break;
				case 1:
				ctx.write_String(payload.word2);
				break;
				case 2:
				ctx.write_String(payload.word3);
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

	read_Word: function(ctx) {
		var payload = new this.factory.Word();
		var v = ctx.reorder_map['Word'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				payload.fragment1 = ctx.read_String();
				break;
				case 1:
				payload.fragment2 = ctx.read_String();
				break;
				case 2:
				payload.fragment3 = ctx.read_String();
				break;
				case 3:
				payload.fragment4 = ctx.read_String();
				break;
				case 4:
				this.read_String(ctx)
				break;
				case 5:
				this.read_String(ctx)
				break;
				case 6:
				this.read_String(ctx)
				break;
				case 7:
				this.read_String(ctx)
				break;
			};
		return payload;
	},

	read_Phrase: function(ctx) {
		var payload = new this.factory.Phrase();
		var v = ctx.reorder_map['Phrase'][1]();
		for (var i = 0; i < v.length; i++)
			switch(v[i]) {
				case 0:
				payload.word1 = ctx.read_String();
				break;
				case 1:
				payload.word2 = ctx.read_String();
				break;
				case 2:
				payload.word3 = ctx.read_String();
				break;
			};
		return payload;
	},

	version_check: function(ver) {
		return (ver < 1 || ver > 3) ? false : true;
	},
	get_high_version: function(ver) {
		return 3
	},
	get_low_version: function(ver) {
		return 1
	}
};
