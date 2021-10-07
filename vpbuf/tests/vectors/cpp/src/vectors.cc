// Software released under the MIT license (see project root for license file)

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
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
#include "vp_vectors.cpp"
using namespace vp_vectors;


// specify output directory and file extension for test output

const string out_dir = "./out/";
const string file_ext = ".dat";

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   // ------------------------------------------------------------------
   // vectors_A - test vector of pointer to struct

   {
      string test_id_str = "vectors_A";
      int count = 10;
      int base = 50000;

      Header h1;
      OuterA o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = -99;
         h1.test_name = test_id_str;


         for (auto i = 0; i < count; i++) {
            auto a = new A;
            a->i1 = base + i;
            a->s1 = "A-" + std::to_string(base + i);
            o1.v.push_back(a);
         }

         write_Header(1, wc, h1);
         write_OuterA(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterA o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterA(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++) {
         assert(o1.v[i]->i1 == o2.v[i]->i1);
         assert(o1.v[i]->s1 == o2.v[i]->s1);
      }
   }

   // ------------------------------------------------------------------
   // vectors_B - test vector of struct

   {
      string test_id_str = "vectors_B";
      int count = 10;
      int base = 50000;

      Header h1;
      OuterB o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = -99;
         h1.test_name = test_id_str;

         A a;

         for (auto i = 0; i < count; i++) {
            a.i1 = base + i;
            a.s1 = "A-" + std::to_string(base + i);
            o1.v.push_back(a);
         }

         write_Header(1, wc, h1);
         write_OuterB(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterB o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterB(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++) {
         assert(o1.v[i].i1 == o2.v[i].i1);
         assert(o1.v[i].s1 == o2.v[i].s1);
      }
   }

   // ------------------------------------------------------------------
   // vectors_C - test vector of string

   {
      string test_id_str = "vectors_C";
      int count = 13;
      int base = 113;

      Header h1;
      OuterC o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = 101;
         h1.test_name = test_id_str;

         for (auto i = 0; i < count; i++)
            o1.v.push_back("C-" + std::to_string(base + i));

         write_Header(1, wc, h1);
         write_OuterC(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterC o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterC(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++)
         assert(o1.v[i] == o2.v[i]);
   }

   // ------------------------------------------------------------------
   // vectors_D - test vector of pointer to string

   {
      string test_id_str = "vectors_D";
      int count = 13;
      int base = 113;

      Header h1;
      OuterD o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = 101;
         h1.test_name = test_id_str;

         for (auto i = 0; i < count; i++)
            o1.v.push_back(new std::string("D-" + std::to_string(base + i)));

         write_Header(1, wc, h1);
         write_OuterD(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterD o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterD(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++)
         assert(*(o1.v[i]) == *(o2.v[i]));
   }

   // ------------------------------------------------------------------
   // vectors_E - test vector of integer

   {
      string test_id_str = "vectors_E";
      int count = 76;
      int base = 112;

      Header h1;
      OuterE o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = 1121;
         h1.test_name = test_id_str;

         for (auto i = 0; i < count; i++)
            o1.v.push_back(int(base + i));

         write_Header(1, wc, h1);
         write_OuterE(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterE o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterE(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++)
         assert(o1.v[i] == o2.v[i]);
   }

   // ------------------------------------------------------------------
   // vectors_F - test vector of pointer to integer

   {
      string test_id_str = "vectors_F";
      int count = 76;
      int base = 112;

      Header h1;
      OuterF o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = 1121;
         h1.test_name = test_id_str;

         for (auto i = 0; i < count; i++)
            o1.v.push_back(new int(base + i));

         write_Header(1, wc, h1);
         write_OuterF(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterF o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterF(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++)
         assert(*(o2.v[i]) == (base +i));
   }

   // ------------------------------------------------------------------
   // vectors_G - test vector of pointer to polymorphic class

   {
      string test_id_str = "vectors_G";
      int count = 17;
      int base = 500;

      Header h1;
      OuterG o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = 1;
         h1.test_name = test_id_str;


         for (auto i = 0; i < count; i++) {
            o1.v.push_back(new Derived1(base + i, "D1-" + std::to_string(base + i)));
            o1.v.push_back(new Derived2(base + i, "D2-" + std::to_string(base + i)));
         }

         write_Header(1, wc, h1);
         write_OuterG(1, wc, o1);

         size_t bytes_out = wc.write_file(out_dir + test_id_str + file_ext);
         std::cout << test_id_str <<" "<< bytes_out <<" bytes written\n";
      }

      Header h2;
      OuterG o2;

      {
         // read the file just written
         read_context rc(out_dir + test_id_str + file_ext);

         read_Header(1, rc, h2);
         read_OuterG(1, rc, o2);

         std::cout << test_id_str <<" "<< rc.get_buffer_size() <<" bytes read\n";
      }

      // compare data written against data read in

      assert(h1.version == h2.version);
      assert(h1.test_name == h2.test_name);
      assert(o1.v.size() == o2.v.size());
      for (auto i = 0; i < count; i++) {
         assert(o1.v[i]->get_i() == o2.v[i]->get_i());
         assert(o1.v[i]->get_s() == o2.v[i]->get_s());
      }
   }
}
