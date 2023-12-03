vector<string> v;
int numN = 0;
LL numbers[2000];
LL* V[141*141];

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

char get(int x, int y) {
  if(x < 0 || y < 0 || x >= (int)v[0].size() || y >= (int)v.size())
    return '.';
  return v[y][x];
}

LL* getN(int x, int y) {
  if(x < 0 || y < 0 || x >= (int)v[0].size() || y >= (int)v.size())
    return NULL;
  return V[y*141 + x];
}

bool isSymbol(int x, int y) {
  char c = get(x, y);
  return !(isDigit(c) || c == '.');
}

int main() {
  string s;
  while(cin >> s)
    v.push_back(s);

  LL answer1 = 0, answer2 = 0;

  FORY((int)v.size()) {
    bool isNumber = false, numberOK = false;
    LL number = 0;

    FORX((int)v[0].size()+1) {
      char c = get(x, y);
      if(isDigit(c)) {
	isNumber = true;
	V[(y*141) + x] = &(numbers[numN]);
	number = 10*number + (c-'0');
	if(isSymbol(x-1, y-1) || isSymbol(x-1, y) || isSymbol(x-1, y+1) ||
	   isSymbol(x  , y-1)                     || isSymbol(x  , y+1) ||
	   isSymbol(x+1, y-1) || isSymbol(x+1, y) || isSymbol(x+1, y+1)) {
	  numberOK = true;
	}
      }
      else {
	V[(y*141) + x] = NULL;
	if(isNumber && numberOK) {
	  answer1 += number;
	  numbers[numN++] = number;
	}
	isNumber = numberOK = false;
	number = 0;
      }
    }
  }
  cout << "Answer 1: " << answer1 << endl;

  FORY((int)v.size()) {
    FORX((int)v[0].size()) {
      if(get(x, y) != '*') continue;
      set<LL*> neighbours;
      for(int yy = y-1; yy <= y+1; yy++) {
	for(int xx = x-1; xx <= x+1; xx++) {
	  if(xx == x && yy == y) continue;
	  LL* n = getN(xx,yy);
	  if(n != NULL)
	    neighbours.insert(n);
	}
      }
      if(neighbours.size() == 2)
	answer2 += **neighbours.begin() * **neighbours.rbegin();
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
