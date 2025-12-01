vector<string> G;
int W, H, UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
PI _up(0,-1), _right(1,0), _down(0,1), _left(-1,0), dirs[4] = {_up, _right, _down, _left};
string chars = "^>v<x";
LL costS[150][150], costT[150][150], HIGH = 9999999999999;
PI S, T;

int main() {
  string line;
  while(getline(cin, line)) {
    W = (int)line.size();
    FORX(W) {
      costS[H][x] = HIGH;
      costT[H][x] = HIGH;
      if(line[x] == 'S') {
	S = PI(x,H);
	costS[H][x] = 0;
      }
      else {
	if(line[x] == 'E') {
	  T = PI(x,H);
	  costT[H][x] = 0;
	}
      }
    }
    G.push_back(line);
    H++;
  }
  cout << "Grid size " << W << " x " << H << endl;
  cout << " Start " << S.XX << ", " << S.YY << endl;
  cout << " End " << T.XX << ", " << T.YY << endl;

  bool improved = true;
  for(LL round = 0; improved; round++) {
    improved = false;
    FORY(H) {
      FORX(W) {
	char c = G[y][x];
	if(c == '#')
	  continue;
	// Try to walk:
	FORI(4) {
	  int nx = x - dirs[i].XX;
	  int ny = y - dirs[i].YY;
	  if(G[ny][nx] == '#')
	    continue;
	  // Update costS and costT:
	  if(costS[ny][nx] == round && costS[y][x] == HIGH) {
	    costS[y][x] = round+1;
	    improved = true;
	  }
	  if(costT[ny][nx] == round && costT[y][x] == HIGH) {
	    costT[y][x] = round+1;
	    improved = true;
	  }
	}
      }
    }
  }

  // Part 1:
  LL standard = costS[T.YY][T.XX];
  cout << "Race length without cheating: " << standard << endl;
  
  PI skips[8];
  int skipsIdx = 0;
  FORI(3)
    skips[skipsIdx++] = PI(-1+i, -1);
  skips[skipsIdx++] = PI(-1, 0);
  skips[skipsIdx++] = PI(1, 0);
  FORI(3)
    skips[skipsIdx++] = PI(-1+i, 1);

  LL answer1 = 0;
  LL minSkip = W > 100 ? 100 : 1; // No min in sample
  for(int y = 1; y < H-1; y++) {
    for(int x = 1; x < W-1; x++) {
      if(G[y][x] != '#')
	continue;

      FORI(4) {
	int xi = x + dirs[i].XX;
	int yi = y + dirs[i].YY;
	if(G[yi][xi] == '#')
	  continue;
	LL startCost = costS[yi][xi];
	
	FORJ(4) {
	  int xj = x+dirs[j].XX;
	  int yj = y+dirs[j].YY;
	  if(i == j || G[yj][xj] == '#')
	    continue;
	  LL endCost = costT[yj][xj];
	  
	  if(endCost + startCost + minSkip + 2 <= standard) {
	    // Skip found!
	    answer1++;
	  }
	}
      }
    }
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  LL answer2 = 0;

  for(int y1 = 1; y1 < H-1; y1++) {
    for(int x1 = 1; x1 < W-1; x1++) {
      if(G[y1][x1] == '#')
	continue;
      LL startCost = costS[y1][x1];
      
      for(int y2 = 1; y2 < H-1; y2++) {
	for(int x2 = 1; x2 < W-1; x2++) {
	  if(G[y2][x2] == '#')
	    continue;
	  int dx = ABS(x2-x1);
	  int dy = ABS(y2-y1);
	  int d = dx+dy;
	  if(d > 20)
	    continue; // Cheat too long!
	  LL endCost = costT[y2][x2];
	  if(endCost + startCost + minSkip + d <= standard) {
	    // Skip found!
	    answer2++;
	  }
	}
      }
    }
  }
  
  cout << "Answer 2: " << answer2 << endl;
}
