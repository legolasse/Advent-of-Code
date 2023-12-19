// Sanitize input: Replace all {;:,} with spaces and space around <>
struct Rule {
  char op, variable; // >, <, .
  int val;
  string nextWorkflow;
};

LL answer1 = 0;
string line, XMAS="xmas";
char variable;
int val, xmas[256];
map<string,vector<Rule> > M;

LL eval(string workflowName, vector<PI> const *intervals) {
  if(workflowName == "R") {
    return 0; // Reject!
  }
  if(workflowName == "A") {
    // Multiply intervals:
    LL ret = 1;
    FORI(4) {
      LL sum = 0;
      FORIT2(vector<PI>, intervals[i]) { // Sum intervals:
	sum += it2->second - it2->first + 1;
      }
      ret *= sum;
    }
    return ret;
  }
  LL ret = 0;

  if(M.find(workflowName) == M.end())
    die();
  vector<Rule> &v = M[workflowName];
  FORIT(vector<Rule>, v) {
    int letterI = xmas[(int)it->variable];
    //cout << "  Rule: " << it->variable << " (" << letterI << ") " << it->op << " " << it->val << " " << it->nextWorkflow << endl;

    if(it->op == '.') {
      ret += eval(it->nextWorkflow, intervals);
      break;
    }

    vector<PI> *intervals2, high, low;
    intervals2 = new vector<PI>[4];

    FORI(4) {
      if(i != letterI) {
	intervals2[i] = intervals[i];
      }
      else {
	intervals2[i].clear();
      }
    }

    if(it->op == '>') { // Recurse with high intervals:
      FORIT2(vector<PI>, intervals[letterI]) {
	if(it2->second > it->val)
	  high.push_back(PI(max(it2->first, it->val+1), it2->second));
	if(it2->first <= it->val)
	  low.push_back(PI(it2->first, min(it2->second, it->val)));
      }
      intervals2[letterI] = high;
      if(!high.empty())
	ret += eval(it->nextWorkflow, intervals2);
      if(low.empty())
	break;
      intervals2[letterI] = low;
      intervals = intervals2;
    }
    else { // op == <
      FORIT2(vector<PI>, intervals[letterI]) {
	if(it2->second >= it->val)
	  high.push_back(PI(max(it2->first, it->val), it2->second));
	if(it2->first < it->val)
	  low.push_back(PI(it2->first, min(it2->second, it->val-1)));
      }
      intervals2[letterI] = low;
      if(!low.empty()) {
	ret += eval(it->nextWorkflow, intervals2);
      }
      if(high.empty()) {
	break;
      }
      intervals2[letterI] = high;
      intervals = intervals2;
    }
  } // FORIT

  return ret;
}

int main() {
  xmas[(int)'x'] = 0;
  xmas[(int)'m'] = 1;
  xmas[(int)'a'] = 2;
  xmas[(int)'s'] = 3;
  
  // Read workflows:
  while(getline(cin, line)) {
    if(line == "")
      break;
    stringstream ss; ss << line;
    string workflow;
    ss >> workflow;
    M[workflow] = vector<Rule>();
    Rule r;
    string first;
    while(ss >> first) {
      if(ss >> r.op >> r.val >> r.nextWorkflow) {
	r.variable = first[0];
	M[workflow].push_back(r);
      }
      else {
	r.op = '.';
	r.nextWorkflow = first;
	r.val = -1;
	M[workflow].push_back(r);
      }
    }
  }

  // Read parts:
  while(getline(cin, line)) {
    vector<PI> *intervals = new vector<PI>[4];
    int sum = 0;
    stringstream ss; ss << line;
    cout << "Part";
    while(ss >> variable >> val) {
      intervals[xmas[(int)variable]].push_back(PI(val,val));
      sum += val;
      cout << " " << variable << " = " << val;
    }
    cout << endl;

    if(eval("in", intervals) > 0) {
      answer1 += sum;
    }
  }
  cout << "Answer1: " << answer1 << endl;

  // Part 2:
  vector<PI> *intervals = new vector<PI>[4];
  FORI(4) {
    intervals[i].push_back(PI(1,4000));
  }

  cout << "Answer2: " << eval("in", intervals) << endl;
}
