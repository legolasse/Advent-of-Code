vector<string> v, v2;
string s;
int width, height;

void north() {
  FORX(width) {
    for(int y = 0; y < height; y++) {
      char c = v[y][x];
      if(c == '#')
	continue;
      // Expect to be first non-#:
      int rocks = 0;
      int y2;
      for(y2 = y; y2 < height; y2++) {
	char c2 = v[y2][x];
	if(c2 == 'O')
	  rocks++;
	else if(c2 == '#') {
	  break;
	}
      }
      // Update:
      for(int y3 = y, cnt = 0; y3 < y2; y3++, cnt++) {
	v[y3][x] = cnt < rocks ? 'O' : '.';
      }
      // Next:
      y = y2;
    }
  }
}

LL load() {
  LL ret = 0;
  FORX(width) {
    FORY(height) {
      char c = v[y][x];
      if(c != 'O')
	continue;
      //cout << "Adding rock for x=" << x << ", y=" << y << ": " << (height-y) << endl;
      ret += height-y;
    }
  }
  return ret;
}

void rotate() {
  FORY(height) {
    FORX(width) {
      v2[y][x] = v[width-1-x][y];
    }
  }
  swap(v, v2);
}

void print() {
  FORY(height) {
    cout << v[y] << endl;
  }
  cout << endl;
}

LL hashV() {
  LL ret = 0;
  FORY(height) {
    FORX(width) {
      char c = v[y][x];
      ret = (ret * 43) + (c == '.' ? 27 : c == '#' ? 19 : 3);
    }
  }
  return ret;
}

int main() {
  // Read input:
  while(cin >> s) {
    v.push_back(s);
    v2.push_back(s);
  }
  width = v[0].size();
  height = v.size();
  cout << "Width: " << width << ", height: " << height << endl;

  // Part 1:
  north();
  print();
  cout << "Answer 1: " << load() << endl << endl;

  // Part 2:
  LL spins = 1000000000;
  map<LL,LL> m;
  for(LL i = 0; i < spins; i++) {    
    FORJ(4) {
      north();
      rotate();
    }
    LL h = hashV();
    if(m.find(h) == m.end()) {
      m[h] = i;
    }
    else {
      cout << "Found cycle! " << i << " = " << m[h] << endl;
      LL remaining = spins - i - 1;
      LL cycleLength = i-m[h];
      i += (remaining/cycleLength)*cycleLength;
    }
  }
  cout << "Answer 2: " << load() << endl;
}
