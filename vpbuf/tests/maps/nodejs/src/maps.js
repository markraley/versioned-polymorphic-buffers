#!/usr/bin/nodejs
// Software released under the MIT license (see project root for license file)

var persist = require("./persist");
var vp = require('./vp_maps');

var read_context = require('./read_context');
var write_context = require('./write_context');
var tools = require('./tools');

const assert = require('chai').assert;
const out_dir = './out/';

// ---------------------------------------------------------------------
// maps_A -

(function() {
    var Test_maps_A = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'maps_A',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_maps_A.h, Test_maps_A.hh);
            assert.deepEqual(Test_maps_A.aa, Test_maps_A.aa);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.a = new persist.OuterA();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.a.lookup[j] = new persist.A(j, 'A-' + j);
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterA(1, write_context, this.a);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_maps_A.hh = vp.read_Header(1, read_context);
            Test_maps_A.aa = vp.read_OuterA(1, read_context);

            console.log(Test_maps_A.test_name, data.length, 'bytes read');

            Test_maps_A.validate();
        }
    };

    vp.factory = persist // set factory

    Test_maps_A.serialize();

    tools.read_File(out_dir + Test_maps_A.test_name + '.dat',
                                Test_maps_A.on_read_complete);
})();

// ---------------------------------------------------------------------
