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
            assert.deepEqual(Test_maps_A.a, Test_maps_A.aa);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.a = new persist.OuterA();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.a.lookup[j] = new persist.A(j, 'A-' + j);
            }

            write_context.init(1);

            vp.write_Header(write_context, this.h);
            vp.write_OuterA(write_context, this.a);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.init(data, 1);

            Test_maps_A.hh = vp.read_Header(read_context);
            Test_maps_A.aa = vp.read_OuterA(read_context);

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
// maps_B -

(function() {
    var Test_maps_B = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'maps_B',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_maps_B.h, Test_maps_B.hh)
            assert.deepEqual(Test_maps_B.b, Test_maps_B.bb)
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.b = new persist.OuterB();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i
                this.b.lookup['' + j] = new persist.A(j, 'B-' + j)
            }

            write_context.init(1);

            vp.write_Header(write_context, this.h);
            vp.write_OuterB(write_context, this.b);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.init(data, 1);

            Test_maps_B.hh = vp.read_Header(read_context);
            Test_maps_B.bb = vp.read_OuterB(read_context);

            console.log(Test_maps_B.test_name, data.length, 'bytes read');

            Test_maps_B.validate();
        }
    };

    vp.factory = persist // set factory

    Test_maps_B.serialize();

    tools.read_File(out_dir + Test_maps_B.test_name + '.dat',
                                Test_maps_B.on_read_complete);
})();

// ---------------------------------------------------------------------
// map_C -

(function() {
    var Test_map_C = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'maps_C',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_map_C.h, Test_map_C.hh);
            assert.deepEqual(Test_map_C.c, Test_map_C.cc);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.c = new persist.OuterA();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.c.lookup[j] = 'C-' + j;
            }

            write_context.init(1);

            vp.write_Header(write_context, this.h);
            vp.write_OuterC(write_context, this.c);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.init(data, 1);

            Test_map_C.hh = vp.read_Header(read_context);
            Test_map_C.cc = vp.read_OuterC(read_context);

            console.log(Test_map_C.test_name, data.length, 'bytes read');

            Test_map_C.validate();
        }
    };

    vp.factory = persist // set factory

    Test_map_C.serialize();

    tools.read_File(out_dir + Test_map_C.test_name + '.dat',
                                Test_map_C.on_read_complete);
})();

// ---------------------------------------------------------------------
// maps_D -

(function() {
    var Test_maps_D = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'maps_D',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_maps_D.h, Test_maps_D.hh)
            assert.deepEqual(Test_maps_D.b, Test_maps_D.bb)
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.b = new persist.OuterB();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i
                this.b.lookup['' + j] = new persist.D1(j, 'D1-' + j)
            }

            write_context.init(1);

            vp.write_Header(write_context, this.h);
            vp.write_OuterD(write_context, this.b);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.init(data, 1);

            Test_maps_D.hh = vp.read_Header(read_context);
            Test_maps_D.bb = vp.read_OuterD(read_context);

            console.log(Test_maps_D.test_name, data.length, 'bytes read');

            Test_maps_D.validate();
        }
    };

    vp.factory = persist // set factory

    Test_maps_D.serialize();

    tools.read_File(out_dir + Test_maps_D.test_name + '.dat',
                                Test_maps_D.on_read_complete);
})();

// ---------------------------------------------------------------------
// maps_E -

(function() {
    var Test_maps_E = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'maps_E',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_maps_E.h, Test_maps_E.hh);
            assert.deepEqual(Test_maps_E.a, Test_maps_E.aa);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.a = new persist.Omlette();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.a.lookup[j] = new persist.Egg(j, 'EGG-' + j);
            }

            write_context.init(1);

            write_context.salt_map['SaltShaker'] = persist.SaltShaker(1);
            write_context.salt_map['PepperShaker'] = persist.PepperShaker(1);

            vp.write_Header(write_context, this.h);
            vp.write_Omlette(write_context, this.a);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.init(data, 1);

            read_context.salt_map['SaltShaker'] = persist.SaltShaker(1);
            read_context.salt_map['PepperShaker'] = persist.PepperShaker(1);

            Test_maps_E.hh = vp.read_Header(read_context);
            Test_maps_E.aa = vp.read_Omlette(read_context);

            console.log(Test_maps_E.test_name, data.length, 'bytes read');

            Test_maps_E.validate();
        }
    };

    vp.factory = persist // set factory

    Test_maps_E.serialize();

    tools.read_File(out_dir + Test_maps_E.test_name + '.dat',
                                Test_maps_E.on_read_complete);
})();

// ---------------------------------------------------------------------
