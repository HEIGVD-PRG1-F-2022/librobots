#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, const string &sep, size_t max_sep) {
  vector<string> ret;
  size_t last = 0;
  size_t next = 0;
  while ((next = s.find(sep, last)) != string::npos &&
         (ret.size() < max_sep || max_sep == 0)) {
    ret.push_back(s.substr(last, next - last));
    last = next + 1;
  }
  ret.push_back(s.substr(last));
  return ret;
}
