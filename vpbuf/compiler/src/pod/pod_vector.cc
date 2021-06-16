// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "pod_vector.h"

// --- cpp ---------------------------------------------------------------------

void
pod_vector::serialize_out_cpp(
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

   std::string vec_type, type_payload, ref_prefix;
   vp_typedefs[payload_index]->get_type_cpp(vec_type);

   if (is_ptr)
      ref_prefix = "*";

   if (code_emitted)
      ofs << tab(in++) << "{\n";

   ofs << tab(in) << "write_int(wc, payload."
            << name << ".size());\n";

   ofs << tab(in) << "for (auto ii = payload." << name << ".begin();"
                     << "ii != payload." << name << ".end(); ii++)\n";

   ofs << tab(in+1) << "write_" << vec_type
            << "(nVersion, wc, "<< ref_prefix <<"(*ii));\n";

   if (code_emitted)
      ofs << tab(--in) << "}\n";
}

void
pod_vector::serialize_in_cpp(
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

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_cpp(vec_type);

   if (code_emitted)
      ofs << tab(in++) << "{\n";

   ofs << tab(in) <<"int count_"<< name <<";\n";
   ofs << tab(in) <<"read_int(rc, count_"<< name <<");\n";
   ofs << tab(in) <<"for (auto i = 0; i < count_"<< name <<"; i++) {\n";

   if (vp_typedefs[payload_index]->is_poly())
      ofs << tab(in+1) << "auto *pod = read_"
               << vec_type
               << "(nVersion, rc);\n";
   else if (is_ptr) {
      ofs <<tab(in+1)<< "auto pod = new " << vec_type << ";\n";

      ofs << tab(in+1) << "read_"
               << vec_type
               << "(nVersion, rc, *pod);\n";
   } else {
      ofs <<tab(in+1)<< vec_type <<" pod;\n";
      ofs << tab(in+1) << "read_"
               << vec_type
               << "(nVersion, rc, pod);\n";
   }

   ofs << tab(in+1) << "payload." << name << ".push_back(pod);\n";
   ofs << tab(in) << "}\n";

   if (code_emitted)
      ofs << tab(--in) << "}\n";
}

// --- python ------------------------------------------------------------------

void
pod_vector::serialize_out_py(ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_python(vec_type);

   out_stream << tab(in) << "count = len(payload." << name << ")\n";
   out_stream << tab(in) << "write_int(ver, f, count)\n";

   out_stream << tab(in) << "i = 0\n";
   out_stream << tab(in) << "while (i < count):\n";
   out_stream << tab(in + 1) << "write_" << vec_type
            << "(ver, f, payload." << name << "[i])\n";
   out_stream << tab(in + 1) << "i = i + 1\n";

}

void
pod_vector::serialize_in_py(ofstream &out_stream,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   int in = 1;
   bool present = code_version_test_py(out_stream, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_python(vec_type);

   out_stream << tab(in) << "payload." << name << " = []\n";
   out_stream << tab(in) << "count = read_int(ver, f)\n";
   out_stream << tab(in) << "i = 0\n";

   out_stream << tab(in) << "while (i < count):\n";
   out_stream << tab(in + 1) << vp_typedefs[payload_index]->format_in_py( "t");

   out_stream << tab(in + 1) << "payload." << name << ".append(t)\n";
   out_stream << tab(in + 1) << "i = i + 1\n";

}

// --- javascript --------------------------------------------------------------

void
pod_vector::serialize_out_js(
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

   std::string vec_type, type_payload;
   vp_typedefs[payload_index]->get_type_js(vec_type);

   out_stream << tab(in) <<"wc.write_Integer(payload."<< name << ".length);\n"
      << tab(in) << "for (var i = 0; i < payload."
                                 << name << ".length; i++)\n"
         << tab(in + 1) << "this.write_" << vec_type
      << "(ver, wc, payload." << name << "[i]);\n";
}

void
pod_vector::serialize_in_js(
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

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_js(vec_type);
   std::string t;

   out_stream <<
      tab(in) << "var count = rc.read_Integer();\n" <<
      tab(in) << "for (var i = 0; i < count; i++) {\n" <<
         tab(in + 1) << "var c = this.read_" << vec_type << "(ver, rc);\n" <<
         tab(in + 1) << "payload." << name << ".push(c);\n" <<
         tab(in) << "}\n"
      ;
}

std::string
pod_vector::declare_js()
{
   std::string vec_type;
   vp_typedefs[payload_index]->get_type_js(vec_type);

   return "var " + name + ":Vector.<" + vec_type
               + "> = new Vector.< " + vec_type + ">;";
}

