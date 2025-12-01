string file;

vector<PI> v; // sectorIndex -> position
vector<int> sizes;

void pri() {
  int sectorIndex = 0;
  FORUI(v.size()) {
    int sector = v[i].first;
    int position = v[i].second;
    int size = sizes[sector];
    while(sectorIndex < position) {
      cout << '.';
      sectorIndex++;
    }
    FORJ(size) {
      cout << sector;
      sectorIndex++;
    }
  }
  cout << endl << endl;
}

int main() {
  cin >> file;
  
  int *sectors = new int[file.size()*9]; // idx => sector
  int sectorIndex = 0;

  // Fill sectors:
  FORUI(file.size()) {
    int c = file[i]-'0'; // 0 - 9

    // Part 2:
    if(i % 2 == 0) {
      sizes.push_back(c);
      v.push_back(PI(i/2, sectorIndex));
    }

    // Part 1:
    FORJ(c) {
      int x = (i % 2 == 0) ? i/2 : -1;
      sectors[sectorIndex++] = x;
    }
  }

  // Part 1:
  int low = 0, high = sectorIndex-1;
  while(low < high) {
    if(sectors[low] != -1) {
      low++;
      continue;
    }
    if(sectors[high] == -1) {
      high--;
      continue;
    }
    sectors[low++] = sectors[high];
    sectors[high] = -1;
    high--;
  }

  LL answer1 = 0;
  FORI(high+1) {
    cout << sectors[i];
    answer1 += i * sectors[i];
  }
  cout << endl;
  cout << "Answer1: " << answer1 << endl;

  // Part 2:
  // vector<PI> v; // sectorIndex -> position
  // vector<int> sizes;
  cout << "Initial disk:" << endl;
  pri();
  
  for(int sector = (int)v.size()-1; sector > 0; sector--) {
    int size = sizes[sector];
    // Find sector:
    int pos = (int)v.size()-1;
    while(v[pos].first != sector) {
      pos--;
    }
    // Find gap:
    int gapPos = 0;
    while(gapPos < pos &&
	  (v[gapPos].second + sizes[v[gapPos].first] + size > v[gapPos+1].second)) {
      gapPos++;
    }
    if(gapPos == pos) {
      continue;
    }
    // Move:
    int newIndex = v[gapPos].second + sizes[v[gapPos].first];
    //cout << " Moving sector " << sector << " to position " << (gapPos+1) << " at index " << newIndex << endl;
    
    // Erase:
    vector<PI>::iterator it = v.begin();
    advance(it, pos);
    v.erase(it);

    it = v.begin();
    advance(it, gapPos+1);
    v.insert(it, PI(sector, newIndex));

    //pri();
  }
  LL answer2 = 0;
  FORI(v.size()) {
    int sector = v[i].first;
    int position = v[i].second;
    int size = sizes[sector];
    FORJ(size) {
      answer2 += (position+j)*sector;
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
