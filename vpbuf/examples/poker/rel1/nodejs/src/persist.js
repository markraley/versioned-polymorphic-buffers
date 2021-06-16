// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

module.exports = {
    suit_arr: [ 'Diamonds', 'Clubs', 'Hearts', 'Spades' ],
    rank_arr: [ 'Ace',   'Two',   'Three', 'Four',
                 'Five',  'Six',   'Seven',
                 'Eight', 'Nine',  'Ten',
                 'Jack',  'Queen', 'King' ],

    Header: function(version = 1, tag = "not set") {
        this.version = version
        this.tag = tag
    },

    Card: function(name = "not set", id = -1) {
        this.name = name
        this.id = id

        this.get_name = function() {
            return this.name
        }
    },

    Deck: function() {
        this.cards = []
    }
};
