// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_poly.h"

// --- cpp ---------------------------------------------------------------------
void
code_out_protos_cpp(ofstream &ofs, int in, Terminals &terms)
{
   if (terms.size() == 0)
      return;

   for (size_t i = 0; i < terms.size() ; i++) {
      ofs <<tab(in)<< "void write_" << terms[i].name
                  <<"(write_context &ctx, "<< terms[i].name
                                                <<" &);\n";
   }

   ofs << "\n";
}

void
vp_typedef_poly::serialize_out_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   Terminals terms;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   if (parent_name.size() == 0) {
      get_terminals(terms, type_map);
      code_out_protos_cpp(ofs, in, terms);
   }

   ofs << tab(in) << "void write_" << type_name
      << "(write_context &ctx, "
      << type_name << " &payload)\n";
   ofs << tab(in) << "{\n";

   if (parent_name.size() == 0) {
      ofs <<tab(in+1)<< "const std::type_info& tid = typeid(payload);\n";

      for (size_t i = 0; i < terms.size() ; i++) {
         ofs << tab(in+1)
            << "if (std::type_index(tid) == std::type_index(typeid("
            << terms[i].name <<"))) {\n";

         size_t k = terms[i].layers.size() - 1;
         for (size_t j = 0;  j < terms[i].layers.size(); j++, k--) {
            ofs <<tab(in+2)<< "write_int(ctx,"
                     << terms[i].layers[k] << ");\n";
         }

         ofs <<tab(in+2)<< "write_" << terms[i].name
                     << "(ctx, dynamic_cast<"<< terms[i].name
                                                   <<" &> (payload)" <<");\n";
         ofs <<tab(in+1)<< "}\n";
      }
   }

   for (auto jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_out_cpp(ofs, in + 1, type_map, tar_lang);
   }

   ofs << tab(in) << "}\n\n";
}

void
code_in_protos_cpp(ofstream &ofs, int in, std::vector<string> &polys)
{
   if (polys.size() == 0)
      return;

   for (size_t i = 0; i < polys.size() ; i++) {
      ofs <<tab(in)<< polys[i] <<"* read_" << polys[i]
                  <<"(read_context &ctx);\n";
   }

   ofs << "\n";
}

void
vp_typedef_poly::serialize_in_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   code_in_protos_cpp(ofs, in, polys);

   ofs <<tab(in)<< type_name <<"* read_" << type_name
      << "(read_context &ctx)\n";
   ofs <<tab(in)<< "{\n";

   ofs <<tab(in+1)<< type_name <<"* payload_ptr; int t; read_int(ctx, t);\n";

   for (size_t i = 0; i < polys.size() ; i++)
   {
      ofs <<tab(in+1)<< "if (t == " << i << ")\n";
      ofs <<tab(in+2)<< "payload_ptr = read_" << polys[i] << "(ctx);\n";
   }

   ofs <<tab(in+1)<< "auto &payload = *payload_ptr;\n";

   for (auto jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_in_cpp(ofs, in + 1, type_map, tar_lang);
   }

   ofs <<tab(in+1)<<"return payload_ptr;\n";
   ofs <<tab(in)<< "}\n\n";
}

// --- python ------------------------------------------------------------------

void
vp_typedef_poly::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs << "def write_" << type_name << "(ctx, payload):\n";

   if (parent_name.size() == 0) {
      Terminals terms;

      get_terminals(terms, type_map);

      ofs << "\tc = type(payload).__name__\n";

      for (size_t i = 0; i < terms.size() ; i++) {
         ofs << "\tif (c == \"" << terms[i].name << "\"):\n";

         size_t k = terms[i].layers.size() - 1;
         for (size_t j = 0;  j < terms[i].layers.size(); j++, k--)
            ofs << "\t\twrite_int(ctx,"
                     << terms[i].layers[k] << ")\n";

         ofs << "\t\twrite_" << terms[i].name
                     << "(ctx, payload)\n";
      }
   }

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_out_py(ofs, in + 1, type_map, tar_lang);
   }

   ofs << "\n\n";
}

void
vp_typedef_poly::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs << "def read_" << type_name << "(ctx):\n";

   ofs << "\tt = read_int(ctx)\n";

   for (size_t i = 0; i < polys.size() ; i++)
   {
      ofs << "\tif (t == " << i << "):\n";
      ofs << "\t\tpayload = read_" << polys[i] << "(ctx)\n";
   }

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj)
   {
      (*jj)->serialize_in_py(ofs, in + 1, type_map, tar_lang);
   }

   ofs << "\treturn payload\n\n";
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_poly::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<<"write_"<< type_name <<": function(ctx, payload) {\n";

   if (parent_name.size() == 0) {
      Terminals terms;

      get_terminals(terms, type_map);

      ofs << tab(in+1) << "var c = payload.constructor.name;\n";

      for (size_t i = 0; i < terms.size() ; i++) {
         ofs << tab(in+1) << "if (c == '" << terms[i].name << "') {\n";

         size_t k = terms[i].layers.size() - 1;
         for (size_t j = 0;  j < terms[i].layers.size(); j++, k--)
            ofs << tab(in+2) <<"ctx.write_Integer("<< terms[i].layers[k] <<")\n";

         ofs << tab(in+2) << "this.write_" << terms[i].name
                  << "(ctx, payload)\n";
         ofs << tab(in+1) << "}\n";

      }
   }

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj)   {
      (*jj)->serialize_out_js(ofs, in + 1, type_map, tar_lang);
   }

   ofs << tab(in) <<"},\n\n";
}

void
vp_typedef_poly::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "read_"<< type_name <<": function(ctx) {\n";

   ofs <<tab(in+1)<< "var t = ctx.read_Integer(ctx)\n";
   ofs << tab(in+1) << "var payload;\n";

   for (size_t i = 0; i < polys.size() ; i++) {
      ofs <<tab(in+1)<< "if (t == " << i << ") {\n";
      ofs <<tab(in+2) << "payload = this.read_" << polys[i]
         << "(ctx)\n";
      ofs <<tab(in+1)<< "}\n";
   }

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_in_js(ofs, in + 1, type_map, tar_lang);
   }

   ofs <<tab(in+1)<< "return payload;\n";

   ofs <<tab(in)<< "},\n\n";
}

std::string
vp_typedef_poly::format_in_js(const std::string var_name)
{
   return "var " + var_name + ":" + type_name
      + " = read_" + type_name + "(ver, input)\n";
}

//------------------------------------------------------------------------------

bool vp_typedef_poly::is_terminal() { return false; }
bool vp_typedef_poly::is_pod() { return false; }

void
vp_typedef_poly::get_terminals(Terminals &terminals, const TypeMap &type_map)
{
   for (size_t i = 0; i < polys.size() ; i++) {
      vp_typedef *p = GetVPType(polys[i], type_map);

      if (p->is_terminal()) {
         Terminal n;

         n.name = p->type_name;
         n.layers.push_back(i);
         n.layer_names.push_back(p->type_name);

         terminals.push_back(n);
      } else {
         size_t c1, c2, c_added;

         c1 = terminals.size();

         p->get_terminals(terminals, type_map);

         c2 = terminals.size();

         c_added = c2 - c1;

         Terminals::reverse_iterator ii;
         ii = terminals.rbegin();

         for (size_t k = 0; k < c_added; k++) {
            ii->layers.push_back(i);
            ii->layer_names.push_back(p->type_name);
            ii++;
         }
      }
   }
}

// ## add_subclass

void vp_typedef_poly::add_subclass(const std::string &t)
{
   polys.push_back(t);

};

// ## add_pod_item

void vp_typedef_poly::add_pod_item(pod_item *new_item)
{
   pod_items.push_back(new_item);
}

// ## add_pod_item_range
void vp_typedef_poly::add_pod_item_range(unsigned int nBegin, unsigned int nEnd)
{
   PodItems::reverse_iterator jj;

   jj = pod_items.rbegin();

   (*jj)->nBegin = nBegin;
   (*jj)->nEnd = nEnd;
}

// ## get_type_python
void vp_typedef_poly::get_type_python(std::string &result)
{
   result = type_name;
}

// ## get_type_cpp
void vp_typedef_poly::get_type_cpp(std::string &result)
{
   result = type_name;

}

// ## get_type_js
void vp_typedef_poly::get_type_js(std::string &result)
{
   result = type_name;

}

std::string vp_typedef_poly::format_in_py(const std::string var_name)
{
   return var_name + " = read_" + type_name + "(ctx)\n";
}

