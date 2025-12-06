int main() {
  LL answer1 = 0, answer2 = 0;
  string s;
  vector<vector<LL> > M;
  vector<string> v;
  int w, h = 0, W = 0;

  while(getline(cin, s)) {
    v.push_back(s);
    if(s[0] == '+' || s[0] == '*')
      break;
    stringstream ss; ss << s;
    LL x;
    vector<LL> v;
    while(ss >> x) {
      v.push_back(x);
    }
    w = (int)v.size();
    M.push_back(v);
    h++;

    // For part 2:
    W = MAX(W, (int)s.size());
  }

  // Part 1:
  stringstream ss; ss << s;
  char c;
  FORX(w) {
    ss >> c;
    LL l = c == '*';
    FORY(h) {
      if(c == '*')
	l *= M[y][x];
      else
	l += M[y][x];
    }
    answer1+=l;
  }

  // Part 2:
  vector<LL> numbers;
  for(int x = W-1; x >= 0; x--) {
    // Add new number:
    LL number = 0;
    FORY(h) {
      char c = v[y][x];
      if(c != ' ')
	number = 10 * number + c - '0';
    }
    numbers.push_back(number);

    char op = v[h][x];
    LL l = op == '*';
    if(op != ' ') {
      FORIT(vector<LL>, numbers) {
	if(op == '*')
	  l *= *it;
	else
	  l += *it;
      }
      answer2 += l;
      numbers.clear();
      x--; // Skip empty column
    }
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
