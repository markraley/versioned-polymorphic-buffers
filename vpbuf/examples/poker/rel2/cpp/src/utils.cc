// -----------------------------------------------------------------------------

size_t save_deck(string deck_name, Deck &deck) {
   long v = get_high_version();
   Header header(v, "VP_POKER");

   write_context wc(v);

   write_Header(wc, header); // always version 1
   write_Deck(wc, deck);

   size_t bytes_out = wc.write_file(deck_name);

   cout <<"write: "<< deck_name <<", version="<< v
         <<", cards="<< deck.cards.size()
         <<", bytes="<< bytes_out << endl;

   return bytes_out;
}

// -----------------------------------------------------------------------------

Deck *load_deck(string deck_name) {
   Deck *deck = NULL;
   Header header;

   read_context rc(deck_name, 1);
   read_Header(rc, header);
   int v = header.version;

   if (!version_check(v)) {
      cout << "version out of range\n";
   } else {
      deck = new Deck();
      rc.set_version(v);
      read_Deck(rc, *deck);

      cout <<"read: "<< deck_name <<", version= "<< v
            <<", cards="<< deck->cards.size()
            <<", bytes="<< rc.buf_arr.size() << endl;
   }

   return deck;
}

// -----------------------------------------------------------------------------