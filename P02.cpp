#include <regex>

string all;
int idx = 0;

LL read() {
  LL ret = 0;
  while(true) {
    char c = all[idx++];
    if(c >= '0' && c <= '9') {
      ret = 10 * ret + c - '0';
    }
    else
      return ret;
  }
}

int main() {
  LL answer = 0; // long needed this time!
  regex R("^(.+)\\1+$"); // For answer 1: No "+"

  cin >> all;

  while(idx < (int)all.size()) {
    LL from = read();
    LL to = read();
    for(LL i = from ; i <= to; i++) {
      string s = to_string(i);
      if(regex_match(s, R)) {
	cout << from << "-" << to << " Invalid " << s << endl;
	answer += i;
      }
    }
  }

  cout << "Answer: " << answer << endl;
}
