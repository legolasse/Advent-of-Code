/* For part 2:
   x1*(a+b+c)
   x2*(d+e)
   ...

   Translates into:
   a*x1 + ... + a*xn = 124
   b*...
   Minimize sum x1+x2+... using Python is easy.

   But let's try to solve it without using an external solver.

   Example 1:
   [.###] (2) (0,1) (1,2) (1,2,3) {9,173,175,13}
   Minimize A+B from:
   B = 9
   B+C=D = 173
   A+C+D = 175
   D = 13
   Remove single var setters!
*/

typedef unsigned long Encoding;
typedef pair<Encoding,int> EQ;

string decode(Encoding e) {
  bool first = true;
  stringstream ss; ss << '(';
  FORI(32) {
    if(((1 << i) & e) != 0) {
      if(!first)
	ss << '+';
      ss << (char)('A'+i);
      first = false;
    }
  }
  ss << ')';
  return ss.str();
}

string decode2(Encoding e) {
  bool first = true;
  stringstream ss; ss << '(';
  FORI(32) {
    if(((1 << i) & e) != 0) {
      if(!first)
	ss << ',';
      ss << i;
      first = false;
    }
  }
  ss << ')';
  return ss.str();
}

void print(vector<EQ> &q) {
  FORUI(q.size()) {
    Encoding e = q[i].first;
    cout << " " << decode(e) << " = " << q[i].second << endl;
  }
  cout << endl;
}

Encoding encode(string &s) {
  s[0] = s[s.size()-1] = ' ';
  FORUI(s.size()) {
    if(s[i] == ',')
      s[i] = ' ';
  }
  stringstream ss; ss << s;
  int idx;
  Encoding ret = 0;
  while(ss >> idx) {
    ret += (1 << idx);
  }
  return ret;
}

bool part1(const Encoding target, const vector<Encoding> &v, const int vIdx, const int rem, const Encoding t) {
  if(t == target)
    return true;
  if(rem == 0 || vIdx >= (int)v.size())
    return false;
  if(part1(target, v, vIdx+1, rem, t)) {
    return true;
  }
  if(part1(target, v, vIdx+1, rem-1, t ^ v[vIdx])) {
    return true;
  }
  return false;
}

// Part 2:

bool removeCovered(vector<EQ> &q, bool &anyRemoved) {
  FORUI(q.size()) {
    Encoding ei = q[i].first;
    FORUJ(q.size()) {
      Encoding ej = q[j].first;
      if(ei == ej)
	continue;
      bool JcoversI = (ej|ei) == ej;
      if(JcoversI) {
	// Remove I from J:
	if(q[j].second < q[i].second)
	  return false;
	q[j].second-=q[i].second;
	q[j].first-=ei;
	anyRemoved = true;
      }
    }
  }
  return true;
}

int part2(vector<EQ> &q, bool first, vector<PI> &solution);

int variableSearch(const vector<EQ> &q, int from, int to, bool first, vector<PI> &solution) {
  for(int i = from; i <= to; i++) {
    Encoding mask = 1 << i;
    int minI = 0, maxI = 999999;
    bool isPresent = false;
    FORUJ(q.size()) {
      Encoding e = q[j].first;
      int val = q[j].second;
      if((e|mask)==e) {
	if(isPresent && e == mask && val != minI)
	  return 999999;
	isPresent = true;
	// I in e:
	if(e==mask)
	  minI = val;
	maxI = MIN(maxI, val);
      }
    }
    if(isPresent) {
      int best = 999999, bestVal = minI;
      vector<EQ> bestQ;
      for(int val = minI; val <= maxI; val++) {
	vector<EQ> q2;
	// Set value for I:
	FORUJ(q.size()) {
	  Encoding e = q[j].first;
	  if((e&mask)==mask) {
	    if(e != mask) {
	      int oldVal = q[j].second;
	      q2.push_back(EQ(e-mask, oldVal-val));
	    }
	  }
	  else
	    q2.push_back(q[j]); // Variable not in q[j], so keep it.
	}
	int attempt = val + part2(q2, false, solution);
	if(attempt < best) {
	  best = attempt;
	  bestVal = val;
	  bestQ = q2;
	}
	//else
	//  break; // Break early due to linear dependencies
      }
      if(first) {
	solution.push_back(PI(i,bestVal));
	part2(bestQ, true, solution); // Add remaing to solution
      }
      return best;
    }
  }
  return 0; // No variables to set
}

/*
  Perform reductions:
  1) Remove letters that are only used once
  2) Remove equations that are alway within others
 */
int part2(vector<EQ> &q, bool first, vector<PI> &solution) {
  bool anyRemoved = false;
  bool ok = removeCovered(q, anyRemoved);
  if(!ok)
    return 999999;
  if(first && anyRemoved) {
    cout << "After covered variable removal:" << endl;
    print(q);
  }
  
  if(!anyRemoved) {
    // Perform variable search!
    int minVariable = 16, maxVariable = 0;
    FORI(16) {
      Encoding mask = 1 << i;
      FORUJ(q.size()) {
	if((q[j].first & mask) == mask) {
	  maxVariable = MAX(maxVariable, i);
	  minVariable = MIN(minVariable, i);
	  break;
	}
      }
    }
    return variableSearch(q, minVariable, maxVariable, first, solution);
  }
  else {
    return part2(q, first, solution);
  }
}

int main() {
  LL answer1 = 0, answer2 = 0;
  string s;
  int problem = 1;

  while(getline(cin, s)) {
    cout << endl << s << endl;
    stringstream ss; ss << s;
    Encoding target = 0;
    ss >> s;
    for(int i = 1; i < (int)s.size()-1; i++) {
      if(s[i] == '#')
	target += 1 << (i-1);
    }

    vector<Encoding> v;
    vector<int> counts;
    while(ss >> s) {
      if(s[0] == '{') {
	s[0] = s[s.size()-1] = ' ';
	FORUI(s.size()) {
	  if(s[i] == ',')
	    s[i] = ' ';
	}
	stringstream ss2; ss2 << s;
	int count;
	while(ss2 >> count)
	  counts.push_back(count);
	break;
      }
      Encoding d = encode(s);
      v.push_back(d); // Max 13 of these
    }
    
    // Part 1:
    for(int presses = 0; presses <= (int)v.size(); presses++) {
      if(part1(target, v, 0, presses, 0)) {
	answer1 += presses;
	break;
      }
    }

    // Part 2:
    // Transform input into inequalities:
    vector<EQ> q;
    int maxCount = 0;
    FORUI(counts.size()) {
      Encoding e = 0;
      FORUJ(v.size()) {
	if((v[j] & (1<<i)) != 0)
	  e += 1 << j;
      }
      q.push_back(EQ(e, counts[i]));
      maxCount = MAX(maxCount, counts[i]);
    }
    cout << "Part 2. Initial problem:" << endl;
    print(q);
    vector<PI> solution;
    int toAdd = part2(q, true, solution);
    cout << " SOLUTION:" << endl;
    FORIT(vector<PI>, solution) {
      cout << "  " << decode2(v[it->first]) << " x " << it->second << endl;
    }
    // Check solution:
    vector<int> cur;
    cout << "Target counts: ";
    FORUI(counts.size()) {
      cout << counts[i] << " ";
      cur.push_back(0);
    }
    cout << endl;
    int xcheck = 0;
    FORIT(vector<PI>, solution) {
      Encoding e = v[it->first];
      int mult = it->second;
      for(int pos = 0; pos < 16; pos++) {
	Encoding mask = 1 << pos;
	if((e&mask)==mask)
	  cur[pos]+=mult;
      }
      xcheck += mult;
    }
    cout << "Result counts: ";
    FORUI(counts.size()) {
      cout << cur[i] << " ";
      if(cur[i] != counts[i]) {
	cerr << "ERROR IN PROBLEM " << problem << " FOR POSITION " << i << ": " << cur[i] << " < " << counts[i] << endl;
	return 1;
      }
    }
    cout << endl << endl;
    if(toAdd != xcheck) {
      cerr << "CROSS XCHECK ERROR IN PROBLEM " << problem << ": " << xcheck << " != " << xcheck << endl;
      return 2;
    }
    answer2 += toAdd;
    cout << "### " << (problem++) << " ### " << toAdd << " ### " << answer2 << endl << endl;
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
