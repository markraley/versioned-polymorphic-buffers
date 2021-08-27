// Versioned Polymorphic Buffers (vpbuf) - data interchange format
//    Copyright Mark Raley, All Rights Reserved, https://github.com/markraley
//    Software release is via MIT license (see project root for license file)

#pragma once

using boost::phoenix::function;
using boost::phoenix::ref;

using boost::spirit::qi::unused_type;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

typedef std::ofstream ofstream;
typedef std::string string;

enum {
   VPTypePod = 0,
   VPTypePoly,
   VPTypeVector,
   VPTypeIntrinsic,
   VPTypeReorderPod
} vp_typedef_types;

struct target_language // just this way for boost interface
{
   string name;
   string name_space;
   unsigned int start, end; // first and last versions to be generated
   string path_out;
   string file_ext;
};

typedef struct VRange {
   unsigned int nBegin;
   unsigned int nEnd;
   VRange() : nBegin(1), nEnd(0) {};
   bool overlap(unsigned int nBase, unsigned int nLimit);
} VRange;

BOOST_FUSION_ADAPT_STRUCT(
    target_language,
    (string, name)
    (unsigned int, start)
    (unsigned int, end)
    (string, name_space)
    (string, path_out)
    (string, file_ext)
)

typedef struct
{
   std::vector <unsigned int> layers;  // vp_typedef index
   std::vector <string> layer_names;   // type name of layer
   string name;
} Terminal;

typedef std::vector<Terminal> Terminals;
struct impl_specifier
{
   string name;
};

struct vp_typedef;

typedef std::map<string, impl_specifier> ImplMap;
typedef std::map<string, vp_typedef *> TypeMap;
typedef struct target_language TarLang;

struct pod_item;

struct vp_typedef
{
   string type_name;
   ImplMap impls;
   string parent_name;
   VRange vrange;

   virtual void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual void serialize_out_py(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_py(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual void serialize_out_js(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_js(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual string format_in_py(const string var_name) = 0;
   virtual string format_in_js(const string var_name) = 0;

   virtual void get_type_python(string &) = 0;
   virtual void get_type_cpp(string &) = 0;
   virtual void get_type_js(string &) = 0;

   virtual void add_pod_item(pod_item *) = 0;
   virtual void add_pod_item_range(unsigned int nBegin, unsigned int nEnd) = 0;
   virtual void add_subclass(const string &) = 0;
   virtual bool is_terminal() = 0;
   virtual bool is_poly() = 0;
   virtual bool is_pod() = 0;
   virtual void get_terminals(Terminals &, const TypeMap &) = 0;
   void add_range(unsigned int nBegin, unsigned int nEnd);

};

typedef std::vector <vp_typedef *> TypeVector;

struct pod_item
{
   pod_item() : nBegin(1), nEnd(0) {}
   string name;
   unsigned int nBegin;
   unsigned int nEnd;

   virtual void serialize_out_cpp(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_cpp(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual void serialize_out_py(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_py(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual void serialize_out_js(ofstream &, int, TypeMap &, TarLang &) = 0;
   virtual void serialize_in_js(ofstream &, int, TypeMap &, TarLang &) = 0;

   virtual string declare_js() = 0;
};

typedef std::vector<pod_item *> PodItems;

#define INTRINSIC_COUNT 3

void code_version_test_cpp(ofstream&, bool&, bool&, int, int, int, int, int);
bool code_version_test_py(ofstream&, int&, int, int, int, int);
void code_version_test_js(ofstream&, bool&, bool&, int, int, int, int, int);

string tab(int n);
vp_typedef *GetVPType(string &type_name, const TypeMap &);
