// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"

struct pod_vector : public pod_item
{

   int payload_index;
   TypeVector &vp_typedefs;
   bool is_ptr;

   pod_vector(TypeVector &vp_typedefs_, bool is_ptr_)
         : vp_typedefs(vp_typedefs_), is_ptr(is_ptr_) {}

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int in, TypeMap &, TarLang &);
   void serialize_in_js(ofstream &, int in, TypeMap &, TarLang &);

   std::string declare_js();
};
