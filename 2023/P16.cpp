#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
vector<string> v;
string line;
int height, width;
bool E[112][112][4]; 

int run(int startX, int startY, int dir) {
  FORX(width+2) {
    FORY(height+2) {
      FORI(4) {
	E[x][y][i] = false;
      }
    }
  }
  E[startX][startY][dir] = true;

  // Flood fill:
  bool improved = true;
  while(improved) {
    improved = false;
    FORX(width) {
      int X = x+1;
      FORY(height) {
	int Y = y+1;
	char c = v[y][x];
	switch(c) {
	case '.':
	  if(!E[X][Y][RIGHT] && E[X-1][Y][RIGHT]) {
	    E[X][Y][RIGHT] = true;
	    improved = true;
	  }
	  if(!E[X][Y][DOWN] && E[X][Y-1][DOWN]) {
	    E[X][Y][DOWN] = true;
	    improved = true;
	  }
	  if(!E[X][Y][UP] && E[X][Y+1][UP]) {
	    E[X][Y][UP] = true;
	    improved = true;
	  }
	  if(!E[X][Y][LEFT] && E[X+1][Y][LEFT]) {
	    E[X][Y][LEFT] = true;
	    improved = true;
	  }
	  break;
	case '/':
	  if(!E[X][Y][RIGHT] && E[X][Y+1][UP]) {
	    E[X][Y][RIGHT] = true;
	    improved = true;
	  }
	  if(!E[X][Y][DOWN] && E[X+1][Y][LEFT]) {
	    E[X][Y][DOWN] = true;
	    improved = true;
	  }
	  if(!E[X][Y][UP] && E[X-1][Y][RIGHT]) {
	    E[X][Y][UP] = true;
	    improved = true;
	  }
	  if(!E[X][Y][LEFT] && E[X][Y-1][DOWN]) {
	    E[X][Y][LEFT] = true;
	    improved = true;
	  }
	  break;
	case '\\':
	  if(!E[X][Y][RIGHT] && E[X][Y-1][DOWN]) {
	    E[X][Y][RIGHT] = true;
	    improved = true;
	  }
	  if(!E[X][Y][DOWN] && E[X-1][Y][RIGHT]) {
	    E[X][Y][DOWN] = true;
	    improved = true;
	  }
	  if(!E[X][Y][UP] && E[X+1][Y][LEFT]) {
	    E[X][Y][UP] = true;
	    improved = true;
	  }
	  if(!E[X][Y][LEFT] && E[X][Y+1][UP]) {
	    E[X][Y][LEFT] = true;
	    improved = true;
	  }
	  break;
	case '-':
	  if(!E[X][Y][RIGHT] && (E[X-1][Y][RIGHT] || E[X][Y-1][DOWN] || E[X][Y+1][UP])) {
	    E[X][Y][RIGHT] = true;
	    improved = true;
	  }
	  if(!E[X][Y][LEFT] && (E[X+1][Y][LEFT] || E[X][Y+1][UP] || E[X][Y-1][DOWN])) {
	    E[X][Y][LEFT] = true;
	    improved = true;
	  }
	  break;
	case '|':
	  if(!E[X][Y][DOWN] && (E[X][Y-1][DOWN] || E[X-1][Y][RIGHT] || E[X+1][Y][LEFT])) {
	    E[X][Y][DOWN] = true;
	    improved = true;
	  }
	  if(!E[X][Y][UP] && (E[X][Y+1][UP] || E[X-1][Y][RIGHT] || E[X+1][Y][LEFT])) {
	    E[X][Y][UP] = true;
	    improved = true;
	  }
	  break;
	}
      }
    }
  }

  int ret = 0;
  FORY(height) {
    FORX(width) {
      bool e = false;
      FORI(4) {
	e = e || E[x+1][y+1][i];
      }
      //cout << (e ? '#' : '.');
      if(e)
	ret++;
    }
    //cout << endl;
  }
  return ret;
}

int main() {
  while(getline(cin, line)) {
    v.push_back(line);
  }
  width = (int)v[0].size();
  height = (int)v.size();

  cout << "Answer1: " << run(0, 1, RIGHT) << endl;
  int best = 0;
  FORX(width) {
    best = max(best, run(1+x, 0, DOWN));
    best = max(best, run(1+x, height+1, UP));
  }
  FORY(height) {
    best = max(best, run(0, 1+y, RIGHT));
    best = max(best, run(width+1, 1+y, LEFT));
  }
  cout << "Answer2: " << best << endl;
}
