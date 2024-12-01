LL answer1 = 0, answer2 = 0, cas = 0;
string line;
vector<string> V;

bool sameVertical(int x1, int x2) {
  FORUY(V.size()) {
    if(V[y][x1] != V[y][x2]) {
      return false;
    }
  }
  return true;
}

int diffV(int x1, int x2) {
  int ret = 0;
  FORUY(V.size()) {
    if(V[y][x1] != V[y][x2]) {
      ret++;
    }
  }
  return ret;
}

int diffH(int y1, int y2) {
  int ret = 0;
  FORUX(V[0].size()) {
    if(V[y1][x] != V[y2][x]) {
      ret++;
    }
  }
  return ret;
}

int main() {
  while(true) {
    V.clear();
    cout << endl;
    while(true) {
      if(!getline(cin, line))
	break;
      if(line == "")
	break;
      V.push_back(line);
      cout << line << endl;
    }
    cout << endl;
    if(V.empty())
      break; // Done
    
    // Cases:
    cout << "Case " << cas++ << endl;
    bool foundV = false, foundH = false;
    int height = (int)V.size();
    int width = (int)V[0].size();
    int smudgeV = 0, smudgeH = 0;

    // Check horizontal:
    cout << "Checking HORIZONTAL MID -> " << height-1 << endl;
    for(int y = height/2; y < height; y++) {
      bool ok = true;
      int d = 0;
      for(int y2 = 0; y2 < y; y2++) {
	int y3 = y + (y-y2-1);
	if(y3 >= height)
	  continue;
	if(V[y2] != V[y3]) {
	  ok = false;
	}
	d += diffH(y2,y3);
      }
      if(ok && !foundH) {
	answer1 += 100*y;
	foundH = true;
      }
      if(d == 1) {
	cout << "Found HIGHER HORIZONTAL " << y << endl;
	smudgeH++;
	answer2 += 100*y;
	cout << endl;
	FORI(height) {
	  cout << V[i] << endl;
	  if(i+1 == y) {
	    FORUJ(width)
	      cout << "-";
	    cout << endl;
	  }
	}
	cout << endl;
      }      
    }
    for(int y = height/2-1; y >= 1; y--) {
      bool ok = true;
      int d = 0;
      for(int y2 = 0; y2 < y; y2++) {
	int y3 = y + (y-y2-1);
	if(y3 >= height)
	  continue;
	if(V[y2] != V[y3]) {
	  ok = false;
	}
	d += diffH(y2,y3);
      }
      if(ok && !foundH) {
	answer1 += 100*y;
	foundH = true;
      }
      if(d == 1) {
	cout << "Found LOWER HORIZONTAL " << y << endl;
	smudgeH++;
	answer2 += 100*y;
	cout << endl;
	FORI(height) {
	  cout << V[i] << endl;
	  if(i+1 == y) {
	    FORUJ(width)
	      cout << "-";
	    cout << endl;
	  }
	}
	cout << endl;
      }
    }
    
    // Check vertical:
    cout << "Checking VERTICAL" << endl;
    for(int x = width/2; x < width; x++) {
      bool ok = true;
      int d = 0;
      for(int x2 = 0; x2 < x; x2++) {
	int x3 = x + (x-x2-1);
	if(x3 >= width)
	  continue;
	// Check:
	if(!sameVertical(x2, x3)) {
	  ok = false;
	}
	d += diffV(x2,x3);
      }
      if(ok && !foundV) {
	answer1 += x;
	foundV = true;
      }
      if(d == 1) {
	cout << "Found HIGHER VERTICAL " << x << endl;
	answer2 += x;
	smudgeV++;
	cout << endl;
	FORI(height) {
	  FORJ(width) {
	    cout << V[i][j];
	    if(j+1 == x) {
	      cout << "|";
	    }
	  }
	  cout << endl;
	}
	cout << endl;
      }
    }
    for(int x = width/2-1; x >= 1; x--) {
      bool ok = true;
      int d = 0;
      for(int x2 = 0; x2 < x; x2++) {
	int x3 = x + (x-x2-1);
	if(x3 >= width)
	  continue;
	// Check:
	if(!sameVertical(x2, x3)) {
	  ok = false;
	}
	d += diffV(x2,x3);
      }
      if(ok && !foundV) {
	answer1 += x;
	foundV = true;
      }
      if(d == 1) {
	cout << "Found LOWER VERTICAL " << x << endl;
	smudgeV++;
	answer2 += x;
	cout << endl;
	FORI(height) {
	  FORJ(width) {
	    cout << V[i][j];
	    if(j+1 == x) {
	      cout << "|";
	    }
	  }
	  cout << endl;
	}
	cout << endl;
      }
    }

    if(smudgeH + smudgeV != 1) {
      cout << "UNEXPECTED! " << smudgeH << " / " << smudgeV << endl;
      die();
    }
  } // while true


  cout << "Answer 1" << endl << answer1 << endl;
  cout << "Answer 2" << endl << answer2 << endl;
} // main
