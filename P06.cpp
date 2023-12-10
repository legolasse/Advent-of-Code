string line, ignore;
LL t[100], record[100], answer1 = 1, answer2;
int size = 0;

int main() {
  // Get ts:
  getline(cin, line);
  stringstream ss1; ss1 << line; ss1 >> ignore;
  while(ss1 >> t[size]) {
    size++;
  }
  getline(cin, line);
  stringstream ss2; ss2 << line; ss2 >> ignore;
  size = 0;
  while(ss2 >> record[size]) {
    size++;
  }
  cout << size << " boat races!" << endl;
  
  FORI(size) { // For each race:
    cout << "Race " << i << " time " << t[i] << " record " << record[i] << endl;

    // Part 1:
    LL wins = 0;
    FORJ(t[i]) { // For each time:
      LL dist = j * (t[i]-j);
      if(dist > record[i]) {
	wins++;
      }
    }
    cout << " Ways of winning: " << wins << endl;
    answer1 *= wins;

    
  }
  cout << "Answer 1: " << answer1 << endl;
  // For answer 2, just manually update the input file.
}
