#!/usr/bin/nodejs
// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

"use strict";

const persist = require("./persist");
var tools = require('./tools');
var vp = require('./vp_poker');
var read_context = require('./read_context');
var write_context = require('./write_context');

// ---------------------------------------------------------------------

(function() {
    var library = {
        draw_count: 1,
        file_name: '',

        save_deck: function(file_name, deck) {
            var v = vp.get_high_version()
            var h = new persist.Header(v, 'VP_POKER')

            vp.write_Header(1, write_context, h) // always version 1
            vp.write_Deck(v, write_context, deck)

            var bytes_out = write_context.write_File(file_name)
            console.log('write: ' + file_name + ', version=' + v
                        + ', cards=' + deck.cards.length
                        + ', bytes=' + bytes_out)
        },

        on_read_complete: function(data) {
            read_context.dv = new DataView(tools.toArrayBuffer(data));
            read_context.cur_pos = 0;
            vp.factory = persist

            library.hh = vp.read_Header(1, read_context) // always version 1

            if (!vp.version_check(library.hh.version)) {
                console.log('version mismatch')
                return
            } else {
                var v = library.hh.version
                library.deck = vp.read_Deck(v, read_context)

                console.log('read: ' + library.file_name + ', version=' + v
                            + ', cards=' + library.deck.cards.length
                            + ', bytes=' + data.length)

                if (library.draw_count > library.deck.cards.length) {
                    console.log('not enough cards left')
                } else {

                    // modify the deck by removing cards

                    for (var i = 0; i < library.draw_count; i++) {
                        var c = library.deck.cards.pop()
                        console.log('draw: ' + c.get_name())
                    }

                    // write the modified deck back out

                    library.save_deck(library.file_name, library.deck)
                }
            }
        }
    };

    // -----------------------------------------------------------------
    // begin command line processing

    const args = process.argv.slice(2)

    if (args.length == 0) {
        console.log('usage is: draw <deck_name> [ <card_count> ]')
    } else {
        var deck_name = args[0]
        var count = 1

        if (args.length > 1)
            count = args[1]

        library.draw_count = count
        library.file_name = deck_name

        // load the specified deck

        tools.read_File(deck_name, library.on_read_complete);
    }
})();

// ---------------------------------------------------------------------

