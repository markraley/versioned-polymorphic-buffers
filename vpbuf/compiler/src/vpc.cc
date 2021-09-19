// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"

#include "pod_vector.h"
#include "pod_map.h"
#include "pod_typed.h"
#include "pod_string.h"
#include "pod_varint.h"

#include "vp_typedef_character.h"
#include "vp_typedef_map.h"
#include "vp_typedef_pod.h"
#include "vp_typedef_reorder_pod.h"
#include "vp_typedef_poly.h"
#include "vp_typedef_varint.h"
#include "vp_typedef_string.h"
#include "vp_typedef_vector.h"

#include <filesystem>

// -----------------------------------------------------------------------------

std::string
tab(int n)
{
   std::string result;

   for (int i = 0; i < n; i++)
      result += "\t";

   return result;
}

// --- cpp header and footer ---------------------------------------------------

bool
code_header_cpp(ofstream &ofs, int &in, const TarLang &tar_lang)
{
   ofs <<tab(in)<<"#pragma once\n";
   ofs <<tab(in)<<"namespace "<< tar_lang.name_space <<" {\n\n";

   in += 1;

   ofs <<tab(in)<<"bool version_check(long ver)\n";
   ofs <<tab(in)<< "{\n";
   ofs <<tab(in+1)<<"return (ver < "<< tar_lang.start
         << " || ver > "<< tar_lang.end <<") ? false : true;\n";
   ofs <<tab(in)<<"}\n";

   ofs <<tab(in)<<"long get_high_version() {\n";
   ofs <<tab(in+1)<<"return "<< tar_lang.end <<";\n";
   ofs <<tab(in)<<"}\n";

   ofs <<tab(in)<<"long get_low_version() {\n";
   ofs <<tab(in+1)<<"return "<< tar_lang.start <<";\n";
   ofs <<tab(in)<<"}\n\n";
   return true;
}

bool
code_footer_cpp(ofstream &ofs, int &in, const TarLang &tar_lang)
{
   ofs << "}\n";

   return true;
}

// --- javascript header and footer --------------------------------------------

bool
code_header_js(ofstream &ofs, int &in, const TarLang &tar_lang)
{
   ofs <<tab(in)<<"// vpbuf generated code - do not modify\n";
   ofs <<tab(in)<<"\"use strict\";\n";
   ofs <<tab(in)<<"module.exports = {\n\n";

   in += 1;
   ofs <<tab(in)<< "factory: null, // must be set to class factory object\n\n";

   return true;
}

bool
code_footer_js(ofstream &ofs, int &in, const TarLang &tar_lang)
{
   ofs <<tab(in)<<"version_check: function(ver) {\n";
   ofs <<tab(in+1)<<"return (ver < "<< tar_lang.start
         << " || ver > "<< tar_lang.end <<") ? false : true;\n";
   ofs <<tab(in)<<"},\n";

   ofs <<tab(in)<<"get_high_version: function(ver) {\n";
   ofs <<tab(in+1)<<"return "<< tar_lang.end <<"\n";
   ofs << tab(in)<<"},\n";

   ofs <<tab(in)<<"get_low_version: function(ver) {\n";
   ofs <<tab(in+1)<<"return "<< tar_lang.start <<"\n";
   ofs <<tab(in)<<"}\n";

   ofs << "};\n";

   return true;
}

// --- python header -----------------------------------------------------------

bool
code_header_python(ofstream &ofs, int &in, const TarLang &tar_lang)
{
   ofs <<"from "<< tar_lang.name_space <<".persist import *\n\n";

   ofs <<tab(in)<< "def version_check(ver):\n";
   ofs <<tab(in+1)<< "if (ver < " << tar_lang.start
                        << " or ver > "<< tar_lang.end << "):\n";
   ofs <<tab(in+2)<< "return False\n";
   ofs <<tab(in+1)<< "else:\n";
   ofs <<tab(in+2)<< "return True\n\n";


   ofs <<tab(in)<< "def get_high_version():\n";
   ofs <<tab(in+1)<< "return "<< tar_lang.end <<"\n\n";

   ofs <<tab(in)<< "def get_low_version():\n";
   ofs <<tab(in+1)<< "return "<< tar_lang.start <<"\n\n";

   return true;
}

// --- generates version testing code for class elements (pod_*)

void
code_version_test_cpp(
   ofstream &ofs,
   bool &present,             // sets
   bool &code_emitted,        // sets
   int in,
   int nBegin,
   int nEnd,
   int nBase,
   int nLimit)
{
   present = true;
   code_emitted = false;

   if (nBegin > nBase && nEnd == 0) {
      if (nBegin > nLimit)
         present = false;
      else {
         ofs << tab(in) << "if (nVersion >= " << nBegin << ")\n";
         code_emitted = true;
      }
   } else if (nBegin > nBase || nEnd != 0) {
      if (nEnd < nBase || nBegin > nLimit)
         present = false;
      else if (nEnd == nLimit && nBegin == nBase)
         present = true;
      else {
         ofs << tab(in) << "if (nVersion >= "
            << nBegin << " && nVersion <= " << nEnd << ")\n";
         code_emitted = true;
      }
   }
}

bool
code_version_test_py(
   ofstream &ofs,
   int &nIndent,
   int nBegin,
   int nEnd,
   int nBase,
   int nLimit)
{
   int in = 0;
   bool is_present = true;

   if (nBegin > nBase && nEnd == 0) {
      if (nBegin > nLimit)
         is_present = false;
      else {
         ofs << "\tif (ver >= " << nBegin << "):\n";
         in = 1;
      }
   } else if (nBegin > nBase || nEnd != 0) {
      if (nEnd < nBase || nBegin > nLimit)
         is_present = false;
      else {
         ofs << "\tif (ver >= "
            << nBegin << " and ver <= " << nEnd << "):\n";
         in = 1;
      }
   }

   if (is_present) {
      nIndent += in;
   }

   return is_present;
}

void
code_version_test_js(
   ofstream &ofs,
   bool &present,             // sets
   bool &code_emitted,        // sets
   int in,
   int nBegin,
   int nEnd,
   int nBase,
   int nLimit)
{
   present = true;
   code_emitted = false;

   if (nBegin > nBase && nEnd == 0) {
      if (nBegin > nLimit)
         present = false;
      else {
         ofs << tab(in) << "if (ver >= " << nBegin << ")\n";
         code_emitted = true;
      }
   } else if (nBegin > nBase || nEnd != 0) {
      if (nEnd < nBase || nBegin > nLimit)
         present = false;
      else if (nEnd == nLimit && nBegin == nBase)
         present = true;
      else {
         ofs << tab(in) << "if (ver >= "
            << nBegin << " && ver <= " << nEnd << ")\n";
         code_emitted = true;
      }
   }
}

void vp_typedef::gen_cpp_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // empty stub
}

void vp_typedef::gen_py_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // empty stub
}

void vp_typedef::gen_js_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // empty stub
}

void vp_typedef::add_range(unsigned int nBegin, unsigned int nEnd)
{
   this->vrange.nBegin = nBegin;
   this->vrange.nEnd = nEnd;
}

bool VRange::overlap(unsigned int nBase, unsigned int nLimit)
{
   bool present = true;

   if (this->nBegin > nBase && this->nEnd == 0) { // open range
      if (this->nBegin > nLimit)
         present = false;
   } else if (this->nBegin > nBase || this->nEnd != 0) {
      if (this->nEnd < nBase || this->nBegin > nLimit)
         present = false;
   }

   return present;
}

// -----------------------------------------------------------------------------

vp_typedef *GetVPType(std::string &type_name, const TypeMap &type_map)
{
   TypeMap::const_iterator ii = type_map.find(type_name);

   if (ii != type_map.end())
      return ii->second;
   else
      return NULL;
}


struct var_generate_code
{
   template <typename, typename>
   struct result { typedef void type; };

   var_generate_code(
            qi::symbols<char, int>& vars,
            TypeVector &vp_typedefs,
            std::string &vpc_path)
         : vars(vars)
      , vp_typedefs(vp_typedefs)
      , vpc_path(vpc_path) {}

   void operator()(std::vector <TarLang> &tlist, int& nvars) const
   {
      TypeVector::iterator ii;
      std::vector <TarLang>::iterator tt;
      TypeMap type_map;

      std::cout <<"vpc_path: "<<
         (this->vpc_path.size() ? this->vpc_path : "<current>") <<"\n";

      for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
         type_map[(*ii)->type_name] = *ii;

      for (tt = tlist.begin(); tt != tlist.end(); tt++)
      {

         std::filesystem::path out_file_name(this->vpc_path);
         out_file_name.append(tt->path_out);
         out_file_name.append(tt->name_space + "." + tt->file_ext);

         std::ofstream ostr(out_file_name);

         if (ostr.fail()) {
            std::cout << out_file_name << " open failed\n";
            exit(1);
         }

         std::string msg;

         std::cout <<"generating "<< out_file_name
                        <<" "<< tt->start <<" "<< tt->end <<"\n";

         int in = 0;

         if (tt->name == "cplusplus") {
            code_header_cpp(ostr, in, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_out_cpp(ostr, in, type_map, *tt);

            for (ii = vp_typedefs.begin() ; ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_in_cpp(ostr, in, type_map, *tt);

            code_footer_cpp(ostr, in, *tt);
         } else if (tt->name == "python") {
            code_header_python(ostr, in, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->gen_py_utils(ostr, in, type_map, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_out_py(ostr, in, type_map, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_in_py(ostr, in, type_map, *tt);

         } else if (tt->name == "javascript") {
            code_header_js(ostr, in, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_out_js(ostr, in, type_map, *tt);

            for (ii = vp_typedefs.begin(); ii != vp_typedefs.end(); ++ii)
               (*ii)->serialize_in_js(ostr, in, type_map, *tt);

            code_footer_js(ostr, in, *tt);
         }
      }

   };

   qi::symbols<char, int>& vars;
   TypeVector &vp_typedefs;
   std::string vpc_path;
};

struct var_adder
{
   template <typename, typename, typename>
   struct result { typedef void type; };

   var_adder(qi::symbols<char, int>& vars, TypeVector &vp_typedefs)
      : vars(vars), vp_typedefs(vp_typedefs) {}

   void operator()(std::string const& var, int& nvars, int nType) const
   {
      vars.add(var.begin(), var.end(), nvars++);

      if (nType == VPTypePod) {

         vp_typedef_pod *new_run = new vp_typedef_pod();

         new_run->type_name = var;

         vp_typedefs.push_back(new_run);
      } else if (nType == VPTypeVector) {
         vp_typedef_vector *pnew = new vp_typedef_vector();

         pnew->type_name = var;

         vp_typedefs.push_back(pnew);
      } else if (nType == VPTypePoly) {
         vp_typedef_poly *new_run = new vp_typedef_poly();

         new_run->type_name = var;

         vp_typedefs.push_back(new_run);
      } else if (nType == VPTypeReorderPod) {
         auto new_run = new vp_typedef_reorder_pod();

         new_run->type_name = var;

         vp_typedefs.push_back(new_run);
      }
   };

   qi::symbols<char, int>& vars;
   TypeVector &vp_typedefs;
};

struct pod_item_varint_adder
{
   template <typename>
   struct result { typedef void type; };

   pod_item_varint_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(std::string const& item_name) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      pod_varint * new_item = new pod_varint();

      new_item->name = item_name;

      (*ii)->add_pod_item(new_item);
   };

   TypeVector &vp_typedefs;
};

struct pod_item_string_adder
{
   template <typename>
   struct result { typedef void type; };

   pod_item_string_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(std::string const& item_name) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      pod_string * new_item = new pod_string();

      new_item->name = item_name;

      (*ii)->add_pod_item(new_item);
   };

   TypeVector &vp_typedefs;
};

struct pod_item_type_adder
{
   template <typename, typename, typename>
   struct result { typedef void type; };

   pod_item_type_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void
   operator()(int const& var_index, std::string const& item_name,
            bool is_ptr) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      pod_typed * new_item = new pod_typed(vp_typedefs, is_ptr);

      new_item->name = item_name;
      new_item->payload_index = var_index;
      new_item->is_ptr = is_ptr;

      (*ii)->add_pod_item(new_item);
   };

   TypeVector &vp_typedefs;
};

struct type_payload_adder
{
   template <typename, typename, typename>
   struct result { typedef void type; };

   type_payload_adder(TypeVector &vp_typedefs)
   : vp_typedefs(vp_typedefs) {}

   void operator()(int const& var_index, bool is_ptr, int nType) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      if (nType == 1) { // TODO: document
         vp_typedef_vector *p = dynamic_cast<vp_typedef_vector *>(*ii);

         p->payload_index = var_index;
         p->is_ptr = is_ptr;
      }
   };

   TypeVector &vp_typedefs;
};

struct pod_item_map_adder
{
   template <typename, typename, typename>
   struct result { typedef void type; };

   pod_item_map_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void
   operator()(std::string const& key_type, int const& var_index,
               std::string const& item_name) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      pod_map * new_item = new pod_map(vp_typedefs, false);

      new_item->name = item_name;
      new_item->payload_index = var_index;
      new_item->key_type = key_type;

      (*ii)->add_pod_item(new_item);
   };

   TypeVector &vp_typedefs;
};

struct pod_item_vector_adder
{
   template <typename, typename, typename>
   struct result { typedef void type; };

   pod_item_vector_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void
   operator()(int const& var_index, std::string const& item_name,
               bool is_ptr) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      pod_vector * new_item = new pod_vector(vp_typedefs, is_ptr);

      new_item->name = item_name;
      new_item->payload_index = var_index;

      (*ii)->add_pod_item(new_item);
   };

   TypeVector &vp_typedefs;
};

struct sequence_format_hint_adder
{
   template <typename, typename>
   struct result { typedef void type; };

   sequence_format_hint_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void
   operator()(const std::string &lang_specifier,
            const std::string &impl) const
   {
      TypeVector::reverse_iterator ii;
      PodItems::reverse_iterator jj;

      ii = vp_typedefs.rbegin();

      impl_specifier tmp;
      tmp.name = impl;

      (*ii)->impls[lang_specifier] = tmp;
   };

   TypeVector &vp_typedefs;
};

struct subclass_to_parent_adder
{
   template <typename>
   struct result { typedef void type; };

   subclass_to_parent_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(int const& var_index) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      vp_typedefs[var_index]->add_subclass((*ii)->type_name);

      (*ii)->parent_name = vp_typedefs[var_index]->type_name;
   };

   TypeVector &vp_typedefs;
};

struct version_sequence_adder
{
   template <typename, typename>
   struct result { typedef void type; };

   version_sequence_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(unsigned int nBegin, unsigned int nEnd) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      (*ii)->add_pod_item_range(nBegin, nEnd);
   };

   TypeVector &vp_typedefs;
};

struct typedef_vrange_adder
{
   template <typename, typename>
   struct result { typedef void type; };

   typedef_vrange_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(unsigned int nBegin, unsigned int nEnd) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      (*ii)->add_range(nBegin, nEnd);
   };

   TypeVector &vp_typedefs;
};

struct vptype_option_adder
{
   template <typename, typename>
   struct result { typedef void type; };

   vptype_option_adder(TypeVector &vp_typedefs)
      : vp_typedefs(vp_typedefs) {}

   void operator()(unsigned int nBegin, unsigned int nEnd) const
   {
      TypeVector::reverse_iterator ii;

      ii = vp_typedefs.rbegin();

      (*ii)->add_range(nBegin, nEnd);
   };

   TypeVector &vp_typedefs;
};

template <typename Iterator>
struct vp_compiler : qi::grammar<Iterator, ascii::space_type>
{
   TypeVector vp_typedefs;
   std::vector <TarLang> tlist;
   qi::symbols<char, int> vars;
   int nvars;
   std::string vpc_path;

   vp_compiler(std::string vpc_path);

   qi::rule<Iterator, ascii::space_type>
            type_list, item_varint, item_string, item_typed;
   qi::rule<Iterator, ascii::space_type> pod_def, reorder_pod_def;
   qi::rule<Iterator, ascii::space_type> poly_def;
   qi::rule<Iterator, qi::locals<int, int>, ascii::space_type> format_set;
   qi::rule<Iterator,  ascii::space_type> root;
   qi::rule<Iterator, target_language(), ascii::space_type> target;
   qi::rule<Iterator, target_language(), ascii::space_type> target_ignore;
   qi::rule<Iterator, ascii::space_type> target_list;
   qi::rule<Iterator, ascii::space_type> version_sequence;
   qi::rule<Iterator, ascii::space_type> typedef_vrange, vptype_options,
                                          vptype_options_list,
                                          vptype_options_item,
                                          vptype_options_item_params,
                                          vptype_option_vrange;
   qi::rule<Iterator, std::string(), ascii::space_type>
      identifier, sequence_type, lang_specifier, quoted_string;
   qi::rule<Iterator, qi::locals<int>, ascii::space_type>
      item_map, item_vector;
   qi::rule<Iterator, int(), ascii::space_type>
      var_ref, var_ref_ptr, pod_parent;

   function<var_adder> add_var;
   function<var_generate_code> gen_code;
   function<pod_item_varint_adder> pod_item_varint_add;
   function<pod_item_string_adder> pod_item_string_add;
   function<pod_item_type_adder> pod_item_type_add;
   function<type_payload_adder> type_payload_add;
   function<pod_item_map_adder> pod_item_map_add;
   function<pod_item_vector_adder> pod_item_vector_add;
   function<sequence_format_hint_adder> sequence_format_hint_add;
   function<subclass_to_parent_adder> subclass_to_parent_add;
   function<version_sequence_adder> version_sequence_add;
   function<typedef_vrange_adder> typedef_vrange_add;
};


template <typename Iterator>
vp_compiler<Iterator>::vp_compiler(std::string vpc_path)
   : vp_compiler::base_type(root)
   , nvars(0)
   , add_var(var_adder(vars, vp_typedefs))
   , gen_code(var_generate_code(vars, vp_typedefs, vpc_path))
   , pod_item_varint_add(vp_typedefs)
   , pod_item_string_add(vp_typedefs)
   , pod_item_type_add(vp_typedefs)
   , pod_item_map_add(vp_typedefs)
   , type_payload_add(vp_typedefs)
   , pod_item_vector_add(vp_typedefs)
   , sequence_format_hint_add(vp_typedefs)
   , subclass_to_parent_add(vp_typedefs)
   , version_sequence_add(vp_typedefs)
   , typedef_vrange_add(vp_typedefs)
   , vpc_path(vpc_path)
{
   using namespace qi::labels;
   using qi::lexeme;
   using ascii::char_;
   using ascii::alnum;
   using qi::lit;
   using qi::debug;
   using qi::uint_;
   using qi::raw;
   using qi::alpha;
   using boost::phoenix::push_back;
   using boost::phoenix::ref;

   // When adding an intrinsic type
   //    be sure to modify both sections of code below.

   // Section #1

   vars.add("string", nvars++);
   vars.add("varint", nvars++);
   vars.add("character", nvars++);

   // Section #2

   {
      vp_typedef_string *intrinsic_type = new vp_typedef_string();
      intrinsic_type->type_name = "string";
      vp_typedefs.push_back(intrinsic_type);
   }

   {
      vp_typedef_varint *intrinsic_type = new vp_typedef_varint();
      intrinsic_type->type_name = "varint";
      vp_typedefs.push_back(intrinsic_type);
   }

   {
      vp_typedef_character *intrinsic_type = new vp_typedef_character();
      intrinsic_type->type_name = "character";
      vp_typedefs.push_back(intrinsic_type);
   }

   identifier = raw[lexeme[alpha >> *(alnum | '_')]];
   quoted_string = lit('"') >> raw[lexeme[+(char_ - '"')]] >> lit('"');

   var_ref =
         lexeme
         [
                     vars        [_val = _1]
               >>  !(alnum | '_') // make sure we have whole words
         ];

   var_ref_ptr %= lit("*") >> var_ref;

   version_sequence = (uint_ >> uint_)[version_sequence_add(_1, _2)]
                        | uint_[version_sequence_add(_1, 0)];

   typedef_vrange = (uint_ >> lit("-") >> uint_)[typedef_vrange_add(_1, _2)]
               | uint_[typedef_vrange_add(_1, 0)]
               | qi::attr(("unspecified"))
            ;

   vptype_option_vrange = (uint_ >> lit("-") >> uint_) | uint_ ;

   item_varint = lit("varint") >> identifier[pod_item_varint_add(_1)]
                        >> version_sequence;
   item_string = lit("string") >> identifier[pod_item_string_add(_1)]
                        >> version_sequence;

   item_map = lit("map") >> (identifier >> var_ref >> identifier)
                                 [pod_item_map_add(_1, _2, _3)]
            >> version_sequence;

   sequence_type = lit("zero-terminated") | lit("string");
   lang_specifier = lit("cplusplus")
                  | lit("python")
                  | lit("javascript");

   item_vector = lit("vector")
      >> (
            (var_ref_ptr >> identifier)[pod_item_vector_add(_1, _2, true)]
            |
            (var_ref >> identifier)[pod_item_vector_add(_1, _2, false)]
         )
            >> version_sequence;

   item_typed =
            (
               (var_ref >> identifier)[pod_item_type_add(_1, _2, false)]
               |
               (var_ref_ptr >> identifier)[pod_item_type_add(_1, _2, true)]
            ) >> version_sequence
            ;

   type_list = *(item_varint | item_string | item_map
               | item_vector  | item_typed);

   pod_parent = (lit("is") >> var_ref)[subclass_to_parent_add(_1)]
                  | qi::attr(("unspecified"));

   // TODO: implement vptype_option_vrange support

   vptype_options_item_params = lit("(") >> identifier
                              >> -vptype_option_vrange >> lit(")") ;
   vptype_options_item = identifier >> vptype_options_item_params;
   vptype_options_list = vptype_options_item
                           >> *(lit(",") >> vptype_options_item);
   vptype_options = (lit(":") >> vptype_options_list) ;

   pod_def = lit("pod")
               >> identifier [add_var(_1, ref(nvars), VPTypePod)]
               >> pod_parent >> typedef_vrange
               >> -vptype_options >> type_list;

   reorder_pod_def = lit("rpod") >>
               identifier [add_var(_1, ref(nvars), VPTypeReorderPod)]
               >> pod_parent >> typedef_vrange
               >> -vptype_options >> type_list;

   poly_def = (lit("poly") >> identifier)[add_var(_1, ref(nvars), VPTypePoly)]
            >> pod_parent >> typedef_vrange >> -vptype_options >> type_list;

   // name, version start, version end, name space, path out, file extension
   target = lit("language") >> lang_specifier >> uint_ >> uint_
                                    >> identifier >> quoted_string >> identifier;
   target_ignore = lit("-language") >> lang_specifier >> uint_ >> uint_
                                    >> identifier >> quoted_string >> identifier;

   target_list = *(target[push_back(boost::phoenix::ref(tlist), _1)]
                     |
                  target_ignore);

   format_set = lit("target")
      >> (target_list
      >> +(poly_def | pod_def | reorder_pod_def))
               [gen_code(boost::phoenix::ref(tlist), ref(nvars))];

   root %= format_set ;

#if 0
   debug(format_set);
   debug(type_list);
   debug(pod_def);
   debug(item_varint);
   debug(item_string);
#endif
   format_set.name("format_set");
   type_list.name("type_list");
   pod_def.name("pod_def");
}


std::string
read_from_file(char const* infile)
{
   std::ifstream instream(infile);
   if (!instream.is_open())
         exit(-1);

   instream.unsetf(std::ios::skipws);

   return std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                      std::istreambuf_iterator<char>());
}


int
main(int argc, char *argv[])
{
   typedef std::string::const_iterator iterator_type;
   typedef vp_compiler<iterator_type> vp_compiler;
   using boost::spirit::ascii::space;

   int result;

   std::filesystem::path vpc_file_path(std::filesystem::relative(argv[1]));

   if (!std::filesystem::exists(vpc_file_path)) {
      std::cout << "file not found\n";
      return 2;
   }

   std::cout <<"Versioned Polymorphic Buffers Compiler (VPC)";
   std::cout <<" by Mark Raley, pre-release\n";
   std::cout <<"parsing: "<< argv[1] <<"\n";

   vp_compiler vpc(vpc_file_path.remove_filename());

   std::string str(read_from_file(argv[1]));

   std::string::const_iterator iter = str.begin();
   std::string::const_iterator end = str.end();
   bool r = phrase_parse(iter, end, vpc, space, result);

   if (r && iter == end) {
      std::cout <<"parse succeeded, type count is: "
                        << vpc.vp_typedefs.size() <<"\n";
      return 0;
   } else {
      std::cout <<"parse ***FAILED*** near:\n";
      int c = 0;
      while (iter != end && c < 3) {
         c += (*iter == '\n') ? 1 : 0;
         std::cout << *iter++;
      }
      std::cout <<"\nparse ends\n";
      return 1;
   }
}

