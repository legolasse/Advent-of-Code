LL answer1 = 0, answer2 = 0;
LL instances[215], points[215];
int games = 0;
string line, ignore, gameID, s;

int main() {
  FORI(215) {
    instances[i] = 1;
  }
  
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    ss >> ignore >> gameID;
    //cout << "Game " << gameID << " instances: " << instances[games] << endl;
    answer2 += instances[games];
    set<string> own, all;
    while(ss >> s) {      
      if(s == "|") {
	break;
      }
      own.insert(s);
    }
    points[games] = 0;
    while(ss >> s) {      
      if(own.find(s) != own.end()) {
	points[games]++;
      }
    }

    // Part 1:
    if(points[games]  > 0) {
      LL toAdd = 1;
      for(LL i = 1; i < points[games]; i++) {
	toAdd *= 2;
      }
      answer1 += toAdd;
    }

    // Part 2:
    for(int i = 0; i < points[games]; i++) {
      instances[games+1+i] += instances[games];
    }
    
    games++;    
  } // while getline
  cout << "Answer 1" << endl << answer1 << endl;
  cout << "Answer 2" << endl << answer2 << endl;
} // main
