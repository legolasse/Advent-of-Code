string dirs = "^>v<";

vector<string> grid;

void pri(PI guard, int dir) {
  FORUY(grid.size()) {
    FORUX(grid[0].size()) {
      if(guard.YY == y && guard.XX == x) {
	cout << dirs[dir];
      }
      else {
	cout << grid[y][x];
      }
    }
    cout << endl;
  }
  cout << endl;
}

int cnt(PI guard, int dir) {
  set<PI> seen;
  set<PI> seenDir[4];
  // Part 1: walk:
  while(true) {
    //pri();
    seen.insert(guard);
    if(seenDir[dir].find(guard) == seenDir[dir].end()) {
      seenDir[dir].insert(guard);
    }
    else {
      return 0;
    }

    PI next = guard;

    switch(dir) {
    case 0: // Up
      next.YY--;
      break;
    case 1:
      next.XX++;
      break;
    case 2:
      next.YY++;
      break;
    case 3:
      next.XX--;
      break;
    }

    if(next.XX < 0 || next.YY < 0 || next.XX >= (int)grid[0].size() || next.YY >= (int)grid.size()) {
      break;
    }

    if(grid[next.YY][next.XX] == '#') {
      dir = (dir+1)%4;
    }
    else {
      guard = next;
    }
  }
  return (int)seen.size();
}

int main() {
  PI guard;
  int dir = -1;
  
  // Read input:
  string line;
  while(getline(cin, line)) {
    if(dir == -1) { // Guard not seen yet:
      FORUI(line.size()) {
	char c = line[i];
	if(c != '#' && c != '.') {
	  guard.XX = (int)i;
	  guard.YY = (int)grid.size();
	  FORJ(4) {
	    if(c == dirs[j]) {
	      dir = j;
	      break;
	    }
	  }
	  line[i] = '.';
	}
      }
    }
    grid.push_back(line);
  }

  // Part 1: walk:
  cout << "Answer 1: " << cnt(guard, dir) << endl;

  // Part 2: Try to make loops (optimize by only checking the places where the guard has walked... But this is fast enough in C++...)
  int answer2 = 0;
  FORUY(grid.size()) {
    FORUX(grid[0].size()) {
      if(grid[y][x] == '#') {
	continue; // Already obstructed
      }
      if(guard.YY == y && guard.XX == x) {
	continue; // Guard is here
      }
      grid[y][x] = '#';
      if(cnt(guard, dir) == 0) {
	answer2++;
      }
      grid[y][x] = '.'; // Restore
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
