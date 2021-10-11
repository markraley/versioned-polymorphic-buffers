// vpbuf generated code - do not modify
"use strict";
var persist = require("./persist");

module.exports = {
	factory: null, // must be set to class factory object

	init_reorder_map: function(map, ver) {
	},

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
		wc.write_Integer(payload.id);
		wc.write_String(payload.name);
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
		var payload = new this.factory.Card();
		payload.id = rc.read_Integer();
		payload.name = rc.read_String();
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
