typedef map<PC,string> ssmap;
ssmap numpadMoves, dpadMoves; // <ST> -> <move chars>
string numpad = "789456123 0A", dpad = " ^A<v>";
typedef map<char,PI> posmap;
posmap numpadPos, dpadPos; // char -> pos
map<string,LL> cache[26];

// Key insight:
// < is most expensive to press, so we want to do < before any other operation, and:
// ^v before A>
bool is0A(char c) {
  return c == '0' || c == 'A';
}

bool is147(char c) {
  return c == '1' || c == '4' || c == '7';
}

bool dangerNumpad(char c1, char c2) {
  return (is0A(c1) && is147(c2)) || (is0A(c2) && is147(c1));
}

bool dangerDpad(char c1, char c2) {
  return c1 == '<' || c2 == '<';
}

bool danger(char c1, char c2) {
  return dangerNumpad(c1, c2) || dangerDpad(c1, c2);
}

// See comments in top!
void populate(const posmap &pos, ssmap &moves) {
  FORIT(posmap, pos) {
    char c1 = it->first;
    PI p1 = it->second;
    FORIT2(posmap, pos) {
      char c2 = it2->first;
      PI p2 = it2->second;
      stringstream ss;
      if(danger(c1, c2)) {
	FORI(-p1.XX + p2.XX) {
	  ss << '>';
	}
	FORI(-p1.YY + p2.YY) {
	  ss << 'v';
	}
	FORI(p1.YY - p2.YY) {
	  ss << '^';
	}
	FORI(p1.XX - p2.XX) {
	  ss << '<';
	}
      }
      else {
	FORI(p1.XX - p2.XX) {
	  ss << '<';
	}
	FORI(-p1.YY + p2.YY) {
	  ss << 'v';
	}
	FORI(p1.YY - p2.YY) {
	  ss << '^';
	}
	FORI(-p1.XX + p2.XX) {
	  ss << '>';
	}
      }
      ss << 'A';
      moves[PC(c1,c2)] = ss.str();
    }
  }
}

// Assume only one A, and it is the last character
// Assume robot starts at A
LL cnt(const int robotsLeft, const string &s) {
  if(robotsLeft == 0) { // Last robot: Just walk!
    return (LL)s.size();
  }
  if(cache[robotsLeft].find(s) != cache[robotsLeft].end()) {
    return cache[robotsLeft][s];
  }

  LL ret = 0;
  char prev = 'A';
  FORUI(s.size()) {
    char c = s[i];
    ret += cnt(robotsLeft-1, dpadMoves[PC(prev,c)]);
    prev = c;
  }

  cache[robotsLeft][s] = ret;
  return ret;
}

int main() {
  // Numpad setup:
  FORI((int)numpad.size()) {
    char c = numpad[i];
    if(c == ' ')
      continue;
    int x = i % 3;
    int y = i / 3;
    numpadPos[c] = PI(x,y);
  }
  // DPad setup:
  FORI((int)dpad.size()) {
    char c = dpad[i];
    if(c == ' ')
      continue;
    int x = i % 3;
    int y = i / 3;
    dpadPos[c] = PI(x,y);
  }
  
  populate(numpadPos, numpadMoves);
  populate(dpadPos, dpadMoves);

  LL answer1 = 0, answer2 = 0;

  string line;
  while(getline(cin, line)) {
    LL x = 0, y = 0, z = 0;
    char prev = 'A';
    FORUI(line.size()) {
      char c = line[i];
      if(c >= '0' && c <= '9') {
	x = (x*10) + (c-'0');
      }
      string s = numpadMoves[PC(prev,c)];
      y += cnt(2, s);
      z += cnt(25, s);
      prev = c;
    }
    answer1 += x * y;
    answer2 += x * z;
  }

  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
