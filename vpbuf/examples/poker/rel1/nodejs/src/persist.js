// Software released under the MIT license (see project root for license file)

const fs = require('fs');
var read_context = require('./read_context');
var write_context = require('./write_context');
var vp = require('./vp_poker');

// -----------------------------------------------------------------------------

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
    },

// -----------------------------------------------------------------------------

    save_deck: function(file_name, deck) {
        var v = vp.get_high_version()
        var h = new this.Header(v, 'VP_POKER')

        vp.write_Header(1, write_context, h) // always version 1
        vp.write_Deck(v, write_context, deck)

        var bytes_out = write_context.write_File(file_name)
        console.log('write: ' + file_name + ', version=' + v
                    + ', cards=' + deck.cards.length
                    + ', bytes=' + bytes_out)
    },

// -----------------------------------------------------------------------------

    read_File: function(file_name, callback) {
        fs.readFile(file_name,
            function(err, data) {
                if (err)
                    console.log('read_File: error', err);
                // TODO: better error handling
                callback(data);
            }
        );
    },

    toArrayBuffer: function (buf) {
//      console.log('toArrayBuffer:', buf.length);
        var ab = new ArrayBuffer(buf.length);
        var view = new Uint8Array(ab);
        for (var i = 0; i < buf.length; ++i) {
            view[i] = buf[i];
        }
        return ab;
    },

    on_read_complete: function(data) {
        read_context.dv = new DataView(this.context.toArrayBuffer(data));
        read_context.cur_pos = 0;

        this.hh = vp.read_Header(1, read_context) // always version 1

        if (!vp.version_check(this.hh.version)) {
            console.log('version mismatch')
            return
        } else {
            var v = this.hh.version
            this.deck = vp.read_Deck(v, read_context)

            console.log('read: ' + this.file_name + ', version=' + v
                        + ', cards=' + this.deck.cards.length
                        + ', bytes=' + data.length)

            if (this.draw_count > this.deck.cards.length) {
                console.log('not enough cards left')
            } else {

                // modify the deck by removing cards

                for (var i = 0; i < this.draw_count; i++) {
                    var c = this.deck.cards.pop()
                    console.log('draw: ' + c.get_name())
                }

                // write the modified deck back out

                this.context.save_deck(this.file_name, this.deck)
            }
        }
    }
};
