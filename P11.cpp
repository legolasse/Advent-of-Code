typedef vector<string> VS;

int main() {
  string s;
  map<string,LL> counts, countsD, countsF, countsB; // B for "both"
  map<string, VS> M;

  while(getline(cin, s)) {
    s[3] = ' ';
    stringstream ss; ss << s;
    string from, to; ss >> from;
    counts[from] = countsD[from] = countsF[from] = countsB[from] = 0;
    while(ss >> to) {
      M[from].push_back(to);
      counts[to] = countsD[to] = countsF[to] = countsB[to] = 0;
    }
  }

  // Part 1:
  counts["you"] = 1;
  set<string> S1, S2;
  S1.insert("you");
  while(!S1.empty()) {
    FORIT(set<string>, S1) {
      FORIT2(VS, M[*it]) {
	counts[*it2] += counts[*it];
	S2.insert(*it2);
      }
    }
    swap(S1,S2);
    S2.clear();
  }
  cout << "Answer1: " << counts["out"] << endl;

  // Part 2:
  counts.clear();
  counts["svr"] = 1;
  S1.insert("svr");
  while(!S1.empty()) {
    FORIT(set<string>, S1) {
      FORIT2(VS, M[*it]) {
	if(*it2 == "dac") {
	  countsB[*it2] += countsB[*it] + countsF[*it]; // Both if already both or F
	  countsD[*it2] += counts[*it] + countsD[*it]; // D if already D or none
	  counts[*it2] = countsF[*it2] = 0;
	}
	else if(*it2 == "fft") {
	  countsB[*it2] += countsB[*it] + countsD[*it]; // Both if already both or D
	  countsF[*it2] += counts[*it] + countsF[*it]; // F if already F or none
	  counts[*it2] = countsD[*it2] = 0;
	}
	else {
	  counts[*it2] += counts[*it];
	  countsD[*it2] += countsD[*it];
	  countsF[*it2] += countsF[*it];
	  countsB[*it2] += countsB[*it];	
	}
	S2.insert(*it2);
      }
      if(*it != "out")
	counts[*it] = countsD[*it] = countsF[*it] = countsB[*it] = 0;
    }
    swap(S1,S2);
    S2.clear();
  }  

  cout << "Answer2: " << countsB["out"] << endl;
}
