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

class EggScrambler : public ReorderCog {
   public:
      vector <int> base_arr;
      uint seed;

   public:
      EggScrambler(
         vector <int> const &v,
         uint seed = 1) : base_arr(v), seed(seed) { };

      vector<int> operator ()() {
         auto tmp(base_arr);
         auto j = tmp.size() - 1;
         uint i = 0;

         while (j > 0) {
            seed = (seed * 61) % 233;
            i = seed % j;

//            cout << seed <<" "<< i <<" "<< j << endl;

            auto xchg = tmp[j];
            tmp[j] = tmp[i];
            tmp[i] = xchg;

            j--;

         }

//         for (auto const& ii : tmp)
//            cout << tmp[ii] << " ";
//         cout << endl;

         return tmp;
      }
};

// -----------------------------------------------------------------------------


class SaltShaker : public Shaker {
   public:
      int seed;
      SaltShaker(int seed = 1) : seed(seed) {};

      virtual string operator () ()
      {
         seed = (seed * 53) % 113;
         return "SALT-" + to_string(seed);
      };

};

class PepperShaker : public Shaker {
   public:
      int seed;
      PepperShaker(int seed = 1) : seed(seed) {};

      virtual string operator () ()
      {
         seed = (seed * 47) % 199;
         return "PEPPER-" + to_string(seed);
      };

};

// -----------------------------------------------------------------------------
