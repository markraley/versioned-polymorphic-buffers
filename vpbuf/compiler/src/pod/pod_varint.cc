// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_varint.h"

// --- cpp ---------------------------------------------------------------------
void
pod_varint::serialize_out_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   bool present, code_emitted;

   if (!skip_test) {
      code_version_test_cpp(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
      if (code_emitted)
         in++;
   }

   ofs <<tab(in)<< "write_int(ctx, payload." << name << ");\n";
}

void
pod_varint::serialize_in_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   bool present, code_emitted;

   if (!skip_test) {
      code_version_test_cpp(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
      if (code_emitted)
         in++;
   }

   ofs <<tab(in)<< "read_int(ctx, payload." << name << ");\n";
}

// --- python ------------------------------------------------------------------

void
pod_varint::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   if (!skip_test) {
      bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
   }

   ofs <<tab(in)<<"write_int(ctx, payload."<< name <<")\n";
}

void
pod_varint::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   if (!skip_test) {
      bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
   }

   ofs <<tab(in)<<"payload."<< name <<" = read_int(ctx)\n";
}

// --- javascript --------------------------------------------------------------

void
pod_varint::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   bool present, code_emitted;

   if (!skip_test) {
      code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
      if (code_emitted)
         in++;
   }

   ofs <<tab(in)<<"ctx.write_Integer(payload." << name <<");\n";

}

void
pod_varint::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   bool present, code_emitted;

   if (!skip_test) {
      code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
      if (!present)
         return;
      if (code_emitted)
      in++;
   }

   ofs <<tab(in)<<"payload."<< name <<" = ctx.read_Integer();\n";
}

std::string pod_varint::declare_js()
{
   return "var " + name + " = 0";
}

