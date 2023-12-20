// Remove , and -> from input, and add space after & and %
/*
Part 2 analysis:

rx only appears in:
& ls rx

ls appears in:
& tx ls
& dd ls
& nz ls
& ph ls
Checking those:

 */
LL totalLow = 0, totalHigh = 0, buttons = 0;
LL answer2 = 1;

LL gcd(LL a, LL b) {
  LL c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

LL lcm(LL a, LL b) {
  LL g = gcd(a,b);
  return a*b/g;
}

typedef map<string,bool> SourceMap;
struct Module {
  bool on, isFlipFlop;
  vector<string> targets;
  SourceMap sources;
};

typedef map<string,Module> Map;
Map M;
set<string> broadcasts;

queue<pair<PS, bool> > Q;

void send(string source, string target, bool high) {
  if(target == "rx" && !high) {
    cout << "Answer2: " << buttons << endl;
    die();
  }
  if(target == "tx" || target == "dd" || target == "nz" || target == "ph") {
    if(!high) {
      cout << "Target: " << target << " at button " << buttons << endl;
      answer2 = lcm(answer2, buttons);
      cout << "Current LCM: " << answer2 << endl;
    }
  }
  Q.push(pair<PS, bool>(PS(source,target), high));
}

void handle(string source, string target, bool high) {
  if(high)
    totalHigh++;
  else
    totalLow++;
  //cout << source << " -" << (high ? "high" : "low") << "-> " << target << endl;

  if(M.find(target) == M.end()) {
    cout << target << " does not exist" << endl;
    return; // Does not exist.
  }
  Module &m = M[target];
  if(m.isFlipFlop) {
    if(high) {
      return; // ignore
    }
    m.on = !m.on;
  }
  else { // m is conjunction:
    m.sources[source] = high;
    bool allHigh = true;
    FORIT(SourceMap, m.sources) {
      if(!it->second) {
	allHigh = false;
      }
    }
    m.on = !allHigh;
  }

  FORIT(vector<string>, m.targets) {
    send(target, *it, m.on);
  }
}

int main() {
  string line, s, x, c;
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    ss >> c;

    if(c == "broadcaster") {
      while(ss >> s) {
        broadcasts.insert(s);
      }
      continue;
    }
			   
    ss >> s; // Module
    Module m;
    m.isFlipFlop = c[0] == '%';
    m.on = false;
    while(ss >> x) {
      m.targets.push_back(x);
    }
    M[s] = m;
  }
  // Set up sources:
  FORIT(Map, M) {
    const Module &m = it->second;
    FORIT2(vector<string>, m.targets) {
      M[*it2].sources[it->first] = false;
    }
  }

  // Part 1:
  FORI(5000) { // 1000 for part 1
    buttons++;
    totalLow++; // Button
    FORIT(set<string>, broadcasts) {
      send("broadcaster", *it, false);
    }
    while(!Q.empty()) {
      pair<PS, bool> pulse = Q.front();
      Q.pop();
      handle(pulse.first.first, pulse.first.second, pulse.second);
    }
  }
  cout << "Total low " << totalLow << ", high " << totalHigh << endl;
  cout << "Answer1: " << totalLow * totalHigh << endl;
}
