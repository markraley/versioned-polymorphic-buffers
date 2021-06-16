// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct pod_string : public pod_item
{
   virtual void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &);
   virtual void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &);

   virtual void serialize_out_py(ofstream &, TypeMap &, TarLang &);
   virtual void serialize_in_py(ofstream &, TypeMap &, TarLang &);

   virtual void serialize_out_js(ofstream &, int, TypeMap &, TarLang &);
   virtual void serialize_in_js(ofstream &, int, TypeMap &, TarLang &);

   virtual std::string declare_js();
};
