// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_vector.h"

void vp_typedef_vector::get_type_python(std::string &result)
{

   ImplMap::iterator ii = impls.find("python");

   // a string is a kind of vector
   if (ii != impls.end())
   {
      impl_specifier impl = ii->second;

      if (impl.name == "string")
         result = "str";
   }
   else
      result = "[]";
}

void vp_typedef_vector::get_type_cpp(std::string &result)
{
   result = "std::vector";
}

void vp_typedef_vector::get_type_js(std::string &result)
{
   result = "[]";
}

std::string vp_typedef_vector::format_in_py(const std::string var_name)
{
   return var_name + " = read_" + type_name + "(ctx)\n";
}

// --- cpp ---------------------------------------------------------------------

void
vp_typedef_vector::serialize_out_cpp(
   ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

void
vp_typedef_vector::serialize_in_cpp(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

// --- python ------------------------------------------------------------------

void
vp_typedef_vector::serialize_out_py(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

void
vp_typedef_vector::serialize_in_py(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &)
{
#if 0
   std::string t;

   get_type_python(t);

   if (t == "str")
   {
      ofs << "def read_" << type_name << "(ctx):\n";
      ofs << "\treturn read_str(ctx)\n";
   }

   ofs << "\n\n";
#endif
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_vector::serialize_out_js(
   ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

void
vp_typedef_vector::serialize_in_js(
   ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

std::string
vp_typedef_vector::format_in_js(const std::string var_name)
{
   return "var " + var_name + " = read_" + type_name + "(ver, input)\n";
}

// -----------------------------------------------------------------------------

void vp_typedef_vector::add_pod_item(pod_item *) {};
void vp_typedef_vector::add_pod_item_range
      (unsigned int nBegin, unsigned int nEnd) {};

