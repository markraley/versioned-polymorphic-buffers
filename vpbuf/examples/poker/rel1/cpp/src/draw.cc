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

// include output from vpc code generator
#include "vp_poker.cc"
using namespace vp_poker;

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

      cout <<"draw "<< count << endl;

      // load the specified deck

      Deck *deck = load_deck(deck_name);

      // modify the deck by removing cards

      if (deck->cards.size() < count) {
         cout << "too few cards remaining\n";
      } else {
         cout <<"(cpp) draw:";
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