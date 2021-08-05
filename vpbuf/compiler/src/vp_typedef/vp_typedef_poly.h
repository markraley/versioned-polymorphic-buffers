// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

struct vp_typedef_poly : public vp_typedef
{
   PodItems pod_items;
   std::vector <std::string> polys;

   virtual void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &);
   virtual void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &);

   virtual void serialize_out_py(ofstream &, TypeMap &, TarLang &);
   virtual void serialize_in_py(ofstream &, TypeMap &, TarLang &);

   virtual void serialize_out_js(ofstream &, int, TypeMap &, TarLang &);
   virtual void serialize_in_js(ofstream &, int, TypeMap &, TarLang &);

   virtual std::string format_in_py(const std::string var_name);
   virtual std::string format_in_js(const std::string var_name);

   virtual void get_type_python(std::string &result);
   virtual void get_type_cpp(std::string &result);
   virtual void get_type_js(std::string &result);

   virtual void add_pod_item(pod_item *);
   virtual void add_pod_item_range(unsigned int nBegin, unsigned int nEnd);
   virtual void add_range(unsigned int nBegin, unsigned int nEnd);

   virtual void add_subclass(const std::string &t);
   virtual bool is_terminal();
   virtual bool is_poly();
   virtual bool is_pod();
   virtual void get_terminals(Terminals &terminals, const TypeMap &type_map);
};
