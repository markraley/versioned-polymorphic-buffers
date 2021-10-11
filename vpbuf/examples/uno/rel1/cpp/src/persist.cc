// Software released under the MIT license (see project root for license file)

using namespace std;

vector<string> color_arr = {"Red", "Yellow", "Green", "Blue" };

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

      string get_name()
         { return string(this->color) +" "+ to_string(this->value);};
};

class Action : public Card {
   public:
      string color, name;
      Action(int id = -1, string color = "not set", string name = "not set")
         : Card(id), color(color), name(name) {};
      string get_name() { return string(this->color +" "+ this->name); }
      virtual ~Action() = 0;
};

Action::~Action() {}

class Reverse : public Action {
   public:
      Reverse(int id = -1, string color = "not set")
         : Action(id, color, "Reverse") {}
};

class Skip : public Action {
   public:
      Skip(int id = -1, string color = "not set")
         : Action(id, color, "Skip") {}
};

class DrawTwo : public Action {
   public:
      DrawTwo(int id = -1, string color = "not set")
         : Action(id, color, "DrawTwo") {}
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

// -----------------------------------------------------------------------------
