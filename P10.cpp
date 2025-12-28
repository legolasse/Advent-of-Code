/* For part 2:
   x1*(a+b+c)
   x2*(d+e)
   ...

   Translates into:
   a*x1 + ... + a*xn < 124
   b*...
   Minimize sum x1+x2+... using Python is easy.

   But let's try to solve it without using an external solver.

   Example 1:
   [.###] (2) (0,1) (1,2) (1,2,3) {9,173,175,13}
   Immediately discard subsets and Part1-section:
   (0,1) (1,2,3) {9,173,175,13}
   So:
   Minimize A+B from
   A >= 9
   A+B >= 173
   B >= 175
   B >= 13
   Notice largest can be considered as equality!
   A >= 9
   A+B >= 173
   B = 175
   B >= 13
   Which removes all, but:
   A >= 9
   B = 175
   
   Example 2 (Part 1 and subsets removed):
   (0,1,2,3,4) (0,1,2,4,5) {10,11,11,5,10,5}   
   A+B >= 10
   A+B >= 11
   A+B >= 11
   A >= 5
   A+B >= 10
   B >= 5
   Set largest as equality and remove redundancies:
   A+B = 11
   A >= 5
   B >= 5

   Example 3:
   (4,6) (1,5) (3,4) (0,5) (0,1,2,4) (1,2,3,6) {34,49,56,171,181,28,52}
   A     B     C     D     E         F          0  1  2  3   4   5  6
   D+E   >= 34
   B+E+F >= 49
   E+F   >= 56
   C+F   >= 171
   A+C+E =  181
   B+D   >= 28
   A+F   >= 53
   Notice B+E+F overruled by E+F:
   D+E   >= 34
   E+F   >= 56
   C+F   >= 171
   A+C+E =  181
   B+D   >= 28
   A+F   >= 53
   B only in one rule, so set B=0:
   B = 0
   D+E   >= 34
   E+F   >= 56
   C+F   >= 171
   A+C+E =  181
   D     >= 28
   A+F   >= 53
   D only in self and D+E rule, so set to 28:
   B = 0
   D = 28
   E     >= 6
   E+F   >= 56
   C+F   >= 171
   A+C+E =  181
   A+F   >= 53
   Run A, C, F (E computed) => n^3 OK!

   Example 4:
   (A+C+  F    ) >= 39
   (A+  E+F    ) >= 23
   (A+    F+  I) >= 31
   (A+  E+  G+I) >= 81
   (  C+  F+G  ) >= 38
   (    E+F+  I) >= 28
   (A+  E+F+G+I) = 100
   (A+C+E+    I) >= 61
   
*/

typedef unsigned long Encoding;
typedef pair<Encoding,PI> PEI;

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

void print(vector<PEI> &q) {
  FORUI(q.size()) {
    Encoding e = q[i].first;
    PI interval = q[i].second;
    cout << " " << decode(e) << " ";
    if(interval.second == -1) {
      cout << ">= " << interval.first;
    }
    else if(interval.first==interval.second)
      cout << "= " << interval.first;
    else
      cout << "= [" << interval.first << ";" << interval.second << "]";
    cout << endl;
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

void removeRedundantInequalities(vector<PEI> &q) {
  vector<PEI> ret;
  FORUI(q.size()) {
    bool keepI = true;
    Encoding ei = q[i].first;
    PI ii = q[i].second;
    FORUJ(q.size()) {
      if(i == j)
	continue;
      Encoding ej = q[j].first;
      PI ij = q[j].second;
      if(ei == ej) {
	// Same encoding:
	if(ij == ii) {
	  // And same interval
	  if(i < j) {
	    keepI = false;
	    break; // Keep only one
	  }
	}
	else {
	  if(ii.first < ij.first) {
	    keepI = false;
	    break; // Keep only if more restricting
	  }
	}
      }
      else if((ei | ej) == ei) {
	// J within I: Remove I if J is higher count:
	if(ij.first > ii.first) {
	  keepI = false;
	  break;
	}
      }
    }
    if(keepI)
      ret.push_back(q[i]);
  }

  q = ret;
}

void remove(vector<PEI> &q, int i, int valueI) {
  Encoding mask = 1 << i;
  vector<PEI> q2;
  FORUJ(q.size()) {
    Encoding e = q[j].first;
    if((e|mask)!=e) {
      q2.push_back(q[j]);
      continue;
    }
    PI interval = q[j].second;
    if(e == mask) {
      if(interval.first == valueI)
	q2.push_back(PEI(e,PI(interval.first, interval.first)));
      continue;
    }
    if(interval.first <= valueI)
      continue; // Smaller than valueI, so no longer usable.
    e-=mask;
    if(interval.second == -1)
      q2.push_back(PEI(e,PI(interval.first-valueI, -1)));
    else
      q2.push_back(PEI(e,PI(interval.first-valueI, interval.second-valueI)));
  }
  q = q2;
}

bool removeSingleUseVariables(vector<PEI> &q) {
  bool anyRemoved = false;
  FORI(16) { // Assume at most 16 variables
    Encoding mask = 1 << i;
    int usages = 0;
    int setValue = 0;
    FORUJ(q.size()) {
      Encoding e = q[j].first;
      if(e == mask) {
	setValue = MAX(setValue,q[j].second.first);
      }
      else if((e | mask) == e) {
	// Letter in e: Count
	usages++;
      }
    }
    if(usages == 1) {
      // Remove letter:
      remove(q, i, setValue);
      anyRemoved = true;
    }
  }
  return anyRemoved;
}

bool removeCoveredVariables(vector<PEI> &q) {
  bool anyRemoved = false;
  FORI(16) { // Assume at most 16 variables
    Encoding maskI = 1 << i;
    bool keepI = true;
    FORJ(16) {
      if(i == j)
	continue;
      Encoding maskJ = 1 << j;
      bool JcoversI = false;
      FORUK(q.size()) {
	Encoding e = q[k].first;
	if((e|maskI) != e)
	  continue; // I not in e
	if((e|maskJ) != e) {
	  JcoversI = false; // J not in e
	  break;
	}
	JcoversI = true;
      }
      if(JcoversI) {
	keepI = false;
	break;
      }
    }
    if(!keepI) {
      // Remove I from q:
      remove(q, i, 0);
      anyRemoved = true;
    }
  }
  return anyRemoved;
}

int part2(vector<PEI> &q, bool first, vector<PI> &solution);

int variableSearch(vector<PEI> &q, int from, int to, bool first, vector<PI> &solution) {
  for(int i = from; i <= to; i++) {
    Encoding mask = 1 << i;
    int minI = 0, maxI = 0;
    FORUJ(q.size()) {
      PI interval = q[j].second;
      maxI = MAX(maxI, interval.first);
    }
    bool isPresent = false;
    FORUJ(q.size()) {
      Encoding e = q[j].first;
      PI interval = q[j].second;
      if((e|mask)==e) {
	isPresent = true;
	// I in e:
	if(e==mask)
	  minI = MAX(minI, interval.first); // Single variable I
	if(interval.second != -1)
	  maxI = MIN(maxI, interval.second);
      }
    }
    if(isPresent) {
      int best = 999999, bestVal = minI;
      vector<PEI> prevQ;
      for(int val = minI; val <= maxI; val++) {
	vector<PEI> q2;
	// Set value for I:
	FORUJ(q.size()) {
	  Encoding e = q[j].first;
	  if((e&mask)==mask) {
	    if(e != mask) {
	      PI interval = q[j].second;
	      if(interval.first > val) {
		interval.first-=val;
		if(interval.second != -1)
		  interval.second-=val;
		q2.push_back(PEI(e-mask, interval));
	      }
	    }
	  }
	  else
	    q2.push_back(q[j]); // Variable not in q[j], so keep it.
	}
	int attempt = val + part2(q2, false, solution);
	if(attempt < best) {
	  best = attempt;
	  bestVal = val;
	  prevQ = q2;
	}
	else
	  break; // Break early due to simple linear dependencies
      }
      if(first) {
	solution.push_back(PI(i,bestVal));
	part2(prevQ, true, solution); // Add remaing to solution
      }
      return best;
    }
  }
  return 0; // No variables to set
}

/*
  Perform reductions:
  1) Remove redundant inequalities
  2) Remove letters that are only used once
  3) Remove letters that are alway accompanied by another
 */
int part2(vector<PEI> &q, bool first, vector<PI> &solution) {
  unsigned int sizeBefore = q.size();
  removeRedundantInequalities(q);
  if(first && q.size() != sizeBefore) {
    cout << "After removal of redundancies:" << endl;
    print(q);
  }
  bool anyRemoved1 = removeSingleUseVariables(q);
  if(first && anyRemoved1) {
    cout << "After single use variable removal:" << endl;
    print(q);
  }
  bool anyRemoved2 = removeCoveredVariables(q);
  if(first && anyRemoved2) {
    cout << "After covered variable removal:" << endl;
    print(q);
  }
  
  if(!anyRemoved1 && !anyRemoved2 && sizeBefore == q.size()) {
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
    vector<PEI> q;
    int maxCount = 0;
    FORUI(counts.size()) {
      Encoding e = 0;
      FORUJ(v.size()) {
	if((v[j] & (1<<i)) != 0)
	  e += 1 << j;
      }
      q.push_back(PEI(e, PI(counts[i], -1)));
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
      if(cur[i] < counts[i]) {
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
