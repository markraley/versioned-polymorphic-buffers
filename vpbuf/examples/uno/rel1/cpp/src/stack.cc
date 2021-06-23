// Software released under the MIT license (see project root for license file)

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <typeindex> // needed for class polymorphism

using namespace std;

typedef char byte;
typedef vector<byte> ByteVec;

// buffer management helper classes and functions
#include "buffer_context.cc"

// include classes to be serialized
#include "persist.cc"

// -----------------------------------------------------------------------------

Deck *build_uno_deck(int max_cards) {
   Deck *deck = new Deck;
   int count = 0;

   for (auto i = 0; i < suit_arr.size(); i++) {
      for (auto j = 0; j < rank_arr.size(); j++) {
         count += 1;
         if (count > max_cards)
            return deck;
//         Card *card = new Value(count, 3, "Red");
         Card *card = new Reverse(count, "Green");
         deck->cards.push_back(card);
      }
   }
   return deck;
}

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   string deck_name;
   int count = 3;

   if (argc == 1) {
      cout << "usage: stack <deck_name> [<card_count>]\n";
   } else {

      deck_name = argv[1];

      if (argc == 3)
         count = stoi(argv[2]);

      cout <<"[vrange="<< get_low_version() <<"-"<< get_high_version()
               <<", cpp] STACK " << count <<" cards"<<endl;

      Deck *deck = build_uno_deck(count);

      size_t bytes_out = save_deck(deck_name, *deck);

      delete deck;
   }
}

// -----------------------------------------------------------------------------