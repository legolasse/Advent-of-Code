#include <regex>

int main() {
  LL answer1 = 0, answer2 = 0;
  regex R("mul\\(([\\d]{1,3})\\,([\\d]{1,3})\\)|do\\(\\)|don\\'t\\(\\)");
  bool enabled = true;

  string line, start = "mul(";
  while(getline(cin, line)) {
    string::const_iterator searchStart(line.cbegin());
    std::smatch M;

    // Scan for mul(123)
    while(regex_search(searchStart, line.cend(), M, R)) {
      searchStart = M.suffix().first;

      if(M[0] == "do()") {
	enabled = true;
	continue;
      }
      if(M[0] == "don't()") {
	enabled = false;
	continue;
      }

      answer1 += stoi(M[1]) * stoi(M[2]);
      if(enabled)
	answer2 += stoi(M[1]) * stoi(M[2]);
    }
  }
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
