// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_salt.h"

// --- cpp ---------------------------------------------------------------------

void
pod_salt::serialize_out_cpp(
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

   string t;
   vp_typedefs[payload_index]->get_type_cpp(t);

   ofs <<tab(in)<<"write_" << t <<"(ctx, (*ctx.salt_map[\""<< name <<"\"])());\n";
}

void
pod_salt::serialize_in_cpp(
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

   string t;
   vp_typedefs[payload_index]->get_type_cpp(t);

   ofs <<tab(in) <<"read_" << t << "(ctx);\n";
}

// --- python ------------------------------------------------------------------

void
pod_salt::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string t;
   vp_typedefs[payload_index]->get_type_python(t);

   ofs <<tab(in)<< "write_" << t
      <<"(ctx, ctx.salt_map['" << name << "']())\n";
}

void
pod_salt::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   ofs <<tab(in)
      <<vp_typedefs[payload_index]->format_in_py("v");
}

// --- javascript --------------------------------------------------------------

void
pod_salt::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   std::string t;
   bool present, code_emitted;
   code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   vp_typedefs[payload_index]->get_type_js(t);

   ofs <<tab(in)<<"ctx.write_"<< t <<"(ctx.salt_map['"<< name <<"']());\n";
}

void
pod_salt::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   std::string t;
   bool present, code_emitted;
   code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   vp_typedefs[payload_index]->get_type_js(t);

   ofs <<tab(in)<<"this.read_"<< t <<"(ctx);\n";
}

std::string
pod_salt::declare_js()
{
   std::string t;
   int in = 1;

   vp_typedefs[payload_index]->get_type_js(t);

   return "var " + name + " = new " + t + "()";
}

// -----------------------------------------------------------------------------