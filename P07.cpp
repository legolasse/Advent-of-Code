int main() {
  LL answer1 = 0, answer2 = 0;
  string s;
  vector<string> v;
  int w, h = 0;
  set<int> T1, T2;
  LL M1[200], M2[200];
  FORX(200)
    M1[x] = M2[x] = 0;

  while(cin >> s) {
    w = (int)s.size();
    v.push_back(s);
    if(h == 0) {
      // First time: Find S:
      FORX(w) {
	if(s[x] == 'S') {
	  T1.insert(x);
	  M1[x] = 1;
	}
      }
    }
    h++;
  }

  // Part 1:
  for(int y = 1; y < h; y++) {
    FORIT(set<int>, T1) {
      if(v[y][*it] == '^') {
	T2.insert((*it)-1);
	T2.insert((*it)+1);
	answer1++;
      }
      else {
	T2.insert(*it);
      }
    }
    swap(T1, T2);
    T2.clear();
  }

  // Part 2:
  for(int y = 1; y < h; y++) {
    FORX(w) {
      if(v[y][x] == '^') {
	M2[x-1] += M1[x];
	M2[x+1] += M1[x];
      }
      else
	M2[x] += M1[x];
    }
    swap(M1, M2);
    FORX(w)
      M2[x] = 0;
  }

  FORX(w)
    answer2 += M1[x];

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
