vector<string> v,vWithOnlyMainPath;
char M[1000][1000];

int main() {
  // Read data:
  string line;
  while(cin >> line) {
    line = line + '.';
    v.push_back(line);
    vWithOnlyMainPath.push_back(line);
  }
  int width = (int)v[0].size();
  int height = (int)v.size();  

  // Find Start S:
  PI S;
  FORY(height) {
    FORX(width) {
      if(v[y][x] == 'S') {
	S = PI(x, y);
      }
      vWithOnlyMainPath[y][x] = ' ';
    }
  }
  cout << "S: " << S.XX << ", " << S.YY << endl;

  PI prev(S.XX, S.YY), p(S.XX, S.YY+1), tmp;
  int steps = 1;
  v[S.YY][S.XX] = '|';
  vWithOnlyMainPath[S.YY][S.XX] = '|';
  while(p != S) {
    char c = v[p.YY][p.XX];
    tmp = p;
    vWithOnlyMainPath[p.YY][p.XX] = c;

    switch(c) {
    case '|':
      if(prev.YY < p.YY) {
	p.YY++;
      }
      else {
	p.YY--;
      }
      break;
    case '-':
      if(prev.XX < p.XX) {
	p.XX++;
      }
      else {
	p.XX--;
      }
      break;
    case 'L':
      if(prev.YY != p.YY) {	
	p.XX++;
      }
      else {
	p.YY--;
      }
      break;
    case 'J':
      if(prev.YY != p.YY) {
	p.XX--;
      }
      else
	p.YY--;
      break;
    case '7':
      if(prev.YY != p.YY) {
	p.XX--;
      }
      else {
	p.YY++;
      }
      break;
    case 'F':
      if(prev.YY != p.YY) {
	p.XX++;
      }
      else {
	p.YY++;
      }
      break;
    }
    prev = tmp;
    steps++;
  }
  cout << "Answer 1: " << steps/2 << endl;

  
  cout << "Part 2" << endl;
  // Draw:
  FORY(height) {
    FORX(width) {
      for(int y2 = 0; y2 < 3; y2++) {
	for(int x2 = 0; x2 < 3; x2++) {
	  M[y*3 + y2][x*3 + x2] = ' ';
	}
      }
      char c = vWithOnlyMainPath[y][x];
      if(c == ' ') {
	M[y*3 + 1][x*3 + 1] = '.'; // Cheese
	continue;
      }
      M[y*3 + 1][x*3 + 1] = c;
      switch(c) {
      case '|':
	M[y*3 + 0][x*3 + 1] = '#';
	M[y*3 + 2][x*3 + 1] = '#';      
	break;
      case '-':
	M[y*3 + 1][x*3 + 0] = '#';
	M[y*3 + 1][x*3 + 2] = '#';
	break;
      case 'L':
	M[y*3 + 0][x*3 + 1] = '#';
	M[y*3 + 1][x*3 + 2] = '#';
	break;
      case 'J':
	M[y*3 + 0][x*3 + 1] = '#';
	M[y*3 + 1][x*3 + 0] = '#';
	break;
      case '7':
	M[y*3 + 1][x*3 + 0] = '#';
	M[y*3 + 2][x*3 + 1] = '#';
	break;
      case 'F':
	M[y*3 + 1][x*3 + 2] = '#';
	M[y*3 + 2][x*3 + 1] = '#';
	break;
      }
    }
  }

  // Flood fill!:
  M[0][0] = 'X';
  bool improved = true;
  while(improved) {
    improved = false;
    FORY(height*3) {
      FORX(width*3) {
	if(M[y][x] != 'X') {
	  continue;
	}
	int x2 = x, y2 = y-1;	
	if(y2 > 0 && (M[y2][x2] == ' ' || M[y2][x2] == '.')) {
	  M[y2][x2] = 'X';
	  improved = true;
	}
	x2 = x; y2 = y+1;	
	if(y2 < height*3 && (M[y2][x2] == ' ' || M[y2][x2] == '.')) {
	  M[y2][x2] = 'X';
	  improved = true;
	}
	x2 = x-1; y2 = y;	
	if(x2 > 0 && (M[y2][x2] == ' ' || M[y2][x2] == '.')) {
	  M[y2][x2] = 'X';
	  improved = true;
	}
	x2 = x+1; y2 = y;	
	if(x2 < width*3 && (M[y2][x2] == ' ' || M[y2][x2] == '.')) {
	  M[y2][x2] = 'X';
	  improved = true;
	}
      }
    }
  }

  LL answer2 = 0;
  FORY(height*3) {
    FORX(width*3) {
      cout << M[y][x];
      if(M[y][x] == '.')
	answer2++;
    }
    cout << endl;
  }
  cout << "Answer 2: " << answer2 << endl;
}
