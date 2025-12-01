#include <ctime>

typedef set<PC> spc;
typedef map<PC,spc> m;
m M;

void AND(spc &a, spc &b, spc &ret) {
  FORIT(spc, a) {
    PC p = *it;
    if(b.find(p) != b.end()) {
      ret.insert(p);
    }
  }
}

/*
https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm

algorithm BronKerbosch2(R, P, X) is
    if P and X are both empty:
        report R as a maximal clique
    choose a pivot vertex u in P ⋃ X
    for each vertex v in P \ N(u):
        BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
 */

spc answer2;
void BronKerbosch2(spc R, spc P, spc X) {
  if(P.empty() && X.empty()) {
    // report R as a maximal clique
    if(R.size() > answer2.size()) {
      answer2 = R;
    }
    return;
  }
  // choose a (random) pivot vertex u in P ⋃ X:
  spc &U = P.empty() ? X : (X.empty() ? P : ((rand() % 2 == 0) ? P : X));
  spc::iterator it3 = begin(U);
  int pos = rand() % U.size();
  advance(it3, pos);
  PC u = *it3;

  spc P2 = P;
  FORIT(spc, P2) {
    PC v = *it;
    if(M[u].find(v) != M[u].end()) {
      continue; //for each vertex v in P \ N(u):
    }

    spc Ruv = R; Ruv.insert(v);
    spc PnN; AND(P, M[v], PnN);
    spc XnN; AND(X, M[v], XnN);

    BronKerbosch2(Ruv, PnN, XnN);

    P.erase(v);
    X.insert(v);
  }
}

int main() {
  string line;
  while(getline(cin, line)) {
    PC a(line[0],line[1]), b(line[3],line[4]);
    if(M.find(a) == M.end())
      M[a] = spc();
    if(M.find(b) == M.end())
      M[b] = spc();
    M[a].insert(b);
    M[b].insert(a);
  }
  
  // Part 1:
  int answer1 = 0;
  FORIT(m, M) {
    PC a = it->first;

    FORIT2(spc, it->second) {
      PC b = *it2;
      FORIT3(spc, it->second) {
	PC c = *it3;
	if(b == c || c == a) {
	  continue;
	}
	
	if(M[c].find(b) != M[c].end()) {
	  if(a.XX == 't' || b.XX == 't' || c.XX == 't') {
	    answer1++;
	  }
	}
      }
    }
  }
  cout << "Answer 1: " << answer1/6 << endl;

  // Part 2:
  srand(time(nullptr));
  spc R, P, X;
  FORIT(m, M) {
    P.insert(it->first);
  }
  BronKerbosch2(R, P, X);

  // Sort:
  vector<PC> v;
  FORIT(spc, answer2) {
    v.push_back(*it);
  }
  sort(v.begin(), v.end());
  
  cout << "Answer 2: ";
  bool first = true;
  FORIT(vector<PC>, v) {
    if(!first)
      cout << ",";
    first = false;
    cout << it->XX << it->YY;
  }
  cout << endl;
}
