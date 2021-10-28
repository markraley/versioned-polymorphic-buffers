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

class Salt {
   public:
      virtual string operator ()() = 0;
      virtual ~Salt();
};

Salt::~Salt() {}

// -----------------------------------------------------------------------------

class flip : public ReorderCog {
   public:
      vector <int> base_list;

   public:
      flip(vector <int> &v) : base_list(v) { };

      vector<int> operator ()() {
         auto tmp(base_list);
         reverse(base_list.begin(), base_list.end());
         return tmp;
      }
};

class EggScrambler : public ReorderCog {
   public:
      vector <int> base_arr;
      uint seed;

   public:
      EggScrambler(vector <int> &v, uint seed = 1) : base_arr(v), seed(seed) { };

      vector<int> operator ()() {
         auto tmp(base_arr);
         auto j = tmp.size();
         uint i = 0;

#if 0
         while (false && j > 0) {
            seed = (seed * 61) % 223;
            i = seed % j;

            printf("%d", seed);

            auto xchg = tmp[j];
            tmp[j] = tmp[i];
            tmp[i] = xchg;

            j--;
         }
#endif
         reverse(base_arr.begin(), base_arr.end());

         return tmp;
      }
};

// -----------------------------------------------------------------------------


class SaltShaker : public Salt {
   public:
      int seed;
      SaltShaker(int seed = 1) : seed(seed) {};

      virtual string operator () ()
      {
         seed = (seed * 53) % 113;
         return "SALT-" + to_string(seed);
      };

};

class PepperShaker : public Salt {
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

