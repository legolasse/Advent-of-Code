struct S {
  int a[5];
};

vector<S> L, K;

int main() {
  vector<string> lines;
  string line;
  while(true) {
    bool hasLine = getline(cin, line);
    if(!hasLine || line == "") {
      bool isKey = lines[0] == ".....";
      S s;
      FORI(5) {
	int cnt = 0;
	FORJ(7) {
	  if(lines[j][i] == '#')
	    cnt++;
	}
	s.a[i] = cnt-1;
      }
      if(isKey) {
	K.push_back(s);
	cout << "Key";
      }
      else {
	L.push_back(s);
	cout << "Lock";
      }
      FORI(5)
	cout << " " << s.a[i];
      cout << endl;
      lines.clear();
    }
    else {
      lines.push_back(line);
    }
    if(!hasLine)
      break;    
  }
  
  // Part 1:
  int answer1 = 0;
  FORUI(K.size()) {
    S key = K[i];
    FORUJ(L.size()) {
      S lock = L[j];
      bool fit = true;
      FORK(5) {
	int kk = key.a[k];
	int ll = lock.a[k];
	if(kk + ll > 5) {
	  fit = false;
	  break;
	}
      }
      if(fit) {
	answer1++;
      }
    }
  }

  cout << "Answer 1: " << answer1 << endl;
}
