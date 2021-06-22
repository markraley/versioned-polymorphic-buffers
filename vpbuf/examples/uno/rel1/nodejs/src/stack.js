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
            var count = 0

            for (const c of persist.color_arr) {
                if (++count > max_count)
                    return d
                d.cards.push(new persist.Skip(count, c))

                if (++count > max_count)
                    return d
                d.cards.push(new persist.Reverse(count, c))

                for (var k = 0; k < 10; k++) {
                    if (++count > max_count)
                        return d
                    d.cards.push(new persist.Value(count, k, c))
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

        console.log('[vrange='+ vp.get_low_version() +'-'+ vp.get_high_version()
                            +', nodejs] STACK '+ count + ' cards')

        var deck = library.build_uno_deck(count)

        persist.save_deck(deck_name, deck)
    }
})();

// ---------------------------------------------------------------------

