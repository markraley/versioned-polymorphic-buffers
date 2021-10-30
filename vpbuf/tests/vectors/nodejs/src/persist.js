// Software released under the MIT license (see project root for license file)

module.exports = {
    Header: function(version = 1, test_name = "not set") {
        this.version = version;
        this.test_name = test_name;
    },

    A: function (i1 = 1, s1 = "not set") {
        this.i1 = i1;
        this.s1 = s1;
    },

    OuterA: function() {
        this.v = [];
    },

    OuterB: function() {
        this.v = [];
    },

    OuterC: function() {
        this.v = [];
    },

    OuterD: function() {
        this.v = [];
    },

    OuterE: function() {
        this.v = [];
    },

    OuterF: function() {
        this.v = [];
    },

    Base: function() {
        this.i = 0;
    },

    Derived1: function(i1 = 1, s1 = "Derived1") {
        module.exports.Base.call(this);
        this.i1 = i1;
        this.s1 = s1;
    },

    Derived2: function(i2 = 2, s2 = "Derived2") {
        module.exports.Base.call(this);
        this.i1 = i2;
        this.s1 = s2;
    },

    OuterG: function() {
        this.v = [];
    },

// -----------------------------------------------------------------------------

    IdentityScrambler: function(base_arr) {
        return function() {
            var tmp = base_arr.slice()
            return tmp
        }
    },

    EggScrambler: function(base_arr, seed = 1) {
        return function() {
            var tmp = base_arr.slice()
            var j = tmp.length - 1

            while (j > 0) {
                seed = (seed * 61) % 233
                var i = seed % j

                var xchg = tmp[j]
                tmp[j] = tmp[i]
                tmp[i] = xchg

                j -= 1
            }

            return tmp
        }
    },

// -----------------------------------------------------------------------------

    SaltShaker: function(seed = 1) {
        return function() {
            seed = (seed * 53) % 113
            return "SALT-" + seed;
        }
    },

    PepperShaker: function(seed = 1) {
        return function() {
            seed = (seed * 47) % 199
            return "PEPPER-" + seed;
        }
    }

// -----------------------------------------------------------------------------

};


module.exports.Derived1.prototype = Object.create(module.exports.Base.prototype);
module.exports.Derived1.prototype.constructor = module.exports.Derived1;

module.exports.Derived2.prototype = Object.create(module.exports.Base.prototype);
module.exports.Derived2.prototype.constructor = module.exports.Derived2;

// -----------------------------------------------------------------------------
