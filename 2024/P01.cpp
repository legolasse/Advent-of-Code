int main() {
  vector<int> L, R;
  int l, r;
  while(cin >> l >> r) {
    L.push_back(l);
    R.push_back(r);
  }
  sort(L.begin(), L.end());
  sort(R.begin(), R.end());

  int answer1 = 0, answer2 = 0;

  map<int,int> cnt;
  FORUI(R.size()) {
    int x = R[i];
    if(cnt.find(x) == cnt.end())
      cnt[x] = 0;
    cnt[x]++;
  }
  FORUI(L.size()) {
    answer1 += ABS(L[i] - R[i]);
    int x = L[i];
    if(cnt.find(x) != cnt.end())
      answer2 += x * cnt[x];
  }
  
  cout << answer1 << endl << answer2 << endl;
}
