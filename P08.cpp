struct Vector {
  LL x, y, z;
  Vector() {}
  Vector(LL x, LL y, LL z) : x(x), y(y), z(z) {}
  Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}
  bool operator==(const Vector &v) const {
    return x==v.x && y==v.y && z==v.z;
  }
  LL d2(Vector &v) {
    LL dx = x-v.x;
    LL dy = y-v.y;
    LL dz = z-v.z;
    return dx*dx + dy*dy + dz*dz;
  }
};

typedef pair<LL,PI> PPI;
int CC[1000];

int getCCSize(int i) {
  int ret = 0;
  FORJ(1000) {
    if(CC[j] == i)
      ret++;
  }
  return ret;
}

void connect(int i, int j) {
  //cout << "Connecting " << i << " and " << j << endl;
  i = CC[i];
  j = CC[j];
  if(i == j)
    return;
  if(i > j)
    swap(i,j);
  FORK(1000) {
    if(CC[k] == j) {
      CC[k] = i;
      //cout << " " << k << " -> " << i << endl;
    }
  }
}

int main() {
  LL answer1 = 1, answer2 = 0;
  vector<Vector> V;

  int x, y, z; string s;
  while(cin >> s) {
    FORUI(s.size()) {
      if(s[i] == ',')
	s[i] = ' ';
    }
    stringstream ss; ss << s; ss >> x >> y >> z;
    V.push_back(Vector(x,y,z));
  }

  // Part 1:
  FORI(1000)
    CC[i] = i;
  vector<PPI> dists;
  FORUI(V.size()) {
    for(unsigned int j = i + 1; j < V.size(); j++) {
      dists.push_back(PPI(V[i].d2(V[j]), PI(i,j)));
    }
  }
  sort(dists.begin(), dists.end());
  int toConnect = V.size() == 1000 ? 1000 : 10;
  FORI(toConnect) {
    int a = dists[i].second.first;
    int b = dists[i].second.second;
    connect(a,b);
  }
  vector<int> ccSizes;
  FORI((int)V.size()) {
    int ccSize = getCCSize(i);
    if(ccSize > 1)
      ccSizes.push_back(ccSize);
  }
  sort(ccSizes.rbegin(), ccSizes.rend());
  FORI(3)
    answer1 *= ccSizes[i];

  // Part 2:
  for(int i = toConnect; getCCSize(0) != V.size(); i++) {
    int a = dists[i].second.first;
    int b = dists[i].second.second;
    connect(a,b);
    answer2 = V[a].x * V[b].x;
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
