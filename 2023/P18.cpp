typedef pair<PLL,PLL> QLL;

LL hexToInt(char c) {
  if(c >= 'a' && c <= 'f')
    return 10 + c-'a';
  if(c >= 'A' && c <= 'F')
    return 10 + c-'A';
  return c-'0';
}

LL answer = 0;
//LL width, height;
string dirs = "RDLU";
set<LL> DX;
vector<QLL> vertical, horizontal;
char M[400][400];

int main() {
  FORY(400) {
    FORX(400) {
      M[y][x] = '.';
    }
  }
  char dir;
  string color;
  LL cnt;
  LL x = 0, y = 0, minX = 0, minY = 0, maxX = 0, maxY = 0;
  vector<PLL> links;
  while(cin >> dir >> cnt >> color) {
    // Part 2:
    
    cnt = 0;
    FORI(5) {
      cnt = 16*cnt + hexToInt(color[2+i]);
    }
    dir = dirs[color[7]-'0'];
    //cout << color << " = " << dir << " " << cnt << endl;
    //*/
    
    switch(dir) {
    case 'U':
      vertical.push_back(QLL(PLL(x, y-cnt), PLL(x, y)));
      y-=cnt;
      minY = min(minY, y);
      break;
    case 'D':
      vertical.push_back(QLL(PLL(x, y), PLL(x, y+cnt)));
      y+=cnt;
      maxY = max(maxY, y);
      break;
    case 'L':
      horizontal.push_back(QLL(PLL(x-cnt, y), PLL(x, 0)));
      x-=cnt;
      minX = min(minX, x);
      DX.insert(x);
      break;
    case 'R':
      horizontal.push_back(QLL(PLL(x, y), PLL(x+cnt, 1)));
      x+=cnt;
      maxX = max(maxX, x);
      DX.insert(x);
      break;
    }
    links.push_back(PLL(cnt, dir));
  }
  /*
  width = (maxX-minX)+1;
  height = (maxY-minY)+1;
  x = -minX;
  y = -minY;
  FORIT(vector<PLL>, links) {
    cnt = it->first;
    dir = (char)it->second;
    FORI((int)cnt) {
      switch(dir) {
      case 'U':
	y--;
	break;
      case 'D':
	y++;
	break;
      case 'L':
	x--;
	break;
      case 'R':
	x++;
	break;
      }
      M[y][x] = '#';	
    }
  }
  FORI(height) {
    FORJ(width) {
      cout << M[i][j];
    }
    cout << endl;
  }//*/
  
  // Pseudo-Sweep line approach:
  LL prevX = *DX.begin();
  FORIT(set<LL>, DX) {
    x = *it;
    //cout << "x=" << x << ":" << endl;

    if(prevX < x-1) { // Handle space before x:
      set<PLL> DY;
      FORIT2(vector<QLL>, horizontal) {
	if(it2->first.XX <= x-1 && it2->second.XX >= x-1) {
	  DY.insert(PLL(it2->first.YY, it2->second.YY));
	}
      }
      LL prevY, dy = 0;
      bool inside = false;
      FORIT2(set<PLL>, DY) {
	if(inside) {
	  dy += it2->first - prevY + 1;
	}
	inside = it2->second;
	prevY = it2->first;
      }
      LL toAdd = dy * (x-prevX-1);
      //cout << " SUM SPACE x=[" << (prevX+1) << ";" << (x-1) << "] * " << dy << " = " << toAdd << endl;
      answer += toAdd;
    }

    // Handle line:
    set<PLL> DY;
    FORIT2(vector<QLL>, horizontal) {
      if(it2->first.XX <= x && it2->second.XX >= x) {
	DY.insert(PLL(it2->first.YY, it2->second.second));
	//cout << " y: " << it2->first.YY << endl;
      }
    }
    set<LL> V;
    FORIT2(vector<QLL>, vertical) {
      if(it2->first.XX == x) {
	//cout << " Vertical at x=" << x << ": " << (it2->first.YY) << " -> " << (it2->second.YY) << endl;
	V.insert(it2->first.YY);
	V.insert(it2->second.YY);
      }
    }
    LL prevY = DY.begin()->first, dy=0;
    bool inside1 = false, inside2 = false;
    FORIT2(set<PLL>, DY) {
      y = it2->first;
      if(inside1 || inside2) {
	dy += y-prevY;
      }

      if(V.find(y) != V.end()) {
	if(!(inside1 || inside2))
	  dy++;
	inside2 = !inside2;
      }
      else { // non-vertical line point:
	if(!(inside1 || inside2))
	  dy++;
      }
      inside1 = it2->second;

      prevY = y;
    }
    //cout << " SUM LINE x=" << x << ": " << dy << endl;
    answer+=dy;
    
    prevX = x;
  } // FOR DX

  cout << "Answer: " << answer << endl;
}
