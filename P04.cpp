int main() {
  LL answer1 = 0, answer2 = 0;
  string s;
  vector<string> v;
  int w, h = 0;

  while(cin >> s) {
    w = (int)s.size();
    v.push_back(s);
    h++;
  }

  // Part 1:
  FORY(h) {
    FORX(w) {
      if(v[y][x] != '@')
	continue;
      int cnt = 0;
      for(int yy = MAX(0,y-1); yy <= y+1 && yy < h; yy++) {
	for(int xx = MAX(0,x-1); xx <= x+1 && xx < w; xx++) {
	  if(v[yy][xx] == '@')
	    cnt++;
	}
      }
      if(cnt < 4 + 1) {
	answer1++;
      }
    }
  }

  // Part 2:
  bool improved = true;
  while(improved) {
    improved = false;
    FORY(h) {
      FORX(w) {
	if(v[y][x] != '@')
	  continue;
	int cnt = 0;
	for(int yy = MAX(0,y-1); yy <= y+1 && yy < h; yy++) {
	  for(int xx = MAX(0,x-1); xx <= x+1 && xx < w; xx++) {
	    if(v[yy][xx] == '@')
	      cnt++;
	  }
	}
	if(cnt < 4 + 1) {
	  answer2++;
	  improved = true;
	  v[y][x] = ' ';
	}
      }
    }
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
