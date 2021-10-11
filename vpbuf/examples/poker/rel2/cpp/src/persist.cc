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
      Card(string name = "not set", int id = 0): name(name), id(id) {};
      string get_name()
      {
         int i = this->id - 1;
         int l = rank_arr.size();
         return string(rank_arr[i % l]
                        + " of " + suit_arr[i / l]);
      };

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

// -----------------------------------------------------------------------------

class ReorderCog {
   public:
      virtual vector<int> operator ()() = 0;
      virtual string step() = 0;
      virtual ~ReorderCog();
};

ReorderCog::~ReorderCog() {}

// -----------------------------------------------------------------------------