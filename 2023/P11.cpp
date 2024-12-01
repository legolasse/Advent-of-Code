LL answer1 = 0, answer2 = 0;
string line;
vector<PI> G1; // Galaxies
set<int> xs;
map<int,int> mx; // Expand to x

int main() {
  int y = 0;
  int width;
  while(cin >> line) {
    width = (int)line.size();
    int cnt = 0;    
    FORX(width) {
      if(line[x] == '#') {
	G1.push_back(PI(x,y));
	cnt++;
	xs.insert(x);
      }
    }
    y++;
    if(cnt == 0)
      y+=1000000-1; // For part 1, just use += 1
  }

  // Expand on x:
  for(int x = 0, X = 0; x < width; x++, X++) {
    if(xs.find(x) == xs.end()) {
      X+=1000000-1; // For part 1, just use += 1
    }
    else {
      mx.insert(PI(x,X));
    }
  }
  // Update galaxies 
  FORI((int)G1.size()) {
    G1[i].XX = mx[G1[i].XX];
  }

  // Compute sum of distances:
  FORI((int)G1.size()) {
    int x1 = G1[i].XX, y1 = G1[i].YY;
    for(int j = i+1; j < (int)G1.size(); j++) {
      int x2 = G1[j].XX, y2 = G1[j].YY;
      answer1 += abs(x2-x1) + abs(y2-y1);
    }
  }

  cout << "Answer: " << answer1 << endl;
}
