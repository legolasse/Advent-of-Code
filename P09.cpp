LL answer1 = 0, answer2 = 0, x;
string line;
vector<LL> s1, s2, f;

bool done() {
  FORIT(vector<LL>, s1) {
    if(*it != 0)
      return false;
  }
  return true;
}

int main() {
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    s1.clear(); f.clear();
    LL last = 0;

    while(ss >> x) {
      s1.push_back(x);      
    }

    while(!done()) {
      last += *(s1.rbegin());
      f.push_back(*(s1.begin()));
      s2.clear();
      for(int i = 1; i < (int)s1.size(); i++) {
	s2.push_back(s1[i]-s1[i-1]);
      }
      swap(s1, s2);
    } // while !done()

    // Find next:
    LL F1 = 0;
    for(int i = (int)f.size()-1; i >= 0; i--) {
      LL y = f[i]; // y - F0 = F1 =>  
      F1 = y - F1;
    }
    answer2 += F1;
    answer1 += last;
    
  } // while getline
  cout << "Answer 1" << endl << answer1 << endl;
  cout << "Answer 2" << endl << answer2 << endl;
} // main
