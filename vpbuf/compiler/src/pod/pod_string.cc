// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_string.h"

// --- cpp ---------------------------------------------------------------------

void
pod_string::serialize_out_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_cpp(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   ofs <<tab(in)<< "write_string(wc, payload." << name << ");\n";
}

void
pod_string::serialize_in_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_cpp(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   ofs <<tab(in)<< "read_string(rc, payload." << name << ");\n";
}

// --- python ------------------------------------------------------------------

void
pod_string::serialize_out_py(
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   out_stream <<tab(in)<< "write_str(ver, f, payload." << name << ")\n";
}

void
pod_string::serialize_in_py(
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   out_stream <<tab(in)<< "payload." << name << " = read_str(ver, f)\n";
}

// --- javascript --------------------------------------------------------------

void
pod_string::serialize_out_js(
   ofstream &out_stream,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_js(out_stream, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   out_stream <<tab(in)
      << "wc.write_String(payload." << name << ");\n";
}

void
pod_string::serialize_in_js(
   ofstream &out_stream,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_js(out_stream, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   out_stream <<tab(in)
      << "payload." << name << " = rc.read_String();\n";
}

std::string
pod_string::declare_js()
{
   return "var " + name + " = '';";
}

// -----------------------------------------------------------------------------