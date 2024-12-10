vector<string> G;
set<PI> tops[54][54];
int W, H, ratings[54][54];

void add(int x1, int y1, int x2, int y2) {
  if(x2 < 0 || x2 >= W || y2 < 0 || y2 >= H) {
    return; // Out of bounds
  }
  int a = G[y1][x1];
  int b = G[y2][x2];
  if(b == a+1) {
    FORIT(set<PI>, tops[y2][x2]) {
      tops[y1][x1].insert(*it);
    }
    ratings[y1][x1] += ratings[y2][x2];
  }
}

int main() {
  string line;
  while(getline(cin, line)) {
    G.push_back(line);
    W = (int)line.size();
    FORX(W) {
      int n = line[x]-'0';
      if(n == 9) {
	tops[H][x].insert(PI(x,H));
	ratings[H][x] = 1;
      }
      else {
	ratings[H][x] = 0;
      }
    }
    H++;
  }
  
  // Part 1:
  int answer1 = 0, answer2 = 0;
  for(int a = 8; a >= 0; a--) {
    FORY(H) {
      FORX(W) {
	if(G[y][x] - '0' != a) {
	  continue; // Not a
	}
	add(x, y, x-1, y);
	add(x, y, x+1, y);
	add(x, y, x, y-1);
	add(x, y, x, y+1);
	if(a == 0) {
	  answer1 += tops[y][x].size();
	  answer2 += ratings[y][x];
	}
      }
    }
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
