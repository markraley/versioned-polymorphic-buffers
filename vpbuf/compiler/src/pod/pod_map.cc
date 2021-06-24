// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_map.h"

// --- cpp ---------------------------------------------------------------------

void
pod_map::serialize_out_cpp(
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
   // TODO:implement
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
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_python(local_key_type);
   vp_typedefs[payload_index]->get_type_python(payload_type);

   out_stream <<tab(in)<< "write_int(ver, f, len(payload." << name << "))\n";

   out_stream <<tab(in)<< "for k, v in iter(payload." << name << ".items()):\n";
   out_stream <<tab(in+1) << "write_" << local_key_type << "(ver, f, k)\n";
   out_stream <<tab(in+1) << "write_" << payload_type << "(ver, f, v)\n";

}

void
pod_map::serialize_in_py(
   ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string payload_type, local_key_type;

   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);
   vp_key->get_type_python(local_key_type);
   vp_typedefs[payload_index]->get_type_python(payload_type);

   out_stream <<
      tab(in) << "payload." << name << " = {}\n" <<
      tab(in) << "count = read_int(ver, f)\n" <<
      tab(in) << "i = 0\n" <<
      tab(in) << "while (i < count):\n" <<
         tab(in + 1) << "k = " << local_key_type << "()\n" <<
         tab(in + 1) << vp_key->format_in_py("k") <<
         tab(in + 1) << "t = " << payload_type << "()\n" <<
         tab(in + 1) << vp_typedefs[payload_index]->format_in_py("t") <<

         tab(in + 1) << "payload." << name << "[k] = t\n" <<
         tab(in + 1) << "i = i + 1\n\n"
      ;

}

// --- javascript --------------------------------------------------------------

void
pod_map::serialize_out_js(
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

   std::string payload_type, local_key_type;
   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);

   vp_key->get_type_js(local_key_type);
   vp_typedefs[payload_index]->get_type_js(payload_type);

   out_stream <<
      tab(in) << "{\n" <<
      tab(in + 1) << "var count:int = 0;\n" <<
      tab(in + 1) << "var key:String;\n" <<
      tab(in + 1) << "for (key in payload." << name << ")\n" <<
         tab(in + 2) << "count++;\n" <<

      tab(in + 1) << "write_int(ver, output, count);\n" <<
      tab(in + 1) << "for (key in payload." << name << ")\n" <<
      tab(in + 1) << "{\n" <<
         tab(in + 2) << "write_str(ver, output, key);\n" <<
         tab(in + 2) << "write_" << payload_type
            << "(ver, output, payload." << name << "[key]);\n" <<
      tab(in + 1) << "}\n" <<
      tab(in) << "}\n";
}

void
pod_map::serialize_in_js(
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

   std::string payload_type, local_key_type, temp_var_name;
   vp_typedef *tdi = vp_typedefs[payload_index];
   vp_typedef *vp_key = GetVPType(key_type, type_map);

   vp_key->get_type_js(local_key_type);
   vp_typedefs[payload_index]->get_type_js(payload_type);

   temp_var_name = "t_" + name;

   out_stream <<
      tab(in) << "{\n" <<
      tab(in + 1) << "var count:int = read_int(ver, input);\n" <<
      tab(in + 1) << "for(var i:int = 0; i < count; i++)\n" <<
      tab(in + 1) << "{\n" <<
         tab(in + 2) << "var key:String = read_str(ver, input);\n" <<
         tab(in + 2) << vp_typedefs[payload_index]->format_in_js(temp_var_name)
            << tab(in + 2) << "payload." << name << "[key] = "
            << temp_var_name << ";\n" <<
      tab(in + 1) << "}\n" <<
      tab(in) << "}\n";
}

std::string pod_map::declare_js()
{
   return "var " + name +":Object = new Object();";
}
