#!/usr/bin/nodejs
// Software released under the MIT license (see project root for license file)

"use strict";

const persist = require("./persist");
var vp = require('./vp_uno');

// ---------------------------------------------------------------------

(function() {
    var library = {
        build_uno_deck: function(max_count) {
            var d = new persist.Deck()
            var build_arr = []
            var count = 0

            for (const c of persist.color_arr) {

                for (var k = 0; k < 2; k++) {
                    build_arr.push(new persist.Skip(++count, c))
                    build_arr.push(new persist.Reverse(++count, c))
                    build_arr.push(new persist.DrawTwo(++count, c))
                }

                build_arr.push(new persist.Value(++count, 0, c))

                for (var k = 1; k < 10; k++) {
                    build_arr.push(new persist.Value(++count, k, c))
                    build_arr.push(new persist.Value(++count, k, c))
                }
            }

            d.cards = build_arr.slice(count - max_count)

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

        console.log('[vrange='+ vp.get_low_version() +'-'+ vp.get_high_version()
                            +', nodejs] STACK '+ count + ' cards')

        var deck = library.build_uno_deck(count)

        persist.save_deck(deck_name, deck)
    }
})();

// ---------------------------------------------------------------------

