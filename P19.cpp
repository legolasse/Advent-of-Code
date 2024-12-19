#include <regex>
vector<string> towels;
map<unsigned int,LL> cache;

LL cnt(unsigned int from, string &design) {
  if(from == design.size()) {
    return 1;
  }
  if(cache.find(from) != cache.end()) {
    return cache[from];
  }

  LL ret = 0;

  FORUI(towels.size()) {
    string &t = towels[i];
    unsigned int L = t.size();
    if(t == design.substr(from, L)) {
      ret += cnt(from + L, design);
    }
  }

  cache[from] = ret;
  return ret;
}

int main() {
  LL answer1 = 0, answer2 = 0;
  string line, towel;
  stringstream ss, ss2;
  bool any = false;

  getline(cin, line);
  FORUI(line.size()) {
    if(line[i] == ',')
      line[i] = ' ';
  }
  ss2 << line;
  while(ss2 >> towel) {
    if(!any) {
      ss << "^(" << towel;
      any = true;
    }
    else {
      ss << "|" << towel;
    }
    towels.push_back(towel);
  }
  ss << ")*$";

  string regexString = ss.str();
  cout << regexString << endl;
  regex R(regexString);
  getline(cin, line); // Blank line

  while(getline(cin, line)) {
    // Part 1: (can use cache.clear();answer1+=cnt(0, line) > 0; for faster results, but working with regex in C++ is so much fun...)
    cmatch M;
    if(regex_match(line.c_str(), M, R)) {
      answer1++;
    }
    // Part 2:
    cache.clear();
    answer2 += cnt(0, line);
  }
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
