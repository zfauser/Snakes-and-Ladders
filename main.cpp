#include <iostream>
#include <iomanip>

using namespace std;

string name;
string compName;
bool usersTurn;
int userHorT = 0;
int userPos = 0;
int compPos = 0;
string compNames[] = {"Elon Musk", "Bill Gates", "Jeff Bezos", "Mark Zuckerberg", "Joe Biden", "Taylor Swift", "Olivia Rodrigo", "Allan N. Caughey", "Xi Jinping", "Bjarne Stroustrup"};

string getName() {
  string tempName;
  cout << "What's your name: ";
  getline(cin, tempName);  
  return tempName;
}

int getRand(int min, int max) {
  return rand() % (max - min + 1) + min;
}

string getCompName() {
  return compNames[getRand(0, 9)];
}

int getUserHorT() {
  string tempUsersChoice;
  cout << "Heads or Tails? (H/T): ";
  cin >> tempUsersChoice;
  while (tempUsersChoice != "H" && tempUsersChoice != "T" && tempUsersChoice != "h" && tempUsersChoice != "t") {
    cout << "Invalid choice. Please enter H or T: ";
    cin >> tempUsersChoice;
  }
  if (tempUsersChoice == "H" || tempUsersChoice == "h") {
    return 0;
  } else {
    return 1;
  }
}

bool flipCoin() {
  int coin = getRand(0, 1);
  if (coin == 0) {
    cout << "The coin landed on Heads!\n";
  } else {
    cout << "The coin landed on Tails!\n";
  }
  if (coin == userHorT) {
    cout << name << " goes first!\n";
    return true;
  } else {
    cout << compName << " goes first!\n";
    return false;
  }
}
/*
{
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
["","","","","","","","","",""]
}
*/
void printBoard(int uPos, int aiPos) {
  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      if (i % 2 == 0) {
        cout << "|" << setw(4) << left << i * 10 + j + 1;
      } else {
        cout << "|" << setw(4) << left << i * 10 + 10 - j;
      }
    }
    for (int j = 0; j < 10; j++) {
      if (i % 2 == 0) {
        cout << "|" << setw(4) << left;
      } else {
        cout << "|" << setw(4) << left;
      }
    }
    cout << "|\n";
  }
}

void printPos() {
  cout << name << " is at position " << userPos << endl;
  cout << compName << " is at position " << compPos << endl;
}

void turn() {
  
}

int main() {
  srand(time(0));
  cout << "Welcome to Snakes and Ladders!\n";
  // name = getName();
  name = "zach";
  cout << "Howdy there, " << name << "!\n";
  compName = getCompName();
  cout << "You will be playing against " << compName << "!\n";
  // userHorT = getUserHorT();
  userHorT = 0;
  usersTurn = flipCoin();
  printBoard(userPos, compPos);
}