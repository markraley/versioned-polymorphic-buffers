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

    D1: function(i = 1, s = "not set") {
        this.apod = new module.exports.A(i + 5, 'apod' + s)
        this.i = i
        this.s = s
        this.aref = new module.exports.A(i - 5, 'aref' + s)
    },

    OuterA: function() {
        this.lookup = {}
    },

    OuterB: function() {
        this.lookup = {}
    },

    OuterC: function() {
        this.lookup = {}
    },

    OuterD: function() {
        this.lookup = {}
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
    }
};


module.exports.Derived1.prototype = Object.create(module.exports.Base.prototype);
module.exports.Derived1.prototype.constructor = module.exports.Derived1;

module.exports.Derived2.prototype = Object.create(module.exports.Base.prototype);
module.exports.Derived2.prototype.constructor = module.exports.Derived2;