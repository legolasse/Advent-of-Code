// 71 for normal input, 7 for sample:
#define SIZE 71
// 1024 for normal input, 12 for sample
#define DROPS 1024

int W = SIZE, H = SIZE, G[SIZE][SIZE]; // -1 = corrupted, 0 = free, 1+ = visit in round
vector<PI> drops;

void pri() {
  cout << endl;
  FORY(H) {
    FORX(W) {
      int v = G[y][x];
      if(v == 0)
	cout << " ";
      else if(v == -1)
	cout << "#";
      else
	cout << ".";
    }
    cout << endl;
  }
  cout << endl;
}

bool round(int number) {
  bool any = false;
  FORY(H) {
    FORX(W) {
      if(G[y][x] != 0)
	continue;
      if((x > 0 && G[y][x-1] == number-1) ||
	 (y > 0 && G[y-1][x] == number-1) ||
	 (x < W-1 && G[y][x+1] == number-1) ||
	 (y < H-1 && G[y+1][x] == number-1)) {
	G[y][x] = number;
	any = true;
      }
    }
  }
  return any;
}

void reset(int n) {
  FORY(H) {
    FORX(H) {
      G[y][x] = 0;
    }
  }
  G[0][0] = 1;
  for(int i = 0; i < n && i < (int)drops.size(); i++) {
    PI p = drops[i];
    G[p.YY][p.XX] = -1;
  }
}

int main() {
  FORY(H) {
    FORX(H) {
      G[y][x] = 0; // Unvisited
    }
  }
  string line;
  while(getline(cin, line)) {
    FORUI(line.size()) {
      if(line[i] == ',')
	line[i] = ' ';
    }
    stringstream ss; ss << line;
    int x, y; ss >> x >> y;
    drops.push_back(PI(x,y));
  }
  int answer1 = 0, answer2 = DROPS;
  
  // Part 1:
  reset(DROPS);
  while(G[H-1][W-1] == 0) {
    round(answer1+2);
    answer1++;
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  while(true) {
    reset(answer2);
    bool blocked = false;
    for(int n = 2; G[H-1][W-1] == 0; n++) {
      if(!round(n)) {
	blocked = true;
	break;
      }
    }
    if(blocked) {
      //pri();
      cout << "Answer 2: " << drops[answer2-1].XX << "," << drops[answer2-1].YY << endl;
      break;
    }
    answer2++;
  }
}
