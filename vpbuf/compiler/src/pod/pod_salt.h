// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct pod_salt : public pod_item
{
   int payload_index;
   TypeVector &vp_typedefs;
   bool assert_on_read;

   pod_salt(TypeVector &vp_typedefs, bool assert_on_read)
      : vp_typedefs(vp_typedefs), assert_on_read(assert_on_read) {}

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_js(ofstream &, int, TypeMap &, TarLang &, bool);

   std::string declare_js();
};