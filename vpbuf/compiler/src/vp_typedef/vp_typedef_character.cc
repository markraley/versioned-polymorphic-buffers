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
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}

void
vp_typedef_character::serialize_in_cpp(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &) {}


void
vp_typedef_character::serialize_out_py(
   std::ofstream &ofs, TypeMap &type_map, TarLang &)
{
   ofs << "def write_str(ver, f, payload):\n";
   ofs <<
"\
    f.writeString(payload)\n\
";
   ofs << "\n";
}

void
vp_typedef_character::serialize_in_py(
   std::ofstream &ofs, TypeMap &type_map, TarLang &)
{
   ofs << "def read_str(ver, f):\n";
   ofs <<
"\
   t = f.readInteger()\n\
   assert(t == 6)\n\
   return f.readString()\n\
";

   ofs << "\n";
}


void
vp_typedef_character::serialize_out_js(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &)
{}

void
vp_typedef_character::serialize_in_js(
   std::ofstream &ofs, int in, TypeMap &type_map, TarLang &)
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
vp_typedef_character::add_range
   (unsigned int nBegin, unsigned int nEnd) {};

void
vp_typedef_character::add_subclass
   (const std::string &t) {};

bool
vp_typedef_character::is_terminal() { return true; };

bool
vp_typedef_character::is_poly() { return false; };

bool
vp_typedef_character::is_pod() { return false; };

void
vp_typedef_character::get_terminals
   (Terminals &terminals, const TypeMap &type_map) {};
