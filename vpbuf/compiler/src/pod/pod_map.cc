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

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_cpp(local_key_type);
   vp_typedefs[payload_index]->get_type_cpp(payload_type);

   ofs <<tab(in)<<"write_int(wc, payload."<< name <<".size());\n";
   ofs <<tab(in)<< "for (auto ii = payload." << name << ".begin();"
                     << "ii != payload." << name << ".end(); ii++) {\n";
   ofs <<tab(in+1)<<"write_" << local_key_type << "(nVersion, wc, (ii->first));\n";
   ofs <<tab(in+1)<<"write_" << payload_type << "(nVersion, wc, (ii->second));\n";
   ofs <<tab(in)<<"}\n";
}

void
pod_map::serialize_in_cpp(
   ofstream &out_stream,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present, code_emitted;
   code_version_test_cpp(out_stream, present, code_emitted, in,
                           nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;
}

// --- python ------------------------------------------------------------------

void
pod_map::serialize_out_py(
   ofstream &ofs,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_python(local_key_type);
   vp_typedefs[payload_index]->get_type_python(payload_type);

   ofs <<tab(in)<<"write_int(ver, f, len(payload."<< name <<"))\n";

   ofs <<tab(in)<<"for k, v in iter(payload."<< name <<".items()):\n";
   ofs <<tab(in+1)<<"write_" << local_key_type << "(ver, f, k)\n";
   ofs <<tab(in+1)<<"write_" << payload_type << "(ver, f, v)\n";

}

void
pod_map::serialize_in_py(
   ofstream &ofs,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
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
   ofs <<tab(in) << "count = read_int(ver, f)\n";
   ofs <<tab(in) << "i = 0\n";
   ofs <<tab(in) << "while (i < count):\n";
   ofs <<tab(in + 1) << "k = " << local_key_type << "()\n";
   ofs <<tab(in + 1) << vp_key->format_in_py("k");
   ofs <<tab(in + 1) << "t = " << payload_type << "()\n";
   ofs <<tab(in + 1) << vp_typedefs[payload_index]->format_in_py("t");

   ofs <<tab(in + 1) << "payload." << name << "[k] = t\n";
   ofs <<tab(in + 1) << "i = i + 1\n\n";

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

   ofs <<tab(in)<<"wc.write_Integer(Object.keys(payload."<< name <<").length)\n";

   ofs <<tab(in)<<"for (const [k, v] of Object.entries(payload."<< name <<")) {\n";
   ofs <<tab(in+1)<<"this.write_" << local_key_type << "(ver, wc, k)\n";
   ofs <<tab(in+1)<<"this.write_" << payload_type << "(ver, wc, v)\n";
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
   ofs <<tab(in) << "var count = rc.read_Integer()\n";
   ofs <<tab(in) << "for (var i = 0; i < count; i++) {\n";
//   ofs <<tab(in + 1) << "k = " << local_key_type << "()\n";
   ofs <<tab(in + 1) << vp_key->format_in_js("k");
//   ofs <<tab(in + 1) << "t = " << payload_type << "()\n";
   ofs <<tab(in + 1) << vp_typedefs[payload_index]->format_in_js("t");

   ofs <<tab(in + 1) << "payload." << name << "[k] = t\n";
   ofs <<tab(in)<< "}\n\n";
}

std::string pod_map::declare_js()
{
   return "var " + name +":Object = new Object();";
}
