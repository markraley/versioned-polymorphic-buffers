// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

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

      // load the specified deck

      Deck *deck = load_deck(deck_name);

      // modify the deck by removing cards

      if (deck->cards.size() < count) {
         cout << "too foo cards remaining\n";
      } else {
         cout <<"\n";
         for (auto i = 0; i < count; i++) {
            Card *c =  deck->cards.back();
            cout << c->get_name() <<"\n";
            deck->cards.pop_back();
         }

         // write the modified deck back out

         size_t bytes_out = save_deck(deck_name, *deck);
         std::cout << deck_name <<" "<< bytes_out <<" bytes written\n";
      }
   }
}

// -----------------------------------------------------------------------------