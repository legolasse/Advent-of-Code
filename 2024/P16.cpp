vector<string> G;
int W, H, UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
PI _up(0,-1), _right(1,0), _down(0,1), _left(-1,0), dirs[4] = {_up, _right, _down, _left};
string chars = "^>v<x";
LL cost[4][141][141], HIGH = 9999999999999;
PI S, T;
bool part2[4][141][141];

int main() {
  string line;
  while(getline(cin, line)) {
    W = (int)line.size();
    FORX(W) {
      if(line[x] == 'S') {
	S = PI(x,H);
	FORI(4) {
	  cost[i][H][x] = (i == RIGHT) ? 0 : HIGH;
	}
      }
      else {
	FORI(4)
	  cost[i][H][x] = HIGH;
	if(line[x] == 'E') {
	  T = PI(x,H);
	}
      }
    }
    G.push_back(line);
    H++;
  }
  cout << "Grid size " << W << " x " << H << endl;
  cout << " Start " << S.XX << ", " << S.YY << endl;

  bool improved = true;
  while(improved) {
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
	  LL neighbour = cost[i][ny][nx] + 1;
	  if(G[ny][nx] != '#' && neighbour < cost[i][y][x]) {
	    cost[i][y][x] = neighbour;
	    improved = true;
	  }
	  // Try to turn right:
	  if(cost[(i+1)%4][y][x] + 1000 < cost[i][y][x]) {
	    cost[i][y][x] = cost[(i+1)%4][y][x] + 1000;
	    improved = true;
	  }
	  // Try to turn left:
	  if(cost[(i+3)%4][y][x] + 1000 < cost[i][y][x]) {
	    cost[i][y][x] = cost[(i+3)%4][y][x] + 1000;
	    improved = true;
	  }
	}
      }
    }
  }
  LL answer1 = HIGH;
  FORI(4) {
    int x = T.XX;
    int y = T.YY;
    answer1 = MIN(answer1, cost[i][y][x]);
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  FORY(H) {
    FORX(W) {
      FORI(4) {
	if(cost[i][y][x] == answer1) {
	  G[y][x] = 'O';
	  part2[i][y][x] = true;
	}
	else {
	  part2[i][y][x] = false;
	}
      }
    }
  }
  improved = true;
  while(improved) {
    improved = false;
    FORY(H) {
      FORX(W) {
	char c = G[y][x];
	if(c == '#')
	  continue;
	FORI(4) {
	  if(!part2[i][y][x])
	    continue;
	  int nx = x - dirs[i].XX;
	  int ny = y - dirs[i].YY;
	  if(G[ny][nx] != '#' && !part2[i][ny][nx] && cost[i][ny][nx] == cost[i][y][x]-1) {
	    G[ny][nx] = 'O';
	    part2[i][ny][nx] = true;
	    improved = true;
	  }
	  // Turning:
	  if(!part2[(i+1)%4][y][x] && cost[(i+1)%4][y][x] + 1000 == cost[i][y][x]) {
	    part2[(i+1)%4][y][x] = true;
	    improved = true;
	  }
	  if(!part2[(i+3)%4][y][x] && cost[(i+3)%4][y][x] + 1000 == cost[i][y][x]) {
	    part2[(i+3)%4][y][x] = true;
	    improved = true;
	  }
	}
      }
    }
  }

  LL answer2 = 0;
  FORY(H) {
    cout << G[y] << endl;
    FORX(W) {
      if(G[y][x] == 'O') {
	answer2++;
      }
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
