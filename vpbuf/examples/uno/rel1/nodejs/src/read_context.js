// Software released under the MIT license (see project root for license file)

const assert = require('chai').assert;
"use strict";

var persist = require("./persist");
var vp = require('./vp_uno');
var tools = require('./tools');

(function() {
    var rc = {
        ver: 1,
        cur_pos: 0,
        dv: new DataView(new ArrayBuffer()),
        reorder_map: {},

        init: function(data, ver = 1) {
            this.dv = new DataView(tools.toArrayBuffer(data));
            this.cur_pos = 0;
            this.set_version(ver);
        },

        set_version: function(ver) {
            this.ver = ver;
            vp.init_reorder_map(this.reorder_map, ver);
        },

        _read_Integer: function() {
            var result = 0, varLen = 0;

            while (varLen++ < 3 && ((b = this.dv.getUint8(this.cur_pos)) & 0x80) !== 0) {
              result <<= 7;
              result |= (b & 0x7F);
              this.cur_pos += 1;
            }

            result <<= (varLen <= 3 ? 7: 8);
            result |= this.dv.getUint8(this.cur_pos++);

            result <<= 3;
            result >>= 3;

            return result;
        },

        read_Integer: function() {
            var tag = this._read_Integer();
            assert(tag, 4); // integer tag is 4
            return this._read_Integer();
        },

        _read_String: function() {
            var s = [];
            var l = this._read_Integer();
            for (var i = 0; i < (l >> 1); i++) {
                b = this.dv.getUint8(this.cur_pos++);
                s += (String.fromCharCode(b));
            }
            r = String(s);

            return r;
        },

        read_String: function() {
            var tag = this._read_Integer();
            assert(tag, 6); // string tag is 6
            return this._read_String();
        }
    };

    return module.exports = rc;
})();