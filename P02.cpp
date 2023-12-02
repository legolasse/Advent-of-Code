// Sanitize input:
//  RM [:,]
//  Make ; into ' 0 ; '
LL answer1 = 0, answer2 = 0;
LL maxR = 12, maxG = 13, maxB = 14, cnt, gameID;
string line, ignore, color;

int main() {
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    ss >> ignore >> gameID;
    cout << "Game " << gameID << endl;
    LL minR = 0, minG = 0, minB = 0;
    bool ok = true;
    while(ss >> cnt >> color) {      
      if(color == ";") {
	continue;
      }
      if(color == "red") {
	if(cnt > maxR) {
	  ok = false;
	}
	minR = max(minR, cnt);
      }
      if(color == "green") {
	if(cnt > maxG) {
	  ok = false;
	}
	minG = max(minG, cnt);
      }
      if(color == "blue") {
	if(cnt > maxB) {
	  ok = false;
	}
	minB = max(minB, cnt);
      }
    }
    if(ok) {
      answer1 += gameID;
    }
    answer2 += minR * minG * minB;
  } // while getline
  cout << "Answer 1" << endl << answer1 << endl;
  cout << "Answer 2" << endl << answer2 << endl;
} // main
