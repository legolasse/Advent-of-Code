bool can(LL answer, LL tmp, vector<LL> &ops, int idx) {
  if(idx == (int)ops.size()) {
    return answer == tmp;
  }
  // Try to add and mult next:
  LL next = ops[idx];
  return can(answer, tmp+next, ops, idx+1) || can(answer, tmp*next, ops, idx+1);
}

LL concat(LL a, LL b) {
  LL ret = a;
  stack<int> s;
  while(b > 0) {
    int digit = b%10;
    s.push(digit);
    b/=10;
  }
  while(!s.empty()) {
    int digit = s.top();
    ret = 10*ret + digit;
    s.pop();
  }
  return ret;
}

bool can2(LL answer, LL tmp, vector<LL> &ops, int idx) {
  if(idx == (int)ops.size()) {
    return answer == tmp;
  }
  // Try to add, mult and concat next:
  LL next = ops[idx];
  return can2(answer, tmp+next, ops, idx+1)
    || can2(answer, tmp*next, ops, idx+1)
    || can2(answer, concat(tmp,next), ops, idx+1);
}

int main() {
  LL answer1 = 0, answer2 = 0;

  string line;
  while(getline(cin, line)) {
    FORUI(line.size()) {
      if(line[i] == ':')
	line[i] = ' ';
    }
    stringstream ss; ss << line;
    LL answer, op;
    vector<LL> ops;
    ss >> answer;
    while(ss >> op) {
      ops.push_back(op);
    }
    if(can(answer, ops[0], ops, 1)) {
      answer1 += answer;
      answer2 += answer;      
    }
    else if(can2(answer, ops[0], ops, 1)) {
      answer2 += answer;
    }
  }
  
  cout << answer1 << endl << answer2 << endl;
}
