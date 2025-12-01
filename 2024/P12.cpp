vector<string> V;
int W, H = 0;
set<PI> seen, seen2;
int regions[141][141];
map<int,int> areaMap; // region -> area

typedef pair<PI,PI> fence;

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

// Return perimeter
int countPerimeter(const PI &p, char expect) {
  int x = p.XX;
  int y = p.YY;
  if(x < 0 || y < 0 || x >= W || y >= H)
    return 1;
  char c = V[y][x];
  if(c != expect)
    return 1;
  if(seen.find(p) != seen.end())
    return 0;

  // Expected and in region:
  seen.insert(p);
  seen2.insert(p);
  int ret = 0;
  ret += countPerimeter(PI(x-1,y), expect);
  ret += countPerimeter(PI(x+1,y), expect);
  ret += countPerimeter(PI(x,y-1), expect);
  ret += countPerimeter(PI(x,y+1), expect);
  return ret;
}

int main() {
  int answer1 = 0, answer2 = 0;
  
  string line;
  while(getline(cin, line)) {
    V.push_back(line);
    W = (int)line.size();
    H++;
  }

  // Part 1:
  int areaIndex = 0;
  FORY(H) {
    FORX(W) {
      const PI p(x,y);
      if(seen.find(p) != seen.end())
	continue;
      seen2.clear();
      // Enclose region:
      const char c = V[y][x];
      const int perimeter = countPerimeter(p, c);
      const int area = (int)seen2.size();
      
      cout << V[y][x] << " at " << x << ", " << y << " area: " << area << ", perimeter: " << perimeter << endl;
      answer1 += area * perimeter;

      areaMap[areaIndex] = area;
      FORIT(set<PI>, seen2) {
	int x2 = it->XX;
	int y2 = it->YY;
	regions[y2][x2] = areaIndex;
      }

      areaIndex++;
    }
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2:
  for(int areaI = 0; areaI < areaIndex; areaI++) {
    int sides = 0;
    // Fences to the left of areaI:
    FORX(W) {
      bool prevIsFence = false;
      FORY(H) {
	bool isArea = regions[y][x] == areaI;
	bool isFence = isArea && (x == 0 || regions[y][x-1] != areaI);
	if(!prevIsFence && isFence)
	  sides++;
	prevIsFence = isFence;
      }
    }
    // Fences to the right of areaI:
    FORX(W) {
      bool prevIsFence = false;
      FORY(H) {
	bool isArea = regions[y][x] == areaI;
	bool isFence = isArea && (x == W-1 || regions[y][x+1] != areaI);
	if(!prevIsFence && isFence)
	  sides++;
	prevIsFence = isFence;
      }
    }
    // Fences above area:
    FORY(H) {
      bool prevIsFence = false;
      FORX(W) {
	bool isArea = regions[y][x] == areaI;
	bool isFence = isArea && (y == 0 || regions[y-1][x] != areaI);
	if(!prevIsFence && isFence)
	  sides++;
	prevIsFence = isFence;
      }
    }
    // Fences below area:
    FORY(H) {
      bool prevIsFence = false;
      FORX(W) {
	bool isArea = regions[y][x] == areaI;
	bool isFence = isArea && (y == H-1 || regions[y+1][x] != areaI);
	if(!prevIsFence && isFence)
	  sides++;
	prevIsFence = isFence;
      }
    }
    answer2 += sides * areaMap[areaI];
  }

  cout << "Answer 2: " << answer2 << endl;
}
