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
		ctx.write_String(payload.tag);
	},

	write_Card: function(ctx, payload) {
		ctx.write_Integer(payload.id);
		ctx.write_String(payload.name);
	},

	write_Deck: function(ctx, payload) {
		ctx.write_Integer(payload.cards.length);
		for (var i = 0; i < payload.cards.length; i++)
			this.write_Card(ctx, payload.cards[i]);
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
		payload.tag = ctx.read_String();
		return payload;
	},

	read_Card: function(ctx) {
		var payload = new this.factory.Card();
		payload.id = ctx.read_Integer();
		payload.name = ctx.read_String();
		return payload;
	},

	read_Deck: function(ctx) {
		var payload = new this.factory.Deck();
		var count = ctx.read_Integer();
		for (var i = 0; i < count; i++) {
			var c = this.read_Card(ctx);
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
