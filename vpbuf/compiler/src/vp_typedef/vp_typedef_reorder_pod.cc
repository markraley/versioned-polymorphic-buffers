// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_reorder_pod.h"

void
vp_typedef_reorder_pod::add_pod_item(pod_item *new_item)
{
   pod_items.push_back(new_item);
}

void
vp_typedef_reorder_pod::add_pod_item_range(
   unsigned int nBegin,
   unsigned int nEnd)
{
   PodItems::reverse_iterator jj;

   jj = pod_items.rbegin();

   (*jj)->nBegin = nBegin;
   (*jj)->nEnd = nEnd;
}

void
vp_typedef_reorder_pod::get_type_python(std::string &result)
{
   result = type_name;
}

void
vp_typedef_reorder_pod::get_type_cpp(std::string &result)
{
   result = type_name;
}

void
vp_typedef_reorder_pod::get_type_js(std::string &result)
{
   result = type_name;
}

std::string
vp_typedef_reorder_pod::format_in_py(const std::string var_name)
{
   return var_name + " = read_" + type_name + "(ctx)\n";
}

void vp_typedef_reorder_pod::gen_cpp_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // ------ vlist

   ofs <<tab(in)<< "vector<tuple<int, int>> vlist_"<< type_name <<" = {\n";
   auto jj_last = prev(pod_items.end());
   for (auto jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+1)<<"{ "<< (*jj)->nBegin <<", "<< (*jj)->nEnd <<" }";
      if (jj_last == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "};\n\n";

   // ------- rlist

   ofs <<tab(in)<< "vector<tuple<int, int, string>> rlist_"
               << type_name <<" = {\n";
   auto jj_rlast = prev(vptype_options.end());
   for (auto jj = vptype_options.begin(); jj != vptype_options.end(); ++jj) {
      ofs <<tab(in+1)<<"{ "
                  << (*jj).vrange.nBegin <<", "
                  << (*jj).vrange.nEnd <<", "
                  <<"\""<< (*jj).opt_name <<"\"}";
      if (jj_rlast == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "};\n\n";

   // ------ rcog_factory

   ofs <<tab(in)<< "ReorderCog *rcog_factory_"<< type_name
                     <<"(string &n, vector<int> v, uint seed) {\n";

   for (auto jj = vptype_options.begin(); jj != vptype_options.end(); ++jj) {
      ofs <<tab(in+1)<< "if (n == \"" << (*jj).opt_name <<"\")\n";
      ofs <<tab(in+2)<< "return new "<< (*jj).opt_class <<"(v, seed);\n";
   }

   ofs <<tab(in+1)<< "return(NULL);\n";
   ofs <<tab(in)<< "}\n\n";

   // ------ get_vlist

   ofs <<tab(in)<< "vector<int> get_vlist_"<< type_name <<"(int ver) {\n";

   ofs <<tab(in+1)<< "vector<int> v; int i = 0;\n";
   ofs <<tab(in+1)<< "for (auto tt = vlist_"<< type_name
                     <<".begin(); tt != vlist_"
                     << type_name <<".end(); tt++, i++) {\n";
   ofs <<tab(in+2)<< "if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) "<<
            "|| (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {\n";
   ofs <<tab(in+3)<< "v.push_back(i);\n";
   ofs <<tab(in+2)<< "}\n";

   ofs <<tab(in+1)<< "};\n\n";


   ofs <<tab(in+1)<< "return v;\n";
   ofs <<tab(in)<< "}\n\n";

   // ------ get_rcog

   ofs <<tab(in)<< "ReorderCog *get_rcog_"<< type_name
                              <<"(int ver, uint seed) {\n";

   ofs <<tab(in+1)<< "for (auto tt = rlist_"<< type_name
                     <<".begin(); tt != rlist_"
                     << type_name <<".end(); tt++) {\n";
   ofs <<tab(in+2)<< "if ((get<1>(*tt) == 0 && ver >= get<0>(*tt)) "<<
            "|| (ver >= get<0>(*tt) && ver <= get<1>(*tt))) {\n";
   ofs <<tab(in+3)<<"return rcog_factory_" << type_name
                  <<"(get<2>(*tt), get_vlist_"<< type_name <<"(ver), seed);\n";
   ofs <<tab(in+2)<< "}\n";

   ofs <<tab(in+1)<< "};\n\n";


   ofs <<tab(in+1)<< "return(new IdentityReorderCog(get_vlist_"
                           << type_name <<"(ver)));\n";
   ofs <<tab(in)<< "}\n\n";

}

void vp_typedef_reorder_pod::gen_js_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   // ------ vlist

   ofs <<tab(in)<< "vlist_"<< type_name <<": [\n";
   auto jj_last = prev(pod_items.end());
   for (auto jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+1)<<"[ "<< (*jj)->nBegin <<", "<< (*jj)->nEnd <<" ]";
      if (jj_last == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "],\n\n";

   // vlist wrapper function

   ofs <<tab(in)<< "get_vlist_"<< type_name <<": function(ver) {\n";

   ofs <<tab(in+1)<< "var v = [];\n";
   ofs <<tab(in+1)<< "this.vlist_"<< type_name <<".forEach(function(p, i) {\n";
   ofs <<tab(in+2)<< "if ((p[1] == 0 && ver >= p[0]) "<<
            "|| (ver >= p[0] && ver <= p[1])) {\n";
   ofs <<tab(in+3)<< "v.push(i);\n";
   ofs <<tab(in+2)<< "}\n";

   ofs <<tab(in+1)<< "});\n";


   ofs <<tab(in+1)<< "return v;\n";

   ofs <<tab(in)<< "},\n\n";

   // ------- rlist

   ofs <<tab(in)<< "rlist_"<< type_name <<": [\n";
   auto jj_rlast = prev(vptype_options.end());
   for (auto jj = vptype_options.begin(); jj != vptype_options.end(); ++jj) {
      ofs <<tab(in+1)<<"[ "
                  << (*jj).vrange.nBegin <<", "
                  << (*jj).vrange.nEnd <<", "
                  <<"'"<< (*jj).opt_name  <<"', persist."
                  << (*jj).opt_class
                  <<" ]";
      if (jj_rlast == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "],\n\n";

   // ------ rlist wrapper function

   ofs <<tab(in)<< "get_rlist_"<< type_name <<": function (ver, seed) {\n";

   ofs <<tab(in+1)<< "for (var i = 0; i < this.rlist_"
                     << type_name << ".length; i++) {\n";
   ofs <<tab(in+2)<< "var p = this.rlist_"<< type_name <<"[i]\n";
   ofs <<tab(in+2)<< "if ((p[1] == 0 && ver >= p[0]) "<<
            "|| (ver >= p[0] && ver <= p[1]))\n";
   ofs <<tab(in+3)<< "return [p[2], p[3](this.get_vlist_"
                     << type_name <<"(ver), seed)]\n";
   ofs <<tab(in+1)<< "}\n";

   ofs <<tab(in+1)<<"return ['ident', persist.IdentityScrambler(this.get_vlist_"
                     << type_name <<"(ver))]\n";

   ofs <<tab(in)<< "},\n\n";

}

// --- cpp ---------------------------------------------------------------------

void
vp_typedef_reorder_pod::serialize_out_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs << tab(in) << "void write_" << type_name
      << "(write_context &ctx, " << type_name << " &payload)\n";
   ofs << tab(in) << "{\n";

   ofs << tab(in+1) << "vector<int> v((*ctx.reorder_map[\""
      << type_name <<"\"])());\n\n";

   int j = 0;
   ofs <<tab(in+1)<< "for (auto i : v) \n";
   ofs <<tab(in+2)<< "switch(i) {\n";;
   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+3)<< "case "<< j++ <<":\n";
      (*jj)->serialize_out_cpp(ofs, in+3, type_map, tar_lang);
      ofs <<tab(in+3)<< "break;\n";
   }
   ofs <<tab(in+2)<< "}\n";


   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<<"write_"<< parent_name <<"(ctx, payload);\n";
   }

   ofs << tab(in) << "}\n\n";
}

void
vp_typedef_reorder_pod::serialize_in_cpp(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;
   bool is_polymorphic = (parent_name.size() > 0);

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   if (is_polymorphic) {
      ofs <<tab(in)<< type_name <<" *read_" << type_name
         << "(read_context &ctx)\n";
      ofs <<tab(in)<< "{\n";
      ofs <<tab(in+1)<< "auto *payload_ptr = new "<< type_name <<";\n";
      ofs <<tab(in+1)<< "auto &payload = *payload_ptr;\n";

      ofs << tab(in+1) << "vector<int> v((*ctx.reorder_map[\""
         << type_name <<"\"])());\n\n";

      int j = 0;
      ofs <<tab(in+1)<< "for (auto i : v) \n";
      ofs <<tab(in+2)<< "switch(i) {\n";;
      for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
         ofs <<tab(in+3)<< "case "<< j++ <<":\n";
         (*jj)->serialize_in_cpp(ofs, in+4, type_map, tar_lang);
         ofs <<tab(in+4)<< "break;\n";
      }
      ofs <<tab(in+2)<< "}\n";

      ofs <<tab(in+1)<< "return payload_ptr;\n";

      ofs << tab(in) << "}\n\n";
   }

   ofs <<tab(in)<< "void read_" << type_name
      << "(read_context &ctx, "
      << type_name << " &payload)\n";
   ofs <<tab(in)<< "{\n";

   ofs << tab(in+1) << "vector<int> v((*ctx.reorder_map[\""
      << type_name <<"\"])());\n\n";

   int j = 0;
   ofs <<tab(in+1)<< "for (auto i : v) \n";
   ofs <<tab(in+2)<< "switch(i) {\n";;
   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+3)<< "case "<< j++ <<":\n";
      (*jj)->serialize_in_cpp(ofs, in+4, type_map, tar_lang);
      ofs <<tab(in+4)<< "break;\n";
   }
   ofs <<tab(in+2)<< "}\n";

   ofs << tab(in) << "}\n\n";
}

// --- python ------------------------------------------------------------------

void vp_typedef_reorder_pod::gen_py_utils(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{

   // vlist

   ofs <<tab(in)<< "vlist_"<< type_name <<" = [\n";
   auto jj_last = prev(pod_items.end());
   for (auto jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+1)<<"( "<< (*jj)->nBegin <<", "<< (*jj)->nEnd <<" )";
      if (jj_last == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "]\n\n";

   // vlist wrapper function

   ofs <<tab(in)<< "def get_vlist_"<< type_name <<"(ver):\n";

   ofs <<tab(in+1)<< "c, v = 0, []\n";

   ofs <<tab(in+1)<< "for p in vlist_"<< type_name<< ":\n";
   ofs <<tab(in+2)<< "if (p[1] == 0 and ver >= p[0]) "<<
            "or (ver >= p[0] and ver <= p[1]):\n";
   ofs <<tab(in+3)<< "v.append(c)\n";
   ofs <<tab(in+3)<< "c += 1\n";

   ofs <<tab(in+1)<< "return v\n";

   ofs << "\n";

   // ------ rlist

   ofs <<tab(in)<< "rlist_"<< type_name <<" = [\n";
   auto jj_rlast = prev(vptype_options.end());
   for (auto jj = vptype_options.begin(); jj != vptype_options.end(); ++jj) {
      ofs <<tab(in+1)<<"( "
                  << (*jj).vrange.nBegin <<", "
                  << (*jj).vrange.nEnd <<", "
                  <<"'"<< (*jj).opt_name  <<"', "
                  << (*jj).opt_class
                  <<" )";
      if (jj_rlast == jj)
         ofs << "\n";
      else
         ofs << ",\n";

   }
   ofs <<tab(in)<< "]\n\n";

   // ------ rlist wrapper function

   ofs <<tab(in)<< "def get_rlist_"<< type_name <<"(ver, seed):\n";

   ofs <<tab(in+1)<< "for p in rlist_"<< type_name<< ":\n";
   ofs <<tab(in+2)<< "if (p[1] == 0 and ver >= p[0]) "<<
            "or (ver >= p[0] and ver <= p[1]):\n";
   ofs <<tab(in+3)<< "return [p[2], p[3](get_vlist_"
                           << type_name <<"(ver), seed)]\n";

   ofs <<tab(in+1)<< "return ['ident', IdentityScrambler(get_vlist_"
                           << type_name <<"(ver))]\n";

   ofs << "\n";
}

// --- python ------------------------------------------------------------------

void
vp_typedef_reorder_pod::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "def write_"<< type_name <<"(ctx, payload):\n";

   ofs <<tab(in+1)<< "for i in ctx.reorder_map['"<< type_name <<"'][1]():\n";
   int k = 0;
   // TODO: replace this with match/case when available
   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+2)<< ((jj == pod_items.begin())?"if":"elif")
                                                <<" i=="<< k++ <<":\n";
      (*jj)->serialize_out_py(ofs, in+3, type_map, tar_lang, true);
   }

   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<< "write_"<< parent_name <<"(ctx, payload)\n";
   }

   ofs << "\n";
}

void
vp_typedef_reorder_pod::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang,
   bool skip_test)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<<"def read_"<< type_name <<"(ctx):\n";

   ofs <<tab(in+1)<<"payload = "<< type_name <<"()\n";

   ofs <<tab(in+1)<< "for i in ctx.reorder_map['"<< type_name <<"'][1]():\n";
   int k = 0;
   // TODO: replace this with match/case when available
   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+2)<< ((jj == pod_items.begin())?"if":"elif")
                                                <<" i=="<< k++ <<":\n";
      (*jj)->serialize_in_py(ofs, in+3, type_map, tar_lang, true);
   }

   ofs <<tab(in+1)<< "return payload\n\n";
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_reorder_pod::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;
   int j = 0;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<<"write_"<< type_name <<": function(ctx, payload) {\n";

   ofs <<tab(in+1)<< "var v = ctx.reorder_map['"<< type_name <<"'][1]();\n";
   ofs <<tab(in+1)<< "for (var i = 0; i < v.length; i++)\n";
   ofs <<tab(in+2)<< "switch(v[i]) {\n";
   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+3)<< "case "<< j++ <<":\n";
      (*jj)->serialize_out_js(ofs, in+3, type_map, tar_lang);
      ofs <<tab(in+3)<< "break;\n";
   }

   ofs <<tab(in+2)<< "};\n";

   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<< "this.write_"
                           << parent_name << "(ctx, payload)\n";
   }

   ofs << tab(in) << "},\n\n";
}

void
vp_typedef_reorder_pod::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;
   int j = 0;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "read_"<< type_name <<": function(ctx) {\n";

   ofs <<tab(in+1) <<"var payload = new this.factory." << type_name << "();\n";

   ofs <<tab(in+1)<< "var v = ctx.reorder_map['"<< type_name <<"'][1]();\n";
   ofs <<tab(in+1)<< "for (var i = 0; i < v.length; i++)\n";
   ofs <<tab(in+2)<< "switch(v[i]) {\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      ofs <<tab(in+3)<< "case "<< j++ <<":\n";
      (*jj)->serialize_in_js(ofs, in+3, type_map, tar_lang);
      ofs <<tab(in+3)<< "break;\n";
   }

   ofs <<tab(in+2)<< "};\n";

   ofs <<tab(in+1)<< "return payload;\n";
   ofs <<tab(in)<< "},\n\n";
}

string
vp_typedef_reorder_pod::format_in_js(const string var_name)
{
   return "var " + var_name + " = this.read_" + type_name + "(ctx)\n";
}

// ----------------------------------------------------------------------------

bool vp_typedef_reorder_pod::is_pod() { return true; }
bool vp_typedef_reorder_pod::can_reorder() { return true; }




