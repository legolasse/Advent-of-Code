typedef pair<PI,PI> QI;
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define INF 99999999
string line;
vector<string> v;
int width, height, V[141][141][4][11], dx[]={1,0,-1,0}, dy[]={0,1,0,-1};

int main() {
  // Read input:
  while(getline(cin, line)) {
    v.push_back(line);
  }
  width = (int)v[0].size();
  height = (int)v.size();
  cout << "Map size " << width << " x " << height << endl;

  // Set up:
  FORY(height) {
    FORX(width) {
      FORI(4) {
	FORJ(11) {
	  V[y][x][i][j] = INF;
	}
      }
    }
  }
  V[0][0][RIGHT][10] = 0;
  V[0][0][DOWN][10] = 0;

  bool improved = true;
  while(improved) {
    improved = false;
    FORX(width) {
      FORY(height) {
	for(int dir = 0; dir < 4; dir++) {
	  PI from(x-dx[dir], y-dy[dir]);
	  
	  if(from.XX < 0 || from.YY<0 || from.XX >= width || from.YY >= height)
	    continue;

	  // For part 1, use < 3:
	  for(int stamina = 0; stamina < 10; stamina++) {
	    if(V[from.YY][from.XX][dir][stamina+1] != INF) {
	      int cost = V[from.YY][from.XX][dir][stamina+1] + (v[y][x]-'0');
	      if(V[y][x][dir][stamina] > cost) {
		V[y][x][dir][stamina] = cost;
		improved = true;
	      }
	      // Turn left and right:
	      if(stamina > 6)
		continue;
	      for(int dir2 = 0; dir2 < 4; dir2++) {
		if(dir2 == dir || ((dir2+2)%4==dir))
		  continue;
		if(V[y][x][dir2][10] > cost) {
		  V[y][x][dir2][10] = cost;
		  improved = true;
		}
	      }
	    }

	  } // for stamina
	} // for dir
      } // FORY
    } // FORX
  } // while improved
  
  int answer = INF;
  for(int i = 2; i < 4; i++) { // For part 1 start from 0
    FORJ(11) { // 4 for part 1
      answer = min(answer, V[height-1][width-1][i][j]);
      //cout << "dir " << i << ", stamina " << j << ": " << V[height-1][width-1][i][j] << endl;
    }    
  }
  cout << "Answer: " << answer << endl;
}
