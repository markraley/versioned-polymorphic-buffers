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
      ofs <<tab(in++)<<"{\n";

   ofs <<tab(in)<<"write_int(ctx, payload."<< name <<".size());\n";

   ofs <<tab(in)<<"for (auto ii = payload."<< name <<".begin();"
                     <<"ii != payload."<< name << ".end(); ii++)\n";

   ofs <<tab(in+1)<<"write_"<< vec_type
            <<"(ctx, "<< ref_prefix <<"(*ii));\n";

   if (code_emitted)
      ofs <<tab(--in)<<"}\n";
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

   ofs <<tab(in)<<"int count_"<< name <<";\n";
   ofs <<tab(in)<<"read_int(ctx, count_"<< name <<");\n";
   ofs <<tab(in)<<"for (auto i = 0; i < count_"<< name <<"; i++) {\n";

   if (vp_typedefs[payload_index]->is_poly())
      ofs <<tab(in+1)<<"auto *pod = read_"<< vec_type <<"(ctx);\n";
   else if (is_ptr) {
      ofs <<tab(in+1)<<"auto pod = new "<< vec_type <<";\n";

      ofs <<tab(in+1)<<"read_"<< vec_type <<"(ctx, *pod);\n";
   } else {
      ofs <<tab(in+1)<< vec_type <<" pod;\n";
      ofs <<tab(in+1)<<"read_"<< vec_type <<"(ctx, pod);\n";
   }

   ofs <<tab(in+1)<<"payload."<< name <<".push_back(pod);\n";
   ofs <<tab(in) << "}\n";

   if (code_emitted)
      ofs <<tab(--in)<<"}\n";
}

// --- python ------------------------------------------------------------------

void
pod_vector::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_python(vec_type);

   ofs <<tab(in)<<"count = len(payload." << name <<")\n";
   ofs <<tab(in)<<"write_int(ctx, count)\n";

   ofs <<tab(in)<<"i = 0\n";
   ofs <<tab(in)<<"while (i < count):\n";
   ofs <<tab(in+1)<<"write_" << vec_type
            << "(ctx, payload." << name << "[i])\n";
   ofs <<tab(in+1)<<"i = i + 1\n";
}

void
pod_vector::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   bool present = code_version_test_py(ofs, in,
                                    nBegin, nEnd, tar_lang.start, tar_lang.end);
   if (!present)
      return;

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_python(vec_type);

   ofs <<tab(in)<< "payload."<< name <<" = []\n";
   ofs <<tab(in)<< "count = read_int(ctx)\n";
   ofs <<tab(in)<< "i = 0\n";

   ofs <<tab(in)<<"while (i < count):\n";
   ofs <<tab(in+1)<< vp_typedefs[payload_index]->format_in_py( "t");

   ofs <<tab(in+1)<<"payload." << name << ".append(t)\n";
   ofs <<tab(in+1)<<"i = i + 1\n";

}

// --- javascript --------------------------------------------------------------

void
pod_vector::serialize_out_js(
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

   std::string vec_type, type_payload;
   vp_typedefs[payload_index]->get_type_js(vec_type);

   ofs <<tab(in)<<"ctx.write_Integer(payload."<< name <<".length);\n"
      <<tab(in)<<"for (var i = 0; i < payload."<< name <<".length; i++)\n"
      <<tab(in+1)<<"this.write_"<< vec_type
                        <<"(ctx, payload."<< name <<"[i]);\n";
}

void
pod_vector::serialize_in_js(
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

   std::string vec_type;
   vp_typedefs[payload_index]->get_type_js(vec_type);
   std::string t;

   ofs <<
      tab(in)<< "var count = ctx.read_Integer();\n"
      <<tab(in)<< "for (var i = 0; i < count; i++) {\n"
      <<tab(in+1)<< "var c = this.read_" << vec_type << "(ctx);\n"
      <<tab(in+1)<< "payload." << name << ".push(c);\n"
      <<tab(in)<< "}\n";
}

std::string
pod_vector::declare_js()
{
   std::string vec_type;
   vp_typedefs[payload_index]->get_type_js(vec_type);

   return "var " + name + ":Vector.<" + vec_type
               + "> = new Vector.< " + vec_type + ">;";
}

