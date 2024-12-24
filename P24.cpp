typedef map<string,int> M;

struct Gate {
  string l, r, o;
  string type;
};

map<string,int> wireValues; // -1, if not set
typedef map<string,Gate> GateMap;
GateMap gates;
vector<string> answer2;

int getWireValue(string wire) {
  if(wireValues.find(wire) != wireValues.end()) {
    return wireValues[wire];
  }
  return -1;
}

void pri(const string &gate) {
  if(gates.find(gate) == gates.end()) {
    cout << gate;
    return;
  }
  const Gate &g = gates[gate];
  cout << "(";
  pri(g.l);
  cout << " " << g.type << " ";
  pri(g.r);
  cout << ")";
}

int decode(const string &s) {
  if(s[0] == 'x' || s[0] == 'y' || s[0] == 'z') {
    return 10*(s[1]-'0') + (s[2]-'0');
  }
  return -1; // Not an x or y or z!
}

bool isTopXor(const string &gate, int val) {
  const Gate &g = gates[gate];
  if(g.type != "XOR") {
    return false;
  }
  return decode(g.l) == val && decode(g.r) == val;  
}

Gate findXorGate(int val) {
  FORIT(GateMap, gates) {
    const Gate &g = it->second;

    if(g.type != "XOR") {
      continue;
    }

    if(decode(g.l) == val && decode(g.r) == val) {
      return it->second;
    }
  }
  die(); return Gate();
}

void check(const string &gate, int val) {
  if(val <= 1)
    return; // Manually checked z00 and z11

  // One side should be XOR of input vals
  // Other side should be carry:
  const Gate &g = gates[gate];
  if(g.type != "XOR") {
    // Find XOR gate for left:
    Gate child = findXorGate(val);
    // Find XOR gate with child as l or r:

    FORIT(GateMap, gates) {
      const Gate &g2 = it->second;
      if(g2.type != "XOR")
	continue;
      if(g2.l == child.o || g2.r == child.o) {
	answer2.push_back(gate);
	answer2.push_back(g2.o);
	break;
      }
    }
    return;
  }
  else if(isTopXor(g.l, val)) {
    return;
  }
  else if(isTopXor(g.r, val)) {
    return;
  }
  else {
    Gate xorChild = findXorGate(val);
    Gate l = gates[g.l];
    Gate r = gates[g.r];
    // Either l or r should be replaced by child!
    // They should be XOR and OR gates, so any and is false:
    if(l.type == "AND") {
      answer2.push_back(l.o);
      answer2.push_back(xorChild.o);
    }
    else if(r.type == "AND") {
      answer2.push_back(r.o);
      answer2.push_back(xorChild.o);
    }
    else {
      return; // TODO!
    }
  }
}

int main() {
  // Read initial wires:
  string line;
  while(getline(cin, line)) {
    if(line == "")
      break;
    FORUI(line.size()) {
      if(line[i] == ':')
	line[i] = ' ';
    }
    stringstream ss; ss << line;
    string wire; ss >> wire;
    int initialValue; ss >> initialValue;
    wireValues[wire] = initialValue;
  }
  // Read gates:
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    Gate g;
    string ignore; ss >> g.l >> g.type >> g.r >> ignore >> g.o;
    gates[g.o] = g;
  }
  
  // Part 1:
  bool improved = true;
  while(improved) {
    improved = false;
    FORIT(GateMap, gates) {
      const Gate &g = it->second;
      if(getWireValue(g.o) != -1)
	continue;
      if(getWireValue(g.l) == -1)
	continue;
      if(getWireValue(g.r) == -1)
	continue;
      // Gate ready:
      if(g.type == "AND") {
	wireValues[g.o] = wireValues[g.l] & wireValues[g.r];
      }
      else if(g.type == "OR") {
	wireValues[g.o] = wireValues[g.l] | wireValues[g.r];
      }
      else { // if(g.type == "XOR") {
	wireValues[g.o] = wireValues[g.l] ^ wireValues[g.r];
      }
      improved = true;
    }
  }

  LL answer1 = 0;
  for(auto it = wireValues.rbegin(); it != wireValues.rend(); it++) {
    if(it->first[0] == 'z') {
      int bit = it->second;
      //cout << it->first << ": " << bit << endl;
      answer1 = (answer1 << 1) + bit;
    }
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  // Output all for analysis:
  FORIT(GateMap, gates) {
    if(it->first[0] == 'z') {
      //cout << it->first << " = ";
      //pri(it->first);
      //cout << endl;
    }
  }
  //cout << endl;

  /*
     Top gate missing child that is Top XOR! z15 FAILURE: z15
      z15 = (((y14 AND x14) OR ...
      tpr XOR dwp -> z15
       wkm OR pwq -> tpr
       x15 AND y15 -> dwp
     Find x15 and y15:
      y15 XOR x15 -> kfm      
     Find usages of kfm:
      kfm OR knt -> phm
     So dwp <-> kfm
  */
  FORIT(GateMap, gates) {
    if(it->first[0] == 'z') {
      int gate = 10*(it->first[1]-'0') + (it->first[2]-'0');
      if(gate != 45) { // Skip, as z45 is only built using carry
	check(it->first, gate);
      }
    }
  }
  sort(answer2.begin(), answer2.end());
  cout << "Answer 2: ";
  FORUI(answer2.size()) {
    if(i != 0)
      cout << ",";
    cout << answer2[i];
  }
  cout << endl;
}
