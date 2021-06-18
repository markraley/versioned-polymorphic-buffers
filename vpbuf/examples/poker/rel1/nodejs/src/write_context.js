// Software released under the MIT license (see project root for license file)

const fs = require('fs');
const assert = require('chai').assert;
"use strict";

(function() {
    var wc = {
        buf_arr: [],
        _write_Integer: function(i) {
//          console.log('writing i', i);
            if (i >= 0 && i <= 0x7F) {
                this.buf_arr.push(new Uint8Array([i]));
            } else if (i > 0x7F && i <= 0x3FFF) {
                this.buf_arr.push(new Uint8Array([
                                    (i >> 7) | 0x80,
                                    i & 0x7F
                                ])
                            );
            } else if (i > 0x3FFF && i <= 0x1FFFFF) {
                this.buf_arr.push(new Uint8Array([
                                     (i >> 14) | 0x80,
                                    ((i >> 7) & 0x7F) | 0x80,
                                    i & 0x7F
                                ])
                            );
            } else {
                this.buf_arr.push(new Uint8Array([
                                     (i >> 21) | 0x80,
                                    ((i >> 14) & 0x7F) | 0x80,
                                    ((i >> 7 ) & 0x7F) | 0x80,
                                    i & 0xFF
                                ])
                            );
            }

        },

        write_Integer: function(i) {
            this._write_Integer(4); // tag
            this._write_Integer(i);
        },

        _write_String: function(s) {
            this._write_Integer((s.length << 1) | 0x1);
            var byte_arr = [];
            for (var i = 0; i < s.length; i++) {
                var code = s.charCodeAt(i);
                byte_arr.push(code);
            }
    //          console.log('bytes', byte_arr.join(', '));
            this.buf_arr.push(new Uint8Array(byte_arr));
        },

        write_String: function(s) {
            this._write_Integer(6); // tag
            this._write_String(s);
        },

        write_File: function(file_name) {

            var all_bytes = [];
            for (var i = 0; i < this.buf_arr.length; i++) {
                    all_bytes.push(...this.buf_arr[i]);
            }

//          for (var i = 0; i < this.buf_arr.length; i++) {
//              console.log(tools.hexDump(this.buf_arr[i]));
//          }

            var buf = Buffer.from(all_bytes, 'binary');

            fs.writeFile(file_name, buf,
                function(err) {
                    if (err)
                        console.log('write_File: error', err);
                }
            )

            return buf.length;

        }
    };
    return module.exports = wc;
})();