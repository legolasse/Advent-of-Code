// Add number of steps as first line of input
LL answer1 = 0;
string line;
int height = 0, width;
vector<string> V;

/**
 * Lagrange's (simplified) Interpolation Formula
 * y = ax^2 + bx + c, x=[0,1,2], y=[y0,y1,y2]
 * y = (x^2-3x+2) * y0/2 - (x^2-2x)*y1 + (x^2-x) * y2/2
 * =>
 * a = y0/2 - y1 + y2/2
 * b = -3*y0/2 + 2*y1 - y2/2
 * c = y0
 */
LL simplifiedLagrange(LL y0, LL y1, LL y2, LL x) {
  LL a = y0/2 - y1 + y2/2;
  LL b = (-3*y0 + 4*y1 - y2)/2; // Divide by to at last, so we can use integers.
  LL c = y0;
  //cout << "Lagrange a: " << a << ", b: " << b << ", c: " << c << endl;
  return a*x*x + b*x + c;
}

int main() {
  // Read input:
  GI(steps1);
  GI(steps2);
  set<PI> S1, S2;
  while(cin >> line) {
    V.push_back(line);
    width = (int)line.size();
    FORX(width) {
      char c = line[x];
      if(c == 'S') {
	S1.insert(PI(x, height));
	cout << "S found at " << x << ", " << height << endl;
      }
    }
    height++;
  }
  cout << "Read map " << width << " x " << height << endl;
  
  LL values[3], valueIdx = 0;
  int rem = steps2 % width;
  cout << "REM: " << rem << endl;
  LL target = (steps2-rem)/width;
  cout << "Target: " << target << endl;
  int N[8] = {-1, 0, 1, 0, 0, 1, 0, -1};
  for(int i = 1; true; i++) {
    if(!S2.empty())
      die();
    FORIT(set<PI>, S1) {
      int x = it->XX, y = it->YY;
      for(int j = 0; j < 8; j+=2) {
	int xx = x + N[j];
	int yy = y + N[j+1];
	if(V[(yy+100*height)%height][(xx+100*width)%width] != '#') {
	  S2.insert(PI(xx,yy));
	}
      }      
    }
    if(i == steps1) {
      cout << "Answer 1: " << S2.size() << endl;
    }
    if(i%width == rem) {
      cout << i << ": " << S2.size() << endl;;
      values[valueIdx++] = (int)S2.size();
      if(valueIdx == 3) {
	break; // Done.
      }
    }
    S1.clear();
    swap(S1, S2);
  }
  cout << "Answer 2: " << simplifiedLagrange(values[0], values[1], values[2], target) << endl;

  /*
    Analysis of test input:
    width = height = 131
    Notice: 26501365 = 202300 * 131 + 65 = target * width + REM
    S is in the middle!
    No obstacle in row, nor column of S => 131 steps to "S" of neighbours => periodic expansion!
    Side length 131
   */
}
