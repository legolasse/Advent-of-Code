// Split input on ,
LL answer1 = 0, answer2 = 0;
string s;
vector<PSI> v[256];

int main() {
  while(cin >> s) {
    LL h = 0;
    LL labelHash;
    char operation = 0;
    string label = "";
    int lens;
    FORUI(s.size()) {
      char c = s[i];
      if(c == '=' || c == '-') {
	labelHash = h;
	operation = c;
      }
      else if(operation != 0) {
	lens = c-'0';
      }
      else { // operation == 0
	label += c;
      }
      h+=c;
      h*=17;
      h%=256;
    }
    answer1+=h;

    // Part 2:
    if(operation == '-') {
      // Find label:
      for(vector<PSI>::iterator it = v[labelHash].begin(); it != v[labelHash].end(); it++) {
	if(it->first == label) {
	  v[labelHash].erase(it);
	  break;
	}
      }
    }
    else {
      bool inserted = false;
      for(vector<PSI>::reverse_iterator it = v[labelHash].rbegin(); it != v[labelHash].rend(); it++) {
	if(it->first == label) {
	  it->second = lens;
	  inserted = true;
	  break;
	}
      }
      if(!inserted) {
	v[labelHash].push_back(PSI(label, lens));
      }
    }
    cout << "After '" << s << "'" << endl;
    FORI(256) {
      if(v[i].empty())
	continue;
      cout << "Box " << i << ":";
      FORUJ(v[i].size()) {
	cout << " [" << v[i][j].first << " " << v[i][j].second << "]";
      }
      cout << endl;
    }
    cout << endl;
  }

  cout << "Answer1: " << answer1 << endl;
  FORI(256) {
    FORUJ(v[i].size()) {
      answer2 += (i+1) * (j+1) * v[i][j].second;
    }
  }
  cout << "Answer2: " << answer2 << endl;
}
