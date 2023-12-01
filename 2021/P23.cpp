#define SIZE_TOP 7
#define STACK_SIZE 4

vector<char> v[4];
string s, top;
int best = 99999999;
int topPositions[SIZE_TOP] = {1, 2, 4, 6, 8, 10, 11};
bool ready[4] = {false, false, false, false}; // If v[] is ready to be filled.
LL counter = 0;

void readLine(bool read) {
  if(read)
    getline(cin, s);
  for(int i = 3, j = 0; i < 10; i+=2, j++) {
    v[j].push_back(s[i]);
  }
}

int getPrice(char c) {
  switch(c) {
  case 'A':
    return 1;
  case 'B':
    return 10;
  case 'C':
    return 100;
  case 'D':
    return 1000;
  }
  cerr << "Unknown " << c << endl; die(); return -1;
}

void print(int cost) {
  cout << "State at cost " << cost << " vs best " << best << endl;
  cout << "#############" << endl;
  cout << top << endl;
  FORI(STACK_SIZE) {
    if(i == 0) cout << "##";
    else cout << "  ";

    FORJ(4) {
      cout << "#";
      int idx = STACK_SIZE-i-1;
      if(idx >= v[j].size())
	cout << ".";
      else
	cout << v[j][idx];
    }

    if(i == 0) cout << "###" << endl;
    else cout << "#  " << endl;
  }
    cout << "  #########" << endl;

}

void go(int cost) {
  if(cost >= best)
    return;
  if(counter++ % 1000000 == 0)
    print(cost);

  // Sanity check:
  int sanity = 0;
  FORI(4)
    sanity += v[i].size();
  FORI(SIZE_TOP) {
    if(top[topPositions[i]] != '.')
      sanity++;
  }
  if(sanity != STACK_SIZE*4) {
    cout << "Sanity check fail!" << endl;
    die();
  }
  
  // Check end condition:
  bool done = true;
  FORI(4) {
    if(!ready[i]) {
      done = false;
      break;
    }
  }
  FORI(SIZE_TOP) {
    if(top[topPositions[i]] != '.') {
      done = false;
      break;
    }
  }
  if(done) {
    if(cost < best) {
      //print(cost);
      best = cost;
    }
    return;
  }
  
  // First clean up all that is possible:
  FORI(SIZE_TOP) {
    int pos = topPositions[i];
    char c = top[pos];
    if(c == '.')
      continue;
    // Try to push into v:
    int idxV = c-'A';
    if(!ready[idxV])
      continue;
    int posV = 3 + 2*idxV;
    bool ok = true;
    if(posV > pos) {
      for(int j = pos+1; j < posV; j++) {
	if(top[j] != '.') {
	  ok = false;
	  break;
	}
      }
    }
    else {
      for(int j = pos-1; j > posV; j--) {
	if(top[j] != '.') {
	  ok = false;
	  break;
	}
      }
    }
    if(ok) { // Recurse!
      //cout << "Moving " << c << " down" << endl;
      int costAdd = getPrice(c) * (abs(pos-posV) + STACK_SIZE-v[idxV].size());
      v[idxV].push_back(c);
      top[pos] = '.';

      go(cost + costAdd);

      // Clean:
      top[pos] = c;
      v[idxV].pop_back();
    }
  }
  
  // Try to move stuff up!
  FORI(4) {
    if(ready[i])
      continue; // No more up!
    char c = v[i].back();
    // Move up from v[i]!
    FORJ(SIZE_TOP) {
      int posTop = topPositions[j];
      int posV = 3 + 2*i;
      bool ok = true;
      if(posV < posTop) {
	for(int k = posV+1; k <= posTop; k++) {
	  if(top[k] != '.') {
	    ok = false;
	    break;
	  }
	}
      }
      else {
	for(int k = posV-1; k >= posTop; k--) {
	  if(top[k] != '.') {
	    ok = false;
	    break;
	  }
	}
      }
      if(ok) {
	//cout << "Moving " << c << " up from stack " << i << " to move " << (posTop-posV) << " in top" << endl;
	int costAdd = getPrice(c) * (abs(posTop-posV) + 1+STACK_SIZE-v[i].size());
	v[i].pop_back();

	top[posTop] = c;
	ready[i] = v[i].empty();

	go(cost + costAdd);

	// Clean:
	top[posTop] = '.';
	v[i].push_back(c);
	ready[i] = v[i].empty();
      }
    }
  }
}

int main() {
  getline(cin, s); // #######
  getline(cin, top); // #......#
  readLine(true);
  if(STACK_SIZE == 4) {
    s = "  #D#C#B#A#"; readLine(false);
    s = "  #D#B#A#C#"; readLine(false);
  }
  readLine(true); // Ignore the rest of input
  FORI(4) {
    reverse(v[i].begin(), v[i].end());
  }

  go(0);
  cout << best << endl;
}
