set<int> B[100];
int incoming[100];

int main() {
  int answer1 = 0, answer2 = 0, a, b;

  string line;
  while(true) {
    getline(cin, line);
    if(line == "")
      break;
    // Rule aa|bb line:
    line[2] = ' ';
    stringstream ss;
    ss << line;
    ss >> a >> b;
    cout << a << " before " << b << endl;
    B[b].insert(a);    
  }
  // Parse aa,bb,cc,... lines:
  while(getline(cin, line)) {
    FORUI(line.size()) {
      if(line[i] == ',')
	line[i] = ' ';
    }
    stringstream ss; ss << line;
    vector<int> v;
    while(ss >> a) {
      cout << a << " ";
      v.push_back(a);
    }
    cout << endl;

    bool ok = true;
    FORI((int)v.size()) {
      a = v[i];
      for(int j = i+1; j < (int)v.size(); j++) {
	b = v[j];
	if(B[a].find(b) != B[a].end()) {
	  //cout << "Rule broken: " << a << " before " << b << endl;
	  ok = false;
	  break;
	}	
      }
      if(!ok)
	break;
    }
    if(ok) {
      a = v[v.size()/2];
      answer1 += a;
    }
    else {
      // Extend partial order to total order:
      vector<int> w;
      FORI(100) {incoming[i] = 0;}

      FORI((int)v.size()) {
	a = v[i];
	FORJ((int)v.size()) {
	  if(i == j)
	    continue;	  
	  b = v[j];
	  
	  if(B[a].find(b) != B[a].end()) {
	    incoming[a]++;
	  }
	}
      }

      int noIn = -1;
      FORUI(v.size()) {
	a = v[i];
	if(incoming[a] == 0) {
	  noIn = a;
	}
      }

      cout << "Reordered: ";
      while(noIn != -1) {
	w.push_back(noIn);
	cout << noIn << " ";
	int newNoIn = -1;
	FORI(v.size()) {
	  a = v[i];
	  if(a == noIn)
	    continue;
	  if(B[a].find(noIn) != B[a].end()) {
	    --incoming[a];
	    if(incoming[a] == 0) {
	      newNoIn = a;
	    }
	  }
	}
	noIn = newNoIn;
      }
      cout << endl;

      answer2 += w[w.size()/2];
    }
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
