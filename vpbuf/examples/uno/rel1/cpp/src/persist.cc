// Software released under the MIT license (see project root for license file)

using namespace std;

vector<string> suit_arr = {"Diamonds", "Clubs", "Hearts", "Spades" };
vector<string> rank_arr = {"Ace", "Two", "Three", "Four", "Five",
                           "Six", "Seven", "Eight", "Nine", "Ten",
                           "Jack", "Queen", "King"};

// -----------------------------------------------------------------------------

class Header {
   public:
      Header(int version = -1, string tag = "not set")
         : version(version), tag(tag) {}
      int version;
      std::string tag;
};

class Card {
   public:
      Card(int id): id(id) {};
      Card() : id(-1) {}
      virtual ~Card() = 0;
      virtual string get_name() = 0;
      int id;
};

Card::~Card() {}

class Value : public Card {
   public:
      int value;
      string color;
      Value(
            int id = -1,
            int value = -1,
            string color = "not set"
         ) : Card(id), value(value), color(color) {};

      string get_name() { return string(this->color); };
};

class Action : public Card {
   public:
      string color;
      Action(int id = -1, string color = "not set")
         : Card(id), color(color) {};
      string get_name() { return string(this->color); }
      virtual ~Action() = 0;
};

Action::~Action() {}

class Reverse : public Action {
   public:
      Reverse(int id = -1, string color = "not set")
         : Action(id, color) {}
};

class Skip : public Action {
   public:
      Skip(int id = -1, string color = "not set")
         : Action(id, color) {}
};

class DrawTwo : public Action {
   public:
      DrawTwo(int id = -1, string color = "not set")
         : Action(id, color) {}
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
#include "vp_uno.cc"
using namespace vp_uno;

// -----------------------------------------------------------------------------

size_t save_deck(string deck_name, Deck &deck) {
   long v = get_high_version();
   Header header(v, "VP_UNO");

   write_context wc;

   write_Header(1, wc, header); // always version 1
   write_Deck(v, wc, deck);

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

   read_context rc(deck_name);
   read_Header(1, rc, header);
   int v = header.version;

   if (!version_check(v)) {
      cout << "version out of range\n";
   } else {
      deck = new Deck();
      read_Deck(v, rc, *deck);

      cout <<"read: "<< deck_name <<", version= "<< v
            <<", cards="<< deck->cards.size()
            <<", bytes="<< rc.buf_arr.size() << endl;
   }

   return deck;
}

// -----------------------------------------------------------------------------