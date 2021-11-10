// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct vp_typedef_pod : public vp_typedef
{
   PodItems pod_items;

   void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &);
   void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &);

   void serialize_out_py(ofstream &, int, TypeMap &, TarLang &, bool);
   void serialize_in_py(ofstream &, int, TypeMap &, TarLang &, bool);

   void serialize_out_js(ofstream &, int, TypeMap &, TarLang &);
   void serialize_in_js(ofstream &, int, TypeMap &, TarLang &);

   std::string format_in_py(const std::string var_name);
   std::string format_in_js(const std::string var_name);

   void get_type_python(std::string &result);
   void get_type_cpp(std::string &result);
   void get_type_js(std::string &result);

   void add_pod_item(pod_item *);
   void add_pod_item_range(unsigned int nBegin, unsigned int nEnd);

   bool is_pod();
};
