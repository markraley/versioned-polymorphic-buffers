// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_character.h"

void
vp_typedef_character::get_type_python(std::string &result)
{
   result = "int";
}

void
vp_typedef_character::get_type_cpp(std::string &result)
{
   result = "char";
}

void
vp_typedef_character::get_type_js(std::string &result)
{
   result = "int";
}

std::string
vp_typedef_character::format_in_py(const std::string var_name)
{
   return var_name + " = read_" + type_name + "(ver, f)\n";
}

void
vp_typedef_character::serialize_out_cpp(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &) {}

void
vp_typedef_character::serialize_in_cpp(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &) {}


void
vp_typedef_character::serialize_out_py(
   std::ofstream &out_stream, TypeMap &type_map, TarLang &)
{
   out_stream << "def write_str(ver, f, payload):\n";
   out_stream <<
"\
    f.writeString(payload)\n\
";
   out_stream << "\n";
}

void
vp_typedef_character::serialize_in_py(
   std::ofstream &out_stream, TypeMap &type_map, TarLang &)
{
   out_stream << "def read_str(ver, f):\n";
   out_stream <<
"\
   t = f.readInteger()\n\
   assert(t == 6)\n\
   return f.readString()\n\
";

   out_stream << "\n";
}


void
vp_typedef_character::serialize_out_js(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &)
{}

void
vp_typedef_character::serialize_in_js(
   std::ofstream &out_stream, int in, TypeMap &type_map, TarLang &)
{}

std::string
vp_typedef_character::format_in_js(const std::string var_name)
{
   return "var " + var_name + " = read_" + type_name + "(ver, input)\n";
}

void vp_typedef_character::add_pod_item
   (pod_item *) {};

void
vp_typedef_character::add_pod_item_range
   (unsigned int nBegin, unsigned int nEnd) {};

void
vp_typedef_character::add_subclass
   (const std::string &t) {};

bool
vp_typedef_character::is_terminal() { return true; };

bool
vp_typedef_character::is_poly() { return false; };

void
vp_typedef_character::get_terminals
   (Terminals &terminals, const TypeMap &type_map) {};
