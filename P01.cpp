int ret = 0;
string x;

string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
string numbers[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

// For part 1:
int add() {
  int i = 0;
  while(true) {
    if(x[i] >= '0' && x[i] <= '9') {
      return x[i]-'0';
    }
    i++;
  }
}

int main() {
  while(cin >> x) {
    cout << x << endl;
    // Part 2 code:
    int min = 1000000, max = -1, minDigit, maxDigit;
    for(int i = 0; i < 9; i++) {
      size_t f = x.find(digits[i]);
      if(f != string::npos && f < min) {
	cout << i+1 << " at " << f << endl;
	minDigit = i+1;
	min = (int)f;
      }
      f = x.rfind(digits[i]);
      if(f != string::npos && (int)f > max) {
	cout << i+1 << " at " << f << endl;
	maxDigit = i+1;
	max = (int)f;
      }
    }
    for(int i = 0; i < 9; i++) {
      size_t f = x.find(numbers[i]);
      if(f != string::npos && f < min) {
	cout << i+1 << " at " << f << endl;
	minDigit = i+1;
	min = (int)f;
      }
      f = x.rfind(numbers[i]);
      if(f != string::npos && (int)f > max) {
	cout << i+1 << " at " << f << endl;
	maxDigit = i+1;
	max = (int)f;
      }
    }
    ret += 10*minDigit + maxDigit;

    // Part 1 code:
    //ret += 10*add();
    //reverse(x.begin(), x.end());
    //ret += add();
  }
  

  cout << "Result:" << endl << ret << endl;
  return 0;
}
