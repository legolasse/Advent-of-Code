int main() {
  int answer1 = 0, answer2 = 0;

  int dial = 50, d2 = 50;
  string s;
  while(cin >> s) {
    int toAdd = atoi(s.c_str()+1);

    if(s[0] == 'L') {
      FORUI(toAdd) {
	d2--;
	if(d2 == 0)
	  answer2++;
	if(d2 < 0)
	  d2 = 99;
      }
      dial -= toAdd;
    }
    else {
      FORUI(toAdd) {
	d2++;
	if(d2 == 100) {
	  answer2++;
	  d2 = 0;
	}
      }
      dial += toAdd;
    }

    dial += 1000;
    dial %= 100;

    if(dial == 0)
      answer1++;
  }

  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
