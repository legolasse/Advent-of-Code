char board[500][500];
map<LL,LL> mx, my;
vector<LL> vx, vy;

void printBoard() {
  cout << endl;
  FORUY(vy.size()) {
    FORUX(vx.size()) {
      cout << board[y][x];
    }
    cout << endl;
  }
  cout << endl;
}

LL decode(string &s, int &idx) {
  LL ret = 0;
  while(idx < s.size()) {
    char c = s[idx];
    if(c == ',') {
      idx++; // Range indicator
      break;
    }
    ret = 10*ret + c - '0';
    idx++;
  }

  return ret;
}

PLL decodeRange(string &s) {
  int idx = 0;
  return PLL(decode(s,idx),decode(s,idx));
}

LL area(PLL a, PLL b) {
  LL dx = ABS(a.first-b.first) + 1;
  LL dy = ABS(a.second-b.second) + 1;
  return dx * dy;
}

bool areaOK(PLL a, PLL b) {
  LL x1 = mx[a.XX];
  LL y1 = my[a.YY];
  LL x2 = mx[b.XX];
  LL y2 = my[b.YY];

  if(x1 > x2)
    swap(x1,x2);
  if(y1 > y2)
    swap(y1,y2);

  for(int y = y1; y <= y2; y++) {
    for(int x = x1; x <= x2; x++) {
      if(board[y][x] == '.')
	return false;
    }
  }
  return true;
}

int main() {
  FORX(500) {
    FORY(500) {
      board[y][x] = ' ';
    }
  }
  LL answer1 = 0, answer2 = 0;
  vector<PLL> red;
  set<LL> sx, sy;

  string s;
  
  PLL maxTile;
  while(getline(cin, s)) {
    PLL tile = decodeRange(s);
    sx.insert(tile.XX);
    sy.insert(tile.YY);
    red.push_back(tile);
    maxTile.XX = MAX(maxTile.XX, tile.XX);
    maxTile.YY = MAX(maxTile.YY, tile.YY);
  }
  sx.insert(0);
  sy.insert(0);
  sx.insert(maxTile.XX+1);
  sy.insert(maxTile.YY+1);

  int idx = 0;
  FORIT(set<LL>, sx) {
    mx[*it] = idx;
    vx.push_back(idx++);
  }
  idx = 0;
  FORIT(set<LL>, sy) {
    my[*it] = idx;
    vy.push_back(idx++);
  }

  // Part 1:
  FORIT(vector<PLL>, red) {
    FORIT2(vector<PLL>, red) {
      LL a = area(*it, *it2);
      answer1 = MAX(answer1, a);
    }
  }

  // Part 2:
  PLL prev = PLL(mx[red[red.size()-1].XX], my[red[red.size()-1].YY]);
  board[prev.YY][prev.XX] = '#';
  FORIT(vector<PLL>, red) {
    PLL p = PLL(mx[it->XX], my[it->YY]);
    //cout << "Walk " << prev.XX <<","<<prev.YY<<" -> " <<p.XX<<","<<p.YY<<endl;
    board[p.YY][p.XX] = '#';
    if(prev.XX == p.XX) {
      LL minY = MIN(p.YY, prev.YY);
      LL maxY = MAX(p.YY, prev.YY);
      for(LL y = minY+1; y < maxY; y++)
	board[y][p.XX] = 'X';
    }
    else {
      LL minX = MIN(p.XX, prev.XX);
      LL maxX = MAX(p.XX, prev.XX);
      for(LL x = minX+1; x < maxX; x++)
	board[p.YY][x] = 'X';
    }
    prev = p;
  }
  //printBoard();

  // Draw in rest:
  PLL p(0,0);
  set<PLL> wave, wave2;
  wave.insert(p);
  while(!wave.empty()) {
    FORIT(set<PLL>, wave) {
      p = *it;
      char c = board[p.YY][p.XX];
      if(c != ' ')
	continue;
      board[p.YY][p.XX] = '.';
      for(int x = MAX(0,p.XX-1); x < MIN(p.XX+2,(int)vx.size()); x++) {
	for(int y = MAX(0,p.YY-1); y < MIN(p.YY+2,(int)vy.size()); y++) {
	  if(board[y][x] == ' ') {
	    wave2.insert(PLL(x,y));
	  }
	}
      }
    }
    swap(wave,wave2);
    wave2.clear();
  }
  printBoard();

  // Finally, compute max rect:
  FORIT(vector<PLL>, red) {
    FORIT2(vector<PLL>, red) {
      if(!areaOK(*it, *it2))
	continue;
      
      LL a = area(*it, *it2);
      answer2 = MAX(answer2, a);
    }
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
