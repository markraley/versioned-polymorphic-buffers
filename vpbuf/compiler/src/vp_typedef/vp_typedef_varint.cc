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
   return var_name + " = read_int(ctx)\n";
}

// --- cpp ---------------------------------------------------------------------

void
vp_typedef_varint::serialize_out_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
}

void
vp_typedef_varint::serialize_in_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
}

// --- python ------------------------------------------------------------------

void
vp_typedef_varint::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{

   ofs << "def write_int(ctx, payload):\n";
   ofs <<
"\
    ctx.encoder.writeInteger(payload) # amf3\n\
";
   ofs << "\n";
}

void
vp_typedef_varint::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   ofs << "def read_int(ctx):\n";

   ofs <<
"\
   t = ctx.decoder.readInteger() # amf3\n\
   assert(t == 4)\n\
   return ctx.decoder.readInteger()\n\
";

   ofs << "\n";
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_varint::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   ofs <<tab(in)<< "write_Integer: function(ctx, payload) {\n";
   ofs <<tab(in+1)<< "ctx.write_Integer(payload);\n";
   ofs <<tab(in)<< "},\n\n";
}

void
vp_typedef_varint::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   ofs <<tab(in)<< "read_Integer: function(ctx) {\n";
   ofs <<tab(in+1)<< "return ctx.read_Integer();\n";
   ofs <<tab(in)<< "},\n\n";
}

std::string vp_typedef_varint::format_in_js(const std::string var_name)
{
   return "var " + var_name + " = ctx.read_Integer()\n";
}

void vp_typedef_varint::add_pod_item(pod_item *) {};
