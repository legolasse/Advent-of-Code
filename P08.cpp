vector<string> grid; // grid is only used for debugging.
set<char> chars; // Chars in use.
vector<PI> positions[256]; // char -> positions
set<PI> antinodes, allAntinodes;

bool add(const PI &p, set<PI> &s) {
  if(p.XX >= 0 && p.YY >= 0 && p.XX < (int)grid[0].size() && p.YY < (int)grid.size()) {
    s.insert(p);
    return true;
  }
  return false;
}

int main() {
  string line;
  while(getline(cin, line)) {
    FORUI(line.size()) {
      int y = (int)grid.size();
      char c = line[i];
      if(c != '.') {
	chars.insert(c);
	positions[(int)c].push_back(PI((int)i, y));
      }
    }
    grid.push_back(line);
  }

  for(set<char>::iterator it = chars.begin(); it != chars.end(); it++) {
    char c = *it;
    FORUI(positions[(int)c].size()) {
      PI p1(positions[(int)c][i]);
      for(unsigned int j = i+1; j < positions[(int)c].size(); j++) {
	PI p2(positions[(int)c][j]);
	int dx = p2.XX-p1.XX;
	int dy = p2.YY-p1.YY;

	// Part 1:
	{
	  PI p3(p1.XX - dx, p1.YY - dy);
	  add(p3, antinodes);
	  PI p4(p2.XX + dx, p2.YY + dy);
	  add(p4, antinodes);
	}

	// Part 2:
	for(int mult = 0; true; mult++) {
	  PI p3(p1.XX - mult*dx, p1.YY - mult*dy);
	  if(!add(p3, allAntinodes)) {
	    break;
	  }
	}
	for(int mult = 0; true; mult++) {
	  PI p4(p2.XX + mult*dx, p2.YY + mult*dy);
	  if(!add(p4, allAntinodes)) {
	    break;
	  }
	}
      }
    }
  }
  
  cout << "Answer 1: " << antinodes.size() << endl;
  cout << "Answer 2: " << allAntinodes.size() << endl;
}
