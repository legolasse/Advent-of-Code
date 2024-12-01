// Sanitize input: Remove all but the numbers and instructions
LL answer1 = 0, answer2 = 1;
string line, ignore, instructions, a, b, c;
map<string,int> m; map<int,string> rmap;
int _left[1000], _right[1000], ia, ib, ic, size, aPos[100], bPos[100], ghosts = 0, firstZ[10], secondZ[10];
bool isZ[1000];

bool done() {
  FORI(ghosts) {
    int pos = aPos[i];
    if(!isZ[pos]) {
      return false;
    }
  }
  return true;
}

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


int main() {
  getline(cin, instructions);
  getline(cin, ignore);
  FORI(1000)
    isZ[i] = false;
    
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    ss >> a >> b >> c;

    if(m.find(a) == m.end()) {
      m.insert(PSI(a, (int)m.size()));      
    }
    ia = m[a];
    rmap[ia] = a;
    if(a[2] == 'A') {
      aPos[ghosts++] = ia;
    }
    else if(a[2] == 'Z') {
      isZ[ia] = true;
    }
    
    if(m.find(b) == m.end())
      m.insert(PSI(b, (int)m.size()));
    ib = m[b];
    rmap[ib] = b;
    if(b[2] == 'A') {
      aPos[ghosts++] = ib;
    }
    else if(b[2] == 'Z') {
      isZ[ib] = true;
    }

    if(m.find(c) == m.end())
      m.insert(PSI(c, (int)m.size()));
    ic = m[c];
    rmap[ic] = c;
    if(c[2] == 'A') {
      aPos[ghosts++] = ic;
    }
    else if(c[2] == 'Z') {
      isZ[ic] = true;
    }

    _left[ia] = ib;
    _right[ia] = ic;
  } // while getline

  // Part 1:
  int pos = m["AAA"];
  answer1 = 0;
  for(int i = 0; pos != m["ZZZ"]; i++) {
    char step = instructions[i % instructions.size()];
    if(step == 'L') {
      pos = _left[pos];
    }
    else {
      pos = _right[pos];
    }
    answer1++;
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  FORI(10){firstZ[i] = -1;}
  FORI(10){secondZ[i] = -1;}

  for(int i = 0; !done(); i++) {
    char step = instructions[i % instructions.size()];
    FORJ(ghosts) {
      int p = aPos[j];
      bPos[j] = step == 'L' ? _left[p] : _right[p];
      if(isZ[bPos[j]]) {
	if(firstZ[j] == -1) {
	  firstZ[j] = i;
	  cout << "GHOST " << j << " reached FIRST Z position in iteration " << i << endl;
	  answer2 = lcm(answer2, i+1);
	  cout << "Answer 2 now: " << answer2 << endl;
	  
	}
	else if(secondZ[j] == -1) {
	  secondZ[j] = i;
	  cout << "GHOST " << j << " reached SECOND Z position in iteration " << i << ", " << (i - firstZ[j]) << " after first" << endl;
	}
      }
    }
    
    swap(aPos, bPos);
  }
  
} // main
