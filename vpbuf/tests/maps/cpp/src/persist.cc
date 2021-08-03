// Software released under the MIT license (see project root for license file)

using namespace std;

class Header {
   public:
      int version;
      string test_name;
};

class A {
   public:
      A(int i = -1, string s = "not set") : i1(i), s1(s) {}
      int i1;
      string s1;
};

class D1 {
   public:
      D1(int i = -1, string s = "not set")
         : i(i), s(s), aref(new A(i-5, "aref" + s)), apod(i+5, "apod" + s) {}
      A apod;
      int i;
      string s;
      A *aref;
};

class OuterA {
   public:
      map<int, A *> lookup;
};

class OuterB {
   public:
      map<string, A *> lookup;
};

class OuterC {
   public:
      map<int, string> lookup;
};

class OuterD {
   public:
      map<string, D1 *> lookup;
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

      virtual ~Derived1() {}
         int i1;
         string s1;
};

class Derived2 : public Base {
   public:
      Derived2(int i, std::string s) : i1(i), s1(s) {}
      Derived2() : i1(0), s1("") {}

      int get_i() {return i1;};
      string get_s() {return s1;}

      virtual ~Derived2() {}
         int i1;
         string s1;
};

class OuterG {
   public:
      std::vector<Base *> v;
};