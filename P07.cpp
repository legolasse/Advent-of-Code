// For part 1, remove the Joker stuff:
#define JOKER 0

int valueToI(char c) {
  switch(c) {
  case 'A':
    return 14;
  case 'K':
    return 13;
  case 'Q':
    return 12;
  case 'J':
    return JOKER;
  case 'T':
    return 10;
  default:
    return c-'0';
  }
}

struct Hand {
  string orig;
  int cards[5], cnt[15];
  LL bet;
};

int maxSame(const Hand &h) {
  int cntJokers = h.cnt[0];
  int ret = 0;
  for(int i = 1; i < 15; i++) {
    if(h.cnt[i] + cntJokers >= ret) {
      ret = h.cnt[i] + cntJokers;
    }
  }
  return ret;
}
bool house(const Hand &h) {
  // Check that max 2 numbers present:
  int cnt = 0;
  for(int i = 1; i < 15; i++) {
    if(h.cnt[i] > 0) {
      cnt++;
    }
  }
  return cnt <= 2;
}
int numPairs(const Hand &h) {
  int pairs = 0;
  for(int i = 1; i < 15; i++) {
    if(h.cnt[i] == 2) {
      pairs++;
    }
  }
  return pairs + h.cnt[JOKER];
}

bool cmpHighCard(Hand const * const h1, Hand const * const h2) {  
  FORI(5) {
    int a = valueToI(h1->orig[i]);
    int b = valueToI(h2->orig[i]);
    if(a != b)
      return a > b;
  }
  return false;
}

bool cmp(Hand const * const h1, Hand const * const h2) {
  int same1 = maxSame(*h1);
  int same2 = maxSame(*h2);
  
  if(same1 >= 5 && same2 >= 5)
    return cmpHighCard(h1, h2);
  if(same2 >= 5)
    return false;
  if(same1 >= 5)
    return true;

  if(same1 >= 4 && same2 >= 4)
    return cmpHighCard(h1, h2);
  if(same2 >= 4)
    return false;
  if(same1 >= 4)
    return true;

  if(house(*h1) && house(*h2))
    return cmpHighCard(h1, h2);
  if(house(*h2))
    return false;
  if(house(*h1))
    return true;

  if(same1 >= 3 && same2 >= 3)
    return cmpHighCard(h1, h2);
  if(same2 >= 3)
    return false;
  if(same1 >= 3)
    return true;

  int p1 = numPairs(*h1);
  int p2 = numPairs(*h2);
  if(p1 == p2) {
    return cmpHighCard(h1, h2);
  }

  return p1 > p2;
}

typedef pair<Hand*,int> PHI;

int main() {
  vector<Hand*> hands; // Hand, bet
  int bet;
  string s;

  while(cin >> s >> bet) {
    Hand *h = new Hand();
    FORI(5) {
      h->cards[i] = valueToI(s[i]);
    }
    sort(h->cards, h->cards+5);
    FORI(15) h->cnt[i] = 0;
    FORI(5) {
      h->cnt[h->cards[i]]++;
    }
    h->bet = bet;
    h->orig = s;
    hands.push_back(h);
  }
  sort(hands.begin(), hands.end(), cmp);
  
  LL answer1 = 0;
  for(int i = 0; i < (int)hands.size(); i++) {
    Hand *h = hands[i];
    LL winnings = h->bet * (((LL)hands.size())-i);
    answer1+=winnings;
    cout << "Hand " << h->orig << " bet " << h->bet << " winnings: " << winnings << endl;
  }
  cout << "Answer 1: " << answer1 << endl;
}
