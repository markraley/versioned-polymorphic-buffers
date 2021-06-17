#!/usr/bin/nodejs
// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

"use strict";

const persist = require("./persist");

// ---------------------------------------------------------------------

(function() {
    var library = {
        build_poker_deck: function(max_count) {
            var d = new persist.Deck()
            var count = 0

            for (const i of persist.suit_arr) {
                for (const j of persist.rank_arr) {
                    if (++count > max_count)
                        return d
                    var c = new persist.Card('' + j + ' of ' + i, count)
                    d.cards.push(c)
                }
            }
            return d
        }
    };

    // -----------------------------------------------------------------
    // begin command line processing

    const args = process.argv.slice(2)

    if (args.length == 0) {
        console.log('usage is: stack <deck_name> [ <card_count> ]')
    } else {
        var deck_name = args[0]
        var count = 3

        if (args.length > 1)
            count = args[1]

        var deck = library.build_poker_deck(count)

        persist.save_deck(deck_name, deck)
    }
})();

// ---------------------------------------------------------------------

