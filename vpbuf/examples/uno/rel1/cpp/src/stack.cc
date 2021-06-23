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
   vector<Card *> build_arr;

   for (auto c = 0; c < color_arr.size(); c++) {
      for (auto k = 0; k < 2; k++) {
         build_arr.push_back(new Skip(++count, color_arr[c]));
         build_arr.push_back(new Reverse(++count, color_arr[c]));
         build_arr.push_back(new DrawTwo(++count, color_arr[c]));
      }

      build_arr.push_back(new Value(++count, 0, color_arr[c]));

      for (auto k = 1; k < 10; k++) {
         build_arr.push_back(new Value(++count, k, color_arr[c]));
         build_arr.push_back(new Value(++count, k, color_arr[c]));
      }
   }

   deck->cards = vector<Card *>(build_arr.begin() + (build_arr.size() - max_cards)
                                 , build_arr.end());

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