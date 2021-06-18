const fs = require('fs');
"use strict";

module.exports = {
    read_File: function(file_name, callback) {
        fs.readFile(file_name,
            function(err, data) {
                if (err)
                    console.log('read_File: error', err);
                // TODO: better error handling
                callback(data);
            }
        );
    },

    makeBytesFromHexString: function(s) {
          s = s.replace(/\s+/g, '');
          var a2 = new Uint8Array(s.length/2);
          for (var i=0; i<s.length/2; i++) {
            a2[i] = parseInt(s.substr(i*2,2), 16);
          }
          return a2.buffer;
        },
    hexDump: function(v, log) {
        var r = '';
        var byte = function(v) {
        return ('00' + v.toString(16)).substr(-2) + ' ';
        };
        switch (typeof v) {
        case 'string':
        case 'number':
          var hex = v.toString(16);
          hex = ((1 === hex.length % 2) ? '0' : '') + hex;
          r += hex.replace(/[0-9a-f]{2}/ig, '$& ');
          break;
        case 'undefined':
          r += 'undefined';
          break;
        case 'object':
          if (null === v) {
            r += '<null>';
            break;
          }
          switch (v.constructor.name) {
            case 'Uint8Array':
              for (var i=0; i<v.length; i++) {
                r += byte(v[i]);
              }
              break;
            case 'ArrayBuffer':
              var dv = new DataView(v);
              for (var i=0; i<v.byteLength; i++) {
                r += byte(dv.getUint8(i));
              }
              break;
            default:
              r += '<unsupported type: object:'+ v.constructor.name +'>';
              break;
          }
          break;
        default:
          r += '<unsupported type: '+ typeof v +'>';
          break;
        }
        if (log) console.log('hexDump: '+ r);
        return r;
    },

    toArrayBuffer: function (buf) {
//      console.log('toArrayBuffer:', buf.length);
        var ab = new ArrayBuffer(buf.length);
        var view = new Uint8Array(ab);
        for (var i = 0; i < buf.length; ++i) {
            view[i] = buf[i];
        }
        return ab;
    }

};