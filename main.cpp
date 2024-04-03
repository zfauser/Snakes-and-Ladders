#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "colors.h"

using namespace std;

string name = "";
string compName = "";
bool usersTurn;
bool userRolled6 = false;
bool compRolled6 = false;
int userHorT = 0;
int userPos = 0;
int compPos = 0;
char userInitial;
char compInitial;
string compNames[] = {"Elon Musk",        "Bill Gates",       "Jeff Bezos",
                      "Mark Zuckerberg",  "Joe Biden",        "Taylor Swift",
                      "Olivia Rodrigo",   "Allan N. Caughey", "Xi Jinping",
                      "Bjarne Stroustrup"};
vector<int> snakePosUpper;
vector<int> snakePosLower;
vector<int> ladderPosUpper;
vector<int> ladderPosLower;
int ladderCount = 0;
int snakeCount = 0;
bool userWon = false;
string elonURL = "https://zfauser.github.io/winner/elonmuskwin.png";
string billURL = "https://zfauser.github.io/winner/billgateswin.png";
string jeffURL = "https://zfauser.github.io/winner/jeffbezoswin.png";
string markURL = "https://zfauser.github.io/winner/markzuckerbergwin.png";
string joeURL = "https://zfauser.github.io/winner/joebidenwin.png";
string taylorURL = "https://zfauser.github.io/winner/taylorswiftwin.png";
string oliviaURL = "https://zfauser.github.io/winner/oliviarodrigowin.png";
string allanURL = "https://zfauser.github.io/winner/alcaugheywin.png";
string xiURL = "https://zfauser.github.io/winner/xijinpingwin.png";
string bjarneURL = "https://zfauser.github.io/winner/bjarnestroustrupwin.png";
string youURL = "https://zfauser.github.io/winner/youwin.png";

string getName() {
  string tempName;
  cout << "What's your name: ";
  getline(cin, tempName);
  while (tempName.empty()) {
    cout << "Please enter a valid name: ";
    getline(cin, tempName);
  }
  return tempName;
}

int getRand(int min, int max) { return rand() % (max - min + 1) + min; }

string getCompName() { return compNames[getRand(0, 9)]; }

int getUserHorT() {
  string tempUsersChoice;
  cout << "Heads or Tails? (H/T): ";
  cin >> tempUsersChoice;
  while (tempUsersChoice != "H" && tempUsersChoice != "T" &&
         tempUsersChoice != "h" && tempUsersChoice != "t") {
    cout << "Invalid choice. Please enter H or T: ";
    cin >> tempUsersChoice;
  }
  if (tempUsersChoice == "H" || tempUsersChoice == "h") {
    return 0;
  } else {
    return 1;
  }
}

char getFirstInitial(string name) { return name.at(0); }

void printBoard(int uPos, int aiPos) {
  // use  i-- in order to print from 100 down to 1
  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      int cell;
      // if row is even, print from left to right
      if (i % 2 == 0) {
        cell = i * 10 + j + 1;
      }
      // otherwise, print from right to left
      else {
        cell = i * 10 + 10 - j;
      }
      cout << "| ";
      // if both user and computer are at the same position, print both initials
      if (cell == uPos && cell == aiPos) {
        cout << BLUE << setw(3) << userInitial << RED << compInitial << RESET;
      }
      // otherwise, if the cell is the user's position, print the user's initial
      else if (cell == uPos) {
        cout << BLUE << setw(4) << userInitial << RESET;
      }
      // otherwise, if the cell is the computer's position, print the computer's
      // initial
      else if (cell == aiPos) {
        cout << RED << setw(4) << compInitial << RESET;
      }
      // otherwise...
      else {
        bool isSnakeOrLadder = false;
        // check if the cell is a snake
        for (int k = 0; k < snakeCount; k++) {
          if (cell == snakePosUpper[k]) {
            cout << BRIGHT_GREEN << setw(4) << "S" + to_string(k + 1) << RESET;
            isSnakeOrLadder = true;
            break;
          } else if (cell == snakePosLower[k]) {
            cout << GREEN << setw(4) << "s" + to_string(k + 1) << RESET;
            isSnakeOrLadder = true;
            break;
          }
        }
        // if not a snake, check if the cell is a ladder
        if (!isSnakeOrLadder) {
          for (int k = 0; k < ladderCount; k++) {
            if (cell == ladderPosUpper[k]) {
              cout << BRIGHT_MAGENTA << setw(4) << "L" + to_string(k + 1)
                   << RESET;
              isSnakeOrLadder = true;
              break;
            } else if (cell == ladderPosLower[k]) {
              cout << MAGENTA << setw(4) << "l" + to_string(k + 1) << RESET;
              isSnakeOrLadder = true;
              break;
            }
          }
        }
        // if not a snake or ladder, print the cell number
        if (!isSnakeOrLadder) {
          cout << setw(4) << cell;
        }
      }
    }
    cout << "|\n";
  }
}

void printPos() {
  cout << name << " is at position " << userPos << endl;
  cout << compName << " is at position " << compPos << endl;
  printBoard(userPos, compPos);
}

void checkSnakeLadderOverlap() {
  for (int i = 0; i < snakeCount; i++) {
    for (int j = 0; j < ladderCount; j++) {
      // if a snake and ladder overlap, generate a new snake
      if (snakePosUpper.at(i) == ladderPosUpper.at(j) ||
          snakePosUpper.at(i) == ladderPosLower.at(j) ||
          snakePosLower.at(i) == ladderPosUpper.at(j) ||
          snakePosLower.at(i) == ladderPosLower.at(j)) {
        snakePosUpper.at(i) = getRand(10, 99);
        snakePosLower.at(i) = getRand(1, snakePosUpper.at(i) - 10);
      }
    }
  }
}

void genSnakes() {
  snakeCount = getRand(3, 7);
  for (int i = 0; i < snakeCount; i++) {
    int upper = getRand(10, 99);
    int lower = getRand(1, upper - 10);

    for (int j = 0; j < snakePosLower.size(); j++) {
      // if the snake overlaps with another snake, generate a new snake
      while (lower == snakePosLower[j] || upper == snakePosUpper[j]) {
        lower = getRand(1, upper - 10);
        j = 0; // recheck new snake against all other snakes
      }
    }

    snakePosUpper.push_back(upper);
    snakePosLower.push_back(lower);
  }
}

void genLadders() {
  ladderCount = getRand(3, 7);
  for (int i = 0; i < ladderCount; i++) {
    int lower = getRand(1, 90);
    int upper = getRand(lower + 10, 100);

    for (int j = 0; j < ladderPosLower.size(); j++) {
      while (lower == ladderPosLower[j] || upper == ladderPosUpper[j]) {
        lower = getRand(1, 90);
        upper = getRand(lower + 10, 100);
        j = 0;
      }
    }

    ladderPosUpper.push_back(upper);
    ladderPosLower.push_back(lower);
  }
}

int checkSnakesLadders(int pos) {
  for (int i = 0; i < snakeCount; i++) {
    if (pos == snakePosUpper.at(i)) {
      pos = snakePosLower.at(i);
      if (usersTurn) {
        cout << name << " landed on a snake! " << name << " is now at position "
             << pos << endl;
      } else {
        cout << compName << " landed on a snake! " << compName
             << " is now at position " << pos << endl;
      }
      return pos;
    }
  }
  for (int i = 0; i < ladderCount; i++) {
    if (pos == ladderPosLower.at(i)) {
      pos = ladderPosUpper.at(i);
      if (usersTurn) {
        cout << name << " landed on a ladder! " << name
             << " is now at position " << pos << endl;
      } else {
        cout << compName << " landed on a ladder! " << compName
             << " is now at position " << pos << endl;
      }
      return pos;
    }
  }
  return pos;
}

void turn() {
  // clear screen using:
  // https://stackoverflow.com/questions/17335816/clear-screen-using-c
  cout << "\033[2J\033[1;1H";
  int roll = getRand(1, 6);
  if (usersTurn) {
    cout << name << " rolled a " << roll << "!\n";
    if (!userRolled6) {
      if (roll == 6) {
        userRolled6 = true;
      } else {
        userRolled6 = false;
      }
    }
    if (userRolled6) {
      userPos += roll;
      userPos = checkSnakesLadders(userPos);
      if (userPos == 100) {
        userWon = true;
        printPos();
        cout << name << " wins!\n";
        return;
      } else if (userPos > 100) {
        userPos = userPos - roll;
      }
    }
    printPos();
    usersTurn = false;
  } else {
    cout << compName << " rolled a " << roll << "!\n";
    if (!compRolled6) {
      if (roll == 6) {
        compRolled6 = true;
      } else {
        compRolled6 = false;
      }
    }
    if (compRolled6) {
      compPos += roll;
      compPos = checkSnakesLadders(compPos);
      if (compPos == 100) {
        userWon = false;
        printPos();
        cout << compName << " wins!\n";
        return;
      } else if (compPos > 100) {
        compPos = compPos - roll;
      }
    }
    printPos();
    usersTurn = true;
  }
}

void waitForAnyKey() {
  cin.clear();
  cout << "Press any key to continue...";
  cin.ignore();
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

void redirectToWinScreen() {
  // open an image that shows who won
  string url;
  if (userWon) {
    url = youURL;
  } else {
    if (compName == "Elon Musk") {
      url = elonURL;
    } else if (compName == "Bill Gates") {
      url = billURL;
    } else if (compName == "Jeff Bezos") {
      url = jeffURL;
    } else if (compName == "Mark Zuckerberg") {
      url = markURL;
    } else if (compName == "Joe Biden") {
      url = joeURL;
    } else if (compName == "Taylor Swift") {
      url = taylorURL;
    } else if (compName == "Olivia Rodrigo") {
      url = oliviaURL;
    } else if (compName == "Allan N. Caughey") {
      url = allanURL;
    } else if (compName == "Xi Jinping") {
      url = xiURL;
    } else if (compName == "Bjarne Stroustrup") {
      url = bjarneURL;
    }
  }
  string command = "xdg-open " + url;
  (void)system(command.c_str());
}

int main() {
  srand(time(0));
  cout << "Welcome to Snakes and Ladders!\n";
  name = getName();
  cout << "Howdy there, " << name << "!\n";
  compName = getCompName();
  cout << "You will be playing against " << compName << "!\n";
  userInitial = getFirstInitial(name);
  compInitial = getFirstInitial(compName);
  userHorT = getUserHorT();
  usersTurn = flipCoin();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  waitForAnyKey();
  genSnakes();
  genLadders();
  checkSnakeLadderOverlap();
  while (userPos < 100 && compPos < 100) {
    turn();
    waitForAnyKey();
  }
  redirectToWinScreen();
}