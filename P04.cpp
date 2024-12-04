char S[200][200];
char T[200][200];
int W = 0, H = 0;

void pri() {
  cout << "size " << W << " x " << H << ":" << endl;
  FORY(H) {
    FORX(W) {
      cout << S[y][x];
    }
    cout << endl;
  }
  cout << endl;
}

void rot() {
  // Copy into T:
  FORY(H) {
    FORX(W) {
      T[y][x] = S[y][x];
    }
  }
  // Rotate:
  swap(W, H);
  FORY(H) {
    FORX(W) {
      S[y][x] = T[x][H-y-1];
    }
  }
}

int cnt() {
  int ret = 0;
  FORY(H) {
    FORX(W) {
      if(x+3 < W &&
	 S[y][x+0] == 'X' &&
	 S[y][x+1] == 'M' &&
	 S[y][x+2] == 'A' &&
	 S[y][x+3] == 'S') {
	ret++;
      }
      
      if(x+3 < W &&
	 y+3 < H &&
	 S[y+0][x+0] == 'X' &&
	 S[y+1][x+1] == 'M' &&
	 S[y+2][x+2] == 'A' &&
	 S[y+3][x+3] == 'S') {
	ret++;
      }
    }
  }
  return ret;
}

int cnt2() {
  int ret = 0;
  for(int y = 1; y < H-1; y++) {
    for(int x = 1; x < W-1; x++) {
      if(S[y][x] != 'A')
	continue;

      // a b
      //  A
      // c d
      char a = S[y-1][x-1];
      char b = S[y-1][x+1];
      char c = S[y+1][x-1];
      char d = S[y+1][x+1];
      if(a == d || b == c)
	continue;
      if(a != 'M' && a != 'S')
	continue;
      if(b != 'M' && b != 'S')
	continue;
      if(c != 'M' && c != 'S')
	continue;
      if(d != 'M' && d != 'S')
	continue;
      ret++;
    }
  }
  return ret;
}

int main() {  
  string s;
  while(cin >> s) {
    W = (int)s.size();
    FORI(W) {
      S[H][i] = s[i];
    }
    H++;
  }

  int answer1 = 0, answer2 = cnt2();

  FORI(4) {
    pri();
    answer1 += cnt();
    rot();
  }
  pri();
  
  cout << answer1 << endl << answer2 << endl;
}
