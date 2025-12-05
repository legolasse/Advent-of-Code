LL decode(string &s, int &idx) {
  LL ret = 0;
  while(idx < s.size()) {
    char c = s[idx];
    if(c == '-') {
      idx++; // Range indicator
      break;
    }
    ret = 10*ret + c - '0';
    idx++;
  }

  return ret;
}

PLL decodeRange(string &s) {
  int idx = 0;
  return PLL(decode(s,idx),decode(s,idx));
}

int main() {
  LL answer1 = 0, answer2 = 0;
  vector<PLL> ranges1, ranges2;

  string s;

  while(getline(cin, s)) {
    if(s.size() == 0)
      break;
    PLL range = decodeRange(s);
    // Update ranges:
    FORIT(vector<PLL>, ranges1) {
      PLL old = *it;
      if(range.first <= old.first && range.second >= old.second)
	continue; // Old is inside
      else if(range.first >= old.first && range.second <= old.second)
	range = old; // New is inside old: Update
      else if(range.second < old.first || range.first > old.second)
	ranges2.push_back(old); // Outside
      else if(old.first < range.first && old.second >= range.first)
	ranges2.push_back(PLL(old.first, range.first-1));
      else
	ranges2.push_back(PLL(range.second+1, old.second));
    }
    ranges2.push_back(range);

    swap(ranges1,ranges2);
    ranges2.clear();
  }

  // Part 1:
  while(getline(cin, s)) {
    int idx = 0;
    LL ingredient = decode(s, idx);
    bool inRange = false;
    FORIT(vector<PLL>, ranges1) {
      if(it->first <= ingredient && it->second >= ingredient) {
	inRange = true;
	break;
      }
    }
    if(inRange)
      answer1++;
  }

  // Part 2:
  FORIT(vector<PLL>, ranges1) {
    answer2 += -it->first + it->second + 1;
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
