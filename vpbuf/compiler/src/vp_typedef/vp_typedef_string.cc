// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_string.h"

void
vp_typedef_string::get_type_python(std::string &result)
{
   result = "str";
}

void
vp_typedef_string::get_type_cpp(std::string &result)
{
   result = "string";
}

void
vp_typedef_string::get_type_js(std::string &result)
{
   result = "String";
}

std::string
vp_typedef_string::format_in_py(const std::string var_name)
{
   std::string t;

   get_type_python(t);

   return var_name + " = read_" + t + "(ver, f)\n";
}

// -----------------------------------------------------------------------------

void
vp_typedef_string::serialize_out_cpp(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &) {}

void vp_typedef_string::serialize_in_cpp(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &) {}

// -----------------------------------------------------------------------------

void vp_typedef_string::serialize_out_py(
   std::ofstream &out_stream, TypeMap &type_map, TarLang &) {}

void vp_typedef_string::serialize_in_py(
   std::ofstream &out_stream, TypeMap &type_map, TarLang &) {}

// -----------------------------------------------------------------------------

void
vp_typedef_string::serialize_out_js(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &)
{

   ofs <<tab(in)<< "write_String: function(ver, wc, payload) {\n";
   ofs <<tab(in+1)<< "wc.write_String(payload);\n";
   ofs <<tab(in)<< "},\n\n";
}

void
vp_typedef_string::serialize_in_js(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &)
{
   ofs <<tab(in)<< "read_String: function(ver, rc) {\n";
   ofs <<tab(in+1)<< "return rc.read_String();\n";
   ofs <<tab(in)<< "},\n\n";
}

// -----------------------------------------------------------------------------

std::string
vp_typedef_string::format_in_js(const std::string var_name)
{
   std::string t;

   get_type_js(t);

   return "var " + var_name + " = read_" + t + "(ver, input)\n";
}

void vp_typedef_string::add_pod_item(pod_item *) {};
void vp_typedef_string::add_pod_item_range(
   unsigned int nBegin, unsigned int nEnd) {};
void vp_typedef_string::add_subclass(const std::string &t) {};
bool vp_typedef_string::is_terminal() { return true; };
bool vp_typedef_string::is_poly() { return false; };
void vp_typedef_string::get_terminals(
   Terminals &terminals, const TypeMap &type_map) {};

