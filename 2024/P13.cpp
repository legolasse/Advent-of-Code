/*
  Analysis:
  For all inputs:
  ax != ay
  proportions ax/ay != bx/by
  So all answers are unique!
 */

bool getInt(LL &a) {
  string s;
  while(cin >> s) {
    a = 0;
    bool any = false;
    FORUI(s.size()) {
      char c = s[i];
      if(c >= '0' && c <= '9') {
	a = 10*a + (c-'0');
	any = true;
      }
    }
    if(any)
      return true;
  }
  return false;
}

int main() {
  /*
    a * ax + b * bx == x
    a * ay + b * by == y
    Minimize cost = 3 * a + b
  */
  LL answer1 = 0, answer2 = 0;
  LL ax, ay, bx, by, X, Y;
  while(getInt(ax)) {
    getInt(ay);
    getInt(bx);
    getInt(by);
    getInt(X);
    getInt(Y);
    if(ax < ay) {
      swap(ax, ay);
      swap(bx, by);
      swap(X, Y);	
    }
    //cout << "A: " << ax << ", " << ay << endl;
    //cout << "B: " << bx << ", " << by << endl;
    //cout << "Price: " << X << ", " << Y << endl;

    // Part 1:
    FORI(101) {
      FORJ(101) {
	LL x = i * ax + j * bx;
	LL y = i * ay + j * by;
	if(x == X && y == Y) {
	  answer1 += 3*i + 1*j; // See analysis above!
	}
      }
    }

    // Part 2:
    X += 10000000000000;
    Y += 10000000000000;

    // Find a suitable high value for b:
    LL bHigh = MIN(X / bx, Y / by);
    while(bHigh * bx > X || bHigh * by > Y)
      bHigh--;
    LL bLow = 1;

    // Binary search B to make proportions
    // X-(b*bx) to Y-(b*by)
    // match
    // ax / ay
    // (X-(b*bx)) / (Y-(b*by)) == ax / ay
    // (X-(b*bx)) * ay == (Y-(b*by)) * ax

    // We know ax > ay:
    while(bLow < bHigh-1) {
      LL b = (bLow+bHigh)/2;
      LL left = (X-(b*bx)) * ay;
      LL right = (Y-(b*by)) * ax;
      if(left <= right) {
	bLow = b;
      }
      else {
	bHigh = b;
      }
    }

    // Wiggle-search for a and b:
    for(LL b = bHigh+1; b >= bLow; b--) {
      LL a = (X-(b*bx))/ax;
      if(X == a*ax + b*bx && Y == a*ay + b*by) {	
	answer2 += 3*a+b;
	break;
      }
    }
  }
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
