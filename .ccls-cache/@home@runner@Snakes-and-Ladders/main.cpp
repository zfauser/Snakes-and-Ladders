/*
  Name: Zach Fauser
  Date: March 25th, 2024
  Purpose: To create a game of Snakes and Ladders in C++
*/

// Define libraries
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

// Include colors.h so that colors can be used in the program
#include "colors.h"

using namespace std;

// Define global variables
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
bool playAgain = true;
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

string getName()
/*
  Returns:
    string: what the user has inputted as their name
*/
{
  string tempName;
  cout << "What's your name: " << BLUE;
  getline(cin, tempName);
  while (tempName.empty()) {
    cout << RED << "Invalid input. Please enter a valid name: " << BLUE;
    getline(cin, tempName);
  }
  cout << RESET;
  return tempName;
}

int getRand(int min, int max)
/*
  Args:
    min (int): the minimum value that can be chosen
    max (int): the maximum value that can be chosen
  Returns:
    int: a random number between min and max
*/
{
  return rand() % (max - min + 1) + min;
}

string getCompName()
/*
  Returns:
    string: Returns a random name for the computer from the compNames array
*/
{
  return compNames[getRand(0, 9)];
}

int getUserHorT()
/*
  Returns:
    int: 0 if the user chooses heads, 1 if the user chooses tails
*/
{
  string tempUsersChoice;
  cout << "Heads or Tails? (H/T): ";
  getline(cin, tempUsersChoice);
  while ((tempUsersChoice != "H" && tempUsersChoice != "T" &&
          tempUsersChoice != "h" && tempUsersChoice != "t") ||
         cin.fail() || tempUsersChoice.empty()) {
    cout << RED << "Invalid choice. Please enter H or T: " << RESET;
    getline(cin, tempUsersChoice);
  }
  if (tempUsersChoice == "H" || tempUsersChoice == "h") {
    return 0;
  } else {
    return 1;
  }
}

char getFirstInitial(string name)
/*
  Args:
    name (string): the name that we want the first initial of
  Returns:
    char: the first initial of the name
*/
{
  return name.at(0);
}

void printBoard(int uPos, int aiPos)
/*
  Args:
    uPos (int): the user's position on the board
    aiPos (int): the computer's position on the board
  Output:
    Prints the board with the user, computer, snakes, and ladders
*/
{
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
          // if the cell is the top of a snake, print the snake number in bright
          // green
          if (cell == snakePosUpper[k]) {
            cout << BRIGHT_GREEN << setw(4) << "S" + to_string(k + 1) << RESET;
            isSnakeOrLadder = true;
            break;
          }
          // if the cell is the bottom of a snake, print the snake number in
          // green
          else if (cell == snakePosLower[k]) {
            cout << GREEN << setw(4) << "s" + to_string(k + 1) << RESET;
            isSnakeOrLadder = true;
            break;
          }
        }
        // if not a snake, check if the cell is a ladder
        if (!isSnakeOrLadder) {
          for (int k = 0; k < ladderCount; k++) {
            if (cell == ladderPosUpper[k]) {
              // if the cell is the top of a ladder, print the ladder number in
              // bright magenta
              cout << BRIGHT_MAGENTA << setw(4) << "L" + to_string(k + 1)
                   << RESET;
              isSnakeOrLadder = true;
              break;
            }
            // if the cell is the bottom of a ladder, print the ladder number in
            // magenta
            else if (cell == ladderPosLower[k]) {
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

void printPos()
/*
  Output:
    Prints the positions of the user and computer on the board and the board
  itself
*/
{
  cout << BLUE << name << " is at position " << userPos << RESET << endl;
  cout << RED << compName << " is at position " << compPos << RESET << endl;
  printBoard(userPos, compPos);
}

void checkSnakeLadderOverlap()
/*
  Purpose:
    Checks if any snakes and ladders overlap. If they do, generate a new snake
  until there are no overlaps.
*/
{
  for (int i = 0; i < snakeCount; i++) {
    for (int j = 0; j < ladderCount; j++) {
      // if a snake and ladder overlap, generate a new snake
      if (snakePosUpper.at(i) == ladderPosUpper.at(j) ||
          snakePosUpper.at(i) == ladderPosLower.at(j) ||
          snakePosLower.at(i) == ladderPosUpper.at(j) ||
          snakePosLower.at(i) == ladderPosLower.at(j)) {
        snakePosUpper.at(i) = getRand(10, 99);
        snakePosLower.at(i) = getRand(1, snakePosUpper.at(i) - 9);
        j = 0;
      }
    }
  }
}

void genSnakes()
/*
  Purpose:
    Generates a random number of snakes between 3 and 5 and assigns them random
  positions on the board.
*/
{
  snakeCount = getRand(3, 5);
  for (int i = 0; i < snakeCount; i++) {
    int upper = getRand(10, 99);
    int lower = getRand(1, upper - 9);
    for (int j = 0; j < snakePosLower.size(); j++) {
      // if the snake overlaps with another snake, generate a new snake
      if (lower == snakePosLower[j] || upper == snakePosUpper[j]) {
        upper = getRand(10, 99);
        lower = getRand(1, upper - 9);
        j = 0; // recheck new snake against all other snakes
      }
    }

    snakePosUpper.push_back(upper);
    snakePosLower.push_back(lower);
  }
}

void genLadders()
/*
  Purpose:
    Generates a random number of ladders between 3 and 7 and assigns them random
  positions on the board.
*/
{
  ladderCount = getRand(3, 7);
  for (int i = 0; i < ladderCount; i++) {
    int lower = getRand(1, 90);
    int upper = getRand(lower + 10, 100);

    for (int j = 0; j < ladderPosLower.size(); j++) {
      // if the ladder overlaps with another ladder, generate a new ladder
      if (lower == ladderPosLower[j] || upper == ladderPosUpper[j]) {
        lower = getRand(1, 90);
        upper = getRand(lower + 10, 100);
        j = 0;
      }
    }

    ladderPosUpper.push_back(upper);
    ladderPosLower.push_back(lower);
  }
}

int checkSnakesLadders(int pos)
/*
  Args:
    pos (int): the position of the user or computer
  Returns:
    int: the new position of the user or computer after checking for snakes and
  ladders
*/
{
  for (int i = 0; i < snakeCount; i++) {
    // if the user or computer lands on a snake, move them to the end of the
    // snake
    if (pos == snakePosUpper.at(i)) {
      pos = snakePosLower.at(i);
      if (usersTurn) {
        cout << BLUE << name << " landed on a snake! " << name
             << " is now at position " << pos << RESET << endl;
      } else {
        cout << RED << compName << " landed on a snake! " << compName
             << " is now at position " << pos << RESET << endl;
      }
      return pos;
    }
  }
  for (int i = 0; i < ladderCount; i++) {
    // if the user or computer lands on a ladder, move them to the top of the
    // ladder
    if (pos == ladderPosLower.at(i)) {
      pos = ladderPosUpper.at(i);
      if (usersTurn) {
        cout << BLUE << name << " landed on a ladder! " << name
             << " is now at position " << pos << RESET << endl;
      } else {
        cout << RED << compName << " landed on a ladder! " << compName
             << " is now at position " << pos << RESET << endl;
      }
      return pos;
    }
  }
  return pos;
}

void turn()
/*
  Purpose:
    This is what is run when it is the user's or computer's turn. It rolls a
  dice, moves the user or computer, checks for snakes and ladders, and prints
  the position of the user and computer.
*/
{
  // clear screen using:
  // https://stackoverflow.com/questions/17335816/clear-screen-using-c
  cout << "\033[2J\033[1;1H";
  int roll = getRand(1, 6);
  // if it is the user's turn
  if (usersTurn) {
    cout << BLUE << name << " rolled a " << roll << "!\n" << RESET;
    // if the user hasn't rolled a 6 yet, they need to roll a 6 to start moving
    if (!userRolled6) {
      if (roll == 6) {
        userRolled6 = true;
      } else {
        userRolled6 = false;
      }
    }
    // if the user has rolled a 6, they can start moving
    if (userRolled6) {
      userPos += roll;
      userPos = checkSnakesLadders(userPos);
      // if the user reaches 100, they win
      if (userPos == 100) {
        userWon = true;
        printPos();
        cout << BLUE << name << " wins!\n" << RESET;
        cout << BOLD
             << "You are about to be redirected to a page with an image, "
                "please return to this window after you are finished looking "
                "at the image\n"
             << RESET;
        return;
      } else if (userPos > 100) {
        userPos = userPos - roll;
      }
    }
    printPos();
    if (roll != 6) {
      usersTurn = false;
    } else {
      usersTurn = true;
    }
  } else {
    cout << RED << compName << " rolled a " << roll << "!\n" << RESET;
    // if the computer hasn't rolled a 6 yet, they need to roll a 6 to start
    // moving
    if (!compRolled6) {
      if (roll == 6) {
        compRolled6 = true;
      } else {
        compRolled6 = false;
      }
    }
    // if the computer has rolled a 6, they can start moving
    if (compRolled6) {
      compPos += roll;
      compPos = checkSnakesLadders(compPos);
      // if the computer reaches 100, they win
      if (compPos == 100) {
        userWon = false;
        printPos();
        cout << RED << compName << " wins!\n" << RESET;
        cout << BOLD
             << "You are about to be redirected to a page with an image, "
                "please return to this window after you are finished looking "
                "at the image\n"
             << RESET;
        return;
      } else if (compPos > 100) {
        compPos = compPos - roll;
      }
    }
    printPos();
    if (roll != 6) {
      usersTurn = true;
    } else {
      usersTurn = false;
    }
  }
}

void waitForEnter()
/*
  Purpose:
    Waits for the user to press enter before continuing
*/
{
  cin.clear();
  cout << "Press enter to continue...";
  cin.ignore();
}

bool flipCoin()
/*
  Returns:
    bool: true if the user goes first, false if the computer goes first
*/
{
  int coin = getRand(0, 1);
  if (coin == 0) {
    cout << "The coin landed on Heads!\n";
  } else {
    cout << "The coin landed on Tails!\n";
  }
  if (coin == userHorT) {
    cout << BLUE << name << " goes first!\n" << RESET;
    return true;
  } else {
    cout << RED << compName << " goes first!\n" << RESET;
    return false;
  }
}

void redirectToWinScreen()
/*
  Purpose:
    Opens a browser window with an image of the winner
*/
{
  string url;
  // Open the browser with the winner's image
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

bool askPlayAgain()
/*
  Returns:
    bool: true if the user wants to play again, false if the user doesn't want
  to play again
*/
{
  string playAgainChoice;
  cout << "Would you like to play again? (Y/N): ";
  getline(cin, playAgainChoice);
  while ((playAgainChoice != "Y" && playAgainChoice != "N" &&
          playAgainChoice != "y" && playAgainChoice != "n") ||
         cin.fail() || playAgainChoice.empty()) {
    cout << RED << "Invalid choice. Please enter Y or N: " << RESET;
    getline(cin, playAgainChoice);
  }
  if (playAgainChoice == "Y" || playAgainChoice == "y") {
    userRolled6 = false;
    compRolled6 = false;
    userPos = 0;
    compPos = 0;
    userWon = false;
    snakePosUpper.clear();
    snakePosLower.clear();
    ladderPosUpper.clear();
    ladderPosLower.clear();
    return true;
  } else {
    cout << "Hope you had fun playing Snakes and Ladders! Goodbye!";
    return false;
  }
}

int main()
/*
  Purpose:
    The main function of the program. It welcomes the user and explains the
  rules of the game. It then runs the necessary functions until the user decides
  to stop playing.
*/
{
  srand(time(0));
  cout << YELLOW << BOLD << "Welcome to Snakes and Ladders!\n\n" << RESET;
  cout << BOLD << "Rules:\n" << RESET;
  cout
      << "The goal of the game is to reach the 100th square before your "
         "opponent does. You must roll to exactly 100 (i.e if you are on space "
         "99 you need to roll a 1, if you roll more you will not move)\n";
  cout << "You must roll a 6 to start moving and if you roll a 6 during the "
          "game you continue rolling.\n";
  cout << "If you land on a snake (uppercase S), you will go down to the tail "
          "of the snake (lowercase s).\n";
  cout << "If you land on a ladder (lowercase l), you will go up to the top of "
          "the ladder (uppercase L).\n\n";
  name = getName();
  cout << "Howdy there, " << BLUE << name << RESET << "!\n";
  while (playAgain) {
    compName = getCompName();
    cout << "You will be playing against " << RED << compName << RESET << "!\n";
    userInitial = getFirstInitial(name);
    compInitial = getFirstInitial(compName);
    userHorT = getUserHorT();
    usersTurn = flipCoin();
    genSnakes();
    genLadders();
    checkSnakeLadderOverlap();
    waitForEnter();
    while (userPos < 100 && compPos < 100) {
      turn();
      waitForEnter();
    }
    redirectToWinScreen();
    playAgain = askPlayAgain();
  }
}