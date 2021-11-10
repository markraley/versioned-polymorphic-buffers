// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct pod_typed : public pod_item
{
   int payload_index;
   TypeVector &vp_typedefs;
   bool is_ptr;

   pod_typed(TypeVector &vp_typedefs, bool is_ptr)
      : vp_typedefs(vp_typedefs), is_ptr(is_ptr) {}

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_js(ofstream &, int, TypeMap &, TarLang &, bool);

   std::string declare_js();
};