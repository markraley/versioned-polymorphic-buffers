// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#include "shared_header.h"
#include "vp_typedef_pod.h"

void
vp_typedef_pod::add_pod_item(pod_item *new_item)
{
   pod_items.push_back(new_item);
}

void
vp_typedef_pod::add_pod_item_range(unsigned int nBegin, unsigned int nEnd)
{
   PodItems::reverse_iterator jj;

   jj = pod_items.rbegin();

   (*jj)->nBegin = nBegin;
   (*jj)->nEnd = nEnd;
}

void
vp_typedef_pod::get_type_python(std::string &result)
{
   result = type_name;
}

void
vp_typedef_pod::get_type_cpp(std::string &result)
{
   result = type_name;
}

void
vp_typedef_pod::get_type_js(std::string &result)
{
   result = type_name;
}

std::string
vp_typedef_pod::format_in_py(const std::string var_name)
{
   return var_name + " = read_" + type_name + "(ver, f)\n";
}

// --- cpp ---------------------------------------------------------------------

void
vp_typedef_pod::serialize_out_cpp(
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
      << "(long nVersion, "
      << "write_context &wc, " << type_name << " &payload)\n";
   ofs << tab(in) << "{\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_out_cpp(ofs, in + 1, type_map, tar_lang);
   }

   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<<"write_"<< parent_name <<"(nVersion, wc, payload);\n";
   }

   ofs << tab(in) << "}\n\n";
}

void
vp_typedef_pod::serialize_in_cpp(
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
         << "(long nVersion, "
         << "read_context &rc)\n";
      ofs <<tab(in)<< "{\n";
      ofs <<tab(in+1)<< "auto *payload_ptr = new "<< type_name <<";\n";
      ofs <<tab(in+1)<< "auto &payload = *payload_ptr;\n";

      for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
         (*jj)->serialize_in_cpp(ofs, in + 1, type_map, tar_lang);
      }
      ofs <<tab(in+1)<< "return payload_ptr;\n";

      ofs << tab(in) << "}\n\n";
   }

   ofs <<tab(in)<< "void read_" << type_name
      << "(long nVersion, "
      << "read_context &rc, "
      << type_name << " &payload)\n";
   ofs <<tab(in)<< "{\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_in_cpp(ofs, in + 1, type_map, tar_lang);
   }

   ofs << tab(in) << "}\n\n";
}

// --- python ------------------------------------------------------------------

void
vp_typedef_pod::serialize_out_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "def write_" << type_name << "(ver, f, payload):\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_out_py(ofs, in + 1, type_map, tar_lang);
   }

   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<< "write_" << parent_name << "(ver, f, payload)\n";
   }

   ofs << "\n";
}

void
vp_typedef_pod::serialize_in_py(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "def read_" << type_name << "(ver, f):\n";

   ofs <<tab(in+1)<< "payload = " << type_name << "()\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_in_py(ofs, in + 1, type_map, tar_lang);
   }

   ofs <<tab(in+1)<< "return payload\n\n";
}

// --- javascript --------------------------------------------------------------

void
vp_typedef_pod::serialize_out_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<<"write_"<< type_name <<": function(ver, wc, payload) {\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_out_js(ofs, in + 1, type_map, tar_lang);
   }

   if (parent_name.size() > 0) {
      vp_typedef *p = GetVPType(parent_name, type_map);

      if (p->parent_name.size() > 0)
         ofs <<tab(in+1)<< "this.write_" << parent_name << "(ver, wc, payload)\n";
   }

   ofs << tab(in) << "},\n\n";
}

void
vp_typedef_pod::serialize_in_js(
   ofstream &ofs,
   int in,
   TypeMap &type_map,
   TarLang &tar_lang)
{
   PodItems::iterator jj;

   // check if this typedef is in the targeted version range
   if (!this->vrange.overlap(tar_lang.start, tar_lang.end))
      return;

   ofs <<tab(in)<< "read_"<< type_name <<": function(ver, rc) {\n";

   ofs <<tab(in+1) <<"var payload = new this.factory." << type_name << "();\n";

   for (jj = pod_items.begin(); jj != pod_items.end(); ++jj) {
      (*jj)->serialize_in_js(ofs, in + 1, type_map, tar_lang);
   }

   ofs <<tab(in+1)<< "return payload;\n";
   ofs <<tab(in)<< "},\n\n";
}

string
vp_typedef_pod::format_in_js(const string var_name)
{
   return "var " + var_name + " = this.read_" + type_name + "(ver, rc)\n";
}

// ----------------------------------------------------------------------------

bool vp_typedef_pod::is_terminal() { return true; }
bool vp_typedef_pod::is_poly() { return false; }
bool vp_typedef_pod::is_pod() { return true; }
void vp_typedef_pod::add_subclass(const std::string &t) {}
void vp_typedef_pod::get_terminals
   (Terminals &terminals, const TypeMap &type_map) {}



