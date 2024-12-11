int AGE = 0;
set<PLL> seen;
map<PLL,LL> cnt;

struct Stone {
  LL value, age;
  bool isSplit;
  Stone *L, *R;

  void pri() {
    if(isSplit) {
      L->pri();
      cout << " ";
      R->pri();
    }
    else {
      cout << value;
    }
  }

  void kill() {
    if(isSplit) {
      L->kill();
      R->kill();
      delete L;
      delete R;
    }
  }

  void blink() {
    if(seen.find(PLL(value,age)) != seen.end()) {
      return; // Seen!
    }
    
    if(isSplit) {
      L->blink();
      R->blink();
      seen.insert(PLL(value,age));
      return;
    }

    if(value == 0) {
      value++;
      age = AGE;
      seen.insert(PLL(value,age));
      return;
    }

    LL v = value;
    int digits = 0;
    while(v > 0) {
      digits++;
      v/=10;
    }

    if(digits % 2 == 0) {
      isSplit = true;
      L = new Stone();
      L->isSplit = false;
      L->age = AGE;
      R = new Stone();
      R->isSplit = false;
      R->age = AGE;
      stack<int> s;
      v = value;
      while(v > 0) {
	s.push(v%10);
	v /= 10;
      }
      L->value = 0;
      FORI(digits/2) {
	L->value *= 10;
	L->value += s.top();
	s.pop();
      }
      FORI(digits/2) {
	R->value *= 10;
	R->value += s.top();
	s.pop();
      }
    }
    else {
      value *= 2024;
      age = AGE;
    }
    seen.insert(PLL(value,age));
  }

  LL count() {
    if(cnt.find(PLL(value,age)) != cnt.end()) {
      return cnt[PLL(value,age)]; // Seen!
    }

    LL ret;
    if(!isSplit)
      ret = 1;
    else
      ret = L->count() + R->count();

    cnt[PLL(value,age)] = ret;

    return ret;
  }
};

int main() {
  LL answer = 0;
  
  Stone stone;
  int s;
  while(cin >> s) {
    AGE = 0;
    stone.value = s;
    stone.isSplit = false;
    stone.age = 0;
    FORI(75) { // Set to 25 for part 1 and 75 for part 2
      stone.blink();
      seen.clear();
      //stone.pri(); cout << endl << endl;
      AGE++;
    }
    answer += stone.count();
    cnt.clear();
    stone.kill();
  }

  cout << "Answer: " << answer << endl;
}
