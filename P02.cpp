bool okUp(vector<int> &v, int ignore) {
  int prev;
  bool any = false;
  FORUI(v.size()) {
    int cur = v[i];
    if(i == ignore) {
      continue;
    }
    if(!any) {
      prev = cur;
      any = true;
      continue;
    }
    int d = cur-prev;
    if(d < 1 || d > 3)
      return false;
    prev = cur;
  }
  return true;
}

bool okDown(vector<int> &v, int ignore) {
  int prev;
  bool any = false;
  FORUI(v.size()) {
    int cur = -v[i];
    if(i == ignore) {
      continue;
    }
    if(!any) {
      prev = cur;
      any = true;
      continue;
    }
    int d = cur-prev;
    if(d < 1 || d > 3)
      return false;
    prev = cur;
  }
  return true;
}

int main() {
  int answer1 = 0, answer2 = 0;
  string line;
  while(getline(cin, line)) {
    stringstream ss;
    ss << line;
    vector<int> v;
    int cur;
    while(ss >> cur) {
      v.push_back(cur);
    }

    bool u = okUp(v, -1);
    bool d = okDown(v, -1);
    if(u || d) {
      answer1++;
    }

    bool u2 = false;
    FORUI(v.size()) {
      if(okUp(v, (int)i)) {
	u2 = true;
	break;
      }
    }
    FORUI(v.size()) {
      if(okDown(v, (int)i)) {
	u2 = true;
	break;
      }
    }
    if(u2) {
      answer2++;
    }
    
  }
  cout << answer1 << endl;
  cout << answer2 << endl;
}
