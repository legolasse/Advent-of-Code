vector<string> presents;
vector<int> presentSizes;
int w, h, a[6];

bool guess() {
  // Is there even enough space?
  int total = w * h;
  FORUI(presents.size()) {
    total -= presentSizes[i] * a[i];
  }
  cout << w << " * " << h << " = " << (w*h) << ": " << total << endl;

  return total > 0;
}

int main() {
  int answer = 0;
  string s;

  while(cin >> s) {
    stringstream ss;
    if(s.size() == 2) {
      // Present:
      FORI(3) {
	cin >> s;
	ss << s;
      }
      string present = ss.str();
      presents.push_back(present);
      int presentSize = 0;
      FORJ(9) {
	char c = present[j];
	if(c == '#')
	  presentSize++;
      }
      cout << "Size of present " << presentSizes.size() << ": " << presentSize << endl;
      presentSizes.push_back(presentSize);
    }
    else {
      s[2] = s[5] = ' ';
      ss << s;
      ss >> w >> h;
      FORUI(presents.size())
	cin >> a[i];
      if(guess())
	answer1++; // Apparently this guess is sufficient...
    }
  }

  cout << "Answer: " << answer << endl;
}
