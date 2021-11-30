// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct pod_reorder_string : public pod_item
{

   std::vector<VPOption> cogs;

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_js(ofstream &, int, TypeMap &, TarLang &, bool);

   std::string declare_js();
};

