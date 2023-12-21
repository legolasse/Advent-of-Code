// PLL: init, range

LL answer1 = 0, answer2 = 0;
string line, ignore;
LL seeds[100], seed, dest, source, len;
int size = 0;
set<PLL> ranges1, ranges2, rangesLeftOver;

int main() {
  // Read first line:
  getline(cin, line);
  stringstream ss2; ss2 << line;
  ss2 >> ignore;
  while(ss2 >> seed) {
    seeds[size++] = seed;
  }
  getline(cin, line); // Empty line
  //cout << size << " seeds" << endl;

  // Part 2 setup:
  for(int i = 0; i < size; i+=2) {
    PLL p(seeds[i], seeds[i+1]);
    ranges1.insert(p);
  }
  /*cout << "Initial ranges:" << endl;
  FORIT(set<PLL>, ranges1) {
    cout << " " << it->first << " len " << it->second << endl;
  }
  cout << endl;*/

  // Handle each conversion step:
  bool converted[100];
  while(true) { // For each conversion:
    FORI(size) {
      converted[i] = false;
    }
    if(!getline(cin, line)) {
      break; // No top line:
    }
    //cout << line << endl; // Map line
    
    while(getline(cin, line)) { // Each conversion line:
      if(line == "") {
	break; // Empty line
      }
      stringstream ss; ss << line;
      ss >> dest >> source >> len;
      //cout << source << " -> " << dest << " (" << (dest-source) << ") len " << len << endl;

      // Part 1:
      FORI(size) {
	if(converted[i])
	  continue;
	seed = seeds[i];
	if(seed >= source && seed < source+len) {
	  seeds[i] = dest + (seed-source);
	  converted[i] = true;
	}
      }

      // Part 2:
      FORIT(set<PLL>, ranges1) {
	LL rangeStart = it->first;
	LL rangeLen = it-> second;
	if(rangeStart >= source + len) {
	  rangesLeftOver.insert(*it);
	  continue; // Out of range
	}
	if(source >= rangeStart+rangeLen) {
	  rangesLeftOver.insert(*it);
	  continue; // Out of range
	}
	//cout << " Converting range " << rangeStart << " len " << rangeLen << endl;
	// We have overlap!
	if(rangeStart < source) {
	  rangeLen -= source-rangeStart;
	  rangeStart = source;
	}
	if(rangeStart+rangeLen > source+len) {
	  rangeLen -= (rangeStart+rangeLen) - (source+len);
	}
	// Convert:
	PLL to(dest + (rangeStart - source), rangeLen);
	ranges2.insert(to);
	//cout << "  to " << to.XX << " len " << to.YY << endl;
	// Handle left over:
	if(rangeStart > it->first) {
	  rangesLeftOver.insert(PLL(it->first, rangeStart-it->first));
	}
	if(rangeStart+rangeLen < it->first+it->second) {
	  rangesLeftOver.insert(PLL(rangeStart+rangeLen, (it->first+it->second)-(rangeStart+rangeLen )));
	}
      } // FORIT
      swap(rangesLeftOver, ranges1);
      rangesLeftOver.clear();
    } // For each conversion line

    FORIT(set<PLL>, ranges2) {
      ranges1.insert(*it);
    }
    rangesLeftOver.clear();
    ranges2.clear();
    /*
    cout << "Ranges after conversion:" << endl;
    FORIT(set<PLL>, ranges1) {
      cout << " " << it->first << " len " << it->second << endl;
    }
    cout << endl;*/
  } // For each conversion

  // Answer 1:
  answer1 = seeds[0];
  FORI(size-1) {
    answer1 = min(answer1, seeds[i+1]);
  }
  cout << "Answer 1" << endl << answer1 << endl;

  // Answer 2:
  answer2 = 9999999999;
  FORIT(set<PLL>, ranges1) {
    answer2 = min(answer2, it->first);
  }
  cout << "Answer 2" << endl << answer2 << endl;
} // main
