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
		var c = payload.constructor.name;
		if (c == 'Value') {
			ctx.write_Integer(0)
			this.write_Value(ctx, payload)
		}
		if (c == 'Reverse') {
			ctx.write_Integer(1)
			ctx.write_Integer(0)
			this.write_Reverse(ctx, payload)
		}
		if (c == 'Skip') {
			ctx.write_Integer(1)
			ctx.write_Integer(1)
			this.write_Skip(ctx, payload)
		}
		if (c == 'DrawTwo') {
			ctx.write_Integer(1)
			ctx.write_Integer(2)
			this.write_DrawTwo(ctx, payload)
		}
		ctx.write_Integer(payload.id);
	},

	write_Value: function(ctx, payload) {
		ctx.write_Integer(payload.value);
		ctx.write_String(payload.color);
	},

	write_Action: function(ctx, payload) {
		ctx.write_String(payload.color);
	},

	write_Reverse: function(ctx, payload) {
		this.write_Action(ctx, payload)
	},

	write_Skip: function(ctx, payload) {
		this.write_Action(ctx, payload)
	},

	write_DrawTwo: function(ctx, payload) {
		this.write_Action(ctx, payload)
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
		var t = ctx.read_Integer(ctx)
		var payload;
		if (t == 0) {
			payload = this.read_Value(ctx)
		}
		if (t == 1) {
			payload = this.read_Action(ctx)
		}
		payload.id = ctx.read_Integer();
		return payload;
	},

	read_Value: function(ctx) {
		var payload = new this.factory.Value();
		payload.value = ctx.read_Integer();
		payload.color = ctx.read_String();
		return payload;
	},

	read_Action: function(ctx) {
		var t = ctx.read_Integer(ctx)
		var payload;
		if (t == 0) {
			payload = this.read_Reverse(ctx)
		}
		if (t == 1) {
			payload = this.read_Skip(ctx)
		}
		if (t == 2) {
			payload = this.read_DrawTwo(ctx)
		}
		payload.color = ctx.read_String();
		return payload;
	},

	read_Reverse: function(ctx) {
		var payload = new this.factory.Reverse();
		return payload;
	},

	read_Skip: function(ctx) {
		var payload = new this.factory.Skip();
		return payload;
	},

	read_DrawTwo: function(ctx) {
		var payload = new this.factory.DrawTwo();
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
