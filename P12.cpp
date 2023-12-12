// Remove , from input
LL answer = 0;
string line, s;
int G[100], sizeG;
map<PI, LL> m1, m2; // without and with forced #

void dynamicProgrammingStore(PI pi, LL x, map<PI, LL> &m) {
  m[pi] = x;
}

LL go(int sIdx, int gIdx, map<PI, LL> &m) {
  PI pi(sIdx,gIdx);  
  if(m.find(pi) != m.end()) {
    return m[pi];
  }  

  if(sIdx >= (int)s.size()) {
    LL ret = 0;
    if(gIdx >= sizeG) {
      ret = 1;
    }
    dynamicProgrammingStore(pi, ret, m);
    return ret;
  }
  if(s[sIdx] == '.') {
    LL ret = go(sIdx+1, gIdx, m1);
    dynamicProgrammingStore(pi, ret, m);
    return ret;
  }
  if(s[sIdx] == '#') { // Has to fit G:
    if(gIdx >= sizeG) {
      dynamicProgrammingStore(pi, 0, m);
      return 0; // No matching group.
    }
    int sizeHash = G[gIdx];
    if(sIdx + sizeHash > (int)s.size()) {
      dynamicProgrammingStore(pi, 0, m);
      return 0; // Not big enough for group
    }
    // Check fitting hash:
    FORI(sizeHash) {
      char c = s[sIdx+i];
      if(c == '.') {
	dynamicProgrammingStore(pi, 0, m);
	return 0;
      }
    }
    if(s[sIdx+sizeHash] == '#') {
      dynamicProgrammingStore(pi, 0, m);
      return 0; // Not a group of this size!
    }
    LL ret = go(sIdx+sizeHash+1, gIdx+1, m1);
    dynamicProgrammingStore(pi, ret, m);
    return ret;
  }
  // s[sIdx] == '?': Try as . and #:
  s[sIdx] = '.';
  LL ret = go(sIdx+1, gIdx, m1); // This tries as .

  s[sIdx] = '#';
  ret += go(sIdx, gIdx, m2); // This tries as #
  s[sIdx] = '?';
  dynamicProgrammingStore(pi, ret, m);
  return ret;
}

int main() {
  while(getline(cin, line)) {
    stringstream ss;
    ss << line; ss >> s;
    cout << s << "    ";
    sizeG = 0;
    while(ss >> G[sizeG]) {
      cout << "  " << G[sizeG];
      sizeG++;
    }
    cout << endl;
    
    // Part 2:
    string g = s;
    FORI(4) {
      s = s + "?" + g;
      FORJ(sizeG) {
	G[j+(i+1)*sizeG] = G[j];
      }
    }
    sizeG *= 5;
    cout << " ->" << endl;
    cout << s << "    ";
    FORI(sizeG)
      cout << "  " << G[i];
    cout << endl;
    //*/
    // End part 2


    m1.clear();
    m2.clear();
    LL toAdd = go(0, 0, m1);
    answer += toAdd;
    cout << " " << toAdd << " added" << endl;
  }

  cout << "Answer: " << answer << endl;
}
