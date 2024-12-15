vector<string> G, G2;
int W, W2, H;
vector<char> moves;
PI robot, robot2;

bool move(const char direction, const PI &p) {
  char c = G[p.YY][p.XX];
  if(c == '#')
    return false;
  if(c == '.')
    return true;
  PI next = p;
  switch(direction) {
  case '^':
    next.YY--;
    break;
  case '<':
    next.XX--;
    break;
  case '>':
    next.XX++;
    break;
  case 'v':
    next.YY++;
    break;
  if(!move(direction, next))
    return false;
  // Move:
  G[next.YY][next.XX] = c;
  G[p.YY][p.XX] = '.';
  return true;
}

void move(const char direction) {
  if(move(direction, robot)) {
    switch(direction) {
    case '^':
      robot.YY--;
      break;
    case '<':
      robot.XX--;
      break;
    case '>':
      robot.XX++;
      break;
    case 'v':
      robot.YY++;
      break;
  }
}

bool canMove(const char direction, const PI p, bool fromNeighbour) {
  char c = G2[p.YY][p.XX];
  if(c == '#')
    return false;
  if(c == '.')
    return true;

  PI next = p;
  switch(direction) {
  case '^':
    next.YY--;
    break;
  case '<':
    next.XX--;
    break;
  case '>':
    next.XX++;
    break;
  case 'v':
    next.YY++;
    break;
  }
  if(!canMove(direction, next, false))
    return false;
  if(!fromNeighbour && next.YY != p.YY) {
    if(c == ']') {
      if(!canMove(direction, PI(p.XX-1, p.YY), true))
	return false;
    }
    else if(c == '[') {
      if(!canMove(direction, PI(p.XX+1, p.YY), true))
	return false;
    }
  }
  return true;
}

void move2(const char direction, const PI &p, bool checked) {
  char c = G2[p.YY][p.XX];
  if(c == '#')
    return;
  if(c == '.')
    return;

  PI next = p;
  switch(direction) {
  case '^':
    next.YY--;
    break;
  case '<':
    next.XX--;
    break;
  case '>':
    next.XX++;
    break;
  case 'v':
    next.YY++;
    break;
  }
  move2(direction, next, false);

  if(!checked && next.YY != p.YY) {
    if(c == ']') {
      move2(direction, PI(p.XX-1, p.YY), true);
    }
    else if(c == '[') {
      move2(direction, PI(p.XX+1, p.YY), true);
    }
  }
  // Move:
  G2[next.YY][next.XX] = c;
  G2[p.YY][p.XX] = '.';
}

void move2(const char direction) {
  if(canMove(direction, robot2, true)) {
    move2(direction, robot2, true);
    switch(direction) {
    case '^':
      robot2.YY--;
      break;
    case '<':
      robot2.XX--;
      break;
    case '>':
      robot2.XX++;
      break;
    case 'v':
      robot2.YY++;
      break;
    default:
      cout << "Unknown direction: '" << direction << "'" << endl;
      die();
    }
  }
}

int main() {
  int answer1 = 0, answer2 = 0;

  string line;
  while(getline(cin, line)) {
    if(line == "")
      break;
    G.push_back(line);
    W = (int)line.size();
    W2 = 2*W;
    FORX(W) {
      char c = line[x];
      if(c == '@') {
	robot = PI(x, H);
      }
    }
    // Part 2:
    stringstream ss;
    FORX(W) {
      char c = line[x];
      if(c == 'O') {
	ss << '[' << ']';
      }
      else if(c != '@') {
	ss << c << c;
      }
      else {
	ss << c << '.';
	robot2 = PI(x*2, H);
      }
    }
    G2.push_back(ss.str());
    
    H++;
  }

  while(getline(cin, line)) {
    FORUI(line.size()) {
      char c = line[i];
      moves.push_back(c);
    }
  }
  
  // Part 1:
  FORUI(moves.size()) {
    char c = moves[i];
    move(c);
  }
  FORY(H) {
    FORX(W) {
      char c = G[y][x];
      if(c == 'O') {
	answer1 += x + 100 * y;
      }
    }
  }

  // Part 2:
  FORUI(moves.size()) {
    char c = moves[i];
    move2(c);
  }
  FORY(H) {
    FORX(W2) {
      char c = G2[y][x];
      if(c == '[') {
	answer2 += x + 100 * y;
      }
    }
  }
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
