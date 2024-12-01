int answer1 = 0, answer2 = 0;
vector<string> V;
string line;
bool M[150][150];
int width, height = 2, N[8] = {1,0,-1,0,0,1,0,-1};
char special[8] = {'>', '>', '<', '<', 'v', 'v', '^', '^'};

void walk1(PI p, int steps) {
  int x = p.XX, y = p.YY;
  if(M[y][x])
    return; // Already visited
  if(y == height-2) {
    answer1 = max(answer1, steps);
  }
  M[y][x] = true; // Visit self
  char c = V[y][x];
  for(int i = 0; i < 8; i+=2) { // Step to neighbour:
    int nx = x + N[i];
    int ny = y + N[i+1];
    if(M[ny][nx])
      continue; // Neighbour already visited
    char n = V[ny][nx];
    if(n == '#')
      continue; // Neighbour not visitable
    //if(c != '.' && c != special[i])
    //  continue; // Cannot visit neighbour from slope
    walk1(PI(nx,ny), steps+1);
  }
  M[y][x] = false; // Unvisit self
}

int main() {
  V.push_back("##############################################################################################################################################");
  while(getline(cin, line)) {
    V.push_back(line);
    height++;
    width = (int)line.size();
  }
  V.push_back("##############################################################################################################################################");
  cout << "Read map of size " << width << " x " << height << endl;
  // Initiallize M:
  FORY(height) {
    FORX(width) {
      M[y][x] = false;
    }
    cout << V[y] << endl;
  }

  // Walk:
  walk1(PI(1,1), 0);

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
