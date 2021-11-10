// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct pod_salt : public pod_item
{
   int payload_index;
   TypeVector &vp_typedefs;

   pod_salt(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int, TypeMap &, TarLang &);
   void serialize_in_js(ofstream &, int, TypeMap &, TarLang &);

   std::string declare_js();
};