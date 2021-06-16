// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_varint.h"


void
vp_typedef_varint::get_type_python(std::string &result)
{
   result = "int";
}

void
vp_typedef_varint::get_type_cpp(std::string &result)
{
   result = "int";
}

void
vp_typedef_varint::get_type_js(std::string &result)
{
   result = "Integer";

}

std::string
vp_typedef_varint::format_in_py(const std::string var_name)
{
   return var_name + " = read_int(ver, f)\n";
}

// --- cpp ---------------------------------------------------------------------

void
vp_typedef_varint::serialize_out_cpp(
   ofstream &out_stream,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
}

void
vp_typedef_varint::serialize_in_cpp(
   ofstream &out_stream,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
}

// --- python ------------------------------------------------------------------

void
vp_typedef_varint::serialize_out_py(
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{

   out_stream << "def write_int(ver, f, payload):\n";
   out_stream <<
"\
    f.writeInteger(payload)\n\
";
   out_stream << "\n";
}

void
vp_typedef_varint::serialize_in_py(
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   out_stream << "def read_int(ver, f):\n";

   out_stream <<
"\
   t = f.readInteger()\n\
   assert(t == 4)\n\
   return f.readInteger()\n\
";

   out_stream << "\n";
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_varint::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   ofs <<tab(in)<< "write_Integer: function(ver, wc, payload) {\n";
   ofs <<tab(in+1)<< "wc.write_Integer(payload);\n";
   ofs <<tab(in)<< "},\n\n";
}

void
vp_typedef_varint::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   ofs <<tab(in)<< "read_Integer: function(ver, rc) {\n";
   ofs <<tab(in+1)<< "return rc.read_Integer();\n";
   ofs <<tab(in)<< "},\n\n";
}

std::string vp_typedef_varint::format_in_js(const std::string var_name)
{
   return "var " + var_name + ":int = read_int(ver, input)\n";
}

void vp_typedef_varint::add_pod_item(pod_item *) {};
void vp_typedef_varint::add_pod_item_range(unsigned int nBegin, unsigned int nEnd) {};
void vp_typedef_varint::add_subclass(const std::string &t) {};
bool vp_typedef_varint::is_terminal() { return true; };
bool vp_typedef_varint::is_poly() { return false; };
void vp_typedef_varint::get_terminals(Terminals &terminals, const TypeMap &type_map) {};