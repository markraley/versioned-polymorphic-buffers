// Software released under the MIT license (see project root for license file)

using namespace std;

typedef char byte;
typedef vector<byte> ByteVec;

// -----------------------------------------------------------------------------

void
pushInteger(std::vector<byte> &buf_arr, int i) {
   if (i >= 0 && i <= 0x7F) {
      buf_arr.push_back((byte) i);
   } else if (i > 0x7F && i <= 0x3FFF) {
      buf_arr.push_back(byte(i >> 7 | 0x80));
      buf_arr.push_back(byte(i & 0x7F));
   } else if (i > 0x3FFF && i <= 0x1FFFFF) {
      buf_arr.push_back(byte(i >> 14 | 0x80));
      buf_arr.push_back(byte(((i >> 7) & 0x7F) | 0x80));
      buf_arr.push_back(byte(i & 0x7F));
   } else {
      buf_arr.push_back(byte(i >> 22 | 0x80));
      buf_arr.push_back(byte(((i >> 15) & 0x7F) | 0x80));
      buf_arr.push_back(byte(((i >> 8 ) & 0x7F) | 0x80));
      buf_arr.push_back(byte(i & 0xFF));
   }
}


void
pullInteger(
      std::vector<byte>::const_iterator &ii,
      std::vector<byte>::const_iterator jj,
      int &val,
      int max_bytes = 4
   )
{
   int i = 0;
   val = 0;

   if (ii == jj)
      throw std::out_of_range("iterator out of range");

   if (max_bytes < 1 or max_bytes > 8)
      throw std::out_of_range("max_bytes out of range");

   while (i++ < (max_bytes - 1) && *ii & 0x80) {
      val = (val << 7) | (*ii++ & 0x7F);

      if (ii == jj)
         throw std::out_of_range("iterator range error");
   }

   val <<= (i <= 3 ? 7 : 8);
   val |= *ii++;

   val <<= 3;
   val >>= 3;
}

// -----------------------------------------------------------------------------

class read_context {
   public:
      map<string, ReorderCog *> reorder_map;
      ByteVec buf_arr;
      ByteVec::const_iterator ii;

      size_t get_buffer_size() { return buf_arr.size(); }

      read_context(string file_name)
      {
         std::ifstream ifile(file_name, std::ifstream::binary);
         ByteVec in_arr(std::istreambuf_iterator<char>(ifile), {});
         ifile.close();

         buf_arr = in_arr;
         ii = buf_arr.cbegin();
      }
};

class write_context {
   public:
      map<string, ReorderCog *> reorder_map;
      std::vector<byte> buf_arr;

      size_t write_file(string file_name)
      {
         std::ofstream ofile1(file_name, std::ofstream::binary);
         for (auto i = 0; i < buf_arr.size(); i++)
            ofile1 << buf_arr[i];
         ofile1.close();

         return (buf_arr.size());
      }
};

// -----------------------------------------------------------------------------

void write_int(write_context &wc, int i)
{
   pushInteger(wc.buf_arr, (int) 4); // tag
   pushInteger(wc.buf_arr, i);

}

void write_int(long nVersion, write_context &wc, int i)
{
   pushInteger(wc.buf_arr, (int) 4); // tag
   pushInteger(wc.buf_arr, i);

}

void read_int(read_context &rc, int &i)
{
   int tag = 0;
   pullInteger(rc.ii, rc.buf_arr.cend(), tag, 1);
   pullInteger(rc.ii, rc.buf_arr.cend(), i);
}

void read_int(long nVersion, read_context &rc, int &i)
{
   int tag = 0;
   pullInteger(rc.ii, rc.buf_arr.cend(), tag, 1);
   pullInteger(rc.ii, rc.buf_arr.cend(), i);
}

// -----------------------------------------------------------------------------

void write_string(write_context &wc, std::string &s)
{
   pushInteger(wc.buf_arr, (int) 6);  // tag
   pushInteger(wc.buf_arr, (s.length() << 1) | 0x1);
   for (int j = 0; j < s.length(); j++)
      wc.buf_arr.push_back(s[j]);
}

void write_string(long nVersion, write_context &wc, std::string &s)
{
   pushInteger(wc.buf_arr, (int) 6);  // tag
   pushInteger(wc.buf_arr, (s.length() << 1) | 0x1);
   for (int j = 0; j < s.length(); j++)
      wc.buf_arr.push_back(s[j]);
}

void read_string(read_context &rc, std::string &s)
{
   int tag = 0;
   int str_len = 0;

   pullInteger(rc.ii, rc.buf_arr.cend(), tag, 1);
   pullInteger(rc.ii, rc.buf_arr.cend(), str_len);

   s = "";
   str_len = str_len >> 1;

   for (int k = 0; k < str_len; k++) {
      char c;
      c = (char) (*rc.ii++);
      s.push_back(c);
   }
}

void read_string(long nVersion, read_context &rc, std::string &s)
{
   int tag = 0;
   int str_len = 0;

   pullInteger(rc.ii, rc.buf_arr.cend(), tag, 1);
   pullInteger(rc.ii, rc.buf_arr.cend(), str_len);

   s = "";
   str_len = str_len >> 1;

   for (int k = 0; k < str_len; k++) {
      char c;
      c = (char) (*rc.ii++);
      s.push_back(c);
   }
}
