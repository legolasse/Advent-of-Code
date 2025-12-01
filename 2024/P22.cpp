vector<int> V;

LL prune(LL a) {
  return a % 16777216;
}

LL mix(LL a, LL b) {
  return a ^ b;
}

LL next(LL x) {
  x = mix(x, x*64);
  x = prune(x);
  x = mix(x, x/32);
  x = prune(x);
  x = mix(x, x*2048);
  x = prune(x);
  return x;
}

LL iterate(LL x, int iterations) {
  FORI(iterations) {
    x = next(x);
  }
  return x;
}

int getBananas(int a, int b, int c, int d, int x) {
  int diffs[4];
  FORI(2000) {
    int prev = x;
    x = next(x);
    diffs[i%4] = (x%10)-(prev%10);
    if(i >= 3) {
      if(diffs[(i+0)%4] == d &&
	 diffs[(i+1)%4] == a &&
	 diffs[(i+2)%4] == b &&
	 diffs[(i+3)%4] == c) {
	return x%10;
      }
    }
  }
  return 0;
}

int main() {
  LL answer1 = 0, answer2 = 0;

  // Part 1:
  string line;
  while(getline(cin, line)) {
    int x = atoi(line.c_str());
    V.push_back(x);
    LL y = iterate(x, 2000);
    //cout << x << ": " << y << endl;
    answer1 += y;
  }
  cout << "Answer 1: " << answer1 << endl;
  
  // Part 2:
  int min = -9, max = 9;
  for(int a = -5; a <= max; a++) {
    for(int b = min; b <= max; b++) {
      if(9 + a + b < 0 || 0 + a + b > 9)
	continue;
      for(int c = min; c <= max; c++) {
	if(9 + a + b + c < 0 || 0 + a + b + c > 9)
	  continue;
	for(int d = 0; d <= max; d++) {
	  if(9 + a + b + c + d < 0 || 0 + a + b + c + d > 9)
	    continue;
	  //cout << "Trying " << a << " " << b << " " << c << " " << d << ", current best: " << answer2 << endl;
	  LL bananas = 0;
	  FORIT(vector<int>, V) {
	    bananas += getBananas(a, b, c, d, *it);
	  }
	  if(bananas > answer2) {
	    answer2 = bananas;
	    cout << " " << a << " " << b << " " << c << " " << d << " => " << bananas << endl;
	  }
	}
      }
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
