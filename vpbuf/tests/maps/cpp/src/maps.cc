// Software released under the MIT license (see project root for license file)

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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
#include "vp_maps.cpp"
using namespace vp_maps;


// specify output directory and file extension for test output

const string out_dir = "./out/";
const string file_ext = ".dat";

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   // ------------------------------------------------------------------
   // maps_A -

   {
      string test_id_str = "maps_A";
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
            o1.lookup[base + i] = a;
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
      assert(o1.lookup.size() == o2.lookup.size());
      for (auto ii = o1.lookup.begin();ii != o1.lookup.end(); ii++) {
         auto p = o2.lookup[ii->first];
         assert((ii->second)->s1 == p->s1);
         assert((ii->second)->i1 == p->i1);
      }
   }

   // ------------------------------------------------------------------
   // maps_B -

   {
      string test_id_str = "maps_B";
      int count = 10;
      int base = 50000;

      Header h1;
      OuterB o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = -99;
         h1.test_name = test_id_str;


         for (auto i = 0; i < count; i++) {
            auto a = new A;
            a->i1 = base + i;
            a->s1 = "B-" + std::to_string(base + i);
            o1.lookup[to_string(base + i)] = a;
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
      assert(o1.lookup.size() == o2.lookup.size());
      for (auto ii = o1.lookup.begin();ii != o1.lookup.end(); ii++) {
         auto p = o2.lookup[ii->first];
         assert((ii->second)->s1 == p->s1);
         assert((ii->second)->i1 == p->i1);
      }
   }

// ------------------------------------------------------------------
   // maps_C -

   {
      string test_id_str = "maps_C";
      int count = 10;
      int base = 50000;

      Header h1;
      OuterC o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = -99;
         h1.test_name = test_id_str;


         for (auto i = 0; i < count; i++) {
            o1.lookup[base + i] = "C-" + to_string(base + i);
         }

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
      assert(o1.lookup.size() == o2.lookup.size());
      for (auto ii = o1.lookup.begin();ii != o1.lookup.end(); ii++) {
         auto p = o2.lookup[ii->first];
         assert((ii->second) == p);
      }
   }

   // ------------------------------------------------------------------
   // maps_D -

   {
      string test_id_str = "maps_D";
      int count = 10;
      int base = 50000;

      Header h1;
      OuterD o1;

      {
         // initialize test data structures and write to file
         write_context wc;

         h1.version = -99;
         h1.test_name = test_id_str;


         for (auto i = 0; i < count; i++) {
            int j = base + i;
            o1.lookup[to_string(j)] = new D1(j, "D1-" + to_string(j));
         }

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
      assert(o1.lookup.size() == o2.lookup.size());
      for (auto ii = o1.lookup.begin();ii != o1.lookup.end(); ii++) {
         auto p = o2.lookup[ii->first];
         assert((ii->second)->s == p->s);
         assert((ii->second)->i == p->i);
      }
   }

   // ------------------------------------------------------------------

}

// -----------------------------------------------------------------------------
