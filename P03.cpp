LL get(string &s, int digitsLeft, int idx, LL cur) {
  if(digitsLeft == 0)
    return cur;

  int largestI = idx;
  for(int i = idx; i < (int)s.size()-digitsLeft+1; i++) {
    if(s[i] > s[largestI])
      largestI = i;
  }
  return get(s, digitsLeft-1, largestI+1, 10 * cur + s[largestI]-'0');
}

int main() {
  LL answer1 = 0, answer2 = 0;
  string s;

  while(cin >> s) {
    answer1 += get(s, 2, 0, 0);
    answer2 += get(s, 12, 0, 0);
  }

  cout << "Answer1: " << answer1 << endl;
  cout << "Answer2: " << answer2 << endl;
}
