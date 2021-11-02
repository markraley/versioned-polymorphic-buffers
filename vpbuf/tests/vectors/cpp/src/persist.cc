// Software released under the MIT license (see project root for license file)

class Header {
   public:
      int version;
      std::string test_name;
};

class A {
   public:
      int i1;
      std::string s1;
};

class OuterA {
   public:
      std::vector<A *> v;
};

class OuterB {
   public:
      std::vector<A> v;
};

class OuterC {
   public:
      std::vector<std::string> v;
};

class OuterD {
   public:
      std::vector<std::string *> v;
};

class OuterE {
   public:
      std::vector<int> v;
};

class OuterF {
   public:
      std::vector<int *> v;
};

class Base {
   public:
      virtual int get_i() = 0;
      virtual string get_s() = 0;
      virtual ~Base() = 0;
};

Base::~Base() {}

class Derived1 : public Base {
   public:
      Derived1(int i, std::string s) : i1(i), s1(s) {}
      Derived1() : i1(0), s1("") {}

      int get_i() {return i1;};
      string get_s() {return s1;}

      ~Derived1() {}
      int i1;
      string s1;
};

class Derived2 : public Base {
   public:
      Derived2(int i, std::string s) : i1(i), s1(s) {}
      Derived2() : i1(0), s1("") {}

      int get_i() {return i1;};
      string get_s() {return s1;}

      ~Derived2() {}
      int i1;
      string s1;
};

class OuterG {
   public:
      std::vector<Base *> v;
};

// -----------------------------------------------------------------------------

class ReorderCog {
   public:
      virtual vector<int> operator ()() = 0;
      virtual ~ReorderCog();
};

ReorderCog::~ReorderCog() {}

class Shaker {
   public:
      virtual string operator ()() = 0;
      virtual ~Shaker();
};

Shaker::~Shaker() {}

// -----------------------------------------------------------------------------

class IdentityReorderCog : public ReorderCog {
   public:
      vector <int> base_list;

   public:
      IdentityReorderCog(vector <int> const &v) : base_list(v) { };

      vector<int> operator ()() {
         return base_list;
      }
};

// -----------------------------------------------------------------------------

