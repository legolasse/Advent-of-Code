// Remove : from input
typedef set<string> Set;
typedef map<string,Set> Map;

Map MAP;
Set SET2, SET1;

void insert(string a, string b) {
  if(MAP.find(a) == MAP.end()) {
    MAP.insert(pair<string,Set>(a, Set()));
  }
  MAP[a].insert(b);
  SET2.insert(a);
  SET2.insert(b);
}

set<PS> used;
Set seen;

bool findPathToSET1(string a, int len) {
  if(SET1.find(a) != SET1.end()) {
    return true;
  }
  if(seen.find(a) != seen.end())
    return false; // Was already here
  if(len > 6)
    return false;
  seen.insert(a);
  // Walk neighbours of a:
  Set n = MAP[a];
  FORIT(Set, n) {
    string b = *it;
    if(used.find(PS(a,b)) != used.end())
      continue; // Already walked
    used.insert(PS(a,b));
    used.insert(PS(b,a));
    if(findPathToSET1(b, len+1)) {
      return true;
    }
    used.erase(PS(a,b));
    used.erase(PS(b,a));
  }
  seen.erase(a);
  return false;
}

bool shouldInclude(string a) {
  // Quick check: Must have at least 1 direct connection:
  Set n = MAP[a];
  bool direct = false;
  FORIT(Set, n) {
    string b = *it;
    if(SET1.find(b) != SET1.end()) {
      direct = true;
      break;
    }
  }
  if(!direct) {
    return false;
  }
  
  int connections = 0;
  while(connections <= 3 && findPathToSET1(a, 0)) {
    connections++;
    seen.clear();
  }
  seen.clear();
  used.clear();
  return connections > 3;
}

int main() {
  string line, a, b;
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    ss >> a;
    while(ss >> b) {
      insert(a, b);
      insert(b, a);
    }
  }

  SET1.insert(*SET2.begin()); // Random
  SET2.erase(*SET1.begin());
  bool improved = true;
  while(improved) {
    improved = false;
    // Find a strongly-connected node to include in SET1:
    FORIT(Set, SET2) {
      a = *it;
      if(SET1.find(a) != SET1.end())
	continue; // Already in SET1
      // Find number of paths to a:
      if(shouldInclude(a)) {
	SET1.insert(a);
	SET2.erase(a);
	improved = true;
	break;
      }
    }
  }
  
  cout << "Answer: " << (SET1.size() * SET2.size()) << endl;
}
