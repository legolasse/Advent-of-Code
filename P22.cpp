#define EMPTY -1
// Remove all but numbers from input
struct Brick {
  int x1, y1, z1, x2, y2, z2;
};
vector<Brick> V;
// min is 0, 0, 1 (floor at z=0)
int maxX = 0, maxY = 0, maxZ = 0, G[10][10][361];

void printTower() {
  for(int z = maxZ; z >= 0; z--) {
    FORX(maxX+1) {
      FORY(maxY+1) {
	if(G[x][y][z] == EMPTY)
	  cout << " .";
	else
	  cout << " " << (char)('A'+G[x][y][z]);
      }
    }
    cout << endl;
  }
}

int main() {
  FORX(10) {
    FORY(10) {
      FORZ(361) {
	G[x][y][z] = EMPTY;
      }
    }
  }
  
  // Read input:
  Brick b;
  while(cin >> b.x1 >> b.y1 >> b.z1 >> b.x2 >> b.y2 >> b.z2) {
    maxX = max(max(maxX, b.x1), b.x2);
    maxY = max(max(maxY, b.y1), b.y2);
    maxZ = max(max(maxZ, b.z1), b.z2);
    // Insert into grid:
    for(int x = min(b.x1,b.x2); x <= max(b.x1,b.x2); x++) {
      for(int y = min(b.y1,b.y2); y <= max(b.y1,b.y2); y++) {
	for(int z = min(b.z1,b.z2); z <= max(b.z1,b.z2); z++) {
	  G[x][y][z] = (int)V.size();
	}
      }
    }
    V.push_back(b);
  }
  cout << "Input with " << V.size() << " bricks" << endl;
  cout << "MAX " << maxX << ", " << maxY << ", " << maxZ << endl;
  int i = 1;
  FORIT(vector<Brick>, V) {
    cout << (i++) << ": " << it->x1 << " " << it->y1 << " " << it->z1 << " " << it->x2 << " " << it->y2 << " " << it->z2 << endl;
  }
  //printTower();

  // Move input down:
  set<int> moved;
  for(int z = 1; z <= maxZ; z++) {
    cout << "CHECKING Z=" << z << endl;
    FORX(maxX+1) {
      FORY(maxY+1) {
	int brickIdx = G[x][y][z];
	if(brickIdx == EMPTY || moved.find(brickIdx) != moved.end())
	  continue; // Empty or already moved.

	cout << " Moving brick " << brickIdx << endl;
	Brick &b = V[brickIdx];
	int lowestZ = min(b.z1, b.z2);
	while(lowestZ > 1) {
	  // Check there is space below:
	  bool ok = true;
	  for(int xx = min(b.x1,b.x2); xx <= max(b.x1,b.x2); xx++) {
	    for(int yy = min(b.y1,b.y2); yy <= max(b.y1,b.y2); yy++) {
	      if(G[xx][yy][lowestZ-1] != EMPTY) {
		ok = false;
	      }
	    }
	  }
	  if(!ok)
	    break;
	  lowestZ--;
	}
	int dz = min(b.z1,b.z2) - lowestZ;
	cout << "  Is moved dz=" << dz << " down" << endl;
	// Remove:
	for(int xx = min(b.x1,b.x2); xx <= max(b.x1,b.x2); xx++) {
	  for(int yy = min(b.y1,b.y2); yy <= max(b.y1,b.y2); yy++) {
	    for(int zz = min(b.z1,b.z2); zz <= max(b.z1,b.z2); zz++) {
	      //cout << " REMOVING AT " << xx << ", " << yy << ", " << zz << endl;
	      G[xx][yy][zz] = EMPTY;
	    }
	  }
	}
	//cout << " REMOVED " << brickIdx << endl;
	//printTower();
	// Insert:
	for(int xx = min(b.x1,b.x2); xx <= max(b.x1,b.x2); xx++) {
	  for(int yy = min(b.y1,b.y2); yy <= max(b.y1,b.y2); yy++) {
	    for(int zz = min(b.z1,b.z2); zz <= max(b.z1,b.z2); zz++) {
	      G[xx][yy][zz-dz] = brickIdx;
	    }
	  }
	}
	//cout << " INSERTED" << endl;
	//printTower();
	// Update b:
	b.z1-=dz;
	b.z2-=dz;
	moved.insert(brickIdx);
      } // for y
    } // for x
  } // for z
  //printTower();

  // Part 1:
  // For each brick, if only one pillar, then mark pillar as important:
  set<int> important;
  FORI((int)V.size()) {
    Brick &b = V[i];
    set<int> pillars;
    int z = min(b.z1,b.z2)-1;
    for(int x = min(b.x1,b.x2); x <= max(b.x1,b.x2); x++) {
      for(int y = min(b.y1,b.y2); y <= max(b.y1,b.y2); y++) {
	int below = G[x][y][z];
	if(below != EMPTY)
	  pillars.insert(below);
      }
    }
    if(pillars.size() == 1) {
      important.insert(*pillars.begin());
    }
  }
  cout << "Answer 1: " << V.size() - important.size() << endl;

  // Part 2:
  int answer2 = 0;
  FORI((int)V.size()) {
    set<int> fallen;
    fallen.insert(i);
    bool improved = true;
    while(improved) {
      improved = false;
      // Try all bricks:
      FORJ((int)V.size()) {
	if(fallen.find(j) != fallen.end())
	  continue; // Already fallen
	Brick &b = V[j];
	int z = min(b.z1,b.z2)-1;
	bool ok = z != 0; // Cannot fall from start
	for(int x = min(b.x1,b.x2); x <= max(b.x1,b.x2); x++) {
	  for(int y = min(b.y1,b.y2); y <= max(b.y1,b.y2); y++) {
	    int below = G[x][y][z];
	    if(below != EMPTY && fallen.find(below) == fallen.end())
	      ok = false;
	  }
	}
	if(ok) {
	  fallen.insert(j);
	  improved = true;
	}
      }
    } // while improved
    //cout << "Disintegrate " << (char)('A'+i) << " causes " << fallen.size()-1 << endl;

    answer2 += (int)fallen.size()-1;
  }
  // 1496 low
  cout << "Answer 2: " << answer2 << endl;
}
