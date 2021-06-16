// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

using namespace std;

vector<string> suit_arr = {"Diamonds", "Clubs", "Hearts", "Spades" };
vector<string> rank_arr = {"Ace", "Two", "Three", "Four", "Five",
                           "Six", "Seven", "Eight", "Nine", "Ten",
                           "Jack", "Queen", "King"};

class Header {
   public:
      int version;
      std::string tag;
};

class Card {
   public:
      Card(string name = "not set", int id = 0): name(name), id(id) {};
      string get_name() { return string(this->name); };
      std::string name;
      int id;
};

class Deck {
   public:
      Deck() { }
      std::vector<Card *> cards;

      ~Deck() {
         for (auto i = 0; i < cards.size(); i++)
            delete cards[i];
      }
};

// include output from vpc code generator
#include "vp_poker.cc"
using namespace vp_poker;

// -----------------------------------------------------------------------------

size_t save_deck(string deck_name, Deck &deck) {
   Header header;
   header.version = 1;
   header.tag = "VP_POKER";
   write_context wc;

   write_Header(1, wc, header); // always version 1
   write_Deck(get_high_version(), wc, deck);

   return wc.write_file(deck_name);
}

// -----------------------------------------------------------------------------

Deck *load_deck(string deck_name) {
   Deck *deck = NULL;
   Header header;

   read_context rc(deck_name);
   read_Header(1, rc, header);

   if (!version_check(header.version)) {
      cout << "version out of range\n";
   } else {
      deck = new Deck();
      read_Deck(header.version, rc, *deck);
   }

   return deck;
}

// -----------------------------------------------------------------------------