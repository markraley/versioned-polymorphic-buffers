#!/usr/bin/nodejs
// Software released under the MIT license (see project root for license file)

const persist = require("./persist");
var vp = require('./vp_poker');

// ---------------------------------------------------------------------

(function() {
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

        console.log('draw ' + count)

        // set some variables as read callback will run in this context

        this.draw_count = count
        this.file_name = deck_name
        this.context = persist

        // load the specified deck

        vp.factory = persist // set class factory
        persist.read_File(deck_name, persist.on_read_complete);
    }
})();

// ---------------------------------------------------------------------

