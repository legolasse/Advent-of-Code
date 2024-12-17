vector<int> program;
LL registers[3];

LL getCombo(int opcode) {
  if(opcode <= 3)
    return opcode;
  return registers[opcode-4];
}

void run(LL regA, vector<int> &ret) {
  int ptr = 0;
  registers[0] = regA;
  registers[1] = 0;
  registers[2] = 0;
  
  while(ptr < (int)program.size()) {
    int instruction = program[ptr++];
    int literal = program[ptr++];
    LL combo = getCombo(literal);

    switch(instruction) {
    case 0: // adv
      registers[0] /= (1 << combo);
      break;
    case 1: // bxl
      registers[1] = registers[1] ^ literal;
      break;
    case 2: // bst
      registers[1] = combo % 8;
      break;
    case 3: // jnz
      if(registers[0] != 0)
	ptr = literal;
      break;
    case 4: // bxc
      registers[1] = registers[1] ^ registers[2];
      break;
    case 5: // out
      ret.push_back(combo % 8);
      break;
    case 6: // bdv
      registers[1] = registers[0] / (1 << combo);
      break;
    case 7: // cdv
      registers[2] = registers[0] / (1 << combo);
      break;
    }
  }
}

LL findDigit(int k, LL base) {
  if(k == (int)program.size())
    return base;
  LL best = -1;

  int digit = program[program.size() - 1 - k];
  // Try to add a digit:
  FORI(8) {
    LL regA = (base * 8) + i;
    vector<int> v;
    run(regA, v);
    if(v[0] == digit) {
      // Digit OK. Try to finish all:
      LL full = findDigit(k+1, regA);
      if(full != -1 && (best == -1 || full < best)) // Found a solution!
	best = full;
    }
  }
  return best;
}

int main() {
  string ignore, line;
  FORI(3) {
    cin >> ignore >> ignore >> registers[i];
  }
  cin >> ignore >> line;
  FORUI(line.size()) {
    if(line[i] == ',')
      line[i] = ' ';
  }
  stringstream ss; ss << line;
  int x;
  while(ss >> x) {
    program.push_back(x);
  }

  // Part 1:
  vector<int> v;
  run(registers[0], v);

  cout << "Answer 1: ";
  FORUI(v.size()) {
    if(i > 0)
      cout << ",";
    cout << v[i];
  }
  cout << endl;

  // Part 2:
  // Match bytes of
  // Register A from left to right
  // with
  // program from right to left:
  LL answer2 = findDigit(0, 0);
  cout << "Answer 2: " << answer2 << endl;
}
