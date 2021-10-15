// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_map.h"

// --- cpp ---------------------------------------------------------------------

void
pod_map::serialize_out_cpp(
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

   std::string payload_type, local_key_type, payload_prefix;

   if (vp_typedefs[payload_index]->is_pod()
         || !vp_typedefs[payload_index]->is_terminal())
      payload_prefix = "*";

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_cpp(local_key_type);
   vp_typedefs[payload_index]->get_type_cpp(payload_type);

   ofs <<tab(in)<<"write_int(ctx, payload."<< name <<".size());\n";
   ofs <<tab(in)<< "for (auto ii = payload." << name << ".begin();"
                     << "ii != payload." << name << ".end(); ii++) {\n";
   ofs <<tab(in+1)<<"write_"<< local_key_type << "(ctx, ii->first);\n";
   ofs <<tab(in+1)<<"write_"<< payload_type <<"(ctx, "
                              << payload_prefix <<"(ii->second));\n";
   ofs <<tab(in)<<"}\n";
}

void
pod_map::serialize_in_cpp(
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

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_cpp(local_key_type);
   vp_typedefs[payload_index]->get_type_cpp(payload_type);

   ofs << tab(in) <<"int count_"<< name <<";\n";
   ofs << tab(in) <<"read_int(ctx, count_"<< name <<");\n";
   ofs << tab(in) <<"for (auto i = 0; i < count_"<< name <<"; i++) {\n";

   ofs <<tab(in+1)<< local_key_type <<" k;\n";
   ofs <<tab(in+1)<<"read_"<< local_key_type <<"(ctx, k);\n";

   if (vp_typedefs[payload_index]->is_pod()
         || !vp_typedefs[payload_index]->is_terminal()) {
      ofs <<tab(in+1)<< "auto *v = new "<< payload_type <<";\n";
      ofs <<tab(in+1)<<"read_"<< payload_type <<"(ctx, *v);\n";
   } else {
      ofs <<tab(in+1)<< payload_type <<" v;\n";
      ofs <<tab(in+1)<<"read_"<< payload_type <<"(ctx, v);\n";
   }

   ofs <<tab(in + 1) << "payload." << name << "[k] = v;\n";
   ofs <<tab(in)<< "}\n\n";
}

// --- python ------------------------------------------------------------------

void
pod_map::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_python(local_key_type);
   vp_typedefs[payload_index]->get_type_python(payload_type);

   ofs <<tab(in)<<"write_int(ctx, len(payload."<< name <<"))\n";

   ofs <<tab(in)<<"for k, v in iter(payload."<< name <<".items()):\n";
   ofs <<tab(in+1)<<"write_" << local_key_type << "(ctx, k)\n";
   ofs <<tab(in+1)<<"write_" << payload_type << "(ctx, v)\n";

}

void
pod_map::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_python(local_key_type);
   vp_typedefs[payload_index]->get_type_python(payload_type);

   ofs <<tab(in)<< "payload." << name << " = {}\n";
   ofs <<tab(in)<< "count = read_int(ctx)\n";
   ofs <<tab(in)<< "i = 0\n";
   ofs <<tab(in)<< "while (i < count):\n";

   ofs <<tab(in+1)<< "k = " << local_key_type << "()\n";
   ofs <<tab(in+1)<< vp_key->format_in_py("k");
   ofs <<tab(in+1)<< "t = " << payload_type << "()\n";
   ofs <<tab(in+1)<< vp_typedefs[payload_index]->format_in_py("t");

   ofs <<tab(in+1)<< "payload." << name << "[k] = t\n";
   ofs <<tab(in+1)<< "i = i + 1\n\n";

}

// --- javascript --------------------------------------------------------------

void
pod_map::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_js(local_key_type);
   vp_typedefs[payload_index]->get_type_js(payload_type);

   ofs <<tab(in)<<"ctx.write_Integer(Object.keys(payload."
                  << name <<").length)\n";

   ofs <<tab(in)<<"for (const [k, v] of Object.entries(payload."
                  << name <<")) {\n";
   ofs <<tab(in+1)<<"this.write_" << local_key_type << "(ctx, k)\n";
   ofs <<tab(in+1)<<"this.write_" << payload_type << "(ctx, v)\n";
   ofs <<tab(in)<<"}\n";
}

void
pod_map::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_js(ofs, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
   if (code_emitted)
      in++;
   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_js(local_key_type);
   vp_typedefs[payload_index]->get_type_js(payload_type);

   ofs <<tab(in)<< "payload." << name << " = {}\n";
   ofs <<tab(in)<< "var count = ctx.read_Integer()\n";
   ofs <<tab(in)<< "for (var i = 0; i < count; i++) {\n";
   ofs <<tab(in+1)<< vp_key->format_in_js("k");
   ofs <<tab(in+1)<< vp_typedefs[payload_index]->format_in_js("t");

   ofs <<tab(in+1)<< "payload." << name << "[k] = t\n";
   ofs <<tab(in)<< "}\n\n";
}

std::string pod_map::declare_js()
{
   return "var " + name +":Object = new Object();";
}
