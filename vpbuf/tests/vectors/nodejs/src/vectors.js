// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

var persist = require("./persist");
var vp = require('./vp_vectors');

var read_context = require('./read_context');
var write_context = require('./write_context');
var tools = require('./tools');

const assert = require('chai').assert;
const out_dir = './out/';

// ---------------------------------------------------------------------
// vectors_A - test vector of pointer to struct

(function() {
    var Test_vectors_A = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'vectors_A',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_A.h, Test_vectors_A.hh);
            assert.deepEqual(Test_vectors_A.g, Test_vectors_A.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterA();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push(new persist.A(j, 'A-' + j));
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterA(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_A.hh = vp.read_Header(1, read_context);
            Test_vectors_A.gg = vp.read_OuterA(1, read_context);

            console.log(Test_vectors_A.test_name, data.length, 'bytes read');

            Test_vectors_A.validate();
        }
    };

    vp.factory = persist // set factory

    Test_vectors_A.serialize();

    tools.read_File(out_dir + Test_vectors_A.test_name + '.dat',
                                Test_vectors_A.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_B - test vector of struct

(function() {
    var Test_vectors_B = {
        count: 10,
        base: 50000,
        version: -99,
        test_name: 'vectors_B',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_B.h, Test_vectors_B.hh);
            assert.deepEqual(Test_vectors_B.g, Test_vectors_B.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterB();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push(new persist.A(j, 'A-' + j));
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterB(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_B.hh = vp.read_Header(1, read_context);
            Test_vectors_B.gg = vp.read_OuterB(1, read_context);

            console.log(Test_vectors_B.test_name, data.length, 'bytes read');

            Test_vectors_B.validate();
        }
    };

    Test_vectors_B.serialize();

    tools.read_File(out_dir + Test_vectors_B.test_name + '.dat',
                                Test_vectors_B.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_C - test vector of string

(function() {
    var Test_vectors_C = {
        count: 13,
        base: 113,
        version: 101,
        test_name: 'vectors_C',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_C.h, Test_vectors_C.hh);
            assert.deepEqual(Test_vectors_C.g, Test_vectors_C.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterC();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push('C-' + j);
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterC(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_C.hh = vp.read_Header(1, read_context);
            Test_vectors_C.gg = vp.read_OuterC(1, read_context);

            console.log(Test_vectors_C.test_name, data.length, 'bytes read');

            Test_vectors_C.validate();
        }
    };

    Test_vectors_C.serialize();

    tools.read_File(out_dir + Test_vectors_C.test_name + '.dat',
                                Test_vectors_C.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_D - test vector of pointer to string

(function() {
    var Test_vectors_D = {
        count: 13,
        base: 113,
        version: 101,
        test_name: 'vectors_D',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_D.h, Test_vectors_D.hh);
            assert.deepEqual(Test_vectors_D.g, Test_vectors_D.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterD();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push('D-' + j);
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterD(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_D.hh = vp.read_Header(1, read_context);
            Test_vectors_D.gg = vp.read_OuterD(1, read_context);

            console.log(Test_vectors_D.test_name, data.length, 'bytes read');

            Test_vectors_D.validate();
        }
    };

    Test_vectors_D.serialize();

    tools.read_File(out_dir + Test_vectors_D.test_name + '.dat',
                                Test_vectors_D.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_E - test vector of integer

(function() {
    var Test_vectors_E = {
        count: 76,
        base: 112,
        version: 1121,
        test_name: 'vectors_E',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_E.h, Test_vectors_E.hh);
            assert.deepEqual(Test_vectors_E.g, Test_vectors_E.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterE();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push(j);
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterE(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_E.hh = vp.read_Header(1, read_context);
            Test_vectors_E.gg = vp.read_OuterE(1, read_context);

            console.log(Test_vectors_E.test_name, data.length, 'bytes read');

            Test_vectors_E.validate();
        }
    };

    Test_vectors_E.serialize();

    tools.read_File(out_dir + Test_vectors_E.test_name + '.dat',
                                Test_vectors_E.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_F - test vector of pointer to integer

(function() {
    var Test_vectors_F = {
        count: 76,
        base: 112,
        version: 1121,
        test_name: 'vectors_F',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_F.h, Test_vectors_F.hh);
            assert.deepEqual(Test_vectors_F.g, Test_vectors_F.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterF();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push(j);
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterF(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_F.hh = vp.read_Header(1, read_context);
            Test_vectors_F.gg = vp.read_OuterF(1, read_context);

            console.log(Test_vectors_F.test_name, data.length, 'bytes read');

            Test_vectors_F.validate();
        }
    };

    Test_vectors_F.serialize();

    tools.read_File(out_dir + Test_vectors_F.test_name + '.dat',
                                Test_vectors_F.on_read_complete);
})();

// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// vectors_G - test vector of pointer to polymorphic class

(function() {
    var Test_vectors_G = {
        count: 17,
        base: 500,
        version: 1,
        test_name: 'vectors_G',

        // vars h and g are initialized and serialized to buffer, then file
        // vars hh and gg are deserializations of the same

        validate: function() {
            assert.deepEqual(Test_vectors_G.h, Test_vectors_G.hh);
            assert.deepEqual(Test_vectors_G.g, Test_vectors_G.gg);
        },

        serialize: function() {
            this.h = new persist.Header(this.version, this.test_name);
            this.g = new persist.OuterG();

            for (var i = 0; i < this.count; i++) {
                var j = this.base + i;
                this.g.v.push(new persist.Derived1(j, 'D1-' + j));
                this.g.v.push(new persist.Derived2(j, 'D2-' + j));
            }

            write_context.buf_arr = [];
            vp.write_Header(1, write_context, this.h);
            vp.write_OuterG(1, write_context, this.g);

            bytes_out = write_context.write_File(out_dir
                                                    + this.test_name + '.dat');

            console.log(this.test_name, bytes_out, 'bytes written');
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;

            Test_vectors_G.hh = vp.read_Header(1, read_context);
            Test_vectors_G.gg = vp.read_OuterG(1, read_context);

            console.log(Test_vectors_G.test_name, data.length, 'bytes read');

            Test_vectors_G.validate();
        }
    };

    Test_vectors_G.serialize();

    tools.read_File(out_dir + Test_vectors_G.test_name + '.dat',
                                Test_vectors_G.on_read_complete);
})();
// ---------------------------------------------------------------------
