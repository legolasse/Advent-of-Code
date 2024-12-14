int W = 101, H = 103;
//int W = 11, H = 7; // For sample input
int quadrants[4] = {0,0,0,0};
vector<PI> P, V;
int x,y,vx,vy,G[103][101];

int main() {
  int answer1 = 1, answer2 = 0;

  string line;
  while(getline(cin, line)) {
    FORUI(line.size()) {
      char c = line[i];
      if(c == '-' || (c >= '0' && c <= '9'))
	continue;
      line[i] = ' ';
    }
    stringstream ss; ss << line;
    ss >> x >> y >> vx >> vy;

    // Part 2:
    P.push_back(PI(x,y));
    V.push_back(PI(vx,vy));

    // Move for 100 seconds:
    x = (x + 100 * (vx+W))%W;
    y = (y + 100 * (vy+H))%H;
    if(x == W/2 || y == H/2)
      continue; // Not counted.
    int quadrant = (x < W/2)*2 + (y < H/2)*1;
    quadrants[quadrant]++;
  }

  FORI(4) {
    cout << "Quadrant " << i << ": " << quadrants[i] << endl;
    answer1 *= quadrants[i];
  }

  FORI(100000) {
    FORY(H) {
      FORX(W) {
	G[y][x] = 0;
      }
    }
    FORUJ(P.size()) {
      x = P[j].XX;
      y = P[j].YY;
      vx = V[j].XX;
      vy = V[j].YY;
      x = (x + i * (vx+W))%W;
      y = (y + i * (vy+H))%H;
      G[y][x]++;
    }
    // Check if picture:
    int check = 0;
    FORY(H-1) {
      FORX(W-1) {
	if(G[y][x] == 0)
	  continue;
	if(G[y][x+1] > 0 || G[y+1][x] > 0)
	  check++;
      }
    }
    if(check < ((int)P.size())/4) {
      continue; // Skip
    }

    cout << "After " << i << " seconds:" << endl;
    FORY(H) {
      FORX(W) {
	if(G[y][x] == 0)
	  cout << '.';
	else
	  cout << G[y][x];
      }
      cout << endl;
    }
    cout << endl;
    answer2 = i;
    break;
  }
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
