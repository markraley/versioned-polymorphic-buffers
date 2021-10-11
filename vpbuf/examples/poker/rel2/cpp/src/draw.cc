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

// include classes to be serialized
#include "persist.cc"

// buffer management helper classes and functions
#include "buffer_context.cc"

// include output from vpc code generator
#include "vp_poker.cc"
using namespace vp_poker;

#include "utils.cc"

// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   string deck_name;
   int count = 1;

   if (argc == 1) {
      cout << "usage: draw <deck_name> [<card_count>]\n";
   } else {
      deck_name = argv[1];

      if (argc == 3)
         count = stoi(argv[2]);

      cout <<"[vrange="<< get_low_version() <<"-"<< get_high_version()
               <<", cpp] DRAW " << count <<" cards"<<endl;

      // load the specified deck

      Deck *deck = load_deck(deck_name);

      if (!deck)
         exit(1);

      // modify the deck by removing cards

      if (deck->cards.size() < count) {
         cout << "too few cards remaining\n";
      } else {
         cout <<"card pop:";
         for (auto i = 0; i < count; i++) {
            Card *c =  deck->cards.back();
            cout <<" "<< c->get_name();
            deck->cards.pop_back();
         }
         cout <<endl;

         // write the modified deck back out

         save_deck(deck_name, *deck);

         cout <<"cards left "<< deck->cards.size() <<endl;
      }
   }
}

// -----------------------------------------------------------------------------